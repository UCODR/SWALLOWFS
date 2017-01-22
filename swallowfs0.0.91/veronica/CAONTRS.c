#include "CAONTRS.h"

int CAONTRS_HASHKEY(BYTE *key,//输出hash结果
							BYTE *context,//原文
							int strlen
							)//计算值
{
	int resTF;
	resTF=AONTRS_HASHKEY(key,context,strlen);
	if(resTF==FALSE)
	{
		show_error("CAONTRS","CAONTRS_HASHKEY","the hash value cannot calculate");
		return FALSE;
	}
	return TRUE;
}
int CAONTRS_CHRYPTEXT(BYTE *out,
							BYTE *in,
							int strlen,
							BYTE *key,
							int keylen)//重新定义加密接口
{
	
	int resTF;
	resTF=AONTRS_CHRYPTEXT(out,in,strlen,key,keylen);
	if(resTF==FALSE)
	{
		show_error("CAONTRS","CAONTRS_HASHKEY","the encrypt text cannot calculate");
		return FALSE;
	}
	return TRUE;
}
int CAONTRS_XORKEY(BYTE *out,
						BYTE *in,
						int strlen)//将in异或out存到out
{
	int resTF;
	resTF=AONTRS_XORKEY(out,in,strlen);
	if(resTF==FALSE)
	{
		show_error("CAONTRS","CAONTRS_HASHKEY","the XOR key cannot calculate");
		return FALSE;
	}
	return TRUE;
}
int CAONTRS_CHRYPTER(BYTE *cipertext,//密文
							BYTE *context,//原文
							int strlen)
{
	//这个函数要改进一下主要的区别
	BYTE *originalcipertext,*curcipertext;
	
	BYTE *hashvalue,*hashkey;
	BYTE *randnum;
	int resTF,hashlen,cpylen;

	hashlen=SHA256_DIGEST_LENGTH;
	cpylen=strlen-hashlen;//一样需要计算偏移量

	originalcipertext=cipertext;
	randnum=cipertext+cpylen;//计算位置

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

	hashkey=talloc(BYTE,hashlen);
	if(hashkey==NULL)
	{
		show_error("CAONTRS","CAONTRS_CHRYPTER","No memory");
		return FALSE;
	}

	hashvalue=talloc(BYTE,hashlen);
	if(hashvalue==NULL)
	{
		show_error("CAONTRS","CAONTRS_CHRYPTER","No memory");
		return FALSE;
	}
	//不是一个随机值我们先要计算报文的hash值
	resTF=CAONTRS_HASHKEY(hashkey,context,cpylen);//进行hash计算
	if(resTF==FALSE)
	{
		show_error("CAONTRS","CAONTRS_CHRYPTER","hash key cannot calculate");
		return FALSE;
	}
	resTF=CAONTRS_CHRYPTEXT(originalcipertext,context,cpylen,hashkey,SHA256_DIGEST_LENGTH);
	if(resTF==FALSE)
	{
		show_error("AONTRS","AONTRS_CHRYPTER","chrypt text cannot calculate");
		return FALSE;
	}
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
//生成一组share
int CAONTRS_RS(AONTSHAREGROUP *sharegroupptr,
					BYTE *cipertext,
					CODEPARA *codeptr,
					int strlen)
{
	int resTF;
	resTF=AONTRS_RS(sharegroupptr,cipertext,codeptr,strlen);
	if(resTF==FALSE)
	{
		show_error("CAONTRS","CAONTRS_HASHKEY","the RS cannot calculate");
		return FALSE;
	}
	return TRUE;
}
int CAONTRS_STORE(AONTSHAREGROUP *sharegroupptr)//根据当前参数将数据存入
{
	int resTF;
	resTF=AONTRS_STORE(sharegroupptr);
	if(resTF==FALSE)
	{
		show_error("CAONTRS","CAONTRS_HASHKEY","the sharegroup cannot store");
		return FALSE;
	}
	return TRUE;
}
//给定一个内容给定一个地址集合尝试
int CAONTRS_API(BYTE *content,int strlen,ADDRESSLIST *addresslistptr)
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
		show_error("AONTRS","AONTRS_STORE","No memory");
		return FALSE;
	}

	memspace=talloc(BYTE,cpylen+codesize);
	if(memspace==NULL)
	{
		show_error("AONTRS","AONTRS_STORE","No memory");
		return FALSE;
	}
	curmemptr=memspace;

	sharegroupptr=talloc(AONTSHAREGROUP,1);
	if(sharegroupptr==NULL)
	{
		show_error("AONTRS","AONTRS_STORE","No memory");
		return FALSE;
	}

	shareptr=talloc(AONTSHARE,totnum);
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

	resTF=CAONTRS_CHRYPTER(cpytext,content,cpylen);//加密
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

	resTF=CAONTRS_STORE(sharegroupptr);
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