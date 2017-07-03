#include "MDR.h"

int MDRI_create_encode_matrix_B(BITMATRIX *matrix)//k代表数据盘+p盘
{
	//计算B矩阵
	UINT32 *mat;
	UINT32 *tempmat1,*tempmat2;
	int rows,cols,w,tempwsize,ltempwsize,tempsize;
	int i,j,u,v,isouindex,ksouindex,x,k;
	

	int ltempcols,ltemprows,ntempcols,ntemprows;

	int index,lindex,windex,lwindex;
	int tarindex;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	x=caldevice(rows,w);
	k=caldevice(cols,w);

	if(x!=1)
	{
		show_error("MDRI","create_encode_matrix","RAID-6 two parity device");
		return FALSE;
	}
	if(w!=(int)pow((float)2,(k-1)))
	{
		show_error("MDRI","create_encode_matrix","RDP code w!=k");
		return FALSE;
	}
	if(mat==NULL)
	{
		mat=talloc(UINT32,rows*cols);//开空间
		if(mat==NULL)
		{
			show_error("MDRI","create_encode_matrix","No memory");
			return FALSE;
		}
	}
	tempmat1=talloc(UINT32,8);//将第一个空间开8个
	if(tempmat1==NULL)
	{
		show_error("MDR","create_encode_matrix","No memory");
		return FALSE;
	}
	for(i=0;i<2;i++)//将两个矩阵合并
	{
		tempmat1[i]=MDRIB1matrix[i];
		tempmat1[i+2]=MDRIB2matrix[i];
		tempmat1[i+4]=MDRIB1matrix[i+2];
		tempmat1[i+6]=MDRIB2matrix[i+2];
	}
	if(k==2)
	{
		//直接返回无需计算
		//free(mat);//释放空间
		mcpy(mat,tempmat1,UINT32,rows*cols);
		free(tempmat1);
		return TRUE;
	}
	ltempwsize=2;
	ltempcols=4;
	ltemprows=2;

	ntempcols=12;
	ntemprows=4;
	tempwsize=4;//每一个当前的w大小

	for(i=3;i<(k+1);i++)//因为k大所以可以从3开始，先计算k-1个非目标矩阵
	{
		//计算需要的内存量当前
		tempsize=i*tempwsize*tempwsize;
		tempmat2=talloc(UINT32,tempsize);
		if(tempmat2==NULL)
		{
			show_error("MDR","create_encode_matrix","No memory");
			return FALSE;
		}
		bzero(tempmat2,UINT32,tempsize);
		//开始计算
		for(j=0;j<tempwsize;j++)
		{
			index=j*ntempcols;//定位
			for(u=0;u<i;u++)//当前第几个矩阵
			{
				windex=u*tempwsize;//当前索引
				//定位到矩阵算法
				if(u<(i-2))
				{
					for(v=0;v<tempwsize;v++)//拷贝一行并且相加
					{
						if(j<(tempwsize/2))//如果是下半部分
						{
							if(v<(tempwsize/2))
							{
								//j*cols/2;
								tarindex=index+windex+v;//计算位置

								lindex=j*ltempcols;
								lwindex=u*ltempwsize;
								isouindex=lindex+lwindex+v;//计算坐标

								lindex=j*ltempcols;
								lwindex=(i-2)*ltempwsize;//
								ksouindex=lindex+lwindex+v;

								tempmat2[tarindex]=tempmat1[isouindex]+tempmat1[ksouindex];
								
								//tempmat2[tarindex]=
							}
						}
						else
						{
							if(v>=(tempwsize/2))//如果在第三象限
							{
								tarindex=index+windex+v;//计算位置

								lindex=(j-tempwsize/2)*ltempcols;
								lwindex=u*ltempwsize;
								isouindex=lindex+lwindex+(v-tempwsize/2);

								lindex=(j-tempwsize/2)*ltempcols;
								lwindex=(i-2)*ltempwsize;
								ksouindex=lindex+lwindex+(v-tempwsize/2);

								tempmat2[tarindex]=tempmat1[isouindex]+tempmat1[ksouindex];
							}
						}
					}
					
				}
				if(u==(i-2))
				{
					for(v=0;v<tempwsize;v++)//拷贝一行并且相加
					{
						//第二象限
						if(j<(tempwsize/2))
						{
							if(v>=(tempwsize/2))
							{
								if(j==(v-tempwsize/2))//判断数据
								{
									tarindex=index+windex+v;
									tempmat2[tarindex]=1;
								}
							}
						}
					}
				}
				if(u==(i-1))
				{
					for(v=0;v<tempwsize;v++)
					{
						//第四象限
						if(j>=(tempwsize/2))
						{
							if(v<(tempwsize/2))
							{
								if((j-tempwsize/2)==v)
								{
									tarindex=index+windex+v;
									tempmat2[tarindex]=1;
								}
							}
						}
					}
				}
			}
			
		}
		
		free(tempmat1);//前面一个不要了
		tempmat1=tempmat2;
		ltempwsize=tempwsize;
		ltempcols=ntempcols;
		ltemprows=ntemprows;
		//重新计算当前数据
		tempwsize=tempwsize*2;
		ntemprows=tempwsize;
		ntempcols=tempwsize*(i+1);
	}
	//计算最后的数据
	mcpy(mat,tempmat1,UINT32,rows*cols);
	free(tempmat1);

	return TRUE;
}
int MDRII_create_encode_matrix_B(BITMATRIX *matrix)
{
	//计算B矩阵
	UINT32 *mat;
	UINT32 *tempmat1,*tempmat2;
	int rows,cols,w,tempwsize,ltempwsize,tempsize;
	int i,j,u,v,tarindex,isouindex,ksouindex,x,k;

	int ltempcols,ltemprows,ntempcols,ntemprows;

	int index,windex,lwindex,lindex;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	x=caldevice(rows,w);
	k=caldevice(cols,w);

	if(x!=1)
	{
		show_error("MDRI","create_encode_matrix","RAID-6 two parity device");
		return FALSE;
	}
	if(w!=(int)pow((float)2,(k-2)))
	{
		show_error("RDP","create_encode_matrix","RDP code w!=k");
		return FALSE;
	}
	if(mat==NULL)
	{
		mat=talloc(UINT32,rows*cols);//开空间
		if(mat==NULL)
		{
			show_error("MDR","create_encode_matrix","No memory");
			return FALSE;
		}
	}
	tempmat1=talloc(UINT32,4*16);//将第一个空间开8个
	if(tempmat1==NULL)
	{
		show_error("MDR","create_encode_matrix","No memory");
		return FALSE;
	}
	for(i=0;i<4;i++)//将两个矩阵合并
	{
		
		for(u=0;u<4;u++)//拷贝一行
		{
			ksouindex=i*16;
			tarindex=ksouindex+u;
			isouindex=i*4;
			ksouindex=isouindex+u;
			tempmat1[tarindex]=MDRIIB1matrix[ksouindex];
			tempmat1[tarindex+4]=MDRIIB2matrix[ksouindex];
			tempmat1[tarindex+8]=MDRIIB3matrix[ksouindex];
			tempmat1[tarindex+12]=MDRIIB4matrix[ksouindex];
		}
	}
	if(k==4)
	{
		//直接返回无需计算
		//free(mat);//释放空间
		//matrix->matrix=tempmat1;
		mcpy(mat,tempmat1,UINT32,rows*cols);
		free(tempmat1);
		return TRUE; 
	}
	ltempwsize=4;
	ltempcols=16;
	ltemprows=4;

	tempwsize=8;
	ntempcols=40;
	ntemprows=8;
	for(i=5;i<(k+1);i++)
	{
		tempsize=i*tempwsize*tempwsize;
		tempmat2=talloc(UINT32,tempsize);
		if(tempmat2==NULL)
		{
			show_error("MDRII","create_encode_matrix_B","No memory");
			return FALSE;
		}
		bzero(tempmat2,UINT32,tempsize);

		for(j=0;j<tempwsize;j++)//按行计算
		{
			index=j*ntempcols;//定位
			for(u=0;u<i;u++)//第几个矩阵
			{
				windex=u*tempwsize;
				if(u<(i-2))
				{
					for(v=0;v<tempwsize;v++)
					{
						if(j<(tempwsize/2))
						{
							if(v<(tempwsize/2))
							{
								tarindex=index+windex+v;

								lindex=j*ltempcols;
								lwindex=u*ltempwsize;
								isouindex=lindex+lwindex+v;//计算坐标

								tempmat2[tarindex]=tempmat1[isouindex];
							}
						}
						else
						{
							if(v>=(tempwsize/2))
							{
								tarindex=index+windex+v;

								lindex=(j-tempwsize/2)*ltempcols;
								lwindex=u*ltempwsize;
								isouindex=lindex+lwindex+(v-tempwsize/2);//计算坐标

								tempmat2[tarindex]=tempmat1[isouindex];
							}
						}
					}
				}
				if(u==(i-2))
				{
					for(v=0;v<tempwsize;v++)
					{
						if(j<(tempwsize/2))
						{
							if(v<(tempwsize/2))//第一象限
							{
								tarindex=index+windex+v;

								lindex=j*ltempcols;
								lwindex=u*ltempwsize;
								isouindex=lindex+lwindex+v;//计算坐标

								tempmat2[tarindex]=tempmat1[isouindex];
							}
							else//第二象限
							{
								if(j==(v-tempwsize/2))
								{
									tarindex=index+windex+v;
									tempmat2[tarindex]=1;
								}
							}
						}
						else
						{
							if(v>=(tempwsize/2))//第四象限
							{
								tarindex=index+windex+v;

								lindex=(j-tempwsize/2)*ltempcols;
								lwindex=u*ltempwsize;
								isouindex=lindex+lwindex+(v-tempwsize/2);

								tempmat2[tarindex]=tempmat1[isouindex];
							}
						}
					}
				}
				if(u==(i-1))
				{
					for(v=0;v<tempwsize;v++)
					{
						if(j>=(tempwsize/2))
						{
							if(v<(tempwsize/2))
							{
								if((j-tempwsize/2)==v)
								{
									tarindex=index+windex+v;
									tempmat2[tarindex]=1;
								}
							}
						}
					}
				}
			}
		}
		free(tempmat1);//前面一个不要了
		tempmat1=tempmat2;
		ltempwsize=tempwsize;
		ltempcols=ntempcols;
		ltemprows=ntemprows;

		tempwsize=tempwsize*2;
		ntemprows=tempwsize;
		ntempcols=tempwsize*(i+1);
	}
	//计算最后的数据
	mcpy(mat,tempmat1,UINT32,rows*cols);
	free(tempmat1);

	return TRUE;
}

