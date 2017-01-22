#include "encoder.h"
//meta-layer
//��ȡ�ļ�Ԫ���ݺ���Ӧ�ļ�����
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
	bufferptr=talloc(BYTE,filesize);//�ļ���С�Ļ�����
	if(bufferptr==NULL)
	{
		show_error("encoder","METALAYER_matedata","No mempry");
		return FALSE;
	}
	

	i=0;
	//while(!feof(fp))//û�ж�ȡ��Ͼͼ���
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
	//ԭ������fmeta�����
	//filemetaid=get_state_glofileid();
	//set_state_glofileid_add(1);
	//filemetaptr->FileID=filemetaid;
	//filemetaptr->filesize=(UINT64)filesize;//���ļ���С��ֵ
	
	return TRUE;
}

//���ļ����ݷֽ���Ӧ�Ŀ�
int encoder_METALAYER_split(CHUNKBLOCKGROUP *ckbgroup,BYTESTREAM *filecontent)
{

	//����ǰ�����ݲ�ֳ�Ϊ
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

	chunkptr=chunkblockptr->chunkptr;//��ȡ��ǰchunkָ��
	chunksize=chunkptr->sizenum;//�ó�Ŀ��chunk���ֽ���

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
		//���ڴ濽����ȥ
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
//���ñ��뺯��
//ʹ��ѡ��region���뷽ʽ������Ӧȫ�����ݿ���������������У��
int encoder_ENCODERLAYER_encoder_data_ptr(STRIPBLOCKGROUP *stripblockgroupptr,REGION *regionptr)
{
	int codetype;
	int maintype;
	int subtype,resTF;
	//��ȡ�������
	codetype=regionptr->codetype;
	maintype=maintype(codetype);
	subtype=subtype(codetype);
	//�ҵ���Ӧ�ı������
	switch(maintype)
	{
	//ʹ��Hamming�൱��RAID-2
	case Hamming:
		resTF=HAMMING_calculate_parity(stripblockgroupptr);
		if(resTF==FALSE)
		{
			show_error("encoder","ENCODERLAYER_encoder_data_ptr","HAMMING can't run");
			return FALSE;
		}
		break;
	//reed-solomon����ӿ�
	case reed_sol:
		resTF=RSCODE_calculate_parity(stripblockgroupptr,subtype);
		if(resTF==FALSE)
		{
			show_error("encoder","ENCODERLAYER_encoder_data_ptr","RSCODE can't run");
			return FALSE;
		}
		break;
	//ʹ��RAID-5
	case RAID5:
		resTF=RAID5_calculate_parity(stripblockgroupptr);
		if(resTF==FALSE)
		{
			show_error("encoder","ENCODERLAYER_encoder_data_ptr","RAID5 can't run");
			return FALSE;
		}
		break;
	//ʹ��RAID-6�а���EVENODD����Ҫ
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
//ͨ��regionid�����ݿ���б���
int encoder_ENCODERLAYER_encoder_data_id(STRIPBLOCKGROUP *stripblockgroupptr,UINT64 regionid)
{
	REGIONGROUP *regiongroupptr;
	REGION *regionptr,*curregionptr;
	int i,regiongroupsize,resTF;
	UINT64 currentid;
	//�õ���ǰ��region���
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
//�洢����
//�����ݿ����ָ��λ��
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
//�����ݿ����ָ��λ��+�ļ�����
int encoder_MAPLAYER_map_data_and_file_ptr(STRIPBLOCKGROUP *stripblockgroupptr,FILEMETABLOCKGROUP *filemetablockgroupptr,REGION *regionptr)
{
	//ֻ��Ҫ������
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

	//��ʼ���������ݵĻ�����
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
	//֪������Ҫ�޸ĵĲ���ͬ��˳��
	//��ͬ��Ԫ���ݣ��Ƚ������趨Ϊ��Ȼ��һ��ͬ��

	
	mcpy(dirtystripblockptr,stripblockptr,STRIPBLOCK,stripsize);//�����Ѿ������˿�������

	//������д����̲��ҽ�Ԫ�����趨Ϊ������
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
				if(resTF==FALSE)//��ǰ��Ϊ��
				{
					resTF=profile_chunk_data_haswrited(curchunkptr);
					if(resTF==TRUE)//�Ѿ�д����Ҫͬ��
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
	//�趨�ļ�������
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
	//����ͬ��
	profile_dirtydata_set_data(dirtychunkblockptr,chunknum,//chunk����
										dirtystrsetblockptr,strsetnum,//stripsect����
										dirtystripblockptr,stripsize,//strip����
										dirtyregionblockptr,regionsize,//region����
										dirtyfilemetablockptr,filenum,//file����
										NULL,0,//device����
										NULL,0,//disk����
										NULL,0//user����
										);//�趨ȫ��������
	resTF=profile_dirtydata_sync();//����������ͬ��
	if(resTF==FALSE)
	{
		show_error("encoder","MAPLAYER_map_data_ptr","dirtydata can't sync");
		return FALSE;
	}

	/*chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunksize=chunkblockgroupptr->groupsize;
	//������д�����
	curchunkblockptr=chunkblockptr;
	for(i=0;i<chunksize;i++)
	{
		//��ָ���������д��
		chunkptr=curchunkblockptr->chunkptr;//��ָ��ȡ��
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
//ͨ��ID�����ݷ���ָ��λ��
//int encoder_MAPLAYER_map_data_id(CHUNKBLOCKGROUP *chunkblockgroupptr,STRIPBLOCKGROUP *stripblockgroupptr,UINT64 regionid)
int encoder_MAPLAYER_map_data_id(STRIPBLOCKGROUP *stripblockgroupptr,UINT64 regionid)
{
	//�ҵ�regionid��region��ͬ��
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

//ͬ��������Ԫ����
int encoder_MAPLAYER_map_data_ptr_stripmeta(STRIPBLOCKGROUP *stripblockgroupptr,FILEMETABLOCKGROUP *filemetablockgroupptr,REGION *regionptr)
{
	//ֻ��Ҫ������
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

	//��ʼ���������ݵĻ�����
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
	//֪������Ҫ�޸ĵĲ���ͬ��˳��
	//��ͬ��Ԫ���ݣ��Ƚ������趨Ϊ��Ȼ��һ��ͬ��

	
	mcpy(dirtystripblockptr,stripblockptr,STRIPBLOCK,stripsize);//�����Ѿ������˿�������

	//������д����̲��ҽ�Ԫ�����趨Ϊ������
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
	//�趨�ļ�������
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
	//����ͬ��
	profile_dirtydata_set_data(dirtychunkblockptr,chunknum,//chunk����
										dirtystrsetblockptr,strsetnum,//stripsect����
										dirtystripblockptr,stripsize,//strip����
										dirtyregionblockptr,regionsize,//region����
										dirtyfilemetablockptr,filenum,//file����
										NULL,0,//device����
										NULL,0,//disk����
										NULL,0//user����
										);//�趨ȫ��������
	resTF=profile_dirtydata_sync();//����������ͬ��
	if(resTF==FALSE)
	{
		show_error("encoder","MAPLAYER_map_data_ptr","dirtydata can't ");
		return FALSE;
	}
	return TRUE;
}
//��У�������ݿ�д���ڴ�
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
//ͬ������Ԫ���ݺ����ݿ������Լ���ӦУ��
int encoder_MAPLAYER_map_data_ptr_chunk(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *datablockgroupptr,REGION *regionptr)
{
	//��һ����ȡ
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
//ͬ������Ԫ���ݺ����ݿ������Լ��ļ�
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






//������ú���
//����soupath�Ǳ����ļ�·����tarpath���ļ�ϵͳ·��
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
	//��ȡ����
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
//����BYTESTREAM filecontent�����ļ����ݣ�tarpath���ļ�ϵͳ·��
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

	STRIPBLOCKGROUP *stripblockgroupptr;//���ڼ�¼
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
	int i,resTF,chunknum;//������Ҫ����chunk
	int chunksize;
	//regionָ��
	//��һ������id
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

	//����chkblockgroupptr
	chkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(chkblockgroupptr==NULL)
	{
		show_error("encoder","filestore_API_CONTENT","No memory");
		return FALSE;
	}
	chkblockgroupptr->chunkblockptr=NULL;
	chkblockgroupptr->groupsize=0;

	//����strsetblockgroup
	strsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(strsetblockgroupptr==NULL)
	{
		show_error("encoder","filestore_API_CONTENT","No memory");
		return FALSE;
	}
	strsetblockgroupptr->stripsectblockptr=NULL;
	strsetblockgroupptr->groupsize=0;

	//����stripblockgroup
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

	//��������Ҫ֪����Ҫ��Ҫ���ٸ���
	chunksize=stripdesptr->chunksize;//��ȡ��ǰregion��chunk��С
	filesize=filecontent->bytessize;

	chunknum=calchunknum(filesize,chunksize);
	//��������
	chunkblockptr=talloc(CHUNKBLOCK,chunknum);//������Ҫ��Ϊ��ʱ����ռ䲻�ȶ���˸�Ϊ�̶��ռ�
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

	stripblockptr=talloc(STRIPBLOCK,chunknum);//strip��ൽchunk����������ÿһ��stripһ��chunk
	if(stripblockptr==NULL)
	{
		show_error("encoder","filestore_API_CONTENT","No memory");
		return FALSE;
	}
	stripblockgroupptr->stripblockptr=stripblockptr;

	filemetablockptr=talloc(FILEMETABLOCK,2);//�������ļ��ļ�
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

		//������Ӧ����������
		stripptr=chkpathptr->stripptr;//��ȡ��ǰ����
		//�����ݼ���stripblockgroup
		resTF=profile_stripblockgroup_strip_add(stripblockgroupptr,stripptr);//��stripblockgroupptr�м���һ��strip
		if(resTF==FALSE)
		{
			show_error("encoder","filestore_API_CONTENT","stripptr can't add to stripblockgroup");
			return FALSE;
		}

		strsetptr=chkpathptr->stripsectptr;//��ȡ��ǰstripsect
		//�����ݼ���stripsectblockgroup
		resTF=profile_stripsetblockgroup_stripsect_add(strsetblockgroupptr,strsetptr);;
		if(resTF==FALSE)
		{
			show_error("encoder","filestore_API_CONTENT","stripsectptr can't add to stripblockgroup");
			return FALSE;
		}

		//�õ������chunkָ��
		chunkptr=chkpathptr->chunkptr;
		chunkptr->fmeta=filemetaptr;
		chunkptr->fileid=filemetaptr->FileID;

		resTF=profile_chunkblockgroup_chunk_add(chkblockgroupptr,chunkptr);
		if(resTF==FALSE)
		{
			show_error("encoder","filestore_API_CONTENT","chunkptr can't add to chunkblockgroup");
			return FALSE;
		}
		mcpy(curchunkpathptr,chkpathptr,CHUNKPATH,1);//�������ݿ�����Ŀ���ַ
		curchunkpathptr++;
		//�����ݿ�����Ŀ��λ��
		free(chkpathptr);//��Ȼ����������䵫�ǻ���Ҫ�ͷ�
	}
	//�����ݽ��з�Ƭ
	resTF=encoder_METALAYER_split(chkblockgroupptr,filecontent);
	if(resTF==FALSE)
	{
		show_error("encoder","filestore_API_CONTENT","filecontent can't split");
		return FALSE;
	}
	//ͨ��������������У���
	resTF=encoder_ENCODERLAYER_encoder_data_ptr(stripblockgroupptr,regionptr);
	if(resTF==FALSE)
	{
		show_error("encoder","filestore_API_CONTENT","strip can't encoder");
		return FALSE;
	}
	
	//�����ϱߵĲ��������Ѿ������ݴ洢��ֲ�ʽϵͳ��
	//д���ļ��洢��Ϣ
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
	resTF=profile_region_filemeta_add(regionptr,filemetaptr);//�ļ���Ȼ�Ѿ�����˿��Խ������뵽region��
	if(resTF==FALSE)
	{
		show_error("encoder","filestore_API_CONTENT","file can't add to region");
		return FALSE;
	}
	//�����ݶ�λ����Ӧ�Ŀ���
	//resTF=encoder_MAPLAYER_map_data_ptr(chkblockgroupptr,stripblockgroupptr,regionptr);
	resTF=encoder_MAPLAYER_map_data_and_file_ptr(stripblockgroupptr,filemetablockgroupptr,regionptr);
	if(resTF==FALSE)
	{
		show_error("encoder","filestore_API_CONTENT","strip can't encoder");
		return FALSE;
	}
	//����������global_define��ͬ��
	resTF=profile_globaldefine_sync();
	if(resTF==FALSE)
	{
		show_error("encoder","filestore_API_CONTENT","globaldefine can't sync");
		return FALSE;
	}

	//������ռ��ͷ�
	free(filemetablockgroupptr);
	//������Ҫ����
	//free(filemetablockptr);

	free(chkblockgroupptr);
	//free(chunkblockptr);

	free(stripblockgroupptr);
	//free(stripblockptr);
	free(strsetblockgroupptr);
	
	return TRUE;
}
//�����µĿռ佫���ݷ��䵽�м�
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
	int upfull,downfull;//���¿黹�ǲ����ڱ߽�

	contentptr=updatestream->BYTEcontent;
	updatesize=updatestream->bytessize;

	stripdes=regionptr->strdes;
	//��ȡchunksize
	chunksize=stripdes->chunksize;

	//�ȿ���offset�ǲ��������ڱ߽߱���
	//��Ҫ֪�����½��ϵ
	if((offset%chunksize)==0)
	{
		if(((offset+updatesize)%chunksize)==0)
		{
			//˵������������chunk����
			//�����
			upindex=offset/chunksize;
			downindex=(offset+updatesize)/chunksize;

			upfull=TRUE;
			downfull=TRUE;
		}
		else
		{
			//���е�һ�����ڱ߽��ϣ����治��
			upindex=offset/chunksize;//����ȡ�Ͻ�
			downindex=(offset+updatesize)/chunksize;

			upfull=TRUE;
			downfull=FALSE;
		}
	}
	else
	{
		if(((offset+updatesize)%chunksize)==0)
		{
			//˵�����һ�����ڱ���
			upindex=offset/chunksize;
			downindex=(offset+updatesize)/chunksize;

			upfull=FALSE;
			downfull=TRUE;
		}
		else
		{
			//�����ڱ߽�����
			upindex=offset/chunksize;
			downindex=(offset+updatesize)/chunksize;

			upfull=FALSE;
			downfull=FALSE;
		}
	}
	//����chunk����
	updatechunknum=downindex-upindex+1;//����chunkindex����һ��
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


	//��Ҫ������ƫ����
	if(upfull==FALSE)
	{
		//�ҵ���һ��chunk�����һ��chunk
		startoffset=profile_update_startoffset(chunksize,offset);
		curchunkblockptr=chunkblockptr+upindex;
		firstchunkptr=curchunkblockptr->chunkptr;
	}
	else
	{
		firstchunkptr=NULL;
		startoffset=FALSE;//��ǰû��ƫ����
		firstchunkptr=NULL;
	}

	//��Ҫ������ƫ����
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
	if(updatechunknum==1)//�ȴ���һ���������Ǵ���һ��chunk�����
	{
		
		curchunkpositionblockptr=chunkpositionblockptr;
		curchunkblockptr=chunkblockptr+upindex;//�ҵ���ǰ��
		chunkptr=curchunkblockptr->chunkptr;

		tarchunkptr=talloc(CHUNK,1);
		if(tarchunkptr==NULL)
		{
			show_error("encoder","METALAYER_update_map","No memory");
			return FALSE;
		}

		resTF=matrix_CHUNK_copy_meta(tarchunkptr,chunkptr);//��Ԫ���ݿ�������
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
		
		//�Ƚ�Ԫ���ݽ��п���
		curchunkpositionblockptr=chunkpositionblockptr;
		curchunkblockptr=chunkblockptr+upindex;//��λ��ǰchunkλ��
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

			resTF=matrix_CHUNK_copy_meta(tarchunkptr,chunkptr);//��Ԫ���ݿ�������
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
		//����Ҫ������д���ڲ�
		resTF=encoder_METALAYER_update_data_split(chunkpositionblockgroupptr,//��ǰ����chunk�б�
													firstchunkptr,startoffset,//��һ������chunk�Լ��뿪ͷ����ƫ����
													lastchunkptr,lastoffset,//���һ������chunk�Լ�����chunk���ײ���ƫ����
													updatestream);//���ݵ�ָ��
		if(resTF==FALSE)
		{
			show_error("encoder","METALAYER_update_map","update data chunk can't create");
			return FALSE;
		}
		//printf("several chunk\n");
	}
	//���㵱ǰ����chunk�ھ����е�λ��
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
//����chunkλ������
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
		if(isparity==FALSE)//�������У���
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
					if(curchunkid==souchunkid)//�������id��ͬ˵����һ����
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
//��λchunk�������е�λ��
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
										CHUNK *chunkptr,int startoffset,int lastoffset,//���ݿ�
										BYTESTREAM *bytecontentptr//���ݵ�ָ��
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

	contentptr=bytecontentptr->BYTEcontent;//��ǰ������
	contentsize=bytecontentptr->bytessize;

	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	tarchunkptr=chunkpositionblockptr->chunkptr;//��ǰĿ���

	chunksize=chunkptr->sizenum;
	tarcontentptr=chunkptr->chunkcontent;//������ǰ�����ǲ���Ϊ��
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
	if(soucontentptr==NULL)//˵����ǰ���ݲ����ڴ���Ҫ����
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

	//��ʼ�ֶδ���
	//��һ���ֽ��д���
	if(startoffset!=FALSE)
	{
		//���Ƚ�chunk��ǰ�벿�ֽ��п���
		mcpy(tarcontentptr,soucontentptr,BYTE,startoffset);
	}
	//��Ŀ��ָ���ƶ���Ŀ��λ��
	curtarcontentptr=tarcontentptr+startoffset;
	mcpy(curtarcontentptr,contentptr,BYTE,contentsize);
	
	//�ж�һ�����һ������Ҫ��Ҫ����
	if(lastoffset!=FALSE)
	{
		curtarcontentptr=curtarcontentptr+contentsize;//����ƶ������
		cursoucontentptr=soucontentptr+lastoffset;//�ƶ������
		//����Ҫ������������
		lastcopysize=chunksize-lastoffset;
		//���Կ�����
		mcpy(curtarcontentptr,cursoucontentptr,BYTE,lastcopysize);
	}
	//���ڴ濽������������chunksize
	set_state_memcpynum_add(chunksize);
	/*resTF=matrix_CHUNK_copy_data(tarchunkptr,chunkptr);//������ôд���ǻ�����ϸ��һ��Ч��
	if(resTF==FALSE)
	{
		show_error("encoder","MATELAYER_update_data_chunk","chunk data can't copy");
		return FALSE;
	}*/
	return TRUE;
}

//����һ��
int encoder_METALAYER_update_data_split(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//��ǰ����chunk�б�
												CHUNK *firstchunkptr,int startoffset,//��һ������chunk�Լ��뿪ͷ����ƫ����
												CHUNK *lastchunkptr,int lastoffset,//���һ������chunk�Լ�����chunk���ײ���ƫ����
												BYTESTREAM *bytecontentptr//���ݵ�ָ��
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
	soucontentptr=bytecontentptr->BYTEcontent;//�ȼ��費��Ҫ���е�һ���������
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
		
		if(startoffset!=FALSE)//��ʼ��Ҫ����
		{
			if(i==0)
			{
				//�����һ������
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
					//��������ͷŶ���
					resTF=profile_tempfree_chunk_ptr(firstchunkptr);
					if(resTF==FALSE)
					{
						show_error("encoder","MATELAYER_update_data_chunk","tempfree list can't create");
						return FALSE;
					}
				}

				mcpy(tarcontentptr,soucontentptr,BYTE,startoffset);
			
				soucontentptr=bytecontentptr->BYTEcontent;
				curtarcontentptr=tarcontentptr+startoffset;//����
				copydatasize=chunksize-startoffset;
				mcpy(curtarcontentptr,soucontentptr,BYTE,copydatasize);

				soucontentptr=soucontentptr+copydatasize;//��ָ�����û�ȥ

				curchunkpositionblockptr++;//
				continue;
			}
		}
		if(lastoffset!=FALSE)//�����Ҫ����
		{
			if(i==(chunknum-1))
			{
				//����
				//soucontentptr=bytecontentptr->BYTEcontent;
				mcpy(tarcontentptr,soucontentptr,BYTE,lastoffset);
				//cursoucontentptr=soucontentptr+lastoffset;
				//����ʣ����Ҫ����������
				copydatasize=chunksize-lastoffset;
				soucontentptr=lastchunkptr->chunkcontent;//���һ��chunk
				if(soucontentptr==NULL)
				{
					resTF=FILELAYER_CHUNK_READER_DATA(lastchunkptr);//û���ݶ�����
					if(resTF==FALSE)
					{
						show_error("encoder","METALAYER_update_data_split","chunk data can't read");
						return FALSE;
					}
					soucontentptr=lastchunkptr->chunkcontent;
					//��������ͷŶ���
					resTF=profile_tempfree_chunk_ptr(lastchunkptr);
					if(resTF==FALSE)
					{
						show_error("encoder","MATELAYER_update_data_chunk","tempfree list can't create");
						return FALSE;
					}
				}
				curtarcontentptr=tarcontentptr+lastoffset;
				cursoucontentptr=soucontentptr+lastoffset;
				copydatasize=chunksize-lastoffset;//���㵱ǰ��Ҫ������������
				mcpy(curtarcontentptr,cursoucontentptr,BYTE,copydatasize);//�����һ����ƴ����ȥ

				curchunkpositionblockptr++;
				continue;
			}
		}
		copydatasize=chunksize;
		mcpy(tarcontentptr,soucontentptr,BYTE,copydatasize);//������Ŀ��chunk������chunk��

		soucontentptr=soucontentptr+chunksize;//�����ݿ������ݵ�ָ��
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
//������д����Ӧ���̺��ڴ�λ��
int encoder_MAPLAYER_update_map_data_and_pairty(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr)
{
	//������ͬ������Ӧ��λ��
	int i,resTF;

	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	int chunknum;
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *chunkptr;
	int paritynum;

	GLOTEMPFREELIST  *tempfreelistptr;

	//��ǰ��Ҫfree���б�

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

	//֮ǰ����Ҫ��ȡ���ڼ���Ŀռ�Ҳ��ȫ���ͷ�
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

	CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr;//��¼��Ҫ���еĿ�

	CHUNKBLOCKGROUP *parityblockgroupptr;
	CHUNKBLOCK *parityblockptr;

	CHUNKBLOCKGROUP *chunkblockgroupptr;//��¼��ǰ�ļ�chunkλ��
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

	FILEMETA *filemetaptr;//��ȡ�ļ�Ԫ����
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
	//���ļ����ݶ���
	regionptr=filemetaptr->regionptr;
	strdesptr=regionptr->strdes;
	chunksize=strdesptr->chunksize;

	codeparamptr=regionptr->codepara;
	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	w=codeparamptr->w;

	updatesize=updatestream->bytessize;
	updatechunknum=updatesize/chunksize+2;//�����Ҫ����Ŀ�,��Ϊ���ܿ��
	//printf("codenum is %d",codenum);
	//printf("updatechunknum is %d",updatechunknum);
	parityblockptr=talloc(CHUNKBLOCK,codenum*w);//���費ͬ�����ݷֲ��ڲ�ͬstrip��������
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
	parityblockgroupptr->groupsize=0;//��ǰ��¼Ϊ0

	tempfreelistptr=get_state_tempfreelist();
	freechunkblockptr=tempfreelistptr->chunkblockptr;
	if(freechunkblockptr!=NULL)//���ﲻΪ���ͷ�
	{
		free(freechunkblockptr);
	}
	//��ָ��ռ�
	freechunkblockptr=talloc(CHUNKBLOCK,w*(datanum+codenum));
	if(freechunkblockptr==NULL)
	{
		show_error("encoder","filestore_API_update","file pointer can't get");
		return FALSE;
	}
	tempfreelistptr->chunkblockptr=freechunkblockptr;
	tempfreelistptr->tempnum=0;//��ǰ��û����Ҫ��Ҫ�ͷŵ�ָ��

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
	//��һ�������ݽ����������ݿ�
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