#include "RAID5.h"
//需要将数据进行校验计算
int RAID5_do_parity(CHUNKBLOCKGROUP *chunkblockgroupptr,CHUNK *parity)
{
	int i,resTF,chunkblockgroupsize;
	//int chunksize;
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *chunkptr;
	int chunksize;

	BYTE *chunkcontent;
	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunkblockgroupsize=chunkblockgroupptr->groupsize;

	chunkptr=chunkblockptr->chunkptr;
	//chunksize=chunkptr->sizenum;//获取当前数据
	/*resTF=profile_chunk_data_isfree(chunkptr);
	if(resTF==TRUE)
	{
		//是不是空
		resTF=profile_chunk_data_haswrited(chunkptr);
		if(resTF==TRUE)
		{
			resTF=FILELAYER_CHUNK_READER_DATA(chunkptr);
			if(resTF==FALSE)
			{
				show_error("RAID5","do_parity","chunk data can't read");
				return FALSE;
			}
		}
		else
		{
			chunksize=chunkptr->sizenum;
			chunkcontent=talloc(BYTE,chunksize);
			if(chunkcontent==NULL)
			{
				show_error("RAID5","do_parity","No memory");
				return FALSE;
			}
			bzero(chunkcontent,BYTE,chunksize);
			chunkptr->chunkcontent=chunkcontent;
		}
	}*/
	resTF=profile_chunk_data_read(chunkptr);
	if(resTF==FALSE)
	{
		show_error("RAID5","do_parity","chunk data can't map");
		return FALSE;
	}
	resTF=matrix_CHUNK_copy_data(parity,chunkptr);
	if(resTF==FALSE)
	{
		show_error("RAID5","do_parity","data can't copy");
		return FALSE;
	}

	curchunkblockptr=chunkblockptr+1;
	for(i=0;i<(chunkblockgroupsize-1);i++)
	{
		chunkptr=curchunkblockptr->chunkptr;
		resTF=profile_chunk_data_read(chunkptr);
		if(resTF==FALSE)
		{
			show_error("RAID5","do_parity","chunk data can't map");
			return FALSE;
		}
		resTF=matrix_CHUNK_add_data(parity,chunkptr);
		if(resTF==FALSE)
		{
			show_error("RAID5","do_parity","data can't xor");
			return FALSE;
		}
		curchunkblockptr++;
	}
	return TRUE;
}
//处理一个strip中的编码
int RAID5_calculate_parity_strip(STRIP *stripptr)
{
	CHUNKBLOCKGROUP *chunkblockgroupptr;
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr,*parityptr;

	int i,chunkgroupsize,resTF;

	chunkgroupptr=stripptr->chunklist;

	chunkgroupsize=chunkgroupptr->groupsize;
	chunkptr=chunkgroupptr->ckgroup;

	curchunkptr=chunkptr;

	//开始进行空间分配
	chunkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(chunkblockgroupptr==NULL)
	{
		show_error("RAID5","calculate_parity_strip","No memory");
		return FALSE;
	}

	chunkblockptr=talloc(CHUNKBLOCK,chunkgroupsize-1);
	if(chunkblockptr==NULL)
	{
		show_error("RAID5","calculate_parity_strip","No memory");
		return FALSE;
	}
	chunkblockgroupptr->chunkblockptr=chunkblockptr;
	chunkblockgroupptr->groupsize=chunkgroupsize-1;

	//虽然可以使用matrix但是需要，需要重新编写
	curchunkblockptr=chunkblockptr;
	for(i=0;i<chunkgroupsize;i++)
	{
		//将数据进行异或即可
		if(curchunkptr->isparity==TRUE)
		{
			parityptr=curchunkptr;
		}
		else
		{
			curchunkblockptr->chunkptr=curchunkptr;
			curchunkblockptr->chunkid=curchunkptr->ChunkID;
			curchunkblockptr++;
		}
		curchunkptr++;
	}
	//计算校验块
	resTF=RAID5_do_parity(chunkblockgroupptr,parityptr);
	if(resTF==FALSE)
	{
		show_error("RAID5","calculate_parity_strip","parityvhunk can't created");
		return FALSE;
	}
	//清理现场
	free(chunkblockgroupptr);
	free(chunkblockptr);
	return TRUE;
}
//RAID5计算校验
int RAID5_calculate_parity(STRIPBLOCKGROUP *stripblockgroupptr)
{
	STRIP *stripptr;
	STRIPBLOCK	*stripblockptr,*curstripblockptr;
	
	int i,stripgroupsize,resTF;

	stripblockptr=stripblockgroupptr->stripblockptr;
	stripgroupsize=stripblockgroupptr->groupsize;

	curstripblockptr=stripblockptr;
	for(i=0;i<stripgroupsize;i++)
	{
		//将数据进行分离
		stripptr=curstripblockptr->stripptr;
		resTF=RAID5_calculate_parity_strip(stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID5","calculate_parity","the strip can't calculate parity");
			return FALSE;
		}
		curstripblockptr++;
	}
	return TRUE;
}