//其中w代表w条带宽度，k为数据盘
int MDRI_create_encode_matrix(BITMATRIX *matrix)
{
	BITMATRIX *matrixB;//计算
	UINT32 *mat,*matB;
	int i,j,u,rows,cols,w,k,x,resTF;
	int rowsB,colsB;
	int index,windex,sindex1,souwindex1,sindex2,souwindex2,tarindex,souindex1,souindex2;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	x=caldevice(rows,w);
	k=caldevice(cols,w);

	if(x!=2)
	{
		show_error("MDRI","create_encode_matrix","RAID6 should have two parity disk");
		return FALSE;
	}
	if(w!=(int)pow((float)2,k))
	{
		show_error("MDRI","create_encode_matrix","the w should be 2^k");
		return FALSE;
	}
	if(mat==NULL)
	{
		mat=talloc(UINT32,rows*cols);
		if(mat==NULL)
		{
			show_error("MDRI","create_encode_matrix","No memory");
			return FALSE;
		}
		matrix->matrix=mat;
	}
	bzero(mat,UINT32,rows*cols);
	matrixB=talloc(BITMATRIX,1);
	if(matrixB==NULL)
	{
		show_error("MDRI","create_encode_matrix","No memory");
		return FALSE;
	}
	rowsB=1*w;
	colsB=(k+1)*w;

	matrixB->xm=rowsB;
	matrixB->ym=colsB;
	matrixB->w=w;

	matB=talloc(UINT32,rowsB*colsB);//建立数据库
	if(matB==NULL)
	{
		show_error("MDRI","create_encode_matrix","No memory");
		return FALSE;
	}
	matrixB->matrix=matB;

	resTF=MDRI_create_encode_matrix_B(matrixB);
	if(resTF==FALSE)
	{
		show_error("MDRI","create_encode_matrix_B","matrix B can't create");
		return FALSE;
	}
	matB=matrixB->matrix;
	//建立矩阵A
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
	//计算q盘
	for(i=0;i<rows;i++)
	{
		index=w*cols+i*cols;//计算数据
		sindex1=i*colsB;
		sindex2=i*colsB;
		for(j=0;j<k;j++)
		{
			windex=j*w;
			souwindex1=j*w;
			souwindex2=w*k;
			for(u=0;u<w;u++)
			{
				tarindex=index+windex+u;
				souindex1=sindex1+souwindex1+u;
				souindex2=sindex2+souwindex2+u;
				mat[tarindex]=matB[souindex1]+matB[souindex2];
			}
		}
	}

	return TRUE;
}
//其中w代表w条带宽度，k为数据盘
int MDRII_create_encode_matrix(BITMATRIX *matrix)
{
	BITMATRIX *matrixB;//计算
	UINT32 *mat,*matB;
	int i,j,u,rows,cols,w,k,x,resTF;
	int rowsB,colsB;
	int index,windex,sindex1,souwindex1,sindex2,souwindex2,tarindex,souindex1,souindex2;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	x=caldevice(rows,w);
	k=caldevice(cols,w);
	if(x!=2)
	{
		show_error("MDRI","create_encode_matrix","RAID6 should have two parity disk");
		return FALSE;
	}
	if(w!=(int)pow((float)2,(k-1)))
	{
		show_error("MDRI","create_encode_matrix","the w should be 2^k");
		return FALSE;
	}
	if(mat==NULL)
	{
		mat=talloc(UINT32,rows*cols);
		if(mat==NULL)
		{
			show_error("MDRI","create_encode_matrix","No memory");
			return FALSE;
		}
		matrix->matrix=mat;
	}
	bzero(mat,UINT32,rows*cols);

	matrixB=talloc(BITMATRIX,1);
	if(matrixB==NULL)
	{
		show_error("MDRI","create_encode_matrix","No memory");
		return FALSE;
	}
	rowsB=1*w;
	colsB=(k+1)*w;

	matrixB->xm=rowsB;
	matrixB->ym=colsB;
	matrixB->w=w;

	matB=talloc(UINT32,rowsB*colsB);//建立数据库
	if(matB==NULL)
	{
		show_error("MDRI","create_encode_matrix","No memory");
		return FALSE;
	}
	matrixB->matrix=matB;

	resTF=MDRII_create_encode_matrix_B(matrixB);
	if(resTF==FALSE)
	{
		show_error("MDRI","create_encode_matrix_B","matrix B can't create");
		return FALSE;
	}
	matB=matrixB->matrix;
	//建立矩阵A
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
	//计算q盘
	for(i=0;i<rows;i++)
	{
		index=w*cols+i*cols;//计算数据
		sindex1=i*colsB;
		sindex2=i*colsB;
		for(j=0;j<k;j++)
		{
			windex=j*w;
			souwindex1=j*w;
			souwindex2=w*k;
			for(u=0;u<w;u++)
			{
				tarindex=index+windex+u;
				souindex1=sindex1+souwindex1+u;
				souindex2=sindex2+souwindex2+u;
				mat[tarindex]=matB[souindex1]+matB[souindex2];
			}
		}
	}
	return TRUE;
}


