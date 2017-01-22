#include "cauchy_org.h"
//原始cauchy RS编码RAID6接口
int cauchy_org_API_RAID6(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr)
{
	REGION *regionptr;
	CODEPARA *codeparamptr;
	BITMATRIX *matrix;
	UINT32 *mat;
	int datanum,codenum;
	int rows,cols,w,resTF;
	
	//生成矩阵
	matrix=talloc(BITMATRIX,1);
	if(matrix==NULL)
	{
		show_error("cauchy","org_API_RAID6","No memory");
		return FALSE;
	}
	regionptr=pparityptr->regionptr;
	codeparamptr=regionptr->codepara;

	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	w=codeparamptr->w;

	rows=codenum*w;
	cols=datanum*w;
	mat=talloc(UINT32,rows*cols);
	if(mat==NULL)
	{
		show_error("cauchy_org","API_RAID6","No memory");
		return FALSE;
	}
	matrix->matrix=mat;
	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w=w;
	resTF=cauchy_orgininal_coding_bitmatrix(matrix);
	if(resTF==FALSE)
	{
		show_error("cauchy_org","API_RAID6","bitmatrix can't create");
		return FALSE;
	}
	resTF=matrix_bitmatrix_encode_stripsect_RAID6(strsetblockgroupptr,pparityptr,qparityptr,matrix);
	if(resTF==FALSE)
	{
		show_error("cauchy_org","API_RAID6","cauchy_org RAID6 can't calculate");
		return FALSE;
	}
	free(matrix);
	free(mat);
	return TRUE;
}
//原始cauchy编码
int cauchy_org_API(STRIP *stripptr)
{
	BITMATRIX *matrix;

	REGION *regionptr;
	CODEPARA *codeparamptr;
	//STRIPSECT *strsetptr,*curstrsetptr;
	UINT32 *mat;
	int w,datanum,codenum,rows,cols,resTF;
	//生成矩阵
	matrix=talloc(BITMATRIX,1);
	if(matrix==NULL)
	{
		show_error("cauchy","org_API_RAID6","No memory");
		return FALSE;
	}
	regionptr=stripptr->regionptr;
	codeparamptr=regionptr->codepara;

	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	w=codeparamptr->w;

	rows=codenum*w;
	cols=datanum*w;
	mat=talloc(UINT32,rows*cols);
	if(mat==NULL)
	{
		show_error("cauchy_org","API_RAID6","No memory");
		return FALSE;
	}
	matrix->matrix=mat;
	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w;
	resTF=cauchy_orgininal_coding_bitmatrix(matrix);
	if(resTF==FALSE)
	{
		show_error("cauchy_org","API_RAID6","bitmatrix can't create");
		return FALSE;
	}

	free(matrix);
	free(mat);
	return TRUE;
}
//计算update
int cauchy_org_update_API_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr)
{
	BITMATRIX *matrix;

	REGION *regionptr;
	CODEPARA *codeparamptr;

	STRIPSECTGROUP *strsetgroupptr;
	STRIPSECT *strsetptr,*curstrsetptr;

	STRIPSECT *pparityptr,*qparityptr;

	STRIPSECTBLOCKGROUP *strsetblockgroupptr;
	STRIPSECTBLOCK *strsetblockptr,*curstrsetblockptr;
	int i,isparity;
	int strsetnum;

	//STRIPSECT *strsetptr,*curstrsetptr;
	UINT32 *mat;
	int w,datanum,codenum,rows,cols,resTF;
	//生成矩阵

	matrix=talloc(BITMATRIX,1);
	if(matrix==NULL)
	{
		show_error("cauchy","org_API_RAID6","No memory");
		return FALSE;
	}
	regionptr=stripptr->regionptr;
	codeparamptr=regionptr->codepara;

	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	w=codeparamptr->w;

	rows=codenum*w;
	cols=datanum*w;
	mat=talloc(UINT32,rows*cols);
	if(mat==NULL)
	{
		show_error("cauchy_org","update_API_RAID6","No memory");
		return FALSE;
	}
	matrix->matrix=mat;
	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w=w;

	strsetnum=datanum;
	strsetblockptr=talloc(STRIPSECTBLOCK,strsetnum);
	if(strsetblockptr==NULL)
	{
		show_error("cauchy_org","API_RAID6","No memory");
		return FALSE;
	}
	strsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(strsetblockgroupptr==NULL)
	{
		show_error("cauchy_org","API_RAID6","No memory");
		return FALSE;
	}
	strsetblockgroupptr->stripsectblockptr=strsetblockptr;
	strsetblockgroupptr->groupsize=strsetnum;

	strsetgroupptr=stripptr->stripsectlist;

	strsetptr=strsetgroupptr->stripsectgroup;
	strsetnum=strsetgroupptr->groupsize;

	curstrsetptr=strsetptr;
	curstrsetblockptr=strsetblockptr;
	for(i=0;i<strsetnum;i++)
	{
		isparity=curstrsetptr->isparity;
		if(isparity==FALSE)
		{
			curstrsetblockptr->stripsectptr=curstrsetptr;
			curstrsetblockptr->stripsectid=curstrsetptr->StripsectID;
			curstrsetblockptr++;
		}
		if(isparity==PPARITY)
		{
			pparityptr=curstrsetptr;
		}
		if(isparity==QPARITY)
		{
			qparityptr=curstrsetptr;
		}
		curstrsetptr++;
	}
	
	resTF=cauchy_orgininal_coding_bitmatrix(matrix);
	if(resTF==FALSE)
	{
		show_error("cauchy_org","API_RAID6","bitmatrix can't create");
		return FALSE;
	}
	resTF=UPDATE_API_bitmatrix_update_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
											pparityptr,qparityptr,parityblockgroupptr,matrix);
	if(resTF==FALSE)
	{
		show_error("cauchy_org","API_RAID6","update can't execute");
		return FALSE;
	}
	free(matrix);
	free(mat);
	free(strsetblockptr);
	free(strsetblockgroupptr);
	return TRUE;
}
extern int cauchy_org_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr)
{
	BITMATRIX *matrix;

	REGION *regionptr;
	CODEPARA *codeparamptr;
	STRIPSECT *strsetptr,*curstrsetptr;
	UINT32 *mat;
	int w,datanum,codenum,rows,cols,resTF;
	//生成矩阵
	matrix=talloc(BITMATRIX,1);
	if(matrix==NULL)
	{
		show_error("cauchy","org_API_RAID6","No memory");
		return FALSE;
	}
	regionptr=stripptr->regionptr;
	codeparamptr=regionptr->codepara;

	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	w=codeparamptr->w;

	rows=codenum*w;
	cols=datanum*w;
	mat=talloc(UINT32,rows*cols);
	if(mat==NULL)
	{
		show_error("cauchy_org","API_RAID6","No memory");
		return FALSE;
	}
	matrix->matrix=mat;
	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w;
	resTF=cauchy_orgininal_coding_bitmatrix(matrix);
	if(resTF==FALSE)
	{
		show_error("cauchy_org","API_RAID6","bitmatrix can't create");
		return FALSE;
	}
	resTF=UPDATE_API_bitmatrix_update(chunkpositionblockgroupptr,stripptr,parityblockgroupptr,matrix);
	if(resTF==FALSE)
	{
		show_error("cauchy_org","update_API","update can't execute");
		return FALSE;
	}
	free(matrix);
	free(mat);
	return TRUE;
}

//经典RS解码接口
int cauchy_org_decoder_API_strip(STRIP *stripptr,ERRORPATTERN *errormatrix)
{
	BITMATRIX *matrix;

	REGION *regionptr;
	CODEPARA *codeparamptr;
	STRIPSECT *strsetptr,*curstrsetptr;
	UINT32 *mat;
	int w,datanum,codenum,rows,cols,resTF;

	return TRUE;
}
//经典RS解码接口
int cauchy_org_decoder_API_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix)
{
	BITMATRIX *matrix;

	REGION *regionptr;
	CODEPARA *codeparamptr;
	STRIPSECT *strsetptr,*curstrsetptr;
	UINT32 *mat;
	int w,datanum,codenum,rows,cols,resTF;

	return TRUE;
}