//处理一个条带中的chunkblock
int RAID5_decoder_parity_strip(STRIP *stripptr,ERRORPATTERN *errormatrix)
{
	int i,j,resTF,isfirst;
	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr,*tarchunkptr;
	int chunknum,chunksize;

	BYTE *contentptr;
	BITMATRIX *bitmatrixptr;
	UINT32 *erarray;
	int disknum,errordisknum;

	errordisknum=errormatrix->errordisknum;
	if(errordisknum>1)
	{
		show_error("RAID5","decoder_parity_strip","RAID5 error disk number is bigger than 1");
		return FALSE;
	}
	bitmatrixptr=errormatrix->bitmatrix;
	erarray=bitmatrixptr->matrix;
	disknum=bitmatrixptr->xm;

	isfirst=TRUE;

	chunkgroupptr=stripptr->chunklist;

	chunkptr=chunkgroupptr->ckgroup;
	chunknum=chunkgroupptr->groupsize;

	chunksize=chunkptr->sizenum;

	/*contentptr=talloc(BYTE,chunksize);
	if(contentptr==NULL)
	{
		show_error("RAID5","decoder_parity_strip","No memory");
		return FALSE;
	}*/

	curchunkptr=chunkptr;
	for(i=0;i<chunknum;i++)
	{
		if(erarray[i]==TRUE)//找到需要chunk数据
		{
			tarchunkptr=curchunkptr;//空间copy时会检查
			//tarchunkptr->chunkcontent=contentptr;
			for(j=0;j<chunknum;j++)
			{
				curchunkptr=chunkptr;
				if(erarray[j]==FALSE)//找到需要chunk数据
				{
					if(isfirst==TRUE)
					{
						resTF=matrix_CHUNK_copy_data(chunkptr,curchunkptr);
						if(resTF==FALSE)
						{
							show_error("RAID5","decoder_parity_strip","data can't copy");
							return FALSE;
						}
						isfirst=FALSE;
					}
					else
					{
						resTF=matrix_CHUNK_add_data(chunkptr,curchunkptr);
						if(resTF==FALSE)
						{
							show_error("RAID5","decoder_parity_strip","data can't add");
							return FALSE;
						}
					}
				}
			}
			return TRUE;
		}
		curchunkptr++;
	}
	return TRUE;
}
//计算stripblockgroup中的strip的源码块
int RAID5_decoder_pairty(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr)
{
	int i,resTF;
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	STRIPGROUP *stripgroupptr;
	STRIP *stripptr,*curstripptr;
	int stripnum;

	if(stripblockgroupptr==NULL)
	{
		stripgroupptr=regionptr->striplist;

		stripptr=stripgroupptr->stripgroup;
		stripnum=stripgroupptr->groupsize;

		curstripptr=stripptr;
		for(i=0;i<stripnum;i++)
		{
			resTF=RAID5_decoder_parity_strip(curstripptr,errormatrix);
			if(resTF==FALSE)
			{
				show_error("RAID5","decoder_parity","the strip can't calculate data");
				return FALSE;
			}
			curstripptr++;
		}
	}
	else
	{
		stripblockptr=stripblockgroupptr->stripblockptr;
		stripnum=stripblockgroupptr->groupsize;

		curstripblockptr=stripblockptr;
		for(i=0;i<stripnum;i++)
		{
			stripptr=curstripblockptr->stripptr;
			resTF=RAID5_decoder_parity_strip(stripptr,errormatrix);
			if(resTF==FALSE)
			{
				show_error("RAID5","decoder_parity","the strip can't calculate data");
				return FALSE;
			}
			curstripblockptr++;
		}
	}
	return TRUE;
}

