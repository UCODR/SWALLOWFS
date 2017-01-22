#include "encoder.h"
//meta-layer
//提取文件元数据和相应文件内容
int encoder_METALAYER_matedata(BYTESTREAM *filecontent,char *filepath)
{
	INT64 filesize; 
	int i,resTF;
	//UINT64 filemetaid,userid,;
	BYTE *bufferptr;
	//struct tm *createtime;
	//struct tm *updatetime;
	FILE *fp;

	
	
	fp=fopen(filepath,"rb");
	if(fp==NULL)
	{
		show_error("encoder","METALAYER_matedata","file handle can't open");
		return FALSE;
	}

	filesize=file_FILELAYER_get_filesize(fp);
	if(filesize==NONE)
	{
		show_error("encoder","METALAYER_matedata","file has no content");
		return FALSE;
	}
	bufferptr=talloc(BYTE,filesize);//文件大小的缓冲区
	if(bufferptr==NULL)
	{
		show_error("encoder","METALAYER_matedata","No mempry");
		return FALSE;
	}
	

	i=0;
	//while(!feof(fp))//没有读取完毕就继续
	/*for(i=0;i<filesize;i++)
	{
		//bufferptr[i]=fgetc(fp);
		fscanf(fp,"%c",&bufferptr[i]);
		//i++;
	}*/
	fread(bufferptr,1,filesize,fp);
	filecontent->BYTEcontent=bufferptr;
	filecontent->bytessize=filesize;
	filesize=i;

	fclose(fp);
	/*if(filemetaptr!=NULL)
	{
		free(filemetaptr);
	}
	/*filemetaptr=talloc(FILEMETA,1);
	if(filemetaptr==NULL)
	{
		show_error("encoder","METALAYER_matedata","No mempry");
		return FALSE;
	}*/
	//原来创建fmeta已完成
	//filemetaid=get_state_glofileid();
	//set_state_glofileid_add(1);
	//filemetaptr->FileID=filemetaid;
	//filemetaptr->filesize=(UINT64)filesize;//将文件大小赋值
	
	return TRUE;
}

//将文件数据分解相应的块
int encoder_METALAYER_split(CHUNKBLOCKGROUP *ckbgroup,BYTESTREAM *filecontent)
{

	//将当前讲数据拆分成为
	int i,chkgroupsize,chunknum;
	int chunksize;

	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;

	CHUNK *chunkptr,*curchunkptr;
	UINT64 filesize;

	int remainsize;
	
	BYTE *chunkcontent,*cursourceptr;
	chunkblockptr=ckbgroup->chunkblockptr;
	if(chunkblockptr==NULL)
	{
		show_error("encoder","METALAYER_split","chunkblockptr is NULL");
		return FALSE;
	}

	chunkptr=chunkblockptr->chunkptr;//获取当前chunk指针
	chunksize=chunkptr->sizenum;//得出目标chunk的字节数

	filesize=filecontent->bytessize;
	chunknum=calchunknum(filesize,chunksize);

	chkgroupsize=ckbgroup->groupsize;
	if(chunknum!=chkgroupsize)
	{
		show_error("encoder","METALAYER_split","chunkgroupsize is not correct");
		return FALSE;
	}

	curchunkblockptr=chunkblockptr;
	cursourceptr=filecontent->BYTEcontent;
	for(i=0;i<chkgroupsize;i++)
	{
		curchunkptr=curchunkblockptr->chunkptr;
		chunkcontent=talloc(BYTE,chunksize);
		if(chunkcontent==NULL)
		{
			show_error("encoder","METALAYER_split","No memory");
			return FALSE;
		}
		//将内存拷贝过去
		if(i<(chkgroupsize-1))
		{
			mcpy(chunkcontent,cursourceptr,BYTE,chunksize);
		}
		else
		{
			remainsize=calremainsize(chunksize,chunknum,filesize);
			mcpy(chunkcontent,cursourceptr,BYTE,remainsize);
		}
		curchunkptr->chunkcontent=chunkcontent;
		curchunkblockptr++;
		cursourceptr=cursourceptr+chunksize;
	}
	return TRUE;
}

