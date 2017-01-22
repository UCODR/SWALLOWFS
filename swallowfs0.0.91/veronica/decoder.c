#include "decoder.h"
//元数据层
//将数据存储到相应的文件指针中
int decoder_METALAYER_storage(char *filepath,BYTESTREAM *filecontent)
{
	//向文件内输入
	BYTE *BYTEcontentptr;
	int filesize,resTF;

	FILE *fp;

	BYTEcontentptr=filecontent->BYTEcontent;
	filesize=filecontent->bytessize;

	fp=fopen(filepath,"wb");
	if(fp==NULL)
	{
		show_error("decoder","METALAYER_storage","file handle can't open");
		return FALSE;
	}

	resTF=fwrite(BYTEcontentptr,filesize,1,fp);
	if(resTF==FALSE)
	{
		show_error("decoder","METALAYER_storage","the data can't write into file");
		return FALSE; 
	}
	fclose(fp);
	return TRUE;
}
int decoder_MATELAYER_free_space(CHUNKBLOCKGROUP *chunkblockgrouptr)
{
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *chunkptr;
	int i,chunknum;

	BYTE *chunkcontent;

	chunkblockptr=chunkblockgrouptr->chunkblockptr;
	chunknum=chunkblockgrouptr->groupsize;

	curchunkblockptr=chunkblockptr;
	for(i=0;i<chunknum;i++)
	{
		chunkptr=curchunkblockptr->chunkptr;
		chunkcontent=chunkptr->chunkcontent;
		free(chunkcontent);
		curchunkblockptr++;
	}
	return TRUE;
}
//将数据重新组织成为数据流
int decoder_METALAYER_merger(BYTESTREAM *filecontent,CHUNKBLOCKGROUP *chunkblockgroupptr)
{
	//将数据进行计算
	int i,chunksize,chunknum;
	int remainsize;

	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *chunkptr;
	BYTE *chunkcontent;

	BYTE *tarcontent,*curtarcontent;
	int filesize;	

	filesize=filecontent->bytessize;
	tarcontent=filecontent->BYTEcontent;

	if(tarcontent!=NULL)
	{
		free(tarcontent);
	}
	tarcontent=talloc(BYTE,filesize);
	if(tarcontent==NULL)
	{
		show_error("decoder","METALAYER_merger","No memory");
		return FALSE;
	}


	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunknum=chunkblockgroupptr->groupsize;

	chunkptr=chunkblockptr->chunkptr;
	chunksize=chunkptr->sizenum;

	curchunkblockptr=chunkblockptr;
	curtarcontent=tarcontent;
	for(i=0;i<chunknum;i++)
	{
		//获取chunk数据
		chunkptr=curchunkblockptr->chunkptr;
		chunkcontent=chunkptr->chunkcontent;
		if(i<(chunknum-1))//当前数据最后一个块要计算偏移量
		{
			mcpy(curtarcontent,chunkcontent,BYTE,chunksize);
		}
		else
		{
			remainsize=calremainsize(chunksize,chunknum,filesize);
			mcpy(curtarcontent,chunkcontent,BYTE,remainsize);

		}
		curchunkblockptr++;
		curtarcontent=curtarcontent+chunksize;
	}
	filecontent->BYTEcontent=tarcontent;
	return TRUE;
}

