#include "update_opt.h"
int UPDATE_OPT_free_matrix(BITMATRIX *matrixptr)
{
	UINT32 *mat;
	mat=matrixptr->matrix;
	if(mat!=NULL)
	{
		free(mat);
	}
	return TRUE;
}

int UPDATE_OPT_free_schedule(SCHEDULE *schedule)
{
	SCHEDOP *schedlist;
	schedlist=schedule->schedlist;
	if(schedlist!=NULL)
	{
		free(schedlist);
	}
	return TRUE;
}

int UPDATE_OPT_free_bitelementgroup(BITELEMENTGROUP *bitelementgroupptr)
{
	int i,resTF;
	int groupsize;
	BITELEMENT *bitelementptr,*curbitelementptr;
	bitelementptr=bitelementgroupptr->bitelemetgroup;
	groupsize=bitelementgroupptr->groupsize;

	curbitelementptr=bitelementptr;
	for(i=0;i<groupsize;i++)
	{
		resTF=UPDATE_OPT_free_bitelement(curbitelementptr);
		if(resTF==FALSE)
		{
			show_error("UPDATE_OPT","free_bitelementgroup","bitelement can't free");
			return FALSE;
		}
		curbitelementptr++;
	}
	return TRUE;
}
int UPDATE_OPT_free_bitelement(BITELEMENT *bitelementptr)
{
	int resTF;
	BITMATRIX *elementptr;
	SCHEDULE *scheduleptr;
	elementptr=elementptr=bitelementptr->elementptr;
	scheduleptr=bitelementptr->scheduleptr;
	if(elementptr!=NULL)
	{
		resTF=UPDATE_OPT_free_matrix(elementptr);
		if(resTF==FALSE)
		{
			show_error("UPDATE_OPT","free_bitelement","elementptr can't free");
			return FALSE;
		}
		free(elementptr);
	}
	scheduleptr=bitelementptr->scheduleptr;
	if(scheduleptr!=NULL)
	{
		resTF=UPDATE_OPT_free_schedule(scheduleptr);
		if(resTF==FALSE)
		{
			show_error("UPDATE_OPT","free_bitelement","schedule can't free");
			return FALSE;
		}
		free(scheduleptr);
	}
	return TRUE;
}


int UPDATE_OPT_free_updateelementgroup(UPDATEELEMENTGROUP *updateelementgroupptr)
{
	int i,resTF;
	UPDATEELEMENT *updateelementptr,*curupdateelementptr;
	int groupsize;

	updateelementptr=updateelementgroupptr->updategroup;
	groupsize=updateelementgroupptr->groupsize;

	curupdateelementptr=updateelementptr;
	for(i=0;i<groupsize;i++)
	{
		resTF=UPDATE_OPT_free_updateelement(curupdateelementptr);
		if(resTF==FALSE)
		{
			show_error("UPDATE_OPT","free_updateelementgroup","updateelement can't free");
			return FALSE;
		}
		curupdateelementptr++;
	}
	return TRUE;
}
int UPDATE_OPT_free_updateelement(UPDATEELEMENT *updateelementptr)
{
	int resTF;
	BITELEMENT *bitelementptr;
	BITMATRIX *updateIelementptr,*updateIIelementptr;
	SCHEDULE *updateIscheduleptr,*updateIIscheduleptr;
	BYTE *updatecontentptr;
	CHUNK *tempchunkptr;
	bitelementptr=updateelementptr->bitelementptr;
	if(bitelementptr!=NULL)
	{
		resTF=UPDATE_OPT_free_bitelement(bitelementptr);
		if(resTF==FALSE)
		{
			show_error("UPDATE_OPT","free_updateelement","bitelementptr can't free");
			return FALSE;
		}
		free(bitelementptr);
	}
	
	updateIelementptr=updateelementptr->updateIelementptr;
	if(updateIelementptr!=NULL)
	{
		resTF=UPDATE_OPT_free_matrix(updateIelementptr);
		if(resTF==FALSE)
		{
			show_error("UPDATE_OPT","free_updateelement","updateIelementptr can't free");
			return FALSE;
		}
		free(updateIelementptr);
	}
	updateIIelementptr=updateelementptr->updateIIelementptr;
	if(updateIIelementptr!=NULL)
	{
		resTF=UPDATE_OPT_free_matrix(updateIIelementptr);
		if(resTF==FALSE)
		{
			show_error("UPDATE_OPT","free_updateelement","updateIIelementptr can't free");
			return FALSE;
		}
		free(updateIIelementptr);
	}

	tempchunkptr=updateelementptr->tempchunkptr;
	if(tempchunkptr!=NULL)
	{
		updatecontentptr=tempchunkptr->chunkcontent;
		free(updatecontentptr);
		free(tempchunkptr);
	}

	updateIscheduleptr=updateelementptr->updateIscheduleptr;
	if(updateIscheduleptr!=NULL)
	{
		resTF=UPDATE_OPT_free_schedule(updateIscheduleptr);
		if(resTF==FALSE)
		{
			show_error("UPDATE_OPT","free_updateelement","updateIscheduleptr can't free");
			return FALSE;
		}
		free(updateIscheduleptr);
		return TRUE;//两个共享存储区域那么I型有，II型一定没有
	}

	updateIIscheduleptr=updateelementptr->updateIIscheduleptr;
	if(updateIIscheduleptr!=NULL)
	{
		resTF=UPDATE_OPT_free_schedule(updateIIscheduleptr);
		if(resTF==FALSE)
		{
			show_error("UPDATE_OPT","free_updateelement","updateIIscheduleptr can't free");
			return FALSE;
		}
		free(updateIscheduleptr);
	}
	
	return TRUE;
}


int UPDATE_OPT_bitelement_ptr(BITELEMENT *bitelementptr,
									STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
									STRIPSECTBLOCKGROUP *codestrsetblockgroupptr)
{
	int stripsectindex,chunkindex;

	STRIPSECTBLOCK *datastrsetblockptr;
	int datanum;

	STRIPSECTBLOCK *codestrsetblockptr,*curcodestrsetblockptr;
	//int codenum;
	STRIPSECT *strsetptr;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;

	chunkindex=bitelementptr->chunkindex;
	stripsectindex=bitelementptr->stripsectindex;

	datastrsetblockptr=datastrsetblockgroupptr->stripsectblockptr;
	datanum=datastrsetblockgroupptr->groupsize;

	codestrsetblockptr=codestrsetblockgroupptr->stripsectblockptr;
	curcodestrsetblockptr=codestrsetblockptr+stripsectindex-datanum;//计算当前位置

	strsetptr=curcodestrsetblockptr->stripsectptr;
	chunkgroupptr=strsetptr->chunklist;
	chunkptr=chunkgroupptr->ckgroup;
	curchunkptr=chunkptr+chunkindex;
	
	bitelementptr->chunkptr=curchunkptr;
	bitelementptr->chunkid=curchunkptr->ChunkID;

	return TRUE;
}
int UPDATE_OPT_bitelement(BITELEMENT *bitelementptr,
							STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
							STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
							BITMATRIX *matrix,REGION *regionptr)
{
	int resTF;
	int stripsectindex,chunkindex;

	int curindex,index,rowsindex;

	BITMATRIX *bitmatrixptr;

	UINT32 *tarmat;
	//int tarrows,tarcols;

	UINT32 *soumat;
	int sourows,soucols,w;

	STRIPSECTBLOCK *datastrsetblockptr;
	int datanum;

	STRIPSECTBLOCK *codestrsetblockptr;
	int codenum;

	stripsectindex=bitelementptr->stripsectindex;
	chunkindex=bitelementptr->chunkindex;

	bitmatrixptr=bitelementptr->elementptr;
	if(bitmatrixptr==NULL)
	{
		bitmatrixptr=talloc(BITMATRIX,1);
		if(bitmatrixptr==NULL)
		{
			show_error("UPDATE_OPT","bitelement","No memory");
			return FALSE;
		}
		bitmatrixptr->matrix=NULL;
		bitelementptr->elementptr=bitmatrixptr;//赋值回去
	}
	datastrsetblockptr=datastrsetblockgroupptr->stripsectblockptr;
	datanum=datastrsetblockgroupptr->groupsize;

	codestrsetblockptr=codestrsetblockgroupptr->stripsectblockptr;
	codenum=codestrsetblockgroupptr->groupsize;

	soumat=matrix->matrix;
	sourows=matrix->xm;
	soucols=matrix->ym;
	w=matrix->w;


	tarmat=bitmatrixptr->matrix;
	if(tarmat==NULL)
	{
		tarmat=talloc(UINT32,soucols);
		if(tarmat==NULL)
		{
			
			show_error("UPDATE_OPT","bitelement","No memory");
			return FALSE;
		}
		bitmatrixptr->matrix=tarmat;
	}
	bitmatrixptr->xm=soucols;
	bitmatrixptr->ym=NONE;
	bitmatrixptr->w=w;
	//找到对应行啊拷贝过来
	index=w*(stripsectindex-datanum)*soucols;
	rowsindex=chunkindex*soucols;
	curindex=index+rowsindex;

	soumat=soumat+curindex;

	mcpy(tarmat,soumat,UINT32,soucols);//数据拷贝过去

	resTF=UPDATE_OPT_bitelement_ptr(bitelementptr,datastrsetblockgroupptr,codestrsetblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","bitelement","chunk pointer can't found");
		return FALSE;
	}
	return TRUE;
}
int UPDATE_OPT_updateI_II_element(UPDATEELEMENT *updateelementptr,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
											BITMATRIX *matrix,REGION *regionptr)
{
	int i,resTF;
	CHUNKPOSITIONBLOCK *chunkpositionblockptr;
	int chunknum;

	BITELEMENT *bitelementptr;//当前bitelement
	int stripsectindex,chunkindex;

	BITMATRIX *updateImatrixptr;

	UINT32 *updateImat,*curupdateImat;
	
	BITMATRIX *updateIImatrixptr;

	UINT32 *updateIImat,*curupdateIImat;

	UINT32 *mat,*curmat;
	int rows,cols,w;

	//int curindex,rowsindex,colsindex;


	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	updateImatrixptr=updateelementptr->updateIelementptr;
	if(updateImatrixptr==NULL)
	{
		updateImatrixptr=talloc(BITMATRIX,1);
		if(updateImatrixptr==NULL)
		{
			show_error("UPDATE_OPT","updateI_II_element","No memory");
			return FALSE;
		}
		updateImatrixptr->matrix=NULL;
		updateelementptr->updateIelementptr=updateImatrixptr;
	}

	updateIImatrixptr=updateelementptr->updateIIelementptr;
	if(updateIImatrixptr==NULL)
	{
		updateIImatrixptr=talloc(BITMATRIX,1);
		if(updateIImatrixptr==NULL)
		{
			show_error("UPDATE_OPT","updateI_II_element","No memory");
			return FALSE;
		}
		updateIImatrixptr->matrix=NULL;
		updateelementptr->updateIIelementptr=updateIImatrixptr;
	}


	updateImat=updateImatrixptr->matrix;
	if(updateImat==NULL)
	{
		updateImat=talloc(UINT32,cols);
		if(updateImat==NULL)
		{
			show_error("UPDATE_OPT","updateI_II_element","No memory");
			return FALSE;
		}
		updateImatrixptr->matrix=updateImat;
	}
	updateImatrixptr->xm=cols;
	updateImatrixptr->ym=NONE;
	updateImatrixptr->w=w;
	
	updateIImat=updateIImatrixptr->matrix;
	if(updateIImat==NULL)
	{
		updateIImat=talloc(UINT32,cols);
		if(updateIImat==NULL)
		{
			show_error("UPDATE_OPT","updateI_II_element","No memory");
			return FALSE;
		}
		updateIImatrixptr->matrix=updateIImat;
	}
	updateIImatrixptr->xm=cols;
	updateIImatrixptr->ym=NONE;
	updateIImatrixptr->w=w;

	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	chunknum=chunkpositionblockgroupptr->groupsize;

	//调整当前指针
	bzero(updateImat,UINT32,cols);//以防万一
	bzero(updateIImat,UINT32,cols);//以防万一
	curupdateImat=updateImat;
	curupdateIImat=updateIImat;
	curmat=mat;
	for(i=0;i<cols;i++)
	{
		bitelementptr=updateelementptr->bitelementptr;
		stripsectindex=i;
		chunkindex=bitelementptr->chunkindex;
		resTF=profile_search_chunkposition_id(stripsectindex,chunkindex,chunkpositionblockgroupptr);
		if(resTF==PFALSE)
		{
			*curupdateImat=*curmat;
		}
		else
		{
			*curupdateIImat=*curmat;
		}
		curupdateImat++;
		curupdateIImat++;
		curmat++;
	}
	//matrix_print_bitmatrix_oneline(updateImatrixptr);
	//matrix_print_bitmatrix_oneline(updateIImatrixptr);
	return TRUE;
}
int UPDATE_OPT_update_element(UPDATEELEMENT *updateelementptr,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
								STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
								STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
								int *updatelist,BITMATRIX *matrix,
								int stripsectindex,int chunkindex,
								REGION *regionptr)
{
	int resTF;
	CHUNK *chunkptr;
	BITMATRIX *elementptr;
	SCHEDULE *scheduleptr;


	BITELEMENT *bitelementptr;
	BITMATRIX *updateIelementptr;
	BITMATRIX *updateIIelementptr;
	bitelementptr=updateelementptr->bitelementptr;
	if(bitelementptr==NULL)
	{
		bitelementptr=talloc(BITELEMENT,1);
		if(bitelementptr==NULL)
		{
			show_error("UPDATE_OPT","update_element","No memory");
			return FALSE;
		}
		chunkptr=talloc(CHUNK,1);
		if(chunkptr==NULL)
		{
			show_error("UPDATE_OPT","update_element","No memory");
			return FALSE;
		}
		bitelementptr->chunkptr=chunkptr;
		elementptr=talloc(BITMATRIX,1);
		if(chunkptr==NULL)
		{
			show_error("UPDATE_OPT","update_element","No memory");
			return FALSE;
		}
		bitelementptr->elementptr=elementptr;
		scheduleptr=talloc(SCHEDULE,1);
		if(scheduleptr==NULL)
		{
			show_error("UPDATE_OPT","update_element","No memory");
			return FALSE;
		}
		bitelementptr->scheduleptr=NULL;

		bitelementptr->stripsectindex=stripsectindex;
		bitelementptr->chunkindex=chunkindex;
		bitelementptr->istarget=TRUE;
		updateelementptr->bitelementptr=bitelementptr;
	}
	//
	

	updateIelementptr=updateelementptr->updateIelementptr;
	if(updateIelementptr==NULL)
	{
		updateIelementptr=talloc(BITMATRIX,1);
		if(updateIelementptr==NULL)
		{
			show_error("UPDATE_OPT","update_element","No memory");
			return FALSE;
		}
		updateIelementptr->matrix=NULL;
		updateelementptr->updateIelementptr=updateIelementptr;
	}

	updateIIelementptr=updateelementptr->updateIIelementptr;
	if(updateIIelementptr==NULL)
	{
		updateIIelementptr=talloc(BITMATRIX,1);
		if(updateIIelementptr==NULL)
		{
			show_error("UPDATE_OPT","update_element","No memory");
			return FALSE;
		}
		updateIIelementptr->matrix=NULL;
		updateelementptr->updateIIelementptr=updateIIelementptr;
	}

	resTF=UPDATE_OPT_bitelement(bitelementptr,
								datastrsetblockgroupptr,codestrsetblockgroupptr,
								matrix,regionptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","update_element","bit element can't create");
		return FALSE;
	}
	//使用更新两个updateI和updateII的序列
	resTF=UPDATE_OPT_updateI_II_element(updateelementptr,chunkpositionblockgroupptr,matrix,regionptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","update_element","update I and update II element can't create");
		return FALSE;
	}
	return TRUE;
}

