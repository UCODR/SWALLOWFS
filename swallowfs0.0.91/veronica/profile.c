
#include "profile.h"
int profile_updateelement_updatelist_countnum(int *updatelist,int updatenum)
{
	int i,resultnum;
	resultnum=0;
	for(i=0;i<updatenum;i++)
	{
		resultnum=resultnum+updatelist[i];
	}
	return resultnum;
}
CHUNK *profile_updateelement_chunk_ptr(UPDATEELEMENT *updateelementptr)
{
	BITELEMENT *bitelementptr;
	CHUNK *chunkptr;
	bitelementptr=updateelementptr->bitelementptr;
	chunkptr=bitelementptr->chunkptr;
	return chunkptr;
}
int profile_updateelement_bitelement_equal(UPDATEELEMENT *updateelementptr,BITELEMENT *bitelementptr)
{
	BITELEMENT *updatebitelement;
	int updatestripsectindex,updatechunkindex;
	int bitstripsectindex,bitchunkindex;
	updatebitelement=updateelementptr->bitelementptr;
	updatestripsectindex=updatebitelement->stripsectindex;
	updatechunkindex=updatebitelement->chunkindex;

	bitstripsectindex=bitelementptr->stripsectindex;
	bitchunkindex=bitelementptr->chunkindex;
	if((updatestripsectindex==bitstripsectindex)&&(updatechunkindex==bitchunkindex))
	{
		return TRUE;
	}
	return FALSE;
}
int profile_updateelement_updateelement_equal(UPDATEELEMENT *tarupdateelementptr,UPDATEELEMENT *souupdateelementptr)
{
	BITELEMENT *tarbitelement;
	int tarstripsectindex,tarchunkindex;

	BITELEMENT *soubitelement;
	int soustripsectindex,souchunkindex;

	tarbitelement=tarupdateelementptr->bitelementptr;
	tarstripsectindex=tarbitelement->stripsectindex;
	tarchunkindex=tarbitelement->chunkindex;

	soubitelement=souupdateelementptr->bitelementptr;
	soustripsectindex=soubitelement->stripsectindex;
	souchunkindex=soubitelement->chunkindex;
	if((tarstripsectindex==soustripsectindex)&&(tarchunkindex==souchunkindex))
	{
		return TRUE;
	}
	return FALSE;
}

CHUNK *profile_updateelement_temp_chunk_ptr(UPDATEELEMENT *updateelementptr)
{
	return updateelementptr->tempchunkptr;
}

UPDATEELEMENT *profile_updateelement_search_ptr(UPDATEELEMENTGROUP *updateelementgroupptr,int stripsectindex,int chunkindex)
{
	int i,resTF;
	UPDATEELEMENT *updateelementptr,*curupdateelementptr;
	BITELEMENT *bitelementptr;
	int groupsize;

	int curstrsetindex,curchunkindex;

	updateelementptr=updateelementgroupptr->updategroup;
	groupsize=updateelementgroupptr->groupsize;
	curupdateelementptr=updateelementptr;
	for(i=0;i<groupsize;i++)
	{
		bitelementptr=curupdateelementptr->bitelementptr;
		curstrsetindex=bitelementptr->stripsectindex;
		curchunkindex=bitelementptr->chunkindex;
		if((curstrsetindex==stripsectindex)&&(curchunkindex==chunkindex))
		{
			return curupdateelementptr;
		}
		curupdateelementptr++;
	}
	return NULL;
}
int profile_updateelement_is_exist(UPDATEELEMENTGROUP *updateelementgroupptr,int stripsectindex,int chunkindex) //判断一个元素在不在updateelement组中
{
	int i,resTF;
	UPDATEELEMENT *updateelementptr,*curupdateelementptr;
	BITELEMENT *bitelementptr;
	int groupsize;

	int curstrsetindex,curchunkindex;
	
	updateelementptr=updateelementgroupptr->updategroup;
	groupsize=updateelementgroupptr->groupsize;
	curupdateelementptr=updateelementptr;
	for(i=0;i<groupsize;i++)
	{
		bitelementptr=curupdateelementptr->bitelementptr;
		curstrsetindex=bitelementptr->stripsectindex;
		curchunkindex=bitelementptr->chunkindex;
		if((curstrsetindex==stripsectindex)&&(curchunkindex==chunkindex))
		{
			return TRUE;
		}
		curupdateelementptr++;
	}
	return FALSE;
}

int profile_matrix1_matrix2_update_distance(BITMATRIX *matrix1,BITMATRIX *matrix2,BITMATRIX *readmapmatrix)
{
	int i,j,resTF;
	UINT32 *mat;
	int strsetnum,chunknum,w;

	UINT32 *mat1,*mat2;
	int matindex;
	int countnum;

	mat=readmapmatrix->matrix;
	chunknum=readmapmatrix->xm;
	strsetnum=readmapmatrix->ym;
	w=readmapmatrix->w;

	mat1=matrix1->matrix;
	mat2=matrix2->matrix;
	matindex=0;
	countnum=0;
	for(i=0;i<strsetnum;i++)
	{
		for(j=0;j<chunknum;j++)
		{
			resTF=mat1[matindex]^mat2[matindex];
			if(resTF==TRUE)
			{
				resTF=profile_memory_map_is_exist(readmapmatrix,i,j);
				if(resTF==TRUE)
				{
					countnum++;
				}
			}
			matindex++;
		}
	}
	return countnum;
}

int profile_updateelement_updatelement_updateI_distance(UPDATEELEMENT *tarupdateelement,UPDATEELEMENT *souupdateelement,BITMATRIX *readmapmatrix)
{
	int countnum;

	int souisupdateI;

	BITMATRIX *soumatrix,*tarmatrix;

	BITMATRIX *elementptr;
	UINT32 *mat;
	int rows,cols,w;
	elementptr=tarupdateelement->updateIelementptr;
	mat=elementptr->matrix;
	rows=elementptr->xm;
	cols=elementptr->ym;
	w=elementptr->w;

	souisupdateI=souupdateelement->isupdateI;
	switch(souisupdateI)
	{
	case PFALSE://无
		show_error("profile","updateelement_updatelement_updateI_distinct","souupdateelement should be exist");
		return PFALSE;
	case TRUE://updateI
		tarmatrix=tarupdateelement->updateIelementptr;
		soumatrix=souupdateelement->updateIelementptr;
		
		break;
	case FALSE://updateII
		tarmatrix=tarupdateelement->updateIelementptr;
		soumatrix=souupdateelement->updateIIelementptr;
		break;
	}
	countnum=profile_matrix1_matrix2_update_distance(tarmatrix,soumatrix,readmapmatrix);
	return countnum;
}
int profile_updateelement_updatelement_updateII_distance(UPDATEELEMENT *tarupdateelement,UPDATEELEMENT *souupdateelement,BITMATRIX *readmapmatrix)
{
	int countnum;

	int souisupdateI;

	BITMATRIX *soumatrix,*tarmatrix;

	BITMATRIX *elementptr;
	UINT32 *mat;
	int rows,cols,w;
	elementptr=tarupdateelement->updateIIelementptr;
	mat=elementptr->matrix;
	rows=elementptr->xm;
	cols=elementptr->ym;
	w=elementptr->w;

	souisupdateI=souupdateelement->isupdateI;
	switch(souisupdateI)
	{
	case PFALSE://无
		show_error("profile","updateelement_updatelement_updateII_distinct","souupdateelement should be exist");
		return PFALSE;
	case TRUE://updateI
		tarmatrix=tarupdateelement->updateIIelementptr;
		soumatrix=souupdateelement->updateIelementptr;
		break;
	case FALSE://updateII
		tarmatrix=tarupdateelement->updateIIelementptr;
		soumatrix=souupdateelement->updateIIelementptr;
		break;
	}
	countnum=profile_matrix1_matrix2_update_distance(tarmatrix,soumatrix,readmapmatrix);
	if(countnum==PFALSE)
	{
		show_error("profile","updateelement_updatelement_updateII_distinct","countnum can't calculate");
		return PFALSE;
	}
	return countnum;
}
//返回两个updateelement的距离，其中souupdateelement为源模式，计算与当前结果距离,并且经tarupdateelement改成对应模式
int profile_updateelement_updatelement_distance(UPDATEELEMENT *tarupdateelement,UPDATEELEMENT *souupdateelement,BITMATRIX *readmapmatrix)
{
	int updateIcountnum,updateIIcountnum;
	int updatecountnum;
	int isupdateI;
	if(tarupdateelement==souupdateelement)
	{
		return MAXVALUE;
	}
	isupdateI=souupdateelement->isupdateI;
	if(isupdateI==PFALSE)
	{
		return MAXVALUE;
	}
	updateIcountnum=profile_updateelement_updatelement_updateI_distance(tarupdateelement,souupdateelement,readmapmatrix);
	if(updateIcountnum==PFALSE)
	{
		show_error("profile","updateelement_updatelement_distinct","updateI distance can't calculate");
		return PFALSE;
	}
	updateIIcountnum=profile_updateelement_updatelement_updateII_distance(tarupdateelement,souupdateelement,readmapmatrix);
	if(updateIcountnum==PFALSE)
	{
		show_error("profile","updateelement_updatelement_distinct","updateII distance can't calculate");
		return FALSE;
	}
	if(updateIcountnum<=updateIIcountnum)
	{
		tarupdateelement->isupdateI=TRUE;
		updatecountnum=updateIcountnum;
	}
	else
	{
		tarupdateelement->isupdateI=FALSE;
		updatecountnum=updateIIcountnum;
	}
	return updatecountnum;
}

int profile_updateelememt_bitelement_updateI_distance(UPDATEELEMENT *tarupdateelement,BITELEMENT *soubitelement,BITMATRIX *readmapmatrix)//返回updateelement的距离
{
	int countnum;

	//int souisupdateI;

	BITMATRIX *soumatrix,*tarmatrix;

	//BITMATRIX *elementptr;
	tarmatrix=tarupdateelement->updateIelementptr;
	soumatrix=soubitelement->elementptr;
	//matrix_print_bitmatrix_oneline(tarmatrix);
	//matrix_print_bitmatrix_oneline(soumatrix);
	countnum=profile_matrix1_matrix2_update_distance(tarmatrix,soumatrix,readmapmatrix);
	if(countnum==PFALSE)
	{
		show_error("profile","updateelememt_bitelement_updateI_distance","distance can't calculate");
		return PFALSE;
	}
	return countnum;
}
int profile_updateelememt_bitelement_updateII_distance(UPDATEELEMENT *tarupdateelement,BITELEMENT *soubitelement,BITMATRIX *readmapmatrix)//返回updateelement的距离
{
	int countnum;
	BITMATRIX *soumatrix,*tarmatrix;

	tarmatrix=tarupdateelement->updateIIelementptr;
	soumatrix=soubitelement->elementptr;
	//matrix_print_bitmatrix_oneline(tarmatrix);
	//matrix_print_bitmatrix_oneline(soumatrix);
	countnum=profile_matrix1_matrix2_update_distance(tarmatrix,soumatrix,readmapmatrix);
	if(countnum==PFALSE)
	{
		show_error("profile","updateelememt_bitelement_updateI_distance","distance can't calculate");
		return PFALSE;
	}
	return countnum;
}
int profile_updateelememt_bitelement_distance(UPDATEELEMENT *tarupdateelement,BITELEMENT *soubitelement,BITMATRIX *readmapmatrix)//返回updateelement的距离
{
	int resTF;
	int updatecountnum;
	int updateIcountnum,updateIIcountnum;
	resTF=profile_updateelement_bitelement_equal(tarupdateelement,soubitelement);
	if(resTF==TRUE)
	{
		//不能通过自己算自己
		return MAXVALUE;
	}
	updateIcountnum=profile_updateelememt_bitelement_updateI_distance(tarupdateelement,soubitelement,readmapmatrix);
	if(updateIcountnum==PFALSE)
	{
		show_error("profile","updateelememt_bitelement_distance","distance can't calculate");
		return PFALSE;
	}
	updateIIcountnum=profile_updateelememt_bitelement_updateII_distance(tarupdateelement,soubitelement,readmapmatrix);
	if(updateIIcountnum==PFALSE)
	{
		show_error("profile","updateelememt_bitelement_distance","distance can't calculate");
		return PFALSE;
	}
	if(updateIcountnum<=updateIIcountnum)
	{
		updatecountnum=updateIcountnum;
		tarupdateelement->isupdateI=TRUE;
	}
	else
	{
		updatecountnum=updateIIcountnum;
		tarupdateelement->isupdateI=FALSE;
	}
	return updatecountnum;
}

//计算当前内存地图
int profile_memory_map_is_exist(BITMATRIX *readmapmatrixptr,int stripsectindex,int chunkindex)//判断一个元素在不在内存地图内//TRUE代表需要从硬盘读//FALSE代表不需要//PFALSE代表有错
{
	UINT32 *mat;
	int rows,cols,w;

	int tarindex;

	mat=readmapmatrixptr->matrix;
	rows=readmapmatrixptr->xm;
	cols=readmapmatrixptr->ym;
	w=readmapmatrixptr->w;
	//安全性检测
	if(chunkindex>rows)
	{
		show_error("profile","memory_map_add_element","stripsect outrange");
		return PFALSE;
	}
	if(stripsectindex>cols)
	{
		show_error("profile","memory_map_add_element","stripsect outrange");
		return PFALSE;
	}
	tarindex=chunkindex*cols+stripsectindex;
	return mat[tarindex];
}
//readmapmatrix，x为chunknum，y为sripsectnum
int profile_memory_map_add_element(BITMATRIX *readmapmatrixptr,int stripsectindex,int chunkindex)//想内存地图中加入一个元素
{
	UINT32 *mat;
	int rows,cols,w;

	int tarindex;

	mat=readmapmatrixptr->matrix;
	rows=readmapmatrixptr->xm;
	cols=readmapmatrixptr->ym;
	w=readmapmatrixptr->w;
	//安全性检测
	if(chunkindex>rows)
	{
		show_error("profile","memory_map_add_element","stripsect outrange");
		return FALSE;
	}
	if(stripsectindex>cols)
	{
		show_error("profile","memory_map_add_element","stripsect outrange");
		return FALSE;
	}
	tarindex=chunkindex*cols+stripsectindex;
	mat[tarindex]=FALSE;//不需要从内存读
	return TRUE;
}

double profile_calculate_time_diff(long starttick,long endtick)
{
	double timediff;
	long clocktick;
	clocktick=endtick-starttick;
	timediff=(double)clocktick/CLOCKS_PER_SEC;
	return timediff;
}


int profile_bitelement_dataelement(int stripsectindex,int chunkindex,BITELEMENT *bitelementptr,BITMATRIX *matrix,REGION *regionptr)//将数据中一行进行拷贝
{
	BITMATRIX *matrixptr;

	int tarindex;

	UINT32 *mat;
	int rows,cols,w;

	UINT32 *cmat;
	int crows,ccols,cw;
	matrixptr=bitelementptr->elementptr;

	mat=matrixptr->matrix;
	rows=matrixptr->xm;
	cols=matrixptr->ym;
	w=matrixptr->w;

	cmat=matrix->matrix;
	crows=matrix->xm;
	ccols=matrix->ym;
	cw=matrix->w;
	if(mat==NULL)
	{
		mat=talloc(UINT32,cols);
		if(mat==NULL)
		{
			show_error("profile","bitelement_dataelement","No memory");
			return FALSE;

		}
		matrixptr->matrix=mat;
	}
	bzero(mat,UINT32,cols);
	tarindex=stripsectindex*cw+chunkindex;
	mat[tarindex]=1;

	return TRUE;
}
int profile_bitelement_codeelement(int stripsectindex,int chunkindex,BITELEMENT *bitelementptr,BITMATRIX *matrix,REGION *regionptr)//生成相应的数据块
{

	BITMATRIX *matrixptr;

	UINT32 *elemat;
	int elerows,elecols;

	UINT32 *mat,*curmat;
	int rows,cols,w;

	CODEPARA *codeparamptr;
	int datanum,codenum;
	int rowsindex;
	int tarindex;
	codeparamptr=regionptr->codepara;
	datanum=codeparamptr->datanum;


	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	matrixptr=bitelementptr->elementptr;

	elemat=matrixptr->matrix;
	elerows=matrix->xm;
	elecols=matrix->ym;
	w=matrix->w;
	if(elemat==NULL)
	{
		elemat=talloc(UINT32,cols);
		if(elemat==NULL)
		{
			show_error("profile","bitelement_codeelement","No memory");
			return FALSE;
		}
		matrixptr->matrix=elemat;
	}
	rowsindex=(stripsectindex-datanum)*w;
	rowsindex=rowsindex+chunkindex;
	tarindex=rowsindex*cols;
	curmat=mat+tarindex;
	mcpy(elemat,curmat,UINT32,cols);
	return TRUE;
}
//生成全局错误模式
extern int profile_create_global_errorpattern(ERRORPATTERN *errormatrix)
{
	BITMATRIX *matrixptr;

	UINT32 *mat;
	int rows,cols,w;

	int i,resTF;

	DISK *diskptr,*curdiskptr;
	int disknum;

	DISKGROUP *diskgroupptr;

	diskgroupptr=get_state_glodiskgroup_PTR();
	
	diskptr=diskgroupptr->diskgroup;
	disknum=diskgroupptr->groupsize;

	errormatrix->errordisknum=disknum;
	errormatrix->errorchunknum=NONE;

	matrixptr=errormatrix->bitmatrix;

	mat=matrixptr->matrix;
	rows=matrixptr->xm;
	cols=matrixptr->ym;
	w=matrixptr->w;

	matrixptr->xm=disknum;

	curdiskptr=diskptr;
	for(i=0;i<disknum;i++)
	{
		resTF=file_FILELAYER_device_available(curdiskptr);
		if(resTF==TRUE)
		{
			mat[i]=FALSE;//当前不需要纠删
		}
		else
		{
			mat[i]=TRUE;//当前需要纠删
		}
		curdiskptr++;
	}

	return TRUE;
}
extern int profile_set_disk_available_state()
{

	int i,resTF;

	DISK *diskptr,*curdiskptr;
	int disknum;

	DISKGROUP *diskgroupptr;

	diskgroupptr=get_state_glodiskgroup_PTR();

	diskptr=diskgroupptr->diskgroup;
	disknum=diskgroupptr->groupsize;

	curdiskptr=diskptr;
	for(i=0;i<disknum;i++)
	{
		resTF=file_FILELAYER_device_available(curdiskptr);
		if(resTF==TRUE)
		{
			curdiskptr->availstate=TRUE;
		}
		else
		{
			curdiskptr->availstate=FALSE;
		}
		curdiskptr++;
	}
	return TRUE;
}
extern int profile_create_global_errorpattern_global_errorpattern(ERRORPATTERN *errormatrix)
{
	int resTF;
	resTF=profile_create_global_errorpattern(errormatrix);
	if(resTF==FALSE)
	{
		show_error("profile","create_global_errorpattern_global_errorpattern","error pattern can't create");
		return FALSE;
	}
	resTF=profile_set_disk_available_state();
	if(resTF==FALSE)
	{
		show_error("profile","create_global_errorpattern_global_errorpattern","disk state can't create");
		return FALSE;
	}
	return TRUE;
}
//产生人工错误
extern int profile_set_global_disk_error(ERRORPATTERN *errormatrix)
{
	int resTF;
	int i;
	BITMATRIX *matrixptr;

	UINT32 *mat;
	int rows,cols,w;

	int errordisknum,errorchunknum;

	DISKGROUP *diskgroupptr;
	DISK *diskptr,*curdiskptr;
	int disknum;

	matrixptr=errormatrix->bitmatrix;
	errordisknum=errormatrix->errordisknum;
	errorchunknum=errormatrix->errorchunknum;

	mat=matrixptr->matrix;
	rows=matrixptr->xm;
	cols=matrixptr->ym;
	w=matrixptr->w;

	diskgroupptr=get_state_glodiskgroup_PTR();

	diskptr=diskgroupptr->diskgroup;
	disknum=diskgroupptr->groupsize;

	curdiskptr=diskptr;
	for(i=0;i<disknum;i++)
	{
		resTF=mat[i];
		if(resTF==FALSE)
		{
			curdiskptr->availstate=TRUE;
		}
		else
		{
			curdiskptr->availstate=FALSE;
		}
		curdiskptr++;
	}
	return TRUE;
}