int MDRI_API(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr)
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
		show_error("MDR","API","No memory");
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
		show_error("MDR","API","No memory");
		return FALSE;
	}

	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w=w;
	matrix->matrix=mat;

	resTF=MDRI_create_encode_matrix(matrix);
	if(resTF==FALSE)
	{
		show_error("MDRI","API","bit matrix can't create");
		return FALSE;
	}

	resTF=matrix_bitmatrix_encode_stripsect_RAID6(strsetblockgroupptr,pparityptr,qparityptr,matrix);
	if(resTF==FALSE)
	{
		show_error("MDRI","API","EVENODD RAID6 can't calculate");
		return FALSE;
	}
	resTF=matrix_destroy(matrix);
	if(resTF==FALSE)
	{
		show_error("MDRI","API","matrix can't free");
		return FALSE;
	}
	free(matrix);
	return TRUE;
}
int MDRII_API(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr)
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
		show_error("MDR","API","No memory");
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
		show_error("MDRII","API","No memory");
		return FALSE;
	}
	resTF=MDRII_create_encode_matrix(matrix);
	if(resTF==FALSE)
	{
		show_error("MDRII","API","bit matrix can't create");
		return FALSE;
	}

	resTF=matrix_bitmatrix_encode_stripsect_RAID6(strsetblockgroupptr,pparityptr,qparityptr,matrix);
	if(resTF==FALSE)
	{
		show_error("MDRII","API","EVENODD RAID6 can't calculate");
		return FALSE;
	}
	resTF=matrix_destroy(matrix);
	if(resTF==FALSE)
	{
		show_error("MDRII","API","matrix can't free");
		return FALSE;
	}
	free(matrix);
	return TRUE;
}

