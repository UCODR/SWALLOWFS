#include "MDR.h"

int MDRI_create_encode_matrix_B(BITMATRIX *matrix)//k����������+p��
{
	//����B����
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
		mat=talloc(UINT32,rows*cols);//���ռ�
		if(mat==NULL)
		{
			show_error("MDRI","create_encode_matrix","No memory");
			return FALSE;
		}
	}
	tempmat1=talloc(UINT32,8);//����һ���ռ俪8��
	if(tempmat1==NULL)
	{
		show_error("MDR","create_encode_matrix","No memory");
		return FALSE;
	}
	for(i=0;i<2;i++)//����������ϲ�
	{
		tempmat1[i]=MDRIB1matrix[i];
		tempmat1[i+2]=MDRIB2matrix[i];
		tempmat1[i+4]=MDRIB1matrix[i+2];
		tempmat1[i+6]=MDRIB2matrix[i+2];
	}
	if(k==2)
	{
		//ֱ�ӷ����������
		//free(mat);//�ͷſռ�
		mcpy(mat,tempmat1,UINT32,rows*cols);
		free(tempmat1);
		return TRUE;
	}
	ltempwsize=2;
	ltempcols=4;
	ltemprows=2;

	ntempcols=12;
	ntemprows=4;
	tempwsize=4;//ÿһ����ǰ��w��С

	for(i=3;i<(k+1);i++)//��Ϊk�����Կ��Դ�3��ʼ���ȼ���k-1����Ŀ�����
	{
		//������Ҫ���ڴ�����ǰ
		tempsize=i*tempwsize*tempwsize;
		tempmat2=talloc(UINT32,tempsize);
		if(tempmat2==NULL)
		{
			show_error("MDR","create_encode_matrix","No memory");
			return FALSE;
		}
		bzero(tempmat2,UINT32,tempsize);
		//��ʼ����
		for(j=0;j<tempwsize;j++)
		{
			index=j*ntempcols;//��λ
			for(u=0;u<i;u++)//��ǰ�ڼ�������
			{
				windex=u*tempwsize;//��ǰ����
				//��λ�������㷨
				if(u<(i-2))
				{
					for(v=0;v<tempwsize;v++)//����һ�в������
					{
						if(j<(tempwsize/2))//������°벿��
						{
							if(v<(tempwsize/2))
							{
								//j*cols/2;
								tarindex=index+windex+v;//����λ��

								lindex=j*ltempcols;
								lwindex=u*ltempwsize;
								isouindex=lindex+lwindex+v;//��������

								lindex=j*ltempcols;
								lwindex=(i-2)*ltempwsize;//
								ksouindex=lindex+lwindex+v;

								tempmat2[tarindex]=tempmat1[isouindex]+tempmat1[ksouindex];
								
								//tempmat2[tarindex]=
							}
						}
						else
						{
							if(v>=(tempwsize/2))//����ڵ�������
							{
								tarindex=index+windex+v;//����λ��

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
					for(v=0;v<tempwsize;v++)//����һ�в������
					{
						//�ڶ�����
						if(j<(tempwsize/2))
						{
							if(v>=(tempwsize/2))
							{
								if(j==(v-tempwsize/2))//�ж�����
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
						//��������
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
		
		free(tempmat1);//ǰ��һ����Ҫ��
		tempmat1=tempmat2;
		ltempwsize=tempwsize;
		ltempcols=ntempcols;
		ltemprows=ntemprows;
		//���¼��㵱ǰ����
		tempwsize=tempwsize*2;
		ntemprows=tempwsize;
		ntempcols=tempwsize*(i+1);
	}
	//������������
	mcpy(mat,tempmat1,UINT32,rows*cols);
	free(tempmat1);

	return TRUE;
}
int MDRII_create_encode_matrix_B(BITMATRIX *matrix)
{
	//����B����
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
		mat=talloc(UINT32,rows*cols);//���ռ�
		if(mat==NULL)
		{
			show_error("MDR","create_encode_matrix","No memory");
			return FALSE;
		}
	}
	tempmat1=talloc(UINT32,4*16);//����һ���ռ俪8��
	if(tempmat1==NULL)
	{
		show_error("MDR","create_encode_matrix","No memory");
		return FALSE;
	}
	for(i=0;i<4;i++)//����������ϲ�
	{
		
		for(u=0;u<4;u++)//����һ��
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
		//ֱ�ӷ����������
		//free(mat);//�ͷſռ�
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

		for(j=0;j<tempwsize;j++)//���м���
		{
			index=j*ntempcols;//��λ
			for(u=0;u<i;u++)//�ڼ�������
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
								isouindex=lindex+lwindex+v;//��������

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
								isouindex=lindex+lwindex+(v-tempwsize/2);//��������

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
							if(v<(tempwsize/2))//��һ����
							{
								tarindex=index+windex+v;

								lindex=j*ltempcols;
								lwindex=u*ltempwsize;
								isouindex=lindex+lwindex+v;//��������

								tempmat2[tarindex]=tempmat1[isouindex];
							}
							else//�ڶ�����
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
							if(v>=(tempwsize/2))//��������
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
		free(tempmat1);//ǰ��һ����Ҫ��
		tempmat1=tempmat2;
		ltempwsize=tempwsize;
		ltempcols=ntempcols;
		ltemprows=ntemprows;

		tempwsize=tempwsize*2;
		ntemprows=tempwsize;
		ntempcols=tempwsize*(i+1);
	}
	//������������
	mcpy(mat,tempmat1,UINT32,rows*cols);
	free(tempmat1);

	return TRUE;
}

//����w����w������ȣ�kΪ������
int MDRI_create_encode_matrix(BITMATRIX *matrix)
{
	BITMATRIX *matrixB;//����
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

	matB=talloc(UINT32,rowsB*colsB);//�������ݿ�
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
	//��������A
	//����p��
	for(i=0;i<w;i++)
	{
		index=i*cols+i;
		for(j=0;j<k;j++)
		{
			mat[index]=1;
			index+=w;
		}
	}     
	//����q��
	for(i=0;i<rows;i++)
	{
		index=w*cols+i*cols;//��������
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
//����w����w������ȣ�kΪ������
int MDRII_create_encode_matrix(BITMATRIX *matrix)
{
	BITMATRIX *matrixB;//����
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

	matB=talloc(UINT32,rowsB*colsB);//�������ݿ�
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
	//��������A
	//����p��
	for(i=0;i<w;i++)
	{
		index=i*cols+i;
		for(j=0;j<k;j++)
		{
			mat[index]=1;
			index+=w;
		}
	}     
	//����q��
	for(i=0;i<rows;i++)
	{
		index=w*cols+i*cols;//��������
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
	//����MDRI�������
	BITMATRIX *Bmatrixptr,*curBmatrixptr;
	UINT32 *mat;
	int i,k,groupsize,matrixsize;
	//��ʼ��ֵ
	
	groupsize=matrix->groupsize;
	Bmatrixptr=matrix->matrix;
	k=groupsize-1;
	if(Bmatrixptr==NULL)
	{
		Bmatrixptr=talloc(BITMATRIX,groupsize);//���ռ�
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
	//����MDRII�������
	BITMATRIX *Bmatrixptr,*curBmatrixptr;
	UINT32 *mat;
	int i,k,groupsize,matrixsize;
	//��ʼ��ֵ
	
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