int UPDATE_OPT_update_element_group(UPDATEELEMENTGROUP *updategroupptr,
									CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
									STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
									STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
									int *updatelist,
									BITMATRIX *matrix,REGION *regionptr)
{
	int i,j,resTF;
	int chunknum;
	int datanum,codenum;
	CODEPARA *codeparamptr;

	
	BITELEMENT *bitelementptr;

	UPDATEELEMENT *updateelementptr,*curupdateelementptr;
	int updatenum;
	int updateindex;

	UINT32 *mat;
	int rows,cols,w;

	int stripsectindex,chunkindex;

	STRIPDES *strdes;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	strdes=regionptr->strdes;
	codeparamptr=regionptr->codepara;
	codenum=codeparamptr->codenum;
	datanum=codeparamptr->datanum;

	chunknum=strdes->chunknum;

	updateelementptr=updategroupptr->updategroup;
	updatenum=updategroupptr->groupsize;

	updateindex=0;
	curupdateelementptr=updateelementptr;
	for(i=0;i<codenum;i++)
	{
		//第一步
		for(j=0;j<chunknum;j++)
		{
			if(updatelist[updateindex]==TRUE)//当前需要更新
			{
				stripsectindex=i+datanum;//设置一下位置
				chunkindex=j;
				
				bitelementptr=curupdateelementptr->bitelementptr;

				curupdateelementptr->stripsecindex=stripsectindex;
				curupdateelementptr->chunkindex=chunkindex;

				bitelementptr->stripsectindex=stripsectindex;
				bitelementptr->chunkindex=chunkindex;

				resTF=UPDATE_OPT_update_element(curupdateelementptr,chunkpositionblockgroupptr,
												datastrsetblockgroupptr,codestrsetblockgroupptr,
												updatelist,matrix,stripsectindex,chunkindex,regionptr);
				if(resTF==FALSE)
				{
					show_error("UPDATE_OPT","update_element_group","element can't create");
					return FALSE;
				}
				curupdateelementptr++;
			}
			updateindex++;
		}
	}
	return TRUE;
}
int UPDATE_OPT_update_element_group_RAID6(UPDATEELEMENTGROUP *updategroupptr,
											CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
											STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
											STRIPSECT *pparity,STRIPSECT *qparity,
											int *pupdatelist,int *qupdatelist,
											BITMATRIX *matrix,REGION *regionptr)
{
	int resTF;

	UINT32 *mat;
	int rows,cols,w;

	STRIPSECTBLOCKGROUP *codestrsetblockgroupptr;
	STRIPSECTBLOCK *codestrsetblockptr,*curcodestrsetblockptr;
	int codenum;

	int *updatelist,*curupdatelist;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	codenum=2;
	codestrsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(codestrsetblockgroupptr==NULL)
	{
		show_error("UPDATE_OPT","update_element_group_RAID6","No memory");
		return FALSE;
	}
	codestrsetblockptr=talloc(STRIPSECTBLOCK,codenum);
	if(codestrsetblockptr==NULL)
	{
		show_error("UPDATE_OPT","update_element_group_RAID6","No memory");
		return FALSE;
	}
	codestrsetblockgroupptr->stripsectblockptr=codestrsetblockptr;
	codestrsetblockgroupptr->groupsize=codenum;

	curcodestrsetblockptr=codestrsetblockptr;
	curcodestrsetblockptr->stripsectptr=pparity;
	curcodestrsetblockptr->stripsectid=pparity->StripsectID;

	curcodestrsetblockptr=curcodestrsetblockptr+1;

	curcodestrsetblockptr->stripsectptr=qparity;
	curcodestrsetblockptr->stripsectid=qparity->StripsectID;

	//创建updatelist
	updatelist=talloc(int,rows);
	if(updatelist==NULL)
	{
		show_error("UPDATE_OPT","update_element_group_RAID6","No memory");
		return FALSE;
	}
	curupdatelist=updatelist;

	mcpy(curupdatelist,pupdatelist,int,w);

	curupdatelist=curupdatelist+w;

	mcpy(curupdatelist,qupdatelist,int,w);
	
	resTF=UPDATE_OPT_update_element_group(updategroupptr,chunkpositionblockgroupptr,
											datastrsetblockgroupptr,codestrsetblockgroupptr,
											updatelist,matrix,regionptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","update_element_group_RAID6","element group can't update");
		return FALSE;
	}
	free(codestrsetblockgroupptr);
	free(codestrsetblockptr);
	return TRUE;
}
//将disk和memory进行
int UPDATE_OPT_create_memory_disk_readmapmatrix(BITELEMENTGROUP *memorygroupptr,BITELEMENTGROUP *diskgroupptr,
										STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
										BITMATRIX *readmapmatrix,BITMATRIX *matrix,
										int *countnum,REGION *regionptr)
{
	int resTF;
	resTF=UPDATE_OPT_create_memory_disk_index(memorygroupptr,diskgroupptr,readmapmatrix);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","create_memory_disk_readmapmatrix","index can't create");
		return FALSE;
	}
	resTF=UPDATE_OPT_create_memory_disk_ptr(memorygroupptr,diskgroupptr,
									datastrsetblockgroupptr,codestrsetblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","create_memory_disk_readmapmatrix","pointer can't create");
		return FALSE;
	}
	resTF=UPDATE_OPT_create_menory_disk_bitnumber_set(memorygroupptr,diskgroupptr,
												readmapmatrix,matrix,regionptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","create_memory_disk_readmapmatrix","bitnumber can't create");
		return FALSE;
	}
	return TRUE;
}
int UPDATE_OPT_create_memory_disk(BITELEMENTGROUP *memorygroupptr,BITELEMENTGROUP *diskgroupptr,
										STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
										BITMATRIX *readmapmatrix,BITMATRIX *matrix,
										int *countnum,REGION *regionptr)
{
	int resTF;
	//生成memory情况
	resTF=profile_create_memory_map(readmapmatrix,datastrsetblockgroupptr,
									codestrsetblockgroupptr,countnum,regionptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","create_memory_disk"," read map can't create");
		return FALSE;
	}
	resTF=UPDATE_OPT_create_memory_disk_index(memorygroupptr,diskgroupptr,readmapmatrix);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","create_memory_disk","index can't create");
		return FALSE;
	}
	resTF=UPDATE_OPT_create_memory_disk_ptr(memorygroupptr,diskgroupptr,
									datastrsetblockgroupptr,codestrsetblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","create_memory_disk","pointer can't create");
		return FALSE;
	}
	resTF=UPDATE_OPT_create_menory_disk_bitnumber_set(memorygroupptr,diskgroupptr,
												readmapmatrix,matrix,regionptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","create_memory_disk","bitnumber can't create");
		return FALSE;
	}
	return TRUE;
}
int UPDATE_OPT_create_memory_disk_index(BITELEMENTGROUP *memorygroupptr,BITELEMENTGROUP *diskgroupptr,
										BITMATRIX *readmapmatrix)
{
	int i,j,resTF;
	int stripsectnum,chunknum;

	BITELEMENT  *diskelementptr,*curdiskelementptr;
	int disknum;

	BITELEMENT *memoryelementptr,*curmemoryelementptr;
	int memorynum;

	stripsectnum=readmapmatrix->ym;
	chunknum=readmapmatrix->xm;

	memoryelementptr=memorygroupptr->bitelemetgroup;
	memorynum=memorygroupptr->groupsize;

	diskelementptr=diskgroupptr->bitelemetgroup;
	disknum=diskgroupptr->groupsize;

	curmemoryelementptr=memoryelementptr;
	curdiskelementptr=diskelementptr;
	memorynum=0;
	disknum=0;
	for(i=0;i<stripsectnum;i++)
	{
		for(j=0;j<chunknum;j++)
		{
			resTF=profile_memory_map_is_exist(readmapmatrix,i,j);
			if(resTF==TRUE)
			{
				curdiskelementptr->stripsectindex=i;
				curdiskelementptr->chunkindex=j;
				curdiskelementptr++;
				disknum++;
			}
			else
			{
				curmemoryelementptr->stripsectindex=i;
				curmemoryelementptr->chunkindex=j;
				curmemoryelementptr++;
				memorynum++;
			}
		}
	}
	memorygroupptr->groupsize=memorynum;
	diskgroupptr->groupsize=disknum;
	return TRUE;
}
int UPDATE_OPT_create_memory_disk_ptr(BITELEMENTGROUP *memorygroupptr,BITELEMENTGROUP *diskgroupptr,
										STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
										STRIPSECTBLOCKGROUP *codestrsetblockgroupptr)
{
	int i;
	int strsetindex,chunkindex;
	BITELEMENT *diskelementptr,*curdiskelementptr;
	int disknum;

	BITELEMENT *memoryelementptr,*curmemoryelementptr;
	int memorynum;

	STRIPSECTBLOCK *datastrsetblockptr,*curdatastrsetblockptr;
	STRIPSECT *datastrsetptr;
	int datastrsetnum;

	STRIPSECTBLOCK *codestrsetblockptr,*curcodestrsetblockptr;
	STRIPSECT *codestrsetptr;
	int codestrsetnum;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;

	memoryelementptr=memorygroupptr->bitelemetgroup;
	memorynum=memorygroupptr->groupsize;

	diskelementptr=diskgroupptr->bitelemetgroup;
	disknum=diskgroupptr->groupsize;

	datastrsetblockptr=datastrsetblockgroupptr->stripsectblockptr;
	datastrsetnum=datastrsetblockgroupptr->groupsize;

	codestrsetblockptr=codestrsetblockgroupptr->stripsectblockptr;
	codestrsetnum=codestrsetblockgroupptr->groupsize;

	curmemoryelementptr=memoryelementptr;
	curdiskelementptr=diskelementptr;
	for(i=0;i<memorynum;i++)
	{
		strsetindex=curmemoryelementptr->stripsectindex;
		chunkindex=curmemoryelementptr->chunkindex;
		if(strsetindex<datastrsetnum)
		{
			curdatastrsetblockptr=datastrsetblockptr+strsetindex;//找到当前stripsect位置
			datastrsetptr=curdatastrsetblockptr->stripsectptr;

			chunkgroupptr=datastrsetptr->chunklist;
			chunkptr=chunkgroupptr->ckgroup;

			curchunkptr=chunkptr+chunkindex;

			curmemoryelementptr->chunkid=curchunkptr->ChunkID;
			curmemoryelementptr->chunkptr=curchunkptr;
		}
		else
		{
			curcodestrsetblockptr=codestrsetblockptr+strsetindex-datastrsetnum;
			codestrsetptr=curcodestrsetblockptr->stripsectptr;

			chunkgroupptr=codestrsetptr->chunklist;
			chunkptr=chunkgroupptr->ckgroup;

			curchunkptr=chunkptr+chunkindex;

			curmemoryelementptr->chunkid=curchunkptr->ChunkID;
			curmemoryelementptr->chunkptr=curchunkptr;
		}
		curmemoryelementptr++;
	}
	for(i=0;i<disknum;i++)
	{
		strsetindex=curdiskelementptr->stripsectindex;
		chunkindex=curdiskelementptr->chunkindex;
		if(strsetindex<datastrsetnum)
		{
			curdatastrsetblockptr=datastrsetblockptr+strsetindex;
			datastrsetptr=curdatastrsetblockptr->stripsectptr;

			chunkgroupptr=datastrsetptr->chunklist;

			chunkptr=chunkgroupptr->ckgroup;

			curchunkptr=chunkptr+chunkindex;
			curdiskelementptr->chunkptr=curchunkptr;
			curdiskelementptr->chunkid=curchunkptr->ChunkID;
		}
		else
		{
			curcodestrsetblockptr=codestrsetblockptr+strsetindex-datastrsetnum;
			codestrsetptr=curcodestrsetblockptr->stripsectptr;

			chunkgroupptr=codestrsetptr->chunklist;
			chunkptr=chunkgroupptr->ckgroup;

			curchunkptr=chunkptr+chunkindex;

			curdiskelementptr->chunkid=curchunkptr->ChunkID;
			curdiskelementptr->chunkptr=curchunkptr;
		}
		curdiskelementptr++;
	}
	return TRUE;
}
//
int UPDATE_OPT_create_menory_disk_bitnumber_set(BITELEMENTGROUP *memorygroupptr,BITELEMENTGROUP *diskgroupptr,
												BITMATRIX *readmapmatrix,BITMATRIX *matrix,REGION *regionptr)
{
	int i,j,resTF;

	UINT32 *readmat;
	int readrows,readcols,w;

	UINT32 *mat;
	int rows,cols;

	BITMATRIX *curmatrixptr;

	int stripsectindex,chunkindex;

	CODEPARA *codeparamptr;
	int datanum,codenum;

	BITELEMENT *diskelementptr,*curdiskelementptr;
	int disknum;

	BITELEMENT *memoryelementptr,*curmemoryelementptr;
	int memorynum;

	codeparamptr=regionptr->codepara;
	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;

	diskelementptr=diskgroupptr->bitelemetgroup;
	disknum=diskgroupptr->groupsize;

	memoryelementptr=memorygroupptr->bitelemetgroup;
	memorynum=memorygroupptr->groupsize;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	readmat=readmapmatrix->matrix;
	readrows=readmapmatrix->xm;
	readcols=readmapmatrix->ym;
	
	curmemoryelementptr=memoryelementptr;
	curdiskelementptr=diskelementptr;
	for(i=0;i<memorynum;i++)
	{
		stripsectindex=curmemoryelementptr->stripsectindex;
		chunkindex=curmemoryelementptr->chunkindex;
		if(stripsectindex<datanum)
		{
			resTF=profile_bitelement_dataelement(stripsectindex,chunkindex,curmemoryelementptr,matrix,regionptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","create_menory_disk_bitnumber_set","dataelement can't create");
				return FALSE;
			}
		}
		else
		{
			resTF=profile_bitelement_codeelement(stripsectindex,chunkindex,curmemoryelementptr,matrix,regionptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","create_menory_disk_bitnumber_set","dataelement can't create");
				return FALSE;
			}
		}
		curmemoryelementptr++;
	}
	for(i=0;i<disknum;i++)
	{
		stripsectindex=curdiskelementptr->stripsectindex;
		chunkindex=curdiskelementptr->chunkindex;
		if(stripsectindex<datanum)
		{
			resTF=profile_bitelement_dataelement(stripsectindex,chunkindex,curdiskelementptr,matrix,regionptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","create_menory_disk_bitnumber_set","dataelement can't create");
				return FALSE;
			}
		}
		else
		{
			resTF=profile_bitelement_codeelement(stripsectindex,chunkindex,curdiskelementptr,matrix,regionptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","create_menory_disk_bitnumber_set","dataelement can't create");
				return FALSE;
			}
		}
		curdiskelementptr++;
	}
	/*for(i=0;i<readrows;i++)
	{
		for(j=0;j<readcols;j++)
		{
			rowsindex=i*readcols;
			colsindex=j;
			curindex=rowsindex+colsindex;
			if(readmat[curindex]==TRUE)//需要读取
			{
				if(j<cols)
				{
					//当前原句
					curmatrixptr=curdiskelementptr->elementptr;
					if(curmatrixptr==NULL)
					{
						curmatrixptr=talloc(BITMATRIX,1);
						if(curmatrixptr==NULL)
						{
							show_error("UPDATE_OPT","create_menory_disk_bitnumber_set","No memory");
							return FALSE;
						}
						curmatrixptr->matrix=NULL;
						curdiskelementptr->elementptr=curmatrixptr;
					}
					resTF=profile_bitelement_dataelement(i,j,curdiskelementptr,matrix);
					if(resTF==FALSE)
					{
						show_error("UPDATE_OPT","create_menory_disk_bitnumber_set","dataelement can't create");
						return FALSE;
					}
				}
				else
				{
					curmatrixptr=curdiskelementptr->elementptr;
					if(curmatrixptr==NULL)
					{
						curmatrixptr=talloc(BITMATRIX,1);
						if(curmatrixptr==NULL)
						{
							show_error("UPDATE_OPT","create_menory_disk_bitnumber_set","No memory");
							return FALSE;
						}
						curmatrixptr->matrix=NULL;
						curdiskelementptr->elementptr=curmatrixptr;
					}
					resTF=profile_bitelement_codeelement(i,j,curdiskelementptr,matrix);
					if(resTF==FALSE)
					{
						show_error("UPDATE_OPT","create_menory_disk_bitnumber_set","dataelement can't create");
						return FALSE;
					}
				}
				curdiskelementptr->scheduleptr=NULL;
				curdiskelementptr->chunkindex=i;
				curdiskelementptr->stripsectindex=j;
				curdiskelementptr->istarget=FALSE;
				curdiskelementptr++;

			}
			else
			{
				if(j<cols)
				{
					//当前原句
					curmatrixptr=curmemoryelementptr->elementptr;
					if(curmatrixptr==NULL)
					{
						curmatrixptr=talloc(BITMATRIX,1);
						if(curmatrixptr==NULL)
						{
							show_error("UPDATE_OPT","create_menory_disk_bitnumber_set","No memory");
							return FALSE;
						}
						curmatrixptr->matrix=NULL;
						curmemoryelementptr->elementptr=curmatrixptr;
					}
					resTF=profile_bitelement_dataelement(i,j,curdiskelementptr,matrix);
					if(resTF==FALSE)
					{
						show_error("UPDATE_OPT","create_menory_disk_bitnumber_set","dataelement can't create");
						return FALSE;
					}
				}
				else
				{
					//当前原句
					curmatrixptr=curmemoryelementptr->elementptr;
					if(curmatrixptr==NULL)
					{
						curmatrixptr=talloc(BITMATRIX,1);
						if(curmatrixptr==NULL)
						{
							show_error("UPDATE_OPT","create_menory_disk_bitnumber_set","No memory");
							return FALSE;
						}
						curmatrixptr->matrix=NULL;
						curmemoryelementptr->elementptr=curmatrixptr;
					}
					resTF=profile_bitelement_codeelement(i,j,curdiskelementptr,matrix);
					if(resTF==FALSE)
					{
						show_error("UPDATE_OPT","create_menory_disk_bitnumber_set","dataelement can't create");
						return FALSE;
					}
				}
				curmemoryelementptr->scheduleptr=NULL;
				curmemoryelementptr->chunkindex=i;
				curmemoryelementptr->stripsectindex=j;
				curmemoryelementptr->istarget=FALSE;
				curmemoryelementptr++;
			}
			//curdiskelementptr++;这里不能加在这里
			//curmemoryelementptr++;
		}
	}*/
	return TRUE;
}