//readmap，x为chunknum，y为sripsectnum
int profile_create_memory_map(BITMATRIX *matrix,STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
									STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,int *countnum,REGION *regionptr)
{
	int i,j,resTF;
	int rows,cols,w;
	UINT32 *mat;

	CODEPARA *codeparamptr;
	int datanum,codenum,totnum;

	STRIPSECTBLOCK *datastrsetblockptr,*curdatastrsetblockptr;
	STRIPSECT *datastrsetptr;
	int datagroupsize;

	STRIPSECTBLOCK *codestrsetblockptr,*curcodestrsetblockptr;
	STRIPSECT *codestrsetptr;
	int codegroupsize;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;
	int chunknum;

	int rowsindex,colsindex,curindex;

	codeparamptr=regionptr->codepara;

	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	totnum=codeparamptr->totnum;
	w=codeparamptr->w;

	rows=w;
	cols=totnum;
	mat=matrix->matrix;
	if(mat==NULL)
	{
		mat=talloc(UINT32,rows*cols);
		if(mat==NULL)
		{
			show_error("profile","create_memory_map","No memory");
			return FALSE;
		}
		bzero(mat,UINT32,rows*cols);
	}
	matrix->matrix=mat;
	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w;

	countnum[0]=0;
	countnum[1]=0;

	datastrsetblockptr=datastrsetblockgroupptr->stripsectblockptr;
	datagroupsize=datastrsetblockgroupptr->groupsize;

	curdatastrsetblockptr=datastrsetblockptr;
	for(i=0;i<datagroupsize;i++)
	{
		datastrsetptr=curdatastrsetblockptr->stripsectptr;
		chunkgroupptr=datastrsetptr->chunklist;

		chunkptr=chunkgroupptr->ckgroup;
		chunknum=chunkgroupptr->groupsize;

		curchunkptr=chunkptr;
		for(j=0;j<chunknum;j++)
		{
			resTF=profile_chunk_should_read(curchunkptr);
			rowsindex=j*cols;//根据chunkindex计算行号
			colsindex=i;//strset计算列号
			curindex=rowsindex+colsindex;
			if(resTF==TRUE)
			{
				mat[curindex]=TRUE;//将其设置为TRUE
				countnum[0]++;
			}
			else
			{
				mat[curindex]=FALSE;
				countnum[1]++;
			}
			curchunkptr++;
		}

		curdatastrsetblockptr++;
	}
	codestrsetblockptr=codestrsetblockgroupptr->stripsectblockptr;
	codegroupsize=codestrsetblockgroupptr->groupsize;

	curcodestrsetblockptr=codestrsetblockptr;
	for(i=0;i<codegroupsize;i++)
	{
		codestrsetptr=curcodestrsetblockptr->stripsectptr;
		chunkgroupptr=codestrsetptr->chunklist;

		chunkptr=chunkgroupptr->ckgroup;
		chunknum=chunkgroupptr->groupsize;

		curchunkptr=chunkptr;
		for(j=0;j<chunknum;j++)
		{
			//计算位置
			resTF=profile_chunk_should_read(curchunkptr);
			rowsindex=j*cols;
			colsindex=i+datanum;//填写后面两位
			curindex=rowsindex+colsindex;
			if(resTF==TRUE)
			{
				mat[curindex]=TRUE;
				countnum[0]++;
			}
			else
			{
				mat[curindex]=FALSE;
				countnum[1]++;
			}
			curchunkptr;
		}

		curcodestrsetblockptr++;
	}
	return TRUE;	
}
int profile_create_memory_map_RAID6(BITMATRIX *matrix,STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
									STRIPSECT *pparity,STRIPSECT *qparity,int *countnum,REGION *regionptr)
{
	int resTF;

	STRIPSECTBLOCKGROUP *codestrsetblockgroupptr;
	STRIPSECTBLOCK *codestrsetblockptr;
	int codenum;

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

	codestrsetblockptr->stripsectptr=pparity;
	codestrsetblockptr->stripsectid=pparity->StripsectID;

	codestrsetblockptr=codestrsetblockptr+1;

	codestrsetblockptr->stripsectptr=qparity;
	codestrsetblockptr->stripsectid=qparity->StripsectID;
	resTF=profile_create_memory_map(matrix,datastrsetblockgroupptr,codestrsetblockgroupptr,countnum,regionptr);
	if(resTF==FALSE)
	{
		show_error("profile","create_memory_map_RAID6","memory_map can't create");
		return FALSE;
	}
	free(codestrsetblockgroupptr);
	free(codestrsetblockptr);
	return TRUE;
}
int profile_strip_into_stripsect_ptr(STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,STRIP *stripptr)
{
	int i,isparity;
	STRIPSECTBLOCK *datastrsetblockptr,*curdatastrsetblockptr;
	int dataindex;

	STRIPSECTBLOCK *codesrsetblockptr,*curcodesrsetblockptr;
	int codeindex;
	int datanum,codenum;

	STRIPSECTGROUP *strsetgroupptr;
	STRIPSECT *strsetptr,*curstrsetptr;
	int strsetnum;

	datastrsetblockptr=datastrsetblockgroupptr->stripsectblockptr;
	datanum=datastrsetblockgroupptr->groupsize;
	if(datastrsetblockptr==NULL)
	{
		datastrsetblockptr=talloc(STRIPSECTBLOCK,datanum);
		if(datastrsetblockptr==NULL)
		{
			show_error("profile","strip_into_stripsect","No memory");
			return FALSE;
		}
	}
	codesrsetblockptr=codestrsetblockgroupptr->stripsectblockptr;
	codenum=codestrsetblockgroupptr->groupsize;
	if(codesrsetblockptr==NULL)
	{
		codesrsetblockptr=talloc(STRIPSECTBLOCK,codenum);
		if(datastrsetblockptr==NULL)
		{
			show_error("profile","strip_into_stripsect","No memory");
			return FALSE;
		}
	}
	strsetgroupptr=stripptr->stripsectlist;

	strsetptr=strsetgroupptr->stripsectgroup;
	strsetnum=strsetgroupptr->groupsize;

	curstrsetptr=strsetptr;
	dataindex=0;
	codeindex=0;
	for(i=0;i<strsetnum;i++)
	{
		isparity=curstrsetptr->isparity;
		if(isparity==FALSE)
		{
			curdatastrsetblockptr=datastrsetblockptr+dataindex;
			curdatastrsetblockptr->stripsectptr=curstrsetptr;
			curdatastrsetblockptr->stripsectid=curstrsetptr->StripsectID;
			dataindex++;
		}
		else
		{
			codeindex=isparity-1;//当前校验块标号
			curcodesrsetblockptr=codesrsetblockptr+codeindex;
			curcodesrsetblockptr->stripsectptr=curstrsetptr;
			curcodesrsetblockptr->stripsectid=curstrsetptr->StripsectID;
		}
		curstrsetptr++;
	}
	return TRUE;
}
int profile_is_prime(int w)
{
	int i,n;
	n=(int)sqrt((double)w);
	for(i=2;i<=n;i++)
	{
		if(w%i==0)
		{
			return FALSE;
		}
	}
	return TRUE;
}
int profile_next_prime(int datanum)
{
	int resnum,resTF;
	resnum=datanum;
	resTF=profile_is_prime(resnum);
	while(resTF==FALSE)
	{
		resnum++;
		resTF=profile_is_prime(resnum);
	}
	return PFALSE;
}
int profile_chunk_to_chunkposition(CHUNKPOSITIONBLOCK *chunkpositionblockptr,CHUNK *chunkptr)
{
	int i,j,isparity;
	STRIP *stripptr;

	STRIPSECTGROUP *strsetgroupptr;
	STRIPSECT *strsetptr,*curstrsetptr;
	int strsetnum;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *tarchunkptr,*curtarchunkptr;
	int chunknum;
	int chunkindex,strsetindex;

	chunkindex=0;
	strsetindex=0;

	stripptr=chunkptr->stripptr;

	strsetgroupptr=stripptr->stripsectlist;
	strsetptr=strsetgroupptr->stripsectgroup;
	strsetnum=strsetgroupptr->groupsize;

	curstrsetptr=strsetptr;

	strsetindex=0;
	for(i=0;i<strsetnum;i++)
	{
		isparity=curstrsetptr->isparity;
		chunkindex;
		if(isparity==FALSE)//如果当前不是校验块
		{
			chunkgroupptr=curstrsetptr->chunklist;
			tarchunkptr=chunkgroupptr->ckgroup;
			chunknum=chunkgroupptr->groupsize;

			curtarchunkptr=tarchunkptr;
			for(j=0;j<chunknum;j++)
			{
				isparity=curtarchunkptr->isparity;
				//如果是当前块
				if(curtarchunkptr==chunkptr)
				{
					chunkpositionblockptr->chunkptr=chunkptr;
					chunkpositionblockptr->chunkid=chunkptr->ChunkID;

					chunkpositionblockptr->stripsectindex=strsetindex;
					chunkpositionblockptr->chunkindex=chunkindex;
				}
				if(isparity==FALSE)
				{
					chunkindex++;
				}
				curtarchunkptr++;
			}
			strsetindex++;
		}
		curstrsetptr++;
	}
	return TRUE;
}
int profile_chunk_should_read(CHUNK *chunkptr)
{
	//判断这个块是不是为空
	BYTE *contentptr;
	int storestate;
	contentptr=chunkptr->chunkcontent;
	if(contentptr==NULL)
	{
		storestate=chunkptr->storestate;
		if(storestate!=FALSE)//说明已经存储过了
		{
			return TRUE;
		}
	}
	return FALSE;
}
int profile_chunk_create_empty_data(CHUNK *chunkptr)
{
	int chunksize;
	BYTE *chunkcontent;
	chunksize=chunkptr->sizenum;
	chunkcontent=talloc(BYTE,chunksize);
	if(chunkcontent==NULL)
	{
		show_error("profile","chunk_data_read","No memory");
		return FALSE;
	}
	bzero(chunkcontent,BYTE,chunksize);
	chunkptr->chunkcontent=chunkcontent;
	return TRUE;
}
//将chunkdata同步数据到内存
int profile_chunk_data_read(CHUNK *chunkptr)
{
	BYTE *chunkcontent;
	int chunksize;
	int resTF;
	chunkcontent=chunkptr->chunkcontent;
	//需要检测当前chunkptr的数据是不是在内存不在需要同步
	if(chunkcontent==NULL)
	{
		//同步吧
		resTF=profile_chunk_data_haswrited(chunkptr);
		if(resTF==TRUE)
		{
			resTF=FILELAYER_CHUNK_READER_DATA(chunkptr);
			if(resTF==FALSE)
			{
				show_error("profile","chunk_data_read","chunk data can't read");
				return FALSE;
			}
		}
		else
		{
			chunksize=chunkptr->sizenum;
			chunkcontent=talloc(BYTE,chunksize);
			if(chunkcontent==NULL)
			{
				show_error("profile","chunk_data_read","No memory");
				return FALSE;
			}
			bzero(chunkcontent,BYTE,chunksize);
			chunkptr->chunkcontent=chunkcontent;
		}
	}
	return TRUE;
}

//判断一个chunk是否为为空
int profile_chunk_data_haswrited(CHUNK *chunkptr)
{
	int isempty;
	isempty=chunkptr->storestate;
	if(isempty!=EMPTY)
	{
		return TRUE;
	}
	return FALSE;
}

int profile_chunk_data_isfree(CHUNK *chunkptr)
{
	BYTE *contentptr;
	contentptr=chunkptr->chunkcontent;
	if(contentptr==NULL)
	{
		return TRUE;
	}
	return FALSE;
}

//创建region并且进行格式化
int profile_region_setup_without_filemeta(REGION *regionptr,int codetype,CODEPARA *codepara,STRIPDES *strdes,UINT64 totalsize,
									UINT64 *glodeviceidlist,DEVICEBLOCK *glodeviceblockptr,int devicenum,
									UINT64 *glodiskidlist,DISKBLOCK *glodiskblockptr,int disknum)
{
	int resTF;
	GLOBAL_set_REGION_data(regionptr,codetype,codepara,totalsize,
								  NULL,NULL,NOVALUE,//包括的file的列表,文件中进行更新
								  glodiskblockptr,glodiskidlist,disknum,//Disk的列表
								  glodeviceblockptr,glodeviceidlist,devicenum,//device列表
								  strdes,NULL,NULL,NOVALUE,//条带个数
								  NOVALUE,NOVALUE,//chunk和stripsect总数
								  NULL,NOVALUE,//根文件指针,文件中进行更新
								  EMPTY//当前存储状态
								  );//设定当前REGION中的数据
	//信息已足可以格式化了
	resTF=profile_region_format_PTR(regionptr);
	if(resTF==FALSE)
	{
		show_error("profile","_region_setup_without_filemeta","region can't format");
		return FALSE;
	}
	return TRUE;
}
//创建相应的rootdictionary
int profile_region_setup_rootdictionary_filemeta(FILEMETA *rootdicptr,char *filename,USERPROFILE *userprofileptr,REGION *regionptr)
{
	FILEMETABLOCKGROUP *filemetablockgroupptr;
	FILEMETABLOCK *filemetablockptr;
	UINT64 *glofileidlist;
	UINT64 currentid;
	FILEINF *fileinfptr;

	time_t rawtime;
	struct tm *Nowtime;

	filemetablockgroupptr=talloc(FILEMETABLOCKGROUP,1);
	if(filemetablockgroupptr==NULL)
	{
		show_error("profile","region_setup_without_filemeta","No memory");
		return FALSE;
	}
	filemetablockptr=talloc(FILEMETABLOCK,1);
	if(filemetablockptr==NULL)
	{
		show_error("profile","region_setup_without_filemeta","No memory");
		return FALSE;
	}
	glofileidlist=talloc(UINT64,1);
	if(glofileidlist==NULL)
	{
		show_error("profile","region_setup_without_filemeta","No memory");
		return FALSE;
	}

	//设定数据
	rootdicptr->FileID=get_state_glofileid();
	currentid=get_state_glofileid();//先让我记一下
	set_state_glofileid_add(1);
	fileinfptr=NULL;//由于只有初始目录因此没有数据
	
	time(&rawtime);	
	Nowtime=localtime(&rawtime);

	GLOBAL_set_FILEMETA_data(rootdicptr,filename,NOVALUE,NOVALUE,DICTKIND,
									regionptr,regionptr->RegionID,//上层region指针
									userprofileptr,userprofileptr->UserID,//文件所有者，暂时设定为
									NOVALUE,NULL,//上一次文件夹，根目录为NULL
									NULL,NULL,NONE,//暂时没有数据，文件块指针主要指向当前目录下一级元数据块
									Nowtime,//将创建和更新时间都设定为当前时间
									Nowtime,
									NULL//用于存放数据块信息
									);//设定FILEMETA数据值
	//计算当前关系
	//将数据赋值会region区域
	regionptr->rootfileid=currentid;
	regionptr->fileroot=rootdicptr;
	filemetablockgroupptr->filemetablockptr=filemetablockptr;
	filemetablockgroupptr->groupsize=1;

	filemetablockptr->filemetaptr=rootdicptr;
	filemetablockptr->FileID=rootdicptr->FileID;

	regionptr->filemetalist=filemetablockgroupptr;
	//还是要开空间
	glofileidlist[0]=currentid;
	regionptr->fileid=glofileidlist;
	regionptr->filenum=1;
	return TRUE;
}
//计算当前的数据
int profile_region_setup(REGION *regionptr,int codetype,CODEPARA *codepara,STRIPDES *strdes,UINT64 totalsize,
						UINT64 *glodeviceidlist,DEVICEBLOCK *glodeviceblockptr,int devicenum,
						UINT64 *glodiskidlist,DISKBLOCK *glodiskblockptr,int disknum,
						char *filename,USERPROFILE *userprofileptr)
{
	int resTF;
	FILEMETA *rootdicptr;
	//创创建一个根目录
	rootdicptr=talloc(FILEMETA,1);
	if(rootdicptr==NULL)
	{
		show_error("region","setup","No memory");
		return FALSE;
	}

	resTF=profile_region_setup_without_filemeta(regionptr,codetype,codepara,strdes,totalsize,
												glodeviceidlist,glodeviceblockptr,devicenum,
												glodiskidlist,glodiskblockptr,disknum);
	if(resTF==FALSE)
	{
		show_error("region","setup","region can't create");
		return FALSE;
	}
	resTF=profile_region_setup_rootdictionary_filemeta(rootdicptr,filename,userprofileptr,regionptr);
	if(resTF==FALSE)
	{
		show_error("region","setup","the relationship between rootdic and region can' create");
		return FALSE;
	}
	resTF=profile_map_define_intial(regionptr);
	if(resTF==FALSE)
	{
		show_error("region","setup","RAID parity information can't write");
		return FALSE;
	}
	return TRUE;
}



//计算firstoffset
int profile_update_startoffset(int chunksize,int offset)
{
	int startoffset;
	int firstchunkindex;
	//计算第一个chunk的index
	firstchunkindex=offset/chunksize;//计算第一个chunk的索引
	//startoffset=(firstchunkindex+1)*chunksize-offset;
	startoffset=offset-firstchunkindex*chunksize;
	return startoffset;
}
//计算lastoffset
int profile_update_lastoffset(int chunksize,int offset,int updatesize)
{
	int lastoffset;
	int lastchunkindex;
	lastchunkindex=(offset+updatesize)/chunksize;
	//lastoffset=(lastchunkindex+1)*chunksize-offset-updatesize;
	lastoffset=offset+updatesize-lastchunkindex*chunksize;
	return lastoffset;
}


//释放空间
int profile_free_chunk_data(CHUNK *chunkptr)
{
	BYTE *contentptr;
	contentptr=chunkptr->chunkcontent;
	free(contentptr);
	contentptr=NULL;
	chunkptr->chunkcontent=contentptr;
	return TRUE;
}
int profile_free_chunkgroup_data(CHUNKGROUP *chunkgroupptr)
{
	int i;
	BYTE *contentptr;
	CHUNK *chunkptr;
	int groupsize;
	chunkptr=chunkgroupptr->ckgroup;
	groupsize=chunkgroupptr->groupsize;
	for(i=0;i<groupsize;i++)
	{
		contentptr=chunkptr->chunkcontent;
		free(contentptr);
		contentptr=NULL;
		chunkptr->chunkcontent=contentptr;
		chunkptr++;
	}
	return TRUE;
}
int profile_free_chunkblockgroup_data(CHUNKBLOCKGROUP *chunkblockgroupptr)
{
	int i;
	BYTE *contentptr;
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr; 
	CHUNK *chunkptr;
	int chunknum;

	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunknum=chunkblockgroupptr->groupsize;

	curchunkblockptr=chunkblockptr;
	for(i=0;i<chunknum;i++)
	{
		chunkptr=curchunkblockptr->chunkptr;
		contentptr=chunkptr->chunkcontent;
		free(contentptr);
		contentptr=NULL;
		chunkptr->chunkcontent=contentptr;
		curchunkblockptr++;
	}
	return TRUE;
}
int profile_free_chunkpositionblockgroup_data(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgrouipptr)
{
	int i;
	BYTE *contentptr;
	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	CHUNK *chunkptr;
	int chunknum;

	chunkpositionblockptr=chunkpositionblockgrouipptr->chunkblockptr;
	chunknum=chunkpositionblockgrouipptr->groupsize;

	curchunkpositionblockptr=chunkpositionblockptr;
	for(i=0;i<chunknum;i++)
	{
		chunkptr=curchunkpositionblockptr->chunkptr;
		contentptr=chunkptr->chunkcontent;
		free(contentptr);
		contentptr=NULL;
		chunkptr->chunkcontent=contentptr;
		curchunkpositionblockptr++;
	}
	return TRUE;
}
//将数据块记录到tempreelist
int profile_tempfree_chunk_ptr(CHUNK *chunkptr)
{
	//int i;

	GLOTEMPFREELIST *tempfreelistptr;
	CHUNKBLOCK *tarchunkblockptr,*curtarchunkblockptr;
	CHUNK *tarchunkptr;
	int tarchunknum;

	tempfreelistptr=get_state_tempfreelist();
	tarchunkblockptr=tempfreelistptr->chunkblockptr;
	tarchunknum=tempfreelistptr->tempnum;

	curtarchunkblockptr=tarchunkblockptr+tarchunknum;
	curtarchunkblockptr->chunkptr=chunkptr;
	curtarchunkblockptr->chunkid=chunkptr->ChunkID;

	tarchunknum++;
	tempfreelistptr->tempnum=tarchunknum;//赋值回去
	return TRUE;
}
//将数据块组记录到tempfreelist
int profile_tempfree_chunkblock_ptr(CHUNKBLOCKGROUP *chunkblockgroupptr)
{
	int i;
	CHUNKBLOCK *souchunkblockptr,*cursouchunkblockptr;
	CHUNK *souchunkptr;
	int souchunknum;

	GLOTEMPFREELIST *tempfreelistptr;
	CHUNKBLOCK *tarchunkblockptr,*curtarchunkblockptr;
	CHUNK *tarchunkptr;
	int tarchunknum;

	souchunkblockptr=chunkblockgroupptr->chunkblockptr;
	souchunknum=chunkblockgroupptr->groupsize;

	tempfreelistptr=get_state_tempfreelist();
	tarchunkblockptr=tempfreelistptr->chunkblockptr;
	tarchunknum=tempfreelistptr->tempnum;

	//计算当前指针的偏移量
	curtarchunkblockptr=tarchunkblockptr+tarchunknum;
	cursouchunkblockptr=souchunkblockptr;
	for(i=0;i<souchunknum;i++)
	{
		curtarchunkblockptr->chunkptr=cursouchunkblockptr->chunkptr;
		curtarchunkblockptr->chunkid=cursouchunkblockptr->chunkid;
		curtarchunkblockptr++;
		cursouchunkblockptr++;
	}
	tarchunknum=tarchunknum+souchunknum;
	tempfreelistptr->tempnum=tarchunknum;
	return TRUE;
}
//释放当前的free列表
 int profile_tempfree_free()
 {
	 int i;
	 GLOTEMPFREELIST *tempfreelistptr;
	 CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	 CHUNK *chunkptr;
	 int chunknum;

	 BYTE *contentptr;

	 tempfreelistptr=get_state_tempfreelist();

	 chunkblockptr=tempfreelistptr->chunkblockptr;
	 chunknum=tempfreelistptr->tempnum;

	 curchunkblockptr=chunkblockptr;
	 for(i=0;i<chunknum;i++)
	 {
		 chunkptr=curchunkblockptr->chunkptr;
		 contentptr=chunkptr->chunkcontent;
		 free(contentptr);
		 contentptr=NULL;
		 chunkptr->chunkcontent=contentptr;
		 curchunkblockptr++;
	 }
	 return TRUE;
 }
//计算函数
//除余数(带负数)（m mod n）
int profile_mod_number(int m,int n)
{
	int resnum;
	while(m<0)
	{
		m=m+n;
	}
	//计算余数
	resnum=m%n;
	return resnum;
}

//主要需要初始化的参数,显示不同信息
//当前chunk所在stripsec中的位置
int profile_chkpath_to_chunk_stripsectnum(CHUNKPATH *chkpathptr)
{
	return chkpathptr->chunkarrayid;
}
//当前chunk所在stripsec中的位置
int profile_chkpath_to_chunk_stripnum(CHUNKPATH *chkpathptr)
{
	int strsetchunknum,chunkarrayid,strsetarrayid,resnum;
	STRIPSECT *strsetptr;

	strsetptr=chkpathptr->stripsectptr;
	strsetchunknum=strsetptr->chunknum;

	chunkarrayid=chkpathptr->chunkarrayid;
	strsetarrayid=chkpathptr->stripsectarrayid;

	resnum=calchunkstriparrayid(strsetchunknum,strsetarrayid,chunkarrayid);

	return resnum;
}
//当前chunk所在stripsec中的位置
int profile_chkpath_to_chunk_regionnum(CHUNKPATH *chkpathptr)
{
	int stripchunknum,striparrayid,chunkarrayid,resnum;
	STRIP *stripptr;

	stripptr=chkpathptr->stripptr;
	stripchunknum=stripptr->chunknum;

	striparrayid=chkpathptr->striparrayid;
	chunkarrayid=profile_chkpath_to_chunk_stripnum(chkpathptr);//计算在条带中的位置

	resnum=calchunkregionarrayid(stripchunknum,striparrayid,chunkarrayid);
	return resnum;

}


//当前chunk所在的stripsect在strip中的位置
int profile_chkpath_to_stripsect_stripnum(CHUNKPATH *chkpathptr)
{
	return chkpathptr->stripsectarrayid;
}
//当前chunk所在的stripsect在region中的位置
int profile_chkpath_to_stripsect_regionnum(CHUNKPATH *chkpathptr)
{
	int stripstrsetnum,striparrayid,strsetarrayid,resnum;
	STRIP *stripptr;

	stripptr=chkpathptr->stripptr;
	stripstrsetnum=stripptr->strsetnum;

	striparrayid=chkpathptr->striparrayid;
	strsetarrayid=chkpathptr->stripsectarrayid;

	resnum=calstripsectregionarrayid(stripstrsetnum,striparrayid,strsetarrayid);
	return resnum;
}

//当前chunk所在的strip在region中的位置
int profile_chkpath_to_strip_regionnum(CHUNKPATH *chkpathptr)
{
	return chkpathptr->striparrayid;
}







//转化函数
//将当前的数据中的data chunk进行提取
int profile_stripblock_to_datachunkblock(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr)
{
	int i,resTF;
	int isparity;
	
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	STRIP *stripptr;

	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;

	int chunknum,datacountnum;
	int stripblocksize,stripnum;

	stripblocksize=stripblockgroupptr->groupsize;
	stripblockptr=stripblockgroupptr->stripblockptr;
	
	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunknum=chunkblockgroupptr->groupsize;

	curstripblockptr=stripblockptr;
	curchunkblockptr=chunkblockptr;
	datacountnum=0;
	for(i=0;i<stripblocksize;i++)
	{
		stripptr=curstripblockptr->stripptr;

		chunkgroupptr=stripptr->chunklist;

		chunkptr=chunkgroupptr->ckgroup;
		chunknum=chunkgroupptr->groupsize;

		curchunkptr=chunkptr;
		for(i=0;i<chunknum;i++)
		{
			isparity=curchunkptr->isparity;//看看是不是
			if(isparity==FALSE)
			{
				curchunkblockptr->chunkptr=curchunkptr;
				curchunkblockptr->chunkid=curchunkptr->ChunkID;
				datacountnum++;
			}
			curchunkptr++;
			curchunkblockptr++;
		}
		curstripblockptr++;
	}
	chunkblockgroupptr->groupsize=datacountnum;
	return TRUE;
}
//将当前的数据中的parity datachunk进行提取
int profile_stripblock_to_paritychunkblock(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr)
{
	int i,resTF;
	int isparity;
	
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	STRIP *stripptr;

	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;

	int chunknum,paritycountnum;
	int stripblocksize,stripnum;

	stripblocksize=stripblockgroupptr->groupsize;
	stripblockptr=stripblockgroupptr->stripblockptr;

	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunknum=chunkblockgroupptr->groupsize;

	curstripblockptr=stripblockptr;
	curchunkblockptr=chunkblockptr;
	paritycountnum=0;
	for(i=0;i<stripblocksize;i++)
	{
		stripptr=curstripblockptr->stripptr;

		chunkgroupptr=stripptr->chunklist;

		chunkptr=chunkgroupptr->ckgroup;
		chunknum=chunkgroupptr->groupsize;

		curchunkptr=chunkptr;
		for(i=0;i<chunknum;i++)
		{
			isparity=curchunkptr->isparity;//看看是不是
			if(isparity!=FALSE)
			{
				curchunkblockptr->chunkptr=curchunkptr;
				curchunkblockptr->chunkid=curchunkptr->ChunkID;
				paritycountnum++;
			}
			curchunkptr++;
			curchunkblockptr++;
		}
		curstripblockptr++;
	}
	chunkblockgroupptr->groupsize=paritycountnum;

	return TRUE;
}
//找出chunkblock对应的stripblock
int profile_chunkblock_to_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr)
{
	int i,resTF,chunknum;
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *chunkptr;
	STRIP *stripptr;

	STRIPBLOCK *stripblockptr;
	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunknum=chunkblockgroupptr->groupsize;

	curchunkblockptr=chunkblockptr;
	for(i=0;i<chunknum;i++)
	{
		chunkptr=curchunkblockptr->chunkptr;
		stripptr=chunkptr->stripptr;
		resTF=profile_stripblockgroup_strip_add(stripblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("profile","chunkblock_to_stripblock","strip can't add");
			return TRUE;
		}
		curchunkblockptr++;
	}
	return TRUE;
}

