#include "CAONTRS.h"

int CAONTRS_HASHKEY(BYTE *key,//���hash���
							BYTE *context,//ԭ��
							int strlen
							)//����ֵ
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
							int keylen)//���¶�����ܽӿ�
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
						int strlen)//��in���out�浽out
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
int CAONTRS_CHRYPTER(BYTE *cipertext,//����
							BYTE *context,//ԭ��
							int strlen)
{
	//�������Ҫ�Ľ�һ����Ҫ������
	BYTE *originalcipertext,*curcipertext;
	
	BYTE *hashvalue,*hashkey;
	BYTE *randnum;
	int resTF,hashlen,cpylen;

	hashlen=SHA256_DIGEST_LENGTH;
	cpylen=strlen-hashlen;//һ����Ҫ����ƫ����

	originalcipertext=cipertext;
	randnum=cipertext+cpylen;//����λ��

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
	//����һ�����ֵ������Ҫ���㱨�ĵ�hashֵ
	resTF=CAONTRS_HASHKEY(hashkey,context,cpylen);//����hash����
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
//����һ��share
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
int CAONTRS_STORE(AONTSHAREGROUP *sharegroupptr)//���ݵ�ǰ���������ݴ���
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
//����һ�����ݸ���һ����ַ���ϳ���
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

	cpylen=strlen+SHA256_DIGEST_LENGTH;//����������һ�¿ռ䵥λ���ֽ�
	sharesize=cpylen/datanum;
	codesize=sharesize*codenum;//���㵱ǰ�ı���鳤��

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

	resTF=CAONTRS_CHRYPTER(cpytext,content,cpylen);//����
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