#include "PAONTRS.h"
int PAONTRS_RANDKEY(BYTE *content,
							int strlen)
{
	int resTF;
	resTF=AONTRS_RANDKEY(content,strlen);
	if(resTF==FALSE)
	{
		show_error("PAONTRS","PAONTRS_RANDKEY","random ley cannot calculate");
		return FALSE;
	}
	return TRUE;
}
int PAONTRS_HASHKEY(BYTE *key,//���hash���
							BYTE *context,//ԭ��
							int strlen
							)
{
	int resTF;
	resTF=AONTRS_HASHKEY(key,context,strlen);
	if(resTF==FALSE)
	{
		show_error("PAONTRS","PAONTRS_HASHKEY","hashkey cannot calculate");
		return FALSE;
	}
	return TRUE;
}
int PAONTRS_CHRYPTEXT(BYTE *out,
							BYTE *in,
							int startindex,
							int strlen,
							BYTE *key,
							int keylen)
{
	//����share��
	/*int resTF;
	resTF=AONTRS_CHRYPTEXT(out,in,strlen,key,keylen);
	if(resTF==FALSE)
	{
		show_error("PAONTRS","PAONTRS_CHRYPTEXT","chrypt text cannot calculate");
		return FALSE;
	}*/
	int i,j,index;
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
	index=startindex;//������Ҫ�Ľ�
	for(i=0;i<en_len;i++)
	{
		mcpy(invalue,&index,BYTE,4);
		AES_encrypt(invalue,envalue,keyvalue);
		//��Ҫ��������8λ
		for(j=0;j<AES_BLOCK_SIZE;j++)
		{
			(*curout)=(*curin)^(*envalue);//����
			curout++;curin++;
		}
		index++;
		//(*out)=(*in)^(*envalue);//����
		//out++;in++;
	}
	free(invalue);
	free(envalue);
	free(keyvalue);
	return TRUE;
}