int UPDATE_OPT_create_scheduling_calculate()
{
	return TRUE;
}

int UPDATE_OPT_create_scheduling(UPDATEELEMENTBLOCKGROUP *schresult,
								UPDATEELEMENTGROUP *updateelementgroupptr,SCHEDULE *schefuling,
								STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
								STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
								BITMATRIX *matrix,BITMATRIX *readmapmatrix,
								REGION *regionptr)
{
	

	

	
	return TRUE;
}
int UPDATE_OPT_create_scheduling_RAID6(UPDATEELEMENTBLOCKGROUP *schresult,
										UPDATEELEMENTGROUP *updateelementgroupptr,SCHEDULE *schefuling,//
										STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
										STRIPSECT *pparity,STRIPSECT *qparity,//
										CHUNKBLOCKGROUP *parityblockgroupptr,
										BITMATRIX *matrix,BITMATRIX *readmapmatrix,
										REGION *regionptr)
{
	int resTF;
	
	STRIPSECTBLOCKGROUP *codestrsetblockgroupptr;
	STRIPSECTBLOCK *codestrsetblockptr;
	int codenum;

	codenum=2;

	codestrsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(codestrsetblockgroupptr==NULL)
	{
		show_error("UPDATE_OPT","create_scheduling_group_RAID6","No memory");
		return FALSE;
	}
	codestrsetblockptr=talloc(STRIPSECTBLOCK,2);
	if(codestrsetblockptr==NULL)
	{
		show_error("UPDATE_OPT","create_scheduling_group_RAID6","No memory");
		return FALSE;
	}

	codestrsetblockptr->stripsectptr=pparity;
	codestrsetblockptr->stripsectid=pparity->StripsectID;

	codestrsetblockptr=codestrsetblockptr+1;

	codestrsetblockptr->stripsectptr=qparity;
	codestrsetblockptr->stripsectid=qparity->StripsectID;
	resTF=UPDATE_OPT_create_scheduling(schresult,updateelementgroupptr,schefuling,
									datastrsetblockgroupptr,codestrsetblockgroupptr,
									matrix,readmapmatrix,
									regionptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","create_scheduling_group_RAID6","scheduling can't create");
		return TRUE;
	}
	return TRUE;
}

