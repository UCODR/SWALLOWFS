#include "PCAONTRS.h"
int PCAONTRS_RANDKEY(BYTE *content,
							int strlen)
{
	int resTF;
	resTF=PAONTRS_RANDKEY(content,strlen);
	if(resTF==FALSE)
	{
		show_error("PCAONTRS","PCAONTRS_RANDKEY","random key cannot calculate");
		return FALSE;
	}
	return TRUE;
}

int PCAONTRS_HASHKEY(BYTE *key,//���hash���
							BYTE *context,//ԭ��
							int strlen
							)
{
	int resTF;
	resTF=PAONTRS_HASHKEY(key,context,strlen);
	if(resTF==FALSE)
	{
		show_error("PCAONTRS","PCAONTRS_HASHKEY","hash value cannot calculate");
		return FALSE;
	}
	return TRUE;
}

int PCAONTRS_CHRYPTEXT(BYTE *out,
							BYTE *in,
							int startindex,
							int strlen,
							BYTE *key,
							int keylen)
{
	int resTF;
	resTF=PAONTRS_CHRYPTEXT(out,in,startindex,strlen,key,keylen);
	if(resTF==FALSE)
	{
		show_error("PCAONTRS","PCAONTRS_CHRYPTEXT","crptytext cannot calculate");
		return FALSE;
	}
	return TRUE;
}

int PCAONTRS_XORKEY(BYTE *out,
						BYTE *in,
						int strlen)
{
	int resTF;
	resTF=PAONTRS_XORKEY(out,in,strlen);
	if(resTF==FALSE)
	{
		show_error("PCAONTRS","PCAONTRS_XORKEY","XOR value cannot calculate");
		return FALSE;
	}
	return TRUE;
}