//计算解码的源码块
int RAID5_decoder_parity_degrade_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix)
{
	BYTE *contentptr;

	BITMATRIX *bitmatrixptr;
	UINT32 *erarry;
	int disknum,errordisknum;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *curchunkptr;

	STRIP *stripptr;
	int i,resTF,chunknum,chunksize,isfirst;

	errordisknum=errormatrix->errordisknum;
	if(errordisknum>1)
	{
		show_error("RAID5","decoder_parity_degrade_chunk","error disk number is bigger than 1");
		return FALSE;
	}
	bitmatrixptr=errormatrix->bitmatrix;

	erarry=bitmatrixptr->matrix;
	disknum=bitmatrixptr->xm;

	contentptr=chunkptr->chunkcontent;
	chunksize=chunkptr->sizenum;

	if(contentptr==NULL)//
	{
		contentptr=talloc(BYTE,chunksize);
		if(contentptr==NULL)
		{
			show_error("RAID5","decoder_parity_degrade_chunk","No memory");
			return FALSE;
		}
		stripptr=chunkptr->stripptr;
		chunkgroupptr=stripptr->chunklist;

		curchunkptr=chunkgroupptr->ckgroup;
		chunknum=chunkgroupptr->groupsize;

		isfirst=TRUE;
		for(i=0;i<chunknum;i++)
		{
			if(erarry[i]==FALSE)//当前数据
			{
				if(isfirst==TRUE)
				{
					//第一步拷贝
					resTF=matrix_CHUNK_copy_data(chunkptr,curchunkptr);
					if(resTF==FALSE)
					{
						show_error("RAID5","decoder_parity_degrade_chunk","data can't copy");
						return FALSE;
					}
					isfirst=FALSE;
				}
				else
				{
					resTF=matrix_CHUNK_add_data(chunkptr,curchunkptr);
					if(resTF==FALSE)
					{
						show_error("RAID5","decoder_parity_degrade_chunk","data can't add");
						return FALSE;
					}
				}
			}
		}
	}
	return TRUE;
}
//计算块组的数据
int RAID5_decoder_parity_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix)
{
	int i,resTF;
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *chunkptr;
	int chunknum;

	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunknum=chunkblockgroupptr->groupsize;

	curchunkblockptr=chunkblockptr;
	for(i=0;i<chunknum;i++)
	{
		chunkptr=curchunkblockptr->chunkptr;
		resTF=RAID5_decoder_parity_degrade_chunk(chunkptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("RAID5","decoder_parity","chunk data can't decode");
			return FALSE;
		}
		curchunkblockptr++;
	}
	return TRUE;
}
//degrade需要的map的数据
int RAID5_degrade_map_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix)
{
	//看看这个
	int i,errordisknum,resTF;

	BITMATRIX *bitmatrixptr;
	UINT32 *errarray;
	int disknum;

	int dindex;//测试第几个设备上对比
	CHUNKPATH *chunkpathptr;
	BYTE *contentptr;
	
	STRIP *stripptr;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *curchunkptr;
	int chunknum;

	errordisknum=errormatrix->errorchunknum;
	if(errordisknum>1)
	{
		show_error("RAID5","degrade_map_chunk","error disk number bigger than 1");
		return FALSE;
	}
	bitmatrixptr=errormatrix->bitmatrix;

	errarray=bitmatrixptr->matrix;
	disknum=bitmatrixptr->xm;

	chunkpathptr=chunkptr->chkpath;
	//计算当前数据的位置
	dindex=profile_chkpath_to_stripsect_stripnum(chunkpathptr);
	
	if(errarray[dindex]==TRUE)
	{
		stripptr=chunkptr->stripptr;
		chunkgroupptr=stripptr->chunklist;

		chunkptr=chunkgroupptr->ckgroup;
		chunknum=chunkgroupptr->groupsize;

		curchunkptr=chunkptr;
		//RAID5将没有从硬盘中读出的其他数据读出
		for(i=0;i<chunknum;i++)
		{
			if(errarray[i]==FALSE)//当前数据没有坏
			{
				contentptr=curchunkptr->chunkcontent;
				if(contentptr==NULL)
				{
					resTF=FILELAYER_CHUNK_READER_DATA(chunkptr);
					if(resTF==FALSE)
					{
						show_error("RAID5","degrade_map_chunk","chunk data can't read");
						return FALSE;
					}
				}
			}
			curchunkptr++;
		}
	}
	else
	{
		//RAID5将数据调入内存
		contentptr=chunkptr->chunkcontent;
		if(contentptr==NULL)
		{
			resTF=FILELAYER_CHUNK_READER_DATA(chunkptr);
			if(resTF==FALSE)
			{
				show_error("RAID5","degrade_map_chunk","chunk data can't read");
				return FALSE;
			}
		}
	}

	return TRUE;
}
int RAID5_degrade_map_chunkblock(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix)
{
	int i,resTF,chunknum;
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *chunkptr;

	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunknum=chunkblockgroupptr->groupsize;

	curchunkblockptr=chunkblockptr;
	for(i=0;i<chunknum;i++)
	{
		chunkptr=curchunkblockptr->chunkptr;
		resTF=RAID5_degrade_map_chunk(chunkptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("RAID5","degrade_map_chunkblock","chunk data can't map");
			return FALSE;
		}
		curchunkblockptr++;
	}
	return TRUE;
}
//recover需要的map数据
int RAID5_recover_map_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,REGION *regionptr)
{
	//需要数据
	int i,resTF;
	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;
	int chunknum;

	BITMATRIX *bitmatrixptr;
	UINT32 *erarray;
	int disknum;
	int errordisknum;


	errordisknum=errormatrix->errordisknum;
	if(errordisknum>1)
	{
		show_error("RAID5","degrade_map_chunk","error disk number bigger than 1");
		return FALSE;
	}
	bitmatrixptr=errormatrix->bitmatrix;
	erarray=bitmatrixptr->matrix;
	disknum=bitmatrixptr->xm;

	chunkgroupptr=stripptr->chunklist;

	chunkptr=chunkgroupptr->ckgroup;
	chunknum=chunkgroupptr->groupsize;

	curchunkptr=chunkptr;
	for(i=0;i<chunknum;i++)
	{
		if(erarray[i]==FALSE)//将数据进行读取
		{
			resTF=FILELAYER_CHUNK_READER_DATA(curchunkptr);
			if(resTF==FALSE)
			{
				show_error("RAID5","recover_map_strip","chunk data can't read");
				return FALSE;
			}
		}
		curchunkptr++;
	}
	return TRUE;
}
int RAID5_recover_map_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr)
{
	int i,resTF,stripnum;
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	STRIPGROUP *stripgroupptr;
	STRIP *stripptr,*curstripptr;
	
	if(stripblockgroupptr==NULL)
	{
		stripgroupptr=regionptr->striplist;

		stripptr=stripgroupptr->stripgroup;
		stripnum=stripgroupptr->groupsize;

		curstripptr=stripptr;
		for(i=0;i<stripnum;i++)
		{
			resTF=RAID5_recover_map_strip(curstripptr,errormatrix,regionptr);
			if(resTF==FALSE)
			{
				show_error("RAID5","recover_map_strip","chunk data can't map");
				return FALSE;
			}
			curstripptr++;
		}
	}
	else
	{

		stripblockptr=stripblockgroupptr->stripblockptr;
		stripnum=stripblockgroupptr->groupsize;

		curstripblockptr=stripblockptr;
		for(i=0;i<stripnum;i++)
		{
			stripptr=curstripblockptr->stripptr;
			resTF=RAID5_recover_map_strip(stripptr,errormatrix,regionptr);
			if(resTF==FALSE)
			{
				show_error("RAID5","recover_map_strip","chunk data can't map");
				return FALSE;
			}
			curstripblockptr++;
		}
	}
	return TRUE;
}
//方案1是重新算法
int RAID5_updateI_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNK *parityptr,CHUNKBLOCKGROUP *chunkblockgroupptr)
{
	int i,resTF;
	int isfirst;
	int chunkindex;
	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	CHUNK *souchunkptr;
	int chunkpositionnum;

	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *curchunkptr;
	int chunknum;

	CHUNKBLOCKGROUP *tempchunkblockgroupptr;
	CHUNKBLOCK *tempchunkblockptr;

	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	chunkpositionnum=chunkpositionblockgroupptr->groupsize;

	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunknum=chunkblockgroupptr->groupsize;

	tempchunkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(tempchunkblockgroupptr==NULL)
	{
		show_error("RAID5","updateI_chunk","No memory");
		return FALSE;
	}
	tempchunkblockptr=talloc(CHUNKBLOCK,chunknum);
	if(tempchunkblockptr==NULL)
	{
		show_error("RAID5","updateI_chunk","No memory");
		return FALSE;
	}
	tempchunkblockgroupptr->chunkblockptr=tempchunkblockptr;
	tempchunkblockgroupptr->groupsize=0;

	curchunkblockptr=chunkblockptr;
	isfirst=TRUE;
	for(i=0;i<chunknum;i++)
	{
		curchunkptr=curchunkblockptr->chunkptr;
		//找到当前的块
		souchunkptr=profile_get_chunkposition_ptr(i,0,chunkpositionblockgroupptr);
		if(souchunkptr==NULL)//如果没有找到
		{
			souchunkptr=curchunkptr;
			resTF=profile_chunk_data_isfree(curchunkptr);
			if(resTF==TRUE)
			{
				resTF=profile_chunk_data_haswrited(curchunkptr);
				if(resTF==TRUE)
				{
					resTF=FILELAYER_CHUNK_READER_DATA(curchunkptr);
					if(resTF==FALSE)
					{
						show_error("RAID5","updateI_chunk","chunk data can't read");
						return FALSE;
					}
				}
				else
				{
					resTF=profile_chunk_create_empty_data(curchunkptr);
					if(resTF==FALSE)
					{
						show_error("RAID5","updateII_chunk","empty chunk data can't create");
						return FALSE;
					}
				}
				resTF=profile_chunkblockgroup_chunk_add(tempchunkblockgroupptr,curchunkptr);
				if(resTF==FALSE)
				{
					show_error("RAID5","updateI_chunk","chunk data can't add");
					return FALSE;
				}
			}
		}


		if(isfirst==TRUE)
		{
			resTF=matrix_CHUNK_copy_data(parityptr,souchunkptr);
			if(resTF==FALSE)
			{
				show_error("RAID5","updateI_chunk","chunk data can't copy");
				return FALSE;
			}
			isfirst=FALSE;
		}
		else
		{
			resTF=matrix_CHUNK_add_data(parityptr,souchunkptr);
			if(resTF==FALSE)
			{
				show_error("RAID5","updateI_chunk","chunk data can't copy");
				return FALSE;
			}
		}
	}
	resTF=profile_free_chunkblockgroup_data(tempchunkblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("RAID5","updateII_chunk","chunk data can't free");
		return FALSE;
	}
	free(tempchunkblockgroupptr);
	free(tempchunkblockptr);
	return TRUE;
}
//方案2是使用当前的校验块来算
int RAID5_updateII_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNK *parityptr,CHUNKBLOCKGROUP *chunkblockgroupptr)
{

	//第一步我们
	int i,resTF;
	int chunkindex;
	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	CHUNK *souchunkptr;
	int chunkpositionnum;

	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *chunkptr;
	int chunknum;

	CHUNKBLOCKGROUP *tempchunkblockgroupptr;
	CHUNKBLOCK *tempchunkblockptr;

	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	chunkpositionnum=chunkpositionblockgroupptr->groupsize;

	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunknum=chunkblockgroupptr->groupsize;

	tempchunkblockptr=talloc(CHUNKBLOCK,chunknum);
	if(tempchunkblockptr==NULL)
	{
		show_error("RAID5","updateII_chunk","No memory");
		return FALSE;
	}

	tempchunkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(tempchunkblockgroupptr==NULL)
	{
		show_error("RAID5","updateII_chunk","No memory");
		return FALSE;
	}
	tempchunkblockgroupptr->chunkblockptr=tempchunkblockptr;
	tempchunkblockgroupptr->groupsize=0;


	curchunkpositionblockptr=chunkpositionblockptr;

	for(i=0;i<chunkpositionnum;i++)
	{
		chunkindex=curchunkpositionblockptr->stripsectindex;//因为
		souchunkptr=curchunkpositionblockptr->chunkptr;

		curchunkblockptr=chunkblockptr+chunkindex;
		chunkptr=curchunkblockptr->chunkptr;

		resTF=profile_chunk_data_isfree(chunkptr);
		if(resTF==TRUE)//如果当前的chunk中没有数据
		{
			//在看看有没有被写过
			resTF=profile_chunk_data_haswrited(chunkptr);
			if(resTF==TRUE)
			{
				resTF=FILELAYER_CHUNK_READER_DATA(chunkptr);
				if(resTF==FALSE)
				{
					show_error("RAID5","updateII_chunk","chunk data can't read");
					return FALSE;
				}
			}
			else
			{
				resTF=profile_chunk_create_empty_data(chunkptr);
				if(resTF==FALSE)
				{
					show_error("RAID5","updateII_chunk","empty chunk data can't create");
					return FALSE;
				}
			}
			resTF=profile_chunkblockgroup_chunk_add(tempchunkblockgroupptr,chunkptr);
			if(resTF==FALSE)
			{
				show_error("RAID5","updateII_chunk","chunk data can't add");
				return FALSE;
			}
		}

		resTF=matrix_CHUNK_add_data(parityptr,chunkptr);
		if(resTF==FALSE)
		{
			show_error("RAID5","updateII_chunk","chunk data can't add");
			return FALSE;
		}

		resTF=matrix_CHUNK_add_data(parityptr,souchunkptr);
		if(resTF==FALSE)
		{
			show_error("RAID5","updateII_chunk","chunk data can't add");
			return FALSE;
		}

		curchunkpositionblockptr++;
	}
	resTF=profile_free_chunkblockgroup_data(tempchunkblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("RAID5","updateII_chunk","chunk data can't free");
		return FALSE;
	}
	free(tempchunkblockgroupptr);
	free(tempchunkblockptr);
	return TRUE;
}