//搜索函数,将数据从全局列表中找出指针
;//在chunkpositionblockgroup找到对应strip的chunk并且进行填写，返回TRUE和FALSE
int profile_chunkblockpositiongroup_from_chunkblockpositiongroup_search_ptr(CHUNKPOSITIONBLOCKGROUP *tarchunkblockpositiongroupptr,
																			CHUNKPOSITIONBLOCKGROUP *souchunkpositionblockgroupptr,
																			STRIP *stripptr)
{
	int i;
	CHUNKPOSITIONBLOCK *tarchunkpositionblockptr,*curtarchunkpositionblockptr;
	CHUNK *chunkptr;
	STRIP *curstripptr;
	int tarchunknum;

	CHUNKPOSITIONBLOCK *souchunkpositionblockptr,*cursouchunkpositionblockptr;
	int souchunknum;

	tarchunkpositionblockptr=tarchunkblockpositiongroupptr->chunkblockptr;
	tarchunkblockpositiongroupptr->groupsize=0;
	tarchunknum=0;

	souchunkpositionblockptr=souchunkpositionblockgroupptr->chunkblockptr;
	souchunknum=souchunkpositionblockgroupptr->groupsize;

	cursouchunkpositionblockptr=souchunkpositionblockptr;
	curtarchunkpositionblockptr=tarchunkpositionblockptr;
	for(i=0;i<souchunknum;i++)
	{
		chunkptr=cursouchunkpositionblockptr->chunkptr;
		curstripptr=chunkptr->stripptr;
		if(curstripptr==stripptr)
		{
			
			curtarchunkpositionblockptr->chunkindex=cursouchunkpositionblockptr->chunkindex;
			curtarchunkpositionblockptr->stripsectindex=cursouchunkpositionblockptr->stripsectindex;

			curtarchunkpositionblockptr->chunkid=cursouchunkpositionblockptr->chunkid;
			curtarchunkpositionblockptr->chunkptr=cursouchunkpositionblockptr->chunkptr;

			curtarchunkpositionblockptr++;
			tarchunknum++;
		}
		cursouchunkpositionblockptr++;
	}
	tarchunkblockpositiongroupptr->chunkblockptr=tarchunkpositionblockptr;
	tarchunkblockpositiongroupptr->groupsize=tarchunknum;
	return TRUE;
}
//找到相应的strip的数据
int profile_chunkblockstripgroup_search_ptr(CHUNKBLOCKSTRIPGROUP *chunkblockstripgroupptr,STRIP *stripptr)
{
	CHUNKBLOCKSTRIP *chunkblockstripptr,*curchunkblockstripptr;
	STRIP *curstripptr;
	int i,stripnum;

	chunkblockstripptr=chunkblockstripgroupptr->chunkblockstripptr;
	stripnum=chunkblockstripgroupptr->groupsize;

	curchunkblockstripptr=chunkblockstripptr;
	for(i=0;i<stripnum;i++)
	{
		curstripptr=chunkblockstripptr->stripptr;
		if(curstripptr==stripptr)
		{
			return i;
		}
		curchunkblockstripptr++;
	}
	return PFALSE;
}
//找stripptr的指针数据位置，没找到返回-1
int profile_stripblockgroup_search_ptr(STRIPBLOCKGROUP *stripblockgroupptr,STRIP *stripptr)
{
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	STRIP *curstripptr;
	int i,stripblocksize;

	stripblockptr=stripblockgroupptr->stripblockptr;
	stripblocksize=stripblockgroupptr->groupsize;

	curstripblockptr=stripblockptr;
	for(i=0;i<stripblocksize;i++)
	{
		curstripptr=curstripblockptr->stripptr;
		if(stripptr==curstripptr)
		{
			return i;
		}
		curstripblockptr++;
	}
	return PFALSE;//没找到位置
}

//找stripptr的指针数据位置，没找到返回-1
int profile_stripsectblockgroup_search_ptr(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *stripsectptr)
{
	STRIPSECTBLOCK *strsetblockptr,*curstrsetblockptr;
	STRIPSECT *curstrsetptr;
	int i,strsetblocksize;

	strsetblockptr=strsetblockgroupptr->stripsectblockptr;
	strsetblocksize=strsetblockgroupptr->groupsize;

	curstrsetblockptr=strsetblockptr;
	for(i=0;i<strsetblocksize;i++)
	{
		curstrsetptr=curstrsetblockptr->stripsectptr;
		if(curstrsetptr==stripsectptr)
		{
			return i;
		}
		curstrsetblockptr++;
	}
	return PFALSE;
}
//找chunkptr的指针数据位置，没找到返回-1
int profile_chunkblockgroup_search_ptr(CHUNKBLOCKGROUP *chunkblockgroupptr,CHUNK *chunkptr)
{
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *curchunkptr;
	int i,chunkblocksize;

	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunkblocksize=chunkblockgroupptr->groupsize;

	curchunkblockptr=chunkblockptr;
	for(i=0;i<chunkblocksize;i++)
	{
		curchunkptr=chunkblockptr->chunkptr;
		if(chunkptr==curchunkptr)
		{
			return i;
		}
		chunkblockptr++;
	}
	return PFALSE;//没找到位置
}

int profile_region_filemeta_add(REGION *regionptr,FILEMETA *filemetaptr)
{
	//获取数据
	FILEMETABLOCKGROUP *filemetablockgroupptr;
	FILEMETABLOCK *tarfilemetablockptr,*curtarfilemetablockptr;
	UINT64 *fileidlist;
	int filenum;

	filemetablockgroupptr=regionptr->filemetalist;
	fileidlist=regionptr->fileid;
	filenum=regionptr->filenum;
	tarfilemetablockptr=filemetablockgroupptr->filemetablockptr;
	tarfilemetablockptr=ralloc(FILEMETABLOCK,filenum+1,tarfilemetablockptr);
	if(tarfilemetablockptr==NULL)
	{
		show_error("profile","region_filemeta_add","No memory");
		return FALSE;

	}
	curtarfilemetablockptr=tarfilemetablockptr+filenum;

	curtarfilemetablockptr->filemetaptr=filemetaptr;
	curtarfilemetablockptr->FileID=filemetaptr->FileID;

	filemetablockgroupptr->filemetablockptr=tarfilemetablockptr;//将数据赋值回去

	fileidlist=ralloc(UINT64,filenum+1,fileidlist);
	if(fileidlist==NULL)
	{
		show_error("profile","region_filemeta_add","No memory");
		return FALSE;
	}
	fileidlist[filenum]=filemetaptr->FileID;
	regionptr->fileid=fileidlist;

	filenum=filenum+1;

	filemetablockgroupptr->groupsize=filenum;
	regionptr->filenum=filenum;
	return TRUE;
}

int profile_stripblockstripgroup_chunk_add(CHUNKBLOCKSTRIPGROUP *chunkblockstripgroupptr,CHUNK *chunkptr,STRIP *stripptr)
{
	CHUNKBLOCKSTRIP *chunkblockstrippptr,*curchunkblockstrippptr;
	
	//STRIP *curstripptr;
	int stripnum,stripindex,resTF;

	CHUNKBLOCKGROUP *chunkblockgroupptr;
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	//CHUNK *curchunkptr;
	int chunknum;

	chunkblockstrippptr=chunkblockstripgroupptr->chunkblockstripptr;
	stripnum=chunkblockstripgroupptr->groupsize;

	chunkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(chunkblockgroupptr==NULL)
	{
		show_error("profile","stripblockstripgroup_chunk_add","No memory");
		return FALSE;
	}

	if(chunkblockstrippptr==NULL)
	{
		show_error("profile","stripblockstripgroup_chunk_add","chunkblockstrippptr==NULL");
		return FALSE;
	}

	if(stripnum==0)
	{
		chunkblockstrippptr->stripptr=stripptr;
		chunkblockstrippptr->stripid=stripptr->StripID;
		chunkblockstrippptr->chunknum=0;
		//chunkblockstrippptr->datachunkblockptr=NULL;
	}
	else
	{
		//计算
		stripindex=profile_chunkblockstripgroup_search_ptr(chunkblockstripgroupptr,stripptr);
		if(stripindex==PFALSE)
		{
			stripindex=stripnum;
		}
		curchunkblockstrippptr=chunkblockstrippptr+stripindex;//当前
	}

	chunkblockptr=curchunkblockstrippptr->datachunkblockptr;
	chunknum=chunkblockstrippptr->chunknum;
	
	chunkblockgroupptr->chunkblockptr=chunkblockptr;
	chunkblockgroupptr->groupsize=chunknum;
	//将chunk data数据写入
	resTF=profile_chunkblockgroup_chunk_add(chunkblockgroupptr,chunkptr);
	if(resTF==FALSE)
	{
		show_error("profile","stripblockstripgroup_chunk_add","chunk data can't add");
		return FALSE;

	}	
	free(chunkblockgroupptr);
	return TRUE;
}


//在stripblockgroupptr中加入一个strip
int profile_stripblockgroup_strip_add(STRIPBLOCKGROUP *stripblockgroupptr,STRIP *stripptr)
{
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	int stripblocksize;
	int pindex;

	stripblockptr=stripblockgroupptr->stripblockptr;
	stripblocksize=stripblockgroupptr->groupsize;
	//开始是准备临时追加空间但是发现不稳定因此改为预先分配空间
	if(stripblockptr==NULL)
	{
		show_error("profile","stripblockgroup_strip_add","stripblockptr==NULL");
		return FALSE;
	}

	if(stripblocksize==0)//说明第一次
	{
		//当前数据需要生成数据
		/*stripblockptr=talloc(STRIPBLOCK,1);
		if(stripblockptr==NULL)
		{
			show_error("profile","stripblockgroup_strip_add","No memory");
			return FALSE;
		}
		stripblockptr->stripptr=stripptr;
		stripblockptr->stripid=stripptr->StripID;*/
		stripblockptr->stripptr=stripptr;
		stripblockptr->stripid=stripptr->StripID;

		stripblockgroupptr->stripblockptr=stripblockptr;
		stripblockgroupptr->groupsize=1;
		//return TRUE;
	}
	else
	{
		//说明是有空间了
		//第一步判断是否存在
		pindex=profile_stripblockgroup_search_ptr(stripblockgroupptr,stripptr);
		if(pindex==PFALSE)//如果没有找到就添加
		{
			 /*stripblockptr=ralloc(STRIPBLOCK,stripblocksize+1,stripblockptr);//追加空间
			 if(stripblockptr==NULL)
			 {
				 show_error("profile","stripblockgroup_strip_add","No memory");
				 return FALSE;
			 }*/
			 curstripblockptr=stripblockptr+stripblocksize;
			 stripblocksize=stripblocksize+1;

			 curstripblockptr->stripptr=stripptr;
			 curstripblockptr->stripid=stripptr->StripID;

			 stripblockgroupptr->stripblockptr=stripblockptr;
			 stripblockgroupptr->groupsize=stripblocksize;
		}
	}
	return TRUE;
}
//在stripsectblockgroupptr中加入一个stripsect
int profile_stripsetblockgroup_stripsect_add(STRIPSECTBLOCKGROUP *stripsectblockgroupptr,STRIPSECT *stripsectptr)
{
	STRIPSECTBLOCK *strsetblockptr,*curstrsetblockptr;
	int strsetblocksize;
	int pindex;

	strsetblockptr=stripsectblockgroupptr->stripsectblockptr;
	strsetblocksize=stripsectblockgroupptr->groupsize;
	//开始是准备临时追加空间但是发现不稳定因此改为预先分配空间
	if(strsetblockptr==NULL)
	{
		show_error("profile","stripsectblockgroup_strip_add","stripblockptr==NULL");
		return FALSE;
	}
	if(strsetblocksize==0)//说明第一次
	{
		//当前数据需要生成数据
		/*stripblockptr=talloc(STRIPBLOCK,1);
		if(stripblockptr==NULL)
		{
			show_error("profile","stripblockgroup_strip_add","No memory");
			return FALSE;
		}
		stripblockptr->stripptr=stripptr;
		stripblockptr->stripid=stripptr->StripID;*/
		strsetblockptr->stripsectptr=stripsectptr;
		strsetblockptr->stripsectid=stripsectptr->StripsectID;

		stripsectblockgroupptr->stripsectblockptr=strsetblockptr;
		stripsectblockgroupptr->groupsize=1;
		//return TRUE;
	}
	else
	{
		pindex=profile_stripsectblockgroup_search_ptr(stripsectblockgroupptr,stripsectptr);
		if(pindex==PFALSE)//
		{
			/*stripblockptr=ralloc(STRIPBLOCK,stripblocksize+1,stripblockptr);//追加空间
			 if(stripblockptr==NULL)
			 {
				 show_error("profile","stripblockgroup_strip_add","No memory");
				 return FALSE;
			 }*/
			 curstrsetblockptr=strsetblockptr+strsetblocksize;
			 strsetblocksize=strsetblocksize+1;

			 curstrsetblockptr->stripsectptr=stripsectptr;
			 curstrsetblockptr->stripsectid=stripsectptr->StripsectID;

			 stripsectblockgroupptr->stripsectblockptr=strsetblockptr;
			 stripsectblockgroupptr->groupsize=strsetblocksize;
		}
	}
	return TRUE;
}

//在chunkblockgroupptr中加入一个chunk
int profile_chunkblockgroup_chunk_add(CHUNKBLOCKGROUP *chunkblockgroupptr,CHUNK *chunkptr)
{
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	int chunkblocksize;
	int pindex;

	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunkblocksize=chunkblockgroupptr->groupsize;
	//开始是准备临时追加空间但是发现不稳定因此改为预先分配空间
	if(chunkblockptr==NULL)
	{
		show_error("profile","chunkblockgroup_strip_add","stripblockptr==NULL");
		return FALSE;
	}

	if(chunkblocksize==0)//说明第一次
	{
		//当前数据需要生成数据
		/*chunkblockptr=talloc(CHUNKBLOCK,1);
		if(chunkblockptr==NULL)
		{
			show_error("profile","chunkblockgroup_chunk_add","No memory");
			return FALSE;
		}
		chunkblockptr->chunkptr=chunkptr;
		chunkblockptr->chunkid=chunkptr->ChunkID;*/

		chunkblockptr->chunkptr=chunkptr;
		chunkblockptr->chunkid=chunkptr->ChunkID;

		chunkblockgroupptr->chunkblockptr=chunkblockptr;
		chunkblockgroupptr->groupsize=1;
		//return TRUE;
	}
	else
	{
		//说明是有空间了
		//第一步判断是否存在
		pindex=profile_chunkblockgroup_search_ptr(chunkblockgroupptr,chunkptr);
		if(pindex==PFALSE)//如果没有找到就添加
		{
			/* chunkblockptr=ralloc(CHUNKBLOCK,chunkblocksize+1,chunkblockptr);//追加空间
			 if(chunkblockptr==NULL)
			 {
				 show_error("profile","chunkblockgroup_chunk_add","No memory");
				 return FALSE;
			 }*/
			 curchunkblockptr=chunkblockptr+chunkblocksize;
			 chunkblocksize=chunkblocksize+1;

			 curchunkblockptr->chunkptr=chunkptr;
			 curchunkblockptr->chunkid=chunkptr->ChunkID;

			 chunkblockgroupptr->chunkblockptr=chunkblockptr;
			 chunkblockgroupptr->groupsize=chunkblocksize;
		}
	}
	return TRUE;
}

//将存储信息进行设置
int profile_set_file_storage_information(FILEINF *fileinfptr,
												CHUNKBLOCKGROUP *chunkblockgroupptr,STRIPSECTBLOCKGROUP *stripsectblockgroupptr,
												STRIPBLOCKGROUP *stripblockgroupptr,REGION *regionptr,
												CHUNKPATH *chunkpathlist,FILEMETA *filemetaptr
												)
{
	int i;

	DEVICEBLOCK *deviceblockptr;
	UINT64 *deviceidlist;
	int devicenum;

	DISKBLOCK *diskblockptr;
	UINT64 *diskidlist;
	int disknum;

	CHUNKBLOCK *chunkblockptr,*curchunkblock;
	//CHUNK *chunkptr;
	UINT64 *chunkidlist;
	int chunknum;

	STRIPSECTBLOCK *strsetblockptr,*curstrsetblockptr;
	//STRIPSECT *strsetptr;
	UINT64 *strsetidlist;
	int strsetnum;

	STRIPBLOCK *stripblockptr,*curstripblockptr;
	//STRIP *stripptr;
	UINT64 *stripidlist;
	int stripnum;

	UINT64 regionid;
	UINT64 fileid;
	//准备数据
	deviceblockptr=regionptr->devicelist;
	deviceidlist=regionptr->deviceid;
	devicenum=regionptr->devicenum;

	diskblockptr=regionptr->disklist;
	diskidlist=regionptr->diskid;
	disknum=regionptr->disknum;


	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunknum=chunkblockgroupptr->groupsize;

	strsetblockptr=stripsectblockgroupptr->stripsectblockptr;
	strsetnum=stripsectblockgroupptr->groupsize;

	stripblockptr=stripblockgroupptr->stripblockptr;
	stripnum=stripblockgroupptr->groupsize;

	//进入id赋值阶段
	fileid=filemetaptr->FileID;
	regionid=regionptr->RegionID;

	if(fileinfptr==NULL)
	{
		show_error("profile","set_file_storage_information","fileinfptr");
		return FALSE;
	}

	chunkidlist=talloc(UINT64,chunknum);
	if(chunkidlist==NULL)
	{
		show_error("profile","set_file_storage_information","No memory");
		return FALSE;
	}
	strsetidlist=talloc(UINT64,strsetnum);
	if(strsetidlist==NULL)
	{
		show_error("profile","set_file_storage_information","No memory");
		return FALSE;
	}

	stripidlist=talloc(UINT64,stripnum);
	if(stripidlist==NULL)
	{
		show_error("profile","set_file_storage_information","No memory");
		return FALSE;
	}

	//创建id列表

	curchunkblock=chunkblockptr;
	for(i=0;i<chunknum;i++)
	{
		chunkidlist[i]=curchunkblock->chunkid;
		curchunkblock++;
	}

	curstrsetblockptr=strsetblockptr;
	for(i=0;i<strsetnum;i++)
	{
		strsetidlist[i]=curstrsetblockptr->stripsectid;
		curstrsetblockptr++;
	}

	curstripblockptr=stripblockptr;
	for(i=0;i<stripnum;i++)
	{
		stripidlist[i]=curstripblockptr->stripid;
		curstripblockptr++;
	}

	
	//万事具备，开始赋值
	//设定FILEINF数据值
	GLOBAL_set_FILEINF_data(fileinfptr,fileid,chunkidlist,filemetaptr,
								   chunkpathlist,chunkblockptr,chunknum,//chun列表
								   regionptr,regionid,//region指针
								   deviceblockptr,deviceidlist,devicenum,//设备列表
								   diskblockptr,diskidlist,disknum,//存储器列表
								   stripblockptr,stripidlist,stripnum,//条带列表
								   strsetblockptr,strsetidlist,strsetnum//条带区域列表
								   );
	//fileinfptr->devicelist;
	//fileinfptr->chkpath=chunkpathlist;
	return TRUE;
}
//计算文件与上一级指针
int profile_set_parent_filemeta_ptr(FILEMETA *filemetaptr)
{
	FILEMETA *perantptr;
	FILEMETABLOCK *subfilelist,*cursubfilelist;
	UINT64 *subidlist;
	int subfilenum;

	perantptr=filemetaptr->parentptr;
	subfilelist=perantptr->subfilelist;//上一级文件夹的子文件
	subidlist=perantptr->subfileidlist;
	subfilenum=perantptr->subfilenum;
	//如果是空文件夹开空间存
	if((subfilelist==NULL)||(subfilenum==0))//开一个4k的空间
	{
		subfilelist=talloc(FILEMETABLOCK,chksize_KB(4));//开一个4k的空间
		if(subfilelist==NULL)
		{
			show_error("profile","set_parent_filemeta_ptr","No memory");
			return FALSE;
		}
		subidlist=talloc(UINT64,chksize_KB(4));//开一个4k的空间
		if(subidlist==NULL)
		{
			show_error("profile","set_parent_filemeta_ptr","No memory");
			return FALSE;
		}
		subfilelist->filemetaptr=filemetaptr;
		subfilelist->FileID=filemetaptr->FileID;

		subidlist[0]=filemetaptr->FileID;
		//将数值进行赋值
		perantptr->subfilenum=1;
		perantptr->subfileidlist=subidlist;
		perantptr->subfilelist=subfilelist;
	}
	else
	{
		cursubfilelist=subfilelist+subfilenum;

		cursubfilelist->filemetaptr=filemetaptr;
		cursubfilelist->FileID=filemetaptr->FileID;

		subidlist[subfilenum]=filemetaptr->FileID;

		perantptr->subfilenum=subfilenum+1;//定位到下一个位置
	}
	return TRUE;
}



//搜索函数,将数据从全局列表中找出指针
int profile_filemeta_filemetablock_search(FILEMETABLOCK *filemetablockptr,UINT64 *fileidlist,int filenum,FILEMETABLOCKGROUP *filemetablockgroupptr)
{
	int i,j;
	FILEMETABLOCK *curfilemetablockptr,*soufilemetablockptr,*cursoufilemetablockptr;
	int fileblocknum;
	UINT64 curfilemetaid,soufilemetaid;

	soufilemetablockptr=filemetablockgroupptr->filemetablockptr;
	fileblocknum=filemetablockgroupptr->groupsize;

	curfilemetablockptr=filemetablockptr;
	for(i=0;i<filenum;i++)
	{
		curfilemetaid=fileidlist[i];
		cursoufilemetablockptr=soufilemetablockptr;
		for(i=0;i<fileblocknum;i++)
		{
			soufilemetaid=cursoufilemetablockptr->FileID;
			if(soufilemetaid==curfilemetaid)
			{
				curfilemetablockptr->FileID=cursoufilemetablockptr->FileID;
				curfilemetablockptr->filemetaptr=cursoufilemetablockptr->filemetaptr;
				break;
			}
			cursoufilemetablockptr++;
		}
		curfilemetablockptr++;
	}
	return TRUE;
}


int profile_chunk_chunkpath_search(CHUNKBLOCK *chunkblockptr,UINT64 *chunkidlist,CHUNKPATH *chkpathptr,int chunknum)
{
	int i,j;
	UINT64 curchunkid,tarchunkid;
	CHUNKBLOCK *curchunkblockptr;
	CHUNKPATH *curchkpathptr;

	curchunkblockptr=chunkblockptr;
	for(i=0;i<chunknum;i++)
	{
		curchunkid=chunkidlist[i];
		curchkpathptr=chkpathptr;
		for(j=0;j<chunknum;j++)
		{
			tarchunkid=curchkpathptr->chunkid;
			if(tarchunkid==curchunkid)
			{
				curchunkblockptr->chunkptr=curchkpathptr->chunkptr;
				curchunkblockptr->chunkid=curchunkid;
				break;
			}
			curchkpathptr++;
		}
		curchunkblockptr++;
	}
	return TRUE;
}
int profile_stripsect_chunkpath_search(STRIPSECTBLOCK *stripsectblockptr,UINT64 *stripsectidlist,int stripsectnum,CHUNKPATH *chkpathptr,int chunknum)
{
	int i,j;
	UINT64 curstrsetid,tarstrsetid;
	STRIPSECTBLOCK *curstrsetblockptr;
	CHUNKPATH *curchkpathptr;

	curstrsetblockptr=stripsectblockptr;
	for(i=0;i<stripsectnum;i++)
	{
		curstrsetid=stripsectidlist[i];
		curchkpathptr=chkpathptr;
		for(j=0;j<chunknum;j++)
		{
			tarstrsetid=curchkpathptr->stripsectid;
			if(tarstrsetid==curstrsetid)
			{
				curstrsetblockptr->stripsectptr=curchkpathptr->stripsectptr;
				curstrsetblockptr->stripsectid=curchkpathptr->stripsectid;
				break;
			}
			curchkpathptr++;
		}
		curstrsetblockptr++;
	}
	return TRUE;
}
int profile_strip_chunkpath_search(STRIPBLOCK *stripblockptr,UINT64 *stripidlist,int stripnum,CHUNKPATH *chkpathptr,int chunknum)
{
	int i,j;
	UINT64 curstripid,tarstripid;
	STRIPBLOCK *curstripblockptr;
	CHUNKPATH *curchkpathptr;

	curstripblockptr=stripblockptr;
	for(i=0;i<stripnum;i++)
	{
		curstripid=stripidlist[i];
		curchkpathptr=chkpathptr;
		for(j=0;j<chunknum;j++)
		{
			tarstripid=curchkpathptr->stripid;
			if(tarstripid==curstripid)
			{
				curstripblockptr->stripptr=curchkpathptr->stripptr;
				curstripblockptr->stripid=curchkpathptr->stripid;
				break;
			}
			curchkpathptr++;
		}
		curstripblockptr++;
	}
	return TRUE;
}


