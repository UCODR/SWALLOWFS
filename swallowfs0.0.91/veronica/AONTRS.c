#include "AONTRS.h"
//���в������ֽ�Ϊ��λ
int AONTRS_RANDKEY(BYTE *content,
							int strlen)
{
	int i;
	BYTE randnum,*curconptr;
	curconptr=content;
	//һ��һ�����������
	for(i=0;i<strlen;i++)
	{
		randnum=rand()%256;
		mcpy(curconptr,&randnum,BYTE,1);
		curconptr++;
	}
	return TRUE;
}
int AONTRS_HASHKEY(BYTE *key,//���hash���
							BYTE *context,//ԭ��
							int strlen
							)//����ֵ
{
	SHA256_CTX sha256;
	if(key==NULL)
	{
		key=talloc(BYTE,SHA256_DIGEST_LENGTH);//���ɿռ�
		if(key==NULL)
		{
			show_error("AONTRS","AONTRS_HASHKEY","No memory");
			return FALSE;
		}
	}
	
	//��ʼ��
	SHA256_Init(&sha256);
	SHA256_Update(&sha256,context,strlen);//����
	SHA256_Final(key,
			&sha256);//hash������
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
//���¶�����ܽӿ�
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
	//envalue[3]='\0';//���Ǿͼ���16λһ��block
	invalue=talloc(BYTE,AES_BLOCK_SIZE);
	if(invalue==NULL)
	{
		show_error("AONTRS","AONTRS_CHRYPTEXT","No memory");
		return FALSE;
	}
	bzero(invalue,BYTE,AES_BLOCK_SIZE);
	//invalue[3]='\0';//���Ǿͼ���16λһ��block
	keyvalue=talloc(AES_KEY,1);
	if(envalue==NULL)
	{
		show_error("AONTRS","AONTRS_CHRYPTEXT","No memory");
		return FALSE;
	}
	AES_set_encrypt_key(key,keylen*8,keyvalue);
	en_len=strlen/AES_BLOCK_SIZE;//����ֽ�
	curout=out;curin=in;
	for(i=0;i<en_len;i++)
	{

		mcpy(invalue,&i,BYTE,4);
		AES_encrypt(invalue,envalue,keyvalue);
		//��Ҫ��������8λ
		for(j=0;j<AES_BLOCK_SIZE;j++)
		{
			(*curout)=(*curin)^(*envalue);//����
			curout++;curin++;
		}
		//(*out)=(*in)^(*envalue);//����
		//out++;in++;
	}
	free(envalue);
	free(keyvalue);
	return TRUE;
}

int AONTRS_CHRYPTER(BYTE *cipertext,//����
							BYTE *context,//ԭ��
							int strlen)
{
	BYTE *originalcipertext,*curcipertext;
	
	BYTE *hashvalue;
	BYTE *randnum;
	int resTF,hashlen,cpylen;

	hashlen=SHA256_DIGEST_LENGTH;
	cpylen=strlen-hashlen;

	originalcipertext=cipertext;//��ʼд
	randnum=cipertext+cpylen;//��������������

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
	//������һ�������
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
	//��������ֵȡhash
	
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
					int strlen)//����һ��share
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
int AONTRS_STORE(AONTSHAREGROUP *sharegroupptr)//���ݵ�ǰ���������ݴ���
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

	cpylen=strlen+SHA256_DIGEST_LENGTH;//����������һ�¿ռ䵥λ���ֽ�
	sharesize=cpylen/datanum;
	codesize=sharesize*codenum;//���㵱ǰ�ı���鳤��

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
	for(i=0;i<totnum;i++)//ʹ��ԭ��������
	{
		//�ֵ��ڴ�ռ�����֮ǰ�Ѿ�����һ��������ֻҪ
		curshareptr->content=curmemptr;
		curshareptr->sizenum=sharesize;
		curshareptr->storepath=curaddressptr->storepath;
		curmemptr=curmemptr+sharesize;
		curaddressptr++;
		curshareptr++;
	}
	sharegroupptr->sharegroupptr=shareptr;
	sharegroupptr->groupsize=totnum;

	resTF=AONTRS_CHRYPTER(cpytext,content,cpylen);//����
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