//encoder-layer
//调用编码函数
//使用选的region编码方式生成相应全体数据块先数据生成数据校验
int encoder_ENCODERLAYER_encoder_data_ptr(STRIPBLOCKGROUP *stripblockgroupptr,REGION *regionptr)
{
	int codetype;
	int maintype;
	int subtype,resTF;
	//获取编码类别
	codetype=regionptr->codetype;
	maintype=maintype(codetype);
	subtype=subtype(codetype);
	//找到相应的编码类别
	switch(maintype)
	{
	//使用Hamming相当于RAID-2
	case Hamming:
		resTF=HAMMING_calculate_parity(stripblockgroupptr);
		if(resTF==FALSE)
		{
			show_error("encoder","ENCODERLAYER_encoder_data_ptr","HAMMING can't run");
			return FALSE;
		}
		break;
	//reed-solomon编码接口
	case reed_sol:
		resTF=RSCODE_calculate_parity(stripblockgroupptr,subtype);
		if(resTF==FALSE)
		{
			show_error("encoder","ENCODERLAYER_encoder_data_ptr","RSCODE can't run");
			return FALSE;
		}
		break;
	//使用RAID-5
	case RAID5:
		resTF=RAID5_calculate_parity(stripblockgroupptr);
		if(resTF==FALSE)
		{
			show_error("encoder","ENCODERLAYER_encoder_data_ptr","RAID5 can't run");
			return FALSE;
		}
		break;
	//使用RAID-6中包括EVENODD，主要
	case RAID6:
		resTF=RAID6_calculate_parity(stripblockgroupptr,subtype);
		if(resTF==FALSE)
		{
			show_error("encoder","ENCODERLAYER_encoder_data_ptr","RAID6 can't run");
			return FALSE;
		}
		break;
	//MSR
	case MSR:
		resTF=MSR_calculate_parity(stripblockgroupptr,subtype);
		if(resTF==FALSE)
		{
			show_error("encoder","ENCODERLAYER_encoder_data_ptr","MSR can't run");
			return FALSE;
		}
		break;
	//MBR
	case MBR:
		resTF=MBR_calculate_parity(stripblockgroupptr,subtype);
		if(resTF==FALSE)
		{
			show_error("encoder","ENCODERLAYER_encoder_data_ptr","MBR can't run");
			return FALSE;
		}
		break;
	case OTHER:
		resTF=OTHER_calculate_parity(stripblockgroupptr,subtype);
		if(resTF==FALSE)
		{
			show_error("encoder","ENCODERLAYER_encoder_data_ptr","Other code can't run");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
//通过regionid将数据块进行编码
int encoder_ENCODERLAYER_encoder_data_id(STRIPBLOCKGROUP *stripblockgroupptr,UINT64 regionid)
{
	REGIONGROUP *regiongroupptr;
	REGION *regionptr,*curregionptr;
	int i,regiongroupsize,resTF;
	UINT64 currentid;
	//得到当前的region编号
	regiongroupptr=get_state_gloregiongroup_PTR();
	regionptr=regiongroupptr->regiongroup;
	regiongroupsize=regiongroupptr->groupsize;

	curregionptr=regionptr;

	for(i=0;i<regiongroupsize;i++)
	{
		currentid=curregionptr->RegionID;
		if(currentid==regionid)
		{
			regionptr=curregionptr;
			break;
		}
		curregionptr++;
	}
	if(i==regiongroupsize)
	{
		show_error("encoder","ENCODERLAYER_encoder_data_id","regionid can't find");
		return FALSE;
	}
	resTF=encoder_ENCODERLAYER_encoder_data_ptr(stripblockgroupptr,regionptr);
	if(resTF==FALSE)
	{
		show_error("encoder","ENCODERLAYER_encoder_data_id","region ptr");
		return FALSE;
	}
	return TRUE;
}

//map-layer
//存储函数
//讲数据块放入指定位置
//int encoder_MAPLAYER_map_data_ptr(CHUNKBLOCKGROUP *chunkblockgroupptr,STRIPBLOCKGROUP *stripblockgroupptr,REGION *regionptr)
int encoder_MAPLAYER_map_data_ptr(STRIPBLOCKGROUP *stripblockgroupptr,REGION *regionptr)
{
	int resTF;
	resTF=encoder_MAPLAYER_map_data_and_file_ptr(stripblockgroupptr,NULL,regionptr);
	if(resTF==FALSE)
	{
		show_error("encoder","MAPLAYER_map_data_ptr","data can't map");
		return FALSE;
	}
	return TRUE;
}
//将数据块放入指定位置+文件数据
int encoder_MAPLAYER_map_data_and_file_ptr(STRIPBLOCKGROUP *stripblockgroupptr,FILEMETABLOCKGROUP *filemetablockgroupptr,REGION *regionptr)
{
	//只需要将数据
	int i,j,k,resTF;
	int disknum;

	REGIONBLOCK *dirtyregionblockptr;
	int regionsize;

	CHUNKBLOCK *dirtychunkblockptr,*curdirtychunkblockptr;
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;
	int chunksize;
	int chunknum;

	STRIPSECTBLOCK *dirtystrsetblockptr,*curdirtystrsetblockptr;
	STRIPSECTGROUP *strsetgrouptr;
	STRIPSECT *strsetptr,*curstrsetptr;
	int strsetsize;
	int strsetnum;

	STRIPBLOCK *dirtystripblockptr;
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	STRIPDES *strdesptr;
	STRIP *stripptr;
	int stripsize;
	
	FILEMETABLOCK *dirtyfilemetablockptr;
	int filenum;

	strdesptr=regionptr->strdes;

	disknum=strdesptr->disknum;
	chunknum=strdesptr->chunknum;
	
	stripblockptr=stripblockgroupptr->stripblockptr;
	stripsize=stripblockgroupptr->groupsize;

	//开始申请脏数据的缓冲区
	dirtyregionblockptr=talloc(REGIONBLOCK,1);
	if(dirtyregionblockptr==NULL)
	{
		show_error("encoder","MAPLAYER_map_data_ptr","No memory");
		return FALSE;
	}
	regionsize=1;

	dirtyregionblockptr->regionptr=regionptr;
	dirtyregionblockptr->regionid=regionptr->RegionID;

	dirtystripblockptr=talloc(STRIPBLOCK,stripsize);
	if(dirtystripblockptr==NULL)
	{
		show_error("encoder","MAPLAYER_map_data_ptr","No memory");
		return FALSE;
	}

	strsetnum=stripsize*disknum;

	dirtystrsetblockptr=talloc(STRIPSECTBLOCK,strsetnum);
	if(dirtystrsetblockptr==NULL)
	{
		show_error("encoder","MAPLAYER_map_data_ptr","No memory");
		return FALSE;
	}
	curdirtystrsetblockptr=dirtystrsetblockptr;

	chunknum=strsetnum*chunknum;
	dirtychunkblockptr=talloc(CHUNKBLOCK,chunknum);
	if(dirtychunkblockptr==NULL)
	{
		show_error("encoder","MAPLAYER_map_data_ptr","No memory");
		return FALSE;
	}
	curdirtychunkblockptr=dirtychunkblockptr;
	//知道了需要修改的部分同步顺序
	//先同步元数据，先将数据设定为脏然后一起同步

	
	mcpy(dirtystripblockptr,stripblockptr,STRIPBLOCK,stripsize);//数据已经都在了拷贝即可

	//将数据写入磁盘并且将元数据设定为脏数据
	curstripblockptr=stripblockptr;
	for(i=0;i<stripsize;i++)
	{
		stripptr=curstripblockptr->stripptr;

		strsetgrouptr=stripptr->stripsectlist;

		strsetptr=strsetgrouptr->stripsectgroup;
		strsetsize=strsetgrouptr->groupsize;

		curstrsetptr=strsetptr;
		for(j=0;j<strsetsize;j++)
		{
			curdirtystrsetblockptr->stripsectptr=curstrsetptr;
			curdirtystrsetblockptr->stripsectid=curstrsetptr->StripsectID;

			chunkgroupptr=curstrsetptr->chunklist;

			chunkptr=chunkgroupptr->ckgroup;
			chunksize=chunkgroupptr->groupsize;

			curchunkptr=chunkptr;
			for(k=0;k<chunksize;k++)
			{
				curdirtychunkblockptr->chunkptr=curchunkptr;
				curdirtychunkblockptr->chunkid=curchunkptr->ChunkID;
				resTF=profile_chunk_data_isfree(curchunkptr);
				if(resTF==FALSE)//当前不为空
				{
					resTF=profile_chunk_data_haswrited(curchunkptr);
					if(resTF==TRUE)//已经写过需要同步
					{
						resTF=file_chunk_write_API(curchunkptr);
						if(resTF==FALSE)
						{
							show_error("encoder","MAPLAYER_map_data_ptr","chunk data can't write");
							return FALSE;
						}
					}
					else
					{
						resTF=profile_free_chunk_data(curchunkptr);
						if(resTF==FALSE)
						{
							show_error("encoder","MAPLAYER_map_data_ptr","chunk data can't free");
							return FALSE;
						}
					}
				}
				
				

				curdirtychunkblockptr++;
				curchunkptr++;
			}
			curdirtystrsetblockptr++;
			curstrsetptr++;
		}
		curstripblockptr++;
	}
	//设定文件脏数据
	if(filemetablockgroupptr==NULL)
	{
		dirtyfilemetablockptr=NULL;
		filenum=0;
	}
	else
	{
		dirtyfilemetablockptr=filemetablockgroupptr->filemetablockptr;
		filenum=filemetablockgroupptr->groupsize;
	}
	//计算同步
	profile_dirtydata_set_data(dirtychunkblockptr,chunknum,//chunk数据
										dirtystrsetblockptr,strsetnum,//stripsect数据
										dirtystripblockptr,stripsize,//strip数据
										dirtyregionblockptr,regionsize,//region数据
										dirtyfilemetablockptr,filenum,//file数据
										NULL,0,//device数据
										NULL,0,//disk数据
										NULL,0//user数据
										);//设定全局脏数据
	resTF=profile_dirtydata_sync();//总体脏数据同步
	if(resTF==FALSE)
	{
		show_error("encoder","MAPLAYER_map_data_ptr","dirtydata can't sync");
		return FALSE;
	}

	/*chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunksize=chunkblockgroupptr->groupsize;
	//将数据写入磁盘
	curchunkblockptr=chunkblockptr;
	for(i=0;i<chunksize;i++)
	{
		//将指针读出进行写入
		chunkptr=curchunkblockptr->chunkptr;//将指针取出
		resTF=file_chunk_write_API(chunkptr);
		if(resTF==FALSE)
		{
			show_error("encoder","MAPLAYER_map_data_ptr","");
			return FALSE;
		}
		curchunkblockptr++;
	}*/
	return TRUE;
}
//通过ID将数据放入指定位置
//int encoder_MAPLAYER_map_data_id(CHUNKBLOCKGROUP *chunkblockgroupptr,STRIPBLOCKGROUP *stripblockgroupptr,UINT64 regionid)
int encoder_MAPLAYER_map_data_id(STRIPBLOCKGROUP *stripblockgroupptr,UINT64 regionid)
{
	//找到regionid的region并同步
	REGION *regionptr;
	int resTF;
	regionptr=profile_region_search_ptr(regionid);
	if(regionptr==NULL)
	{
		show_error("encoder","MAPLAYER_map_data_id","region can't find");
		return FALSE;
	}
	//resTF=encoder_MAPLAYER_map_data_ptr(chunkblockgroupptr,stripblockgroupptr,regionptr);
	resTF=encoder_MAPLAYER_map_data_ptr(stripblockgroupptr,regionptr);
	if(resTF==FALSE)
	{
		show_error("encoder","MAPLAYER_map_data_id","data can't map");
		return FALSE;
	}
	return TRUE;
}

//同步条带的元数据
int encoder_MAPLAYER_map_data_ptr_stripmeta(STRIPBLOCKGROUP *stripblockgroupptr,FILEMETABLOCKGROUP *filemetablockgroupptr,REGION *regionptr)
{
	//只需要将数据
	int i,j,k,resTF;
	int disknum;

	REGIONBLOCK *dirtyregionblockptr;
	int regionsize;

	CHUNKBLOCK *dirtychunkblockptr,*curdirtychunkblockptr;
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;
	int chunksize;
	int chunknum;

	STRIPSECTBLOCK *dirtystrsetblockptr,*curdirtystrsetblockptr;
	STRIPSECTGROUP *strsetgrouptr;
	STRIPSECT *strsetptr,*curstrsetptr;
	int strsetsize;
	int strsetnum;

	STRIPBLOCK *dirtystripblockptr;
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	STRIPDES *strdesptr;
	STRIP *stripptr;
	int stripsize;
	
	FILEMETABLOCK *dirtyfilemetablockptr;
	int filenum;

	strdesptr=regionptr->strdes;

	disknum=strdesptr->disknum;
	chunknum=strdesptr->chunknum;
	
	stripblockptr=stripblockgroupptr->stripblockptr;
	stripsize=stripblockgroupptr->groupsize;

	//开始申请脏数据的缓冲区
	dirtyregionblockptr=talloc(REGIONBLOCK,1);
	if(dirtyregionblockptr==NULL)
	{
		show_error("encoder","MAPLAYER_map_data_ptr","No memory");
		return FALSE;
	}
	regionsize=1;

	dirtyregionblockptr->regionptr=regionptr;
	dirtyregionblockptr->regionid=regionptr->RegionID;

	dirtystripblockptr=talloc(STRIPBLOCK,stripsize);
	if(dirtystripblockptr==NULL)
	{
		show_error("encoder","MAPLAYER_map_data_ptr","No memory");
		return FALSE;
	}

	strsetnum=stripsize*disknum;

	dirtystrsetblockptr=talloc(STRIPSECTBLOCK,strsetnum);
	if(dirtystrsetblockptr==NULL)
	{
		show_error("encoder","MAPLAYER_map_data_ptr","No memory");
		return FALSE;
	}
	curdirtystrsetblockptr=dirtystrsetblockptr;

	chunknum=strsetnum*chunknum;
	dirtychunkblockptr=talloc(CHUNKBLOCK,chunknum);
	if(dirtychunkblockptr==NULL)
	{
		show_error("encoder","MAPLAYER_map_data_ptr","No memory");
		return FALSE;
	}
	curdirtychunkblockptr=dirtychunkblockptr;
	//知道了需要修改的部分同步顺序
	//先同步元数据，先将数据设定为脏然后一起同步

	
	mcpy(dirtystripblockptr,stripblockptr,STRIPBLOCK,stripsize);//数据已经都在了拷贝即可

	//将数据写入磁盘并且将元数据设定为脏数据
	curstripblockptr=stripblockptr;
	for(i=0;i<stripsize;i++)
	{
		stripptr=curstripblockptr->stripptr;

		strsetgrouptr=stripptr->stripsectlist;

		strsetptr=strsetgrouptr->stripsectgroup;
		strsetsize=strsetgrouptr->groupsize;

		curstrsetptr=strsetptr;
		for(j=0;j<strsetsize;j++)
		{
			curdirtystrsetblockptr->stripsectptr=curstrsetptr;
			curdirtystrsetblockptr->stripsectid=curstrsetptr->StripsectID;

			chunkgroupptr=curstrsetptr->chunklist;

			chunkptr=chunkgroupptr->ckgroup;
			chunksize=chunkgroupptr->groupsize;

			curchunkptr=chunkptr;
			for(k=0;k<chunksize;k++)
			{
				curdirtychunkblockptr->chunkptr=curchunkptr;
				curdirtychunkblockptr->chunkid=curchunkptr->ChunkID;

				/*resTF=file_chunk_write_API(chunkptr);
				if(resTF==FALSE)
				{
					show_error("encoder","MAPLAYER_map_data_ptr","");
					return FALSE;
				}*/

				curdirtychunkblockptr++;
				curchunkptr++;
			}
			curdirtystrsetblockptr++;
			curstrsetptr++;
		}
		curstripblockptr++;
	}
	//设定文件脏数据
	if(filemetablockgroupptr==NULL)
	{
		dirtyfilemetablockptr=NULL;
		filenum=0;
	}
	else
	{
		dirtyfilemetablockptr=filemetablockgroupptr->filemetablockptr;
		filenum=filemetablockgroupptr->groupsize;
	}
	//计算同步
	profile_dirtydata_set_data(dirtychunkblockptr,chunknum,//chunk数据
										dirtystrsetblockptr,strsetnum,//stripsect数据
										dirtystripblockptr,stripsize,//strip数据
										dirtyregionblockptr,regionsize,//region数据
										dirtyfilemetablockptr,filenum,//file数据
										NULL,0,//device数据
										NULL,0,//disk数据
										NULL,0//user数据
										);//设定全局脏数据
	resTF=profile_dirtydata_sync();//总体脏数据同步
	if(resTF==FALSE)
	{
		show_error("encoder","MAPLAYER_map_data_ptr","dirtydata can't ");
		return FALSE;
	}
	return TRUE;
}
//将校验块和数据块写入内存
int encoder_MAPLAYER_map_data_and_parity_ptr(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *datablockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,REGION *regionptr)
{
	int i,paritynum,datanum,resTF;
	CHUNKBLOCK *datachunkblockptr,*curdatachunkblockptr;
	CHUNK *dchunkptr;
	//int datanum;

	CHUNKBLOCK *paritychunkblockptr,*curparitychunkblockptr;
	CHUNK *pchunkptr;
	//int paritynum;
	datachunkblockptr=datablockgroupptr->chunkblockptr;
	datanum=datablockgroupptr->groupsize;

	curdatachunkblockptr=datachunkblockptr;
	for(i=0;i<datanum;i++)
	{
		dchunkptr=curdatachunkblockptr->chunkptr;
		resTF=file_chunk_write_API(dchunkptr);
		if(resTF==FALSE)
		{
			show_error("encoder","MAPLAYER_map_data_ptr","data chunk can't write");
			return FALSE;
		}
		curdatachunkblockptr++;
	}
	paritychunkblockptr=parityblockgroupptr->chunkblockptr;
	paritynum=parityblockgroupptr->groupsize;

	curparitychunkblockptr=paritychunkblockptr;
	for(i=0;i<paritynum;i++)
	{
		pchunkptr=curparitychunkblockptr->chunkptr;
		resTF=file_chunk_write_API(pchunkptr);
		if(resTF==FALSE)
		{
			show_error("encoder","MAPLAYER_map_data_ptr","parity chunk can't write");
			return FALSE;
		}
		curparitychunkblockptr++;
	}

	return TRUE;
}
//同步条带元数据和数据块数据以及相应校验
int encoder_MAPLAYER_map_data_ptr_chunk(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *datablockgroupptr,REGION *regionptr)
{
	//第一步获取
	int resTF;
	CODEPARA *codeparamptr;
	STRIPDES *stripdesptr;
	int codenum,chunknum,codecountnum;

	CHUNKBLOCKGROUP *pchunkblockgroupptr;
	CHUNKBLOCK *pchunkblockptr;

	stripdesptr=regionptr->strdes;
	codeparamptr=regionptr->codepara;
	codenum=codeparamptr->codenum;

	chunknum=stripdesptr->chunknum;
	codenum=codeparamptr->codenum;
	codecountnum=calcodecountnum(chunknum,codenum);
	pchunkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(pchunkblockgroupptr==NULL)
	{
		show_error("encoder","MAPLAYER_map_data_ptr_chunk","No memory");
		return FALSE;
	}
	pchunkblockptr=talloc(CHUNKBLOCK,codecountnum);
	if(pchunkblockptr==NULL)
	{
		show_error("encoder","MAPLAYER_map_data_ptr_chunk","No memory");
		return FALSE;
	}
	pchunkblockgroupptr->chunkblockptr=pchunkblockptr;
	pchunkblockgroupptr->groupsize=codecountnum;
	resTF=profile_stripblock_to_paritychunkblock(stripblockgroupptr,pchunkblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("encoder","MAPLAYER_map_data_ptr_chunk","parity chunk block can't create");
		return FALSE;
	}
	resTF=encoder_MAPLAYER_map_data_and_parity_ptr(stripblockgroupptr,datablockgroupptr,pchunkblockgroupptr,regionptr);
	return TRUE;
}
//同步条带元数据和数据块数据以及文件
int encoder_MAPLAYER_map_data_and_file_ptr_CHUNK(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *datablockgroupptr,FILEMETABLOCKGROUP *filemetablockgroupptr,REGION *regionptr)
{
	//
	int resTF;
	resTF=encoder_MAPLAYER_map_data_ptr_stripmeta(stripblockgroupptr,filemetablockgroupptr,regionptr);
	if(resTF==FALSE)
	{
		show_error("encoder","MAPLAYER_map_data_and_file_ptr_CHUNK","");
		return FALSE;
	}
	return TRUE;
}






//总体调用函数
//其中soupath是本地文件路径，tarpath是文件系统路径
int encoder_filestore_API_path(char *tarpath,char *soupath)
{
	//FILE *fp;
	int resTF;
	BYTESTREAM *bytestreamptr=NULL;

	bytestreamptr=talloc(BYTESTREAM,1);
	if(bytestreamptr==NULL)
	{
		show_error("encoder","filestore_API_path","No memory");
		return FALSE;
	}
	//提取数据
	resTF=encoder_METALAYER_matedata(bytestreamptr,soupath);
	if(resTF==FALSE)
	{
		show_error("encoder","filestore_API_path","source file can't open");
		return FALSE;
	}
	resTF=encoder_filestore_API_CONTENT(tarpath,bytestreamptr);
	if(resTF==FALSE)
	{
		show_error("encoder","filestore_API_path","data can't write into target path");
		return FALSE;
	}
	return TRUE;
}
//其中BYTESTREAM filecontent代表文件内容，tarpath是文件系统路径
int encoder_filestore_API_CONTENT(char *tarpath,BYTESTREAM *filecontent)
{
	CHUNKBLOCKGROUP *chkblockgroupptr;
	CHUNKBLOCK *chunkblockptr;
	CHUNKPATH *chkpathptr;
	CHUNK *chunkptr=NULL;
	CHUNKPATH *chunkpathptr,*curchunkpathptr;

	//REGIONGROUP *regiongroupptr;
	REGION *regionptr;
	UINT64 regionindex;

	STRIPDES *stripdesptr;

	STRIPBLOCKGROUP *stripblockgroupptr;//用于记录
	STRIPBLOCK *stripblockptr;
	STRIP *stripptr;

	STRIPSECTBLOCKGROUP *strsetblockgroupptr;
	STRIPSECTBLOCK *strsetblockptr;
	STRIPSECT *strsetptr;

	FILEMETABLOCKGROUP *filemetablockgroupptr;
	FILEMETABLOCK *filemetablockptr,*curfilemetablockptr;
	FILEMETA *filemetaptr,*parentptr;
	FILEINF *fileinfptr;

	UINT64 filesize;
	int i,resTF,chunknum;//计算需要几个chunk
	int chunksize;
	//region指针
	//第一步生成id
	/*regionindex=profile_get_region_id(tarpath);
	regionptr=profile_region_search_ptr(regionindex);
	if(regionptr==NULL)
	{
		show_error("encoder","filestore_API_CONTENT","regionptr can't find");
		return FALSE;
	}*/

	filemetaptr=systemcom_FILE_create_handle(tarpath);
	if(filemetaptr==NULL)
	{
		show_error("encoder","filestore_API_CONTENT","file handle can't create");
		return FALSE;
	}
	filemetaptr->filesize=filecontent->bytessize;

	fileinfptr=filemetaptr->filechunkinf;
	if(fileinfptr!=NULL)
	{
		show_error("encoder","filestore_API_CONTENT","file have created already");
		return FALSE;
	}
	regionptr=filemetaptr->regionptr;

	stripdesptr=regionptr->strdes;

	//建立chkblockgroupptr
	chkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(chkblockgroupptr==NULL)
	{
		show_error("encoder","filestore_API_CONTENT","No memory");
		return FALSE;
	}
	chkblockgroupptr->chunkblockptr=NULL;
	chkblockgroupptr->groupsize=0;

	//建立strsetblockgroup
	strsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(strsetblockgroupptr==NULL)
	{
		show_error("encoder","filestore_API_CONTENT","No memory");
		return FALSE;
	}
	strsetblockgroupptr->stripsectblockptr=NULL;
	strsetblockgroupptr->groupsize=0;

	//建立stripblockgroup
	stripblockgroupptr=talloc(STRIPBLOCKGROUP,1);
	if(stripblockgroupptr==NULL)
	{
		show_error("encoder","filestore_API_CONTENT","No memory");
		return FALSE;
	}
	stripblockgroupptr->stripblockptr=NULL;
	stripblockgroupptr->groupsize=0;

	filemetablockgroupptr=talloc(FILEMETABLOCKGROUP,1);
	if(filemetablockgroupptr==NULL)
	{
		show_error("encoder","filestore_API_CONTENT","No memory");
		return FALSE;
	}
	filemetablockgroupptr->filemetablockptr=NULL;
	filemetablockgroupptr->groupsize=1;

	//首先我们要知道需要需要多少个块
	chunksize=stripdesptr->chunksize;//获取当前region的chunk大小
	filesize=filecontent->bytessize;

	chunknum=calchunknum(filesize,chunksize);
	//分配数据
	chunkblockptr=talloc(CHUNKBLOCK,chunknum);//这里主要因为临时申请空间不稳定因此改为固定空间
	if(chunkblockptr==NULL)
	{
		show_error("encoder","filestore_API_CONTENT","No memory");
		return FALSE;
	}
	chkblockgroupptr->chunkblockptr=chunkblockptr;

	chunkpathptr=talloc(CHUNKPATH,chunknum);
	if(chunkpathptr==NULL)
	{
		show_error("encoder","filestore_API_CONTENT","No memory");
		return FALSE;
	}
	
	strsetblockptr=talloc(STRIPSECTBLOCK,chunknum);
	if(strsetblockptr==NULL)
	{
		show_error("encoder","filestore_API_CONTENT","No memory");
		return FALSE;
	}
	strsetblockgroupptr->stripsectblockptr=strsetblockptr;

	stripblockptr=talloc(STRIPBLOCK,chunknum);//strip最多到chunk的数量，即每一个strip一个chunk
	if(stripblockptr==NULL)
	{
		show_error("encoder","filestore_API_CONTENT","No memory");
		return FALSE;
	}
	stripblockgroupptr->stripblockptr=stripblockptr;

	filemetablockptr=talloc(FILEMETABLOCK,2);//有两个文件文件
	if(filemetablockptr==NULL)
	{
		show_error("encoder","filestore_API_CONTENT","No memory");
		return FALSE;
	}
	filemetablockgroupptr->filemetablockptr=filemetablockptr;
	filemetablockptr->filemetaptr=filemetaptr;
	filemetablockptr->FileID=filemetaptr->FileID;

	curchunkpathptr=chunkpathptr;
	for(i=0;i<chunknum;i++)
	{
		chkpathptr=profile_allocate_chunk_data(regionptr);
		if(chkpathptr==NULL)
		{
			show_error("encoder","filestore_API_CONTENT","free chunk can't find");
			return FALSE;
		}

		//创建相应更新条带组
		stripptr=chkpathptr->stripptr;//获取当前条带
		//将数据加入stripblockgroup
		resTF=profile_stripblockgroup_strip_add(stripblockgroupptr,stripptr);//在stripblockgroupptr中加入一个strip
		if(resTF==FALSE)
		{
			show_error("encoder","filestore_API_CONTENT","stripptr can't add to stripblockgroup");
			return FALSE;
		}

		strsetptr=chkpathptr->stripsectptr;//获取当前stripsect
		//将数据加入stripsectblockgroup
		resTF=profile_stripsetblockgroup_stripsect_add(strsetblockgroupptr,strsetptr);;
		if(resTF==FALSE)
		{
			show_error("encoder","filestore_API_CONTENT","stripsectptr can't add to stripblockgroup");
			return FALSE;
		}

		//得到分配的chunk指针
		chunkptr=chkpathptr->chunkptr;
		chunkptr->fmeta=filemetaptr;
		chunkptr->fileid=filemetaptr->FileID;

		resTF=profile_chunkblockgroup_chunk_add(chkblockgroupptr,chunkptr);
		if(resTF==FALSE)
		{
			show_error("encoder","filestore_API_CONTENT","chunkptr can't add to chunkblockgroup");
			return FALSE;
		}
		mcpy(curchunkpathptr,chkpathptr,CHUNKPATH,1);//即将数据拷贝到目标地址
		curchunkpathptr++;
		//将数据拷贝到目标位置
		free(chkpathptr);//虽然不是这里分配但是还是要释放
	}
	//将数据进行分片
	resTF=encoder_METALAYER_split(chkblockgroupptr,filecontent);
	if(resTF==FALSE)
	{
		show_error("encoder","filestore_API_CONTENT","filecontent can't split");
		return FALSE;
	}
	//通过编码层计算条带校验和
	resTF=encoder_ENCODERLAYER_encoder_data_ptr(stripblockgroupptr,regionptr);
	if(resTF==FALSE)
	{
		show_error("encoder","filestore_API_CONTENT","strip can't encoder");
		return FALSE;
	}
	
	//经过上边的步骤数据已经将数据存储入分布式系统。
	//写入文件存储信息
	//fileinfptr=NULL;
	fileinfptr=talloc(FILEINF,1);
	if(fileinfptr==NULL)
	{
		show_error("profile","set_file_storage_information","No memory");
		return FALSE;
	}
	resTF=profile_set_file_storage_information(fileinfptr,
												chkblockgroupptr,strsetblockgroupptr,
												stripblockgroupptr,regionptr,
												chunkpathptr,filemetaptr
												);
	if(resTF==FALSE)
	{
		show_error("encoder","filestore_API_CONTENT","file storage information can't create");
		return FALSE;
	}
	filemetaptr->filechunkinf=fileinfptr;


	
	parentptr=filemetaptr->parentptr;
	resTF=profile_set_parent_filemeta_ptr(filemetaptr);
	if(resTF==FALSE)
	{
		show_error("encoder","filestore_API_CONTENT","filemeta pointer can't setup");
		return FALSE;
	}
	curfilemetablockptr=filemetablockptr+1;
	curfilemetablockptr->filemetaptr=parentptr;
	curfilemetablockptr->FileID=parentptr->FileID;
	filemetablockgroupptr->groupsize=2;
	resTF=profile_region_filemeta_add(regionptr,filemetaptr);//文件竟然已经完成了可以将它加入到region了
	if(resTF==FALSE)
	{
		show_error("encoder","filestore_API_CONTENT","file can't add to region");
		return FALSE;
	}
	//将数据定位到相应的块中
	//resTF=encoder_MAPLAYER_map_data_ptr(chkblockgroupptr,stripblockgroupptr,regionptr);
	resTF=encoder_MAPLAYER_map_data_and_file_ptr(stripblockgroupptr,filemetablockgroupptr,regionptr);
	if(resTF==FALSE)
	{
		show_error("encoder","filestore_API_CONTENT","strip can't encoder");
		return FALSE;
	}
	//最后进行以下global_define的同步
	resTF=profile_globaldefine_sync();
	if(resTF==FALSE)
	{
		show_error("encoder","filestore_API_CONTENT","globaldefine can't sync");
		return FALSE;
	}

	//将申请空间释放
	free(filemetablockgroupptr);
	//由于需要数据
	//free(filemetablockptr);

	free(chkblockgroupptr);
	//free(chunkblockptr);

	free(stripblockgroupptr);
	//free(stripblockptr);
	free(strsetblockgroupptr);
	
	return TRUE;
}
//建立新的空间将数据分配到中间
int encoder_METALAYER_update_map(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr,
								BYTESTREAM *updatestream,int offset,REGION *regionptr)
{
	int i,resTF;
	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	int chunkblocknum;

	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *chunkptr,*curchunkptr,*tarchunkptr;
	int updatechunknum;

	CHUNK *firstchunkptr,*lastchunkptr;
	int startoffset,lastoffset;
	//UINT64 firstchunkid,lastchunkid;

	BYTE *contentptr;
	int updatesize;

	int chunksize;
	STRIPDES *stripdes;

	int upindex,downindex;
	int upfull,downfull;//上下块还是不是在边界

	contentptr=updatestream->BYTEcontent;
	updatesize=updatestream->bytessize;

	stripdes=regionptr->strdes;
	//获取chunksize
	chunksize=stripdes->chunksize;

	//先看看offset是不是正好在边边界上
	//需要知道上下界关系
	if((offset%chunksize)==0)
	{
		if(((offset+updatesize)%chunksize)==0)
		{
			//说明正好是整块chunk分配
			//最好算
			upindex=offset/chunksize;
			downindex=(offset+updatesize)/chunksize;

			upfull=TRUE;
			downfull=TRUE;
		}
		else
		{
			//其中第一个块在边界上，后面不在
			upindex=offset/chunksize;//由于取上界
			downindex=(offset+updatesize)/chunksize;

			upfull=TRUE;
			downfull=FALSE;
		}
	}
	else
	{
		if(((offset+updatesize)%chunksize)==0)
		{
			//说明最后一个块在边上
			upindex=offset/chunksize;
			downindex=(offset+updatesize)/chunksize;

			upfull=FALSE;
			downfull=TRUE;
		}
		else
		{
			//都不在边界大多数
			upindex=offset/chunksize;
			downindex=(offset+updatesize)/chunksize;

			upfull=FALSE;
			downfull=FALSE;
		}
	}
	//计算chunk数据
	updatechunknum=downindex-upindex+1;//上下chunkindex可能一样
	chunkpositionblockptr=talloc(CHUNKPOSITIONBLOCK,updatechunknum);
	if(chunkpositionblockptr==NULL)
	{
		show_error("encoder","METALAYER_update_map","No memory");
		return FALSE;
	}
	chunkpositionblockgroupptr->chunkblockptr=chunkpositionblockptr;
	chunkpositionblockgroupptr->groupsize=updatechunknum;

	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunkblocknum=chunkblockgroupptr->groupsize;


	//需要计算上偏移量
	if(upfull==FALSE)
	{
		//找到第一个chunk和最后一个chunk
		startoffset=profile_update_startoffset(chunksize,offset);
		curchunkblockptr=chunkblockptr+upindex;
		firstchunkptr=curchunkblockptr->chunkptr;
	}
	else
	{
		firstchunkptr=NULL;
		startoffset=FALSE;//当前没有偏移量
		firstchunkptr=NULL;
	}

	//需要计算下偏移量
	if(downfull==FALSE)
	{
		lastoffset=profile_update_lastoffset(chunksize,offset,updatesize);
		curchunkblockptr=chunkblockptr+downindex;
		lastchunkptr=curchunkblockptr->chunkptr;
	}
	else
	{
		lastchunkptr=NULL;
		lastoffset=FALSE;
		lastchunkptr=NULL;
	}
	if(updatechunknum==1)//先处理一个特例就是存在一个chunk的情况
	{
		
		curchunkpositionblockptr=chunkpositionblockptr;
		curchunkblockptr=chunkblockptr+upindex;//找到当前块
		chunkptr=curchunkblockptr->chunkptr;

		tarchunkptr=talloc(CHUNK,1);
		if(tarchunkptr==NULL)
		{
			show_error("encoder","METALAYER_update_map","No memory");
			return FALSE;
		}

		resTF=matrix_CHUNK_copy_meta(tarchunkptr,chunkptr);//将元数据拷贝过来
		if(resTF==FALSE)
		{
			show_error("encoder","METALAYER_update_map","chunk data can't copy");
			return FALSE;
		}
		curchunkpositionblockptr->chunkptr=tarchunkptr;
		curchunkpositionblockptr->chunkid=tarchunkptr->ChunkID;
		resTF=encoder_MATELAYER_update_data_chunk(chunkpositionblockgroupptr,
											chunkptr,startoffset,lastoffset,
											updatestream);
		if(resTF==FALSE)
		{
			show_error("encoder","METALAYER_update_map","update data chunk can't create");
			return FALSE;
		}
		//printf("one chunk\n");
	}
	else
	{
		//chunkblockptr=chunkblockgroupptr->chunkblockptr;
		//chunkblocknum=chunkblockgroupptr->groupsize;
		
		//先将元数据进行拷贝
		curchunkpositionblockptr=chunkpositionblockptr;
		curchunkblockptr=chunkblockptr+upindex;//定位当前chunk位置
		//printf("several chunk split1\n");
		for(i=0;i<updatechunknum;i++)
		{
			
			chunkptr=curchunkblockptr->chunkptr;

			tarchunkptr=talloc(CHUNK,1);
			if(chunkptr==NULL)
			{
				show_error("encoder","METALAYER_update_map","No memory");
				return FALSE;
			}

			resTF=matrix_CHUNK_copy_meta(tarchunkptr,chunkptr);//将元数据拷贝过来
			if(resTF==FALSE)
			{
				show_error("encoder","METALAYER_update_map","chunk data can't copy");
				return FALSE;
			}
			curchunkpositionblockptr->chunkptr=tarchunkptr;
			curchunkpositionblockptr->chunkid=tarchunkptr->ChunkID;
			curchunkpositionblockptr++;
			curchunkblockptr++;
		}
		//printf("several chunk split\n");
		//将需要的数据写入内部
		resTF=encoder_METALAYER_update_data_split(chunkpositionblockgroupptr,//当前已有chunk列表
													firstchunkptr,startoffset,//第一个数据chunk以及离开头部的偏移量
													lastchunkptr,lastoffset,//最后一个数据chunk以及数据chunk到底部的偏移量
													updatestream);//内容的指针
		if(resTF==FALSE)
		{
			show_error("encoder","METALAYER_update_map","update data chunk can't create");
			return FALSE;
		}
		//printf("several chunk\n");
	}
	//计算当前数据chunk在矩阵中的位置
	resTF=encoder_METALAYER_location_chunkposition_update(chunkpositionblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("encoder","METALAYER_update_map","location can't calculate");
		return FALSE;
	}
	/*firstchunkptr=profile_get_chunkblock_ptr(firstchunkid,chunkblockgroupptr);
	if(firstchunkptr==NULL)
	{
		show_error("encoder","METALAYER_update_map","first chunk can't find");
		return FALSE;
	}
	lastchunkptr=profile_get_chunkblock_ptr(lastchunkid,chunkblockgroupptr);
	if(lastchunkptr==NULL)
	{
		show_error("encoder","METALAYER_update_map","last chunk can't find");
		return FALSE;
	}*/
	

	return TRUE;
}
//更新chunk位置数据
int encoder_METALAYER_location_chunkposition_update_chunk(CHUNKPOSITIONBLOCK *chunkpositionblockptr)
{
	UINT64 curchunkid,souchunkid;
	int i,j,isparity,strindex,chunkindex;
	STRIP *stripptr;

	STRIPSECTGROUP *strsetgroupptr;
	STRIPSECT *strsetptr,*curstrsetptr;
	int strsetnum;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr,*souchunkptr;
	int chunknum;

	souchunkptr=chunkpositionblockptr->chunkptr;
	stripptr=souchunkptr->stripptr;

	strsetgroupptr=stripptr->stripsectlist;

	strsetptr=strsetgroupptr->stripsectgroup;
	strsetnum=strsetgroupptr->groupsize;

	curstrsetptr=strsetptr;
	
	strindex=0;
	for(i=0;i<strsetnum;i++)
	{
		isparity=curstrsetptr->isparity;
		chunkindex=0;
		if(isparity==FALSE)//如果不是校验块
		{
			chunkgroupptr=curstrsetptr->chunklist;

			chunkptr=chunkgroupptr->ckgroup;
			chunknum=chunkgroupptr->groupsize;

			curchunkptr=chunkptr;
			chunkindex=0;
			for(j=0;j<chunknum;j++)
			{
				isparity=curchunkptr->isparity;
				if(isparity==FALSE)
				{
					curchunkid=curchunkptr->ChunkID;
					souchunkid=souchunkptr->ChunkID;
					if(curchunkid==souchunkid)//如果两个id相同说明是一个块
					{
						chunkpositionblockptr->stripsectindex=strindex;
						chunkpositionblockptr->chunkindex=chunkindex;
						return TRUE;
					}
					chunkindex++;
				}
				curchunkptr++;
			}
			strindex++;
		}
		
		curstrsetptr++;
	}
	return FALSE;
}
//定位chunk在条带中的位置
int encoder_METALAYER_location_chunkposition_update(CHUNKPOSITIONBLOCKGROUP *chunkposistionblockgroupptr)
{
	int i,resTF;
	
	CHUNKPOSITIONBLOCK *chunkpsitionblockptr,*curchunkpsitionblockptr;
	int chunknum;

	chunkpsitionblockptr=chunkposistionblockgroupptr->chunkblockptr;
	chunknum=chunkposistionblockgroupptr->groupsize;

	curchunkpsitionblockptr=chunkpsitionblockptr;
	for(i=0;i<chunknum;i++)
	{
		resTF=encoder_METALAYER_location_chunkposition_update_chunk(curchunkpsitionblockptr);
		if(resTF==FALSE)
		{
			show_error("encoder","METALAYER_location_chunkposition_update_chunk","update location can't calculate");
			return FALSE;
		}
		curchunkpsitionblockptr++;
	}
	return TRUE;
}

int encoder_MATELAYER_update_data_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										CHUNK *chunkptr,int startoffset,int lastoffset,//数据块
										BYTESTREAM *bytecontentptr//内容的指针
										)
{
	int resTF;
	BYTE *soucontentptr,*cursoucontentptr;
	BYTE *tarcontentptr,*curtarcontentptr;
	BYTE *contentptr;
	int contentsize;

	CHUNKPOSITIONBLOCK *chunkpositionblockptr;
	CHUNK *tarchunkptr;
	int chunksize;

	int lastcopysize;

	//GLOTEMPFREELIST *tempfreelist;

	contentptr=bytecontentptr->BYTEcontent;//当前的内容
	contentsize=bytecontentptr->bytessize;

	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	tarchunkptr=chunkpositionblockptr->chunkptr;//当前目标块

	chunksize=chunkptr->sizenum;
	tarcontentptr=chunkptr->chunkcontent;//看看当前内容是不是为空
	if(tarcontentptr==NULL)
	{
		tarcontentptr=talloc(BYTE,chunksize);
		if(tarcontentptr==NULL)
		{
			show_error("encoder","MATELAYER_update_data_chunk","No memory");
			return FALSE;
		}
	}
	tarchunkptr->chunkcontent=tarcontentptr;

	soucontentptr=chunkptr->chunkcontent;
	if(soucontentptr==NULL)//说明当前数据不在内存需要载入
	{
		resTF=FILELAYER_CHUNK_READER_DATA(chunkptr);
		if(resTF==FALSE)
		{
			show_error("encoder","MATELAYER_update_data_chunk","chunk data can't read");
			return FALSE;
		}
		resTF=profile_tempfree_chunk_ptr(chunkptr);
		if(resTF==FALSE)
		{
			show_error("encoder","MATELAYER_update_data_chunk","tempfree list can;t create");
			return FALSE;
		}
		soucontentptr=chunkptr->chunkcontent;
	}

	//开始分段处理
	//第一部分进行处理
	if(startoffset!=FALSE)
	{
		//首先将chunk的前半部分进行拷贝
		mcpy(tarcontentptr,soucontentptr,BYTE,startoffset);
	}
	//将目标指针移动到目标位置
	curtarcontentptr=tarcontentptr+startoffset;
	mcpy(curtarcontentptr,contentptr,BYTE,contentsize);
	
	//判断一下最后一个部分要不要拷贝
	if(lastoffset!=FALSE)
	{
		curtarcontentptr=curtarcontentptr+contentsize;//向后移动到最后
		cursoucontentptr=soucontentptr+lastoffset;//移动到最后
		//计算要拷贝的数据量
		lastcopysize=chunksize-lastoffset;
		//可以拷贝了
		mcpy(curtarcontentptr,cursoucontentptr,BYTE,lastcopysize);
	}
	//将内存拷贝数据量加上chunksize
	set_state_memcpynum_add(chunksize);
	/*resTF=matrix_CHUNK_copy_data(tarchunkptr,chunkptr);//可以这么写但是还需仔细算一下效率
	if(resTF==FALSE)
	{
		show_error("encoder","MATELAYER_update_data_chunk","chunk data can't copy");
		return FALSE;
	}*/
	return TRUE;
}

//将第一个
int encoder_METALAYER_update_data_split(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//当前已有chunk列表
												CHUNK *firstchunkptr,int startoffset,//第一个数据chunk以及离开头部的偏移量
												CHUNK *lastchunkptr,int lastoffset,//最后一个数据chunk以及数据chunk到底部的偏移量
												BYTESTREAM *bytecontentptr//内容的指针
												)
{
	int i,copydatasize,bytesizenum,resTF;
	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	CHUNK *chunkptr;
	int chunknum,chunksize;

	BYTE *soucontentptr,*cursoucontentptr;
	BYTE *tarcontentptr,*curtarcontentptr;

	bytesizenum=bytecontentptr->bytessize;

	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	chunknum=chunkpositionblockgroupptr->groupsize;

	curchunkpositionblockptr=chunkpositionblockptr;
	soucontentptr=bytecontentptr->BYTEcontent;//先假设不需要进行第一个块的制作
	for(i=0;i<chunknum;i++)
	{
		chunkptr=curchunkpositionblockptr->chunkptr;

		chunksize=chunkptr->sizenum;

		tarcontentptr=chunkptr->chunkcontent;
		if(tarcontentptr==NULL)
		{
			tarcontentptr=talloc(BYTE,chunksize);
			if(tarcontentptr==NULL)
			{
				show_error("encoder","METALAYER_update_data_split","No memory");
				return FALSE;
			}
			chunkptr->chunkcontent=tarcontentptr;
		}
		
		if(startoffset!=FALSE)//开始需要更新
		{
			if(i==0)
			{
				//如果第一个数据
				soucontentptr=firstchunkptr->chunkcontent;
				if(soucontentptr==NULL)
				{
					resTF=FILELAYER_CHUNK_READER_DATA(firstchunkptr);
					if(resTF==FALSE)
					{
						show_error("encoder","METALAYER_update_data_split","chunk data can't read");
						return FALSE;
					}
					soucontentptr=firstchunkptr->chunkcontent;
					//将其加入释放队列
					resTF=profile_tempfree_chunk_ptr(firstchunkptr);
					if(resTF==FALSE)
					{
						show_error("encoder","MATELAYER_update_data_chunk","tempfree list can't create");
						return FALSE;
					}
				}

				mcpy(tarcontentptr,soucontentptr,BYTE,startoffset);
			
				soucontentptr=bytecontentptr->BYTEcontent;
				curtarcontentptr=tarcontentptr+startoffset;//数据
				copydatasize=chunksize-startoffset;
				mcpy(curtarcontentptr,soucontentptr,BYTE,copydatasize);

				soucontentptr=soucontentptr+copydatasize;//将指针设置回去

				curchunkpositionblockptr++;//
				continue;
			}
		}
		if(lastoffset!=FALSE)//最后需要更新
		{
			if(i==(chunknum-1))
			{
				//计算
				//soucontentptr=bytecontentptr->BYTEcontent;
				mcpy(tarcontentptr,soucontentptr,BYTE,lastoffset);
				//cursoucontentptr=soucontentptr+lastoffset;
				//计算剩下需要拷贝的数据
				copydatasize=chunksize-lastoffset;
				soucontentptr=lastchunkptr->chunkcontent;//最后一个chunk
				if(soucontentptr==NULL)
				{
					resTF=FILELAYER_CHUNK_READER_DATA(lastchunkptr);//没数据读进来
					if(resTF==FALSE)
					{
						show_error("encoder","METALAYER_update_data_split","chunk data can't read");
						return FALSE;
					}
					soucontentptr=lastchunkptr->chunkcontent;
					//将其加入释放队列
					resTF=profile_tempfree_chunk_ptr(lastchunkptr);
					if(resTF==FALSE)
					{
						show_error("encoder","MATELAYER_update_data_chunk","tempfree list can't create");
						return FALSE;
					}
				}
				curtarcontentptr=tarcontentptr+lastoffset;
				cursoucontentptr=soucontentptr+lastoffset;
				copydatasize=chunksize-lastoffset;//计算当前需要拷贝的数据量
				mcpy(curtarcontentptr,cursoucontentptr,BYTE,copydatasize);//将最后一部分拼接上去

				curchunkpositionblockptr++;
				continue;
			}
		}
		copydatasize=chunksize;
		mcpy(tarcontentptr,soucontentptr,BYTE,copydatasize);//将数据目标chunk拷贝到chunk中

		soucontentptr=soucontentptr+chunksize;//将数据拷贝数据的指针
		curchunkpositionblockptr++;
	}
	set_state_memcpynum_add(chunknum*chunksize);
	return TRUE;
}

int encoder_ENCODERLAYER_update_encode_id(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,UINT64 regionid)
{
	int resTF;
	REGION *regionptr;
	regionptr=profile_region_search_ptr(regionid);
	resTF=encoder_ENCODERLAYER_updata_encode_ptr(chunkpositionblockgroupptr,parityblockgroupptr,regionptr);
	if(resTF==FALSE)
	{
		show_error("encoder","ENCODERLAYER_update_encode_id","the encoder can't calculate");
		return FALSE;
	}
	return TRUE;
}
int encoder_ENCODERLAYER_updata_encode_ptr(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,REGION *regionptr)
{
	int resTF;
	int codetype;
	int maintype;
	int subtype;

	codetype=regionptr->codetype;
	maintype=maintype(codetype);
	subtype=subtype(codetype);
	switch(maintype)
	{
	case Hamming:
		resTF=HAMMING_update_encode_chunkblock(chunkpositionblockgroupptr,parityblockgroupptr);
		if(resTF==FALSE)
		{
			show_error("encoder","ENCODERLAYER_updata_encode_ptr","Hamming encoder can't run");
			return FALSE;
		}
		break;
	case reed_sol:
		resTF=RSCODE_update_encode_chunkblock(chunkpositionblockgroupptr,parityblockgroupptr,subtype);
		if(resTF==FALSE)
		{
			show_error("encoder","ENCODERLAYER_updata_encode_ptr","RSCODE encoder can't run");
			return FALSE;
		}
		break;
	case RAID5:
		resTF=RAID5_update_encode_chunkblock(chunkpositionblockgroupptr,parityblockgroupptr);
		if(resTF==FALSE)
		{
			show_error("encoder","ENCODERLAYER_updata_encode_ptr","RAID5 encoder can't run");
			return FALSE;
		}
		break;
	case RAID6:
		resTF=RAID6_update_encode_chunkblock(chunkpositionblockgroupptr,parityblockgroupptr,subtype);
		if(resTF==FALSE)
		{
			show_error("encoder","ENCODERLAYER_updata_encode_ptr","RAID6 encoder can't run");
			return FALSE;
		}
		break;
	case MSR:
		resTF=MSR_update_encode_chunkblock(chunkpositionblockgroupptr,parityblockgroupptr,subtype);
		if(resTF==FALSE)
		{
			show_error("encoder","ENCODERLAYER_updata_encode_ptr","MSR encoder can't run");
			return FALSE;
		}
		break;
	case MBR:
		resTF=MBR_update_encode_chunkblock(chunkpositionblockgroupptr,parityblockgroupptr,subtype);
		if(resTF==FALSE)
		{
			show_error("encoder","ENCODERLAYER_updata_encode_ptr","MBR encoder can't run");
			return FALSE;
		}
		break;
	}

	return TRUE;
}
//将数据写入相应磁盘和内存位置
int encoder_MAPLAYER_update_map_data_and_pairty(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr)
{
	//将数据同步到相应的位置
	int i,resTF;

	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	int chunknum;
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *chunkptr;
	int paritynum;

	GLOTEMPFREELIST  *tempfreelistptr;

	//当前需要free的列表

	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	chunknum=chunkpositionblockgroupptr->groupsize;

	curchunkpositionblockptr=chunkpositionblockptr;
	for(i=0;i<chunknum;i++)
	{
		
		chunkptr=curchunkpositionblockptr->chunkptr;
		resTF=file_chunk_write_API(chunkptr);
		if(resTF==FALSE)
		{
			show_error("encoder","MAPLAYER_update_map_data_and_pairty","chunk data can't write");
			return FALSE;
		}
		free(chunkptr);
		curchunkpositionblockptr->chunkptr=NULL;
		curchunkpositionblockptr++;
	}

	chunkblockptr=parityblockgroupptr->chunkblockptr;
	paritynum=parityblockgroupptr->groupsize;

	curchunkblockptr=chunkblockptr;
	for(i=0;i<paritynum;i++)
	{
		chunkptr=curchunkblockptr->chunkptr;
		resTF=file_chunk_write_API(chunkptr);
		if(resTF==FALSE)
		{
			show_error("encoder","MAPLAYER_update_map_data_and_pairty","chunk data can't write");
			return FALSE;
		}
		//free(chunkptr);
		curchunkblockptr->chunkptr=NULL;
		curchunkblockptr++;
	}

	//之前的需要读取用于计算的空间也可全数释放
	resTF=profile_tempfree_free();
	if(resTF==FALSE)
	{
		show_error("encoder","MAPLAYER_update_map_data_and_pairty","chunk");
		return FALSE;
	}
	return TRUE;
}

int encoder_filestore_API_update(char *tarpath,BYTESTREAM *updatestream,int offset)
{
	int resTF;
	CODEPARA *codeparamptr;

	CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr;//记录需要更行的块

	CHUNKBLOCKGROUP *parityblockgroupptr;
	CHUNKBLOCK *parityblockptr;

	CHUNKBLOCKGROUP *chunkblockgroupptr;//记录当前文件chunk位置
	CHUNKBLOCK *chunkblockptr;
	CHUNKBLOCK *freechunkblockptr;
	int filechunknum;

	int w;
	int datanum;
	int codenum;
	int paritynum;

	int updatechunknum,updatesize;

	REGION *regionptr;
	STRIPDES *strdesptr;
	int chunksize;

	GLOTEMPFREELIST *tempfreelistptr;

	FILEMETA *filemetaptr;//获取文件元数据
	FILEINF *fileinfptr;
	int filesize;
	
	chunkpositionblockgroupptr=talloc(CHUNKPOSITIONBLOCKGROUP,1);
	if(chunkpositionblockgroupptr==NULL)
	{
		show_error("encoder","filestore_API_update","No memory");
		return FALSE;
	}

	chunkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(chunkblockgroupptr==NULL)
	{
		show_error("encoder","filestore_API_update","No memory");
		return FALSE;
	}

	filemetaptr=systemcom_FILE_create_handle(tarpath);
	if(filemetaptr==NULL)
	{
		show_error("encoder","filestore_API_update","file pointer can't get");
		return FALSE;
	}
	//将文件数据读出
	regionptr=filemetaptr->regionptr;
	strdesptr=regionptr->strdes;
	chunksize=strdesptr->chunksize;

	codeparamptr=regionptr->codepara;
	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	w=codeparamptr->w;

	updatesize=updatestream->bytessize;
	updatechunknum=updatesize/chunksize+2;//最多需要缓冲的块,因为可能跨块
	//printf("codenum is %d",codenum);
	//printf("updatechunknum is %d",updatechunknum);
	parityblockptr=talloc(CHUNKBLOCK,codenum*w);//假设不同的数据分布在不同strip中算上限
	if(parityblockptr==NULL)
	{
		show_error("encoder","filestore_API_update","No memory");
		return FALSE;
	}
	parityblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(parityblockgroupptr==NULL)
	{
		show_error("encoder","filestore_API_update","No memory");
		return FALSE;
	}
	parityblockgroupptr->chunkblockptr=parityblockptr;
	parityblockgroupptr->groupsize=0;//当前记录为0

	tempfreelistptr=get_state_tempfreelist();
	freechunkblockptr=tempfreelistptr->chunkblockptr;
	if(freechunkblockptr!=NULL)//这里不为空释放
	{
		free(freechunkblockptr);
	}
	//生指针空间
	freechunkblockptr=talloc(CHUNKBLOCK,w*(datanum+codenum));
	if(freechunkblockptr==NULL)
	{
		show_error("encoder","filestore_API_update","file pointer can't get");
		return FALSE;
	}
	tempfreelistptr->chunkblockptr=freechunkblockptr;
	tempfreelistptr->tempnum=0;//当前还没有需要需要释放的指针

	//
	fileinfptr=filemetaptr->filechunkinf;
	if(fileinfptr==NULL)
	{
		show_error("encoder","filestore_API_update","chunk information is not exist");
		return FALSE;
	}
	//fileinfptr=filemetaptr->filechunkinf;

	chunkblockptr=fileinfptr->chunklist;
	filechunknum=fileinfptr->chunknum;

	chunkblockgroupptr->chunkblockptr=chunkblockptr;
	chunkblockgroupptr->groupsize=filechunknum;
	//printf("start function\n");
	//第一步将数据建立更行数据块
	resTF=encoder_METALAYER_update_map(chunkpositionblockgroupptr,chunkblockgroupptr,updatestream,offset,regionptr);
	if(resTF==FALSE)
	{
		show_error("encoder","filestore_API_update","chunk data can't write into temp chunk");
		return FALSE;
	}
	//printf("encoder_METALAYER_update_map\n");
	resTF=encoder_ENCODERLAYER_updata_encode_ptr(chunkpositionblockgroupptr,parityblockgroupptr,regionptr);
	if(resTF==FALSE)
	{
		show_error("encoder","filestore_API_update","parity data can't calculate");
		return FALSE;
	}
	//printf("encoder_ENCODERLAYER_updata_encode_ptr\n");
	resTF=encoder_MAPLAYER_update_map_data_and_pairty(chunkpositionblockgroupptr,parityblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("encoder","filestore_API_update","parity data can't calculate");
		return FALSE;
	}
	//printf("encoder_MAPLAYER_update_map_data_and_pairty\n");
	free(chunkpositionblockgroupptr);
	//printf("chunkpositionblockgroupptr\n");
	free(chunkblockgroupptr);
	//printf("chunkblockgroupptr\n");
	free(freechunkblockptr);
	//printf("freechunkblockptr\n");
	free(parityblockgroupptr);
	//printf("parityblockgroupptr\n");
	free(parityblockptr);
	//printf("parityblockptr\n");

	tempfreelistptr->chunkblockptr=NULL;
	tempfreelistptr->tempnum=0;
	return TRUE;
}