USERPROFILE *profile_get_usergroup_ptr(UINT64 userid,USERGROUP *usergroupptr)
{
	int i;
	USERPROFILE *userprofileptr,*curuserprofileptr;
	int userpronum;
	UINT64 curuserid;
	userprofileptr=usergroupptr->userlist;
	userpronum=usergroupptr->groupsize;

	curuserprofileptr=userprofileptr;
		
	for(i=0;i<userpronum;i++)
	{
		curuserid=curuserprofileptr->UserID;
		if(curuserid==userid)
		{
			//curfilemetaptr->userinf=curuserprofileptr;
			return curuserprofileptr;
			break;
		}
		curuserprofileptr++;
	}
	return NULL;
}
FILEMETA *profile_get_filemetablock_ptr(UINT64 fileid,FILEMETABLOCKGROUP *filemetablockgroupptr)
{
	int i;
	FILEMETABLOCK *filemetablockptr,*curfilemetablockptr;
	FILEMETA *filemetaptr;
	int filenum;
	UINT64 curfileid;

	filemetablockptr=filemetablockgroupptr->filemetablockptr;
	filenum=filemetablockgroupptr->groupsize;

	curfilemetablockptr=filemetablockptr;

	for(i=0;i<filenum;i++)
	{
		curfileid=curfilemetablockptr->FileID;
		if(curfileid==fileid)
		{
			filemetaptr=curfilemetablockptr->filemetaptr;
			return filemetaptr;
		}
		curfilemetablockptr++;
	}
	return NULL;
}

CHUNK *profile_get_chunkblock_ptr(UINT64 chunkid,CHUNKBLOCKGROUP *chunkblockgroupptr)
{
	int i;
	UINT64 curchunkid;
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *curchunkptr;
	int chunknum;

	curchunkptr=NULL;

	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunknum=chunkblockgroupptr->groupsize;

	curchunkblockptr=chunkblockptr;
	for(i=0;i<chunknum;i++)
	{
		curchunkptr=curchunkblockptr->chunkptr;
		curchunkid=curchunkblockptr->chunkid;
		if(curchunkid==chunkid)
		{
			return curchunkptr;
		}
		curchunkblockptr++;
	}
	return NULL;
}

CHUNK *profile_get_chunkposition_ptr(int stripsectindex,int chunkindex,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr)
{
	int i;
	CHUNKPOSITIONBLOCK *chunkpoistionblockptr;
	int chunknum;
	int strsetindex,chkindex;
	CHUNK *chunkptr;

	chunkpoistionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	chunknum=chunkpositionblockgroupptr->groupsize;
	chunkptr=NULL;
	for(i=0;i<chunknum;i++)
	{
		strsetindex=chunkpoistionblockptr->stripsectindex;
		chkindex=chunkpoistionblockptr->chunkindex;
		if((strsetindex==stripsectindex)&&(chkindex==chunkindex))
		{
			chunkptr=chunkpoistionblockptr->chunkptr;
			return chunkptr;
		}
		chunkpoistionblockptr++;
	}
	return chunkptr;
}
int profile_search_chunkposition_id(int stripsectindex,int chunkindex,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr)
{
	int i;
	CHUNKPOSITIONBLOCK *chunkpositionblockptr;
	int chunknum;
	int position;
	int strsetindex,chkindex;

	position=PFALSE;
	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	chunknum=chunkpositionblockgroupptr->groupsize;
	for(i=0;i<chunknum;i++)
	{	
		strsetindex=chunkpositionblockptr->stripsectindex;
		chkindex=chunkpositionblockptr->chunkindex;
		if((strsetindex==stripsectindex)&&(chkindex==chunkindex))
		{
			position=i;
			return position;
		}
		chunkpositionblockptr++;//找到数据
	}
	return position;
	//return TRUE;
}

UINT64 profile_get_region_id(char *filepath)//生成id号
{
	int strindex,i;
	char curchar;
	char curfilenamepart[100];
	UINT64 regionindex;
	strindex=6;
	i=0;
	curchar=filepath[strindex];
	curfilenamepart[i]=curchar;
	i++;
	strindex++;
	curchar=filepath[strindex];
	while(curchar!='\\')
	{
		curchar=filepath[strindex];
		curfilenamepart[i]=curchar;
		i++;
		strindex++;
	}
	curfilenamepart[i]='\0';//补上尾部标记
	STRTOINT64(curfilenamepart,regionindex);//将字符串转化为数值
	return regionindex;
}

REGION *profile_region_search_ptr(UINT64 regionid)
{
	REGIONGROUP *regiongroupptr;
	REGION *regionptr=NULL;

	int i,regiongroupsize;
	UINT64 currentid;

	regiongroupptr=get_state_gloregiongroup_PTR();
	regionptr=regiongroupptr->regiongroup;
	regiongroupsize=regiongroupptr->groupsize;

	for(i=0;i<regiongroupsize;i++)
	{
		currentid=regionptr->RegionID;
		if(currentid==regionid)
		{
			return regionptr;
		}
		regionptr++;
	}
	return NULL;
}
//找到当前id列表中device指针
int profile_device_search(DEVICEBLOCK *deviceblockptr,UINT64 *deviceidlist,int devicenum)
{
	int i,j,glodevicenum;
	DEVICEGROUP *devicegrouplist;
	DEVICE *deviceptr;
	UINT64 currentid;
	devicegrouplist=get_state_glodevicegroup_PTR();
	deviceptr=devicegrouplist->devicegroup;
	glodevicenum=devicegrouplist->groupsize;
	for(i=0;i<devicenum;i++)//找到所有设备
	{
		for(j=0;j<glodevicenum;j++)
		{
			currentid=deviceptr->DeviceID;
			if(currentid==deviceidlist[i])
			{
				deviceblockptr->deviceptr=deviceptr;
				deviceblockptr->deviceid=currentid;
			}
			deviceptr++;
		}
	}
	return TRUE;
}
//找到当前id列表中的disk指针
int profile_disk_search(DISKBLOCK *diskblockptr,UINT64 *diskidlsit,int disknum)
{
	int i,j,glodisknum;
	DISKGROUP *diskgrouplist;
	DISK *diskptr;
	UINT64 currentid;
	diskgrouplist=get_state_glodiskgroup_PTR();
	diskptr=diskgrouplist->diskgroup;
	glodisknum=diskgrouplist->groupsize;
	for(i=0;i<disknum;i++)
	{
		for(j=0;j<glodisknum;j++)
		{
			currentid=diskptr->DiskID;
			if(currentid==diskidlsit[i])
			{
				diskblockptr->diskptr=diskptr;
				diskblockptr->diskid=currentid;
			}
			diskptr++;
		}
	}
	return TRUE;
}
//返回region号
int profile_region_search(REGION *regionptr)
{
	//regiongroup
	REGIONGROUP *gloreggroupptr;
	REGION *gloregionptr;
	int i,gloregsize;
	int regionarrayid;
	//获取全局regiongroup
	gloreggroupptr=get_state_gloregiongroup_PTR();
	gloregionptr=gloreggroupptr->regiongroup;
	gloregsize=gloreggroupptr->groupsize;
	//计算当前位置
	for(i=0;i<gloregsize;i++)//计算当前位置
	{
		regionarrayid=i;
		if(gloregionptr==regionptr)
		{
			return regionarrayid;
		}
		gloregionptr++;//找下一个指针
	}
	return PFALSE;
}
//找到当前列表中deviceid
DEVICE *profile_device_ptr_search(UINT64 deviceid,DEVICEBLOCK *deviceblockptr,int devicenum)
{
	int i;
	DEVICEBLOCK *curdeviceblockptr;
	DEVICE *deviceptr=NULL;
	curdeviceblockptr=deviceblockptr;
	for(i=0;i<devicenum;i++)
	{
		if(curdeviceblockptr->deviceid==deviceid)
		{
			deviceptr=curdeviceblockptr->deviceptr;
			break;
		}
		curdeviceblockptr++;
	}
	return deviceptr;
}
//找到当前列表中deviceid
DISK *profile_disk_ptr_search(UINT64 diskid,DISKBLOCK *diskblockptr,int disknum)
{
	int i;
	DISKBLOCK *curdiskblockptr;
	DISK *diskptr=NULL;
	curdiskblockptr=diskblockptr;
	for(i=0;i<disknum;i++)
	{
		if(curdiskblockptr->diskid==diskid)
		{
			diskptr=curdiskblockptr->diskptr;
			break;
		}
		curdiskblockptr++;
	}
	return diskptr;
}

//根据regionid显示数据
int profile_region_info_ID(UINT64 regionid)
{
	//显示region信息
	REGIONGROUP *reggroupptr;
	REGION *regionptr;
	int i,groupsize;
	UINT64 currentid;
	reggroupptr=get_state_gloregiongroup_PTR();
	groupsize=reggroupptr->groupsize;
	regionptr=reggroupptr->regiongroup;
	for(i=0;i<groupsize;i++)
	{
		currentid=regionptr->RegionID;
		if(currentid==regionid)
		{
			break;//找到就走
		}
		regionptr++;
	}
	//找到regionptr显示
	profile_region_info(regionptr);
	return TRUE;
}
//根据region指针显示数据
int profile_region_info(REGION *regionptr)
{
	//显示region信息
	UINT64 regionid;
	CODEPARA *codepara;
	UINT64 *fileid,*diskid,*deviceid,*stripid,rootfileid,totalsize,chunknum,stripsectnum,filenum;//不同的全局
	int i,codetype,disknum,devicenum,stripnum,storestate;
	STRIPDES *strdes;
	//开始赋值
	regionid=regionptr->RegionID;

	codetype=regionptr->codetype;
	codepara=regionptr->codepara;
	totalsize=regionptr->totalsize;

	filenum=regionptr->filenum;
	fileid=regionptr->fileid;

	disknum=regionptr->disknum;
	diskid=regionptr->diskid;

	devicenum=regionptr->devicenum;
	deviceid=regionptr->deviceid;

	strdes=regionptr->strdes;

	stripnum=regionptr->stripnum;
	stripid=regionptr->stripid;

	chunknum=regionptr->chunknum;
	stripsectnum=regionptr->stripsectnum;

	rootfileid=regionptr->rootfileid;
	storestate=regionptr->storestate;
	//开始输出
	printf("region id:%I64d\n",regionid);
	//开始输出内容
	printf("code type(code):%d,the parameter list:",codetype);
	printf("data disk num:%d\n",codepara->datanum);
	printf("code disk num:%d\n",codepara->codenum);
	printf("total disk num:%d\n",codepara->totnum);
	printf("provider num:%d\n",codepara->pronum);
	printf("sector number:%d\n",codepara->sectornum);
	//总大小
	printf("total size of region:%I64d\n",totalsize);
	printf("there are %d files,file id list:\n",filenum);
	for(i=0;i<filenum;i++)
	{
		printf("%I64d\n",fileid[i]);
	}
	printf("there are %d disks,disk id list:\n",disknum);
	for(i=0;i<disknum;i++)
	{
		printf("%I64d\n",diskid[i]);
	}
	printf("there are %d devices,device id list:\n",devicenum);
	for(i=0;i<devicenum;i++)
	{
		printf("%I64d\n",deviceid[i]);
	}
	printf("stripsect has %d chunks,each chunk is %d bytes\n",strdes->chunknum,strdes->chunksize);
	printf("there are %d strips,strip id list:\n",stripnum);
	for(i=0;i<stripnum;i++)
	{
		printf("%I64d\n",stripid[i]);
	}

	printf("total chunk number:%I64d\n",chunknum);
	printf("total stripsect number:%I64d\n",stripsectnum);

	printf("root file id:%I64d\n",rootfileid);
	printf("region state(countnum):%d\n",storestate);
	return TRUE;
}
//根据strip指针显示数据
int profile_strip_info(STRIP *stripptr)
{
	//显示strip信息
	UINT64 stripid,*diskid,*deviceid,*strsetid,*chunkid,regionid;
	int i,disknum,devicenum,strsetnum,chunknum,storestate;
	STRIPDES *strdes;
	stripid=stripptr->StripID;
	
	strdes=stripptr->strdes;

	disknum=stripptr->disknum;
	diskid=stripptr->diskid;

	devicenum=stripptr->devicenum;
	deviceid=stripptr->deviceid;

	strsetnum=stripptr->strsetnum;
	strsetid=stripptr->stripsectid;

	chunknum=stripptr->chunknum;
	chunkid=stripptr->chunkid;

	regionid=stripptr->regionid;

	storestate=stripptr->storestate;
	//开始显示
	printf("strip id:%I64d\n",stripid);
	//printf("strip description:\n");
	printf("chunknum of each stripsect:%d\n",strdes->chunknum);
	printf("chunksize is:%d\n",strdes->chunksize);
	printf("there are %d disks,disk id list:\n",disknum);
	for(i=0;i<disknum;i++)//由于des中内容与strip中相同写一个分
	{
		printf("%I64d\n",diskid[i]);
	}
	printf("there are %d devices,device id list:\n",devicenum);
	for(i=0;i<devicenum;i++)
	{
		printf("%I64d\n",deviceid[i]);
	}
	printf("there are %d stripsects,stripsect id list:\n",strsetnum);
	for(i=0;i<strsetnum;i++)
	{
		printf("%I64d\n",strsetid[i]);
	}
	printf("there are %d chunks,chunk id list:\n",chunknum);
	for(i=0;i<chunknum;i++)
	{
		printf("%I64d\n",chunkid[i]);
	}
	printf("region id:%I64d\n",regionid);
	printf("strip state(countnum):%d\n",storestate);
	return TRUE;
}
//根据stripsect指针显示数据
int profile_stripsect_info(STRIPSECT *stripsectptr)
{
	int i,chunksize;
	//UINT64 regionid,stripid,strsectid;//各种实体的编号
	UINT64 strsetid;//strset的编号
	//相关元数据信息
	UINT64 *chunkid;//当前chunk的指针组
	int chunknum;//chunk数量
	int isparity;//校验

	UINT64 regionid;//region编号
	UINT64 stripid;//strip编号
	UINT64 diskid;//当前存储器编号
	UINT64 deviceid;//设备编号
	char *filename;//文件名
	char *filepath;//文件路径
	int storestate; //当前存储状态
	//开始赋值
	strsetid=stripsectptr->StripsectID;

	isparity=stripsectptr->isparity;
	chunksize=stripsectptr->chunksize;
	chunknum=stripsectptr->chunknum;

	chunkid=stripsectptr->chunkid;
	regionid=stripsectptr->regionid;
	stripid=stripsectptr->stripid;
	diskid=stripsectptr->diskid;
	deviceid=stripsectptr->deviceid;

	filename=stripsectptr->filename;
	filepath=stripsectptr->filepath;

	storestate=stripsectptr->storestate;

	//显示stripsect信息
	printf("the stripset id: %I64d\n",strsetid);//当前stripsect的编号

	printf("the stripsect is parity(0:FALSE,1:TRUE):%d\n",isparity);//当前是不是校验stripsect
	printf("the chunksize:%d\n",chunksize);//其中每一个chunk的大小
	printf("there are: %d chunks, chunk id list:\n",chunknum);
	for(i=0;i<chunknum;i++)
	{
		printf("%I64d\n",chunkid[i]);//将chunk编号输出到元数据文件中
	}
	//上层id号写入
	printf("region id:%I64d\n",regionid);
	printf("strip id:%I64d\n",stripid);
	printf("disk id:%I64d\n",diskid);
	printf("device id:%I64d\n",deviceid);

	//将数据文件路径写入
	printf("store filename:%s\n",filename);
	printf("store filepath:%s\n",filepath);
	//当前存储状态
	printf("stripsect state(countnum):%d\n",storestate);
	return TRUE;
}
//根据chunk指针显示数据
int profile_chunk_info(CHUNK *chunkptr)
{
	UINT64 chkid;//chunk编号
	//CHUNKPATH *chkpath;//路径
	UINT64 regionid,stripid,stripsectid,deviceid,diskid,fileid;//id大全
	int isparity,sizenum,storestate;
	//开始赋值
	chkid=chunkptr->ChunkID;
	isparity=chunkptr->isparity;

	sizenum=chunkptr->sizenum;
	regionid=chunkptr->regionid;
	stripid=chunkptr->stripid;
	stripsectid=chunkptr->stripsectid;
	diskid=chunkptr->diskid;
	deviceid=chunkptr->deviceid;
	fileid=chunkptr->fileid;

	storestate=chunkptr->storestate;

	//显示chunk信息
	printf("chunk id:%I64d\n",chkid);
	printf("the chunk is parity(0:FALSE,1:TRUE):%d\n",isparity);
	//路径可以不必输出
	printf("the chunk size:%d\n",sizenum);
	printf("region id:%I64d\n",regionid);
	printf("strip id:%I64d\n",stripid);
	printf("stripsect id:%I64d\n",stripsectid);
	printf("disk id:%I64d\n",diskid);
	printf("device id:%I64d\n",deviceid);
	printf("file id:%%I64d\n",fileid);
	//当前存储状态
	printf("chunk state(countnum):%d\n",storestate);
	return TRUE;
}
//根据disk指针显示数据
int profile_disk_info(DISK *diskptr)
{
	//显示disk信息
	UINT64 diskid,deviceid,volumn;
	int disktype,capability;
	UINT64 *regionid;
	int i,regionnum,storestate;
	char *diskpath;
	//开始赋值
	diskid=diskptr->DiskID;
	disktype=diskptr->DiskTYPE;

	capability=diskptr->capability;
	volumn=diskptr->volumn;

	regionnum=diskptr->regionnum;
	regionid=diskptr->regionid;

	deviceid=diskptr->deviceid;
	diskpath=diskptr->diskpath;

	storestate=diskptr->storestate;
	//开始输出
	printf("disk id:%I64d\n",diskid);
	printf("disk type(0:NORHDD,1:HIGHHD,2:SSD):%d\n",disktype);
	printf("disk capability(0:NONCAP,1:LOWCAP,2:MIDCAP,3:HIGHCAP):%d",capability);
	printf("disk volumn:%I64d",volumn);
	printf("there are %d regions,region id list:",regionnum);
	for(i=0;i<regionnum;i++)
	{
		printf("%I64d",regionid[i]);
	}
	printf("device id:%I64d",deviceid);
	printf("disk path:%s",diskpath);
	
	printf("disk state(countnum):%d\n",storestate);
	return TRUE;
}
//根据device指针显示数据
int profile_device_info(DEVICE *deviceptr)
{
	//显示device信息
	UINT64 deviceid,*diskid,*regionid;
	int devicetype,processnum,disknum,regionnum;
	int *speed;
	int i,storestate;
	//开始赋值
	deviceid=deviceptr->DeviceID;
	devicetype=deviceptr->Devicetype;
	processnum=deviceptr->processnum;
	speed=deviceptr->speed;

	disknum=deviceptr->disknum;
	diskid=deviceptr->diskid;

	regionnum=deviceptr->regionnum;
	regionid=deviceptr->regionid;

	storestate=deviceptr->storestate;
	//输出数据
	printf("device id:%I64d\n",deviceid);
	printf("device type(0:RACKMAC,1:PCMAC,2:NASMAC):%d\n",devicetype);
	printf("there are %d processors,speed list:\n",processnum);
	for(i=0;i<processnum;i++)
	{
		printf("%I64d\n",speed[i]);
	}
	printf("there are %d disks,disk id list:",disknum);
	for(i=0;i<disknum;i++)
	{
		printf("%I64d",diskid[i]);
	}
	printf("there are %d regions,region id list:",regionnum);
	for(i=0;i<regionnum;i++)
	{
		printf("%I64d",regionid[i]);
	}
	printf("device state(countnum):%d\n",storestate);
	return TRUE;
}
//根据filemeta指针显示数据
int profile_filemeta_info(FILEMETA *filemetaptr)
{
	//fmeta部分信息
	UINT64 fileid;
	char *filename;
	int i,ACList,filetype,subfilenum;
	UINT64 filesize;
	UINT64 userid,parentid;
	UINT64 *subfileidlist;
	struct tm *createtime,*updatetime;
	FILEINF *filechunkinf;
	CHUNKPATH *chunkpath;
	//filechunkinf参数
	UINT64 *chunkid;
	int chunknum;//chunk数量

	UINT64 regionid;//属于的region的编号

	UINT64 *deviceid;//设备id
	int devicenum;//设备数

	UINT64 *diskid;//存储器id列表
	int disknum;//存储器数量

	UINT64 *stripid;//条带id列表
	int stripnum;//条带数量

	UINT64 *stripsectid;///条带分区id列表
	int stripsectnum;//条带分区数量
	//开始赋值fmeta

	fileid=filemetaptr->FileID;
	filename=filemetaptr->filename;

	filesize=filemetaptr->filesize;
	ACList=filemetaptr->ACList;
	filetype=filemetaptr->filetype;

	regionid=filemetaptr->regionid;

	userid=filemetaptr->userid;

	parentid=filemetaptr->parentid;

	subfilenum=filemetaptr->subfilenum;
	subfileidlist=filemetaptr->subfileidlist;

	createtime=filemetaptr->createtime;
	updatetime=filemetaptr->updatetime;
	filechunkinf=filemetaptr->filechunkinf;
	//赋值filechunkinf
	chunknum=filechunkinf->chunknum;
	chunkid=filechunkinf->chunkid;
	chunkpath=filechunkinf->chkpath;

	devicenum=filechunkinf->devicenum;
	deviceid=filechunkinf->deviceid;

	disknum=filechunkinf->disknum;
	diskid=filechunkinf->diskid;

	stripnum=filechunkinf->stripnum;
	stripid=filechunkinf->stripid;

	stripsectnum=filechunkinf->stripsectnum;
	stripsectid=filechunkinf->stripsectid;
	//显示filemeta信息
	printf("filemeta id:%I64d\n",fileid);
	printf("file name:%s\n",filename);
	printf("file size:%I64d\n",filesize);
	printf("Access Control list:%d\n",ACList);
	printf("file type:%d\n",filetype);

	printf("user id:%I64d\n",userid);

	printf("parent dictionary id:%I64d\n",parentid);
	printf("there are %d subfile,filemeta id list:%\n",subfilenum);
	for(i=0;i<subfilenum;i++)
	{
		printf("%I64d\n",subfileidlist[i]);
	}
	//创建修改时间
	printf("create time:%d/%d/%d/%d/%d,%d/%d/%d,%d\n",
		createtime->tm_year,createtime->tm_mon,createtime->tm_yday,createtime->tm_mday,createtime->tm_wday,
		createtime->tm_hour,createtime->tm_min,createtime->tm_sec,
		createtime->tm_isdst);
	printf("create time:%d/%d/%d/%d/%d,%d/%d/%d,%d\n",
		updatetime->tm_year,updatetime->tm_mon,updatetime->tm_yday,updatetime->tm_mday,updatetime->tm_wday,
		updatetime->tm_hour,updatetime->tm_min,updatetime->tm_sec,
		updatetime->tm_isdst);
	//filechunkinf数据
	printf("there are %d chunks,chunk id list:\n",chunknum);
	for(i=0;i<chunknum;i++)
	{
		printf("%I64d\n",chunkid[i]);
		printf("chunk id:%I64d,chunk array id:%d",chunkpath->chunkid,chunkpath->chunkarrayid);
		printf("stripsect id:%I64d,stripsect array id:%d",chunkpath->stripsectid,chunkpath->stripsectarrayid);
		printf("strip id:%I64d,strip array id:%d",chunkpath->stripid,chunkpath->striparrayid);
		printf("region id:%I64d,region array id:%d",chunkpath->regionid,chunkpath->regionarrayid);
		chunkpath++;
	}
	printf("region id:%I64d\n",regionid);
	printf("there are %d devices,device id list:\n",devicenum);
	for(i=0;i<devicenum;i++)
	{
		printf("%I64d\n",deviceid[i]);
	}
	printf("there are %d disks,disk id list:\n",disknum);
	for(i=0;i<disknum;i++)
	{ 
		printf("%I64d\n",diskid[i]);
	}
	printf("there are % strips,strip id list:\n",stripnum);
	for(i=0;i<stripnum;i++)
	{
		printf("%I64d\n",stripid[i]);//条带id列表
	}
	printf("there are % stripsects,stripsect id list:\n",stripsectnum);
	for(i=0;i<stripsectnum;i++)
	{
		printf("%I64d\n",stripsectid[i]);
	}
	return TRUE;
}
//根据useprofile指针显示数据
int profile_userprofile_info(USERPROFILE *useprofileptr)
{
	//显示useprofile信息
	UINT64 userid,DICid;
	char *username,*password,*DICpath;
	//USERLOCATION *userlocinf;
	int userprivil;
	struct tm *createtime;
	USERLOCATION *userlocinf;
	//先赋值
	userid=useprofileptr->UserID;
	username=useprofileptr->username;
	password=useprofileptr->password;
	
	userlocinf=useprofileptr->userlocinf;
	DICid=userlocinf->DICid;
	DICpath=userlocinf->DICpath;

	userprivil=useprofileptr->userprivil;
	createtime=useprofileptr->createtime;
	//显示useprofile信息
	printf("user id:%I64d\n",userid);
	printf("username:%s\n",username);
	printf("password:%s\n",password);
	printf("user dictionary id:%I64d\n",DICid);
	printf("user dictionary path:%s\n",DICpath);
	printf("user privilege:%d\n",userprivil);
	//int tm_sec;     /* seconds after the minute - [0,59] */
    //   int tm_min;     /* minutes after the hour - [0,59] */
    //    int tm_hour;    /* hours since midnight - [0,23] */
    //    int tm_mday;    /* day of the month - [1,31] */
    //    int tm_mon;     /* months since January - [0,11] */
    //    int tm_year;    /* years since 1900 */
    //    int tm_wday;    /* days since Sunday - [0,6] */
    //    int tm_yday;    /* days since January 1 - [0,365] */
    //    int tm_isdst;   /* daylight savings time flag */
	printf("create time:%d/%d/%d/%d/%d,%d/%d/%d,%d",
		createtime->tm_year,createtime->tm_mon,createtime->tm_yday,createtime->tm_mday,createtime->tm_wday,
		createtime->tm_hour,createtime->tm_min,createtime->tm_sec,
		createtime->tm_isdst);
	return TRUE;
}