int UPDATE_OPT_find_scheduling_memory_closest(UPDATEELEMENT *resultelementptr,
											  BITELEMENTGROUP *memorygroupptr,
											  BITMATRIX *readmapmatrix)
{
	int resTF;
	int i,distance,closedistance,closeupdateI;
	BITELEMENT *memoryelementptr,*curmemoryelementptr;
	int memorynum;
	CHUNK *chunkptr;
	int isupdateI;
	closedistance=MAXVALUE;
	memoryelementptr=memorygroupptr->bitelemetgroup;
	memorynum=memorygroupptr->groupsize;
	
	closeupdateI=PFALSE;

	curmemoryelementptr=memoryelementptr;

	distance=0;//先初始化距离
	chunkptr=profile_updateelement_chunk_ptr(resultelementptr);
	for(i=0;i<memorynum;i++)
	{
		distance=profile_updateelememt_bitelement_distance(resultelementptr,curmemoryelementptr,readmapmatrix);
		if(distance==PFALSE)
		{
			show_error("UPDATE_OPT","find_scheduling_memory_closest","distahce can't calculate");
			return FALSE;
		}
		isupdateI=resultelementptr->isupdateI;
		if(isupdateI==FALSE)
		{
			resTF=profile_chunk_should_read(chunkptr);
			if(resTF==TRUE)
			{
				distance=distance+1;
			}
		}
		if(distance<closedistance)
		{
			closedistance=distance;
			resultelementptr->lastmemoryelement=curmemoryelementptr;
			closeupdateI=isupdateI;
		}
		curmemoryelementptr++;
	}
	resultelementptr->memoryshouldread=closedistance;
	resultelementptr->ismemoryupdateI=closeupdateI;
	return TRUE;
}
int UPDATE_OPT_find_scheduling_disk_closest(UPDATEELEMENT *resultelementptr,
											BITELEMENTGROUP *diskgroupptr,
											BITMATRIX *readmapmatrix)
{
	int resTF;
	int i,distance,closedistance,closeupdateI;
	BITELEMENT *diskelementptr,*curdiskelementptr;
	int isupdateI;
	CHUNK *chunkptr;
	int disknum;

	
	closeupdateI=PFALSE;
	
	closedistance=MAXVALUE;
	diskelementptr=diskgroupptr->bitelemetgroup;
	disknum=diskgroupptr->groupsize;

	curdiskelementptr=diskelementptr;
	chunkptr=profile_updateelement_chunk_ptr(resultelementptr);
	for(i=0;i<disknum;i++)
	{
		
		distance=profile_updateelememt_bitelement_distance(resultelementptr,curdiskelementptr,readmapmatrix);
		if(distance==PFALSE)
		{
			show_error("UPDATE_OPT","scheduling_disk_closest","distance can't calculate");
			return FALSE;
		}
		distance=distance+1;//当前在内存中
		isupdateI=resultelementptr->isupdateI;
		if(isupdateI==FALSE)
		{
			resTF=profile_chunk_should_read(chunkptr);
			if(resTF==TRUE)
			{
				distance=distance+1;
			}
		}
		if(distance<closedistance)
		{
			closedistance=distance;
			//我们大数据记一下
			resultelementptr->lastdiskelement=curdiskelementptr;
			closeupdateI=isupdateI;
		}
		curdiskelementptr++;
	}
	resultelementptr->diskshouldread=closedistance;
	resultelementptr->isdiskupdateI=closeupdateI;
	return TRUE;
}
int UPDATE_OPT_find_scheduling_updateelement_closest(UPDATEELEMENT *resultelementptr,
													UPDATEELEMENTGROUP  *updateelementgroupptr,
													BITMATRIX *readmapmatrix)
{
	int resTF;
	int i,distance,closedistance,closeupdateI,isupdateI;
	UPDATEELEMENT *updateelementptr,*curupdateelementptr;
	int updatenum;
	CHUNK *chunkptr;

	closedistance=MAXVALUE;
	updateelementptr=updateelementgroupptr->updategroup;
	updatenum=updateelementgroupptr->groupsize;

	curupdateelementptr=updateelementptr;
	chunkptr=profile_updateelement_chunk_ptr(resultelementptr);
	for(i=0;i<updatenum;i++)
	{
		distance=profile_updateelement_updatelement_distance(resultelementptr,curupdateelementptr,readmapmatrix);
		if(distance==PFALSE)
		{
			show_error("UPDATE_OPT","find_scheduling_updateelement_closest","distance can't calculate");
			return FALSE;
		}
		isupdateI=resultelementptr->isupdateI;
		if(isupdateI==FALSE)
		{
			resTF=profile_chunk_should_read(chunkptr);
			if(resTF==TRUE)
			{
				distance=distance+1;
			}
		}
		if(distance<closedistance)
		{
			closedistance=distance;
			//我们大数据记一下
			resultelementptr->lastupdateelement=curupdateelementptr;
			closeupdateI=isupdateI;
		}
	}
	resultelementptr->updateshouldread=closedistance;
	resultelementptr->isupdateupdateI=isupdateI;
	return TRUE;
}
int UPDATE_OPT_find_scheduling_closest(UPDATEELEMENT *resultelementptr,
											UPDATEELEMENTGROUP  *updateelementgroupptr,
											BITELEMENTGROUP *memorygroupptr,
											BITELEMENTGROUP *diskgroupptr,
											BITMATRIX *readmapmatrix)
{
	int resTF,minvalue;
	int memoryvalue,diskvalue,updatevalue;
	resTF=UPDATE_OPT_find_scheduling_memory_closest(resultelementptr,memorygroupptr,readmapmatrix);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","find_scheduling_closest","memory closest can't calculate");
		return FALSE;
	}
	resTF=UPDATE_OPT_find_scheduling_disk_closest(resultelementptr,diskgroupptr,readmapmatrix);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","find_scheduling_closest","disk closest can't calculate");
		return FALSE;
	}
	resTF=UPDATE_OPT_find_scheduling_updateelement_closest(resultelementptr,updateelementgroupptr,readmapmatrix);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","find_scheduling_closest","update closest can't calculate");
		return FALSE;
	}
	memoryvalue=resultelementptr->memoryshouldread;
	diskvalue=resultelementptr->diskshouldread;
	updatevalue=resultelementptr->updateshouldread;
	minvalue=MAXVALUE;
	if(memoryvalue<minvalue)
	{
		resultelementptr->lastindex=MEMORYINDEX;
		resultelementptr->isupdateI=resultelementptr->ismemoryupdateI;
		minvalue=memoryvalue;
	}
	if(diskvalue<minvalue)
	{
		resultelementptr->lastindex=DISKINDEX;
		resultelementptr->isupdateI=resultelementptr->isdiskupdateI;
		minvalue=diskvalue;
	}
	if(updatevalue<minvalue)
	{
		resultelementptr->lastindex=UPDATEINDEX;
		resultelementptr->isupdateI=resultelementptr->isupdateupdateI;
		minvalue=updatevalue;
	}
	resultelementptr->shouldreadnum=minvalue;
	return TRUE;
}
UPDATEELEMENT *UPDATE_OPT_find_next_updateelement(UPDATEELEMENTGROUP *updateelementgroupptr,
											BITELEMENTGROUP *memorygroupptr,
											BITELEMENTGROUP *diskgroupptr,
											BITMATRIX *readmapmatrix)
{
	int i,resTF;
	UPDATEELEMENT *updateelement,*curupdateelement;
	int updategroupsize;
	UPDATEELEMENT *minupdateelement;
	int minvalue,shouldreadnum;
	//SCHEDULE *tarschedule;
	int isupdateI;

	minvalue=MAXVALUE;
	minupdateelement=NULL;

	updateelement=updateelementgroupptr->updategroup;
	updategroupsize=updateelementgroupptr->groupsize;

	curupdateelement=updateelement;
	for(i=0;i<updategroupsize;i++)//建立所有
	{
		//处理所有的数据找出最小值
		isupdateI=curupdateelement->isupdateI;
		if(isupdateI==PFALSE)//当前还有没有确定方案
		{
			resTF=UPDATE_OPT_find_scheduling_closest(curupdateelement,updateelementgroupptr,
													memorygroupptr,diskgroupptr,
													readmapmatrix);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","scheduling_group","closest can't create");
				return FALSE;
			}
		
			shouldreadnum=curupdateelement->shouldreadnum;
			if(shouldreadnum<minvalue)
			{
				if(minupdateelement!=NULL)//之前的不是改回去
				{
					minupdateelement->isupdateI=PFALSE;//上面不是改回去
				}
				minvalue=shouldreadnum;
				minupdateelement=curupdateelement;
			}
			else
			{
				curupdateelement->isupdateI=PFALSE;//不是最小的白算了
			}
		}
		
		curupdateelement++;
	}
	return minupdateelement;
}
int UPDATE_OPT_matrix_matrix_create_schedule(BITMATRIX *tarmatrix,BITMATRIX *soumatrix,
											SCHEDULE *sch,
											STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
											STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
											UPDATEELEMENT *updateelement,BITMATRIX *readmapmatrix)
{
	int i,j,resTF;
	//int resTF;
	int lastindex;
	BITELEMENT *lastbitelement;
	UPDATEELEMENT *lastupdateelement;

	UINT32 *soumat,*tarmat;
	int tarnumber,sounumber;
	SCHEDOP *schoplist,*curschoplist;
	int schnum;

	STRIPSECTBLOCK *datastrsetblockptr,*curdatastrsetblockptr;
	STRIPSECT *datastrsetptr;
	int datastrsetgrouppsize;

	int laststripsectindex,lastchunkindex;
	int stripsectindex,chunkindex;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;
	int chunknum;

	UINT64 chunkid;

	int matindex;

	schnum=0;

	schoplist=sch->schedlist;

	tarmat=tarmatrix->matrix;
	tarnumber=tarmatrix->xm;

	soumat=soumatrix->matrix;
	sounumber=soumatrix->xm;

	datastrsetblockptr=datastrsetblockgroupptr->stripsectblockptr;
	datastrsetgrouppsize=datastrsetblockgroupptr->groupsize;
	datastrsetptr=datastrsetblockptr->stripsectptr;

	chunkgroupptr=datastrsetptr->chunklist;
	chunkptr=chunkgroupptr->ckgroup;
	chunknum=chunkgroupptr->groupsize;

	matindex=0;
	if(sounumber!=tarnumber)
	{
		show_error("UPDATE_OPT","matrix_matrix_create_schedule","sounumber!=tarnumber");
		return FALSE;
	}
	
	//将第一个设置为上一个元素
	lastindex=updateelement->lastindex;
	switch(lastindex)
	{
	case DISKINDEX:
		lastbitelement=updateelement->lastdiskelement;
		curchunkptr=lastbitelement->chunkptr;
		laststripsectindex=lastbitelement->stripsectindex;
		lastchunkindex=lastbitelement->chunkindex;
		break;
	case MEMORYINDEX:
		lastbitelement=updateelement->lastmemoryelement;
		curchunkptr=lastbitelement->chunkptr;
		laststripsectindex=lastbitelement->stripsectindex;
		lastchunkindex=lastbitelement->chunkindex;
		break;
	case UPDATEINDEX:
		lastupdateelement=updateelement->lastupdateelement;
		curchunkptr=profile_updateelement_temp_chunk_ptr(lastupdateelement);
		laststripsectindex=lastupdateelement->stripsecindex;
		lastchunkindex=lastupdateelement->chunkindex;
	}
	//设置相应的readmapmatrix
	profile_memory_map_add_element(readmapmatrix,laststripsectindex,lastchunkindex);
	stripsectindex=updateelement->stripsecindex;
	chunkindex=updateelement->chunkindex;
	chunkid=curchunkptr->ChunkID;
	//将当前数据复制并且建立指针
	curschoplist=schoplist;
	matrix_SCHUDOP_set_data(curschoplist,FALSE,laststripsectindex,lastchunkindex,
							stripsectindex,chunkindex,FALSE,curchunkptr,chunkid);
	curschoplist++;
	schnum++;

	curchunkptr=chunkptr;
	curdatastrsetblockptr=datastrsetblockptr;
	
	//生成相应的中间调度序列
	for(i=0;i<datastrsetgrouppsize;i++)
	{
		datastrsetptr=curdatastrsetblockptr->stripsectptr;
		chunkgroupptr=datastrsetptr->chunklist;
		curchunkptr=chunkgroupptr->ckgroup;//重新定位chunkptr
		for(j=0;j<chunknum;j++)
		{
			//计算序列
			resTF=tarmat[matindex]^soumat[matindex];
			if(resTF==TRUE)//当前不同需要调度
			{
				chunkid=curchunkptr->ChunkID;
				matrix_SCHUDOP_set_data(curschoplist,TRUE,i,j,
										stripsectindex,chunkindex,
										FALSE,curchunkptr,chunkid);
				profile_memory_map_add_element(readmapmatrix,i,j);
				curschoplist++;//需要进行计算
				schnum++;
			}
			matindex++;
			curchunkptr++;
		}
		curdatastrsetblockptr++;
		
	}
	sch->size=schnum;
	return TRUE;
}