int RAID5_update_select(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNK *parityptr,CHUNKBLOCKGROUP *chunkblockgroupptr)
{
	//需要计算当前两种方案需要读取的chunk数量
	int i,isparity,resTF;
	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	int positionchunknum;

	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *chunkptr;
	int chunknum;

	int update1chunknum,update2chunknum;

	BYTE *contentptr;

	update1chunknum=0l;
	update2chunknum=0;

	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	positionchunknum=chunkpositionblockgroupptr->groupsize;

	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunknum=chunkblockgroupptr->groupsize;
	
	curchunkblockptr=chunkblockptr;
	for(i=0;i<chunknum;i++)
	{
		chunkptr=curchunkblockptr->chunkptr;

		contentptr=chunkptr->chunkcontent;
		resTF=profile_search_chunkposition_id(i,0,chunkpositionblockgroupptr);//计算当前的位置是不是在chunkposition内
		if(resTF==PFALSE)//不在需要更新的列表中
		{
			resTF=profile_chunk_data_haswrited(chunkptr);
			if(resTF==TRUE)//确实要从内存读数据
			{
				if(contentptr==NULL)//当前为空
				{
					update1chunknum=update1chunknum+1;
				}
			}
		}
		else
		{
			resTF=profile_chunk_data_haswrited(chunkptr);
			if(resTF==TRUE)//确实要从内存读数据
			{
				if(contentptr==NULL)
				{
					update2chunknum=update2chunknum+1;
				}
			}
		}
		curchunkblockptr++;
	}

	resTF=profile_chunk_data_isfree(parityptr);
	if(resTF==TRUE)//当前的校验块是否存在
	{
		if(update1chunknum<(update2chunknum+1))
		{
			resTF=RAID5_updateI_chunk(chunkpositionblockgroupptr,parityptr,chunkblockgroupptr);
			if(resTF==FALSE)
			{
				show_error("RAID5","update_select","RAID5 chunk data can't update");
				return FALSE;
			}
		}
		else
		{
			resTF=RAID5_updateII_chunk(chunkpositionblockgroupptr,parityptr,chunkblockgroupptr);
			if(resTF==FALSE)
			{
				show_error("RAID5","update_select","RAID5 chunk data can't update");
				return FALSE;
			}
		}
	}
	else
	{
		if(update1chunknum<update2chunknum)
		{
			resTF=RAID5_updateI_chunk(chunkpositionblockgroupptr,parityptr,chunkblockgroupptr);
			if(resTF==FALSE)
			{
				show_error("RAID5","update_select","RAID5 chunk data can't update");
				return FALSE;
			}
		}
		else
		{
			resTF=RAID5_updateII_chunk(chunkpositionblockgroupptr,parityptr,chunkblockgroupptr);
			if(resTF==FALSE)
			{
				show_error("RAID5","update_select","RAID5 chunk data can't update");
				return FALSE;
			}
		}
	}
	return TRUE;
}
//计算一个条带中的
int RAID5_update_encode_chunkblock_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr)
{
	int i,resTF,isparity;
	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	int tarchunknum;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;
	int chunknum;

	CHUNKBLOCKGROUP *souchunkblockgroupptr;
	CHUNKBLOCK *souchunkblockptr;
	CHUNK *souchunkptr,*paritychunkptr;
	int souchunknum;
	
	chunkgroupptr=stripptr->chunklist;
	
	chunkptr=chunkgroupptr->ckgroup;
	chunknum=chunkgroupptr->groupsize;

	souchunkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(souchunkblockgroupptr==NULL)
	{
		show_error("RAID5","update_encode_chunkblock_strip","No memory");
		return FALSE;
	}
	souchunkblockptr=talloc(CHUNKBLOCK,chunknum);
	if(souchunkblockptr==NULL)
	{
		show_error("RAID5","update_encode_chunkblock_strip","No memory");
		return FALSE;
	}
	souchunknum=0;

	souchunkblockgroupptr->chunkblockptr=souchunkblockptr;
	souchunkblockgroupptr->groupsize=souchunknum;

	curchunkptr=chunkptr;
	for(i=0;i<chunknum;i++)
	{
		isparity=curchunkptr->isparity;
		//isparity=souchunkptr->isparity;
		if(isparity==FALSE)
		{
			souchunkptr=curchunkptr;
			resTF=profile_chunkblockgroup_chunk_add(souchunkblockgroupptr,souchunkptr);
			if(resTF==FALSE)
			{
				show_error("RAID5","update_encode_chunkblock_strip","chunk can't add to chunkblockgroup");
				return FALSE;
			}
		}
		else
		{
			paritychunkptr=curchunkptr;
			resTF=profile_chunkblockgroup_chunk_add(parityblockgroupptr,paritychunkptr);//将其校验块列表以备map
			if(resTF==FALSE)
			{
				show_error("RAID5","update_encode_chunkblock_strip","chunk can't add to chunkblockgroup");
				return FALSE;
			}
		}
		curchunkptr++;
	}
	RAID5_update_select(chunkpositionblockgroupptr,paritychunkptr,souchunkblockgroupptr);
	free(souchunkblockgroupptr);
	free(souchunkblockptr);
	return TRUE;
}
//计算所有的update数据
int RAID5_update_encode_chunkblock(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr)
{
	int i,resTF;
	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	CHUNK *chunkptr;
	//int chunknum;

	STRIPBLOCKGROUP *stripblockgroupptr;
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	STRIP *stripptr;
	STRIPDES *stripdesptr;
	int stripnum;

	//CHUNKBLOCKSTRIPGROUP *chunkblockstripgroupptr;
	//CHUNKBLOCKSTRIP *chunk;
	CHUNKPOSITIONBLOCKGROUP *souchunkpositionblockgroupptr;
	CHUNKPOSITIONBLOCK *souchunkpositionblockptr;
	int chunknum,disknum;

	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	chunknum=chunkpositionblockgroupptr->groupsize;

	stripblockptr=talloc(STRIPBLOCK,chunknum);
	if(stripblockptr==NULL)
	{
		show_error("RAID5","update_encode_chunkblock","No memory");
		return FALSE;
	}
	
	stripblockgroupptr=talloc(STRIPBLOCKGROUP,1);
	if(stripblockgroupptr==NULL)
	{
		show_error("RAID5","update_encode_chunkblock","No memory");
		return FALSE;
	}
	stripblockgroupptr->stripblockptr=stripblockptr;
	stripblockgroupptr->groupsize=0;

	curchunkpositionblockptr=chunkpositionblockptr;
	for(i=0;i<chunknum;i++)//计算更新需要涉及到的块
	{
		chunkptr=curchunkpositionblockptr->chunkptr;
		stripptr=chunkptr->stripptr;
		resTF=profile_stripblockgroup_strip_add(stripblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock","stripblock can't add");
			return FALSE;
		}
		curchunkpositionblockptr++;
	}
	stripdesptr=stripptr->strdes;
	chunknum=stripdesptr->chunknum;
	disknum=stripdesptr->disknum;

	//开chunk空间用于记下一个条带的信息
	souchunkpositionblockgroupptr=talloc(CHUNKPOSITIONBLOCKGROUP,1);
	if(souchunkpositionblockgroupptr==NULL)
	{
		show_error("RAID6","update_encode_chunkblock","No memory");
		return FALSE;
	}

	souchunkpositionblockptr=talloc(CHUNKPOSITIONBLOCK,chunknum*disknum);
	if(souchunkpositionblockptr==NULL)
	{
		show_error("RAID6","update_encode_chunkblock","No memory");
		return FALSE;
	}
	souchunkpositionblockgroupptr->chunkblockptr=souchunkpositionblockptr;
	souchunkpositionblockgroupptr->groupsize=0;

	stripblockptr=stripblockgroupptr->stripblockptr;
	stripnum=stripblockgroupptr->groupsize;

	curstripblockptr=stripblockptr;
	for(i=0;i<stripnum;i++)
	{
		stripptr=curstripblockptr->stripptr;
		resTF=profile_chunkblockpositiongroup_from_chunkblockpositiongroup_search_ptr(souchunkpositionblockgroupptr,chunkpositionblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock","chunkposition can't findt");
			return FALSE;
		}
		resTF=RAID5_update_encode_chunkblock_strip(souchunkpositionblockgroupptr,parityblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock","chunkblock can't calculate");
			return FALSE;
		}
		curstripblockptr++;
	}
	//释放内存以免内存泄露
	free(stripblockptr);
	free(stripblockgroupptr);
	free(souchunkpositionblockgroupptr);
	free(souchunkpositionblockptr);
	return TRUE;
}