//读取全局的id，包括4个regionid，diskid，deviceid和userid
int profile_global_define_reader()
{
	GLOSYSTEMID *systemid;
	UINT64 maxbuffersize;
	

	CHUNKBLOCK *chunkblockbuffer;
	GLOPUSHLIST *pushlistptr;

	IDITEM *systemnextid;

	int pushtime,*availkind,availnum;
	int resTF;
	//初始化开始需要设定全局metapath
	set_state_glometapath(".\\metadata\\");
	systemid=talloc(GLOSYSTEMID,1);//必须分配空间因为是全局的
	if(systemid==NULL)
	{
		show_error("profile","gloid_read","No memory");
		return FALSE;
	}
	//从元数据路径读取
	resTF=FILELAYER_GLOSYSTEMID_READER(systemid);
	if(resTF==FALSE)
	{
		show_error("profile","gloid_read","glosystemid information can't read");
		return FALSE;
	}
	//开始设定数据
	set_state_glosystemidgroup(systemid);
	pushtime=systemid->glopushtime;
	maxbuffersize=systemid->glomaxbuffersize;

	availkind=systemid->availkind;
	availnum=systemid->availnum;

	systemnextid=systemid->systemnextid;
	//将这些数值
	//set_state_buffer_push_time(pushtime);
	//set_state_buffer_maxbuffersize(maxbuffersize);
	/*chunkblockbuffer=talloc(CHUNKBLOCK,chksize_MB(4));//4G的存储器缓冲，因此4G/1K=最多4M个
	if(chunkblockbuffer==NULL)
	{
		show_error("profile","gloid_read","No memory");
		return FALSE;
	}*/
	chunkblockbuffer=NULL;//开4MB不合适

	pushlistptr=talloc(GLOPUSHLIST,1);
	if(pushlistptr==NULL)
	{
		show_error("profile","gloid_read","No memory");
		return FALSE;
	}
	pushlistptr->chunknum=0;
	pushlistptr->currentbuffersize=0;
	pushlistptr->glolastpushtime=NULL;
	pushlistptr->glopushchunklist=chunkblockbuffer;
	pushlistptr->glopushtime=pushtime;
	//参数设定完毕赋值即可
	set_state_buffer_pushlist(pushlistptr);
	//用完可以拆了
	free(pushlistptr);

	set_state_avail_kind_number(availnum);
	set_state_avail_kind(availkind);

	set_SYSID_PTR(systemnextid);
	//用完可以拆了
	free(systemnextid);
	return TRUE;
}


//获取全局区域元数据
int profile_region_reader()
{
	GLOSYSTEMID *systemid;
	UINT64 *regionidlist;//当前只有id号
	REGION *regionptr,*curregionptr;
	REGIONGROUP *reggrouplist;
	int i,reggroupsize,resTF;
	
	//得到相应数据
	systemid=get_state_glosystemidgroup_PTR();
	regionidlist=systemid->regionid;
	reggroupsize=systemid->regionnum;

	reggrouplist=talloc(REGIONGROUP,1);
	if(reggrouplist==NULL)
	{
		show_error("profile","region_read","No memory");
		return FALSE;
	}
	//建立region指针
	regionptr=talloc(REGION,reggroupsize);
	if(regionptr==NULL)
	{
		show_error("profile","region_read","No memory");
		return FALSE;
	}
	curregionptr=regionptr;
	for(i=0;i<reggroupsize;i++)
	{
		curregionptr->RegionID=regionidlist[i];
		resTF=FILELAYER_REGION_READER(curregionptr);
		if(resTF==FALSE)
		{
			show_error("file","FILELAYER_REGION_READER","region information can't read");
			return FALSE;
		}
		curregionptr++;
	}
	//将数据复制
	reggrouplist->regiongroup=regionptr;
	reggrouplist->groupsize=reggroupsize;

	systemid->gloregiongroup=reggrouplist;

	set_state_gloregiongroup(reggrouplist);
	free(reggrouplist);
	return TRUE;
}

//获取全局用户信息
int profile_userprofile_reader()
{
	GLOSYSTEMID *systemid;
	UINT64 curuserid;
	UINT64 *useridlist;
	USERPROFILE *curuserprofileptr,*userprofileptr;
	int i,resTF,usergroupsize;
	USERGROUP *usergrouplist;

	//开始数据
	systemid=get_state_glosystemidgroup_PTR();
	useridlist=systemid->userid;
	usergroupsize=systemid->usernum;

	//开空间
	usergrouplist=talloc(USERGROUP,1);
	if(usergrouplist==NULL)
	{
		show_error("profile","userprofile_read","No memory");
		return FALSE;
	}
	userprofileptr=talloc(USERPROFILE,usergroupsize);
	if(userprofileptr==NULL)
	{
		show_error("profile","userprofile_read","No memory");
		return FALSE;
	}
	curuserprofileptr=userprofileptr;
	for(i=0;i<usergroupsize;i++)
	{
		curuserprofileptr->UserID=useridlist[i];
		resTF=FILELAYER_USERPROFILE_READER(curuserprofileptr);
		if(resTF==FALSE)
		{
			show_error("profile","userprofile_read","user profile can't read");
			return FALSE;
		}
		curuserprofileptr++;
	}
	usergrouplist->userlist=userprofileptr;
	usergrouplist->groupsize=usergroupsize;

	systemid->glousergroup=usergrouplist;

	set_state_glousergroup(usergrouplist);
	//设定当前用户为第一个用户
	curuserid=userprofileptr->UserID;
	set_state_glosysuserptr(curuserid,userprofileptr);
	return TRUE;
}

//获取设备元数据
int profile_device_reader()
{
	GLOSYSTEMID *systemid;
	UINT64 *deviceidlist,*regionidlist,currentid;
	DEVICE *deviceptr,*curdeviceptr;
	int i,j,k,resTF,devicegroupsize,devregionnum,gloregionnum;
	DEVICEGROUP *devicegrouplist;
	DEVICEBLOCK *curdeviceblockptr,*deviceblockptr;

	REGIONGROUP *regiongrouplist;
	REGION *regionptr,*curregionptr;
	REGIONBLOCK *regionblockptr,*curregionblockptr;
	int regdevicenum,regdeviceindex;//region中包括多少个device
	//赋值数据
	systemid=get_state_glosystemidgroup_PTR();
	deviceidlist=systemid->deviceid;
	devicegroupsize=systemid->devicenum;
	//获取全局region数据
	regiongrouplist=get_state_gloregiongroup_PTR();
	regionptr=regiongrouplist->regiongroup;
	gloregionnum=regiongrouplist->groupsize;
	//开空间
	devicegrouplist=talloc(DEVICEGROUP,1);
	if(devicegrouplist==NULL)
	{
		show_error("profile","device_read","No memory");
		return FALSE;
	}
	deviceptr=talloc(DEVICE,devicegroupsize);
	if(deviceptr==NULL)
	{
		show_error("profile","device_read","No memory");
		return FALSE;
	}
	curdeviceptr=deviceptr;
	for(i=0;i<devicegroupsize;i++)
	{
		curdeviceptr->DeviceID=deviceidlist[i];
		resTF=FILELAYER_DEVICE_READER(curdeviceptr);
		if(resTF==FALSE)
		{
			show_error("profile","device_read","device can't read");
			return FALSE;
		}

		//建立device和region关系
		regionidlist=curdeviceptr->regionid;
		devregionnum=curdeviceptr->regionnum;
		regionblockptr=talloc(REGIONBLOCK,devregionnum);
		curregionblockptr=regionblockptr;
		
		for(j=0;j<devregionnum;j++)
		{
			curregionptr=regionptr;
			
			for(k=0;k<gloregionnum;j++)
			{
				//建立device和region关系
				currentid=curregionptr->RegionID;
				if(currentid==regionidlist[j])
				{
					//找到赋值
					curregionblockptr->regionptr=curregionptr;
					curregionblockptr->regionid=currentid;
					break;
				}
				curregionptr++;
			}
			curregionblockptr++;
		}
		curdeviceptr->regionlist=regionblockptr;
		curdeviceptr++;
	}
	//建立反向方向联系
	curregionptr=regionptr;//重新定位到头部
	for(i=0;i<gloregionnum;i++)
	{
		regdeviceindex=0;

		deviceidlist=curregionptr->deviceid;//重新用一下
		regdevicenum=curregionptr->devicenum;

		deviceblockptr=talloc(DEVICEBLOCK,regdevicenum);
		if(deviceblockptr==NULL)
		{
			show_error("profile","device_read","No memory");
			return FALSE;
		}

		curdeviceblockptr=deviceblockptr;
		
		for(j=0;j<regdevicenum;j++)
		{
			curdeviceptr=deviceptr;
			for(k=0;k<devicegroupsize;k++)
			{
				currentid=curdeviceptr->DeviceID;
				if(currentid==deviceidlist[j])
				{
					curdeviceblockptr->deviceid=curdeviceptr->DeviceID;
					curdeviceblockptr->deviceptr=curdeviceptr;
				}
				curdeviceptr++;
			}
			curdeviceblockptr++;//找到一个指针+1

		}
		curregionptr->devicelist=deviceblockptr;
		curregionptr++;
	}
	
	//将其赋值
	devicegrouplist->devicegroup=deviceptr;
	devicegrouplist->groupsize=devicegroupsize;
	set_state_glodevicegroup(devicegrouplist);
	free(devicegrouplist);//全局有group结构不需要这里有副本
	return TRUE;
}

//获取存储器元数据
int profile_disk_reader()
{
	//整理
	GLOSYSTEMID *systemid;

	int i,j,k,m,resTF,diskgroupsize,devicegroupsize,diskregionnum,gloregionnum;
	int glodiskgroupsize;//整体的

	UINT64 *diskidlist,*regionidlist,currentid;

	DISK *diskptr,*curdiskptr;
	DISKGROUP *diskgrouplist;
	DISKBLOCK *diskblockptr,*curdiskblockptr;

	DEVICE *deviceptr,*curdeviceptr;
	DEVICEGROUP *devicegrouplist;

	REGIONGROUP *regiongrouplist;
	REGIONBLOCK *regionblockptr,*curregionblockptr;
	REGION *curregionptr,*regionptr;
	int regdisknum;
	//得到全局id指针
	systemid=get_state_glosystemidgroup_PTR();
	//磁盘数据
	glodiskgroupsize=systemid->disknum;//disknum数据赋值
	
	diskgrouplist=talloc(DISKGROUP,1);//生成指针组
	if(diskgrouplist==NULL)
	{
		show_error("profile","disk_read","No memory");
		return FALSE;
	}
	diskptr=talloc(DISK,glodiskgroupsize);//生成disk组
	if(diskptr==NULL)
	{
		show_error("profile","disk_read","No memory");
		return FALSE;
	}
	//region列表
	regiongrouplist=get_state_gloregiongroup_PTR();
	regionptr=regiongrouplist->regiongroup;
	gloregionnum=regiongrouplist->groupsize;
	//当前设备列表
	devicegrouplist=get_state_glodevicegroup_PTR();
	deviceptr=devicegrouplist->devicegroup;
	devicegroupsize=devicegrouplist->groupsize;
	//将当前指针赋值
	curdeviceptr=deviceptr;//将两个指针定位到全局空间
	curdiskptr=diskptr;
	for(i=0;i<devicegroupsize;i++)
	{
		diskgroupsize=curdeviceptr->disknum;//知道当前数据多少
		diskidlist=curdeviceptr->diskid;
		curdeviceptr->disklist=talloc(DISKBLOCK,diskgroupsize);
		for(j=0;j<diskgroupsize;j++)
		{
			//先赋值以便定位
			curdiskptr->deviceid=curdeviceptr->DeviceID;
			curdiskptr->DiskID=diskidlist[j];
			//先把disk数据读入内存
			resTF=FILELAYER_DISK_READER(curdiskptr);
			if(resTF==FALSE)
			{
				show_error("profile","disk_read","");
				return FALSE;
			}
			//建立device和disk之间的关系
			resTF=profile_device_disk_setup(curdeviceptr,curdiskptr,j);
			if(resTF==FALSE)
			{
				show_error("profile","disk_read","the relation between disk and device can't establish");
				return FALSE;
			}
			//获取disk的regionnum
			diskregionnum=curdiskptr->regionnum;
			regionidlist=curdiskptr->regionid;
			regionblockptr=talloc(REGIONBLOCK,diskregionnum);
			if(regionblockptr==NULL)
			{
				show_error("profile","disk_read","No memory");
				return FALSE;
			}
			for(k=0;k<diskregionnum;k++)
			{
				curregionblockptr=regionblockptr;
				curregionptr=regionptr;
				for(m=0;m<gloregionnum;m++)
				{
					currentid=curregionptr->RegionID;
					if(currentid==regionidlist[j])
					{
						curregionblockptr->regionptr=curregionptr;
						curregionblockptr->regionid=currentid;
						break;
					}
					curregionptr++;
				}
				curregionblockptr++;
			}
			curdiskptr->regionlist=regionblockptr;
			curdiskptr++;
			//找到当前disk的regionlist
		}
		curdeviceptr++;
	}
	//建立disk和region指针
	curregionptr=regionptr;
	for(i=0;i<gloregionnum;i++)
	{
		diskidlist=curregionptr->diskid;
		regdisknum=curregionptr->disknum;
		diskblockptr=talloc(DISKBLOCK,regdisknum);
		if(diskblockptr==NULL)
		{
			show_error("profile","disk_read","No memory");
			return FALSE;
		}
		curdiskblockptr=diskblockptr;
		for(j=0;j<regdisknum;j++)
		{
			curdiskptr=diskptr;
			for(k=0;k<glodiskgroupsize;k++)
			{
				currentid=curdiskptr->DiskID;
				if(currentid==diskidlist[j])
				{
					curdiskblockptr->diskptr=curdiskptr;
					curdiskblockptr->diskid=curdiskptr->DiskID;
					break;
				}
				curdiskptr++;
			}
			curdiskblockptr++;
		}
		curregionptr->disklist=diskblockptr;
		curregionptr++;
	}
	//最后赋值
	diskgrouplist->diskgroup=diskptr;
	diskgrouplist->groupsize=glodiskgroupsize;
	set_state_glodiskgroup(diskgrouplist);
	free(diskgrouplist);
	return TRUE;
}
//建立device以及disk指针关系
int profile_device_disk_setup(DEVICE *deviceptr,DISK *diskptr,int index)
{
	int tardiskblocksize;//设备的disk数
	//提取目标指针
	//DISK *tardiskptr,*curtardiskptr;
	DISKBLOCK *diskblocklist,*curblockptr;
	diskptr->deviceptr=deviceptr;
	diskptr->deviceid=deviceptr->DeviceID;
	tardiskblocksize=deviceptr->disknum;

	diskblocklist=deviceptr->disklist;
	
	if(tardiskblocksize<index)
	{
		show_error("profile","device_disk_setup","tardiskgroupsize<index");
		return FALSE;
	}
	curblockptr=diskblocklist+index;
	//可以开始赋值了
	curblockptr->diskptr=diskptr;
	curblockptr->diskid=diskptr->DiskID;
	return TRUE;
}

//初始化dirtydata数据组
int profile_dirtydata_intial()
{
	//初始化数据
	GLODIRTYDATA *dirtydataptr;
	dirtydataptr=talloc(GLODIRTYDATA,1);
	if(dirtydataptr==NULL)
	{
		show_error("profile","dirtydata_intial","No memory");
		return FALSE;
	}
	GLOBAL_set_GLODIRTYDATA_data(dirtydataptr,
										NULL,0,
										NULL,0,
										NULL,0,
										NULL,0,
										NULL,0,
										NULL,0,
										NULL,0,
										NULL,0
										);
	set_state_dirtydatalist(dirtydataptr);
	free(dirtydataptr);
	return TRUE;
}

int profile_map_RAID5(REGION *regionptr)
{
	int i,j,resTF;
	int countnum;
	int stripnum,strsetnum,chunknum,disknum;

	//CODEPARA *codeparamptr;//需要编码参数进行赋值
	STRIPDES *stripdesptr;

	STRIPGROUP *stripgroupptr;
	STRIP *stripptr,*curstripptr;

	STRIPSECTGROUP *stsetgroupptr;
	STRIPSECT *strsetptr,*curstrsetptr;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;

	stripgroupptr=regionptr->striplist;
	stripdesptr=regionptr->strdes;
	//codeparamptr=regionptr->codepara;
	//chunknum=stripdesptr->chunknum;

	stripptr=stripgroupptr->stripgroup;
	stripnum=stripgroupptr->groupsize;
	
	disknum=stripdesptr->disknum;//获取
	chunknum=stripdesptr->chunknum;//其实没有必要但是还是赋值一下

	curstripptr=stripptr;

	countnum=0;//计算条带位置
	for(i=0;i<stripnum;i++)
	{
		if(countnum==disknum)//如果
		{
			countnum=0;
		}

		//初始化数据
		stsetgroupptr=curstripptr->stripsectlist;

		strsetptr=stsetgroupptr->stripsectgroup;
		strsetnum=stsetgroupptr->groupsize;

		curstrsetptr=strsetptr+disknum-1-countnum;//因为disknum是6，移动+5即可

		curstrsetptr->isparity=TRUE;//是校验值
		curstrsetptr->storestate=chunknum;
		/*resTF=FILELAYER_STRIPSECT_WRITER(curstrsetptr);
		if(resTF==FALSE)
		{
			show_error("profile","map_RAID5","stripsect metadata can't write");
			return FALSE;
		}*/

		chunkgroupptr=curstrsetptr->chunklist;

		chunkptr=chunkgroupptr->ckgroup;
		chunknum=chunkgroupptr->groupsize;

		curchunkptr=chunkptr;
		for(j=0;j<chunknum;j++)
		{
			curchunkptr->isparity=TRUE;
			curchunkptr->storestate=TRUE;//当前已被占用

			/*resTF=FILELAYER_CHUNK_WRITER_META(curchunkptr);
			if(resTF==FALSE)
			{
				show_error("profile","map_RAID5","chunk metadata can't wirte");
				return FALSE;
			}*/
			curchunkptr++;
		}
		countnum++;
		curstripptr++;
	}
	return TRUE;
}
int profile_map_RAID6(REGION *regionptr)
{
	int i,j,resTF;
	int countnum;
	int stripnum,strsetnum,chunknum,disknum;

	STRIPDES *stripdesptr;

	STRIPGROUP *stripgroupptr;
	STRIP *stripptr,*curstripptr;

	STRIPSECTGROUP *stsetgroupptr;
	STRIPSECT *strsetptr,*curstrsetptr;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *pchunkptr,*curpchunkptr;//用于记录p盘
	CHUNK *qchunkptr,*curqchunkptr;//用于记录q盘

	stripgroupptr=regionptr->striplist;
	stripdesptr=regionptr->strdes;

	stripgroupptr->stripgroup;
	stripgroupptr->groupsize;

	stripptr=stripgroupptr->stripgroup;
	stripnum=stripgroupptr->groupsize;
	
	disknum=stripdesptr->disknum;//获取
	chunknum=stripdesptr->chunknum;//其实没有必要但是还是赋值一下

	curstripptr=stripptr;

	countnum=0;//计算条带位置
	for(i=0;i<stripnum;i++)
	{
		if(countnum==(disknum-1))//当等于disknum时停止
		{
			countnum=0;
		}
		//计算p盘位置
		stsetgroupptr=curstripptr->stripsectlist;

		strsetptr=stsetgroupptr->stripsectgroup;
		strsetnum=stsetgroupptr->groupsize;

		curstrsetptr=strsetptr+disknum-2-countnum;//计算当前p盘位置

		curstrsetptr->isparity=PPARITY;
		curstrsetptr->storestate=chunknum;

		/*resTF=FILELAYER_STRIPSECT_WRITER(curstrsetptr);
		if(resTF==FALSE)
		{
			show_error("profile","map_RAID6","stripsect metadata can't write");
			return FALSE;
		}*/
		chunkgroupptr=curstrsetptr->chunklist;

		pchunkptr=chunkgroupptr->ckgroup;//这是当前p盘起始位置
		chunknum=chunkgroupptr->groupsize;
		curpchunkptr=pchunkptr;
		
		curstrsetptr=curstrsetptr+1;
		curstrsetptr->isparity=QPARITY;
		curstrsetptr->storestate=chunknum;

		/*resTF=FILELAYER_STRIPSECT_WRITER(curstrsetptr);
		if(resTF==FALSE)
		{
			show_error("profile","map_RAID6","stripsect metadata can't write");
			return FALSE;
		}*/
		chunkgroupptr=curstrsetptr->chunklist;

		qchunkptr=chunkgroupptr->ckgroup;//这是当前q盘起始位置
		chunknum=chunkgroupptr->groupsize;
		curqchunkptr=qchunkptr;

		for(j=0;j<chunknum;j++)
		{
			curpchunkptr->isparity=PPARITY;
			curpchunkptr->storestate=TRUE;
			/*resTF=FILELAYER_CHUNK_WRITER_META(curpchunkptr);
			if(resTF==FALSE)
			{
				show_error("profile","map_RAID5","chunk metadata can't wirte");
				return FALSE;
			}*/

			curqchunkptr->isparity=QPARITY;
			curqchunkptr->storestate=TRUE;
			/*resTF=FILELAYER_CHUNK_WRITER_META(curqchunkptr);
			if(resTF==FALSE)
			{
				show_error("profile","map_RAID5","chunk metadata can't wirte");
				return FALSE;
			}*/

			curpchunkptr++;
			curqchunkptr++;
		}
		countnum++;
		curstripptr++;
	}
	return TRUE;
}
int profile_map_define_intial(REGION *regionptr)
{
	int maintype,codetype,resTF;
	codetype=regionptr->codetype;
	maintype=maintype(codetype);//获取主要的编码类别
	switch(maintype)//使用类别
	{
	case RAID6:
		resTF=profile_map_RAID6(regionptr);
		if(resTF==FALSE)
		{
			show_error("profile","map_define_intial","RAID-6 can't define parity");
			return FALSE;
		}
		break;
	case RAID5:
		resTF=profile_map_RAID5(regionptr);
		if(resTF==FALSE)
		{
			show_error("profile","map_define_intial","RAID-6 can't define parity");
			return FALSE;
		}
		break;
	}
	return TRUE;
}


//初始化region系统参数
/*int profile_region_intial(REGION *regionptr)
{
	//三步走
	//1.读取region信息。2.format内存数据3.将数据元数据读入内存
	return TRUE;
}*/


