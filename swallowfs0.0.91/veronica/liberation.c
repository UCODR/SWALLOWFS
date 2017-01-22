#include "liberation.h"
//其中y代表k*w设备数量，w代表块长度
int liberation_create_encode_matrix(BITMATRIX *matrix)
{
	UINT32 *mat;
	int isprime;
	int i,j,x,k,index;
	int rows,cols,w;
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	x=caldevice(rows,w);
	k=caldevice(cols,w);

	if(x!=2)
	{
		show_error("liberation","create_encode_matrix","RAID-6 two parity device");
		return FALSE;
	}
	isprime=profile_is_prime(w);
	if(isprime==FALSE)
	{
		show_error("liberation","create_encode_matrix","RDP code w+1 should be prime");
		return FALSE;
	}
	if(k>w)
	{
		show_error("liberation","create_encode_matrix","liberation code k<w");
		return FALSE;
	}
	if(mat==NULL)
	{
		mat=talloc(UINT32,rows*cols);//开空间
		if(mat==NULL)
		{
			show_error("liberation","create_encode_matrix","No memory");
			return FALSE;
		}
	}
	
	bzero(mat,UINT32,rows*cols);//将内存空间清0
	
	//建立liberation
	//建立P盘
	for(i=0;i<w;i++)
	{
		index=i*cols+i;
		for(j=0;j<k;j++)
		{
			mat[index]=1;
			index+=w;
		}
	}

	//建立Q盘
	for(i=0;i<k;i++)//处理明码块
	{
		index=cols*w+i*w;//处理其中的一个放个
		for(j=0;j<w;j++)
		{
			mat[index+(i+j)%w]=1;
			index+=(cols);//处理下一行
		}
		index=cols*w+i*w;//处理其中的一个放个当前数据已脏重算
		if(i>0)//当前不是第一个加上O矩阵
		{
			j=(i*((w-1)/2))%w;
			mat[index+j*cols+(i+j-1)%w]=1;
		}
	}
	matrix->matrix=mat;//调整指针
	return TRUE;
}
//其中y代表k*w设备数量
int liberation_liber8tion_create_encode_matrix(BITMATRIX *matrix)
{
	UINT32 *mat;
	int i,j,x,k,index;
	int rows,cols,w;
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	x=caldevice(cols,w);
	k=caldevice(cols,w);
	
	if(w!=8)
	{
		show_error("liberation","liber8tion_create_encode_matrix","w!=8");
		return FALSE;
	}
	if(k>w)
	{
		show_error("liberation","liber8tion_create_encode_matrix","liberation code k<w");
		return FALSE;
	}
	if(mat!=NULL)
	{
		free(mat);
	}
	mat=talloc(UINT32,rows*cols);//开空间
	if(mat==NULL)
	{
		show_error("liberation","create_encode_matrix","No memory");
		return FALSE;
	}
	bzero(mat,UINT32,rows*cols);//将内存空间清0
	matrix->matrix=mat;//调整指针
	//可以开始对于数据进行编码了
	//建立liberation
	//建立P盘
	for(i=0;i<w;i++)
	{
		index=i*cols+i;
		for(j=0;j<k;j++)
		{
			mat[index]=1;
			index+=w;
		}
	}
	//q盘进行填写计算
	index = cols*w;//定位开始位置
	if(k==0) return TRUE;//一个没有不需要做

	mat[index+0*k*w+0*w+0] = 1;
	mat[index+1*k*w+0*w+1] = 1;
	mat[index+2*k*w+0*w+2] = 1;
	mat[index+3*k*w+0*w+3] = 1;
	mat[index+4*k*w+0*w+4] = 1;
	mat[index+5*k*w+0*w+5] = 1;
	mat[index+6*k*w+0*w+6] = 1;
	mat[index+7*k*w+0*w+7] = 1;

	if(k==1) return TRUE;

	mat[index+0*k*w+1*w+7] = 1;
	mat[index+1*k*w+1*w+3] = 1;
	mat[index+2*k*w+1*w+0] = 1;
	mat[index+3*k*w+1*w+2] = 1;
	mat[index+4*k*w+1*w+6] = 1;
	mat[index+5*k*w+1*w+1] = 1;
	mat[index+6*k*w+1*w+5] = 1;
	mat[index+7*k*w+1*w+4] = 1;
	mat[index+4*k*w+1*w+7] = 1;

	if(k==2) return TRUE;

	mat[index+0*k*w+2*w+6] = 1;
	mat[index+1*k*w+2*w+2] = 1;
	mat[index+2*k*w+2*w+4] = 1;
	mat[index+3*k*w+2*w+0] = 1;
	mat[index+4*k*w+2*w+7] = 1;
	mat[index+5*k*w+2*w+3] = 1;
	mat[index+6*k*w+2*w+1] = 1;
	mat[index+7*k*w+2*w+5] = 1;
	mat[index+1*k*w+2*w+3] = 1;

	if(k==3) return TRUE;

	mat[index+0*k*w+3*w+2] = 1;
	mat[index+1*k*w+3*w+5] = 1;
	mat[index+2*k*w+3*w+7] = 1;
	mat[index+3*k*w+3*w+6] = 1;
	mat[index+4*k*w+3*w+0] = 1;
	mat[index+5*k*w+3*w+3] = 1;
	mat[index+6*k*w+3*w+4] = 1;
	mat[index+7*k*w+3*w+1] = 1;
	mat[index+5*k*w+3*w+4] = 1;

	if(k==4) return TRUE;

	mat[index+0*k*w+4*w+5] = 1;
	mat[index+1*k*w+4*w+6] = 1;
	mat[index+2*k*w+4*w+1] = 1;
	mat[index+3*k*w+4*w+7] = 1;
	mat[index+4*k*w+4*w+2] = 1;
	mat[index+5*k*w+4*w+4] = 1;
	mat[index+6*k*w+4*w+3] = 1;
	mat[index+7*k*w+4*w+0] = 1;
	mat[index+2*k*w+4*w+0] = 1;

	if(k==5) return TRUE;

	mat[index+0*k*w+5*w+1] = 1;
	mat[index+1*k*w+5*w+2] = 1;
	mat[index+2*k*w+5*w+3] = 1;
	mat[index+3*k*w+5*w+4] = 1;
	mat[index+4*k*w+5*w+5] = 1;
	mat[index+5*k*w+5*w+6] = 1;
	mat[index+6*k*w+5*w+7] = 1;
	mat[index+7*k*w+5*w+0] = 1;
	mat[index+7*k*w+5*w+2] = 1;

	if(k==6) return TRUE;

	mat[index+0*k*w+6*w+3] = 1;
	mat[index+1*k*w+6*w+0] = 1;
	mat[index+2*k*w+6*w+6] = 1;
	mat[index+3*k*w+6*w+5] = 1;
	mat[index+4*k*w+6*w+1] = 1;
	mat[index+5*k*w+6*w+7] = 1;
	mat[index+6*k*w+6*w+4] = 1;
	mat[index+7*k*w+6*w+2] = 1;
	mat[index+6*k*w+6*w+5] = 1;

	if(k==7) return TRUE;

	mat[index+0*k*w+7*w+4] = 1;
	mat[index+1*k*w+7*w+7] = 1;
	mat[index+2*k*w+7*w+1] = 1;
	mat[index+3*k*w+7*w+5] = 1;
	mat[index+4*k*w+7*w+3] = 1;
	mat[index+5*k*w+7*w+2] = 1;
	mat[index+6*k*w+7*w+0] = 1;
	mat[index+7*k*w+7*w+6] = 1;
	mat[index+3*k*w+7*w+1] = 1;

	return TRUE;

}
int liberation_blaum_roth_create_encode_matrix(BITMATRIX *matrix)
{
	UINT32 *mat;
	int isprime;
	int rows,cols,w;
	int i,j,index,x,k,l,m,p;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	x=caldevice(rows,w);
	k=caldevice(cols,w);

	if(x!=2)
	{
		show_error("liberation","blaum_roth_create_encode_matrix","RAID-6 two parity device");
		return FALSE;
	}
	isprime=profile_is_prime(w+1);
	if(isprime==FALSE)
	{
		show_error("liberation","blaum_roth_create_encode_matrix","blaum_roth code w+1 should be prime");
		return FALSE;
	}
	if(k>w)
	{
		show_error("liberation","blaum_roth_create_encode_matrix","liberation code k<w");
		return FALSE;
	}
	if(mat==NULL)
	{
		mat=talloc(UINT32,rows*cols);//开空间
		if(mat==NULL)
		{
			show_error("liberation","blaum_roth_create_encode_matrix","No memory");
			return FALSE;
		}
		matrix->matrix=mat;
	}
	
	bzero(mat,UINT32,rows*cols);//将内存空间清0
	matrix->matrix=mat;//调整指针
	//计算P盘
	for(i=0;i<w;i++)
	{
		index=i*cols+i;
		for(j=0;j<k;j++)
		{
			mat[index]=1;
			index+=w;
		}
	}                                                                                                                                                                                                                                      
	//计算Q盘
	p=w+1;
	for(j=0;j<k;j++)//懒得改plank老师的定义了
	{
		index=cols*w+j*w;
		if(j==0)//如果是第一行
		{
			for(l=0;l<w;l++)
			{
				mat[index+l]=1;
				index+=k*w;
			}
		

		}
		else
		{
			i=j;
			for(l=1;l<w;l++)
			{
				if(l!=(p-i))
				{
					m=l+i;
					if(m>=p)
					{
						m-=p;
					}
					m--;
					mat[index+m]=1;
				}
				else
				{
					mat[index+i-1]=1;
					if(i%2==0)
					{
						m=i/2;
					}
					else
					{
						m=(p/2)+1+(i/2);
					}
					m--;
					mat[index+m]=1;
				}
				index+=k*w;
			}
		}
	}
	return TRUE;
}
int LIBERATION_API(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr)
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
		show_error("Liberation","API","No memory");
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
		show_error("Liberation","API","No memory");
		return FALSE;
	}

	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w=w;
	matrix->matrix=mat;

	resTF=liberation_create_encode_matrix(matrix);
	if(resTF==FALSE)
	{
		show_error("Liberation","API","matrix can't create");
		return FALSE;
	}

	resTF=matrix_bitmatrix_encode_stripsect_RAID6(strsetblockgroupptr,pparityptr,qparityptr,matrix);
	if(resTF==FALSE)
	{
		show_error("Liberation","API","liberation RAID6 can't calculate");
		return FALSE;
	}
	return TRUE;
}
int LIBERATION_blaum_roth_API(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr)
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
		show_error("Liberation","API","No memory");
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
		show_error("Liberation","blaum_roth_API","No memory");
		return FALSE;
	}

	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w=w;
	matrix->matrix=mat;

	resTF=liberation_blaum_roth_create_encode_matrix(matrix);
	if(resTF==FALSE)
	{
		show_error("Liberation","blaum_roth_API","matrix can't create");
		return FALSE;
	}

	resTF=matrix_bitmatrix_encode_stripsect_RAID6(strsetblockgroupptr,pparityptr,qparityptr,matrix);
	if(resTF==FALSE)
	{
		show_error("Liberation","blaum_roth_API","EVENODD RAID6 can't calculate");
		return FALSE;
	}
	return TRUE;
}
int LIBERATION_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix)
{
	return TRUE;
}
int LIBERATION_blaum_roth_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix)
{
	return TRUE;
}

