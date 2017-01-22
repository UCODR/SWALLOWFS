#include "AONTRS.h"
//所有参数以字节为单位
int AONTRS_RANDKEY(BYTE *content,
							int strlen)
{
	int i;
	BYTE randnum,*curconptr;
	curconptr=content;
	//一个一个生成随机数
	for(i=0;i<strlen;i++)
	{
		randnum=rand()%256;
		mcpy(curconptr,&randnum,BYTE,1);
		curconptr++;
	}
	return TRUE;
}
int AONTRS_HASHKEY(BYTE *key,//输出hash结果
							BYTE *context,//原文
							int strlen
							)//计算值
{
	SHA256_CTX sha256;
	if(key==NULL)
	{
		key=talloc(BYTE,SHA256_DIGEST_LENGTH);//生成空间
		if(key==NULL)
		{
			show_error("AONTRS","AONTRS_HASHKEY","No memory");
			return FALSE;
		}
	}
	
	//初始化
	SHA256_Init(&sha256);
	SHA256_Update(&sha256,context,strlen);//计算
	SHA256_Final(key,
			&sha256);//hash结果输出
	return TRUE;
}
int AONTRS_XORKEY(BYTE *out,
						BYTE *in,
						int strlen)
{
	int i=0;
	for(i=0;i<strlen;i++)
	{
		(*out)=(*out)^(*in);
		out++;
		in++;
	}
	return TRUE;
}
//重新定义加密接口
int AONTRS_CHRYPTEXT(BYTE *out,
							BYTE *in,
							int strlen,
							BYTE *key,
							int keylen)
{
	int i,j;
	BYTE *curin,*curout;
	AES_KEY *keyvalue;
	int en_len;
	BYTE *envalue,*invalue;
	envalue=talloc(BYTE,AES_BLOCK_SIZE);
	if(envalue==NULL)
	{
		show_error("AONTRS","AONTRS_CHRYPTEXT","No memory");
		return FALSE;
	}
	//envalue[3]='\0';//我们就加密16位一个block
	invalue=talloc(BYTE,AES_BLOCK_SIZE);
	if(invalue==NULL)
	{
		show_error("AONTRS","AONTRS_CHRYPTEXT","No memory");
		return FALSE;
	}
	bzero(invalue,BYTE,AES_BLOCK_SIZE);
	//invalue[3]='\0';//我们就加密16位一个block
	keyvalue=talloc(AES_KEY,1);
	if(envalue==NULL)
	{
		show_error("AONTRS","AONTRS_CHRYPTEXT","No memory");
		return FALSE;
	}
	AES_set_encrypt_key(key,keylen*8,keyvalue);
	en_len=strlen/AES_BLOCK_SIZE;//变成字节
	curout=out;curin=in;
	for(i=0;i<en_len;i++)
	{

		mcpy(invalue,&i,BYTE,4);
		AES_encrypt(invalue,envalue,keyvalue);
		//需要加密两个8位
		for(j=0;j<AES_BLOCK_SIZE;j++)
		{
			(*curout)=(*curin)^(*envalue);//加密
			curout++;curin++;
		}
		//(*out)=(*in)^(*envalue);//加密
		//out++;in++;
	}
	free(envalue);
	free(keyvalue);
	return TRUE;
}