//格式化region数据,在内存中，如果要format
int profile_region_format_PTR(REGION *regionptr)
{
	//建立相应的层次接口
	UINT64 totalsize,stripsize,strsetsize,chunksize64;//由于计算时空间较大因此统统64位的干活
	int chunksize;
	UINT64 chunknum,disknum64;//辅助行列信息
	UINT64 regionid,nowstripid,nowstrsetid,nowchunkid,nowdiskid,nowdeviceid;//当前id
	int regionarrayid,striparrayid,stripsectarrayid,chunkarrayid;//当前位置

	

	//DISK diskid;不涉及到硬件、因此不用disk
	STRIP *striplist,*curstripptr;//当前strip指针
	STRIPGROUP *stripgroupptr;

	STRIPSECT *strsetlist,*curstrsetptr;//当前stripsect指针
	CHUNK *chunklist,*curchunkptr;//当前chunk指针

	UINT64 *stripid,*strsetid,*chunkid;
	UINT64 *curchunkid;

	STRIPDES *strdes;
	UINT64 *diskid,*deviceid;

	DISKBLOCK *disklist;
	DEVICEBLOCK *devicelist;
	int disknum,devicenum;

	int i,j,k,striptotnum,strsetinstrnum,chunkinstrnum,chunkinstrsetnum;
	int isparity;
	//DISK *disklistptr,*curdiskptr;
	DISK *curdiskptr;
	DEVICE *curdeviceptr;//由于可以从disk中查询因此只需指针即可
	UINT64 strsettotnum,chunktotnum;
	CHUNKPATH *chkpath;//设置路径
	//定义两个chunk和strip两个group
	CHUNKGROUP *chkgrouplist;
	STRIPSECTGROUP *strsetgrouplist;
	//当前stripsect
	char strsetidname[20];
	char *strsetfilename;
	char *strsetfilepath;
	//disk文件路径
	char *diskpath;
	//需要计算的路径
	//char *filename;
	//char *filepath;
	//此时需要计算左右实体的数量
	
	//开始进行赋值
	regionid=regionptr->RegionID;
	totalsize=regionptr->totalsize;
	strdes=regionptr->strdes;
	chunksize64=(UINT64)strdes->chunksize;
	chunksize=strdes->chunksize;
	chunknum=(UINT64)strdes->chunknum;
	disknum64=(UINT64)strdes->disknum;
	//=(UINT64)strdes->diskid;
	strsetsize=calstripsectsize(chunksize64,chunknum);
	stripsize=calstripsize(strsetsize,disknum64);//计算stripsize进行比较
	//计算完成可以安全性检测
	if(totalsize<stripsize)
	{
		show_error("profile","region_format","totalsize<stripsize");
		printf("set totalsize=stripsize\n");
		totalsize=stripsize;
		//return FALSE;
	}
	diskid=regionptr->diskid;
	disklist=regionptr->disklist;
	disknum=regionptr->disknum;
	//disklistptr=disklist->diskgroup;

	deviceid=regionptr->deviceid;
	devicelist=regionptr->devicelist;
	devicenum=regionptr->devicenum;

	//计算需要多少个strip、stripsect和chunk
	striptotnum=calstripnum(totalsize,stripsize);//strip需要多一个
	strsettotnum=striptotnum*disknum;//计算stripsect数量
	chunktotnum=strsettotnum*chunknum;//计算需要的chunk数量

	//计算数据赋值回去
	regionptr->stripnum=striptotnum;
	regionptr->stripsectnum=strsettotnum;
	regionptr->chunknum=chunktotnum;

	//开始计算每一个strip中的数据
	strsetinstrnum=strdes->disknum;
	chunkinstrsetnum=strdes->chunknum;
	chunkinstrnum=strsetinstrnum*chunkinstrsetnum;//总数

	//开始生成相应strip块
	striplist=talloc(STRIP,striptotnum);//分配全局的strip信息
	if(striplist==NULL)
	{
		show_error("profile","region_format","No memory");
		return FALSE;
	}
	stripid=talloc(UINT64,striptotnum);//id标号列表
	if(stripid==NULL)
	{
		show_error("profile","region_format","No memory");
		return FALSE;
	}
	
	//填写相应数据
	regionptr->stripid=stripid;
	stripgroupptr=talloc(STRIPGROUP,1);
	if(stripgroupptr==NULL)
	{
		show_error("profile","region_format","No memory");
		return FALSE;
	}
	stripgroupptr->stripgroup=striplist;
	stripgroupptr->groupsize=striptotnum;
	regionptr->striplist=stripgroupptr;
	regionptr->stripnum=striptotnum;//将数据记下

	regionarrayid=profile_region_search(regionptr);//获取当前region的arrayid
	curstripptr=striplist;//将当前指针进行赋值
	for(i=0;i<striptotnum;i++)
	{
		//先设置标号
		stripid[i]=get_state_glostripid();
		curstripptr->StripID=get_state_glostripid();
		nowstripid=get_state_glostripid();
		striparrayid=i;
		set_state_glostripid_add(1);

		//生成两个新的chunk和stripsect信息块，以备调用
		chunklist=talloc(CHUNK,chunkinstrnum);
		if(chunklist==NULL)
		{
			show_error("profile","region_format","No memory");
			return FALSE;
		}
		strsetlist=talloc(STRIPSECT,strsetinstrnum);
		if(strsetlist==NULL)
		{
			show_error("profile","region_format","No memory");
			return FALSE;
		}

		curchunkptr=chunklist;
		curstrsetptr=strsetlist;
		
		chunkid=talloc(UINT64,chunkinstrnum);
		if(chunkid==NULL)
		{
			show_error("profile","region_format","No memory");
			return FALSE;
		}
		strsetid=talloc(UINT64,strsetinstrnum);
		if(strsetid==NULL)
		{
			show_error("profile","region_format","No memory");
			return FALSE;
		}

		curchunkid=chunkid;

		chkgrouplist=talloc(CHUNKGROUP,1);
		if(chkgrouplist==NULL)
		{
			show_error("profile","region_format","No memory");
			return FALSE;
		}
		strsetgrouplist=talloc(STRIPSECTGROUP,1);
		if(strsetgrouplist==NULL)
		{
			show_error("profile","region_format","No memory");
			return FALSE;
		}

		chkgrouplist->ckgroup=chunklist;
		chkgrouplist->groupsize=chunkinstrnum;

		strsetgrouplist->stripsectgroup=strsetlist;
		strsetgrouplist->groupsize=strsetinstrnum;

		//需要分配一个
		GLOBAL_set_STRIP_data(curstripptr,strdes,//条带描述
								 disklist,diskid,disknum,//包含存储器个数，region中继承
								 devicelist,deviceid,devicenum,//设备列表，region中继承
								 strsetgrouplist,strsetid,strsetinstrnum,//Strset列表，现在还不知道
								 chkgrouplist,chunkid,chunkinstrnum,//chunk列表，现在还不知道
								 regionid,regionptr,//上一级region指针
								 EMPTY//当前存储状态为空
								 );
		curdiskptr=disklist->diskptr;//设定当前disk指针
		//需要设置当前的chunk和stripsect指针
		for(j=0;j<strsetinstrnum;j++)
		{
			//设置当前stripsect信息
			strsetid[j]=get_state_glostripsectid();
			curstrsetptr->StripsectID=get_state_glostripsectid();
			nowstrsetid=get_state_glostripsectid();
			stripsectarrayid=j;
			set_state_glostripsectid_add(1);
			//chkpath=talloc(CHUNKPATH,1);//分配空间
			
			//找到相应的disk指针
			nowdiskid=curdiskptr->DiskID;//获取当前disk指针编号
			
			curdeviceptr=curdiskptr->deviceptr;
			nowdeviceid=curdeviceptr->DeviceID;

			//计算文件名和文件路径
			U64toSTR(strsetidname,nowstrsetid);
			strsetfilename=talloc(char,40);
			if(strsetfilename==NULL)
			{
				show_error("profile","region_format","No memory");
				return FALSE;
			}
			strsetfilename[0]='\0';
			file_stripsectstr_name(strsetfilename,strsetidname);//计算文件名
			
			strsetfilepath=talloc(char,40+1000);
			if(strsetfilepath==NULL)
			{
				show_error("profile","region_format","No memory");
				return FALSE;
			}
			strsetfilepath[0]='\0';
			diskpath=curdiskptr->diskpath;
			//计算文件路径
			strcat(strsetfilepath,diskpath);//拼接diskpath
			strcat(strsetfilepath,strsetfilename);

			chkgrouplist=talloc(CHUNKGROUP,1);
			chkgrouplist->ckgroup=curchunkptr;
			chkgrouplist->groupsize=chunkinstrsetnum;

			isparity=FALSE;//先假设他们不是

			GLOBAL_set_STRIPSECT_data(curstrsetptr,
										isparity,curchunkid,chkgrouplist,chunksize,chunkinstrsetnum,//chunk列表
										regionid,regionptr,//上一级region指针
										stripid[i],curstripptr,//上一级strip指针
										nowdiskid,curdiskptr,//上一级disk指针
										nowdeviceid,curdeviceptr,//上一级device指针
										strsetfilename,strsetfilepath,//路径
										EMPTY
										);//当前存储状态
			for(k=0;k<chunkinstrsetnum;k++)
			{
				//设置当前
				curchunkptr->ChunkID=get_state_glochunkid();
				*curchunkid=get_state_glochunkid();//设定当前标号
				nowchunkid=get_state_glochunkid();
				chunkarrayid=k;
				set_state_glochunkid_add(1);
				chkpath=talloc(CHUNKPATH,1);
				if(chkpath==NULL)
				{
					show_error("profile","region_format","No memory");
					return FALSE;
				}
				//对于chunkpath进行赋值
				GLOBAL_set_CHUNKPATH_data(chkpath,
										 regionid,regionarrayid,regionptr,//region指针
										 nowstripid,striparrayid,curstripptr,//strip指针
										 nowstrsetid,stripsectarrayid,curstrsetptr,//stripsect指针
										 nowchunkid,chunkarrayid,curchunkptr//指向当前chunk
										 );//设定CHUNKPATH数据值
				isparity=FALSE;
				GLOBAL_set_CHUNK_data(curchunkptr,isparity,chkpath,chunksize,//基本信息
										NULL,//内容
										regionid,regionptr,//上一级region的指针
										nowstripid,curstripptr,//上一级strip的指针
										nowstrsetid,curstrsetptr,//上一级stripsect的指针
										nowdiskid,curdiskptr,//上一级disk的指针
										nowdeviceid,curdeviceptr,//上一级device的指针
										NOVALUE,NULL,//属于文件元数据
										EMPTY//当前块存储状态
										);//设定当前CHUNK中的数据
				curchunkptr++;
				curchunkid++;
			}
			curdiskptr++;//将disk也加1
			curstrsetptr++;
		}
		curstripptr++;
	}
	return TRUE;
}
//读取当前数据信息
int profile_region_reader_PTR(REGION *regionptr)
{
	UINT64 nowregionid,nowstripid,nowstrsetid,nowchunkid;
	int i,j,k,resTF,stripgroupsize,strsetgroupsize,chunkgroupsize;
	int devicenum,disknum;
	UINT64 *stripidlist,*strsetidlist,*chunkidlist;
	UINT64 *deviceidlist,*diskidlist;
	
	UINT64 nowdiskid,nowdeviceid;

	DEVICEBLOCK *deviceblockptr;
	DISKBLOCK *diskblockptr;

	int regionarrayid,striparrayid,strsetarrayid,chunkarrayid; 

	DEVICE *deviceptr;

	DISK *diskptr;

	STRIPGROUP *stripgroupptr;
	STRIP *stripptr,*curstripptr;
	STRIPDES *stripdesptr;

	STRIPSECTGROUP *strsetgroupptr;
	STRIPSECT *strsetptr,*curstrsetptr;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;

	CHUNKPATH *chkpath;
	//读取相应的region数据
	//FILELAYER_REGION_READER(regionptr);
	stripgroupsize=regionptr->stripnum;
	stripidlist=regionptr->stripid;
	//开空间
	stripptr=talloc(STRIP,stripgroupsize);
	if(stripptr==NULL)
	{
		show_error("profile","region_reader_PTR","No memory");
		return TRUE;
	}
	stripgroupptr=talloc(STRIPGROUP,1);
	if(stripgroupptr==NULL)
	{
		show_error("profile","region_reader_PTR","No memory");
		return FALSE;
	}
	stripgroupptr->stripgroup=stripptr;
	stripgroupptr->groupsize=stripgroupsize;

	regionptr->striplist=stripgroupptr;//将其赋值回去
	//找到当前regionarrayid
	regionarrayid=profile_region_search(regionptr);
	
	//由于在之间device和disk时已经建立了device和disk与region关系这里可以不写
	

	nowregionid=regionptr->RegionID;
	curstripptr=stripptr;
	
	for(i=0;i<stripgroupsize;i++)
	{
		curstripptr->StripID=stripidlist[i];
		curstripptr->regionid=nowregionid;
		
		resTF=FILELAYER_STRIP_READER(curstripptr);
		if(resTF==FALSE)
		{
			show_error("profile","region_reader_PTR","strip information can't read");
			return FALSE;
		}
		curstripptr->regionptr=regionptr;
		strsetgroupsize=curstripptr->strsetnum;
		strsetptr=talloc(STRIPSECT,strsetgroupsize);
		if(strsetptr==NULL)
		{
			show_error("profile","region_reader_PTR","No memory");
			return FALSE;
		}
		strsetgroupptr=talloc(STRIPSECTGROUP,1);
		if(strsetgroupptr==NULL)
		{
			show_error("profile","region_reader_PTR","No memory");
			return FALSE;
		}
		strsetgroupptr->stripsectgroup=strsetptr;
		strsetgroupptr->groupsize=strsetgroupsize;
		curstripptr->stripsectlist=strsetgroupptr;

		chunkgroupsize=curstripptr->chunknum;
		chunkptr=talloc(CHUNK,chunkgroupsize);
		if(chunkptr==NULL)
		{
			show_error("profile","region_reader_PTR","No memory");
			return FALSE;
		}
		chunkgroupptr=talloc(CHUNKGROUP,1);
		if(chunkgroupptr==NULL)
		{
			show_error("profile","region_reader_PTR","No memory");
			return FALSE;
		}
		chunkgroupptr->ckgroup=chunkptr;
		chunkgroupptr->groupsize=chunkgroupsize;
		curstripptr->chunklist=chunkgroupptr;

		
		

		striparrayid=i;

		nowstripid=curstripptr->StripID;

		strsetidlist=curstripptr->stripsectid;
		//devicelist
		deviceblockptr=regionptr->devicelist;
		curstripptr->devicelist=deviceblockptr;
		//disklist
		diskblockptr=regionptr->disklist;
		curstripptr->disklist=diskblockptr;
		stripdesptr=curstripptr->strdes;
		stripdesptr->disklist=diskblockptr;

		stripdesptr=regionptr->strdes;
		stripdesptr->disklist=diskblockptr;
	/*
		//这一段代码可以在region和strip不一致时使用
		//找到当前deviceblock
		deviceidlist=curstripptr->deviceid;
		devicenum=curstripptr->devicenum;

		deviceblockptr=talloc(DEVICEBLOCK,devicenum);
		if(deviceblockptr==NULL)
		{
			show_error("profile","region_reader_PTR","No memory");
			return FALSE;
		}
		profile_device_search(deviceblockptr,deviceidlist,devicenum);
		//curstripptr->devicelist=deviceblockptr;
		
		//找到当前diskblock
		diskidlist=curstripptr->diskid;
		disknum=curstripptr->disknum;
	
		diskblockptr=talloc(DISKBLOCK,disknum);
		if(diskblockptr==NULL)
		{
			show_error("profile","region_reader_PTR","No memory");
			return FALSE;
		}
		profile_disk_search(diskblockptr,diskidlist,disknum);
		//curstripptr->disklist=diskblockptr;
		*/

		curstrsetptr=strsetptr;
		curchunkptr=chunkptr;
		//同时申请chunk和stripsect空间并且建立指针
		for(j=0;j<strsetgroupsize;j++)
		{
			//开始赋值
			curstrsetptr->regionid=nowregionid;
			curstrsetptr->stripid=nowstripid;

			curstrsetptr->StripsectID=strsetidlist[j];
			resTF=FILELAYER_STRIPSECT_READER(curstrsetptr);
			if(resTF==FALSE)
			{
				show_error("profile","region_reader_PTR","stripsect information can't read");
				return FALSE;
			}
			curstrsetptr->regionptr=regionptr;
			curstrsetptr->stripptr=curstripptr;

			chunkidlist=curstrsetptr->chunkid;
			chunkgroupsize=curstrsetptr->chunknum;
			
			chunkgroupptr=talloc(CHUNKGROUP,1);
			if(chunkgroupptr==NULL)
			{
				show_error("profile","region_reader_PTR","No memory");
				return FALSE;
			}
			chunkgroupptr->ckgroup=curchunkptr;//将当前指针赋值
			chunkgroupptr->groupsize=chunkgroupsize;//大小赋值
			//将当前指针赋值回去
			curstrsetptr->chunklist=chunkgroupptr;

			nowdiskid=curstrsetptr->diskid;
			nowdeviceid=curstrsetptr->deviceid;
			
			disknum=curstripptr->disknum;

			diskptr=profile_disk_ptr_search(nowdiskid,diskblockptr,disknum);//找出当前disk列表中diskid是目标的数据
			if(diskptr==NULL)
			{
				show_error("profile","region_reader_PTR","disk pointer can't find");
				return FALSE;
			}
			curstrsetptr->diskptr=diskptr;

			devicenum=curstripptr->devicenum;
			deviceptr=profile_device_ptr_search(nowdeviceid,deviceblockptr,devicenum);//找出当前device列表中deviceid是目标的数据
			if(deviceptr==NULL)
			{
				show_error("profile","region_reader_PTR","device pointer can't find");
				return FALSE;
			}
			curstrsetptr->deviceptr=deviceptr;

			nowstrsetid=curstrsetptr->StripsectID;
			strsetarrayid=j;
			//curchunkptr=chunkptr;
			for(k=0;k<chunkgroupsize;k++)
			{
				nowchunkid=chunkidlist[k];
				chunkarrayid=k;
				chkpath=talloc(CHUNKPATH,1);
				if(chkpath==NULL)
				{
					show_error("profile","region_reader_PTR","No memory");
					return FALSE;
				}
				GLOBAL_set_CHUNKPATH_data(chkpath,
									 nowregionid,regionarrayid,regionptr,//region指针
									 nowstripid,striparrayid,curstripptr,//strip指针
									 nowstrsetid,strsetarrayid,curstrsetptr,//stripsect指针
									 nowchunkid,chunkarrayid,curchunkptr//指向当前chunk
									 );//设定CHUNKPATH数据值
				curchunkptr->chkpath=chkpath;
				curchunkptr->ChunkID=nowchunkid;
				curchunkptr->stripsectid=nowstrsetid;
				curchunkptr->regionid=nowregionid;
				//读数据
				resTF=FILELAYER_CHUNK_READER_META(curchunkptr);
				if(resTF==FALSE)
				{
					show_error("profile","region_reader_PTR","chunk information can't read");
					return TRUE;
				}
				curchunkptr->chunkcontent=NULL;
				curchunkptr->deviceptr=deviceptr;
				curchunkptr->diskptr=diskptr;
				curchunkptr->regionptr=regionptr;
				curchunkptr->stripptr=curstripptr;
				curchunkptr->stripsectptr=curstrsetptr;
				curchunkptr->fmeta=NULL;
				//curchunkptr->fileid=NOVALUE;
				curchunkptr++;
			}
			curstrsetptr++;
		}
		curstripptr++;
	}
	printf("region information has created\n");
	return TRUE;
}

int profile_chunk_fileinf(CHUNKBLOCK *chunkblockptr,FILEMETA *filemetaptr,int chunknum)
{
	int i;
	CHUNK *chunkptr;
	CHUNKBLOCK *curchunkblockpr;

	curchunkblockpr=chunkblockptr;
	for(i=0;i<chunknum;i++)
	{
		chunkptr=curchunkblockpr->chunkptr;
		//虽然原来有数据还是要计算一下
		chunkptr->fileid=filemetaptr->FileID;
		chunkptr->fmeta=filemetaptr;

		curchunkblockpr++;
	}
	return TRUE;
}

int profile_setup_file_fullchkpath(CHUNKPATH *chkpathptr,REGION *regionptr)
{
	CHUNK *chunkptr,*curchunkptr;
	CHUNKGROUP *chunkgroupptr;

	STRIPSECT *strsetptr,*curstrsetptr;
	STRIPSECTGROUP *strsetgroupptr;

	STRIP *stripptr,*curstripptr;
	STRIPGROUP *stripgroupptr;

	int chunkarrayid,stripsectarrayid,striparrayid,regionarrayid;

	chunkarrayid=chkpathptr->chunkarrayid;
	stripsectarrayid=chkpathptr->stripsectarrayid;
	striparrayid=chkpathptr->striparrayid;
	regionarrayid=chkpathptr->regionarrayid;

	//只需要计算偏移量即可
	stripgroupptr=regionptr->striplist;
	stripptr=stripgroupptr->stripgroup;
	curstripptr=stripptr+striparrayid;

	strsetgroupptr=curstripptr->stripsectlist;
	strsetptr=strsetgroupptr->stripsectgroup;
	curstrsetptr=strsetptr+stripsectarrayid;

	chunkgroupptr=curstrsetptr->chunklist;
	chunkptr=chunkgroupptr->ckgroup;
	curchunkptr=chunkptr+chunkarrayid;

	//可以赋值了
	chkpathptr->chunkptr=curchunkptr;
	chkpathptr->stripsectptr=curstrsetptr;
	chkpathptr->stripptr=curstripptr;
	chkpathptr->regionptr=regionptr;
	return TRUE;
}


int profile_setup_parent_subfile_relation(FILEMETA *parentptr,FILEMETABLOCK *subfileblockptr,int subfilenum)
{
	int i;
	FILEMETABLOCK *cursubfileblockptr;
	FILEMETA *curfilemeatptr;
	parentptr->subfilelist=subfileblockptr;
	cursubfileblockptr=subfileblockptr;
	for(i=0;i<subfilenum;i++)
	{
		//进行赋值
		curfilemeatptr=cursubfileblockptr->filemetaptr;
		curfilemeatptr->parentptr=parentptr;
		cursubfileblockptr++;
	}
	return TRUE;
}
int profile_setup_file_dictionaryinformation(FILEMETA *filemetaptr,FILEMETABLOCKGROUP *filemetablockgroupptr)
{
	//建立相应的子目录结构
	int i,subfilenum,filetype;
	FILEMETABLOCK *fileblockptr;
	UINT64 *subidlist;
	int resTF;
	
	//当前数据
	filetype=filemetaptr->filetype;
	if(filetype==DICTKIND)
	{
		subfilenum=filemetaptr->subfilenum;
		fileblockptr=talloc(FILEMETABLOCK,subfilenum);
		if(fileblockptr==NULL)
		{
			show_error("profile","setup_file_dictionaryinformation","No memory");
			return FALSE;
		}
		subidlist=filemetaptr->subfileidlist;
		resTF=profile_filemeta_filemetablock_search(fileblockptr,subidlist,subfilenum,filemetablockgroupptr);
		if(resTF==FALSE)
		{
			show_error("profile","setup_file_dictionaryinformation","subfile can't find");
			return FALSE;
		}
		resTF=profile_setup_parent_subfile_relation(filemetaptr,fileblockptr,subfilenum);
		if(resTF==FALSE)
		{
			show_error("profile","setup_file_dictionaryinformation","subfile can't find");
			return FALSE;
		}
	}

		
	return TRUE;
}
int profile_setup_file_chunkinformation(FILEMETA *filemetaptr)
{
	int resTF;
	int i;

	FILEINF *fileinfptr;
	REGION *regionptr;
	CHUNKPATH *chkpathptr,*curchkpathptr;

	STRIPBLOCK *stripblockptr;
	UINT64 *stripidlist;
	int stripnum;

	STRIPSECTBLOCK *strsetblockptr;
	UINT64 *strsetidlist;
	int strsetnum;

	CHUNKBLOCK *chunkblockptr;
	UINT64 *chunkidlist;
	int chunknum;
	
	regionptr=filemetaptr->regionptr;
	fileinfptr=filemetaptr->filechunkinf;

	fileinfptr->fileid=filemetaptr->FileID;

	stripnum=fileinfptr->stripnum;
	stripblockptr=talloc(STRIPBLOCK,stripnum);
	if(stripblockptr==NULL)
	{
		show_error("profile","setup_file_chunkinformation","No memory");
		return FALSE;
	}

	strsetnum=fileinfptr->stripsectnum;
	strsetblockptr=talloc(STRIPSECTBLOCK,strsetnum);
	if(strsetblockptr==NULL)
	{
		show_error("profile","setup_file_chunkinformation","No memory");
		return FALSE;
	}

	chunknum=fileinfptr->chunknum;
	chunkblockptr=talloc(CHUNKBLOCK,chunknum);
	if(chunkblockptr==NULL)
	{
		show_error("profile","setup_file_chunkinformation","No memory");
		return FALSE;
	}

	chkpathptr=fileinfptr->chkpath;
	curchkpathptr=chkpathptr;
	for(i=0;i<chunknum;i++)
	{
		resTF=profile_setup_file_fullchkpath(curchkpathptr,regionptr);//数据
		if(resTF==FALSE)
		{
			show_error("profile","setup_file_chunkinformation","chkpath can't full");
			return FALSE;
		}
		curchkpathptr++;
	}
	//依次建立strip，stripsect，chunk指针
	stripidlist=fileinfptr->stripid;
	resTF=profile_strip_chunkpath_search(stripblockptr,stripidlist,stripnum,chkpathptr,chunknum);
	if(resTF==FALSE)
	{
		show_error("profile","setup_file_chunkinformation","stripblock can't setup");
		return FALSE;
	}

	strsetidlist=fileinfptr->stripsectid;
	resTF=profile_stripsect_chunkpath_search(strsetblockptr,strsetidlist,strsetnum,chkpathptr,chunknum);
	if(resTF==FALSE)
	{
		show_error("profile","setup_file_chunkinformation","stripsectblock can't setup");
		return FALSE;
	}

	chunkidlist=fileinfptr->chunkid;
	resTF=profile_chunk_chunkpath_search(chunkblockptr,chunkidlist,chkpathptr,chunknum);
	if(resTF==FALSE)
	{
		show_error("profile","setup_file_chunkinformation","chunkblock can't setup");
		return FALSE;
	}
	resTF=profile_chunk_fileinf(chunkblockptr,filemetaptr,chunknum);
	if(resTF==FALSE)
	{
		show_error("profile","setup_file_chunkinformation","chunk file information can't setup");
		return FALSE;
	}
	fileinfptr->regoinptr=regionptr;
	fileinfptr->striplist=stripblockptr;
	fileinfptr->stripsectlist=strsetblockptr;
	fileinfptr->chunklist=chunkblockptr;
	fileinfptr->filemeta=filemetaptr;//将数据
	return TRUE;
}