int LIBERATION_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr)
{
	UINT32 *mat;
	BITMATRIX *matrix;

	STRIPSECTGROUP *strsetgroupptr;
	STRIPSECT *strsetptr,*curstrsetptr;

	STRIPSECT *pparityptr,*qparityptr;

	STRIPSECTBLOCKGROUP *strsetblockgroupptr;
	STRIPSECTBLOCK *strsetblockptr;
	int strsetnum;

	CODEPARA *codeparamptr;
	REGION *regionptr;
	int datanum,codenum,isparity;
	int i,rows,cols,w,resTF;
	matrix=talloc(BITMATRIX,1);
	if(matrix==NULL)
	{
		show_error("LIBERATION","API","No memory");
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
		show_error("LIBERATION","API","No memory");
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
		show_error("LIBERATION","API","No memory");
		return FALSE;
	}

	strsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(strsetblockgroupptr==NULL)
	{
		show_error("RDP","API","No memory");
		return FALSE;
	}
	strsetblockgroupptr->stripsectblockptr=strsetblockptr;
	strsetblockgroupptr->groupsize=strsetnum;

	strsetgroupptr=stripptr->stripsectlist;

	strsetptr=strsetgroupptr->stripsectgroup;
	strsetnum=strsetgroupptr->groupsize;

	curstrsetptr=strsetptr;
	for(i=0;i<strsetnum;i++)
	{
		isparity=curstrsetptr->isparity;
		if(isparity==FALSE)
		{
			strsetblockptr->stripsectptr=curstrsetptr;
			strsetblockptr->stripsectid=curstrsetptr->StripsectID;
			strsetblockptr++;
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

	resTF=liberation_create_encode_matrix(matrix);
	if(resTF==FALSE)
	{
		show_error("LIBERATION","API","matrix can't create");
		return FALSE;
	}

	resTF=matrix_bitmatrix_update_stripsect_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,pparityptr,qparityptr,parityblockgroupptr,matrix);
	if(resTF==FALSE)
	{
		show_error("LIBERATION","API","data can't update");
		return FALSE;
	}
	return TRUE;
}
int LIBERATION_blaum_roth_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr)
{
	UINT32 *mat;
	BITMATRIX *matrix;

	STRIPSECTGROUP *strsetgroupptr;
	STRIPSECT *strsetptr,*curstrsetptr;

	STRIPSECT *pparityptr,*qparityptr;

	STRIPSECTBLOCKGROUP *strsetblockgroupptr;
	STRIPSECTBLOCK *strsetblockptr;
	int strsetnum;

	CODEPARA *codeparamptr;
	REGION *regionptr;
	int datanum,codenum,isparity;
	int i,rows,cols,w,resTF;
	matrix=talloc(BITMATRIX,1);
	if(matrix==NULL)
	{
		show_error("LIBERATION","API","No memory");
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
		show_error("LIBERATION","API","No memory");
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
		show_error("LIBERATION","API","No memory");
		return FALSE;
	}

	strsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(strsetblockgroupptr==NULL)
	{
		show_error("RDP","API","No memory");
		return FALSE;
	}
	strsetblockgroupptr->stripsectblockptr=strsetblockptr;
	strsetblockgroupptr->groupsize=strsetnum;

	strsetgroupptr=stripptr->stripsectlist;

	strsetptr=strsetgroupptr->stripsectgroup;
	strsetnum=strsetgroupptr->groupsize;

	curstrsetptr=strsetptr;
	for(i=0;i<strsetnum;i++)
	{
		isparity=curstrsetptr->isparity;
		if(isparity==FALSE)
		{
			strsetblockptr->stripsectptr=curstrsetptr;
			strsetblockptr->stripsectid=curstrsetptr->StripsectID;
			strsetblockptr++;
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

	resTF=liberation_blaum_roth_create_encode_matrix(matrix);
	if(resTF==FALSE)
	{
		show_error("LIBERATION","API","matrix can't create");
		return FALSE;
	}

	resTF=matrix_bitmatrix_update_stripsect_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,pparityptr,qparityptr,parityblockgroupptr,matrix);
	if(resTF==FALSE)
	{
		show_error("LIBERATION","API","data can't update");
		return FALSE;
	}
	return TRUE;
}