int UPDATE_OPT_updateelement_bitelement_create_schedule(UPDATEELEMENT *tarupdateelement,
														BITELEMENT *soubitelement,
														STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
														STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
														BITMATRIX *readmapmatrix)
{
	int resTF;
	BITMATRIX *tarmatrix;
	BITMATRIX *soumatrix;
	SCHEDULE *sched;

	int stripsectindex,chunkindex;

	int isupdateI;
	//获取目标模式
	isupdateI=tarupdateelement->isupdateI;
	if(isupdateI==TRUE)//当前数据
	{
		sched=tarupdateelement->updateIscheduleptr;
		tarmatrix=tarupdateelement->updateIelementptr;
	}
	else
	{
		stripsectindex=tarupdateelement->stripsecindex;
		chunkindex=tarupdateelement->chunkindex;
		//方法2需要去读块
		profile_memory_map_add_element(readmapmatrix,stripsectindex,chunkindex);
		sched=tarupdateelement->updateIIscheduleptr;
		tarmatrix=tarupdateelement->updateIIelementptr;
	}
	soumatrix=soubitelement->elementptr;
	
	resTF=UPDATE_OPT_matrix_matrix_create_schedule(tarmatrix,soumatrix,sched,
												datastrsetblockgroupptr,codestrsetblockgroupptr,
												tarupdateelement,readmapmatrix);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","updateelement_bitelement_create_schedule","scheduling can't create");
		return FALSE;
	}
	return TRUE;
}
int UPDATE_OPT_updateelement_updateelement_create_schedule(UPDATEELEMENT *tarupdateelement,
															UPDATEELEMENT *souupdateelement,
															STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
															STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
															BITMATRIX *readmapmatrix)
{
	int resTF;

	BITMATRIX *tarmatrix;
	BITMATRIX *soumatrix;
	SCHEDULE *sched;

	int stripsectindex,chunkindex;
	int isupdateI;
	isupdateI=tarupdateelement->isupdateI;
	if(isupdateI==TRUE)
	{
		sched=tarupdateelement->updateIscheduleptr;
		tarmatrix=tarupdateelement->updateIelementptr;
	}
	else
	{
		stripsectindex=tarupdateelement->stripsecindex;
		chunkindex=tarupdateelement->chunkindex;
		//方法2需要去读块
		profile_memory_map_add_element(readmapmatrix,stripsectindex,chunkindex);
		sched=tarupdateelement->updateIIscheduleptr;
		tarmatrix=tarupdateelement->updateIIelementptr;
	}
	isupdateI=souupdateelement->isupdateI;
	if(isupdateI==TRUE)
	{
		soumatrix=souupdateelement->updateIelementptr;
	}
	else
	{
		soumatrix=souupdateelement->updateIIelementptr;
	}
	
	resTF=UPDATE_OPT_matrix_matrix_create_schedule(tarmatrix,soumatrix,sched,
													datastrsetblockgroupptr,codestrsetblockgroupptr,
													tarupdateelement,readmapmatrix);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","updateelement_updateelement_create_schedule","scheduling can't create");
		return FALSE;
	}
	return TRUE;
}
int UPDATE_OPT_create_scheduling_group(UPDATEELEMENTBLOCKGROUP *schresult,
										UPDATEELEMENTGROUP *updateelementgroupptr,
										STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
										STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
										BITMATRIX *matrix,BITMATRIX *readmapmatrix,int *countnum,
										REGION *regionptr)
{

	//开始创建调度序列
	//
	int i,resTF;
	
	int isupdateI;
	int fromindex;//指明当前的调度是从哪个集合来的

	BITMATRIX *elementptr;
	UINT32 *mat; 

	SCHEDULE *scheduleptr;
	//SCHEDOP *schedopptr;

	UPDATEELEMENTBLOCK *updateelementblockptr,*curupdateelementblockptr;
	int updateblockgroupsize;
	
	UPDATEELEMENT *souupdateelementptr;
	UPDATEELEMENT *updateelement,*curupdateelement;
	int updategroupsize;

	BITELEMENTGROUP *memorygroupptr;
	BITELEMENT *memoryelementptr,*curmemoryelementptr;
	int memorynum;

	BITELEMENTGROUP *diskgroupptr;
	BITELEMENT *diskelementptr,*curdiskelementptr;
	int disknum;

	BITELEMENT *lastdiskelementptr,*lastmemoryelementptr;

	STRIPSECTBLOCK *datastrsetblockptr;
	int datanum;

	STRIPSECTBLOCK *codestrsetblockptr;
	int codenum;

	//UINT32 *mat;
	int rows,cols,w;

	datastrsetblockptr=datastrsetblockgroupptr->stripsectblockptr;
	datanum=datastrsetblockgroupptr->groupsize;

	codestrsetblockptr=codestrsetblockgroupptr->stripsectblockptr;
	codenum=codestrsetblockgroupptr->groupsize;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;
	//上限
	memorynum=(datanum+codenum)*w;
	disknum=(datanum+codenum)*w;

	updateelementblockptr=schresult->updateelementblockptr;
	updateblockgroupsize=schresult->groupsize;

	updateelement=updateelementgroupptr->updategroup;
	updategroupsize=updateelementgroupptr->groupsize;

	diskgroupptr=talloc(BITELEMENTGROUP,1);
	if(diskgroupptr==NULL)
	{
		show_error("UPDATE_OPT","create_scheduling","No memory");
		return FALSE;
	}
	
	diskelementptr=talloc(BITELEMENT,disknum);
	if(diskelementptr==NULL)
	{
		show_error("UPDATE_OPT","create_scheduling","No memory");
		return FALSE;
	}
	diskgroupptr->bitelemetgroup=diskelementptr;
	curdiskelementptr=diskelementptr;
	for(i=0;i<disknum;i++)
	{
		elementptr=talloc(BITMATRIX,1);
		if(elementptr==NULL)
		{
			show_error("UPDATE_OPT","create_scheduling_group","No memory");
			return FALSE;
		}
		mat=talloc(UINT32,cols);
		if(mat==NULL)
		{
			show_error("UPDATE_OPT","create_scheduling_group","No memory");
			return FALSE;
		}
		bzero(mat,UINT32,cols);
		elementptr->matrix=mat;
		elementptr->xm=cols;//只有一行
		elementptr->ym=NONE;
		elementptr->w=w;
		GLOBAL_set_BITELEMENT_data(curdiskelementptr,elementptr,PFALSE,PFALSE,PFALSE,NULL,NULL,PFALSE);
		curdiskelementptr++;
	}

	memorygroupptr=talloc(BITELEMENTGROUP,1);
	if(diskgroupptr==NULL)
	{
		show_error("UPDATE_OPT","create_scheduling","No memory");
		return FALSE;
	}
	
	memoryelementptr=talloc(BITELEMENT,memorynum);
	if(memoryelementptr==NULL)
	{
		show_error("UPDATE_OPT","create_scheduling","No memory");
		return FALSE;
	}
	memorygroupptr->bitelemetgroup=memoryelementptr;
	curmemoryelementptr=memoryelementptr;
	for(i=0;i<memorynum;i++)
	{
		elementptr=talloc(BITMATRIX,1);
		if(elementptr==NULL)
		{
			show_error("UPDATE_OPT","create_scheduling_group","No memory");
			return FALSE;
		}
		mat=talloc(UINT32,cols);
		if(mat==NULL)
		{
			show_error("UPDATE_OPT","create_scheduling_group","No memory");
			return FALSE;
		}
		bzero(mat,UINT32,cols);
		elementptr->matrix=mat;
		elementptr->xm=cols;//只有一行
		elementptr->ym=NONE;
		elementptr->w=w;
		GLOBAL_set_BITELEMENT_data(curmemoryelementptr,elementptr,PFALSE,PFALSE,PFALSE,NULL,NULL,PFALSE);
		curmemoryelementptr++;
	}

	resTF=UPDATE_OPT_create_memory_disk(memorygroupptr,diskgroupptr,
										datastrsetblockgroupptr,codestrsetblockgroupptr,
										readmapmatrix,matrix,
										countnum,regionptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","create_scheduling","memory disk can't create");
		return FALSE;
	}
	disknum=countnum[0];
	diskgroupptr->groupsize=disknum;

	memorynum=countnum[1];
	memorygroupptr->groupsize=memorynum;

	//matrix_print_bitmatrix(readmapmatrix);

	//计算数据初始化
	curupdateelementblockptr=updateelementblockptr;
	for(i=0;i<updateblockgroupsize;i++)
	{
		curupdateelement=UPDATE_OPT_find_next_updateelement(updateelementgroupptr,
															memorygroupptr,diskgroupptr,
															readmapmatrix);
		if(curupdateelement==NULL)
		{
			show_error("UPDATE_OPT","create_scheduling","closest element can't find");
			return FALSE;
		}
		fromindex=curupdateelement->lastindex;
		isupdateI=curupdateelement->isupdateI;
		
		if(isupdateI==TRUE)
		{
			//curupdateelement->updateIscheduleptr=scheduleptr;
			curupdateelement->updateIIscheduleptr=NULL;
		}
		else
		{
			curupdateelement->updateIscheduleptr=NULL;
			//curupdateelement->updateIIscheduleptr=scheduleptr;
		}
		
		
		switch(fromindex)
		{
		case DISKINDEX:
			lastdiskelementptr=curupdateelement->lastdiskelement;
			resTF=UPDATE_OPT_updateelement_bitelement_create_schedule(curupdateelement,lastdiskelementptr,
																		datastrsetblockgroupptr,
																		codestrsetblockgroupptr,
																		readmapmatrix);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","create_scheduling","schedule can't create");
				return FALSE;
			}
			break;
		case MEMORYINDEX:
			lastmemoryelementptr=curupdateelement->lastmemoryelement;
			resTF=UPDATE_OPT_updateelement_bitelement_create_schedule(curupdateelement,lastmemoryelementptr,
																		datastrsetblockgroupptr,
																		codestrsetblockgroupptr,
																		readmapmatrix);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","create_scheduling","schedule can't create");
				return FALSE;
			}
			break;
		case UPDATEINDEX:
			souupdateelementptr=curupdateelement->lastupdateelement;
			resTF=UPDATE_OPT_updateelement_updateelement_create_schedule(curupdateelement,souupdateelementptr,
																			datastrsetblockgroupptr,
																			codestrsetblockgroupptr,
																			readmapmatrix);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","create_scheduling","schedule can't create");
				return FALSE;
			}
			break;
		}
		//matrix_print_bitmatrix(readmapmatrix);
		//我们现在可以赋值了
		resTF=UPDATE_OPT_create_memory_disk_readmapmatrix(memorygroupptr,diskgroupptr,
														datastrsetblockgroupptr,codestrsetblockgroupptr,
														readmapmatrix,matrix,
														countnum,regionptr);
		if(resTF==FALSE)
		{
			show_error("UPDATE_OPT","create_scheduling","disk and memory can't create");
			return FALSE;
		}
		
		curupdateelementblockptr->updateelementptr=curupdateelement;
		//更新数据
		curupdateelementblockptr++;
	}
	memorynum=(datanum+codenum)*w;
	disknum=(datanum+codenum)*w;
	diskgroupptr->groupsize=disknum;
	memorygroupptr->groupsize=memorynum;
	resTF=UPDATE_OPT_free_bitelementgroup(diskgroupptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","create_scheduling_group","diskgroup can't free");
		return FALSE;
	}
	resTF=UPDATE_OPT_free_bitelementgroup(memorygroupptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","create_scheduling_group","memorygroupptr can't free");
		return FALSE;
	}
	free(diskgroupptr);
	free(diskelementptr);
	free(memorygroupptr);
	free(memoryelementptr);
	return TRUE;
}
int UPDATE_OPT_create_scheduling_group_RAID6(UPDATEELEMENTBLOCKGROUP *schresult,
												UPDATEELEMENTGROUP *updateelementgroupptr,
												STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
												STRIPSECT *pparity,STRIPSECT *qparity,
												BITMATRIX *matrix,BITMATRIX *readmapmatrix,int *countnum,
												REGION *regionptr)
{
	int resTF;
	STRIPSECTBLOCKGROUP *codestrsetblockgroupptr;
	STRIPSECTBLOCK *codestrsetblockptr,*curcodestrsetblockptr;
	int codenum;

	//int *updatelist;

	codenum=2;

	codestrsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(codestrsetblockgroupptr==NULL)
	{
		show_error("UPDATE_OPT","create_scheduling_group_RAID6","No memory");
		return FALSE;
	}
	codestrsetblockptr=talloc(STRIPSECTBLOCK,2);
	if(codestrsetblockptr==NULL)
	{
		show_error("UPDATE_OPT","create_scheduling_group_RAID6","No memory");
		return FALSE;
	}
	codestrsetblockgroupptr->stripsectblockptr=codestrsetblockptr;
	codestrsetblockgroupptr->groupsize=2;

	curcodestrsetblockptr=codestrsetblockptr;
	curcodestrsetblockptr->stripsectptr=pparity;
	curcodestrsetblockptr->stripsectid=pparity->StripsectID;

	curcodestrsetblockptr=curcodestrsetblockptr+1;

	curcodestrsetblockptr->stripsectptr=qparity;
	curcodestrsetblockptr->stripsectid=qparity->StripsectID;
	resTF=UPDATE_OPT_create_scheduling_group(schresult,updateelementgroupptr,
											datastrsetblockgroupptr,codestrsetblockgroupptr,
											matrix,readmapmatrix,countnum,
											regionptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","create_scheduling_group_RAID6","scheduling group can't create");
		return FALSE;
	}


	free(codestrsetblockgroupptr);
	free(codestrsetblockptr);
	return TRUE;
}
int UPDATE_OPT_calculate_UPDATEI(SCHEDULE *schedorder,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNK *tarchunkptr,UPDATEELEMENT *updateelementptr)
{
	int i,resTF,isfirst;
	SCHEDOP *schedopptr,*curschedopptr;
	int schudnum;

	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	CHUNK *chunkptr;
	CHUNK *tempchunkptr;
	int chunknum;

	CHUNKBLOCKGROUP *tempchunkblockgroupptr;
	CHUNKBLOCK *tempchunkblockptr;

	schedopptr=schedorder->schedlist;
	schudnum=schedorder->size;

	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	chunknum=chunkpositionblockgroupptr->groupsize;

	curchunkpositionblockptr=chunkpositionblockptr;
	curschedopptr=schedopptr;

	tempchunkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(tempchunkblockgroupptr==NULL)
	{
		show_error("UPDATE_OPT","calculate_UPDATEI","No memory");
		return FALSE;
	}

	tempchunkblockptr=talloc(CHUNKBLOCK,schudnum);
	if(tempchunkblockptr==NULL)
	{
		show_error("UPDATE_OPT","calculate_UPDATEI","No memory");
		return FALSE;
	}
	tempchunkblockgroupptr->chunkblockptr=tempchunkblockptr;
	tempchunkblockgroupptr->groupsize=0;
	tempchunkptr=profile_updateelement_temp_chunk_ptr(updateelementptr);

	isfirst=TRUE;
	tempchunkptr=profile_updateelement_temp_chunk_ptr(updateelementptr);
	for(i=0;i<schudnum;i++)
	{
		chunkptr=curschedopptr->tarchunkptr;
		resTF=profile_chunk_data_isfree(chunkptr);
		if(resTF==TRUE)
		{
			resTF=profile_chunk_data_read(chunkptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","calculate_UPDATEI","chunk data can't read");
				return FALSE;
			}
			
			resTF=profile_chunkblockgroup_chunk_add(tempchunkblockgroupptr,chunkptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","calculate_UPDATEI","chunk data can't add to temp chunk list");
				return FALSE;
			}
		}
		if(isfirst==TRUE)
		{
			resTF=matrix_CHUNK_copy_data(tarchunkptr,chunkptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","calculate_UPDATEI","chunk data can't copy");
				return FALSE;
			}
			resTF=matrix_CHUNK_copy_data(tempchunkptr,chunkptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","calculate_UPDATEI","chunk data can't copy");
				return FALSE;
			}
			isfirst=FALSE;
		}
		else
		{
			resTF=matrix_CHUNK_add_data(tarchunkptr,chunkptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","calculate_UPDATEI","chunk data can't add");
				return FALSE;
			}
			resTF=matrix_CHUNK_add_data(tempchunkptr,chunkptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","calculate_UPDATEI","chunk data can't add");
				return FALSE;
			}
		}
		curschedopptr++;
	}
	for(i=0;i<chunknum;i++)
	{
		chunkptr=curchunkpositionblockptr->chunkptr;
		if(isfirst==TRUE)
		{
			resTF=matrix_CHUNK_copy_data(tarchunkptr,chunkptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","calculate_UPDATEI","chunk data can copy");
				return FALSE;
			}
			isfirst=FALSE;
		}
		else
		{
			resTF=matrix_CHUNK_add_data(tarchunkptr,chunkptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","calculate_UPDATEI","chunk data can add");
				return FALSE;
			}
		}
		curchunkpositionblockptr++;
	}

	//resTF=profile_free_chunkblockgroup_data(tempchunkblockgroupptr);//chunk加入chunkblockgroup
	resTF=profile_tempfree_chunkblock_ptr(tempchunkblockgroupptr);//将chunkblockgroup加入
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","calculate_UPDATEI","chunk data can't free");
		return FALSE;
	}
	free(tempchunkblockgroupptr);
	free(tempchunkblockptr);
	return TRUE;
}
int UPDATE_OPT_calculate_UPDATEII(SCHEDULE *schedorder,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNK *tarchunkptr,UPDATEELEMENT *updateelementptr)
{
	int i,resTF;
	int isfirst;
	int chunksize;

	SCHEDOP *schudopptr,*curschudopptr;
	int schednum;

	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	CHUNK *chunkptr;
	int chunknum;

	CHUNK *souchunkptr;//生成目标模式块
	//int isfirst;
	
	CHUNKBLOCKGROUP *tempchunkblockgroupptr;
	CHUNKBLOCK *tempchunkblockptr;

	CHUNK *tempchunkptr;

	chunksize=tarchunkptr->sizenum;

	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	chunknum=chunkpositionblockgroupptr->groupsize;
	
	schudopptr=schedorder->schedlist;
	schednum=schedorder->size;

	tempchunkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(tempchunkblockgroupptr==NULL)
	{
		show_error("UPDATE_OPT","calculate_UPDATEII","No memory");
		return FALSE;
	}

	tempchunkblockptr=talloc(CHUNKBLOCK,schednum);
	if(tempchunkblockptr==NULL)
	{
		show_error("UPDATE_OPT","calculate_UPDATEII","No memory");
		return FALSE;
	}
	tempchunkblockgroupptr->chunkblockptr=tempchunkblockptr;
	tempchunkblockgroupptr->groupsize=0;
	//需要目标快
	souchunkptr=talloc(CHUNK,1);//生成目标块
	if(souchunkptr==NULL)
	{
		show_error("UPDATE_OPT","calculate_UPDATEII","No memoey");
		return FALSE;
	}
	souchunkptr->sizenum=chunksize;
	resTF=profile_chunk_create_empty_data(souchunkptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","calculate_UPDATEII","chunk can't create");
		return FALSE;
	}
	isfirst=TRUE;

	curchunkpositionblockptr=chunkpositionblockptr;
	curschudopptr=schudopptr;
	//这里至少有一个生成souchunkptr集需要擦除的数据块
	for(i=0;i<schednum;i++)
	{
		chunkptr=curschudopptr->tarchunkptr;
		resTF=profile_chunk_data_isfree(chunkptr);
		if(resTF==TRUE)
		{
			resTF=profile_chunk_data_read(chunkptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","calculate_UPDATEII","chunk data can't read");
				return FALSE;
			}
			resTF=profile_chunkblockgroup_chunk_add(tempchunkblockgroupptr,chunkptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","calculate_UPDATEII","chunk data can't add to temp chunk list");
				return FALSE;
			}
		}
		if(isfirst==TRUE)
		{
			resTF=matrix_CHUNK_copy_data(souchunkptr,chunkptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","calculate_UPDATEII","chunk data can't copy");
				return FALSE;
			}
			isfirst=FALSE;
		}
		else
		{
			resTF=matrix_CHUNK_add_data(souchunkptr,chunkptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","calculate_UPDATEII","chunk data can't add");
				return FALSE;
			}
		}
		curschudopptr++;
	}
	//将缓冲指针取出
	tempchunkptr=profile_updateelement_temp_chunk_ptr(updateelementptr);
	resTF=matrix_CHUNK_copy_data(tempchunkptr,souchunkptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","calculate_UPDATEII","chunk data can't copy");
		return FALSE;
	}
	//将数据读出
	resTF=profile_chunk_data_read(tarchunkptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","calculate_UPDATEII","");
		return FALSE;
	}
	resTF=matrix_CHUNK_add_data(tarchunkptr,souchunkptr);//将原数据抹掉
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","calculate_UPDATEII","chunk data can't add");
		return FALSE;
	}
	//将数据全部加上
	for(i=0;i<chunknum;i++)
	{
		souchunkptr=curchunkpositionblockptr->chunkptr;
		resTF=matrix_CHUNK_add_data(tarchunkptr,souchunkptr);
		if(resTF==FALSE)
		{
			show_error("UPDATE_OPT","calculate_UPDATEII","chunk data can't add");
			return FALSE;
		}
		curchunkpositionblockptr++;
	}
	//resTF=profile_free_chunkblockgroup_data(tempchunkblockgroupptr);//chunk加入chunkblockgroup
	resTF=profile_tempfree_chunkblock_ptr(tempchunkblockgroupptr);//将chunkblockgroup加入
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","calculate_UPDATEII","chunk data can't free");
		return FALSE;
	}
	free(tempchunkblockgroupptr);
	free(tempchunkblockptr);
	return TRUE;
}
//根据当前的数据进行计算
int UPDATE_OPT_calculate_target_chunk(UPDATEELEMENTBLOCKGROUP *updateelementblockgroupptr,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr)
{
	int i,resTF;
	int isupdateI;

	BITELEMENT *bitelementptr;
	CHUNK *tarchunkptr;

	SCHEDULE *schedorder;

	UPDATEELEMENTBLOCK *updateelementblockptr,*curupdateelementblockptr;
	UPDATEELEMENT *updateelementptr;
	int updatenum;

	updateelementblockptr=updateelementblockgroupptr->updateelementblockptr;
	updatenum=updateelementblockgroupptr->groupsize;

	curupdateelementblockptr=updateelementblockptr;
	for(i=0;i<updatenum;i++)
	{
		updateelementptr=curupdateelementblockptr->updateelementptr;
		isupdateI=updateelementptr->isupdateI;//获取签署
		bitelementptr=updateelementptr->bitelementptr;
		tarchunkptr=bitelementptr->chunkptr;
		
		if(isupdateI==TRUE)
		{
			schedorder=updateelementptr->updateIscheduleptr;//现将调度序列赋值
			resTF=UPDATE_OPT_calculate_UPDATEI(schedorder,chunkpositionblockgroupptr,tarchunkptr,updateelementptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","calculate_target_chunk","update I can't calculate");
				return FALSE;
			}
		}
		else
		{
			schedorder=updateelementptr->updateIIscheduleptr;//现将调度序列赋值
			resTF=UPDATE_OPT_calculate_UPDATEII(schedorder,chunkpositionblockgroupptr,tarchunkptr,updateelementptr);
			if(resTF==FALSE)
			{
				show_error("UPDATE_OPT","calculate_target_chunk","update II can't calculate");
				return FALSE;
			}
		}
		curupdateelementblockptr++;
	}
	return TRUE;
}
//根据当前的数据进行计算
int UPDATE_OPT_calculate_target_chunk_RAID6(UPDATEELEMENTBLOCKGROUP *updateelementblockgroupptr,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr)
{
	int resTF;
	resTF=UPDATE_OPT_calculate_target_chunk(updateelementblockgroupptr,chunkpositionblockgroupptr);
	if(resTF==FALSE)
	{
		show_error(" UPDATE_OPT","calculate_target_chunk_RAID6","");
		return FALSE;
	}
	return TRUE;
}