int profile_setup_file_diskinformation(FILEMETA *filemetaptr)
{
	int resTF;
	DISKBLOCK *diskblockptr;
	UINT64 *diskidlist;
	int filedisknum;
	FILEINF *fileinfptr;

	fileinfptr=filemetaptr->filechunkinf;

	diskidlist=fileinfptr->diskid;
	filedisknum=fileinfptr->disknum;

	diskblockptr=talloc(DISKBLOCK,filedisknum);
	if(diskblockptr==NULL)
	{
		show_error("profile","setup_file_diskinformation","No memory");
		return FALSE;
	}
	resTF=profile_disk_search(diskblockptr,diskidlist,filedisknum);
	if(resTF==FALSE)
	{
		show_error("profile","setup_file_diskinformation","diskblockptr can't find");
		return FALSE;
	}
	fileinfptr->disklist=diskblockptr;
	return TRUE;
}
int profile_setup_file_deviceinformation(FILEMETA *filemetaptr)
{
	int resTF;
	DEVICEBLOCK *deviceblockptr;
	//DEVICE *deviceptr;
	UINT64 *deviceidlist;
	//UINT64 curdeviceid;
	//int devicegroupsize;
	int filedevicenum;
	FILEINF *fileinfptr;

	fileinfptr=filemetaptr->filechunkinf;

	deviceidlist=fileinfptr->deviceid;
	filedevicenum=fileinfptr->devicenum;

	deviceblockptr=talloc(DEVICEBLOCK,filedevicenum);
	if(deviceblockptr==NULL)
	{
		show_error("profile","setup_file_deviceinformation","No memory");
		return FALSE;
	}
	
	//遍历当前设备库
	resTF=profile_device_search(deviceblockptr,deviceidlist,filedevicenum);
	if(resTF==FALSE)
	{
		show_error("profile","setup_file_deviceinformation","deviceblockptr can't find");
		return FALSE;
	}
	fileinfptr->devicelist=deviceblockptr;
	return TRUE;
}
int profile_setup_file_userinformation(FILEMETA *filemetaptr)
{
	int resTF;
	USERPROFILE *userprofileptr;//用户指针
	USERGROUP *glousergroupptr;//获取全局指针
	int userpronum;
	UINT64 userid;
	glousergroupptr=get_state_glousergroup_PTR();
	userprofileptr=glousergroupptr->userlist;
	userpronum=glousergroupptr->groupsize;
	userid=filemetaptr->userid;
	userprofileptr=profile_get_usergroup_ptr(userid,glousergroupptr);
	if(userprofileptr==NULL)
	{
		show_error("profile","setup_file_userinformation"," user information can't find");
		return FALSE;
	}
	filemetaptr->userinf=userprofileptr;//

	return TRUE;
}
int profile_setup_file_storeinformation(FILEMETA *filemetaptr)
{
	int resTF;
	resTF=profile_setup_file_deviceinformation(filemetaptr);
	if(resTF==FALSE)
	{
		show_error("profile","setup_file_storeinformation","device information can't setup");
		return FALSE;
	}
	resTF=profile_setup_file_diskinformation(filemetaptr);
	if(resTF==FALSE)
	{
		show_error("profile","setup_file_storeinformation","disk information can't setup");
		return FALSE;
	}
	resTF=profile_setup_file_chunkinformation(filemetaptr);
	if(resTF==FALSE)
	{
		show_error("profile","setup_file_storeinformation","disk information can't setup");
		return FALSE;
	}
	return TRUE;
}
//根据元数据文件夹中文件信息设置，文件系统逻辑结构
int profile_region_read_filemeta(REGION *regionptr)
{
	//读取文件元数据
	UINT64 regionid;//文件数
	int filenum;
	int i,j,k,filegroupsize,resTF;
	int filetype,subfilenum,filestripnum,filestrsetnum,filechunknum;
	UINT64 *fileid,curfileid;

	FILEMETABLOCKGROUP *filemetablockgroupptr;
	FILEMETA *filemetaptr,*curfilemetaptr;

	FILEMETABLOCK *filemetablockptr,*curfilemetablockptr;

	CHUNKPATH *chunkpath;
	//获取需要数据
	filenum=regionptr->filenum;
	filegroupsize=filenum;
	fileid=regionptr->fileid;
	regionid=regionptr->RegionID;
	filemetablockptr=talloc(FILEMETABLOCK,filenum);//权宜之计32位
	if(filemetablockptr==NULL)
	{
		show_error("profile","region_read_filemeta","No memory");
		return FALSE;
	}
	filemetablockgroupptr=talloc(FILEMETABLOCKGROUP,1);
	if(filemetablockgroupptr==NULL)
	{
		show_error("profile","region_read_filemeta","No memory");
		return FALSE;
	}
	regionptr->filemetalist=filemetablockgroupptr;
	filemetablockgroupptr->filemetablockptr=filemetablockptr;//将两个值赋值回去
	filemetablockgroupptr->groupsize=filenum;

	curfilemetablockptr=filemetablockptr;
	//先将数据
	for(i=0;i<filenum;i++)//读出根目录
	{
		//文件id
		curfileid=fileid[i];
		curfilemetaptr=talloc(FILEMETA,1);
		if(curfilemetaptr==NULL)
		{
			show_error("profile","region_read_filemeta","No Memory");
			return FALSE;
		}
		curfilemetaptr->FileID=curfileid;
		curfilemetaptr->regionid=regionid;
		
		resTF=FILELAYER_FILEMETA_READER(curfilemetaptr);//将数据读出
		if(resTF==FALSE)
		{
			show_error("profile","region_read_filemeta","filemeta information can't read");
			return FALSE;
		}
		curfilemetaptr->regionptr=regionptr;//将已知信息进行赋值
		filetype=curfilemetaptr->filetype;
		resTF=profile_setup_file_userinformation(curfilemetaptr);
		if(resTF==FALSE)
		{
			show_error("profile","region_read_filemeta","user information can't setup");
			return FALSE;
		}
		if(filetype!=DICTKIND)//如果当前不是目录类型读取相存储信息
		{
			resTF=profile_setup_file_storeinformation(curfilemetaptr);
			if(resTF==FALSE)
			{
				show_error("profile","region_read_filemeta","store information can't setup");
				return FALSE;
			}
		}
		curfilemetablockptr->filemetaptr=curfilemetaptr;
		curfilemetablockptr->FileID=curfilemetaptr->FileID;

		curfilemetablockptr++;
	}
	filemetaptr=filemetablockptr->filemetaptr;//找到根指针

	regionptr->fileroot=filemetaptr;
	regionptr->rootfileid=filemetaptr->FileID;

	curfilemetablockptr=filemetablockptr;
	//现在需要大搞指针
	for(i=0;i<filenum;i++)//开始建立相应的目录信息
	{
		curfilemetaptr=curfilemetablockptr->filemetaptr;
		resTF=profile_setup_file_dictionaryinformation(curfilemetaptr,filemetablockgroupptr);
		if(resTF==FALSE)
		{
			show_error("profile","region_read_filemeta","dictionaryinformation can't create");
			return FALSE;
		}
		curfilemetablockptr++;
	}
	printf("region filemeta has created\n");
	return TRUE;
}
int profile_region_datafile_create(REGION *regionptr)
{
	int i,j,stripgroupsize,strsetgroupsize,resTF;

	STRIPGROUP *stripgroupptr;
	STRIP *stripptr,*curstripptr;

	STRIPSECTGROUP *strsetgroupptr;
	STRIPSECT *strsetptr,*curstrsetptr;

	stripgroupptr=regionptr->striplist;
	stripptr=stripgroupptr->stripgroup;
	stripgroupsize=stripgroupptr->groupsize;

	//char *filepath;

	curstripptr=stripptr;
	for(i=0;i<stripgroupsize;i++)
	{
		strsetgroupptr=curstripptr->stripsectlist;
		strsetptr=strsetgroupptr->stripsectgroup;
		strsetgroupsize=strsetgroupptr->groupsize;

		curstrsetptr=strsetptr;
		for(j=0;j<strsetgroupsize;j++)
		{
			//filepath=curstrsetptr->filepath;
			resTF=FILELAYER_STRIPSECT_CREATE(curstrsetptr);//创建一个strset组块
			if(resTF==FALSE)
			{
				show_error("profile","region_datafile_create","stripsect datafile can't created");
				return FALSE;
			}
			curstrsetptr++;
		}
		curstripptr++;
	}
	return TRUE;
}
//通过regionptr的数据初始化
int profile_global_region_intial(REGION *regionptr)
{
	//初始化一个系统
	int resTF;
	
	resTF=profile_region_reader_PTR(regionptr);//读取region中的结构数据
	if(resTF==FALSE)
	{
		show_error("profile","global_region_intial","region information can't read");
		return FALSE;
	}
	resTF=profile_region_read_filemeta(regionptr);//读取region中的文件数据
	if(resTF==FALSE)
	{
		show_error("profile","global_region_intial","region filemeta can't read");
		return FALSE;
	}
	resTF=profile_region_datafile_create(regionptr);//生成相应的stripsect数据文件
	if(resTF==FALSE)
	{
		show_error("profile","global_region_intial","region data can't create");
		return FALSE;
	}
	return TRUE;
}
//初始化region数据不不进行datafile创建
int profile_global_region_intial_without_datafile(REGION *regionptr)
{
	//初始化一个系统
	int resTF;
	
	resTF=profile_region_reader_PTR(regionptr);//读取region中的结构数据
	if(resTF==FALSE)
	{
		show_error("profile","global_region_intial","region information can't read");
		return FALSE;
	}
	resTF=profile_region_read_filemeta(regionptr);//读取region中的文件数据
	if(resTF==FALSE)
	{
		show_error("profile","global_region_intial","region filemeta can't read");
		return FALSE;
	}
	return TRUE;
}
//
int profile_global_region_destroy(REGION *regionptr)//未完成
{
	return TRUE;
}


//全局初始化
//初始化disk,device,user,region数据读取,
int profile_global_system_intial_basic()
{
	
	int resTF;

	resTF=profile_global_define_reader();//先读取id//处理当前pushlist
	if(resTF==FALSE)
	{
		show_error("profile","global_system_intial","global_define can't read");
		return FALSE;
	}

	//读取四大原始元数据
	//region数据
	
	resTF=profile_region_reader();
	if(resTF==FALSE)
	{
		show_error("profile","global_system_intial","region information can't read");
		return FALSE;
	}
	
	//userprofile数据
	resTF=profile_userprofile_reader();
	if(resTF==FALSE)
	{
		show_error("profile","global_system_intial","userprofile information can't read");
		return FALSE;
	}
	//device数据
	resTF=profile_device_reader();
	if(resTF==FALSE)
	{
		show_error("profile","global_system_intial","device information can't read");
		return FALSE;
	}
	//disk数据
	resTF=profile_disk_reader();
	if(resTF==FALSE)
	{
		show_error("profile","global_system_intial","disk information can't read");
		return FALSE;
	}
	
	//处理当前脏数据列表
	resTF=profile_dirtydata_intial();
	if(resTF==FALSE)
	{
		show_error("profile","global_system_intial","disk information can't read");
		return FALSE;
	}
	printf("region basic information has created\n");
	return TRUE;
}
int profile_global_system_intial()
{
	REGIONGROUP *regionlist;
	REGION *regionptr;
	int i,resTF,reggroupsize;
	resTF=profile_global_system_intial_basic();
	if(resTF==FALSE)
	{
		show_error("profile","global_system_intial","basic intial fail");
	}
	//读取region中的元数据
	regionlist=get_state_gloregiongroup_PTR();
	regionptr=regionlist->regiongroup;
	reggroupsize=regionlist->groupsize;
	for(i=0;i<reggroupsize;i++)
	{
		resTF=profile_global_region_intial(regionptr);//初始化一个region
		if(resTF==FALSE)
		{
			show_error("profile","global_system_intial","region inital");
			return FALSE;
		}
		regionptr++;
	}
	
	return TRUE;
}
int profile_global_system_intial_without_datafile()
{
	REGIONGROUP *regionlist;
	REGION *regionptr;
	int i,resTF,reggroupsize;
	resTF=profile_global_system_intial_basic();
	if(resTF==FALSE)
	{
		show_error("profile","global_system_intial","basic intial fail");
		return FALSE;
	}
	//读取region中的元数据
	regionlist=get_state_gloregiongroup_PTR();
	regionptr=regionlist->regiongroup;
	reggroupsize=regionlist->groupsize;
	for(i=0;i<reggroupsize;i++)
	{
		resTF=profile_global_region_intial_without_datafile(regionptr);//初始化一个region
		if(resTF==FALSE)
		{
			show_error("profile","global_system_intial","region inital");
			return FALSE;
		}
		regionptr++;
	}
	return TRUE;
}

int profile_global_system_intial_by_REGION(REGION *regionptr)
{
	int resTF;

	resTF=profile_global_system_intial_basic();
	if(resTF==FALSE)
	{
		show_error("profile","global_system_intial","basic intial fail");
	}

	resTF=profile_global_region_intial(regionptr);//初始化一个region
	if(resTF==FALSE)
	{
		show_error("profile","global_system_intial","region inital");
		return FALSE;
	}
	return TRUE;
}
//从当前目录中文件读出元数据文件夹位置
int profile_set_metapath(char *filename)
{
	set_state_glopath(filename);
	return TRUE;
}
//gloabl-define同步
int profile_globaldefine_sync()
{
	//REGION,USERPROFILE,DEVICE,DISK
	GLOSYSTEMID *systemid;
	int i,resTF,regiongroupsize,usergroupsize,devicegroupsize,diskgroupsize;
	UINT64 *regionidlist,*useridlist,*deviceidlist,*diskidlist;
	REGION *regionptr,*curregionptr;
	REGIONGROUP *regiongroupptr;

	USERPROFILE *userprofileptr,*curuserprofileptr;
	USERGROUP *usergroupptr;

	DEVICE *deviceptr,*curdeviceptr;
	DEVICEGROUP *devicegroupptr;

	DISK *diskptr,*curdiskptr;
	DISKGROUP *diskgroupptr;
	//获取全局的systemid指针
	systemid=get_state_glosystemidgroup_PTR();

	//获取全局的指针
	regiongroupptr=get_state_gloregiongroup_PTR();
	usergroupptr=get_state_glousergroup_PTR();
	devicegroupptr=get_state_glodevicegroup_PTR();
	diskgroupptr=get_state_glodiskgroup_PTR();

	regionptr=regiongroupptr->regiongroup;
	regiongroupsize=regiongroupptr->groupsize;

	userprofileptr=usergroupptr->userlist;
	usergroupsize=usergroupptr->groupsize;

	deviceptr=devicegroupptr->devicegroup;
	devicegroupsize=devicegroupptr->groupsize;

	diskptr=diskgroupptr->diskgroup;
	diskgroupsize=diskgroupptr->groupsize;
	//开regionid空间
	regionidlist=systemid->regionid;
	if(regionidlist!=NULL)
	{
		free(regionidlist);
	}
	regionidlist=talloc(UINT64,regiongroupsize);
	if(regionidlist==NULL)
	{
		show_error("profile","globaldefine_sync","No memory");
		return FALSE;
	}
	systemid->regionid=regionidlist;
	//开userid空间
	useridlist=systemid->userid;
	if(useridlist!=NULL)
	{
		free(useridlist);
	}
	useridlist=talloc(UINT64,usergroupsize);
	if(useridlist==NULL)
	{
		show_error("profile","globaldefine_sync","No memory");
		return FALSE;
	}
	systemid->userid=useridlist;
	//开deviceid空间
	deviceidlist=systemid->deviceid;
	if(deviceidlist!=NULL)
	{
		free(deviceidlist);
	}
	deviceidlist=talloc(UINT64,devicegroupsize);
	if(deviceidlist==NULL)
	{
		show_error("profile","globaldefine_sync","No memory");
		return FALSE;
	}
	systemid->deviceid=deviceidlist;
	//开diskid空间
	diskidlist=systemid->diskid;
	if(diskidlist!=NULL)
	{
		free(diskidlist);
	}
	diskidlist=talloc(UINT64,diskgroupsize);
	if(diskidlist==NULL)
	{
		show_error("profile","globaldefine_sync","No memory");
		return FALSE;
	}
	systemid->diskid=diskidlist;

	//生成id列表
	curregionptr=regionptr;
	for(i=0;i<regiongroupsize;i++)
	{
		regionidlist[i]=curregionptr->RegionID;
		curregionptr++;
	}
	curuserprofileptr=userprofileptr;
	for(i=0;i<usergroupsize;i++)
	{
		useridlist[i]=curuserprofileptr->UserID;
		curuserprofileptr++;
	}
	curdeviceptr=deviceptr;
	for(i=0;i<devicegroupsize;i++)
	{
		deviceidlist[i]=curdeviceptr->DeviceID;
		curdeviceptr++;
	}
	curdiskptr=diskptr;
	for(i=0;i<diskgroupsize;i++)
	{
		diskidlist[i]=curdiskptr->DiskID;
		curdiskptr++;
	}
	
	systemid->gloregiongroup=regiongroupptr;
	systemid->regionnum=regiongroupsize;

	systemid->glousergroup=usergroupptr;
	systemid->usernum=usergroupsize;

	systemid->glodevicegroup=devicegroupptr;
	systemid->devicenum=devicegroupsize;

	systemid->glodiskgroup=diskgroupptr;
	systemid->disknum=diskgroupsize;
	//然后同步systemnextid
	systemid->systemnextid=get_SYSID_PTR();
	//同步种类
	systemid->availnum=get_state_avail_kind_number();
	systemid->availkind=get_state_avail_kind();
	//同步pushtime
	systemid->glopushtime=get_state_buffer_push_time();
	resTF=FILELAYER_GLOSYSTEMID_WRITER(systemid);;
	if(resTF==FALSE)
	{
		show_error("profile","globaldefine_sync","globaldefine can't write");
		return FALSE;
	}
	return TRUE;
}
//将内存元数据同步到磁盘上,相对较为简单
int profile_region_sync(REGION *regionptr)//元数据同步到磁盘 
{
	//region信息
	REGION *curregionptr;
	STRIPGROUP *stripgroup;
	STRIP *curstripptr;
	STRIPSECTGROUP *strsetgroup;
	STRIPSECT *curstrsetptr;
	CHUNK *curchunkptr;
	CHUNKGROUP *chkgroup;

	int i,j,k,resTF;
	int strgroupsize,strsetgroupsize,chkgroupsize;
	UINT64 nowregionid,nowstripid,nowstrsetid;
	curregionptr=regionptr;
	//给出当前
	nowregionid=regionptr->RegionID;
	//写入region
	resTF=FILELAYER_REGION_WRITER(curregionptr);
	if(resTF=FALSE)
	{
		show_error("profile","region_sync","region writer failed");
		return FALSE;
	}
	stripgroup=curregionptr->striplist;
	curstripptr=stripgroup->stripgroup;
	strgroupsize=stripgroup->groupsize;
	
	for(i=0;i<strgroupsize;i++)
	{
		
		
		//写入strip
		
		resTF=FILELAYER_STRIP_WRITER(curstripptr);
		if(resTF==FALSE)
		{
			show_error("profile","region_sync","strip writer failed");
			return FALSE;
		}
		strsetgroup=curstripptr->stripsectlist;
		curstrsetptr=strsetgroup->stripsectgroup;
		strsetgroupsize=strsetgroup->groupsize;
		nowstripid=curstripptr->StripID;
		
		for(j=0;j<strsetgroupsize;j++)
		{
			//写入stripsect
			resTF=FILELAYER_STRIPSECT_WRITER(curstrsetptr);
			if(resTF==FALSE)
			{
				show_error("profile","region_sync","stripsect writer failed");
				return FALSE;
			}
			chkgroup=curstrsetptr->chunklist;
			curchunkptr=chkgroup->ckgroup;
			chkgroupsize=chkgroup->groupsize;
			nowstrsetid=curstrsetptr->StripsectID;
			//需要先检测文件夹是否存在
			/*resTF=file_FILELAYER_dictionary_stripsect_exists(nowregionid,nowstripid,nowstrsetid);
			if(resTF==FALSE)
			{
				show_error("profile","region_sync","dictionary can't create");
				return FALSE;
			}*/
			for(k=0;k<chkgroupsize;k++)
			{
				//写入chunk
				resTF=FILELAYER_CHUNK_WRITER_META(curchunkptr);
				if(resTF==FALSE)
				{
					show_error("profile","region_sync","chunk writer failed");
					return FALSE;
				}
				curchunkptr++;
			}
			curstrsetptr++;
		}
		curstripptr++;
	}
	
	return TRUE;
}
//将文件元数据同步
int profile_filemeta_sync(REGION *regionptr)
{
	
	FILEMETABLOCKGROUP *fmetablockgroupptr;
	FILEMETABLOCK *fmetablockptr,*curfmetablockptr;
	FILEMETA *filemetaptr;
	int i,fmetagroupsize;
	//先赋值
	fmetablockgroupptr=regionptr->filemetalist;
	fmetablockptr=fmetablockgroupptr->filemetablockptr;
	fmetagroupsize=fmetablockgroupptr->groupsize;
	curfmetablockptr=fmetablockptr;
	for(i=0;i<fmetagroupsize;i++)
	{
		filemetaptr=curfmetablockptr->filemetaptr;
		FILELAYER_FILEMETA_WRITER(filemetaptr);
		curfmetablockptr++;
	}
	return TRUE;
}
//将device和disk元数据同步到磁盘
int profile_device_disk_sync()
{
	DEVICEGROUP *devicegroupptr;
	DEVICE *deviceptr,*curdeviceptr;
	DISKBLOCK *diskblockptr,*curdiskblockptr;
	DISK *diskptr;
	int i,j,diskblocksize,devicegroupsize,resTF;
	UINT64 curdeviceid;
	//赋值
	devicegroupptr=get_state_glodevicegroup_PTR();
	deviceptr=devicegroupptr->devicegroup;
	devicegroupsize=devicegroupptr->groupsize;
	curdeviceptr=deviceptr;
	for(i=0;i<devicegroupsize;i++)
	{
		//第一步进行device判断
		curdeviceid=curdeviceptr->DeviceID;
		/*resTF=file_FILELAYER_dictionary_device_exists(curdeviceid);
		if(resTF==FALSE)
		{
			show_error("profile","device_disk_sync","DICpath can't create");
			return FALSE;
		}*/
		resTF=FILELAYER_DEVICE_WRITER(curdeviceptr);
		if(resTF==FALSE)
		{
			show_error("profile","device_disk_sync","Device information can't write");
			return FALSE;
		}
		diskblockptr=curdeviceptr->disklist;
		diskblocksize=curdeviceptr->disknum;

		curdiskblockptr=diskblockptr;
		for(j=0;j<diskblocksize;j++)
		{
			diskptr=curdiskblockptr->diskptr;
			resTF=FILELAYER_DISK_WRITER(diskptr);
			if(resTF==FALSE)
			{
				show_error("profile","device_disk_sync","disk can't write");
				return FALSE;
			}
			diskblockptr++;
		}
		curdeviceptr++;
	}
	return TRUE;
}
//用户信息同步到
int profile_userprofile_sync()
{
	int i,usergroupsize,resTF;
	USERGROUP *usergroupptr;
	USERPROFILE *userprofileptr,*curuserprofileptr;
	usergroupptr=get_state_glousergroup_PTR();
	usergroupsize=usergroupptr->groupsize;
	userprofileptr=usergroupptr->userlist;

	curuserprofileptr=userprofileptr;
	/*
	resTF=file_FILELAYER_dictionary_userprofile_exists(0);
	if(resTF==FALSE)
	{
		show_error("profile","userprofile_sync","userprofilr information can't write");
		return FALSE;
	}*/
	for(i=0;i<usergroupsize;i++)
	{
		resTF=FILELAYER_USERPROFILE_WRITER(curuserprofileptr);
		if(resTF==FALSE)
		{
			show_error("profile","userprofile_sync","userprofilr information can't write");
			return FALSE;
		}
		curuserprofileptr++;
	}
	return TRUE;
}
//根据元数据文件中的chunk中数据
int profile_GLOBAL_chunk_data_sync()
{
	CHUNKBLOCK *chunkblockptr;
	CHUNK *curchunkptr;
	GLOPUSHLIST *pushlist;
	int i,chunkblocksize;
	pushlist=get_state_buffer_pushlist();
	chunkblockptr=pushlist->glopushchunklist;
	chunkblocksize=pushlist->chunknum;
	/*chunkptr=chunkgroupptr->ckgroup;
	chunkgroupsize=chunkgroupptr->groupsize;
	curchunkptr=chunkptr;*/
	for(i=0;i<chunkblocksize;i++)
	{
		curchunkptr=chunkblockptr->chunkptr;
		FILELAYER_CHUNK_WRITER_DATA(curchunkptr);
		chunkblockptr++;
	}
	//同步完成释放空间,并且防止野指针
	free(chunkblockptr);

	chunkblockptr=NULL;
	chunkblocksize=0;

	pushlist->glopushchunklist=chunkblockptr;
	pushlist->chunknum=0;
	return TRUE;
}

