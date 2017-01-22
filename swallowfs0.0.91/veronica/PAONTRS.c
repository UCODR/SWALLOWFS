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
int PAONTRS_HASHKEY(BYTE *key,//输出hash结果
							BYTE *context,//原文
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
	//计算share组
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
	index=startindex;//这里需要改进
	for(i=0;i<en_len;i++)
	{
		mcpy(invalue,&index,BYTE,4);
		AES_encrypt(invalue,envalue,keyvalue);
		//需要加密两个8位
		for(j=0;j<AES_BLOCK_SIZE;j++)
		{
			(*curout)=(*curin)^(*envalue);//加密
			curout++;curin++;
		}
		index++;
		//(*out)=(*in)^(*envalue);//加密
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
int PAONTRS_CHRYPTER(AONTSHAREGROUP *sharegroupptr,//密文
							BYTE *context,//原文
							CODEPARA *codeptr,
							int strlen)
{
	//计算数据
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
	cpylen=strlen-hashlen;//计算一下密文长度
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
		show_error("PAONTRS","PAONTRS_CHRYPTER","crypt text cannot calculate");
		return FALSE;
	}
	//计算全文hash值
	mcpy(curcrypptr,curcipertext,BYTE,lastlen);
	//所有的编码数据计算完毕开始计算校验
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

	curcipertext=curcipertext+lastlen;//移动到最后的区域
	mcpy(curcipertext,randnum,BYTE,hashlen);
	//最后把数据统统释放掉
	resTF=PAONTRS_STORE(curshareptr);//将最后的一个块保存一下
	if(resTF==FALSE)
	{
		show_error("PAONTRS","PAONTRS_CHRYPTER","the share cannot store");
		return FALSE;
	}
	free(crypptr);
	free(randnum);
	free(hashvalue);
	return TRUE;
	//originalcipertext=cipertext;//开始写
	//randnum=cipertext+cpylen;//调整到最后的区域

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
	//需要重新设计编码接口
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

	//开始计算+存储
	//step1:datanum切片
	chunksize=sharesize/w;//计算一个chunksize;
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
	//我们可以开始计算可
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
	//开始迭代
	for(i=0;i<datanum;i++)
	{
		souptr=curshareptr->content;
		conptr=souptr;
		//开始将其组成chunkgroup
		for(j=0;j<w;j++)
		{
			/*conptr=talloc(char,chunksize);//先给点空间
			if(conptr==NULL)
			{
				show_error("matrix","matrix_calculate_share","No memory");
				return FALSE;
			}
			mcpy(conptr,souptr,char,chunksize);//开始拷贝数据*/
			curchunkptr->chunkcontent=conptr;
			curchunkptr->sizenum=chunksize;
			curchunkptr++;//一个chunk的数据已经到手了再来一个
			conptr=conptr+chunksize;//移动一个chunksize
		}
		
		curshareptr++;//我们先获取下一个share
	}

	index=0;//矩阵当前元素
	for(i=0;i<codenum;i++)
	{
		conptr=curshareptr->content;
		curconptr=conptr;
		for(j=0;j<w;j++)
		{
			bzero(tarconptr,BYTE,chunksize);//制0用于计算
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
	//处理数据
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
		resTF=sem_post(&PAONT_sem);//完成一个存储+1
		if(resTF==PFALSE)
		{
			show_error("PAONTRS","STORE_thread","semaphore cannot be post");
			return FALSE;
		}
	}*/
	pthread_exit(NULL);//线程销毁
	//return TRUE;
}
int PAONTRS_STORE(AONTSHARE *shareptr)
{
	//使用异步完成实际存储
	int resTF;
	mcpy(&memshareptr,shareptr,BYTE,sizeof(shareptr));
	//我们先把信号量
	resTF=sem_post(&PAONT_full);//等一下所有进程执行完基本没啥资源了等一等其他的数据
	if(resTF==PFALSE)
	{
		show_error("PAONTRS","PAONTRS_API","semophare cannot be post");
		return FALSE;
	}
	resTF=sem_wait(&PAONT_empty);//等待写完
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