int UPDATE_OPT_update_scheduling(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
									STRIP *stripptr,CHUNKBLOCKGROUP *parityblockgroupptr,
									BITMATRIX *matrix)
{
	int i,resTF;

	CHUNK *curchunkptr;

	UINT32 *mat;
	int rows,cols,w;

	REGION *regionptr;
	CODEPARA *codeparamptr;

	CHUNKBLOCK *parityblockptr,*curparityblockptr;

	int *updatelist;
	int updatenum;
	UPDATEELEMENTGROUP *updateelementgroupptr;
	UPDATEELEMENT *updateelementptr,*curupdateelemenptr;

	UPDATEELEMENTBLOCKGROUP *updateelementblockgroupptr;
	UPDATEELEMENTBLOCK *updateelementblockptr;

	STRIPSECTBLOCKGROUP *datastrsetblockgroupptr;
	STRIPSECTBLOCK *datastrsetblockptr;
	int datanum;

	STRIPSECTBLOCKGROUP *codestrsetblockgroupptr;
	STRIPSECTBLOCK *codestrsetblockptr;
	int codenum;

	BITMATRIX *readmatrix;
	int *countnum;

	

	regionptr=stripptr->regionptr;
	codeparamptr=regionptr->codepara;

	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;

	//获取矩阵参数
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	parityblockptr=parityblockgroupptr->chunkblockptr;

	readmatrix=talloc(BITMATRIX,1);
	if(readmatrix==NULL)
	{
		show_error("UPDATE_OPT","update_scheduling","No memory");
		return FALSE;
	}
	readmatrix->matrix=NULL;

	countnum=talloc(int,2);
	if(countnum==NULL)
	{
		show_error("UPDATE_OPT","update_scheduling","No memory");
		return FALSE;
	}

	datastrsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(datastrsetblockgroupptr==NULL)
	{
		show_error("UPDATE_OPT","update_scheduling","No memory");
		return FALSE;
	}

	datastrsetblockptr=talloc(STRIPSECTBLOCK,datanum);
	if(datastrsetblockptr==NULL)
	{
		show_error("UPDATE_OPT","update_scheduling","No memory");
		return FALSE;
	}
	datastrsetblockgroupptr->stripsectblockptr=datastrsetblockptr;
	datastrsetblockgroupptr->groupsize=datanum;


	codestrsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(codestrsetblockgroupptr==NULL)
	{
		show_error("UPDATE_OPT","update_scheduling","No memory");
		return FALSE;
	}
	
	codestrsetblockptr=talloc(STRIPSECTBLOCK,codenum);
	if(codestrsetblockptr==NULL)
	{
		show_error("UPDATE_OPT","update_scheduling","No memory");
		return FALSE;
	}
	codestrsetblockgroupptr->stripsectblockptr=codestrsetblockptr;
	codestrsetblockgroupptr->groupsize=codenum;

	updatenum=codenum*w;

	updatelist=talloc(int,updatenum);
	if(updatelist==NULL)
	{
		show_error("UPDATE_OPT","update_scheduling","No memory");
		return FALSE;
	}
	updateelementgroupptr=talloc(UPDATEELEMENTGROUP,1);
	if(updateelementgroupptr==NULL)
	{
		show_error("UPDATE_OPT","update_scheduling","No memory");
		return FALSE;
	}

	updateelementptr=talloc(UPDATEELEMENT,updatenum);
	if(updateelementptr==NULL)
	{
		show_error("UPDATE_OPT","update_scheduling","No memory");
		return FALSE;
	}
	updateelementgroupptr->updategroup=updateelementptr;
	updateelementgroupptr->groupsize=0;

	updateelementblockgroupptr=talloc(UPDATEELEMENTBLOCKGROUP,1);
	if(updateelementblockgroupptr==NULL)
	{
		show_error("UPDATE_OPT","update_scheduling","No memory");
		return FALSE;
	}
	updateelementblockptr=talloc(UPDATEELEMENTBLOCK,updatenum);
	if(updateelementblockptr==NULL)
	{
		show_error("UPDATE_OPT","update_scheduling","No memory");
		return FALSE;
	}
	updateelementblockgroupptr->updateelementblockptr=updateelementblockptr;
	updateelementblockgroupptr->groupsize=0;


	resTF=matrix_update_bitmatrix_parity_chunklist(updatelist,chunkpositionblockgroupptr,matrix,updatenum);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","update_scheduling","updatelist can't create");
		return FALSE;
	}

	resTF=profile_strip_into_stripsect_ptr(datastrsetblockgroupptr,codestrsetblockgroupptr,stripptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","update_scheduling","strip can't divide into stripsect");
		return FALSE;
	}
	resTF=UPDATE_OPT_update_element_group(updateelementgroupptr,
											chunkpositionblockgroupptr,
											datastrsetblockgroupptr,codestrsetblockgroupptr,
											updatelist,matrix,regionptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","update_scheduling","scheduling element can't create");
		return TRUE;
	}
	curparityblockptr=parityblockptr;

	updateelementptr=updateelementgroupptr->updategroup;
	updatenum=updateelementgroupptr->groupsize;

	curupdateelemenptr=updateelementptr;
	for(i=0;i<updatenum;i++)
	{
		curchunkptr=profile_updateelement_chunk_ptr(curupdateelemenptr);
		curparityblockptr->chunkid=curchunkptr->ChunkID;
		curparityblockptr->chunkptr=curchunkptr;
		curparityblockptr++;
		curupdateelemenptr++;
	}
	parityblockgroupptr->groupsize=updatenum;
	//生成调度序列填写信息
	resTF=UPDATE_OPT_create_scheduling_group(updateelementblockgroupptr,updateelementgroupptr,
											datastrsetblockgroupptr,codestrsetblockgroupptr,
											matrix,readmatrix,countnum,
											regionptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","update_scheduling","scheduling can't create");
		return FALSE;
	}
	resTF=UPDATE_OPT_calculate_target_chunk(updateelementblockgroupptr,chunkpositionblockgroupptr,updateelementptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","update_scheduling","update chunk can't create");
		return FALSE;
	}
	free(datastrsetblockgroupptr);
	free(datastrsetblockptr);

	free(codestrsetblockgroupptr);
	free(codestrsetblockptr);

	free(updatelist);

	free(updateelementgroupptr);
	free(updateelementptr);

	free(readmatrix);
	free(countnum);

	return TRUE;
}
int UPDATE_OPT_update_scheduling_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//
										STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,//
										CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix)
{
	int i,resTF;
	
	UINT32 *mat;
	int rows,cols,w;

	int stripsectindex,chunkindex;

	int pupdatenum;
	int qupdatenum;
	int totupdatenum;

	STRIPDES *strdes;
	CHUNK *curchunkptr;

	BITELEMENT *bitelementptr;
	UPDATEELEMENTGROUP *updateelementgroupptr;
	UPDATEELEMENT *updateelementptr,*curupdateelementptr;
	int updatenum;

	UPDATEELEMENTBLOCKGROUP *updateelementblockgroupptr;
	UPDATEELEMENTBLOCK *updateelementblockptr;

	REGION *regionptr;
	int *pupdatelist,*qupdatelist;

	BITMATRIX *readmatrix;
	int *countnum;

	BITMATRIX *elementptr,*updateIelementptr,*updateIIelementptr;
	SCHEDULE *scheduleptr;
	SCHEDOP *schedopptr;

	CHUNKBLOCK *parityblockptr,*curparityblockptr;

	CHUNK *tempchunkptr;
	int chunksize;
	BYTE *contentptr;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	regionptr=pparity->regionptr;

	strdes=regionptr->strdes;

	chunksize=strdes->chunksize;

	parityblockptr=parityblockgroupptr->chunkblockptr;

	readmatrix=talloc(BITMATRIX,1);
	if(readmatrix==NULL)
	{
		show_error("UPDATE_OPT","update_scheduling","No memory");
		return FALSE;
	}
	readmatrix->matrix=NULL;

	countnum=talloc(int,2);
	if(countnum==NULL)
	{
		show_error("UPDATE_OPT","update_scheduling","No memory");
		return FALSE;
	}

	pupdatelist=talloc(int,w);
	if(pupdatelist==NULL)
	{
		show_error("UPDATE_OPT","update_scheduling","No memory");
		return FALSE;
	}
	bzero(pupdatelist,int,w);
	qupdatelist=talloc(int,w);
	if(qupdatelist==NULL)
	{
		show_error("UPDATE_OPT","update_scheduling","No memory");
		return FALSE;
	}
	bzero(qupdatelist,int,w);
	updateelementgroupptr=talloc(UPDATEELEMENTGROUP,1);
	if(updateelementgroupptr==NULL)
	{
		show_error("UPDATE","OPT_update_scheduling_RAID6","No memory");
		return FALSE;
	}

	updateelementptr=talloc(UPDATEELEMENT,2*w);
	if(updateelementgroupptr==NULL)
	{
		show_error("UPDATE","OPT_update_scheduling_RAID6","No memory");
		return FALSE;
	}
	updateelementgroupptr->updategroup=updateelementptr;
	//开空间

	updateelementblockgroupptr=talloc(UPDATEELEMENTBLOCKGROUP,1);
	if(updateelementblockgroupptr==NULL)
	{
		show_error("UPDATE","OPT_update_scheduling_RAID6","No memory");
		return FALSE;
	}
	updateelementblockptr=talloc(UPDATEELEMENTBLOCK,2*w);
	if(updateelementblockptr==NULL)
	{
		show_error("UPDATE","OPT_update_scheduling_RAID6","No memory");
		return FALSE;
	}
	updateelementblockgroupptr->updateelementblockptr=updateelementblockptr;
	
	curupdateelementptr=updateelementptr;
	//统统设为空防止野指针
	for(i=0;i<2*w;i++)
	{
		stripsectindex=PFALSE;
		chunkindex=PFALSE;
		bitelementptr=talloc(BITELEMENT,1);
		if(bitelementptr==NULL)
		{
			show_error("UPDATE_OPT","update_element_group","No memory");
			return FALSE;
		}
		elementptr=talloc(BITMATRIX,1);
		if(elementptr==NULL)
		{
			show_error("UPDATE_OPT","update_element_group","No memory");
			return FALSE;
		}
		mat=talloc(UINT32,cols);
		if(mat==NULL)
		{
			show_error("UPDATE_OPT","update_element_group","No memory");
			return FALSE;
		}
		bzero(mat,UINT32,cols);
		elementptr->matrix=mat;
		elementptr->xm=cols;
		elementptr->ym=NONE;
		elementptr->w=w;
		scheduleptr=talloc(SCHEDULE,1);
		if(scheduleptr==NULL)
		{
			show_error("UPDATE_OPT","update_element_group","No memory");
			return FALSE;
		}
		schedopptr=talloc(SCHEDOP,cols);
		if(schedopptr==NULL)
		{
			show_error("UPDATE_OPT","update_element_group","No memory");
			return FALSE;
		}
		GLOBAL_set_SCHEDULE_data(scheduleptr,schedopptr,cols,w);
		GLOBAL_set_BITELEMENT_data(bitelementptr,elementptr,stripsectindex,chunkindex,TRUE,scheduleptr,NULL,NONE);
		//开空间
		updateIelementptr=talloc(BITMATRIX,1);
		if(updateIelementptr==NULL)
		{
			show_error("UPDATE_OPT","update_element_group","No memory");
			return FALSE;
		}
		mat=talloc(UINT32,cols);
		if(mat==NULL)
		{
			show_error("UPDATE_OPT","update_element_group","No memory");
			return FALSE;
		}
		bzero(mat,UINT32,cols);
		updateIelementptr->matrix=mat;
		updateIelementptr->xm=cols;
		updateIelementptr->ym=NONE;
		updateIelementptr->w=w;

		updateIIelementptr=talloc(BITMATRIX,1);
		if(updateIIelementptr==NULL)
		{
			show_error("UPDATE_OPT","update_element_group","No memory");
			return FALSE;
		}
		mat=talloc(UINT32,cols);
		if(mat==NULL)
		{
			show_error("UPDATE_OPT","update_element_group","No memory");
			return FALSE;
		}
		bzero(mat,UINT32,cols);
		updateIIelementptr->matrix=mat;
		updateIIelementptr->xm=cols;
		updateIIelementptr->ym=NONE;
		updateIIelementptr->w=w;

		scheduleptr=talloc(SCHEDULE,1);
		if(scheduleptr==NULL)
		{
			show_error("UPDATE_OPT","create_scheduling","No memory");
			return FALSE;
		}
		schedopptr=talloc(SCHEDOP,rows);
		if(schedopptr==NULL)
		{
			show_error("UPDATE_OPT","create_scheduling","No memory");
			return FALSE;
		}
		scheduleptr->schedlist=schedopptr;
		scheduleptr->size=NONE;
		scheduleptr->w=w;

		contentptr=talloc(BYTE,chunksize);
		if(contentptr==NULL)
		{
			show_error("UPDATE_OPT","create_scheduling","No memory");
			return FALSE;
		}
		tempchunkptr=talloc(CHUNK,1);
		if(tempchunkptr==NULL)
		{
			show_error("UPDATE_OPT","create_scheduling","No memory");
			return FALSE;
		}
		tempchunkptr->chunkcontent=contentptr;
		tempchunkptr->sizenum=chunksize;
		GLOBAL_set_UPDATEELEMENT_data(curupdateelementptr,bitelementptr,
									scheduleptr,updateIelementptr,
									scheduleptr,updateIIelementptr,
									stripsectindex,chunkindex,
									PFALSE,tempchunkptr,
									PFALSE,PFALSE,
									NULL,PFALSE,PFALSE,
									NULL,PFALSE,PFALSE,
									NULL,PFALSE,PFALSE);
		curupdateelementptr++;
	}
	//开始生成空间主要原因如果内内部生成本函数没有权利释放

	//生成读取矩阵没有必要内部会生成
	/*resTF=profile_create_memory_map_RAID6(readmatrix,datastrsetblockgroupptr,pparity,qparity,
											countnum,regionptr);//生成内存bit阵
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","scheduling_RAID6","readmapmatrix can't create");
		return FALSE;
	}*/
	//创建需要更新的plist和qlist
	resTF=matrix_update_bitmatrix_pqparity_chunklist_create(pupdatelist,qupdatelist,
															chunkpositionblockgroupptr,matrix);
	if(resTF==FALSE)
	{
		show_error("UPDATE","OPT_update_scheduling_RAID6","updatelist can't create");
		return FALSE;
	}
	pupdatenum=profile_updateelement_updatelist_countnum(pupdatelist,w);
	qupdatenum=profile_updateelement_updatelist_countnum(qupdatelist,w);
	totupdatenum=pupdatenum+qupdatenum;
	updateelementgroupptr->groupsize=totupdatenum;
	updateelementblockgroupptr->groupsize=totupdatenum;
	//创建除调度外的信息
	resTF=UPDATE_OPT_update_element_group_RAID6(updateelementgroupptr,chunkpositionblockgroupptr,
											datastrsetblockgroupptr,pparity,qparity,
											pupdatelist,qupdatelist,
											matrix,regionptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE","OPT_update_scheduling_RAID6","scheduling element can't create");
		return FALSE;
	}
	//printf("updateelement create\n");
	updateelementptr=updateelementgroupptr->updategroup;
	updatenum=updateelementgroupptr->groupsize;

	curparityblockptr=parityblockptr;
	curupdateelementptr=updateelementptr;
	for(i=0;i<updatenum;i++)
	{
		curchunkptr=profile_updateelement_chunk_ptr(curupdateelementptr);
		curparityblockptr->chunkptr=curchunkptr;
		curparityblockptr->chunkid=curchunkptr->ChunkID;
		curparityblockptr++;
		curupdateelementptr++;
	}
	parityblockgroupptr->groupsize=updatenum;
	//给出调度信息
	resTF=UPDATE_OPT_create_scheduling_group_RAID6(updateelementblockgroupptr,updateelementgroupptr,
													datastrsetblockgroupptr,pparity,qparity,
													matrix,readmatrix,countnum,regionptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE","OPT_update_scheduling_RAID6","scheduling order can't calculate");
		return FALSE;
	}
	//printf("scheduling can create\n");
	//计算结果
	resTF=UPDATE_OPT_calculate_target_chunk_RAID6(updateelementblockgroupptr,chunkpositionblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE","OPT_update_scheduling_RAID6","update chunk can't calculate");
		return TRUE;
	}
	//printf("tarchunk can create\n");
	resTF=UPDATE_OPT_free_matrix(readmatrix);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","update_scheduling_RAID6","readmatrix can't free");
		return FALSE;
	}
	updateelementgroupptr->groupsize=2*w;
	resTF=UPDATE_OPT_free_updateelementgroup(updateelementgroupptr);
	if(resTF==FALSE)
	{
		show_error("UPDATE_OPT","update_scheduling_RAID6","updateelementgroupptr can't free");
		return FALSE;
	}
	free(pupdatelist);
	free(qupdatelist);
	free(updateelementgroupptr);
	free(updateelementptr);
	free(updateelementblockgroupptr);
	free(updateelementblockptr);
	free(readmatrix);
	return TRUE;
}