//元数据同步
int profile_metadata_sync()
{
	int i,regiongroupsize,resTF;
	REGION *regionptr,*curregionptr;
	REGIONGROUP *regiongroupptr;
	regiongroupptr=get_state_gloregiongroup_PTR();

	regiongroupsize=regiongroupptr->groupsize;
	regionptr=regiongroupptr->regiongroup;

	curregionptr=regionptr;
	for(i=0;i<regiongroupsize;i++)
	{
		if(curregionptr->RegionID!=NOVALUE)
		{
			resTF=profile_region_sync(curregionptr);
			if(resTF==FALSE)
			{
				show_error("profile","metadata_sync","region information can't snyc");
				return FALSE;
			}
			show_message("region synchronization finish.");
			resTF=profile_filemeta_sync(curregionptr);
			if(resTF==FALSE)
			{
				show_error("profile","metadata_sync","fmeta information can't snyc");
				return FALSE;
			}
			show_message("file metadate synchronization finish.");
		}
		curregionptr++;
	}
	resTF=profile_device_disk_sync();
	if(resTF==FALSE)
	{
		show_error("profile","metadata_sync","device_disk information can't snyc");
		return FALSE;
	}
	show_message("device synchronization finish.");
	resTF=profile_userprofile_sync();
	if(resTF==FALSE)
	{
		show_error("profile","metadata_sync","userprofile information can't snyc");
		return FALSE;
	}
	show_message("userprofile synchronization finish.");
	resTF=profile_globaldefine_sync();
	if(resTF==FALSE)
	{
		show_error("profile","metadata_sync","globaldefine information can't snyc");
		return FALSE;
	}
	show_message("globaldefine synchronization finish.");
	return TRUE;
}
//8个脏数据列表
//设定全局脏数据
int profile_dirtydata_set_data(CHUNKBLOCK *chunkblockptr,int chunknum,
										STRIPSECTBLOCK *stripsectblockptr,int stripsectnum,
										STRIPBLOCK *stripblockptr,int stripnum,
										REGIONBLOCK *regionblockptr,int regionnum,
										FILEMETABLOCK *filemetablockptr,int filemtetanum,
										DEVICEBLOCK *deviceblockptr,int devicenum,
										DISKBLOCK *diskblockptr,int disknum,
										USERBLOCK *userblockptr,int usernum
										)
{
	GLODIRTYDATA *dirtydata;
	dirtydata=get_state_dirtydatalist();//获取全局脏数据指针

	dirtydata->chunkblockptr=chunkblockptr;
	dirtydata->chunknum=chunknum;

	dirtydata->stripsectblockptr=stripsectblockptr;
	dirtydata->stripsectnum=stripsectnum;

	dirtydata->stripblockptr=stripblockptr;
	dirtydata->stripnum=stripnum;

	dirtydata->regionblockptr=regionblockptr;
	dirtydata->regionnum=regionnum;

	dirtydata->filemetablockptr=filemetablockptr;
	dirtydata->filemtetanum=filemtetanum;

	dirtydata->deviceblockptr=deviceblockptr;
	dirtydata->devicenum=devicenum;

	dirtydata->diskblockptr=diskblockptr;
	dirtydata->disknum=disknum;

	dirtydata->userblockptr=userblockptr;
	dirtydata->usernum=usernum;

	return TRUE;
}

//region脏数据同步
int profile_dirtydata_region_sync()
{
	GLODIRTYDATA *dirtydataptr;
	int i,resTF;
	int regionnum;

	REGION *curregionptr;
	REGIONBLOCK *regionblockptr;

	dirtydataptr=get_state_dirtydatalist();

	regionnum=dirtydataptr->regionnum;
	regionblockptr=dirtydataptr->regionblockptr;

	//如果没有数据不需要同步
	if(regionblockptr==NULL)
	{
		return TRUE;
	}

	for(i=0;i<regionnum;i++)
	{
		curregionptr=regionblockptr->regionptr;
		resTF=FILELAYER_REGION_WRITER(curregionptr);
		if(resTF==FALSE)
		{
			show_error("profile","dirtydata_sync","region metadata can't write");
			return FALSE;
		}
		regionblockptr++;
	}
	if(regionnum!=0)//如果不为空释放指针将其置NULL
	{
		regionblockptr=dirtydataptr->regionblockptr;
		free(regionblockptr);
		regionblockptr=NULL;
		dirtydataptr->regionblockptr=regionblockptr;
	}

	return TRUE;
}
//strip脏数据同步
int profile_dirtydata_strip_sync()
{
	GLODIRTYDATA *dirtydataptr;
	int i,resTF;
	int stripnum;

	STRIP *curstripptr;
	STRIPBLOCK *stripblockptr;

	dirtydataptr=get_state_dirtydatalist();

	
	stripnum=dirtydataptr->stripnum;
	stripblockptr=dirtydataptr->stripblockptr;

	//如果没有数据不需要同步
	if(stripblockptr==NULL)
	{
		return TRUE;
	}

	for(i=0;i<stripnum;i++)
	{
		curstripptr=stripblockptr->stripptr;
		resTF=FILELAYER_STRIP_WRITER(curstripptr);
		if(resTF==FALSE)
		{
			show_error("profile","dirtydata_sync","strip metadata can't write");
			return FALSE;
		}
		stripblockptr++;
	}
	if(stripnum!=0)
	{
		stripblockptr=dirtydataptr->stripblockptr;
		free(stripblockptr);
		stripblockptr=NULL;
		dirtydataptr->stripblockptr=stripblockptr;
	}
	return TRUE;
}
//stripsect脏数据同步
int profile_dirtydata_stripsect_sync()
{
	GLODIRTYDATA *dirtydataptr;
	int i,resTF;
	int strsetnum;

	STRIPSECT *curstrsectptr;
	STRIPSECTBLOCK *strsetblockptr;

	dirtydataptr=get_state_dirtydatalist();

	
	strsetnum=dirtydataptr->stripsectnum;
	strsetblockptr=dirtydataptr->stripsectblockptr;

	//如果没有数据不需要同步
	if(strsetblockptr==NULL)
	{
		return TRUE;
	}

	for(i=0;i<strsetnum;i++)
	{
		curstrsectptr=strsetblockptr->stripsectptr;
		resTF=FILELAYER_STRIPSECT_WRITER(curstrsectptr);
		if(resTF==FALSE)
		{
			show_error("profile","dirtydata_sync","stripsect metadata can't write");
			return FALSE;
		}
		strsetblockptr++;
	}
	if(strsetnum!=0)
	{
		strsetblockptr=dirtydataptr->stripsectblockptr;
		free(strsetblockptr);
		strsetblockptr=NULL;
		dirtydataptr->stripsectblockptr=strsetblockptr;
	}
	return TRUE;
}
//chunk脏数据同步
int profile_dirtydata_chunk_sync()
{
	GLODIRTYDATA *dirtydataptr;
	int i,resTF;
	int chunknum;

	CHUNK *curchunkptr;
	CHUNKBLOCK *chunkblockptr;

	dirtydataptr=get_state_dirtydatalist();

	chunknum=dirtydataptr->chunknum;
	chunkblockptr=dirtydataptr->chunkblockptr;

	//如果没有数据不需要同步
	if(chunkblockptr==NULL)
	{
		return TRUE;
	}

	for(i=0;i<chunknum;i++)
	{
		curchunkptr=chunkblockptr->chunkptr;
		resTF=FILELAYER_CHUNK_WRITER_META(curchunkptr);
		if(resTF==FALSE)
		{
			show_error("profile","dirtydata_sync","chunk metadata can't write");
			return FALSE;
		}
		chunkblockptr++;
	}
	if(chunknum!=0)
	{
		chunkblockptr=dirtydataptr->chunkblockptr;
		free(chunkblockptr);
		chunkblockptr=NULL;
		dirtydataptr->chunkblockptr=chunkblockptr;
	}
	return TRUE;
}
//device脏数据同步
int profile_dirtydata_device_sync()
{
	GLODIRTYDATA *dirtydataptr;
	int i,resTF;
	int devicenum;

	DEVICE *curdeviceptr;
	DEVICEBLOCK *deviceblockptr;

	dirtydataptr=get_state_dirtydatalist();
	devicenum=dirtydataptr->devicenum;
	deviceblockptr=dirtydataptr->deviceblockptr;

	//如果没有数据不需要同步
	if(deviceblockptr==NULL)
	{
		return TRUE;
	}

	for(i=0;i<devicenum;i++)
	{
		curdeviceptr=deviceblockptr->deviceptr;
		resTF=FILELAYER_DEVICE_WRITER(curdeviceptr);
		if(resTF==FALSE)
		{
			show_error("profile","dirtydata_sync","device metadata can't write");
			return FALSE;
		}
		deviceblockptr++;
	}
	if(devicenum!=0)
	{
		deviceblockptr=dirtydataptr->deviceblockptr;
		free(deviceblockptr);
		deviceblockptr=NULL;
		dirtydataptr->deviceblockptr=deviceblockptr;
	}

	return TRUE;
}
//disk脏数据同步
int profile_dirtydata_disk_sync()
{
	GLODIRTYDATA *dirtydataptr;
	int i,resTF;
	int disknum;

	DISK *curdiskptr;
	DISKBLOCK *diskblockptr;

	dirtydataptr=get_state_dirtydatalist();

	disknum=dirtydataptr->disknum;
	diskblockptr=dirtydataptr->diskblockptr;

	//如果没有数据不需要同步
	if(diskblockptr==NULL)
	{
		return TRUE;
	}

	for(i=0;i<disknum;i++)
	{
		curdiskptr=diskblockptr->diskptr;
		resTF=FILELAYER_DISK_WRITER(curdiskptr);
		if(resTF==FALSE)
		{
			show_error("profile","dirtydata_sync","disk metadata can't write");
			return FALSE;
		}
		diskblockptr++;
	}
	if(disknum!=0)
	{
		diskblockptr=dirtydataptr->diskblockptr;
		free(diskblockptr);
		diskblockptr=NULL;
		dirtydataptr->diskblockptr=diskblockptr;
	}

	return TRUE;
}
//userprofile脏数据同步
int profile_dirtydata_userprofile_sync()
{
	GLODIRTYDATA *dirtydataptr;
	int i,resTF;
	int usernum;

	USERPROFILE *curuserprofileptr;
	USERBLOCK *userblockptr;

	dirtydataptr=get_state_dirtydatalist();

	usernum=dirtydataptr->usernum;
	userblockptr=dirtydataptr->userblockptr;

	//如果没有数据不需要同步
	if(userblockptr==NULL)
	{
		return TRUE;
	}

	for(i=0;i<usernum;i++)
	{
		curuserprofileptr=userblockptr->userprofileptr;
		resTF=FILELAYER_USERPROFILE_WRITER(curuserprofileptr);
		if(resTF==FALSE)
		{
			show_error("profile","dirtydata_sync","userprofile metadata can't write");
			return FALSE;
		}
		userblockptr++;
	}
	if(usernum!=0)
	{
		userblockptr=dirtydataptr->userblockptr;
		free(userblockptr);
		userblockptr=NULL;
		dirtydataptr->userblockptr=userblockptr;
	}
	return TRUE;
}
//filemeta脏数据同步
int profile_dirtydata_filemeta_sync()
{
	GLODIRTYDATA *dirtydataptr;
	int i,resTF;
	int filenum;

	FILEMETA *curfilemetaptr;
	FILEMETABLOCK *fileblockptr;

	dirtydataptr=get_state_dirtydatalist();

	filenum=dirtydataptr->filemtetanum;
	fileblockptr=dirtydataptr->filemetablockptr;

	//如果没有数据不需要同步
	if(fileblockptr==NULL)
	{
		return TRUE;
	}

	for(i=0;i<filenum;i++)
	{
		curfilemetaptr=fileblockptr->filemetaptr;
		resTF=FILELAYER_FILEMETA_WRITER(curfilemetaptr);
		if(resTF==FALSE)
		{
			show_error("profile","dirtydata_sync","filemeta metadata can't write");
			return FALSE;
		}
		fileblockptr++;
	}
	if(filenum!=0)
	{
		fileblockptr=dirtydataptr->filemetablockptr;
		free(fileblockptr);
		fileblockptr=NULL;
		dirtydataptr->filemetablockptr=fileblockptr;
	}
	return TRUE;
}
//总体脏数据同步
int profile_dirtydata_sync()
{
	//更具脏数据列表同步数据
	//GLODIRTYDATA *dirtydataptr;
	int resTF;

	resTF=profile_dirtydata_region_sync();
	if(resTF==FALSE)
	{
		show_error("profile","dirtydata_sync","region can't synchronization");
		return FALSE;
	}
	
	resTF=profile_dirtydata_strip_sync();
	if(resTF==FALSE)
	{
		show_error("profile","dirtydata_sync","strip can't synchronization");
		return FALSE;
	}

	resTF=profile_dirtydata_stripsect_sync();
	if(resTF==FALSE)
	{
		show_error("profile","dirtydata_sync","stripsect can't synchronization");
		return FALSE;
	}
	
	resTF=profile_dirtydata_chunk_sync();
	if(resTF==FALSE)
	{
		show_error("profile","dirtydata_sync","chunk can't synchronization");
		return FALSE;
	}
	
	resTF=profile_dirtydata_device_sync();
	if(resTF==FALSE)
	{
		show_error("profile","dirtydata_sync","device can't synchronization");
		return FALSE;
	}

	resTF=profile_dirtydata_disk_sync();
	if(resTF==FALSE)
	{
		show_error("profile","dirtydata_sync","disk can't synchronization");
		return FALSE;
	}

	resTF=profile_dirtydata_userprofile_sync();
	if(resTF==FALSE)
	{
		show_error("profile","dirtydata_sync","userprofile can't synchronization");
		return FALSE;
	}

	resTF=profile_dirtydata_filemeta_sync();
	if(resTF==FALSE)
	{
		show_error("profile","dirtydata_sync","filemeta can't synchronization");
		return FALSE;
	}

	return TRUE;
}
//分配更新chunkstate
int profile_update_allocate_chunkstate(CHUNKPATH *chkpath)
{
	REGION *regionptr;
	STRIP *stripptr;
	STRIPSECT *strsetptr;
	CHUNK *chunkptr;

	CODEPARA *codeparamptr;
	STRIPDES *stripdesptr;
	//当前状态
	int maxchunknum,datasectnum;
	int currentstate;
	//从低到高释放块
	chunkptr=chkpath->chunkptr;
	strsetptr=chkpath->stripsectptr;
	stripptr=chkpath->stripptr;
	regionptr=chkpath->regionptr;
	//获取参数
	codeparamptr=regionptr->codepara;
	stripdesptr=regionptr->strdes;

	datasectnum=codeparamptr->datanum;
	maxchunknum=stripdesptr->chunknum;

	//更新数据
	chunkptr->storestate=FULL;

	currentstate=strsetptr->storestate+1;
	strsetptr->storestate=currentstate;
	//
	if(currentstate==maxchunknum)
	{
		
		//chunk数据已满本sytipsect存不下，该strip状态
		currentstate=stripptr->storestate+1;
		stripptr->storestate=currentstate;
		if(currentstate==datasectnum)
		{
			//需要改动region状态
			currentstate=regionptr->storestate+1;
			regionptr->storestate=currentstate;
		}
		
	}
	return TRUE;
}

//释放更新chunkstate
int profile_update_free_chunkstate(CHUNKPATH *chkpath)
{
	REGION *regionptr;
	STRIP *stripptr;
	STRIPSECT *strsetptr;
	CHUNK *chunkptr;
	//当前状态
	int currentstate;
	//从低到高释放块
	chunkptr=chkpath->chunkptr;
	strsetptr=chkpath->stripsectptr;
	stripptr=chkpath->stripptr;
	regionptr=chkpath->regionptr;
	//更新数据
	
	chunkptr->storestate=EMPTY;

	currentstate=strsetptr->storestate-1;
	strsetptr->storestate=currentstate;

	if(currentstate==EMPTY)
	{
		//当前状态减1
		currentstate=stripptr->storestate-1;
		stripptr->storestate=currentstate;
		if(currentstate==EMPTY)
		{
			currentstate=regionptr->storestate-1;
			regionptr->storestate=currentstate;
		}
	}
	return TRUE;
}

//块分配算法
CHUNKPATH *profile_allocate_chunk_data(REGION *regionptr)
{
	CHUNKPATH *chkpath=NULL;

	int i,j,k,isparity,resTF;
	int currentstate;
	int regionindex;

	UINT64 chunksize64,chunknum64;
	UINT64 strsetsize64;
	UINT64 stripsize64;
	UINT64 totalsize64;
	UINT64 disknum64;

	CODEPARA *codeparamptr;
	STRIPDES *stripdesptr;

	int datasectnum,codesectnum;
	int maxchunknum;//最大chunk上限
	int maxstripnum;

	
	STRIPGROUP *stripgroupptr;
	STRIP *stripptr,*curstripptr;
	int stripnum;

	STRIPSECTGROUP *strsectgroupptr;
	STRIPSECT *strsetptr,*curstrsetptr;
	int strsetnum;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;
	int chunknum;
	
	regionindex=profile_region_search(regionptr);//安全性检查
	if(regionindex==PFALSE)
	{
		show_error("profile","allocate_chunk_data","region is found");
		return FALSE;
	}
	//计算数据
	codeparamptr=regionptr->codepara;//获取编码参数
	stripdesptr=regionptr->strdes;

	//第一步检查上限
	chunksize64=(UINT64)stripdesptr->chunksize;
	chunknum64=(UINT64)stripdesptr->chunknum;
	disknum64=(UINT64)stripdesptr->disknum;
	totalsize64=regionptr->totalsize;

	strsetsize64=calstripsectsize(chunksize64,chunknum64);
	stripsize64=calstripsize(strsetsize64,disknum64);
	maxstripnum=calstripnum(totalsize64,stripsize64);

	currentstate=regionptr->storestate;
	if(maxstripnum==currentstate)
	{
		show_error("profile","allocate_chunk_data","the space is full");
		return FALSE;
	}

	datasectnum=codeparamptr->datanum;//strip中stripsect的上限
	codesectnum=codeparamptr->codenum;

	maxchunknum=stripdesptr->chunknum;//最大的machunk数

	stripgroupptr=regionptr->striplist;
	stripptr=stripgroupptr->stripgroup;
	stripnum=stripgroupptr->groupsize;

	chkpath=talloc(CHUNKPATH,1);
	if(chkpath==NULL)
	{
		show_error("profile","allocate_chunk_data","No memory");
		return FALSE;
	}

	curstripptr=stripptr;
	for(i=0;i<stripnum;i++)
	{
 		currentstate=curstripptr->storestate;
		//当前数据
		if(currentstate<datasectnum)
		{
			strsectgroupptr=curstripptr->stripsectlist;

			strsetptr=strsectgroupptr->stripsectgroup;
			strsetnum=strsectgroupptr->groupsize;

			curstrsetptr=strsetptr;
			for(j=0;j<strsetnum;j++)
			{
				isparity=curstrsetptr->isparity;//看看是不是校验块
				if(isparity==TRUE)
				{
					curstrsetptr++;
					continue;
				}
				currentstate=curstrsetptr->storestate;
				//当前数据
				if(currentstate<maxchunknum)
				{
					chunkgroupptr=curstrsetptr->chunklist;

					chunkptr=chunkgroupptr->ckgroup;
					chunknum=chunkgroupptr->groupsize;

					curchunkptr=chunkptr;
					for(k=0;k<chunknum;k++)
					{
						currentstate=curchunkptr->storestate;
						if(currentstate==EMPTY)//分配一个空块
						{
							//找到了chunkpath
							chkpath->chunkid=curchunkptr->ChunkID;
							chkpath->chunkarrayid=k;
							chkpath->chunkptr=curchunkptr;

							chkpath->stripsectid=curstrsetptr->StripsectID;
							chkpath->stripsectarrayid=j;
							chkpath->stripsectptr=curstrsetptr;

							chkpath->stripid=curstripptr->StripID;
							chkpath->striparrayid=i;
							chkpath->stripptr=curstripptr;

							chkpath->regionid=regionptr->RegionID;
							chkpath->regionarrayid=regionindex;
							chkpath->regionptr=regionptr;
							//更新状态
							resTF=profile_update_allocate_chunkstate(chkpath);
							if(resTF==FALSE)
							{
								show_error("profile","allocate_chunk_data","chkpath can't calcualte");
								return NULL;
							}
							return chkpath;
						}
						curchunkptr++;
					}
				}
				curstrsetptr++;
			}
		}
		curstripptr++;
	}
	
	return NULL;
}

//释放数据块
int profile_free_chunk_ptr(CHUNKPATH *chkpath)
{
	int resTF;
	CHUNK *chunkptr;
	//BYTESTREAM *bytestreamptr;
	BYTE *byteptr;
	int currentstate;
	chunkptr=chkpath->chunkptr;
	currentstate=chunkptr->storestate;
	if(currentstate==EMPTY)
	{
		show_error("profile","free_chunk_data","the chunk empty");
		return FALSE;
	}

	byteptr=chunkptr->chunkcontent;
	if(byteptr!=NULL)
	{
		free(byteptr);
	}
	chunkptr->chunkcontent=NULL;

	resTF=profile_update_free_chunkstate(chkpath);
	if(resTF==FALSE)
	{
		show_error("profile","free_chunk_data","chkpath can't calcualte");
		return FALSE;
	}
	
	return TRUE;
}