int AONTRS_CHRYPTER(BYTE *cipertext,//密文
							BYTE *context,//原文
							int strlen)
{
	BYTE *originalcipertext,*curcipertext;
	
	BYTE *hashvalue;
	BYTE *randnum;
	int resTF,hashlen,cpylen;

	hashlen=SHA256_DIGEST_LENGTH;
	cpylen=strlen-hashlen;

	originalcipertext=cipertext;//开始写
	randnum=cipertext+cpylen;//调整到最后的区域

	if(originalcipertext==NULL)
	{
		show_error("AONTRS","AONTRS_CHRYPTER","No memory");
		return FALSE;
	}
	if(randnum==NULL)
	{
		show_error("AONTRS","AONTRS_CHRYPTER","No memory");
		return FALSE;
	}
	//先生成一个随机数
	resTF=AONTRS_RANDKEY(randnum,hashlen);
	if(resTF==FALSE)
	{
		show_error("AONTRS","AONTRS_CHRYPTER","random number cannot generated");
		return FALSE;
	}
	
	//key->rd_key=talloc(BYTE,60);
	hashvalue=talloc(BYTE,hashlen);
	if(hashvalue==NULL)
	{
		show_error("AONTRS","AONTRS_CHRYPTER","No memory");
		return FALSE;
	}
	resTF=AONTRS_CHRYPTEXT(originalcipertext,context,cpylen,randnum,SHA256_DIGEST_LENGTH);
	if(resTF==FALSE)
	{
		show_error("AONTRS","AONTRS_CHRYPTER","chrypt text cannot calculate");
		return FALSE;
	}
	//对于最后的值取hash
	
	resTF=AONTRS_HASHKEY(hashvalue,originalcipertext,SHA256_DIGEST_LENGTH);
	if(resTF==FALSE)
	{
		show_error("AONTRS","AONTRS_CHRYPTER","hash value cannot calculate");
		return FALSE;
	}
	resTF=AONTRS_XORKEY(randnum,hashvalue,SHA256_DIGEST_LENGTH);
	if(resTF==FALSE)
	{
		show_error("AONTRS","AONTRS_CHRYPTER","XOR value cannot calculate");
		return FALSE;
	}
	return TRUE;
}
int AONTRS_RS(AONTSHAREGROUP *sharegroupptr,
					BYTE *cipertext,
					CODEPARA *codeptr,
					int strlen)//生成一组share
{
	int resTF;
	resTF=cauchy_API_Context(sharegroupptr,codeptr,cipertext,strlen);
	if(resTF==FALSE)
	{
		show_error("AONTRS","AONTRS_RS","cauch_RS cannot calculate");
		return FALSE;
	}
	return TRUE;
}
int AONTRS_STORE(AONTSHAREGROUP *sharegroupptr)//根据当前参数将数据存入
{
	int i,resTF,sharenum;
	AONTSHARE *shareptr,*curshareptr;
	sharenum=sharegroupptr->groupsize;
	shareptr=sharegroupptr->sharegroupptr;
	curshareptr=shareptr;
	for(i=0;i<sharenum;i++)
	{
		resTF=file_FILELAYER_SHARE_WRITER(curshareptr);
		if(resTF==FALSE)
		{
			show_error("AONTRS","AONTRS_STORE","share cannot be stored");
			return FALSE;
		}
		curshareptr++;
	}
	return TRUE;
}
int AONTRS_API(BYTE *content,int strlen,ADDRESSLIST *addresslistptr)
{
	int i,resTF,cpylen,sharesize,codesize;
	BYTE *cpytext,*memspace,*curmemptr;
	AONTSHAREGROUP *sharegroupptr;
	AONTSHARE *shareptr,*curshareptr;
	CODEPARA *codeptr;
	SHAREADDRESS *addressptr,*curaddressptr;
	int totnum,codenum,datanum;

	addressptr=addresslistptr->addressptr;
	curaddressptr=addressptr;

	codeptr=addresslistptr->codeptr;
	totnum=codeptr->totnum;
	codenum=codeptr->codenum;
	datanum=codeptr->datanum;

	cpylen=strlen+SHA256_DIGEST_LENGTH;//我们来计算一下空间单位是字节
	sharesize=cpylen/datanum;
	codesize=sharesize*codenum;//计算当前的编码块长度

	cpytext=talloc(BYTE,cpylen);
	if(cpytext==NULL)
	{
		show_error("AONTRS","AONTRS_API","No memory");
		return FALSE;
	}

	memspace=talloc(BYTE,cpylen+codesize);
	if(memspace==NULL)
	{
		show_error("AONTRS","AONTRS_API","No memory");
		return FALSE;
	}
	curmemptr=memspace;

	sharegroupptr=talloc(AONTSHAREGROUP,1);
	if(sharegroupptr==NULL)
	{
		show_error("AONTRS","AONTRS_API","No memory");
		return FALSE;
	}

	shareptr=talloc(AONTSHARE,totnum);
	if(shareptr==NULL)
	{
		show_error("AONTRS","AONTRS_API","No memory");
		return FALSE;
	}
	curshareptr=shareptr;
	for(i=0;i<totnum;i++)//使用原来的数据
	{
		//分点内存空间由于之前已经分了一整块所以只要
		curshareptr->content=curmemptr;
		curshareptr->sizenum=sharesize;
		curshareptr->storepath=curaddressptr->storepath;
		curmemptr=curmemptr+sharesize;
		curaddressptr++;
		curshareptr++;
	}
	sharegroupptr->sharegroupptr=shareptr;
	sharegroupptr->groupsize=totnum;

	resTF=AONTRS_CHRYPTER(cpytext,content,cpylen);//加密
	if(resTF==FALSE)
	{
		show_error("AONTRS","AONTRS_API","share cannot be ctrypted");
		return FALSE;
	}
	if(codenum>0)
	{
		resTF=AONTRS_RS(sharegroupptr,cpytext,codeptr,cpylen);
		if(resTF==FALSE)
		{
			show_error("AONTRS","AONTRS_API","share cannot be encoded");
			return FALSE;
		}
	}

	resTF=AONTRS_STORE(sharegroupptr);
	if(resTF==FALSE)
	{
		show_error("AONTRS","AONTRS_API","shares cannot be stored");
		return FALSE;
	}
	free(cpytext);
	free(memspace);
	free(shareptr);
	free(sharegroupptr);
	return TRUE;
}