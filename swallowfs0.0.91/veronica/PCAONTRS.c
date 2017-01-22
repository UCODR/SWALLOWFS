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

int PCAONTRS_HASHKEY(BYTE *key,//输出hash结果
							BYTE *context,//原文
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

int PCAONTRS_CHRYPTER(AONTSHAREGROUP *sharegroupptr,//密文组填写前datanum个
							BYTE *context,//原文
							CODEPARA *codeptr,
							int strlen)
{
	AONTSHARE *shareptr,*curshareptr;//需要边算边写

	BYTE *curcontentptr,*curcipertext;//用于计算
	BYTE *crypptr,*curcrypptr;//用于计算全文

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

	randnum=talloc(BYTE,hashlen);//给个空间好算随机值
	if(randnum==NULL)
	{
		show_error("PAONTRS","PAONTRS_CHRYPTER","No memory");
		return FALSE;
	}

	cpylen=strlen-hashlen;//计算一下密文的长度
	//生成hash秘钥
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
	//开始进行计算
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
		curcrypptr=curcrypptr+sharesize;//计算指针
		curcontentptr=curcontentptr+sharesize;
		curshareptr++;
	}
	
	//最后处理最后一个share
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
	//计算全文hash值
	mcpy(curcrypptr,curcipertext,BYTE,lastlen);
	//所有的编码数据计算完毕开始计算校验
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
	curcipertext=curcipertext+lastlen;//移动到最后的区域
	mcpy(curcipertext,randnum,BYTE,hashlen);
	//最后把数据统统释放掉
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
//和AONT_RS大同小异
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

	cpylen=strlen+SHA256_DIGEST_LENGTH;//我们来计算一下空间单位是字节
	sharesize=cpylen/datanum;
	codesize=sharesize*codenum;//计算当前的编码块长度

	//信号需要同步因此需要信号量
	//resTF=sem_init(&PAONT_sem,0,totnum-1);//主要
	resTF=sem_init(&PAONT_empty,0,0);
	if(resTF==PFALSE)//如果失败返回
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