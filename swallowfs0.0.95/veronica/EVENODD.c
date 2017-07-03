#include "EVENODD.h"
int EVENODD_add_grandmother(BITMATRIX *matrix)
{
	UINT32 *mat;
	int isprime;
	int rows,cols,w;
	int i,j,index,x,k;
	int tarx,tary,tarindex;
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	x=caldevice(rows,w);
	k=caldevice(cols,w);

	if(x!=2)
	{
		show_error("EVENODD","create_encode_matrix","RAID-6 two parity device");
		return FALSE;
	}

	isprime=profile_is_prime(w+1);
	if(isprime==FALSE)
	{
		show_error("EVENODD","create_encode_matrix","EVENODD code w+1 should be prime");
		return FALSE;
	}

	if(w!=k-1)
	{
		show_error("EVENODD","create_encode_matrix","EVENODD code w!=k-1");
		return FALSE;
	}
	//在原有矩阵基础上计算
	for(i=0;i<w;i++)
	{
		//调整到当前位置
		index=cols*w+i*cols;
		for(j=0;j<(w+1);j++)
		{
			tarx=k-1-j;
			tary=j;
			if(tarx==w)//这个位置无需计算
			{
				continue;
			}
			tarindex=index+tarx+tary*w;
			mat[tarindex]=mat[tarindex]^1;
		}
	}
	return TRUE;
}


int EVENODD_create_encode_matrix(BITMATRIX *matrix)
{
	UINT32 *mat;
	int rows,cols,w,resTF;
	int i,j,index,x,k;
	int isprime;
	int tarx,tary,tarindex;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;
	

	x=caldevice(rows,w);
	k=caldevice(cols,w);

	if(x!=2)
	{
		show_error("EVENODD","create_encode_matrix","RAID-6 two parity devices");
		return FALSE;
	}
	if(w!=(k-1))
	{
		show_error("EVENODD","create_encode_matrix","EVENODD code w!=k-1");
		return FALSE;
	}
	isprime=profile_is_prime(w+1);
	if(isprime==FALSE)
	{
		show_error("EVENODD","create_encode_matrix","EVENODD code w+1 should be prime");
		return FALSE;
	}
	if(mat==NULL)
	{
		mat=talloc(UINT32,rows*cols);//开空间
		if(mat==NULL)
		{
			show_error("EVENODD","create_encode_matrix","No memory");
			return FALSE;
		}
		matrix->matrix=mat;
	}
	bzero(mat,UINT32,rows*cols);//将内存空间清0
	matrix->matrix=mat;//调整指针
	//计算p盘
	for(i=0;i<w;i++)
	{
		index=i*cols+i;
		for(j=0;j<k;j++)
		{
			mat[index]=1;
			index+=w;
		}
	}    
	//matrix_print_bitmatrix(matrix);
	//计算Q盘
	
	for(i=0;i<w;i++)//这里一行一行根据定义算
	{
		//一个一个处理
		index=cols*w+i*cols;
		//先计算
		for(j=0;j<(w+1);j++)
		{
			tarx=profile_mod_number(i-j,w+1);
			tary=j;//第几个设备
			if(tarx==w)//这个位置无需计算
			{
				continue;
			}
			tarindex=index+tarx+tary*w;
			mat[tarindex]=1;	
		}
	}
	//matrix_print_bitmatrix(matrix);
	//计算祖母块每一次计算都要计算grademother
	resTF=EVENODD_add_grandmother(matrix);
	if(resTF==FALSE)
	{
		show_error("EVENODD","create_encode_matrix","grandmother can't add to the matrix");
		return FALSE;
	}
	return TRUE;
}

int EVENODD_API(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr)
{
	UINT32 *mat;
	BITMATRIX *matrix;

	CODEPARA *codeparamptr;
	REGION *regionptr;
	int datanum,codenum;
	int rows,cols,w,resTF;
	matrix=talloc(BITMATRIX,1);
	if(matrix==NULL)
	{
		show_error("EVENODD","API","No memory");
		return FALSE;
	}
	regionptr=pparityptr->regionptr;
	codeparamptr=regionptr->codepara;

	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	w=codeparamptr->w;

	rows=codenum*w;
	if(w!=(datanum-1))
	{
		datanum=w+1;//重新定位
	}
	cols=datanum*w;

	mat=talloc(UINT32,rows*cols);
	if(mat==NULL)
	{
		show_error("EVENODD","API","No memory");
		return FALSE;
	}

	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w=w;
	matrix->matrix=mat;

	resTF=EVENODD_create_encode_matrix(matrix);
	if(resTF==FALSE)
	{
		show_error("EVENODD","API","matrix can't create");
		return FALSE;
	}

	resTF=matrix_bitmatrix_encode_stripsect_RAID6(strsetblockgroupptr,pparityptr,qparityptr,matrix);
	if(resTF==FALSE)
	{
		show_error("EVENODD","API","EVENODD RAID6 can't calculate");
		return FALSE;
	}
	resTF=matrix_destroy(matrix);
	if(resTF==FALSE)
	{
		show_error("EVENODD","API","matrix can't free");
		return FALSE;
	}
	free(matrix);
	return TRUE;
}
int EVENODD_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix)
{
	return TRUE;
}

int EVENODD_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr)
{
	UINT32 *mat;
	BITMATRIX *matrix;

	STRIPSECTGROUP *strsetgroupptr;
	STRIPSECT *strsetptr,*curstrsetptr;

	STRIPSECT *pparityptr,*qparityptr;

	STRIPSECTBLOCKGROUP *strsetblockgroupptr;
	STRIPSECTBLOCK *strsetblockptr,*curstrsetblockptr;
	int strsetnum;

	CODEPARA *codeparamptr;
	REGION *regionptr;
	int datanum,codenum,isparity;
	int i,rows,cols,w,resTF;
	matrix=talloc(BITMATRIX,1);
	if(matrix==NULL)
	{
		show_error("EVENODD","API","No memory");
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
		show_error("EVENODD","API","No memory");
		return FALSE;
	}

	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w=w;
	matrix->matrix=mat;

	strsetnum=datanum;
	strsetblockptr=talloc(STRIPSECTBLOCK,strsetnum);
	if(strsetblockptr==NULL)
	{ 
		show_error("EVENODD","API","No memory");
		return FALSE;
	}
	strsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(strsetblockgroupptr==NULL)
	{
		show_error("EVENODD","API","No memory");
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

	resTF=EVENODD_create_encode_matrix(matrix);
	if(resTF==FALSE)
	{
		show_error("EVENODD","API","matrix can't create");
		return FALSE;
	}

	resTF=UPDATE_API_bitmatrix_update_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,pparityptr,qparityptr,parityblockgroupptr,matrix);
	if(resTF==FALSE)
	{
		show_error("EVENODD","API","update can't execute");
		return FALSE;
	}
	free(matrix);
	free(mat);
	free(strsetblockptr);
	free(strsetblockgroupptr);
	return TRUE;
}