int MDRI_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix)
{
	return TRUE;
}
int MDRII_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix)
{
	return TRUE;
}



int MDRI_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr)
{
	return TRUE;
}
int MDRII_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr)
{
	return TRUE;
}
/*int MDRI_create_encode_matrix(BITMATRIXGROUP *matrix)
{
	//创建MDRI编码矩阵
	BITMATRIX *Bmatrixptr,*curBmatrixptr;
	UINT32 *mat;
	int i,k,groupsize,matrixsize;
	//开始赋值
	
	groupsize=matrix->groupsize;
	Bmatrixptr=matrix->matrix;
	k=groupsize-1;
	if(Bmatrixptr==NULL)
	{
		Bmatrixptr=talloc(BITMATRIX,groupsize);//开空间
		if(Bmatrixptr==NULL)
		{
			show_error("MDRI","matrix_create","No memory");
			return FALSE;
		}

		matrixsize=2^k;
		curBmatrixptr=Bmatrixptr;
		for(i=0;i<groupsize;i++)
		{
			mat=talloc(UINT32,matrixsize);
			if(mat==NULL)
			{
				show_error("MDRI","matrix_create","No memory");
				return FALSE;
			}
			curBmatrixptr->matrix=mat;
			curBmatrixptr++;
		}
		matrix->matrix=Bmatrixptr;
	}
	
	return TRUE;
}
int MDRII_create_encode_matrix(BITMATRIXGROUP *matrix)
{
	//创建MDRII编码矩阵
	BITMATRIX *Bmatrixptr,*curBmatrixptr;
	UINT32 *mat;
	int i,k,groupsize,matrixsize;
	//开始赋值
	
	groupsize=matrix->groupsize;
	Bmatrixptr=matrix->matrix;
	k=groupsize-1;
	if(k<3)
	{
		show_error("MDRII","matrix_create","k should bigger than 3");
		return FALSE;
	}
	if(Bmatrixptr==NULL)
	{
		Bmatrixptr=talloc(BITMATRIX,groupsize);
		if(Bmatrixptr==NULL)
		{
			show_error("MDRII","matrix_create","No memory");
			return FALSE;
		}
		matrixsize=2^(k-1);
		curBmatrixptr=Bmatrixptr;
		for(i=0;i<groupsize;i++)
		{
			mat=talloc(UINT32,matrixsize);
			if(mat==NULL)
			{
				show_error("MDRI","matrix_create","No memory");
				return FALSE;
			}
			curBmatrixptr->matrix=mat;
			curBmatrixptr++;
		}
		matrix->matrix=Bmatrixptr;
	}
	
	return TRUE;
}*/