int PCAONTRS_CHRYPTER(AONTSHAREGROUP *sharegroupptr,//��������дǰdatanum��
							BYTE *context,//ԭ��
							CODEPARA *codeptr,
							int strlen)
{
	AONTSHARE *shareptr,*curshareptr;//��Ҫ�����д

	BYTE *curcontentptr,*curcipertext;//���ڼ���
	BYTE *crypptr,*curcrypptr;//���ڼ���ȫ��

	BYTE *hashvalue;
	BYTE *randnum;
	int i,datanum,codenum,totnum;
	int resTF,hashlen,cpylen,sharesize,startindex,lastlen;
	hashlen=SHA256_DIGEST_LENGTH;
	cpylen=strlen-hashlen;
	crypptr=talloc(BYTE,cpylen);
	if(crypptr==NULL)
	{
		show_error("PAONTRS","PAONTRS_CHRYPTER","No memory");
		return FALSE;
	}

	randnum=talloc(BYTE,hashlen);//�����ռ�������ֵ
	if(randnum==NULL)
	{
		show_error("PAONTRS","PAONTRS_CHRYPTER","No memory");
		return FALSE;
	}

	cpylen=strlen-hashlen;//����һ�����ĵĳ���
	//����hash��Կ
	resTF=PCAONTRS_HASHKEY(randnum,context,cpylen);
	if(resTF==FALSE)
	{
		show_error("PAONTRS","PAONTRS_CHRYPTER","hash value");
		return FALSE;
	}

	hashlen=SHA256_DIGEST_LENGTH;
	hashvalue=talloc(BYTE,hashlen);
	if(hashvalue==NULL)
	{
		show_error("PAONTRS","PAONTRS_CHRYPTER","No memory");
		return FALSE;
	}
	totnum=codeptr->totnum;
	datanum=codeptr->datanum;
	codenum=codeptr->codenum;

	sharesize=strlen/datanum;

	shareptr=sharegroupptr->sharegroupptr;
	sharegroupptr->groupsize=totnum;

	curshareptr=shareptr;
	curcontentptr=context;
	curcrypptr=crypptr;
	startindex=0;
	//��ʼ���м���
	for(i=0;i<(datanum-1);i++)
	{
		curcipertext=curshareptr->content;
		startindex=i*sharesize;
		resTF=PAONTRS_CHRYPTEXT(curcipertext,curcontentptr,startindex,sharesize,randnum,hashlen);
		if(resTF==FALSE)
		{
			show_error("PAONTRS","PAONTRS_CHRYPTER","crypt text cannot calculate");
			return FALSE;
		}
		curshareptr->codeptr=codeptr;
		curshareptr->sizenum=sharesize;
		resTF=PAONTRS_STORE(curshareptr);
		if(resTF==FALSE)
		{
			show_error("PAONTRS","PAONTRS_CHRYPTER","the share cannot store");
			return FALSE;
		}
		mcpy(curcrypptr,curcipertext,BYTE,sharesize);
		startindex=startindex+sharesize;
		curcrypptr=curcrypptr+sharesize;//����ָ��
		curcontentptr=curcontentptr+sharesize;
		curshareptr++;
	}
	
	//��������һ��share
	lastlen=sharesize-hashlen;
	curcipertext=curshareptr->content;

	curshareptr->codeptr=codeptr;
	curshareptr->sizenum=sharesize;

	resTF=PAONTRS_CHRYPTEXT(curcipertext,curcontentptr,startindex,lastlen,randnum,hashlen);
	if(resTF==FALSE)
	{
		show_error("PCAONTRS","PCAONTRS_CHRYPTER","crypt text cannot calculate");
		return FALSE;
	}
	//����ȫ��hashֵ
	mcpy(curcrypptr,curcipertext,BYTE,lastlen);
	//���еı������ݼ�����Ͽ�ʼ����У��
	resTF=PAONTRS_HASHKEY(hashvalue,crypptr,cpylen);
	if(resTF==FALSE)
	{
		show_error("PCAONTRS","PCAONTRS_CHRYPTER","hash value cannot calculate");
		return FALSE;
	}
	resTF=PAONTRS_XORKEY(randnum,hashvalue,hashlen);
	if(resTF==FALSE)
	{
		show_error("PCAONTRS","PCAONTRS_CHRYPTER","XOR value cannot calculate");
		return FALSE;
	}
	curcipertext=curcipertext+lastlen;//�ƶ�����������
	mcpy(curcipertext,randnum,BYTE,hashlen);
	//��������ͳͳ�ͷŵ�
	free(crypptr);
	free(randnum);
	free(hashvalue);

	return TRUE;
}
int PCAONTRS_RS(AONTSHAREGROUP *sharegroupptr)
{
	int resTF;
	resTF=PAONTRS_RS(sharegroupptr);
	if(resTF==FALSE)
	{
		show_error("PCAONTRS","PCAONTRS_RS","");
		return FALSE;

	}
	return TRUE;
}
int PCAONTRS_STORE(AONTSHARE *shareptr)
{
	int resTF;
	resTF=PAONTRS_STORE(shareptr);
	if(resTF==FALSE)
	{
		show_error("PCAONTRS","PCAONTRS_STORE","share cannot store");
		return FALSE;
	}
	return TRUE;
}
//��AONT_RS��ͬС��
int PCAONTRS_API(BYTE *content,int strlen,ADDRESSLIST *addresslistptr)
{
	int i,resTF,cpylen,sharesize,codesize;
	BYTE *cpytext,*memspace,*curmemptr;
	AONTSHAREGROUP *sharegroupptr;
	AONTSHARE *shareptr,*curshareptr;
	CODEPARA *codeptr;
	SHAREADDRESS *addressptr,*curaddressptr;
	pthread_t threadhandle;

	int totnum,codenum,datanum;


	addressptr=addresslistptr->addressptr;
	curaddressptr=addressptr;

	codeptr=addresslistptr->codeptr;
	datanum=codeptr->datanum;
	codenum=codeptr->codenum;
	totnum=codeptr->totnum;

	cpylen=strlen+SHA256_DIGEST_LENGTH;//����������һ�¿ռ䵥λ���ֽ�
	sharesize=cpylen/datanum;
	codesize=sharesize*codenum;//���㵱ǰ�ı���鳤��

	//�ź���Ҫͬ�������Ҫ�ź���
	//resTF=sem_init(&PAONT_sem,0,totnum-1);//��Ҫ
	resTF=sem_init(&PAONT_empty,0,0);
	if(resTF==PFALSE)//���ʧ�ܷ���
	{
		show_error("PAONTRS","PAONTRS_API","semophare cannot initial");
		return FALSE;
	}
	resTF=sem_init(&PAONT_full,0,0);
	if(resTF==PFALSE)
	{
		show_error("PAONTRS","PAONTRS_API","semophare cannot initial");
		return FALSE;
	}

	resTF=pthread_create(&threadhandle, NULL,PAONTRS_STORE_thread,NULL);
	if(resTF==PFALSE)
	{
		show_error("CPAONTRS","PCAONTRS_STORE","store cannot be create");
		return FALSE;
	}
	cpytext=talloc(BYTE,cpylen);
	if(cpytext==NULL)
	{
		show_error("PCAONTRS","PCAONTRS_API","No memory");
		return FALSE;
	}

	memspace=talloc(BYTE,cpylen+codesize);
	if(memspace==NULL)
	{
		show_error("PCAONTRS","PCAONTRS_API","No memory");
		return FALSE;
	}
	curmemptr=memspace;

	sharegroupptr=talloc(AONTSHAREGROUP,1);
	if(sharegroupptr==NULL)
	{
		show_error("PAONTRS","PAONTRS_API","No memory");
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

	resTF=PCAONTRS_CHRYPTER(sharegroupptr,content,codeptr,cpylen);
	if(resTF==FALSE)
	{
		show_error("PCAONTRS","PCAONTRS_API","chryptext cannot calculate");
		return FALSE;
	}
	if(codenum>0)
	{
		resTF=PCAONTRS_RS(sharegroupptr);
		if(resTF==FALSE)
		{
			show_error("PCAONTRS","PCAONTRS_API","rs cannot calculate");
			return FALSE;
		}
	}
	/*resTF=sem_destroy(&PAONT_full);
	if(resTF==PFALSE)
	{
		show_error("PAONTRS","PAONTRS_API","semoshare can be destoryed");
		return FALSE;
	}
	resTF=sem_destroy(&PAONT_empty);
	if(resTF==PFALSE)
	{
		show_error("PAONTRS","PAONTRS_API","semoshare can be destoryed");
		return FALSE;
	}*/
	//resTF=pthread_kill(threadhandle,0);
	resTF=pthread_cancel(threadhandle);
	if(resTF==PFALSE)
	{
		show_error("PCAONTRS","PCAONTRS_API","thread can be killed");
		return FALSE;
	}
	free(cpytext);
	free(memspace);
	free(sharegroupptr);
	free(shareptr);
	return TRUE;
}