int PAONTRS_XORKEY(BYTE *out,
						BYTE *in,
						int strlen)
{
	int resTF;
	resTF=AONTRS_XORKEY(out,in,strlen);
	if(resTF==FALSE)
	{
		show_error("PAONTRS","PAONTRS_XORKEY","XOR cannot calculate");
		return FALSE;
	}
	return TRUE;
}
int PAONTRS_CHRYPTER(AONTSHAREGROUP *sharegroupptr,//����
							BYTE *context,//ԭ��
							CODEPARA *codeptr,
							int strlen)
{
	//��������
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

	resTF=PAONTRS_RANDKEY(randnum,hashlen);
	if(resTF==FALSE)
	{
		show_error("PAONTRS","PAONTRS_CHRYPTER","random key cannot calculate");
		return FALSE;
	}

	hashlen=SHA256_DIGEST_LENGTH;
	hashvalue=talloc(BYTE,hashlen);
	if(hashvalue==NULL)
	{
		show_error("PAONTRS","PAONTRS_CHRYPTER","No memory");
		return FALSE;
	}
	cpylen=strlen-hashlen;//����һ�����ĳ���
	datanum=codeptr->datanum;
	codenum=codeptr->codenum;
	totnum=codeptr->totnum;

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
		show_error("PAONTRS","PAONTRS_CHRYPTER","crypt text cannot calculate");
		return FALSE;
	}
	//����ȫ��hashֵ
	mcpy(curcrypptr,curcipertext,BYTE,lastlen);
	//���еı������ݼ�����Ͽ�ʼ����У��
	resTF=PAONTRS_HASHKEY(hashvalue,crypptr,cpylen);
	if(resTF==FALSE)
	{
		show_error("PAONTRS","PAONTRS_CHRYPTER","hash value cannot calculate");
		return FALSE;
	}
	resTF=PAONTRS_XORKEY(randnum,hashvalue,hashlen);
	if(resTF==FALSE)
	{
		show_error("PAONTRS","PAONTRS_CHRYPTER","XOR value cannot calculate");
		return FALSE;
	}

	curcipertext=curcipertext+lastlen;//�ƶ�����������
	mcpy(curcipertext,randnum,BYTE,hashlen);
	//��������ͳͳ�ͷŵ�
	resTF=PAONTRS_STORE(curshareptr);//������һ���鱣��һ��
	if(resTF==FALSE)
	{
		show_error("PAONTRS","PAONTRS_CHRYPTER","the share cannot store");
		return FALSE;
	}
	free(crypptr);
	free(randnum);
	free(hashvalue);
	return TRUE;
	//originalcipertext=cipertext;//��ʼд
	//randnum=cipertext+cpylen;//��������������

	/*if(originalcipertext==NULL)
	{
		show_error("PAONTRS","PAONTRS_CHRYPTER","No memory");
		return FALSE;
	}
	if(randnum==NULL)
	{
		show_error("PAONTRS","AONTRS_CHRYPTER","No memory");
		return FALSE;
	}*/
	

}
int PAONTRS_RS(AONTSHAREGROUP *sharegroupptr)
{
	//��Ҫ������Ʊ���ӿ�
	BITMATRIX *matrixptr;
	CODEPARA *codeptr;
	AONTSHARE *shareptr,*curshareptr;
	CHUNK *chunkptr,*curchunkptr,*tarchunkptr;
	BYTE *conptr,*curconptr,*tarconptr,*souptr;

	UINT32 *mat;

	int index;
	int datanum,codenum,totnum,w;
	int i,j,k,resTF,rows,cols,chunksize,sharesize;

	shareptr=sharegroupptr->sharegroupptr;

	codeptr=shareptr->codeptr;
	sharesize=shareptr->sizenum;

	w=codeptr->w;
	datanum=codeptr->datanum;
	codenum=codeptr->codenum;
	totnum=codeptr->totnum;

	rows=codenum*w;
	cols=datanum*w;
	mat=talloc(UINT32,rows*cols);
	if(mat==NULL)
	{
		show_error("PAONTRS","PAONTRS_RS","No memory");
		return FALSE;
	}

	matrixptr=talloc(BITMATRIX,1);
	if(matrixptr==NULL)
	{
		show_error("PAONTRS","PAONTRS_RS","No memory");
		return FALSE;
	}
	chunkptr=talloc(CHUNK,cols);
	if(chunkptr==NULL)
	{
		show_error("PAONTRS","PAONTRS_RS","No memory");
		return FALSE;
	}
	
	

	matrixptr->w=w;
	matrixptr->xm=rows;
	matrixptr->ym=cols;
	matrixptr->matrix=mat;
	resTF=cauchy_good_general_coding_bitmatrix(matrixptr);
	if(resTF==FALSE)
	{
		show_error("PAONTRS","PAONTRS_RS","matrix cannor generate");
		return FALSE;
	}

	//��ʼ����+�洢
	//step1:datanum��Ƭ
	chunksize=sharesize/w;//����һ��chunksize;
	curshareptr=shareptr;
	curchunkptr=chunkptr;

	for(i=0;i<datanum;i++)
	{
		conptr=curshareptr->content;
		curconptr=conptr;
		for(j=0;j<w;j++)
		{
			curchunkptr->chunkcontent=curconptr;
			curchunkptr->sizenum=chunksize;
			curconptr=curconptr+chunksize;
		}
		curshareptr++;
	}
	//���ǿ��Կ�ʼ�����
	tarchunkptr=talloc(CHUNK,1);
	if(tarchunkptr==NULL)
	{
		show_error("PAONTRS","PAONTRS_RS","No memory");
		return FALSE;
	}
	tarconptr=talloc(BYTE,chunksize);
	if(tarconptr==NULL)
	{
		show_error("PAONTRS","PAONTRS_RS","No memory");
		return FALSE;
	}
	tarchunkptr->chunkcontent=tarconptr;
	tarchunkptr->sizenum=chunksize;
	curshareptr=shareptr+datanum;
	
	curchunkptr=chunkptr;
	curshareptr=shareptr;
	//��ʼ����
	for(i=0;i<datanum;i++)
	{
		souptr=curshareptr->content;
		conptr=souptr;
		//��ʼ�������chunkgroup
		for(j=0;j<w;j++)
		{
			/*conptr=talloc(char,chunksize);//�ȸ���ռ�
			if(conptr==NULL)
			{
				show_error("matrix","matrix_calculate_share","No memory");
				return FALSE;
			}
			mcpy(conptr,souptr,char,chunksize);//��ʼ��������*/
			curchunkptr->chunkcontent=conptr;
			curchunkptr->sizenum=chunksize;
			curchunkptr++;//һ��chunk�������Ѿ�����������һ��
			conptr=conptr+chunksize;//�ƶ�һ��chunksize
		}
		
		curshareptr++;//�����Ȼ�ȡ��һ��share
	}

	index=0;//����ǰԪ��
	for(i=0;i<codenum;i++)
	{
		conptr=curshareptr->content;
		curconptr=conptr;
		for(j=0;j<w;j++)
		{
			bzero(tarconptr,BYTE,chunksize);//��0���ڼ���
			curchunkptr=chunkptr;
			for(k=0;k<cols;k++)
			{
				if(mat[index]==1)
				{
					resTF=matrix_CHUNK_add_data(tarchunkptr,curchunkptr);
					if(resTF==FALSE)
					{
						show_error("PAONTRS","PAONTRS_RS","XOR cannot calculate");
						return FALSE;
					}
				}
				curchunkptr++;
				index++;
			}
			mcpy(curconptr,tarconptr,BYTE,chunksize);
			curconptr=curconptr+chunksize;
		}
		resTF=PAONTRS_STORE(curshareptr);
		curshareptr=curshareptr+1;
	}
	free(mat);
	free(matrixptr);
	free(chunkptr);
	free(tarchunkptr);
	free(tarconptr);
	return TRUE;
}
void *PAONTRS_STORE_thread(void* arg)
{
	//��������
	int resTF;
	//int sem_value;
	//AONTSHARE *shareptr;
	//shareptr=(AONTSHARE *)arg;
	/*resTF=sem_getvalue(&PAONT_sem,&sem_value);
	if(resTF==PFALSE)
	{
		show_error("PAONTRS","STORE_thread","semaphore cannot get value");
		return FALSE;
	}
	printf("%d\n",sem_value);*/
	
	/*resTF=sem_wait(&PAONT_full);
	if(resTF==PFALSE)
	{
		show_error("PAONTRS","PAONTRS_STORE_thread","semophare cannot be wait");
		return FALSE;
	}*/
	while(1)
	{
		resTF=sem_wait(&PAONT_full);
		if(resTF==PFALSE)
		{
			show_error("PAONTRS","PAONTRS_STORE_thread","semophare cannot be wait");
			return FALSE;
		}
		//sem_wait(&PAONT_sem);
		resTF=file_FILELAYER_SHARE_WRITER(&memshareptr);
		if(resTF==FALSE)
		{
			show_error("PAONTRS","STORE_thread","share cannot store");
			return;
		}
		resTF=sem_post(&PAONT_empty);
		if(resTF==PFALSE)
		{
			show_error("PAONTRS","PAONTRS_STORE_thread","semophare cannot be post");
			return FALSE;
		}
	}
	
	/*if(sem_value<0)
	{
		resTF=sem_post(&PAONT_sem);//���һ���洢+1
		if(resTF==PFALSE)
		{
			show_error("PAONTRS","STORE_thread","semaphore cannot be post");
			return FALSE;
		}
	}*/
	pthread_exit(NULL);//�߳�����
	//return TRUE;
}
int PAONTRS_STORE(AONTSHARE *shareptr)
{
	//ʹ���첽���ʵ�ʴ洢
	int resTF;
	mcpy(&memshareptr,shareptr,BYTE,sizeof(shareptr));
	//�����Ȱ��ź���
	resTF=sem_post(&PAONT_full);//��һ�����н���ִ�������ûɶ��Դ�˵�һ������������
	if(resTF==PFALSE)
	{
		show_error("PAONTRS","PAONTRS_API","semophare cannot be post");
		return FALSE;
	}
	resTF=sem_wait(&PAONT_empty);//�ȴ�д��
	if(resTF==PFALSE)
	{
		show_error("PAONTRS","PAONTRS_API","semophare cannot be wait");
		return FALSE;
	}
	
	
	
	return TRUE;
}

int PAONTRS_API(BYTE *content,int strlen,ADDRESSLIST *addresslistptr)
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
		show_error("PAONTRS","PAONTRS_STORE","store cannot be create");
		return FALSE;
	}
	cpytext=talloc(BYTE,cpylen);
	if(cpytext==NULL)
	{
		show_error("PAONTRS","PAONTRS_API","No memory");
		return FALSE;
	}

	memspace=talloc(BYTE,cpylen+codesize);
	if(memspace==NULL)
	{
		show_error("PAONTRS","PAONTRS_API","No memory");
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

	resTF=PAONTRS_CHRYPTER(sharegroupptr,content,codeptr,cpylen);
	if(resTF==FALSE)
	{
		show_error("PAONTRS","PAONTRS_API","chryptext cannot calculate");
		return FALSE;
	}
	if(codenum>0)
	{
		resTF=PAONTRS_RS(sharegroupptr);
		if(resTF==FALSE)
		{
			show_error("PAONTRS","PAONTRS_API","rs cannot calculate");
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
		show_error("PAONTRS","PAONTRS_API","thread can be killed");
		return FALSE;
	}
	free(cpytext);
	free(memspace);
	free(sharegroupptr);
	free(shareptr);
	return TRUE;
}