//encoderlayer，暂时没用，degrade计算有用
//将校验数据和数据生成失效数据块
int decoder_DECODERLAYER_decoder_data_ptr(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr)
{
	int resTF;
	int maintype,codetype,subtype;
	codetype=regionptr->codetype;
	maintype=maintype(codetype);
	subtype=subtype(codetype);
	//通过不同函数计算源码块
	switch(maintype)
	{
	case Hamming:
		resTF=HAMMING_decoder_parity(stripblockgroupptr,errormatrix,regionptr);
		if(resTF==FALSE)
		{
			show_error("decoder","DECODERLAYER_decoder_data_ptr","Hamming can't run");
			return FALSE;
		}
		break;
	case reed_sol:
		resTF=RSCODE_decoder_parity(stripblockgroupptr,errormatrix,regionptr,subtype);
		if(resTF==FALSE)
		{
			show_error("decoder","DECODERLAYER_decoder_data_ptr","RScode can't run");
		}
		break;
	case RAID5:
		resTF=RAID5_decoder_pairty(stripblockgroupptr,errormatrix,regionptr);
		if(resTF==FALSE)
		{
			show_error("decoder","DECODERLAYER_decoder_data_ptr","RAID5 can't run");
			return FALSE;
		}
		break;
	case RAID6:
		resTF=RAID6_decoder_parity(stripblockgroupptr,errormatrix,regionptr,subtype);
		if(resTF==FALSE)
		{
			show_error("decoder","DECODERLAYER_decoder_data_ptr","RAID6 can't run");
			return FALSE;
		}
		break;
	case MSR:
		resTF=MSR_decoder_parity(stripblockgroupptr,errormatrix,regionptr,subtype);
		if(resTF==FALSE)
		{
			show_error("decoder","DECODERLAYER_decoder_data_ptr","MSR can't run");
			return FALSE;
		}
		break;
	case MBR:
		resTF=MBR_decoder_parity(stripblockgroupptr,errormatrix,regionptr,subtype);
		if(resTF==FALSE)
		{
			show_error("decoder","DECODERLAYER_decoder_data_ptr","MBR can't run");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int decoder_DECODERLAYER_decoder_data_ptr_chunk(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr)
{
	//第一步先找到条带中的元数据块
	int i;
	//REGION *regionptr;
	STRIPDES *strdes;
	//CODEPARA *codeparamptr;

	int stripchunkmaxnum;
	int chunkmaxnum;//最多会有多少个chunk需要指向
	int disknum;
	int resTF;

	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	int chunknum,stripnum;

	resTF=decoder_DECODERLAYER_decoder_data_ptr(stripblockgroupptr,errormatrix,regionptr);
	if(resTF==FALSE)
	{
		show_error("decoder","DECODERLAYER_decoder_data_ptr_chunk","data can't decoder");
		return FALSE;
	}
	
	
	//stripptr=stripblockptr->stripptr;
	strdes=regionptr->strdes;

	disknum=strdes->disknum;
	chunknum=strdes->chunknum;

	stripchunkmaxnum=calstripchunkmaxnum(chunknum,disknum);
	stripnum=stripblockgroupptr->groupsize;

	chunkmaxnum=calmaxchunknum(stripnum,stripchunkmaxnum);
	//可以申请空间了
	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	if(chunkblockptr!=NULL)//不为空释放
	{
		free(chunkblockptr);
	}
	chunkblockptr=talloc(CHUNKBLOCK,chunkmaxnum);
	if(chunkblockptr==NULL)
	{
		show_error("decoder","DECODERLAYER_decoder_data_ptr","No memory");
		return FALSE;
	}
	chunkblockgroupptr->chunkblockptr=chunkblockptr;
	//chunkblockgroupptr->groupsize=chunkmaxnum;
	resTF=profile_stripblock_to_datachunkblock(stripblockgroupptr,chunkblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("decoder","DECODERLAYER_decoder_data_ptr","data chunk block can't create");
		return FALSE;
	}
	return TRUE;
}
int decoder_DECODERLAYER_decoder_data_ID_chunk(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,UINT64 regionid)
{
	REGION *regionptr;
	int resTF;
	regionptr=profile_region_search_ptr(regionid);
	if(regionptr==NULL)
	{
		show_error("decoder","decoder_DECODERLAYER_decoder_data_ID_chunk","regionptr can't find");
		return FALSE;
	}
	resTF=decoder_DECODERLAYER_decoder_data_ptr_chunk(stripblockgroupptr,chunkblockgroupptr,errormatrix,regionptr);
	if(resTF==FALSE)
	{
		show_error("decoder","decoder_DECODERLAYER_decoder_data_ID_chunk","chunk data can't decode");
		return FALSE;
	}
	return TRUE;
}

//recover
int decoder_DECODERLAYER_decoder_data_ptr_chunk_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr)
{
	int resTF,maintype,codetype,subtype;
	codetype=regionptr->codetype;
	maintype=maintype(codetype);
	subtype=subtype(codetype);
	switch(maintype)
	{
	case Hamming:
		resTF=HAMMING_decoder_parity_degrade(chunkblockgroupptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("decoder","DECODERLAYER_decoder_data_ptr_chunk_degrade","HAMMING can't run");
			return FALSE;
		}
		break;
	case reed_sol:
		resTF=RSCODE_decoder_parity_degrade(chunkblockgroupptr,errormatrix,subtype);
		if(resTF==FALSE)
		{
			show_error("decoder","DECODERLAYER_decoder_data_ptr_chunk_degrade","RSCODE can't run");
			return FALSE;
		}
		break;
	case RAID5:
		resTF=RAID5_decoder_parity_degrade(chunkblockgroupptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("decoder","DECODERLAYER_decoder_data_ptr_chunk_degrade","RAID5 can't run");
			return FALSE;
		}
		break;
	case RAID6:
		resTF=RAID6_decoder_parity_degrade(chunkblockgroupptr,errormatrix,subtype);
		if(resTF==FALSE)
		{
			show_error("decoder","DECODERLAYER_decoder_data_ptr_chunk_degrade","RAID6 can't run");
			return FALSE;
		}
		break;
	case MSR:
		resTF=MSR_decoder_parity_degrade(chunkblockgroupptr,errormatrix,subtype);
		if(resTF==FALSE)
		{
			show_error("decoder","DECODERLAYER_decoder_data_ptr_chunk_degrade","MSR can't run");
			return FALSE;
		}
		break;
	case MBR:
		resTF=MBR_decoder_parity_degrade(chunkblockgroupptr,errormatrix,subtype);
		if(resTF==FALSE)
		{
			show_error("decoder","DECODERLAYER_decoder_data_ptr_chunk_degrade","MBR can't run");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int decoder_DECODERLAYER_decoder_data_ID_chunk_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,UINT64 regionid)
{
	REGION *regionptr;
	int resTF;
	regionptr=profile_region_search_ptr(regionid);
	if(regionptr==NULL)
	{
		show_error("decoder","decoder_DECODERLAYER_decoder_data_ID_chunk_degrade","region can't find");
		return FALSE;
	}
	resTF=decoder_DECODERLAYER_decoder_data_ptr_chunk_degrade(chunkblockgroupptr,errormatrix,regionptr);
	if(resTF==FALSE)
	{
		show_error("decoder","decoder_DECODERLAYER_decoder_data_ID_chunk_degrade","chunk can't degrade decode");
		return FALSE;
	}
	return TRUE;
}

//将校验数据和数据生成失效数据块
/*int decoder_DECODERLAYER_decoder_data_ID(CHUNKBLOCKSTRIPGROUP *chunkblockstripptr,ERRORPATTERN *errormatrix,UINT64 regionid)
{
	//进行解码
	int resTF;
	REGION *regionptr;
	regionptr=profile_region_search_ptr(regionid);
	if(regionptr==NULL)
	{
		show_error("decoder","DECODERLAYER_decoder_data_ID","region can't find");
		return FALSE;
	}
	resTF=decoder_DECODERLAYER_decoder_data_ptr(chunkblockgroupptr,stripblockgroupptr,errormatrix,regionptr);
	if(resTF==FALSE)
	{
		show_error("decoder","DECODERLAYER_decoder_data_ID","data can't decoder");
		return FALSE;
	}
	return TRUE;
}*/


//maplayer
//主要调用decode内函数
/*int decoder_MAPLAYER_map_data_PTR_writer_chunk_chunkblockstrip(CHUNKBLOCKSTRIPGROUP *chunkblockstripgroupptr,REGION *regionptr)
{
	//将几个参数读出
	int i,j,resTF,stripnum;
	int chunknum;
	int maxchunknum;
	STRIPBLOCKGROUP *stripblockgroupptr;
	STRIPBLOCK *stripblockptr;

	CHUNKBLOCKSTRIP *chunkblockstripptr,*curchunkblockstripptr;
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr,*tarchunkblockptr;
	CHUNKBLOCKGROUP *chunkblockgroupptr;

	//转化以下接口
	stripnum=chunkblockstripgroupptr->groupsize;
	chunkblockstripptr=chunkblockstripgroupptr->chunkblockstripptr;
	chunknum=chunkblockstripptr->chunknum;
	maxchunknum=calmaxchunknum(stripnum,chunknum);

	tarchunkblockptr=talloc(CHUNKBLOCK,maxchunknum);
	if(tarchunkblockptr==NULL)
	{
		show_error("decoder","MAPLAYER_map_data_PTR_writer_chunk_chunkblockstrip","No memory");
		return FALSE;
	}

	chunkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(chunkblockgroupptr==NULL)
	{
		show_error("decoder","MAPLAYER_map_data_PTR_writer_chunk_chunkblockstrip","No memory");
		return FALSE;
	}
	chunkblockgroupptr->chunkblockptr=tarchunkblockptr;
	chunkblockgroupptr->groupsize=maxchunknum;

	stripblockptr=talloc(STRIPBLOCK,stripnum);
	if(stripblockptr==NULL)
	{
		show_error("decoder","MAPLAYER_map_data_PTR_writer_chunk_chunkblockstrip","No memory");
		return FALSE;
	}
	stripblockgroupptr=talloc(STRIPBLOCKGROUP,1);
	if(stripblockgroupptr==NULL)
	{
		show_error("decoder","MAPLAYER_map_data_PTR_writer_chunk_chunkblockstrip","No memory");
		return FALSE;
	}
	//规格化格式
	curchunkblockstripptr=chunkblockstripptr;
	for(i=0;i<stripnum;i++)
	{
		chunkblockptr=curchunkblockstripptr->datachunkblockptr;
		curchunkblockptr=chunkblockptr;
		for(j=0;j<chunknum;j++)
		{
			tarchunkblockptr->chunkptr=curchunkblockptr->chunkptr;
			tarchunkblockptr->chunkid=curchunkblockptr->chunkid;
			curchunkblockptr++;
			tarchunkblockptr++;
		}
		curchunkblockstripptr++;
	}

	resTF=decoder_MAPLAYER_map_data_PTR_writer_chunk(stripblockgroupptr,chunkblockgroupptr,regionptr);
	if(resTF==FALSE)
	{
		show_error("decoder","MAPLAYER_map_data_PTR_writer_chunk","can't map data");
		return FALSE;
	}
	//用完释放
	free(chunkblockptr);
	free(chunkblockgroupptr);
}*/
//主要调用decode计算
/*int decoder_MAPLAYER_map_data_ID_writer_chunk_chunkblockstrip(CHUNKBLOCKSTRIPGROUP *chunkblockstripgroupptr,UINT64 regionid)
{
}*/


//主要调用encode内函数
int decoder_MAPLAYER_map_data_PTR_writer_chunk(STRIPBLOCKGROUP *stripblockgroup,CHUNKBLOCKGROUP *chunkblockgroup,REGION *regionptr)
{
	int resTF;
	resTF=encoder_MAPLAYER_map_data_ptr_chunk(stripblockgroup,chunkblockgroup,regionptr);
	if(resTF==FALSE)
	{
		show_error("decoder","MAPLAYER_map_data_PTR_write","data can't map");
		return FALSE;
	}
	return TRUE;
}
//主要调用encode计算
int decoder_MAPLAYER_map_data_ID_writer_chunk(STRIPBLOCKGROUP *stripblockgroup,CHUNKBLOCKGROUP *chunkblockgroup,UINT64 regionid)
{
	int resTF;
	REGION *regionptr;
	regionptr=profile_region_search_ptr(regionid);
	if(regionptr==NULL)
	{
		show_error("decoder","MAPLAYER_map_data_ID_write","regionptr can't find");
		return FALSE;
	}
	resTF=decoder_MAPLAYER_map_data_PTR_writer_chunk(stripblockgroup,chunkblockgroup,regionptr);
	if(resTF==FALSE)
	{
		show_error("decoder","MAPLAYER_map_data_ID_write","data can't map");
		return FALSE;
	}
	return TRUE;
}

int decoder_MAPLAYER_map_data_PTR_writer(STRIPBLOCKGROUP *stripblockgroupptr,REGION *regionptr)
{
	int resTF;
	resTF=encoder_MAPLAYER_map_data_ptr(stripblockgroupptr,regionptr);
	if(resTF==FALSE)
	{
		show_error("decoder","MAPLAYER_map_data_PTR_writer","data can't map");
	}
	return TRUE;
}
int decoder_MAPLAYER_map_data_ID_writer(STRIPBLOCKGROUP *stripblockgroupptr,UINT64 regionid)
{
	REGION *regionptr;

	int resTF;
	//REGION *regionptr;
	regionptr=profile_region_search_ptr(regionid);
	if(regionptr==NULL)
	{
		show_error("decoder","MAPLAYER_map_data_ID_write","regionptr can't find");
		return FALSE;
	}
	resTF=decoder_MAPLAYER_map_data_PTR_writer(stripblockgroupptr,regionptr);
	if(resTF==FALSE)
	{
		show_error("decoder","MAPLAYER_map_data_ID_write","data can't map");
		return FALSE;
	}
	return TRUE;
}

//将生成数据根据策略从磁盘读出//这里是pushtime来看策略
int decoder_MAPLAYER_map_data_PTR(CHUNKBLOCKGROUP *chunkblockgroupptr,REGION *regionptr)
{
	//计算
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *chunkptr;
	int i,chunknum,resTF;

	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunknum=chunkblockgroupptr->groupsize;

	curchunkblockptr=chunkblockptr;
	for(i=0;i<chunknum;i++)
	{
		chunkptr=curchunkblockptr->chunkptr;
		//将数据同步即可
		resTF=FILELAYER_CHUNK_READER_DATA(chunkptr);
		if(resTF==FALSE)
		{
			show_error("decoder","MAPLAYER_map_data_PTR","chunk data can't read");
			return FALSE;
		}
		curchunkblockptr++;
	}
	return TRUE;
}
//讲生成数据根据策略从磁盘读出使用id查找群
int decoder_MAPLAYER_map_data_ID(CHUNKBLOCKGROUP *chunkblockgroupptr,UINT64 regionid)
{
	REGION *regionptr;

	int resTF;
	//REGION *regionptr;
	regionptr=profile_region_search_ptr(regionid);
	if(regionptr==NULL)
	{
		show_error("decoder","MAPLAYER_map_data_ID","regionptr can't find");
		return FALSE;
	}
	resTF=decoder_MAPLAYER_map_data_PTR(chunkblockgroupptr,regionptr);
	if(resTF==FALSE)
	{
		show_error("decoder","MAPLAYER_map_data_ID","data can't map");
		return FALSE;
	}
	return TRUE;
}
//条带数据用于degrade download数据
//需要根据不同的算法选择相应的degrade的map读取
int decoder_MAPLAYER_map_data_PTR_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr)
{
	//开始定制map数据
	int codetype,subtype,maintype,resTF;
	codetype=regionptr->codetype;
	maintype=maintype(codetype);
	subtype=subtype(codetype);
	switch(maintype)
	{
	case Hamming:
		resTF=HAMMING_degrade_map_chunkblock(chunkblockgroupptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("decoder","MAPLAYER_map_data_PTR_degrade","chunk data can't map");
			return FALSE;
		}
		break;
	case reed_sol:
		resTF=RSCODE_degrade_map_chunkblock(chunkblockgroupptr,errormatrix,subtype);
		if(resTF==FALSE)
		{
			show_error("decoder","MAPLAYER_map_data_PTR_degrade","chunk data can't map");
			return FALSE;
		}
		break;
	case RAID5:
		resTF=RAID5_degrade_map_chunkblock(chunkblockgroupptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("decoder","MAPLAYER_map_data_PTR_degrade","chunk data can't map");
			return FALSE;
		}
		break;
	case RAID6:
		resTF=RAID6_degrade_map_chunkblock(chunkblockgroupptr,errormatrix,subtype);
		if(resTF==FALSE)
		{
			show_error("decoder","MAPLAYER_map_data_PTR_degrade","chunk data can't map");
			return FALSE;
		}
		break;
	case MSR:
		resTF=MSR_degrade_map_chunkblock(chunkblockgroupptr,errormatrix,subtype);
		if(resTF==FALSE)
		{
			show_error("decoder","MAPLAYER_map_data_PTR_degrade","chunk data can't map");
			return FALSE;
		}
		break;
	case MBR:
		resTF=MBR_degrade_map_chunkblock(chunkblockgroupptr,errormatrix,subtype);
		if(resTF==FALSE)
		{
			show_error("decoder","MAPLAYER_map_data_PTR_degrade","chunk data can't map");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
//需要根据不同的算法选择相应的degrade的map读取
int decoder_MAPLAYER_map_data_ID_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,UINT64 regionid)
{
	REGION *regionptr;

	int resTF;
	//REGION *regionptr;
	regionptr=profile_region_search_ptr(regionid);
	if(regionptr==NULL)
	{
		show_error("decoder","MAPLAYER_map_data_ID_degrade","regionptr can't find");
		return FALSE;
	}
	resTF=decoder_MAPLAYER_map_data_PTR_degrade(chunkblockgroupptr,errormatrix,regionptr);
	if(resTF==FALSE)
	{
		show_error("decoder","MAPLAYER_map_data_PTR_degrade","chunk data can't read map");
		return FALSE;
	}
	return TRUE;
}

//进行recover的map操作
int decoder_MAPLAYER_map_data_PTR_recover(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr)
{
	int resTF,codetype,maintype;
	codetype=regionptr->codetype;
	maintype=maintype(codetype);

	switch(maintype)
	{
	case Hamming:
		resTF=HAMMING_recover_map_stripblock(stripblockgroupptr,errormatrix,regionptr);
		if(resTF==FALSE)
		{
			show_error("decoder","MAPLAYER_map_data_PTR_recover","chunk data can't map");
			return FALSE;
		}
		break;
	case reed_sol:
		resTF=RSCODE_recover_map_stripblock(stripblockgroupptr,errormatrix,regionptr);
		if(resTF==FALSE)
		{
			show_error("decoder","MAPLAYER_map_data_PTR_recover","chunk data can't map");
			return FALSE;
		}
		break;
	case RAID5:
		resTF=RAID5_recover_map_stripblock(stripblockgroupptr,errormatrix,regionptr);
		if(resTF==FALSE)
		{
			show_error("decoder","MAPLAYER_map_data_PTR_recover","chunk data can't map");
			return FALSE;
		}
		break;
	case RAID6:
		resTF=RAID6_recover_map_stripblock(stripblockgroupptr,errormatrix,regionptr);
		if(resTF==FALSE)
		{
			show_error("decoder","MAPLAYER_map_data_PTR_recover","chunk data can't map");
			return FALSE;
		}
		break;
	case MSR:
		resTF=MSR_recover_map_stripblock(stripblockgroupptr,errormatrix,regionptr);
		if(resTF==FALSE)
		{
			show_error("decoder","MAPLAYER_map_data_PTR_recover","chunk data can't map");
			return FALSE;
		}
		break;
	case MBR:
		resTF=MBR_recover_map_stripblock(stripblockgroupptr,errormatrix,regionptr);
		if(resTF==FALSE)
		{
			show_error("decoder","MAPLAYER_map_data_PTR_recover","chunk data can't map");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int decoder_MAPLAYER_map_data_ID_recover(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,UINT64 regionid)
{
	REGION *regionptr;

	int resTF;
	//REGION *regionptr;
	regionptr=profile_region_search_ptr(regionid);
	if(regionptr==NULL)
	{
		show_error("decoder","MAPLAYER_map_data_ID_degrade","regionptr can't find");
		return FALSE;
	}
	resTF=decoder_MAPLAYER_map_data_PTR_recover(stripblockgroupptr,errormatrix,regionptr);
	if(resTF==FALSE)
	{
		show_error("decoder","MAPLAYER_map_data_ID_degrade","chunk data map can't read");
		return FALSE;
	}
	return TRUE;
}

//释放chunk空间
int decoder_MAPLAYER_map_data_free_chunk(CHUNKBLOCKGROUP *chunkblockgroupptr)
{
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *chunkptr;
	int i,chunkgroupsize;
	BYTE *dataptr;
	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunkgroupsize=chunkblockgroupptr->groupsize;

	curchunkblockptr=chunkblockptr;
	for(i=0;i<chunkgroupsize;i++)
	{
		chunkptr=curchunkblockptr->chunkptr;
		dataptr=chunkptr->chunkcontent;
		if(dataptr!=NULL)
		{
			free(dataptr);
			dataptr=NULL;
			chunkptr->chunkcontent=dataptr;
		}
		
		curchunkblockptr++;
	}
	return TRUE;
}
int decoder_MAPLAYER_map_data_free_strip(STRIPBLOCKGROUP *stripblockgroupptr)
{
	int i,j,resTF;
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	STRIP *strippptr;
	int stripnum;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;
	int chunknum;
	BYTE *dataptr;

	stripblockptr=stripblockgroupptr->stripblockptr;
	stripnum=stripblockgroupptr->groupsize;

	curstripblockptr=stripblockptr;
	for(i=0;i<stripnum;i++)
	{
		strippptr=curstripblockptr->stripptr;

		chunkgroupptr=strippptr->chunklist;

		chunkptr=chunkgroupptr->ckgroup;
		chunknum=chunkgroupptr->groupsize;

		curchunkptr=chunkptr;
		for(j=0;j<chunknum;j++)
		{
			dataptr=curchunkptr->chunkcontent;
			if(dataptr!=NULL)
			{
				free(dataptr);
				dataptr=NULL;
				curchunkptr->chunkcontent=dataptr;
			}
			curchunkptr++;
		}
		curstripblockptr++;
	}
}


//总体调用函数
//其中soupath是本地文件路径，tarpath是文件系统路径
int decoder_filestore_API_path(char *tarpath,char *soupath)
{
	int resTF;
	//FILE *fileptr;
	BYTESTREAM *filecontent;
	filecontent=talloc(BYTESTREAM,1);
	if(filecontent==NULL)
	{
		show_error("decoder","filestore_API_path","No memory");
		return FALSE;
	}
	//fileptr=fopen(tarpath,"wb");//将数据写入目标地址
	//计算大小
	//file_FILELAYER_get_filesize(fileptr);

	resTF=decoder_filestore_API_CONTENT(filecontent,soupath);
	if(resTF==FALSE)
	{
		show_error("decoder","filestore_API_path","filecontent can't read");
		return FALSE;
	}
	//fileptr=(soupath,"wb");//将数据写入目标地址
	resTF=decoder_METALAYER_storage(tarpath,filecontent);
	if(resTF==FALSE)
	{
		show_error("decoder","filestore_API_path","filecontent can't storage in the local file system");
		return FALSE;
	}
	return TRUE;
}
//其中BYTESTREAM filecontent代表文件内容，tarpath是文件系统路径
int decoder_filestore_API_CONTENT(BYTESTREAM *filecontent,char *soupath)
{
	FILEMETA *filemetaptr;
	REGION *regionptr;
	CHUNKBLOCK *chunkblockptr;
	CHUNKBLOCKGROUP *chunkblockgroupptr;
	BYTE *filestreamptr;

	int chunknum,resTF,filesize;
	FILEINF *filechunkinf;
	//开空间
	chunkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(chunkblockgroupptr==NULL)
	{
		show_error("decoder","filestore_API_CONTENT","No memory");
		return FALSE;
	}
	//获取当前的regionindex
	filemetaptr=systemcom_FILE_create_handle(soupath);
	if(filemetaptr==NULL)
	{
		show_error("decoder","filestore_API_CONTENT","file handle can't create");
		return FALSE;
	}
	regionptr=filemetaptr->regionptr;
	filechunkinf=filemetaptr->filechunkinf;
	chunkblockptr=filechunkinf->chunklist;
	chunknum=filechunkinf->chunknum;

	filesize=filemetaptr->filesize;
	filestreamptr=NULL;//获取文件大小

	filecontent->bytessize=filesize;
	filecontent->BYTEcontent=filestreamptr;

	chunkblockgroupptr->chunkblockptr=chunkblockptr;
	chunkblockgroupptr->groupsize=chunknum;
	//将数据进行赋值
	resTF=decoder_MAPLAYER_map_data_PTR(chunkblockgroupptr,regionptr);
	if(resTF==FALSE)
	{
		show_error("decoder","MAPLAYER_map_data_PTR","data can't map");
		return FALSE;
	}
	resTF=decoder_METALAYER_merger(filecontent,chunkblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("decoder","MAPLAYER_map_data_PTR","the filecontent can't merge");
		return FALSE;
	}
	//将数据释放
	resTF=decoder_MAPLAYER_map_data_free_chunk(chunkblockgroupptr);//释放chunk空间
	if(resTF==FALSE)
	{
		show_error("decoder","MAPLAYER_map_data_PTR","chunk data can't free");
		return FALSE;
	}
	return TRUE;
}
//degrade函数
//使用出错模式来进行degrade数据读取，其中soupath是本地分布式文件路径，tarpath是计算文件系统路径
int decoder_filestore_API_path_degrade(char *tarpath,char *soupath,ERRORPATTERN *errormatrix)
{
	int resTF;
	BYTESTREAM *filecontent;
	filecontent=talloc(BYTESTREAM,1);
	if(filecontent==NULL)
	{
		show_error("decoder","filestore_API_path_degrade","No memory");
		return FALSE;
	}
	resTF=decoder_filestore_API_CONTENT_degrade(filecontent,soupath,errormatrix);
	if(resTF==FALSE)
	{
		show_error("decoder","filestore_API_path_degrade","No memory");
		return FALSE;
	}
	//fileptr=(soupath,"wb");//将数据写入目标地址
	resTF=decoder_METALAYER_storage(tarpath,filecontent);
	if(resTF==FALSE)
	{
		show_error("decoder","filestore_API_path","filecontent can't storage in the local file system");
		return FALSE;
	}
	return TRUE;
}
//使用出错模式来进行degrade数据读取，其中BYTESTREAM filecontent代表文件内容，tarpath是分布式文件系统路径
extern int decoder_filestore_API_CONTENT_degrade(BYTESTREAM *filecontent,char *soupath,ERRORPATTERN *errormatrix)
{
	int resTF;
	FILEMETA *filemetaptr;
	FILEINF *finfptr;

	CHUNKBLOCKGROUP *chunkblockgroupptr;
	CHUNKBLOCK *chunkblockptr;
	int chunknum;

	STRIPBLOCKGROUP *stripblockgroupptr;

	REGION *regionptr;
	//开空间
	chunkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(chunkblockgroupptr==NULL)
	{
		show_error("decoder","filestore_API_CONTENT","No memory");
		return FALSE;
	}
	//首先开空间
	filemetaptr=systemcom_FILE_create_handle(soupath);
	if(filemetaptr==NULL)
	{
		show_error("decoder","filestore_API_CONTENT","file handle can't create");
		return FALSE;
	}
	filecontent->BYTEcontent=NULL;
	filecontent->bytessize=filemetaptr->filesize;

	regionptr=filemetaptr->regionptr;
	finfptr=filemetaptr->filechunkinf;
	//生成找到相应的数据条带
	chunkblockptr=finfptr->chunklist;
	chunknum=finfptr->chunknum;
	//先将chunk相应的条带数据导入内存，不包括损坏的磁盘
	chunkblockgroupptr->chunkblockptr=chunkblockptr;
	chunkblockgroupptr->groupsize=chunknum;
	//读取数据块
	resTF=decoder_MAPLAYER_map_data_PTR_degrade(chunkblockgroupptr,errormatrix,regionptr);
	if(resTF==FALSE)
	{
		show_error("decoder","filestore_API_CONTENT_degrade","chunk data can't read");
		return FALSE;
	}
	//计算在错误盘中的数据
	resTF=decoder_DECODERLAYER_decoder_data_ptr_chunk_degrade(chunkblockgroupptr,errormatrix,regionptr);
	if(resTF==FALSE)
	{
		show_error("decoder","filestore_API_CONTENT_degrade","chunk data can't degrade");
		return FALSE;
	}
	//将数据合并在一起
	resTF=decoder_METALAYER_merger(filecontent,chunkblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("decoder","filestore_API_CONTENT_degrade","data can't merge");
		return FALSE;
	}
	return TRUE;
}

//recover函数
//使用出错模式来恢复数据,当stripblockgroup为空时,将region恢复全部数据
int decoder_filestore_API_recover_ID(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,UINT64 regionid)
{
	//恢复数据
	int resTF;
	REGION *regionptr;
	regionptr=profile_region_search_ptr(regionid);
	if(regionptr==NULL)
	{
		show_error("decoder","filestore_API_recover_ID","region can't find");
		return FALSE;
	}
	resTF=decoder_filestore_API_recover_PTR(stripblockgroupptr,errormatrix,regionptr);
	if(resTF==FALSE)
	{
		show_error("decoder","filestore_API_recover_ID","data can't recover");
		return FALSE;
	}
	return TRUE;
}
//使用出错模式来恢复数据,当stripblockgroup为空时,将region恢复全部数据
int decoder_filestore_API_recover_PTR(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr)
{
	//恢复数据
	int resTF;
	resTF=decoder_MAPLAYER_map_data_PTR_recover(stripblockgroupptr,errormatrix,regionptr);//需要根据不同的算法选择相应的recover的map读取
	if(resTF==FALSE)
	{
		show_error("decoder","filestore_API_recover","recover can't read");
		return FALSE;
	}
	//resTF=decoder_DECODERLAYER_decoder_data_ptr(stripblockgroupptr,errormatrix,regionptr);
	
	if(resTF==FALSE)
	{
		show_error("decoder","filestore_API_recover","recover can't run");
		return FALSE;
	}
	resTF=decoder_MAPLAYER_map_data_PTR_writer(stripblockgroupptr,regionptr);//将条带数据同步到
	if(resTF==FALSE)
	{
		show_error("decoder","filestore_API_recover","recover can't writer");
		return FALSE;
	}
	return TRUE;
}