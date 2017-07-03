//������Ҫʵ��int������Ϊ�����һ�㲻�漰��������
#include "matrix.h"
//ͳ�Ƶ�ǰ������1�ĸ���
int matrix_count_number_one(BITMATRIX *matrix)
{
	int i,j;
	int countnum;
	UINT32 *mat;
	int rows,cols,w;
	int curindex,rowsindex,colsindex;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;


	countnum=0;
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			rowsindex=i*cols;
			colsindex=j;
			curindex=rowsindex+colsindex;
			if(mat[curindex]==1)
			{
				countnum++;
			}
		}
	}
	return TRUE;
}
//ͳ�Ƶ�ǰ������0�ĸ���
int matrix_count_number_zero(BITMATRIX *matrix)
{
	int i,j;
	int countnum;
	UINT32 *mat;
	int rows,cols,w;
	int curindex,rowsindex,colsindex;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;


	countnum=0;
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			rowsindex=i*cols;
			colsindex=j;
			curindex=rowsindex+colsindex;
			if(mat[curindex]==0)
			{
				countnum++;
			}
		}
	}
	return TRUE;
}


INTMATRIX matrix_create_w08(UINT32 *matrix,int rows,int cols)//������Ӧ8λ������mat��ֵ��ȥ,c�޷������ά��������ֻ��һά
{
	INTMATRIX res;
	res.matrix=(UINT32 *)matrix;
	res.w=8;
	res.xm=rows;
	res.ym=cols;
	return res;
	//for(i=0;i<;i++)
}
INTMATRIX matrix_create_w16(UINT32 *matrix,int rows,int cols)//����16λ
{
	INTMATRIX res;
	res.matrix=(UINT32 *)matrix;
	res.w=16;
	res.xm=rows;
	res.ym=cols;
	return res;
}
INTMATRIX matrix_create_w32(UINT32 *matrix,int rows,int cols)//����32λ
{
	INTMATRIX res;
	res.matrix=matrix;
	res.w=32;
	res.xm=rows;
	res.ym=cols;
	return res;
}

INTMATRIX matrix_create_NULL()//����һ���յ�INTMATRIX
{
	INTMATRIX matrix;
	matrix.w=NOSIZE;
	matrix.xm=NOSIZE;
	matrix.ym=NOSIZE;
	matrix.matrix=NULL;
	return matrix;
	//INTMATRIX *mx;
	//mx=&matrix;
	//mx->w=0;
	//mx->xm=0;
	//mx->ym=0;
	//mx->matrix=NULL;	
}
int matrix_set_data(INTMATRIX *matrix,UINT32 *mat,int rows,int cols,int w)//�趨��
{
	matrix->matrix=mat;
	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w=w;
	return TRUE;
}
INTMATRIX matrix_duplicate(INTMATRIX *matrix)//���ƾ���
{
	INTMATRIX res;
	INTMATRIX *resx;
	int rows,cols;
	resx=&res;
	rows=matrix->xm;
	cols=matrix->ym;
	resx->xm=matrix->xm;
	resx->ym=matrix->ym;
	resx->w=matrix->w;
	resx->matrix=malloc(sizeof(UINT32)*rows*cols);
	//������������
	memcpy(resx->matrix,matrix->matrix,sizeof(UINT32)*rows*cols);
	return res;
}
int matrix_bitmatrix_data_copy(BITMATRIX *tarmatrix,BITMATRIX *soumatrix,int offset,int size)
{
	UINT32 *tarmat;
	UINT32 *soumat;

	tarmat=tarmatrix->matrix;
	soumat=soumatrix->matrix;
	tarmat=tarmat+offset;
	mcpy(tarmat,soumat,UINT32,size);
	return TRUE;
}
int matrix_destroy(INTMATRIX *matrix)//����һ������
{
	free(matrix->matrix);
	matrix->matrix=NULL;
	matrix->w=NOSIZE;
	matrix->xm=NOSIZE;
	matrix->ym=NOSIZE;
	return TRUE;
}
void matrix_print_matrix_outcheck(INTMATRIX *matrix)//��ʾ10������Ӧ��������,����wΪ��Ӧ���ֳ�
{
	int i,j,fw,w;
	char s[30];
	unsigned int w2;
	int rows,cols;
	int *mat;
	mat=matrix->matrix;
	w=matrix->w;
	rows=matrix->xm;//�Ƚ��������ݶ���
	cols=matrix->ym;
	if(w==32)
	{
		fw=11;//32λͳһ��ʾΪ11λ
	}
	else
	{
		w2=(1<<w);
		sprintf(s,"%u",w2-1);
		fw=strlen(s)+1;//���1λ
	}

	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			printf("%*d",fw,mat[i*cols+j]);
		}
		printf("\n");
	}
}
void matrix_print_matrix(INTMATRIX *matrix)//��ʾ10������Ӧ��������,����wΪ��Ӧ���ֳ�
{
	int i,j,fw,w;
	char s[30];
	unsigned int w2;
	int rows,cols;
	int *mat;
	//UINT8 **mat8=NULL;
	//UINT16 **mat16=NULL;
	//UINT32 **mat32=NULL;
	mat=matrix->matrix;
	w=matrix->w;
	rows=matrix->xm;//�Ƚ��������ݶ���
	cols=matrix->ym;
	//mat=matrix.matrix;
	if(w!=8&&w!=16&&w!=32)
	{
		show_error("matrix","w","outofrage");
		return;
	}
	//�������С�仯ָ��
	/*switch(w)
	{
	case 8:
		mat8=(UINT8 **)mat;
		break;
	case 16:
		mat16=(UINT16 **)mat;
		break;
	case 32:
		mat32=mat;
		break;
	}*///������ù�����
	if(w==32)
	{
		fw=11;//32λͳһ��ʾΪ11λ
	}
	else
	{
		w2=(1<<w);
		sprintf(s,"%u",w2-1);
		fw=strlen(s)+1;//���1λ
	}

	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			printf("%*d",fw,mat[i*cols+j]);
		/*
			switch(w)
			{
			case 8:
				printf("%*d",fw,matrix.matrix.matrix8[i*rows+j]);
				break;
			case 16:
				printf("%*d",fw,matrix.matrix.matrix16[i*rows+j]);
				break;
			case 32:
				printf("%*d",fw,matrix.matrix.matrix32[i*rows+j]);
				break;
			}*///*����һ������width
		}
		printf("\n");
	}
}
void matrix_print_16Xmatrix(INTMATRIX *matrix)//��ʾ16������Ӧ��������,����wΪ��Ӧ���ֳ�
{
	int i,j,fw,w;
	char s[30];
	unsigned int w2;
	int rows,cols;
	int *mat;
	//UINT8 **mat8=NULL;
	//UINT16 **mat16=NULL;
	//UINT32 **mat32=NULL;
	mat=matrix->matrix;
	w=matrix->w;
	rows=matrix->xm;//�Ƚ��������ݶ���
	cols=matrix->ym;
	//mat=matrix.matrix;
	if(w!=8&&w!=16&&w!=32)
	{
		show_error("matrix","w","outofrage");
		return;
	}
	//�������С�仯ָ��
	/*switch(w)
	{
	case 8:
		mat8=(UINT8 **)mat;
		break;
	case 16:
		mat16=(UINT16 **)mat;
		break;
	case 32:
		mat32=mat;
		break;
	}*/
	
	if(w==32)
	{
		fw=9;//32λͳһ��ʾΪ9λ
	}
	else
	{
		w2=(1<<w);
		sprintf(s,"%X",w2-1);
		fw=strlen(s)+1;//���1λ
	}

	
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			printf("%*X",fw,mat[i*cols+j]);
			/*
			switch(w)
			{
			case 8:
				printf("%*X",fw,matrix.matrix.matrix8[i*rows+j]);
				break;
			case 16:
				printf("%*X",fw,matrix.matrix.matrix16[i*rows+j]);
				break;
			case 32:
				printf("%*X",fw,matrix.matrix.matrix32[i*rows+j]);
				break;
			}*///*����һ������width
		}
		printf("\n");
	}
}
void matrix_print_bitmatrix_oneline(BITMATRIX *matrix)
{
	int i;
	int cols;
	UINT32 *mat;
	mat=matrix->matrix;
	cols=matrix->xm;
	for(i=0;i<cols;i++)
	{
		printf("%d",mat[i]);
	}
	printf("\n");
}
void matrix_print_bitmatrix(INTMATRIX *matrix)
{
	int i,j,w,rows,cols;
	UINT32 *m;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;
	m=matrix->matrix;
	for(i=0;i<rows;i++)
	{
		if(i!=0&&i%w==0) printf("\n");
		for(j=0;j<cols;j++)
		{
			if(j!=0&&j%w==0) printf(" ");
			printf("%d",m[i*cols+j]);
		}
		printf("\n");
	}
}

int matrix_invert(INTMATRIX *matrix,INTMATRIX *invmatrix)//ʵ�������
{
	int i,j,k,w,x,rows,cols,dw,drows,dcols,ssize,dsize,row_start,rs2,tmp,inverse;
	UINT32 *mat;
	//,**matind;
	UINT32 *inv;
	//,**invind;
	//INTMATRIX res;
	w=matrix->w;rows=matrix->xm;cols=matrix->ym;
	dw=invmatrix->w;drows=matrix->xm;dcols=matrix->ym;
	ssize=rows*cols;
	dsize=drows*dcols;
	//mat=matrix.matrix;
	mat=matrix->matrix;
	//invind=(UINT32 **)inv;
	//matind=(UINT32 **)mat;//
	if(mat==NULL)
	{
		show_error("matrix","matrix","NULL");
		return FALSE;
	}
	if(cols!=rows)//����в�������ֱ�ӷ���
	{
		show_error("matrix","invert","rows!=cols");
		return FALSE;
	}
	if(invmatrix->matrix==NULL||(dsize<ssize))//����Ŀ������ǲ���Ϊ��,���ǿռ��Ƿ���
	{
		inv=(UINT32 *)malloc(sizeof(UINT32)*rows*cols);
	}
	else
	{
		//������ԭ���Ŀռ�
		inv=invmatrix->matrix;
	}

	
	
	k=0;
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			inv[k]=(i==j)?1:0;
			k++;
		}
	}
	//ת��Ϊ��������
	for(i=0;i<cols;i++)
	{
		row_start=cols*i;
		//�����Խ�i,i���Ϊ0����ô������
		if(mat[row_start+i]==0)
		{
			for(j=i+1;j<rows&&mat[cols*j+i]==0;j++) ;//��������0��
			if(j==rows) return FALSE;//���������û�з���FALSE
			rs2=j*cols;
			for(k=0;k<cols;k++)//�ҵ��󽻻��������е�Ԫ��
			{
				//ͬ������
				tmp=mat[row_start+k];
				mat[row_start+k]=mat[rs2+k];
				mat[rs2+k]=tmp;
				tmp=inv[row_start+k];
				inv[row_start+k]=inv[rs2+k];
				inv[rs2+k]=tmp;
			}
		}
		
		tmp=mat[row_start+i];
		//��Ҫ*(i,i)����Ԫ��Ϊ1
		if(tmp!=1)
		{
			inverse=galois_inverse(tmp,w);
			for(j=0;j<cols;j++)//����mat����Ӧ�������
			{
				mat[row_start+j]=galois_single_multiply(mat[row_start+j],inverse,w);
				inv[row_start+j]=galois_single_multiply(inv[row_start+j],inverse,w);
			}
		}
		//���е�j>i,���г˼�
		k=row_start+i;
		for(j=i+1;j!=cols;j++)
		{
			k+=cols;
			if(mat[k]!=0)//�����Ϊ0��Ҫ����
			{
				if(mat[k]==1)//
				{
					rs2=cols*j;
					for(x=0;x<cols;x++)
					{
						mat[rs2+x]^=mat[row_start+x];
						inv[rs2+x]^=inv[row_start+x];
					}
				}
				else
				{
					tmp=mat[k];//��ǰ��Ҫ���г˷���Ԫ��
					rs2=cols*j;
					for(x=0;x<cols;x++)
					{
						mat[rs2+x]^=galois_single_multiply(tmp,mat[row_start+x],w);
						inv[rs2+x]^=galois_single_multiply(tmp,inv[row_start+x],w);//ɨ��һ��
					}
				}
			}	
		}
	}
	//�������������󻯳ɵ�λ��
	for(i=rows-1;i>=0;i--)
	{
		row_start=i*cols;
		for(j=0;j<i;j++)
		{
			rs2=j*cols;//��λԪ��
			if(mat[rs2+i]!=0)
			{
				tmp=mat[rs2+i];//�ҳ���Ӧ��Ҫ�˵�����
				mat[rs2+i]=0;
				for(k=0;k<cols;k++)
				{
					inv[rs2+k]^=galois_single_multiply(tmp,inv[row_start+k],w);//���ڣ�i,i���г˼�tmp��mat�ϵ���ֵ���ӵ�inv��Ӧλ��
				}
			}
		}
	}
	//�������д��invmatrix
	invmatrix->matrix=inv;
	invmatrix->xm=rows;
	invmatrix->ym=cols;
	invmatrix->w=w;
	return TRUE;
}
int matrix_invertible_matrix(INTMATRIX *matrix)
{
	//��������Ƿ����
	int i,j,k,w,x,rows,cols,row_start,rs2,tmp,inverse;
	UINT32 *mat;
	w=matrix->w;rows=matrix->xm;cols=matrix->ym;
	if(cols!=rows)//����в�������ֱ�ӷ���
	{
		show_error("matrix","invert","rows!=cols");
		return FALSE;
	}
	mat=matrix->matrix;
	if(mat!=NULL)
	{
		show_error("matrix","matrix","NULL");
		return FALSE;
	}
	/*k=0;//������Ӧ�ĵ�λ��
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			inv[k]=(i==j)?1:0;
			k++;
		}
	}*/
	//ת��Ϊ��������
	for(i=0;i<cols;i++)
	{
		row_start=cols*i;
		//�����Խ�i,i���Ϊ0����ô������
		if(mat[row_start+i]==0)
		{
			for(j=i+1;j<rows&&mat[cols*j+i]==0;j++) ;//��������0��
			if(j==rows) return FALSE;//���������û�з���FALSE
			rs2=j*cols;
			for(k=0;k<cols;k++)//�ҵ��󽻻��������е�Ԫ��
			{
				//ͬ������
				tmp=mat[row_start+k];
				mat[row_start+k]=mat[rs2+k];
				mat[rs2+k]=tmp;
				//tmp=inv[row_start+k];
				//inv[row_start+k]=inv[rs2+k];
				//inv[rs2+k]=tmp;
			}
		}
		
		tmp=mat[row_start+i];
		//��Ҫ*(i,i)����Ԫ��Ϊ1
		if(tmp!=1)
		{
			inverse=galois_inverse(tmp,w);
			for(j=0;j<cols;j++)//����mat����Ӧ�������
			{
				mat[row_start+j]=galois_single_multiply(mat[row_start+j],inverse,w);
				//inv[row_start+j]=galois_single_multiply(inv[row_start+j],inverse,w);
			}
		}
		//���е�j>i,���г˼�
		k=row_start+i;
		for(j=i+1;j!=cols;j++)
		{
			k+=cols;
			if(mat[k]!=0)//�����Ϊ0��Ҫ����
			{
				if(mat[k]==1)//
				{
					rs2=cols*j;
					for(x=0;x<cols;x++)
					{
						mat[rs2+x]^=mat[row_start+x];
						//inv[rs2+x]^=inv[row_start+x];
					}
				}
				else
				{
					tmp=mat[k];//��ǰ��Ҫ���г˷���Ԫ��
					rs2=cols*j;
					for(x=0;x<cols;x++)
					{
						mat[rs2+x]^=galois_single_multiply(tmp,mat[row_start+x],w);
						//inv[rs2+x]^=galois_single_multiply(tmp,inv[row_start+x],w);//ɨ��һ��
					}
				}
			}	
		}
	}
	//����������������������ͨ���˾Ϳ���
	return TRUE;
}
int matrix_matrix_multiply(INTMATRIX *mat1,INTMATRIX *mat2,INTMATRIX *res)
{
	int i,j,k,w1,w2,rows1,rows2,rows3,cols1,cols2,cols3,dsize,ssize;
	UINT32 *m1,*m2,*pro;
	m1=mat1->matrix;
	m2=mat2->matrix;
	rows1=mat1->xm;
	rows2=mat2->xm;
	rows3=res->xm;
	cols1=mat1->ym;
	cols2=mat2->ym;
	cols3=res->ym;
	w1=mat1->w;
	w2=mat2->w;
	dsize=rows3*cols3;//Ŀ������
	ssize=rows1*cols2;// ԭ����
	//������Ҫ���w���Ƿ���ϳ˷�����
	if(cols1!=rows2||w1!=w2)
	{
		show_error("matrix","multiply","unmultipliable");
		return FALSE;
	}
	//���mat1,mat2
	if(m1==NULL||m2==NULL)
	{
		show_error("matrix","multiply","MatrixNULL");
		return FALSE;
	}
	//���invmatrix
	if(res->matrix==NULL||(dsize<ssize))//����Ŀ������ǲ���Ϊ��,���ǿռ��Ƿ���
	{
		pro=(UINT32 *)malloc(sizeof(UINT32)*rows1*cols2);
	}
	else
	{
		//������ԭ���Ŀռ�
		pro=res->matrix;
	}
	for(i=0;i<rows1*cols2;i++) pro[i]=0;
	for(i=0;i<rows1;i++)
	{
		for(j=0;j<cols2;j++)
		{
			for(k=0;k<rows2;k++)
			{
				pro[i*cols2+j]^=galois_single_multiply(m1[i*cols1+k],m2[k*cols2+j],w1);
			}
		}
	}
	res->matrix=pro;
	res->w=w1;
	res->xm=rows1;
	res->ym=cols2;
	return TRUE;
}

int matrix_invert_bitmatrix(BITMATRIX *matrix,BITMATRIX *invmatrix)//����bitmatrix�������
{
	//bitmatrix���ٰ�����
	int cols,rows,w,drows,dcols,dw,i,j,k;
	int tmp,ssize,dsize;
	int *mat,*inv;//ԭʼ�������
	
	rows=matrix->xm;//��ֵ��ʼ��
	cols=matrix->ym;//
	w=matrix->w;
	mat=matrix->matrix;
	
	drows=invmatrix->xm;
	dcols=invmatrix->ym;
	dw=invmatrix->w;
	inv=invmatrix->matrix;
	
	ssize=rows*cols;
	dsize=drows*dcols;
	if(mat==NULL)
	{
		show_error("matrix","matrix","NULL");
		return FALSE;
	}
	if(rows!=cols)//���rows��cols�Ƿ����
	{
		show_error("matrix","invert","rows!=cols");
		return FALSE;
	}
	
	if(invmatrix->matrix==NULL||(dsize<ssize))//����Ŀ������ǲ���Ϊ��,���ǿռ��Ƿ���
	{
		inv=(UINT32 *)malloc(sizeof(UINT32)*rows*cols);
	}
	else
	{
		//������ԭ���Ŀռ�
		inv=invmatrix->matrix;
	}
	k=0;
	//��ʼ��inv
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			inv[k]=(i==j)?1:0;
			k++;
		}
	}
	//ת������
	for(i=0;i<cols;i++)
	{
		//���Խ��߲����ڣ��򲻿���
		if((mat[i*cols+i])==0)
		{
			for(j=i+1;j<rows&&(mat[j*cols+i])==0;j++) ;//�Ϸ���������
			if(j==rows) return -1;
			for(k=0;k<cols;k++)//������������
			{
				tmp=mat[i*cols+k];mat[i*cols+k]=mat[j*cols+k];mat[j*cols+k]=tmp;
				tmp=inv[i*cols+k];inv[i*cols+k]=inv[j*cols+k];inv[j*cols+k]=tmp;
			}
		}
		//���ڶ������е�j>i,ֻ������������
		for(j=i+1;j!=rows;j++)
		{
			if(mat[j*cols+i]!=0)
			{
				for(k=0;k<cols;k++)
				{
					mat[j*cols+k]^=mat[i*cols+k];
					inv[j*cols+k]^=inv[i*cols+k];
				}
			}
		}
	}
	//����������ת��Ϊ��λ��
	for(i=rows-1;i>=0;i--)
	{
		for(j=0;j<i;j++)
		{
			if(mat[j*cols+i])
			{
				for(k=0;k<cols;k++)
				{
					mat[j*cols+k]^=mat[i*cols+k];
					inv[j*cols+k]^=inv[i*cols+k];
				}
			}
		}
	}
	return TRUE;
}

int matrix_invertable_bitmatrix(BITMATRIX *matrix)//bitmatrix�Ƿ����
{
	//bitmatrix���ٰ�����
	int cols,rows,w,i,j,k;//��������
	int tmp;
	int *mat;//ԭʼ�������

	rows=matrix->xm;//��ֵ��ʼ��
	cols=matrix->ym;//
	w=matrix->w;
	mat=matrix->matrix;

	if(mat==NULL)
	{
		show_error("matrix","matrix","NULL");
		return FALSE;
	}
	if(rows!=cols)//���rows��cols�Ƿ����
	{
		show_error("matrix","invert","rows!=cols");
		return FALSE;
	}
	//����������
	for(i=0;i<cols;i++)
	{
		//���Խ��߲����ڣ��򲻿���
		if((mat[i*cols+i])==0)
		{
			for(j=i+1;j<rows&&(mat[j*cols+i])==0;j++) ;
			if(j==rows) return FALSE;
			for(k=0;k<cols;k++)
			{
				tmp=mat[i*cols+k];mat[i*cols+k]=mat[j*cols+k];mat[j*cols+k]=tmp;
			}
		}
		//���ڽ����ۼӼ���
		for(j=i+1;j!=rows;j++)
		{
			if(mat[j*cols+i]!=0)
			{
				for(k=0;k<cols;k++)//ɨ��һ��
				{
					mat[j*cols+k]^=mat[i*cols+k];
				}
			}
		}
	}
	return TRUE;
}

//chunk����
CHUNK matrix_CHUNK_create_NULL()
{
	//��ʼ��
	CHUNK ck;
	ck.chunkcontent=NULL;
	ck.isparity=NOVALUE;
	ck.regionid=NODEVICE;
	ck.stripid=NODEVICE;
	ck.sizenum=NOSIZE;
	return ck;
}
CHUNKGROUP matrix_CHUNKGROUP_create_NULL()//�����������
{
	//��ʼ��
	CHUNKGROUP ckgroup;
	ckgroup.ckgroup=NULL;
	ckgroup.groupsize=NOSIZE;
	return ckgroup;
}

int matrix_CHUNK_print_data(CHUNK *ck,int cols)//���chunk������
{
	int size,isparity,i,j,rows,index;
	UINT64 regionid,stripid;
	BYTE* content;
	index=0;
	content=ck->chunkcontent;
	regionid=ck->regionid;
	isparity=ck->isparity;
	size=ck->sizenum;
	stripid=ck->stripid;
	if(size<0||content==NULL)
	{
		show_error("matrix","print","NULL");
		return FALSE;
	}
	printf("region id:%d.\n",regionid);
	printf("strip id:%d.\n",stripid);
	printf("size:%d.\n",size);
	printf("is parity:%s.\n",(isparity==TRUE)?"TRUE":"FALSE");
	if(size<cols)//ֻ�赥����ʾ
	{
		for(i=0;i<size;i++)
		{
			printf("%d ",content[i]);
		}
		printf("\n");
	}
	else
	{
		rows=size/cols;
		for(i=0;i<rows;i++)
		{
			for(j=0;j<cols;j++)
			{
				if(index<size)
				{
					printf("%d ",content[i*cols+j]);
				}
				else
				{
					printf("0 ");
				}
				index++;
			}
			printf("\n");
		}
	}
	return TRUE;
}

int matrix_CHUNK_copy_meta(CHUNK *desck,CHUNK *souck)//��ԭ���ݽ��п���
{

	if(desck==NULL)
	{
		desck=talloc(CHUNK,1);
		if(desck==NULL)
		{
			show_error("matrix","CHUNK_copy_meta","No memory");
			return FALSE;
		}
	}
	mcpy(desck,souck,CHUNK,1);
	desck->chunkcontent=NULL;//��ǰchunkcontent����Ϊ��
	return TRUE;
}

int matrix_CHUNK_set_data(CHUNK *ck,BYTE* data,UINT64 regionid,int isparity,UINT64 stripid,int sizenum)//�������ݿ�����
{
	//��ʼ��������
	CHUNK chk;
	if(ck==NULL)
	{
		chk=matrix_CHUNK_create_NULL();
		ck=&chk;
	}
	if(data==NULL)
	{
		show_error("matrix","chunk","data!=NULL");
		return FALSE;
	}
	if(regionid<0||stripid<0||sizenum<0)
	{
		show_error("matrix","chunk","illegal id");
		return FALSE;
	}
	if((isparity!=TRUE)&&(isparity!=FALSE))
	{
		show_error("matrix","chunk","illegeal parity");
		return FALSE;
	}
	ck->chunkcontent=data;
	ck->isparity=isparity;
	ck->regionid=regionid;
	ck->sizenum=sizenum;
	ck->stripid=stripid;
	return TRUE;
}

int matrix_CHUNK_copy_data(CHUNK *desck,CHUNK *souck)//��chunk֮���໥����
{
	BYTE* soudata;
	BYTE* desdata;
	int sizenum;
	soudata=souck->chunkcontent;
	sizenum=souck->sizenum;

	desdata=desck->chunkcontent;
	if(soudata==NULL)
	{
		//���Ԫ���ݲ�����
		show_error("matrix","souchunk","NULL");
		return FALSE;
	}
	/*if(desdata==NULL)//�����Ϊ�����ͷ�ָ��
	{
		free(desdata);
	}*/
	if(desdata==NULL)
	{
		desdata=talloc(BYTE,sizenum);//����ռ�
		if(desdata==NULL)
		{
			show_error("matrix","CHUNK_copy_data","No memory");
			return FALSE;
		}
		desck->chunkcontent=desdata;
	}
	memcpy(desdata,soudata,sizenum);//���ݿ�����ȥ
	set_state_memcpynum_add((UINT64)sizenum);
	
	/*
	//���������ݸ���//����û��Ҫ
	desck->isparity=souck->isparity;
	desck->regionid=souck->regionid;
	desck->sizenum=souck->sizenum;
	desck->stripid=souck->stripid;*/
	return TRUE;
}
int matrix_CHUNK_add_data(CHUNK *desck,CHUNK *souck)
{
	BYTE *soudata,*desdata;
	int i,ssize,dsize;
	soudata=souck->chunkcontent;
	desdata=desck->chunkcontent;
	ssize=souck->sizenum;
	dsize=desck->sizenum;
	if(ssize!=dsize)
	{
		show_error("matrix","chunkadd","sousize!=dessize");
		return FALSE;
	}
	//������
	//galois_region_add(soudata,desdata,ssize);
	for(i=0;i<ssize;i++)
	{
		(*desdata)=((*soudata)^(*desdata));
		desdata++;
		soudata++;
	}
	//����ͳ��ֵ
	set_state_xor_add((UINT64)ssize);
	return TRUE;
}
int matrix_CHUNK_w08_multiply(CHUNK *souck,UINT32 multby)//������08�����£��˷�
{
	//ʹ��galois���г˷�
	BYTE *soudata;
	int size;
	soudata=souck->chunkcontent;
	size=souck->sizenum;
	if(soudata==NULL||size<0)
	{
		show_error("matrix","multiply","souchunk==NULL");
		return FALSE;
	}
	galois_w08_region_multiply(soudata,multby,size,NULL,FALSE);
	set_state_w08_add(size);
	return TRUE;
}
int matrix_CHUNK_w16_multiply(CHUNK *souck,UINT32 multby)//������16�����£��˷�
{
	//ʹ��galois���г˷�
	BYTE *soudata;
	int size;
	soudata=souck->chunkcontent;
	size=souck->sizenum;
	if(soudata==NULL||size<0)
	{
		show_error("matrix","multiply","souchunk==NULL");
		return FALSE;
	}
	if(size%2!=0)//����Ƿ���Խ��м���
	{
		show_error("matrix","w16","should be 16x");
		return FALSE;
	}
	galois_w16_region_multiply(soudata,multby,size,NULL,FALSE);
	set_state_w16_add(size);
	return TRUE;
}
int matrix_CHUNK_w32_multiply(CHUNK *souck,UINT32 multby)//������32�����£��˷�
{
	//ʹ��galois���г˷�
	BYTE *soudata;
	int size;
	soudata=souck->chunkcontent;
	size=souck->sizenum;
	if(soudata==NULL||size<0)
	{
		show_error("matrix","multiply","souchunk==NULL");
		return FALSE;
	}
	if(size%4!=0)//����Ƿ���Խ��м���
	{
		show_error("matrix","w32","should be 32x");
		return FALSE;
	}
	galois_w32_region_multiply(soudata,multby,size,NULL,FALSE);
	set_state_w32_add(size);
	return TRUE;
}

int matrix_CHUNK_w08_multiply_add(CHUNK *desck,CHUNK *souck,UINT32 multby)
{
	//ʹ��galois���г˷�
	BYTE *soudata,*desdata;
	UINT64 regionid,stripid;
	int isparity;

	int size,dsize;
	soudata=souck->chunkcontent;
	size=souck->sizenum;
	regionid=souck->regionid;
	stripid=souck->stripid;
	isparity=souck->isparity;
	if(soudata==NULL||size<0)
	{
		show_error("matrix","multiply","souchunk==NULL");
		return FALSE;
	}
	desdata=desck->chunkcontent;
	dsize=desck->sizenum;
	if(dsize!=size)
	{
		/*if(desdata!=NULL)
		{
			free(desdata);
		}*/
		show_error("matrix","CHUNK_w08_multiply_add","source size!=target size");
		return FALSE;
	}
	if(desdata==NULL)
	{
		desdata=talloc(BYTE,size);//����ռ�
		if(desdata==NULL)
		{
			show_error("matrix","mutiply","no memory");
			return FALSE;
		}
		desck->chunkcontent=desdata;
	}
	galois_w08_region_multiply(soudata,multby,size,desdata,TRUE);//���µ������ۼӺ���
	set_state_w08_add(size);
	set_state_xor_add(size);
	//desck->isparity=isparity;
	//desck->regionid=regionid;
	//desck->stripid=stripid;
	//desck->sizenum=size;
	return TRUE;
}
//��ԴCHUNK��˼ӵ�Ŀ���
int matrix_CHUNK_w16_multiply_add(CHUNK *desck,CHUNK *souck,UINT32 multby)
{
	//ʹ��galois���г˷�
	BYTE *soudata,*desdata;
	UINT64 regionid,stripid;

	int size,dsize,isparity;
	soudata=souck->chunkcontent;
	size=souck->sizenum;
	regionid=souck->regionid;
	stripid=souck->stripid;
	isparity=souck->isparity;
	if(soudata==NULL||size<0)
	{
		show_error("matrix","multiply","souchunk==NULL");
		return FALSE;
	}
	desdata=desck->chunkcontent;
	dsize=desck->sizenum;
	if(dsize!=size)
	{
		/*if(desdata!=NULL)
		{
			free(desdata);
		}*/
		show_error("matrix","CHUNK_w16_multiply_add","source size!=target size");
		return FALSE;
	}
	if(desdata==NULL)
	{
		desdata=talloc(BYTE,size);//����ռ�
		if(desdata==NULL)
		{
			show_error("matrix","mutiply","no memory");
			return FALSE;
		}
		desck->chunkcontent=desdata;
	}
	if(size%2!=0)//����Ƿ���Խ��м���
	{
		show_error("matrix","w16","should be 16x");
		return FALSE;
	}
	galois_w16_region_multiply(soudata,multby,size,desdata,TRUE);//���µ������ۼӺ���
	set_state_w16_add(size);
	set_state_xor_add(size);
	//desck->isparity=isparity;
	//desck->regionid=regionid;
	//desck->stripid=stripid;
	//desck->sizenum=size;
	return TRUE;
}
int matrix_CHUNK_w32_multiply_add(CHUNK *desck,CHUNK *souck,UINT32 multby)
{
	//ʹ��galois���г˷�
	BYTE *soudata,*desdata;
	UINT64 regionid,stripid;

	int size,dsize,isparity;
	soudata=souck->chunkcontent;
	size=souck->sizenum;
	regionid=souck->regionid;
	stripid=souck->stripid;
	isparity=souck->isparity;
	if(soudata==NULL||size<0)
	{
		show_error("matrix","multiply","souchunk==NULL");
		return FALSE;
	}
	desdata=desck->chunkcontent;
	dsize=desck->sizenum;
	if(dsize!=size)
	{
		/*if(desdata!=NULL)
		{
			free(desdata);
		}*/
		show_error("matrix","CHUNK_w32_multiply_add","source size!=target size");
		return FALSE;
	}
	if(desdata==NULL)
	{
		desdata=talloc(BYTE,size);//����ռ�
		if(desdata==NULL)
		{
			show_error("matrix","mutiply","no memory");
			return FALSE;
		}
		desck->chunkcontent=desdata;
	}
	if(size%4!=0)//����Ƿ���Խ��м���
	{
		show_error("matrix","w32","should be 32x");
		return FALSE;
	}
	galois_w32_region_multiply(soudata,multby,size,desdata,TRUE);//���µ������ۼӺ���
	set_state_w32_add(size);
	set_state_xor_add(size);
	//desck->isparity=isparity;
	//desck->regionid=regionid;
	//desck->stripid=stripid;
	//desck->sizenum=size;
	return TRUE;
}

//��desck�ƿգ�����souck��������ֵ��desck��
int matrix_CHUNK_w08_multiply_empty_add(CHUNK *desck,CHUNK *souck,UINT32 multby)
{
	//ʹ��galois���г˷�
	BYTE *soudata,*desdata;
	UINT64 regionid,stripid;
	int isparity;

	int size,dsize;
	soudata=souck->chunkcontent;
	size=souck->sizenum;
	regionid=souck->regionid;
	stripid=souck->stripid;
	isparity=souck->isparity;
	if(soudata==NULL||size<0)
	{
		show_error("matrix","multiply","souchunk==NULL");
		return FALSE;
	}
	desdata=desck->chunkcontent;
	dsize=desck->sizenum;
	if(dsize<size)
	{
		/*if(desdata!=NULL)
		{
			free(desdata);
		}*/
		show_error("matrix","CHUNK_w08_multiply_empty_add","source size!=target size");
		return FALSE;
	}
	if(desdata!=NULL)
	{
		desdata=talloc(BYTE,size);//����ռ�
		if(desdata==NULL)
		{
			show_error("matrix","mutiply","no memory");
			return FALSE;
		}
	}
	galois_w08_region_multiply(soudata,multby,size,desdata,FALSE);//���µ������ۼӺ���
	set_state_w08_add(size);
	set_state_memcpynum_add(size);
	//desck->isparity=isparity;
	//desck->regionid=regionid;
	//desck->stripid=stripid;
	//desck->sizenum=size;
	return TRUE;
}
//��desck�ƿգ�����souck��������ֵ��desck��
int matrix_CHUNK_w16_multiply_empty_add(CHUNK *desck,CHUNK *souck,UINT32 multby)
{
	//ʹ��galois���г˷�
	BYTE *soudata,*desdata;
	UINT64 regionid,stripid;
	int isparity;

	int size,dsize;
	soudata=souck->chunkcontent;
	size=souck->sizenum;
	regionid=souck->regionid;
	stripid=souck->stripid;
	isparity=souck->isparity;
	if(soudata==NULL||size<0)
	{
		show_error("matrix","multiply","souchunk==NULL");
		return FALSE;
	}
	desdata=desck->chunkcontent;
	dsize=desck->sizenum;
	if(dsize<size)
	{
		/*if(desdata!=NULL)
		{
			free(desdata);
		}*/
		show_error("matrix","CHUNK_w08_multiply_empty_add","source size!=target size");
		return FALSE;
	}
	if(desdata!=NULL)
	{
		desdata=talloc(BYTE,size);//����ռ�
		if(desdata==NULL)
		{
			show_error("matrix","mutiply","no memory");
			return FALSE;
		}
	}
	galois_w16_region_multiply(soudata,multby,size,desdata,FALSE);//���µ������ۼӺ���
	set_state_w16_add(size);
	set_state_memcpynum_add(size);
	//desck->isparity=isparity;
	//desck->regionid=regionid;
	//desck->stripid=stripid;
	//desck->sizenum=size;
	return TRUE;
}
//��desck�ƿգ�����souck��������ֵ��desck��
int matrix_CHUNK_w32_multiply_empty_add(CHUNK *desck,CHUNK *souck,UINT32 multby)
{//ʹ��galois���г˷�
	BYTE *soudata,*desdata;
	UINT64 regionid,stripid;
	int isparity;

	int size,dsize;
	soudata=souck->chunkcontent;
	size=souck->sizenum;
	regionid=souck->regionid;
	stripid=souck->stripid;
	isparity=souck->isparity;
	if(soudata==NULL||size<0)
	{
		show_error("matrix","multiply","souchunk==NULL");
		return FALSE;
	}
	desdata=desck->chunkcontent;
	dsize=desck->sizenum;
	if(dsize<size)
	{
		/*if(desdata!=NULL)
		{
			free(desdata);
		}*/
		show_error("matrix","CHUNK_w08_multiply_empty_add","source size!=target size");
		return FALSE;
	}
	if(desdata!=NULL)
	{
		desdata=talloc(BYTE,size);//����ռ�
		if(desdata==NULL)
		{
			show_error("matrix","mutiply","no memory");
			return FALSE;
		}
	}
	galois_w32_region_multiply(soudata,multby,size,desdata,FALSE);//���µ������ۼӺ���
	set_state_w32_add(size);
	set_state_memcpynum_add(size);
	//desck->isparity=isparity;
	//desck->regionid=regionid;
	//desck->stripid=stripid;
	//desck->sizenum=size;
	return TRUE;
}

int matrix_CHUNKGROUP_set_data(CHUNKGROUP* ckgroup,CHUNK* chunklist,int size)//����chunk���б�
{
	CHUNKGROUP chkgroup;
	if(ckgroup==NULL)
	{
		chkgroup=matrix_CHUNKGROUP_create_NULL();
		ckgroup=&chkgroup;
	}
	if(chunklist==NULL)
	{
		show_error("matrix","chunklist","chunklist!=NULL");
		return FALSE;
	}
	if(size<0)
	{
		show_error("matrix","size","should bigger than 0.");
		return FALSE;
	}
	ckgroup->ckgroup=chunklist;
	ckgroup->groupsize=size;
	return TRUE;
}
int matrix_CHUNKGROUP_add_CHUNK(CHUNKGROUP *ckgroup,CHUNK *ck)//��CHUNKGROUP�м���CHUNK
{
	int size;
	CHUNKGROUP chkgroup;
	CHUNK *chunklist;
	CHUNK *tmplist,*index;
	if(ckgroup==NULL)
	{
		chkgroup=matrix_CHUNKGROUP_create_NULL();
		ckgroup=&chkgroup;
	}
	if(ck==NULL)
	{
		show_error("matrix","chunk","chunk!=NULL");
		return FALSE;
	}
	chunklist=ckgroup->ckgroup;
	size=ckgroup->groupsize;
	size++;//��Ҫ����һλ
	
	if(size==0)//˵��û��ֻ��Ҫ����һ������,��size��Ұ
	{
		//chunklist=talloc(CHUNK,size);//����ռ�
		tmplist=talloc(CHUNK,size);//����ռ�	
		if(tmplist==NULL)
		{
			show_error("matrix","chunklist","no memory");
			return FALSE;
		}
		//index=tmplist++
		tmplist=ck;
		
	}
	else
	{
		//free(chunklist);
		//chunklist=talloc(CHUNK,size);//���·���ռ�
		tmplist=talloc(CHUNK,size);//����ռ�
		if(tmplist==NULL)
		{
			show_error("matrix","chunklist","no memory");
			return FALSE;
		}
		memcpy(tmplist,chunklist,(size-1)*sizeof(CHUNK));//�ֽ�֮ǰ������copy��ȥ
		index=tmplist+size-1;//������size-1Ϊ
		index->chunkcontent=ck->chunkcontent;//������copy����
		index->isparity=ck->isparity;
		index->regionid=ck->regionid;
		index->sizenum=ck->sizenum;
		index->stripid=ck->stripid;
		free(chunklist);
	}
	ckgroup->ckgroup=tmplist;
	ckgroup->groupsize=size;
	return TRUE;
}
int matrix_CHUNKGROUP_del_CHUNK(CHUNKGROUP *ckgroup,int index)//ɾ��index��
{
	//ֻ��Ҫ������ָ�����Ʋ��Ҹı���¼���
	
	int i,size;
	CHUNK *chklist;
	size=ckgroup->groupsize;
	chklist=ckgroup->ckgroup;
	for(i=index;i<size-1;i++)
	{
		chklist[i]=chklist[i+1];
	}
	//chklist[size-1]=NULL;
	size--;
	ckgroup->ckgroup=chklist;//С��ʹ�����괬
	ckgroup->groupsize=size;
	return TRUE;
}
//��Ϣ���ú���
DOTINF matrix_DOTINF_create_NULL()//����һ��dotinf
{
	DOTINF dotin;
	dotin.linenum=NODEVICE;
	dotin.colsnum=NOSIZE;
	dotin.src_ids=NULL;
	dotin.packetsize=NOSIZE;
	dotin.parityTF=NOSIZE;
	return dotin;
}
int matrix_DOTINF_set_data(DOTINF *dotin,int *src_ids,int linenum,int colsnum,int packetsize,int parityTF)//����dotinf����
{
	//int colsnum;
	dotin->linenum=linenum;
	dotin->src_ids=src_ids;
	dotin->colsnum=colsnum;
	dotin->parityTF=parityTF;
	return TRUE;
}
ERASES matrix_ERASES_create_NULL()
{
	ERASES erarray;
	erarray.codenum=NOSIZE;
	erarray.datanum=NOSIZE;
	erarray.totnum=NOSIZE;
	erarray.erases=NULL;
	return erarray;
}
int matrix_ERASES_set_data(ERASES *erarray,int *eras,int codenum,int datanum)
{
	erarray->codenum=codenum;
	erarray->datanum=datanum;
	erarray->totnum=codenum+datanum;
	erarray->erases=eras;
	return TRUE;
}
ENDECODEPARA matrix_ENDECODEPARA_create_NULL()//����һ���յ�papra
{
	ENDECODEPARA para;
	para.matrix=NULL;
	para.w=NOSIZE;
	return para;
}
int matrix_ENDECODEPARA_set_data(ENDECODEPARA *endecpara,int w,INTMATRIX *matrix)//����para����
{
	endecpara->matrix=matrix;
	endecpara->w=w;
	return TRUE;
}
//schedule��ز���
SCHEDOP matrix_SCHUDOP_create_NULL()//����һ��SCHUDOP
{
	SCHEDOP schop;
	schop.db=NOSIZE;
	schop.dd=NOSIZE;
	schop.op=NOSIZE;
	schop.sb=NOSIZE;
	schop.sd=NOSIZE;
	return schop;
}
int matrix_SCHUDOP_set_data(SCHEDOP *schedop,int op,int sd,int sb,int dd,int db,int istareget,CHUNK *tarchunkptr,UINT64 chunkid)//����SCHUDOP����
{
	schedop->op=op;
	schedop->sd=sd;
	schedop->sb=sb;
	schedop->dd=dd;
	schedop->db=db;
	schedop->istareget=istareget;
	schedop->tarchunkptr=tarchunkptr;
	schedop->tarchunkid=chunkid;
	return TRUE;
}

SCHEDULE matrix_SCHEDULE_create_NULL()//����һ��SCHUDOP
{
	SCHEDULE schud;
	schud.schedlist=NULL;
	schud.size=NOSIZE;
	return schud;
}
int matrix_SCHEDULE_set_data(SCHEDULE *sched,SCHEDOP *schudlist,int size,int w)//����SCHEDULE����
{
	sched->schedlist=schudlist;
	sched->size=size;
	sched->w=w;
	return TRUE;
}

extern DM_IDS matrix_DM_IDS_create_NULL()//ָʾ��ɾ�豸��
{
	DM_IDS dmids;
	dmids.dm_ids=NULL;
	dmids.size=NOSIZE;
	return dmids;
}
extern int matrix_DM_IDS_set_data(DM_IDS *dmids,int *dmarr,int size)
{
	dmids->dm_ids=dmarr;
	dmids->size=size;
	return TRUE;
}

//�������
int matrix_do_parity(CHUNKGROUP* ckgroup,CHUNK* parity)//����У���
{
	//����RAID-5У���
	int soudvnum,csize,psize,i;//ԭ�豸����
	BYTE* pdata;
	CHUNK* chklist;
	CHUNK* souchunk;
	soudvnum=ckgroup->groupsize;
	chklist=ckgroup->ckgroup;
	souchunk=chklist;
	csize=souchunk->sizenum;
	//�������ԭʼ���ݶ���
	pdata=parity->chunkcontent;
	psize=parity->sizenum;
	if(pdata==NULL)//�����ǲ���Ϊ��
	{
		pdata=talloc(BYTE,csize);//�ռ䲻���ڷ���֮
		if(pdata==NULL)
		{
			show_error("matrix","parity","no memory");
			return FALSE;
		}
		parity->chunkcontent=pdata;//���¸�ֵ��ȥ
	}
	else
	{
		if(psize<csize)//�ռ䲻�����·���
		{
			free(pdata);//��Ϊ���ͷ�
			pdata=talloc(BYTE,csize);//����洢�ռ�
			if(pdata==NULL)
			{
				show_error("matrix","parity","no memory");
				return FALSE;
			}
			parity->chunkcontent=pdata;//���¸�ֵ��ȥ
		}
	}
	//����parityȡֵ
	matrix_CHUNK_copy_data(parity,souchunk);
	for(i=1;i<soudvnum;i++)
	{
		//�������
		souchunk++;
		matrix_CHUNK_add_data(parity,souchunk);
	}	
	parity->isparity=TRUE;
	parity->regionid=souchunk->regionid;
	parity->sizenum=souchunk->sizenum;
	parity->stripid=souchunk->stripid;//��Ȼ�е���൫��Ϊ�˰�ȫ
	return TRUE;
}
int matrix_matrix_encode(CHUNKGROUP *pargroup,CHUNKGROUP *ckgroup,INTMATRIX *matrix)//���ɱ����
{
	//����INT�������
	int i,w,rows,cols,chknum,parnum;
	UINT32 *mat;
	CHUNK *chklist,*parlist;
	DOTINF dotin;
	w=matrix->w;
	rows=matrix->xm;
	cols=matrix->ym;
	mat=matrix->matrix;

	chklist=ckgroup->ckgroup;
	chknum=ckgroup->groupsize;

	parlist=pargroup->ckgroup;
	parnum=pargroup->groupsize;
	if(w!=8&&w!=16&&w!=32)
	{
		show_error("matrix","encode","number w is illegal");
		return FALSE;
	}
	if(rows<parnum)
	{
		//�������Խ��г˷�
		show_error("matrix","encode","rows is not enough");
		return FALSE;
	}
	//��Ҫ���ó�
	dotin=matrix_DOTINF_create_NULL();//����һ��dotinf
	for(i=0;i<parnum;i++)
	{
		matrix_DOTINF_set_data(&dotin,NULL,i,chknum,NOSIZE,TRUE);
		matrix_matrix_dotprod(matrix,ckgroup,parlist,&dotin);
		parlist++;
	}
	return TRUE;
}
//chunkblock���б���
int matrix_matrix_encode_BLOCK(CHUNKBLOCKGROUP *pargroup,CHUNKBLOCKGROUP *ckgroup,INTMATRIX *matrix)
{
	//����INT�������
	int i,w,rows,cols,chknum,parnum,resTF;
	UINT32 *mat;
	CHUNKBLOCK *datablockptr,*curdatablockptr;
	CHUNKBLOCK *parblockptr,*curparablockptr;
	CHUNK *parchunkptr;
	//CHUNK *chunkptr,*parchunkptr;
	DOTINF dotin;

	w=matrix->w;
	rows=matrix->xm;
	cols=matrix->ym;
	mat=matrix->matrix;

	datablockptr=ckgroup->chunkblockptr;
	chknum=ckgroup->groupsize;

	parblockptr=ckgroup->chunkblockptr;
	parnum=pargroup->groupsize;

	if(w!=8&&w!=16&&w!=32)
	{
		show_error("matrix","encode","number w is illegal");
		return FALSE;
	}
	if(rows<parnum)
	{
		//�������Խ��г˷�
		show_error("matrix","encode","rows is not enough");
		return FALSE;
	}

	dotin=matrix_DOTINF_create_NULL();//����һ��dotinf
	curdatablockptr=datablockptr;
	curparablockptr=parblockptr;
	for(i=0;i<parnum;i++)
	{
		parchunkptr=curparablockptr->chunkptr;
		matrix_DOTINF_set_data(&dotin,NULL,i,chknum,NOSIZE,TRUE);
		resTF=matrix_matrix_dotprod_BLOCK(matrix,ckgroup,parchunkptr,&dotin);
		if(resTF==FALSE)
		{
			show_error("matrix","matrix_encode_BLOCK","Dot product can't run");
			return FALSE;
		}
		curparablockptr++;
	}
	return TRUE;
}
//ʹ��bit����б���
int matrix_bitmatrix_encode(CHUNKGROUP *pargroup,CHUNKGROUP *ckgroup,BITMATRIX *matrix,int packetsize)
{
	//����bitmatrix���б���
	int i,rows,cols,w,chknum,parnum,size;
	CHUNK *chklist,*parlist;
	UINT32 *mat;
	DOTINF dotin;

	parlist=pargroup->ckgroup;
	parnum=pargroup->groupsize;

	chklist=ckgroup->ckgroup;
	chknum=ckgroup->groupsize;

	size=chklist->sizenum;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;
	//��ʼ�����黷��
	if(chklist==NULL)
	{
		show_error("matrix","bitmatrix_encode","chklist==NULL");
		return FALSE;
	}
	if(packetsize%sizeof(UINT32)!=0)
	{
		//Ϊ�˱�֤���������Թ涨32λ������
		show_error("matrix","bitmatrix_encode","the packetsize should be 32x");
		return FALSE;
	}
	if(size%(packetsize*w)!=0)
	{
		show_error("matrix","bitmatrix_encode","size%(packetsize*w)!=0");
		return FALSE;
	}
	if(parlist!=NULL)//�ռ䲻Ҫ
	{
		free(parlist);
	}
	parlist=talloc(CHUNK,parnum);
	if(parlist==NULL)
	{
		show_error("matrix","bitmatrix_encode","No memory");
		return FALSE;
	}
	//���Կ�ʼ������
	for(i=0;i<parnum;i++)
	{
		matrix_DOTINF_set_data(&dotin,NULL,i,chknum,packetsize,TRUE);
		matrix_bitmatrix_dotprod(matrix,ckgroup,parlist,&dotin);
		parlist++;
	}
	return TRUE;
}
//ʹ��schedule���б���
int matrix_schedule_encode(CHUNKGROUP *pargroup,CHUNKGROUP *ckgroup,SCHEDULE *sched,int packetsize)
{
	//ʵ��schedule����
	
	int i,schsize,w,chknum,parnum,size;
	CHUNK *chklist,*parlist;
	SCHEDOP *schopp;

	//��ȡ����
	parlist=pargroup->ckgroup;
	parnum=pargroup->groupsize;

	chklist=ckgroup->ckgroup;
	chknum=ckgroup->groupsize;

	size=chklist->sizenum;//������С

	schsize=sched->size;
	w=sched->w;
	schopp=sched->schedlist;

	//��ʼ���
	if(chklist==NULL)
	{
		show_error("matrix","SCHEDULE_encode","chklist==NULL");
		return TRUE;
	}
	if(packetsize%sizeof(UINT32)!=0)
	{
		//Ϊ�˱�֤���������Թ涨32λ������
		show_error("matrix","SCHEDULE_encode","the packetsize should be 32x");
		return FALSE;
	}
	if(size%(packetsize*w)!=0)
	{
		show_error("matrix","SCHEDULE_encodee","size%(packetsize*w)!=0");
		return FALSE;
	}
	if(parlist!=NULL)//�ռ䲻Ҫ
	{
		free(parlist);
	}
	parlist=talloc(CHUNK,parnum);
	if(parlist==NULL)
	{
		show_error("matrix","bitmatrix_encode","No memory");
		return FALSE;
	}
	//
	return TRUE;
}

int matrix_matrix_firstchunk_handle(CHUNK *parityptr,CHUNK *chunkptr,int curvalue,int w)
{
	int resTF;
	if(curvalue==1)
	{
					//������Ҫ���ݸ���
		resTF=matrix_CHUNK_copy_data(parityptr,chunkptr);
		if(resTF==FALSE)
		{
			show_error("matrix","matrix_firstchunk_handle","chunk data can't copy");
			return FALSE;
		}
	}
	else
	{
		switch(w)
		{
		case 8:
			resTF=matrix_CHUNK_w08_multiply_empty_add(parityptr,chunkptr,curvalue);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_firstchunk_handle","data can't calculate in w08");
				return FALSE;
			}
			break;
		case 16:
			resTF=matrix_CHUNK_w16_multiply_empty_add(parityptr,chunkptr,curvalue);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_firstchunk_handle","data can't calculate in w16");
				return FALSE;
			}
			break;
		case 32:
			resTF=matrix_CHUNK_w32_multiply_empty_add(parityptr,chunkptr,curvalue);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_firstchunk_handle","data can't calculate in w32");
				return FALSE;
				}
			break;
		}
				
	}
}
int matrix_matrix_notfirstchunk_handle(CHUNK *parityptr,CHUNK *chunkptr,int curvalue,int w)
{
	int resTF;
	if(curvalue==1)
	{
		//������Ҫ���
		resTF=matrix_CHUNK_add_data(parityptr,chunkptr);
		if(resTF==FALSE)
		{
			show_error("matrix","matrix_notfirstchunk_handle","chunk data can't add");
			return FALSE;
		}
	}
	else
	{
		//��Ҫ���м���
		switch(w)
		{
		case 8:
			resTF=matrix_CHUNK_w08_multiply_add(parityptr,chunkptr,curvalue);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_notfirstchunk_handle","data can't calculate in w08");
				return FALSE;
			}
			break;
		case 16:
			resTF=matrix_CHUNK_w16_multiply_add(parityptr,chunkptr,curvalue);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_notfirstchunk_handle","data can't calculate in w16");
				return FALSE;
			}
			break;
		case 32:
			resTF=matrix_CHUNK_w32_multiply_add(parityptr,chunkptr,curvalue);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_notfirstchunk_handle","data can't calculate in w32");
				return FALSE;
			}
			break;
		}
	}
}

int matrix_bitmatrix_encode_stripsect_RAID6(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr,BITMATRIX *matrix)
{
	int i,j,k,w,rows,cols;
	UINT32 *mat;

	int index,rowsindex,colsindex,curindex,resTF;
	int pisfirst,qisfirst;//����p,q�������Ƿ�����һ��

	BYTE *contentptr;
	int chunksize;

	STRIPSECTBLOCK *datastrsetblockptr,*curdatastrsetblockptr;
	STRIPSECT *strsetptr;
	int strsetnum;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;
	int chunknum;

	CHUNKGROUP *pchunkgroupptr;
	CHUNK *pchunkptr,*curpchunkptr;
	int pchunknum;

	CHUNKGROUP *qchunkgroupptr;
	CHUNK *qchunkptr,*curqchunkptr;
	int qchunknum;

	//BYTE *contentptr;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	datastrsetblockptr=strsetblockgroupptr->stripsectblockptr;
	strsetnum=strsetblockgroupptr->groupsize;

	pchunkgroupptr=pparityptr->chunklist;
	pchunkptr=pchunkgroupptr->ckgroup;
	pchunknum=pchunkgroupptr->groupsize;

	pisfirst=TRUE;
	/*pisfirst=talloc(int,pchunknum);
	if(pisfirst==NULL)
	{
		show_error("matrix","bitmatrix_encode_stripsect","No memory");
		return FALSE;
	}
	for(i=0;i<pchunknum;i++)
	{
		pisfirst[i]=TRUE;
	}*/

	qchunkgroupptr=qparityptr->chunklist;
	qchunkptr=qchunkgroupptr->ckgroup;
	qchunknum=qchunkgroupptr->groupsize;

	qisfirst=TRUE;
	/*qisfirst=talloc(int,qchunknum);
	if(qisfirst==NULL)
	{
		show_error("matrix","bitmatrix_encode_stripsect","No memory");
		return FALSE;
	}
	for(i=0;i<qchunknum;i++)
	{
		qisfirst[i]=TRUE;
	}*/
	//curpchunkptr=pchunkptr;
	//curqchunkptr=qchunkptr;
	
	curdatastrsetblockptr=datastrsetblockptr;
	curpchunkptr=pchunkptr;//�����ݶ�λ����Ӧλ��
	curqchunkptr=qchunkptr;
	for(i=0;i<(rows/2);i++)//ÿһ������rows/2�У���w��,ÿһ�м���һ��p chunk��һ��q chunk
	{
		curdatastrsetblockptr=datastrsetblockptr;//��ָ����ص�һ��
		//����һ��
		for(j=0;j<strsetnum;j++)//��ǰ���ڶ��ٸ�stripnum
		{
			strsetptr=curdatastrsetblockptr->stripsectptr;
			chunkgroupptr=strsetptr->chunklist;

			chunkptr=chunkgroupptr->ckgroup;
			chunknum=chunkgroupptr->groupsize;

			curchunkptr=chunkptr;
		

		
			for(k=0;k<chunknum;k++)
			{
				
				/*resTF=profile_chunk_data_isfree(curchunkptr);
				if(resTF==TRUE)//����ǿյ�
				{
					resTF=profile_chunk_data_haswrited(curchunkptr);
					if(resTF==TRUE)//д�����Զ���
					{
						resTF=FILELAYER_CHUNK_READER_DATA(chunkptr);
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_encode_stripsect","chunk data can't read");
							return FALSE;
						}
					}
					else
					{
						chunksize=curchunkptr->sizenum;
						contentptr=talloc(BYTE,chunksize);
						if(contentptr==NULL)
						{
							show_error("matrix","bitmatrix_encode_stripsect","No memory");
							return FALSE;
						}
						curchunkptr->chunkcontent=contentptr;
					}
				}*/
				contentptr=curpchunkptr->chunkcontent;//��ֹ��ָ��
				chunksize=curpchunkptr->sizenum;
				if(contentptr==NULL)
				{
					contentptr=talloc(BYTE,chunksize);
					if(contentptr==NULL)
					{
						show_error("matrix","bitmatrix_encode_stripsect","No memory");
						return FALSE;
					}
					curpchunkptr->chunkcontent=contentptr;
				}

				//��λ��ǰ����λ��
				//q��
				index=0;
				rowsindex=i*cols;
				colsindex=j*w;
				curindex=index+rowsindex+colsindex+k;

			
				resTF=mat[curindex];
				if(resTF==TRUE)//˵����ǰλ��
				{
					//������ݵ�ǰ�����ݲ����ڴ�ͬ��
					resTF=profile_chunk_data_read(curchunkptr);
					if(resTF==FALSE)
					{
						show_error("matrix","bitmatrix_encode_stripsect","chunk data can't read");
						return FALSE;
					}
					//���ڵ�ǰ���ݽ���
					if(pisfirst==TRUE)
					{
						resTF=matrix_CHUNK_copy_data(curpchunkptr,curchunkptr);//�����ݿ���
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_encode_stripsect","p parity can't copy");
							return FALSE;
						}
						pisfirst=FALSE;//��ʼ����������
					}
					else
					{
						resTF=matrix_CHUNK_add_data(curpchunkptr,curchunkptr);//�������ۼ�
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_encode_stripsect","p parity can't calculate");
							return FALSE;
						}
					}
				}
				//Q��
				contentptr=curqchunkptr->chunkcontent;//��ֹ��ָ��
				chunksize=curqchunkptr->sizenum;
				if(contentptr==NULL)
				{
					contentptr=talloc(BYTE,chunksize);
					if(contentptr==NULL)
					{
						show_error("matrix","bitmatrix_encode_stripsect","No memory");
						return FALSE;
					}
					curqchunkptr->chunkcontent=contentptr;
				}
				//��λ�����λ��
				index=w*cols;
				rowsindex=i*cols;
				colsindex=j*w;
				curindex=index+rowsindex+colsindex+k;

				resTF=mat[curindex];
				
				if(resTF==TRUE)//˵����ǰλ��
				{
					//������ݵ�ǰ�����ݲ����ڴ�ͬ��
					resTF=profile_chunk_data_read(curchunkptr);
					if(resTF==FALSE)
					{
						show_error("matrix","bitmatrix_encode_stripsect","chunk data can't read");
						return FALSE;
					}
					if(qisfirst==TRUE)
					{
						resTF=matrix_CHUNK_copy_data(curqchunkptr,curchunkptr);//�����ݿ���
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_encode_stripsect","q parity can't copy");
							return FALSE;
						}
						qisfirst=FALSE;
					}
					else
					{
						resTF=matrix_CHUNK_add_data(curqchunkptr,curchunkptr);//�������ۼ�
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_encode_stripsect","q parity can't calculate");
							return FALSE;
						}
					}
				}

				
				curchunkptr++;
			}

			curdatastrsetblockptr++;
		}
		curpchunkptr++;
		curqchunkptr++;
	}
	return TRUE;
}
int matrix_matrix_encode_stripsect_RAID6(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr,INTMATRIX *matrix)
{
	int i,j,w,rows,cols;
	UINT32 *mat;

	int index,rowsindex,colsindex,curindex,resTF,pisfirst,qisfirst,curvalue; 

	BYTE *contentptr;
	int chunksize;

	STRIPSECTBLOCK *datastrsetblockptr,*curdatastrsetblockptr;
	STRIPSECT *strsetptr;
	int strsetnum;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;
	int chunknum;

	CHUNKGROUP *pchunkgroupptr;
	CHUNK *pchunkptr,*curpchunkptr;
	int pchunknum;

	CHUNKGROUP *qchunkgroupptr;
	CHUNK *qchunkptr,*curqchunkptr;
	int qchunknum;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	if((w!=8)&&(w!=16)&&(w!=32))
	{
		show_error("matrix","matrix_encode_stripsect","w should be 8,16,32");
		return FALSE;
	}

	datastrsetblockptr=strsetblockgroupptr->stripsectblockptr;
	strsetnum=strsetblockgroupptr->groupsize;

	pchunkgroupptr=pparityptr->chunklist;
	pchunkptr=pchunkgroupptr->ckgroup;
	curpchunkptr=pchunkptr;
	pchunknum=pchunkgroupptr->groupsize;

	qchunkgroupptr=qparityptr->chunklist;
	qchunkptr=qchunkgroupptr->ckgroup;
	curpchunkptr=qchunkptr;
	qchunknum=qchunkgroupptr->groupsize;

	//curpchunkptr=pchunkptr;
	//curqchunkptr=qchunkptr;

	curdatastrsetblockptr=datastrsetblockptr;

	//��ʼ����
	pisfirst=TRUE;
	qisfirst=TRUE;
	for(i=0;i<strsetnum;i++)
	{
		strsetptr=curdatastrsetblockptr->stripsectptr;
		//��������
		chunkgroupptr=strsetptr->chunklist;
		chunkptr=chunkgroupptr->ckgroup;

		curchunkptr=chunkptr;
		//�����ڴ�ͬ��һ��ʼ��ͬ��ԭ������RS�ͱ����֤�����Ϊ0���������
		resTF=profile_chunk_data_read(curchunkptr);
		if(resTF==FALSE)
		{
			show_error("matrix","matrix_encode_stripsect","chunk data can't read");
			return FALSE;
		}
		index=0;
		curindex=index+i;
		curvalue=mat[curindex];
		if(curvalue!=0)//�����ǰ��Ҫ���м���
		{
			resTF=profile_chunk_data_read(curchunkptr);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_encode_stripsect","chunk data can't read");
				return FALSE;
			}
			//����P��
			if(pisfirst==TRUE)
			{
				//�����һ��
				resTF=matrix_matrix_firstchunk_handle(curpchunkptr,curchunkptr,curvalue,w);
				if(resTF==FALSE)
				{
					show_error("matrix","matrix_encode_stripsect","first chunk data can't calculate");
					return FALSE;
				}
				pisfirst=FALSE;
			}
			else
			{
				//˵���Ѿ����ǵ�һ��
				//curvalue=mat[curindex];
				resTF=matrix_matrix_notfirstchunk_handle(curpchunkptr,curchunkptr,curvalue,w);
				if(resTF==FALSE)
				{
					show_error("matrix","matrix_encode_stripsect","chunk data can't calculate");
					return FALSE;
				}

			}
		}
		//����Q��
		index=cols;//
		curindex=index+i;//��λ����ǰ��
		curvalue=mat[curindex];
		if(curvalue!=0)//�����ǰ��Ҫ���м���
		{
			resTF=profile_chunk_data_read(curchunkptr);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_encode_stripsect","chunk data can't read");
				return FALSE;
			}
			if(qisfirst==TRUE)
			{
				resTF=matrix_matrix_firstchunk_handle(curqchunkptr,curchunkptr,curvalue,w);
				if(resTF==FALSE)
				{
					show_error("matrix","matrix_encode_stripsect","first chunk data can't calculate");
					return FALSE;
				}																																									//�����һ��
			
			/*if(curvalue==1)�������Ϊ�������ٴ�����
			{
				//������Ҫ���ݸ���
				resTF=matrix_CHUNK_copy_data(curqchunkptr,curchunkptr);
				if(resTF==FALSE)
				{
					show_error("matrix","matrix_encode_stripsect","chunk data can't copy");
					return FALSE;
				}
			}
			else
			{
				switch(w)
				{
				case 8:
					resTF=matrix_CHUNK_w08_multiply_empty_add(curqchunkptr,curchunkptr,curvalue);
					if(resTF==FALSE)
					{
						show_error("matrix","matrix_encode_stripsect","data can't calculate in w08");
						return FALSE;
					}
					break;
				case 16:
					resTF=matrix_CHUNK_w16_multiply_empty_add(curqchunkptr,curchunkptr,curvalue);
					if(resTF==FALSE)
					{
						show_error("matrix","matrix_encode_stripsect","data can't calculate in w16");
						return FALSE;
					}
					break;
				case 32:
					resTF=matrix_CHUNK_w32_multiply_empty_add(curqchunkptr,curchunkptr,curvalue);
					if(resTF==FALSE)
					{
						show_error("matrix","matrix_encode_stripsect","data can't calculate in w32");
						return FALSE;
					}
					break;
				}
			}*/
				qisfirst=FALSE;
			}
			else
			{
				resTF=matrix_matrix_notfirstchunk_handle(curpchunkptr,curchunkptr,curvalue,w);
				if(resTF==FALSE)
				{
					show_error("matrix","matrix_encode_stripsect","chunk data can't calculate");
					return FALSE;
				}																																										//˵���Ѿ����ǵ�һ��
			//curvalue=mat[curindex];�������Ϊ�������ٴ�����
			/*if(curvalue==1)
			{
				//������Ҫ���
				resTF=matrix_CHUNK_add_data(curqchunkptr,curchunkptr);
				if(resTF==FALSE)
				{
					show_error("matrix","matrix_encode_stripsect","chunk data can't add");
					return FALSE;
				}
			}
			else
			{
				//��Ҫ���м���
				switch(w)
				{
				case 8:
					resTF=matrix_CHUNK_w08_multiply_add(curqchunkptr,curchunkptr,curvalue);
					if(resTF==FALSE)
					{
						show_error("matrix","matrix_encode_stripsect","data can't calculate in w08");
						return FALSE;
					}
					break;
				case 16:
					resTF=matrix_CHUNK_w16_multiply_add(curqchunkptr,curchunkptr,curvalue);
					if(resTF==FALSE)
					{
						show_error("matrix","matrix_encode_stripsect","data can't calculate in w16");
						return FALSE;
					}
					break;
				case 32:
					resTF=matrix_CHUNK_w32_multiply_add(curqchunkptr,curchunkptr,curvalue);
					if(resTF==FALSE)
					{
						show_error("matrix","matrix_encode_stripsect","data can't calculate in w32");
						return FALSE;
					}
					break;
				}
			}*/
			}
		}
		curdatastrsetblockptr++;//��ָ��������
	}
	return TRUE;
}
//һ������㷨�ľ������
int matrix_bitmatrix_encode_strip(STRIP *stripptr,BITMATRIX *matrix)
{
	int i,j,k,l,resTF,isfirst;
	REGION *regionptr;
	CODEPARA *codeparamptr;
	
	CHUNKGROUP *datachunkgroupptr;
	CHUNK *datachunkptr,*curdatachunkptr;
	int datachunknum;

	CHUNKGROUP *codechunkgroupptr;
	CHUNK *codechunkptr,*curcodechunkptr;
	int codechunknum;

	STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,*codestrsetblockgroupptr; 
	STRIPSECTBLOCK *datastrsetblockptr,*curdatastrsetblockptr;
	STRIPSECT *datastrsetptr;

	STRIPSECTBLOCK *codestrsetblockptr,*curcodestrsetblockptr; 
	STRIPSECT *codestrsetptr;

	int datanum,codenum;
	int curindex,strsetindex,chunkindex,colsindex,rowsindex,windex;

	UINT32 *mat;
	int rows,cols,w;

	regionptr=stripptr->regionptr;
	codeparamptr=regionptr->codepara;

	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	//���ռ�
	datastrsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(datastrsetblockgroupptr==NULL)
	{
		show_error("matrix","bitmatrix_encode_strip","No memory");
		return FALSE;
	}
	datastrsetblockptr=talloc(STRIPSECTBLOCK,datanum);
	if(datastrsetblockptr==NULL)
	{
		show_error("matrix","bitmatrix_encode_strip","No memory");
		return FALSE;
	}
	datastrsetblockgroupptr->stripsectblockptr=datastrsetblockptr;
	datastrsetblockgroupptr->groupsize=datanum;

	codestrsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(codestrsetblockgroupptr==NULL)
	{
		show_error("matrix","bitmatrix_encode_strip","No memory");
		return FALSE;
	}
	codestrsetblockptr=talloc(STRIPSECTBLOCK,codenum);
	if(codestrsetblockptr==NULL)
	{
		show_error("matrix","bitmatrix_encode_strip","No memory");
		return FALSE;
	}
	codestrsetblockgroupptr->stripsectblockptr=codestrsetblockptr;
	codestrsetblockgroupptr->groupsize=codenum;
	resTF=profile_strip_into_stripsect_ptr(datastrsetblockgroupptr,codestrsetblockgroupptr,stripptr);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_encode_strip","stripsectblock can't create");
		return FALSE;
	}

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	curcodestrsetblockptr=codestrsetblockptr;
	for(i=0;i<codenum;i++)
	{
		codestrsetptr=curcodestrsetblockptr->stripsectptr;
		codechunkgroupptr=codestrsetptr->chunklist;

		codechunkptr=codechunkgroupptr->ckgroup;
		codechunknum=codechunkgroupptr->groupsize;

		curcodechunkptr=codechunkptr;
		for(j=0;j<codechunknum;j++)
		{
			curdatastrsetblockptr=datastrsetblockptr;
			isfirst=TRUE;
			for(k=0;k<datanum;k++)
			{
				datastrsetptr=curdatastrsetblockptr->stripsectptr;
				datachunkgroupptr=datastrsetptr->chunklist;

				datachunkptr=datachunkgroupptr->ckgroup;
				datachunknum=datachunkgroupptr->groupsize;

				curdatachunkptr=datachunkptr;
				for(l=0;l<datachunknum;l++)
				{
					
					strsetindex=i*cols*w;//����codestripsectλ��
					chunkindex=j*cols;//����codechunk����λ��
					colsindex=strsetindex+chunkindex;
					rowsindex=k*w;
					windex=l;
					curindex=colsindex+rowsindex+windex;
					resTF=mat[curindex];
					if(resTF==TRUE)
					{
						//�����ڴ�ͬ��
						resTF=profile_chunk_data_read(curdatachunkptr);
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_encode_strip","chunk data can't read");
							return FALSE;
						}
						if(isfirst==TRUE)
						{
							resTF=matrix_CHUNK_copy_data(curcodechunkptr,curdatachunkptr);
							if(resTF==FALSE)
							{
								show_error("matrix","bitmatrix_encode_strip","chunk data can't copy");
								return FALSE;
							}
							isfirst=FALSE;
						}
						else
						{
							resTF=matrix_CHUNK_add_data(curcodechunkptr,curdatachunkptr);
							if(resTF==FALSE)
							{
								show_error("matrix","bitmatrix_encode_strip","chunk data can't add");
								return FALSE;
							}
						}
					}
					curdatachunkptr++;
				}
				curdatastrsetblockptr++;
			}
			curcodechunkptr++;
		}

		curcodestrsetblockptr++;
	}

	return TRUE;
}
extern int matrix_matrix_encode_strip(STRIP *stripptr,INTMATRIX *matrix)
{
	int i,j,resTF,isfirst,curvalue;
	REGION *regionptr;
	CODEPARA *codeparamptr;
	
	STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,*codestrsetblockgroupptr; 

	STRIPSECTBLOCK *datastrsetblockptr,*curdatastrsetblockptr;
	STRIPSECT *datastrsetptr;

	STRIPSECTBLOCK *codestrsetblockptr,*curcodestrsetblockptr; 
	STRIPSECT *codestrsetptr;

	CHUNKGROUP *datachunkgroupptr,*codechunkgroupptr;
	CHUNK *datachunkptr,*codechunkptr;

	int datanum,codenum;

	int colsindex,rowsindex,curindex;
	int rows,cols,w;
	UINT32 *mat; 
	regionptr=stripptr->regionptr;
	codeparamptr=regionptr->codepara;

	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	//���ռ�
	datastrsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(datastrsetblockgroupptr==NULL)
	{
		show_error("matrix","matrix_encode_strip","No memory");
		return FALSE;
	}
	datastrsetblockptr=talloc(STRIPSECTBLOCK,datanum);
	if(datastrsetblockptr==NULL)
	{
		show_error("matrix","matrix_encode_strip","No memory");
		return FALSE;
	}
	datastrsetblockgroupptr->stripsectblockptr=datastrsetblockptr;
	datastrsetblockgroupptr->groupsize=datanum;

	codestrsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(codestrsetblockgroupptr==NULL)
	{
		show_error("matrix","matrix_encode_strip","No memory");
		return FALSE;
	}
	codestrsetblockptr=talloc(STRIPSECTBLOCK,codenum);
	if(codestrsetblockptr==NULL)
	{
		show_error("matrix","matrix_encode_strip","No memory");
		return FALSE;
	}
	codestrsetblockgroupptr->stripsectblockptr=codestrsetblockptr;
	codestrsetblockgroupptr->groupsize=codenum;
	resTF=profile_strip_into_stripsect_ptr(datastrsetblockgroupptr,codestrsetblockgroupptr,stripptr);
	if(resTF==FALSE)
	{
		show_error("matrix","matrix_encode_strip","stripsectblock can't create");
		return FALSE;
	}
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;
	curcodestrsetblockptr=codestrsetblockptr;
	for(i=0;i<codenum;i++)
	{
		codestrsetptr=curcodestrsetblockptr->stripsectptr;
		codechunkgroupptr=codestrsetptr->chunklist;
		codechunkptr=codechunkgroupptr->ckgroup;

		curdatastrsetblockptr=datastrsetblockptr;
		isfirst=TRUE;
		for(j=0;j<datanum;j++)
		{
			datastrsetptr=curdatastrsetblockptr->stripsectptr;
			datachunkgroupptr=datastrsetptr->chunklist;
			datachunkptr=datachunkgroupptr->ckgroup;

			rowsindex=i*cols;
			colsindex=j;
			curindex=rowsindex+colsindex;
			resTF=mat[curindex];
			if(curvalue!=0)
			{
				resTF=profile_chunk_data_read(datachunkptr);
				if(resTF==FALSE)
				{
					show_error("matrix","matrix_encode_strip","chunk data can't read");
					return FALSE;
				}
				if(isfirst==TRUE)
				{
					resTF=matrix_matrix_firstchunk_handle(codechunkptr,datachunkptr,curvalue,w);
					if(resTF==FALSE)
					{
						show_error("matrix","matrix_encode_strip","first chunk data can't calculate");
						return FALSE;
					}
				}
				else
				{
					resTF=matrix_matrix_notfirstchunk_handle(codechunkptr,datachunkptr,curvalue,w);
					if(resTF==FALSE)
					{
						show_error("matrix","matrix_encode_strip","first chunk data can't calculate");
						return FALSE;
					}
				}
			}
			curdatastrsetblockptr++;
		}
		curcodestrsetblockptr++;
	}
	return TRUE;
}



//�ҳ���ǰ��Ҫ���и��µ��б�
int matrix_update_bitmatrix_pqparity_chunklist_create(int *pupdatelist,int *qupdatelist,
															CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,BITMATRIX *matrix)
{
	int i,j,curstripsectindex,curchunkindex;
	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	int chunknum;
	int pindex,qindex,pwindex,qwindex,tarpindex,tarqindex,rows,cols,w;
	UINT32 *mat;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	chunknum=chunkpositionblockgroupptr->groupsize;

	//�ҳ��ڱ�������Ҫ���µ�p��q��
	curchunkpositionblockptr=chunkpositionblockptr;//�������еĿ鶼�����ļ��в�����ûд��������
	for(i=0;i<chunknum;i++)
	{
		curstripsectindex=curchunkpositionblockptr->stripsectindex;
		curchunkindex=curchunkpositionblockptr->chunkindex;
		//����ÿһ��У���̵�ǰ��᲻���������
		for(j=0;j<(rows/2);j++)
		{
			//���㵱ǰchunk��Ҫ��PУ���
			pindex=j*cols;
			pwindex=curstripsectindex*w;
			tarpindex=pindex+pwindex+curchunkindex;
			if(mat[tarpindex]==TRUE)//��������λ�õ�������Ҫ����
			{
				//��¼״̬
				pupdatelist[j]=TRUE;
			}


			//���㵱ǰchunk��Ҫ��QУ���
			qindex=w*cols+j*cols;
			qwindex=curstripsectindex*w;
			tarqindex=qindex+qwindex+curchunkindex;
			if(mat[tarqindex]==TRUE)
			{
				//��¼״̬
				qupdatelist[j]=TRUE;
			}
		}
		curchunkpositionblockptr++;
	}
	return TRUE;
}
//�ҳ���ǰ��Ҫ���и��µ��б�
int matrix_update_bitmatrix_pqupdatenum_chunklist_create(int *pupdatelist1,int *pupdatelist2,
															int *qupdatelist1,int *qupdatelist2,
															CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
															STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,
															BITMATRIX *matrix)
{
	int resTF,i,j,k;
	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	int chunknum;

	int pindex,qindex,pwindex,qwindex,tarpindex,tarqindex,rows,cols,w;
	UINT32 *mat;

	STRIPSECTBLOCK *strsetblockptr,*curstrsetblockptr;
	STRIPSECT *strsetptr;
	int strsetnum;

	CHUNKGROUP *pchunkgroupptr;
	CHUNK *pchunkptr,*curpchunkptr;
	int pchunknum;

	CHUNKGROUP *qchunkgroupptr;
	CHUNK *qchunkptr,*curqchunkptr;
	int qchunknum;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr; 

	
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	chunknum=chunkpositionblockgroupptr->groupsize;

	pchunkgroupptr=pparity->chunklist;

	pchunkptr=pchunkgroupptr->ckgroup;
	pchunknum=pchunkgroupptr->groupsize;

	for(i=0;i<w;i++)//���ڵ�ǰУ������ͳ��
	{
		strsetblockptr=strsetblockgroupptr->stripsectblockptr;
		strsetnum=strsetblockgroupptr->groupsize;

		curstrsetblockptr=strsetblockptr;
		//strsetgroupptr=stripptr->stripsectlist;
		//strsetptr=strsetgroupptr->stripsetgroup;
		//strsetnum=strsetgroupptr->groupsize;

		//curstrsetptr=strsetptr;
		for(j=0;j<strsetnum;j++)
		{
			//���������л����chunk��
			strsetptr=curstrsetblockptr->stripsectptr;
			chunkgroupptr=strsetptr->chunklist;

			chunkptr=chunkgroupptr->ckgroup;
			chunknum=chunkgroupptr->groupsize;

			curchunkptr=chunkptr;
			for(k=0;k<chunknum;k++)
			{
				//�������ǰλ���ǲ���Ϊ1
				pindex=i*cols;
				pwindex=j*w;//���㵱ǰwλ��
				tarpindex=pindex+pwindex+k;
				resTF=mat[tarpindex];
				if(resTF==TRUE)//��ǰ��λ����Ҫ����
				{
					resTF=profile_search_chunkposition_id(j,k,chunkpositionblockgroupptr);
					
					if(resTF==PFALSE)
					{
						resTF=profile_chunk_should_read(curchunkptr);
						if(resTF==TRUE)
						{
							pupdatelist1[i]=pupdatelist1[i]+1;
						}
						
					}
					else
					{
						resTF=profile_chunk_should_read(curchunkptr);
						if(resTF==TRUE)
						{
							pupdatelist2[i]=pupdatelist2[i]+1;
						}
					}
				}
				curchunkptr++;
			}
			curstrsetblockptr++;
		}
		pchunkptr++;
	}

	qchunkgroupptr=qparity->chunklist;

	qchunkptr=qchunkgroupptr->ckgroup;
	qchunknum=qchunkgroupptr->groupsize;
	for(i=0;i<w;i++)
	{
		strsetblockptr=strsetblockgroupptr->stripsectblockptr;
		strsetnum=strsetblockgroupptr->groupsize;

		curstrsetblockptr=strsetblockptr;
		//strsetgroupptr=stripptr->stripsectlist;
		//strsetptr=strsetgroupptr->stripsetgroup;
		//strsetnum=strsetgroupptr->groupsize;

		//curstrsetptr=strsetptr;
		//curstrsetptr=strsetptr;
		for(j=0;j<strsetnum;j++)
		{
			//���������л����chunk��
			strsetptr=curstrsetblockptr->stripsectptr;
			chunkgroupptr=strsetptr->chunklist;

			chunkptr=chunkgroupptr->ckgroup;
			chunknum=chunkgroupptr->groupsize;

			curchunkptr=chunkptr;
			for(k=0;k<chunknum;k++)
			{
				qindex=w*cols+i*cols;
				qwindex=j*w;//���㵱ǰwλ��
				tarpindex=qindex+qwindex+k;
				resTF=mat[tarpindex];
				if(resTF==TRUE)
				{
					resTF=profile_search_chunkposition_id(j,k,chunkpositionblockgroupptr);
					if(resTF==PFALSE)
					{
						resTF=profile_chunk_should_read(curchunkptr);
						if(resTF==TRUE)
						{
							qupdatelist1[i]=qupdatelist1[i]+1;
						}
					}
					else
					{
						resTF=profile_chunk_should_read(curchunkptr);
						if(resTF==TRUE)
						{
							qupdatelist2[i]=qupdatelist2[i]+1;
						}
					}
				}
				curchunkptr++;
			}
			curstrsetblockptr++;
		}
		qchunkptr++;
	}
	return TRUE;
}
//����1�������㷨
int matrix_bitmatrix_updateI_chunk_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,
											CHUNK *tarchunkptr,BITMATRIX *matrix,int chkindex)
{
	UINT32 *mat;
	int rows,cols,w,resTF;
	int i,j,index,windex,tarindex,isfirst;

	STRIPSECTBLOCK *strsetblockptr,*curstrsetblockptr;
	STRIPSECT *strsetptr;

	CHUNKBLOCKGROUP *tempchunkblockgroupptr;
	CHUNKBLOCK *tempchunkblockptr;
	
	int tempchunknum;//���ҵ�buff��

	CHUNKBLOCKGROUP *soubuffblockgroup;//Ϊ�˲��л���Ҫ��һ�������ס������Ҫ���л��Ŀ��
	CHUNKBLOCK *soubuffblockptr;
	//int buffnum;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr,*souchunkptr;
	int strsetnum,chunknum,chunksize;

	BYTE *contentptr;


	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	soubuffblockgroup=talloc(CHUNKBLOCKGROUP,1);
	if(soubuffblockgroup==NULL)
	{
		show_error("matrix","bitmatrix_updateI_chunk","No memory");
		return FALSE;
	}

	soubuffblockptr=talloc(CHUNKBLOCK,cols);
	if(soubuffblockptr==NULL)
	{
		show_error("matrix","bitmatrix_updateI_chunk","No memory");
		return FALSE;
	}
	soubuffblockgroup->chunkblockptr=soubuffblockptr;
	soubuffblockgroup->groupsize=0;

	tempchunkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(tempchunkblockgroupptr==NULL)
	{
		show_error("matrix","bitmatrix_updateI_chunk","No memory");
		return FALSE;
	}

	tempchunkblockptr=talloc(CHUNKBLOCK,cols);
	if(tempchunkblockptr==NULL)
	{
		show_error("matrix","bitmatrix_updateI_chunk","No memory");
		return FALSE;
	}
	tempchunkblockgroupptr->chunkblockptr=tempchunkblockptr;
	tempchunkblockgroupptr->groupsize=0;

	chunksize=tarchunkptr->sizenum;//��ȡ��С
	contentptr=tarchunkptr->chunkcontent;
	if(contentptr==NULL)
	{
		//�������¼���ֻ��Ҫ���п��ռ伴��
		contentptr=talloc(BYTE,chunksize);
		if(contentptr==NULL)
		{
			show_error("matrix","bitmatrix_updateI_chunk","No memory");
			return FALSE;
		}
		tarchunkptr->chunkcontent=contentptr;
	}

	index=chkindex*cols;//�ҵ���ǰ��index
	strsetblockptr=strsetblockgroupptr->stripsectblockptr;
	strsetnum=strsetblockgroupptr->groupsize;

	curstrsetblockptr=strsetblockptr;
	isfirst=TRUE;
	for(i=0;i<strsetnum;i++)
	{
		strsetptr=curstrsetblockptr->stripsectptr;

		chunkgroupptr=strsetptr->chunklist;
		chunkptr=chunkgroupptr->ckgroup;
		chunknum=chunkgroupptr->groupsize;

		curchunkptr=chunkptr;
		windex=w*i;

		//ע��Ϊ���л�����
		for(j=0;j<chunknum;j++)
		{
			tarindex=index+windex+j;
			//��ǰ������Ҫ���¼���
			if(mat[tarindex]==TRUE)
			{
				//��������
				souchunkptr=profile_get_chunkposition_ptr(i,j,chunkpositionblockgroupptr);//���ҵ�ǰ�ĸ�����������chunk��
				if(souchunkptr==NULL)//��ǰ������
				{
					souchunkptr=curchunkptr;
					contentptr=souchunkptr->chunkcontent;
					if(contentptr==NULL)
					{
						/*resTF=profile_chunk_data_read(souchunkptr);
						//resTF=FILELAYER_CHUNK_READER_DATA(souchunkptr);
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_updateI_chunk","chunk data can't read");
							return FALSE;
						}*/					
						resTF=profile_chunkblockgroup_chunk_add(tempchunkblockgroupptr,souchunkptr);
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_updateI_chunk","chunkblockgroup can't add chunk");
							return FALSE;
						}
					}
					else
					{
						//����ڲ�ͬ��ֱ�Ӽ��ϼ���
						resTF=profile_chunkblockgroup_chunk_add(soubuffblockgroup,souchunkptr);
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_updateI_chunk","chunkblockgroup can't add chunk");
							return FALSE;
						}
					}
				}
			}
			curchunkptr++;
		}
		curstrsetblockptr++;
	}
	resTF=file_FILELAYER_CHUNKBLOCKGROUP_READER_DATA(tempchunkblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_updateI_chunk","data cannot read");
		return FALSE;
	}
	resTF=profile_XOR_CHUNKBLOCK_CHUNK_DATA(tarchunkptr,tempchunkblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_updateI_chunk","Data cannot calculate");
		return FALSE;
	}
	resTF=profile_XOR_CHUNKBLOCK_CHUNK_DATA_XOR(tarchunkptr,soubuffblockgroup);//֮ǰ�������������Ҫ��һ�������
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_updateI_chunk","Data cannot calculate");
		return FALSE;
	}
				/*if(isfirst==TRUE)
				{
					resTF=matrix_CHUNK_copy_data(tarchunkptr,souchunkptr);
					if(resTF==FALSE)
					{
						show_error(,"chunk data can't copy");
						return FALSE;
					}
				}
				else
				{
					resTF=matrix_CHUNK_add_data(tarchunkptr,souchunkptr);
					if(resTF==FALSE)
					{
						show_error("matrix","bitmatrix_updateI_chunk","chunk data can't add");
						return FALSE;
					}
				}
				*/
			
	//resTF=profile_free_chunkblockgroup_data(tempchunkblockgroupptr);
	resTF=profile_tempfree_chunkblock_ptr(tempchunkblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_updateI_chunk","chunk data can't free");
		return FALSE;
	}
	free(soubuffblockgroup);
	free(soubuffblockptr);
	free(tempchunkblockgroupptr);
	free(tempchunkblockptr);
	return TRUE;
}


//����2��ʹ�õ�ǰ��У�������
int matrix_bitmatrix_updateII_chunk_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,
											CHUNK *tarchunkptr,BITMATRIX *matrix,int chkindex)
{
	UINT32 *mat;
	int i,j,rows,cols,w,resTF;
	int tarindex,index,windex;

	STRIPSECTBLOCK *strsetblockptr,*curstrsetblockptr;
	STRIPSECT *strsetptr;
	int strsetnum;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr,*souchunkptr;
	int chunknum;

	CHUNKBLOCKGROUP *soubuffblkgroup;
	CHUNKBLOCK *soubuffblkptr;
	
	int buffnum;

	CHUNKBLOCKGROUP *tempchunkblockgroupptr;
	CHUNKBLOCK *tempchunkblockptr;
	int tempchunknum;

	BYTE *contentptr;

	int isfirst;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	soubuffblkgroup=talloc(CHUNKBLOCKGROUP,1);
	if(soubuffblkgroup==NULL)
	{
		show_error("matrix","bitmatrix_updateII_chunk","No memory");
		return FALSE;
	}

	soubuffblkptr=talloc(CHUNKBLOCK,cols);
	if(soubuffblkptr==NULL)
	{
		show_error("matrix","bitmatrix_updateII_chunk","No memory");
		return FALSE;
	}
	soubuffblkgroup->chunkblockptr=soubuffblkptr;
	soubuffblkgroup->groupsize=0;

	tempchunkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(tempchunkblockgroupptr==NULL)
	{
		show_error("matrix","bitmatrix_updateII_chunk","No memory");
		return FALSE;
	}
	tempchunkblockptr=talloc(CHUNKBLOCK,cols);
	if(tempchunkblockptr==NULL)
	{
		show_error("matrix","bitmatrix_updateII_chunk","No memory");
		return FALSE;
	}
	tempchunkblockgroupptr->chunkblockptr=tempchunkblockptr;
	tempchunkblockgroupptr->groupsize=0;

	//��ʼ��⵱ǰ�����ݵ�Ŀ��У����ڲ����ڴ�
	contentptr=tarchunkptr->chunkcontent;
	if(contentptr==NULL)
	{
		resTF=profile_chunk_data_read(tarchunkptr);//�����ݶ����ڴ�
		//resTF=FILELAYER_CHUNK_READER_DATA(tarchunkptr);//�����ݶ����ڴ�
		if(resTF==FALSE)
		{
			show_error("matrix","bitmatrix_updateII_chunk_RAID6","chunk data can't read");
			return FALSE;
		}
		//����Ŀ������Ҫд�����ݲ������ͷ�
	}

	strsetblockptr=strsetblockgroupptr->stripsectblockptr;
	strsetnum=strsetblockgroupptr->groupsize;

	curstrsetblockptr=strsetblockptr;

	index=chkindex*cols;
	for(i=0;i<strsetnum;i++)
	{
		windex=i*w;
		strsetptr=curstrsetblockptr->stripsectptr;

		chunkgroupptr=strsetptr->chunklist;
		chunkptr=chunkgroupptr->ckgroup;
		chunknum=chunkgroupptr->groupsize;

		curchunkptr=chunkptr;
		//ע��Ϊ���д���
		for(j=0;j<chunknum;j++)
		{
			//�����ȼ��㵱ǰ�ǲ�����Ҫ����
			tarindex=index+windex+j;
			if(mat[tarindex]==TRUE)//��·����
			{
				souchunkptr=profile_get_chunkposition_ptr(i,j,chunkpositionblockgroupptr);
				if(souchunkptr!=NULL)//��Ȼ���������
				{
					//��ǰ��������Ҫ����
					contentptr=curchunkptr->chunkcontent;
					if(contentptr==NULL)
					{
						//��ǰ����˵�������ڴ�
						resTF=profile_chunkblockgroup_chunk_add(soubuffblkgroup,souchunkptr);
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_updateII_chunk_RAID6","chunkblockgroup can't add chunk");
							return FALSE;
						}
						//resTF=FILELAYER_CHUNK_READER_DATA(curchunkptr);
						/*resTF=profile_chunk_data_read(curchunkptr);
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_updateII_chunk_RAID6","chunk data can't read");
							return FALSE;
						}*/
						resTF=profile_chunkblockgroup_chunk_add(tempchunkblockgroupptr,curchunkptr);
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_updateII_chunk_RAID6","chunkblockgroup can't add chunk");
							return FALSE;
						}
					}
					
					/*//�����ݽ������
					resTF=matrix_CHUNK_add_data(tarchunkptr,curchunkptr);
					if(resTF==FALSE)
					{
						show_error("matrix","bitmatrix_updateII_chunk_RAID6","chunk data can't add");
						return FALSE;
					}
					resTF=matrix_CHUNK_add_data(tarchunkptr,souchunkptr);
					if(resTF==FALSE)
					{
						show_error("matrix","bitmatrix_updateII_chunk_RAID6","chunk data can't add");
						return FALSE;
					}*/
				}
			}
			
			curchunkptr++;
		}
		strsetblockptr++;
	}
	//��ȡ����
	resTF=file_FILELAYER_CHUNKBLOCKGROUP_READER_DATA(tempchunkblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_updateII_chunk_RAID6","data cannot read");
		return FALSE;
	}

	resTF=profile_XOR_CHUNKBLOCK_CHUNK_DATA_XOR(tarchunkptr,tempchunkblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_updateII_chunk_RAID6","data cannot calaulate");
		return FALSE;
	}

	resTF=profile_XOR_CHUNKBLOCK_CHUNK_DATA_XOR(tarchunkptr,soubuffblkgroup);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_updateII_chunk_RAID6","data cannot calaulate");
		return FALSE;
	}
	//resTF=profile_free_chunkblockgroup_data(tempchunkblockgroupptr);
	resTF=profile_tempfree_chunkblock_ptr(tempchunkblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_updateII_chunk_RAID6","chunk data can't free");
		return FALSE;
	}
	free(tempchunkblockgroupptr);
	free(tempchunkblockptr);
	return TRUE;
}

int matrix_bitmatrix_updateI_stripsect_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,
											CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix)
{
	int i,j,k,resTF,curstripsectindex,curchunkindex;

	int pindex,qindex,pwindex,qwindex,tarpindex,tarqindex,rows,cols,w;
	UINT32 *mat;

	

	//STRIPSECTGROUP *strsetgroupptr;
	//STRIPSECT *strsetptr,*curstrsetptr;
	//int strsetnum;
	
	CHUNKGROUP *pchunkgroupptr;
	CHUNK *pchunkptr,*curpchunkptr;
	int pchunknum;

	CHUNKGROUP *qchunkgroupptr;
	CHUNK *qchunkptr,*curqchunkptr;
	int qchunknum;
	
	
	//����1�������㷨������2��ʹ�õ�ǰ��У�������
	int *pupdatelist1,*pupdatelist2;
	int *qupdatelist1,*qupdatelist2;
	int *pupdatelist,*qupdatelist;


	BYTE *contentptr;
	//float poccupyrate,qoccupyrate;
	
	//��ȡ��������
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	//��ȡp��q���б�
	pchunkgroupptr=pparity->chunklist;
	pchunkptr=pchunkgroupptr->ckgroup;
	pchunknum=pchunkgroupptr->groupsize;

	pupdatelist=talloc(int,pchunknum);
	if(pupdatelist==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist,int,pchunknum);//��������0�������еĶ���FALSE

	pupdatelist1=talloc(int,pchunknum);
	if(pupdatelist1==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist1,int,pchunknum);//��������0�������еĶ���FALSE

	pupdatelist2=talloc(int,pchunknum);
	if(pupdatelist2==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist2,int,pchunknum);//��0


	qchunkgroupptr=qparity->chunklist;
	qchunkptr=qchunkgroupptr->ckgroup;
	qchunknum=qchunkgroupptr->groupsize;

	qupdatelist=talloc(int,qchunknum);
	if(qupdatelist==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist,int,qchunknum);//��������0�������еĶ���FALSE

	qupdatelist1=talloc(int,qchunknum);
	if(qupdatelist1==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist1,int,qchunknum);//��������0�������еĶ���FALSE

	qupdatelist2=talloc(int,qchunknum);
	if(qupdatelist2==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist2,int,qchunknum);//��0
	//������Ҫ���µ�У���
	resTF=matrix_update_bitmatrix_pqparity_chunklist_create(pupdatelist,qupdatelist,
													chunkpositionblockgroupptr,matrix);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_update_stripsect","parity chunklist can't create");
		return FALSE;
	}
	resTF=matrix_update_bitmatrix_pqupdatenum_chunklist_create(pupdatelist1,pupdatelist2,
																qupdatelist1,qupdatelist2,
																chunkpositionblockgroupptr,
																strsetblockgroupptr,pparity,qparity,
																matrix);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_update_stripsect","parity count list can't create");
		return FALSE;
	}
	//
	/*for(i=0;i<rows;i++)
	{
		pindex=i*cols;
		qindex=w*cols+i*cols;
		for(j=0;j<cols/w;j++)
		{
			for(k=0;k<w;k++)
			{
				tarpindex=pindex+j;
				tarqindex=qindex+j;
				prowsonenum[i]=prowsonenum[i]+mat[tarpindex];
				qrowsonenum[i]=qrowsonenum[i]+mat[tarqindex];
			}
		}
	}*/
	

	

	//�����Ѿ�֪������Ҫ���µĿ����ڿ��Լ�����
	curpchunkptr=pchunkptr;
	curqchunkptr=qchunkptr;
	for(i=0;i<(rows/2);i++)
	{
		//����P��
		if(pupdatelist[i]!=FALSE)//��ǰ�Ŀ���Ҫ�����㷨
		{
			//��һ�����жϵ���У����ڲ����ڴ�
			//poccupyrate=pupdatelist[j]/prowsonenum[i];
			resTF=profile_chunkblockgroup_chunk_add(parityblockgroupptr,curpchunkptr);
			if(resTF==FALSE)
			{
				show_error("matrix","bitmatrix_update_stripsect","chunk data can't add to parity list");
				return FALSE;
			}
			contentptr=curpchunkptr->chunkcontent;
			//if(contentptr==NULL)
			//{
				
				resTF=matrix_bitmatrix_updateI_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
																curpchunkptr,matrix,i);
				if(resTF==FALSE)
				{
					show_error("matrix","bitmatrix_update_stripsect","parity data can't update");
					return FALSE;
				}
				
			//}
			resTF=matrix_update_bitmatrix_pqupdatenum_chunklist_create(pupdatelist1,pupdatelist2,
																qupdatelist1,qupdatelist2,
																chunkpositionblockgroupptr,
																strsetblockgroupptr,pparity,qparity,
																matrix);
			if(resTF==FALSE)
			{
				show_error("matrix","bitmatrix_update_stripsect","parity count list can't create");
				return FALSE;
			}
		}
		//����Q��
		if(qupdatelist[i]!=FALSE)
		{
			//��һ�����жϵ���У����ڲ����ڴ�
			//��һ�����жϵ���У����ڲ����ڴ�
			//qoccupyrate=qdatelist[j]/qrowsonenum[i];
			resTF=profile_chunkblockgroup_chunk_add(parityblockgroupptr,curqchunkptr);
			if(resTF==FALSE)
			{
				show_error("matrix","bitmatrix_update_stripsect","chunk data can't add to parity list");
				return FALSE;
			}
			contentptr=curqchunkptr->chunkcontent;
			//if(contentptr==NULL)
			//{
				resTF=matrix_bitmatrix_updateI_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
																curqchunkptr,matrix,i+w);
				if(resTF==FALSE)
				{
					show_error("matrix","bitmatrix_update_stripsect","parity data can't update");
					return FALSE;
				}
				
			//}
			resTF=matrix_update_bitmatrix_pqupdatenum_chunklist_create(pupdatelist1,pupdatelist2,
																qupdatelist1,qupdatelist2,
																chunkpositionblockgroupptr,
																strsetblockgroupptr,pparity,qparity,
																matrix);
			if(resTF==FALSE)
			{
				show_error("matrix","bitmatrix_update_stripsect","parity count list can't create");
				return FALSE;
			}

		}
		curpchunkptr++;
		curqchunkptr++;
	}
	free(pupdatelist);
	free(pupdatelist1);
	free(pupdatelist2);

	free(qupdatelist);
	free(qupdatelist1);
	free(qupdatelist2);
	return TRUE;
}
int matrix_bitmatrix_updateII_stripsect_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,
											CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix)
{
	int i,j,k,resTF,curstripsectindex,curchunkindex;

	int pindex,qindex,pwindex,qwindex,tarpindex,tarqindex,rows,cols,w;
	UINT32 *mat;

	

	//STRIPSECTGROUP *strsetgroupptr;
	//STRIPSECT *strsetptr,*curstrsetptr;
	//int strsetnum;
	
	CHUNKGROUP *pchunkgroupptr;
	CHUNK *pchunkptr,*curpchunkptr;
	int pchunknum;

	CHUNKGROUP *qchunkgroupptr;
	CHUNK *qchunkptr,*curqchunkptr;
	int qchunknum;
	
	
	//����1�������㷨������2��ʹ�õ�ǰ��У�������
	int *pupdatelist1,*pupdatelist2;
	int *qupdatelist1,*qupdatelist2;
	int *pupdatelist,*qupdatelist;


	BYTE *contentptr;
	//float poccupyrate,qoccupyrate;
	
	//��ȡ��������
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	//��ȡp��q���б�
	pchunkgroupptr=pparity->chunklist;
	pchunkptr=pchunkgroupptr->ckgroup;
	pchunknum=pchunkgroupptr->groupsize;

	pupdatelist=talloc(int,pchunknum);
	if(pupdatelist==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist,int,pchunknum);//��������0�������еĶ���FALSE

	pupdatelist1=talloc(int,pchunknum);
	if(pupdatelist1==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist1,int,pchunknum);//��������0�������еĶ���FALSE

	pupdatelist2=talloc(int,pchunknum);
	if(pupdatelist2==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist2,int,pchunknum);//��0


	qchunkgroupptr=qparity->chunklist;
	qchunkptr=qchunkgroupptr->ckgroup;
	qchunknum=qchunkgroupptr->groupsize;

	qupdatelist=talloc(int,qchunknum);
	if(qupdatelist==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist,int,qchunknum);//��������0�������еĶ���FALSE

	qupdatelist1=talloc(int,qchunknum);
	if(qupdatelist1==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist1,int,qchunknum);//��������0�������еĶ���FALSE

	qupdatelist2=talloc(int,qchunknum);
	if(qupdatelist2==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist2,int,qchunknum);//��0
	//������Ҫ���µ�У���
	resTF=matrix_update_bitmatrix_pqparity_chunklist_create(pupdatelist,qupdatelist,
													chunkpositionblockgroupptr,matrix);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_update_stripsect","parity chunklist can't create");
		return FALSE;
	}
	resTF=matrix_update_bitmatrix_pqupdatenum_chunklist_create(pupdatelist1,pupdatelist2,
																qupdatelist1,qupdatelist2,
																chunkpositionblockgroupptr,
																strsetblockgroupptr,pparity,qparity,
																matrix);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_update_stripsect","parity count list can't create");
		return FALSE;
	}
	//
	/*for(i=0;i<rows;i++)
	{
		pindex=i*cols;
		qindex=w*cols+i*cols;
		for(j=0;j<cols/w;j++)
		{
			for(k=0;k<w;k++)
			{
				tarpindex=pindex+j;
				tarqindex=qindex+j;
				prowsonenum[i]=prowsonenum[i]+mat[tarpindex];
				qrowsonenum[i]=qrowsonenum[i]+mat[tarqindex];
			}
		}
	}*/
	

	

	//�����Ѿ�֪������Ҫ���µĿ����ڿ��Լ�����
	curpchunkptr=pchunkptr;
	curqchunkptr=qchunkptr;
	for(i=0;i<(rows/2);i++)
	{
		//����P��
		if(pupdatelist[i]!=FALSE)//��ǰ�Ŀ���Ҫ�����㷨
		{
			//��һ�����жϵ���У����ڲ����ڴ�
			//poccupyrate=pupdatelist[j]/prowsonenum[i];
			resTF=profile_chunkblockgroup_chunk_add(parityblockgroupptr,curpchunkptr);
			if(resTF==FALSE)
			{
				show_error("matrix","bitmatrix_update_stripsect","chunk data can't add to parity list");
				return FALSE;
			}
			contentptr=curpchunkptr->chunkcontent;
			//if(contentptr==NULL)
			//{
				
				resTF=matrix_bitmatrix_updateII_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
																curpchunkptr,matrix,i);
				if(resTF==FALSE)
				{
					show_error("matrix","bitmatrix_update_stripsect","parity data can't update");
					return FALSE;
				}
				
			//}
			resTF=matrix_update_bitmatrix_pqupdatenum_chunklist_create(pupdatelist1,pupdatelist2,
																qupdatelist1,qupdatelist2,
																chunkpositionblockgroupptr,
																strsetblockgroupptr,pparity,qparity,
																matrix);
			if(resTF==FALSE)
			{
				show_error("matrix","bitmatrix_update_stripsect","parity count list can't create");
				return FALSE;
			}
		}
		//����Q��
		if(qupdatelist[i]!=FALSE)
		{
			//��һ�����жϵ���У����ڲ����ڴ�
			//��һ�����жϵ���У����ڲ����ڴ�
			//qoccupyrate=qdatelist[j]/qrowsonenum[i];
			resTF=profile_chunkblockgroup_chunk_add(parityblockgroupptr,curqchunkptr);
			if(resTF==FALSE)
			{
				show_error("matrix","bitmatrix_update_stripsect","chunk data can't add to parity list");
				return FALSE;
			}
			contentptr=curqchunkptr->chunkcontent;
			//if(contentptr==NULL)
			//{
				resTF=matrix_bitmatrix_updateII_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
																curqchunkptr,matrix,i+w);
				if(resTF==FALSE)
				{
					show_error("matrix","bitmatrix_update_stripsect","parity data can't update");
					return FALSE;
				}
				
			//}
			resTF=matrix_update_bitmatrix_pqupdatenum_chunklist_create(pupdatelist1,pupdatelist2,
																qupdatelist1,qupdatelist2,
																chunkpositionblockgroupptr,
																strsetblockgroupptr,pparity,qparity,
																matrix);
			if(resTF==FALSE)
			{
				show_error("matrix","bitmatrix_update_stripsect","parity count list can't create");
				return FALSE;
			}

		}
		curpchunkptr++;
		curqchunkptr++;
	}
	free(pupdatelist);
	free(pupdatelist1);
	free(pupdatelist2);

	free(qupdatelist);
	free(qupdatelist1);
	free(qupdatelist2);
	return TRUE;
}
//��ǰchunkblockgroup�е�������Ҫ��һ��strip��
int matrix_bitmatrix_update_stripsect_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,
											CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix)
{
	int i,j,k,resTF,curstripsectindex,curchunkindex;

	int pindex,qindex,pwindex,qwindex,tarpindex,tarqindex,rows,cols,w;
	UINT32 *mat;

	

	//STRIPSECTGROUP *strsetgroupptr;
	//STRIPSECT *strsetptr,*curstrsetptr;
	//int strsetnum;
	
	CHUNKGROUP *pchunkgroupptr;
	CHUNK *pchunkptr,*curpchunkptr;
	int pchunknum;

	CHUNKGROUP *qchunkgroupptr;
	CHUNK *qchunkptr,*curqchunkptr;
	int qchunknum;
	
	
	//����1�������㷨������2��ʹ�õ�ǰ��У�������
	int *pupdatelist1,*pupdatelist2;
	int *qupdatelist1,*qupdatelist2;
	int *pupdatelist,*qupdatelist;


	BYTE *contentptr;
	//float poccupyrate,qoccupyrate;
	
	//��ȡ��������
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	//��ȡp��q���б�
	pchunkgroupptr=pparity->chunklist;
	pchunkptr=pchunkgroupptr->ckgroup;
	pchunknum=pchunkgroupptr->groupsize;

	pupdatelist=talloc(int,pchunknum);
	if(pupdatelist==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist,int,pchunknum);//��������0�������еĶ���FALSE

	pupdatelist1=talloc(int,pchunknum);
	if(pupdatelist1==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist1,int,pchunknum);//��������0�������еĶ���FALSE

	pupdatelist2=talloc(int,pchunknum);
	if(pupdatelist2==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist2,int,pchunknum);//��0


	qchunkgroupptr=qparity->chunklist;
	qchunkptr=qchunkgroupptr->ckgroup;
	qchunknum=qchunkgroupptr->groupsize;

	qupdatelist=talloc(int,qchunknum);
	if(qupdatelist==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist,int,qchunknum);//��������0�������еĶ���FALSE

	qupdatelist1=talloc(int,qchunknum);
	if(qupdatelist1==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist1,int,qchunknum);//��������0�������еĶ���FALSE

	qupdatelist2=talloc(int,qchunknum);
	if(qupdatelist2==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist2,int,qchunknum);//��0
	//������Ҫ���µ�У���
	resTF=matrix_update_bitmatrix_pqparity_chunklist_create(pupdatelist,qupdatelist,
													chunkpositionblockgroupptr,matrix);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_update_stripsect","parity chunklist can't create");
		return FALSE;
	}
	resTF=matrix_update_bitmatrix_pqupdatenum_chunklist_create(pupdatelist1,pupdatelist2,
																qupdatelist1,qupdatelist2,
																chunkpositionblockgroupptr,
																strsetblockgroupptr,pparity,qparity,
																matrix);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_update_stripsect","parity count list can't create");
		return FALSE;
	}
	//
	/*for(i=0;i<rows;i++)
	{
		pindex=i*cols;
		qindex=w*cols+i*cols;
		for(j=0;j<cols/w;j++)
		{
			for(k=0;k<w;k++)
			{
				tarpindex=pindex+j;
				tarqindex=qindex+j;
				prowsonenum[i]=prowsonenum[i]+mat[tarpindex];
				qrowsonenum[i]=qrowsonenum[i]+mat[tarqindex];
			}
		}
	}*/
	

	

	//�����Ѿ�֪������Ҫ���µĿ����ڿ��Լ�����
	curpchunkptr=pchunkptr;
	curqchunkptr=qchunkptr;
	for(i=0;i<(rows/2);i++)
	{
		//����P��
		if(pupdatelist[i]!=FALSE)//��ǰ�Ŀ���Ҫ�����㷨
		{
			//��һ�����жϵ���У����ڲ����ڴ�
			//poccupyrate=pupdatelist[j]/prowsonenum[i];
			resTF=profile_chunkblockgroup_chunk_add(parityblockgroupptr,curpchunkptr);
			if(resTF==FALSE)
			{
				show_error("matrix","bitmatrix_update_stripsect","chunk data can't add to parity list");
				return FALSE;
			}
			contentptr=curpchunkptr->chunkcontent;
			if(contentptr==NULL)
			{
				//chunknum;
				//�������Ȱ�У��
				if(pupdatelist1[i]<(pupdatelist2[i]+1))//��Ҫ���һ��
				{
					resTF=matrix_bitmatrix_updateI_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
																curpchunkptr,matrix,i);
					if(resTF==FALSE)
					{
						show_error("matrix","bitmatrix_update_stripsect","parity data can't update");
						return FALSE;
					}
				}
				else
				{
					resTF=matrix_bitmatrix_updateII_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
																curpchunkptr,matrix,i);
					if(resTF==FALSE)
					{
						show_error("matrix","bitmatrix_update_stripsect","parity data can't update");
						return FALSE;
					}
				}
			}
			else
			{
				//����
				if(pupdatelist1[i]<pupdatelist2[i])
				{
					resTF=matrix_bitmatrix_updateI_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
																curpchunkptr,matrix,i);
					if(resTF==FALSE)
					{
						show_error("matrix","bitmatrix_update_stripsect","parity data can't update");
						return FALSE;
					}
				}
				else
				{
					resTF=matrix_bitmatrix_updateII_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
																curpchunkptr,matrix,i);
					if(resTF==FALSE)
					{
						show_error("matrix","bitmatrix_update_stripsect","parity data can't update");
						return FALSE;
					}
				}
			}
			resTF=matrix_update_bitmatrix_pqupdatenum_chunklist_create(pupdatelist1,pupdatelist2,
																qupdatelist1,qupdatelist2,
																chunkpositionblockgroupptr,
																strsetblockgroupptr,pparity,qparity,
																matrix);
			if(resTF==FALSE)
			{
				show_error("matrix","bitmatrix_update_stripsect","parity count list can't create");
				return FALSE;
			}
		}
		//����Q��
		if(qupdatelist[i]!=FALSE)
		{
			//��һ�����жϵ���У����ڲ����ڴ�
			//��һ�����жϵ���У����ڲ����ڴ�
			//qoccupyrate=qdatelist[j]/qrowsonenum[i];
			resTF=profile_chunkblockgroup_chunk_add(parityblockgroupptr,curqchunkptr);
			if(resTF==FALSE)
			{
				show_error("matrix","bitmatrix_update_stripsect","chunk data can't add to parity list");
				return FALSE;
			}
			contentptr=curqchunkptr->chunkcontent;
			if(contentptr==NULL)
			{
				//������
				if(qupdatelist1[i]<(qupdatelist2[i]+1))
				{
					resTF=matrix_bitmatrix_updateI_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
																curqchunkptr,matrix,i+w);
					if(resTF==FALSE)
					{
						show_error("matrix","bitmatrix_update_stripsect","parity data can't update");
						return FALSE;
					}
				}
				else
				{
					resTF=matrix_bitmatrix_updateII_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
																curqchunkptr,matrix,i+w);
					if(resTF==FALSE)
					{
						show_error("matrix","bitmatrix_update_stripsect","parity data can't update");
						return FALSE;
					}
				}
			}
			else
			{
				//����
				if(qupdatelist1[i]<qupdatelist2[i])
				{
					resTF=matrix_bitmatrix_updateI_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
																curqchunkptr,matrix,i+w);
					if(resTF==FALSE)
					{
						show_error("matrix","bitmatrix_update_stripsect","parity data can't update");
						return FALSE;
					}
				}
				else
				{
					resTF=matrix_bitmatrix_updateII_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
																curqchunkptr,matrix,i+w);
					if(resTF==FALSE)
					{
						show_error("matrix","bitmatrix_update_stripsect","parity data can't update");
						return FALSE;
					}
				}
			}
			resTF=matrix_update_bitmatrix_pqupdatenum_chunklist_create(pupdatelist1,pupdatelist2,
																qupdatelist1,qupdatelist2,
																chunkpositionblockgroupptr,
																strsetblockgroupptr,pparity,qparity,
																matrix);
			if(resTF==FALSE)
			{
				show_error("matrix","bitmatrix_update_stripsect","parity count list can't create");
				return FALSE;
			}

		}
		curpchunkptr++;
		curqchunkptr++;
	}
	free(pupdatelist);
	free(pupdatelist1);
	free(pupdatelist2);

	free(qupdatelist);
	free(qupdatelist1);
	free(qupdatelist2);
	return TRUE;
}

int matrix_matrix_updateII_chunk_calcaulate(CHUNK *tarchunkptr,CHUNK *souchunkptr,int curvalue,int w)
{
	int resTF;
	if(curvalue==1)
	{
		//������Ҫ���
		resTF=matrix_CHUNK_add_data(tarchunkptr,souchunkptr);
		if(resTF==FALSE)
		{
			show_error("matrix","matrix_updateII_chunk_calcaulate","chunk data can't add");
			return FALSE;
		}
	}
	else
	{
		switch(w)
		{
		case 8:
			resTF=matrix_CHUNK_w08_multiply_add(tarchunkptr,souchunkptr,curvalue);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_updateII_chunk_calcaulate","data can't calculate in w08");
				return FALSE;
			}
			break;
		case 16:
			resTF=matrix_CHUNK_w16_multiply_add(tarchunkptr,souchunkptr,curvalue);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_updateII_chunk_calcaulate","data can't calculate in w16");
				return FALSE;
			}
			break;
		case 32:
			resTF=matrix_CHUNK_w32_multiply_add(tarchunkptr,souchunkptr,curvalue);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_updateII_chunk_calcaulate","data can't calculate in w32");
				return FALSE;
			}
			break;
		}
	}
	return TRUE;
}

int matrix_update_matrix_pqupdatenum_chunklist_create(int *pupdatelist,int *qupdatelist,//updatelist��һ��Ϊ��һ���������ڶ���Ϊ�ڶ�����
															CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
															STRIPSECTBLOCKGROUP *strsetblockgroupptr,BITMATRIX *matrix)
{
	int i,resTF;
	STRIPSECTBLOCK *strsetblockptr,*curstrsetblockptr;
	int strsetnum;
	STRIPSECT *strsetptr;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr;

	int tarindex,rowsindex;

	int rows,cols,w;
	UINT32 *mat;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	strsetblockptr=strsetblockgroupptr->stripsectblockptr;
	strsetnum=strsetblockgroupptr->groupsize;

	curstrsetblockptr=strsetblockptr;
	for(i=0;i<strsetnum;i++)
	{
		strsetptr=curstrsetblockptr->stripsectptr;
		chunkgroupptr=strsetptr->chunklist;
		chunkptr=chunkgroupptr->ckgroup;
		rowsindex=0;
		tarindex=rowsindex+i;
		//����p��
		resTF=mat[tarindex];
		if(resTF!=FALSE)//��ǰ��Ҫ����
		{
			resTF=profile_search_chunkposition_id(i,0,chunkpositionblockgroupptr);
			if(resTF==PFALSE)
			{
				resTF=profile_chunk_should_read(chunkptr);
				if(resTF==TRUE)
				{
					pupdatelist[0]=pupdatelist[0]+1;
				}
			}
			else
			{
				resTF=profile_chunk_should_read(chunkptr);
				if(resTF==TRUE)
				{
					pupdatelist[1]=pupdatelist[1]+1;
				}
			}
		}
		rowsindex=cols;
		tarindex=rowsindex+i;

		//����q��
		resTF=mat[tarindex];
		if(resTF==FALSE)
		{
			resTF=profile_search_chunkposition_id(i,0,chunkpositionblockgroupptr);
			if(resTF==FALSE)
			{
				resTF=profile_chunk_should_read(chunkptr);
				if(resTF==FALSE)
				{
					qupdatelist[0]=qupdatelist[0]+1;
				}
			}
			else
			{
				resTF=profile_chunk_should_read(chunkptr);
				if(resTF==FALSE)
				{
					qupdatelist[1]=qupdatelist[1]+1;
				}
			}
		}
		curstrsetblockptr++;
	}
	return TRUE;

}
//1����
int matrix_matrix_updateI_chunk_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition������Ҫ���µ�У����б�
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//��ǰ����������
											CHUNK *tarchunkptr,INTMATRIX *matrix,int chkindex)//Ŀ��У��飬����Ŀ�������
{
	int i,resTF,isfirst;
	int curindex,rowsindex,colsindex,curvalue;
	CHUNKBLOCKGROUP *tempchunkblockgroupptr;
	CHUNKBLOCK *tempchunkblockptr;
	int tempchunknum;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr;
	//BYTE *contentptr;
	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	CHUNK *curchunkptr,*souchunkptr;
	int chunknum;

	STRIPSECTBLOCK *strsetblockptr,*curstrsetblockptr;
	STRIPSECT *strsetptr;
	int strsetnum;

	UINT32 *mat;
	int rows,cols,w;

	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	chunknum=chunkpositionblockgroupptr->groupsize;

	strsetblockptr=strsetblockgroupptr->stripsectblockptr;
	strsetnum=strsetblockgroupptr->groupsize;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	tempchunkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(tempchunkblockgroupptr==NULL)
	{
		show_error("matrix","matrix_updateI_chunk_RAID6","No memory");
		return FALSE;
	}

	tempchunkblockptr=talloc(CHUNKBLOCK,cols);
	if(tempchunkblockptr==NULL)
	{
		show_error("matrix","matrix_updateI_chunk_RAID6","No memory");
		return FALSE;
	}
	//contentptr=tarchunkptr->chunkcontent;
	resTF=profile_chunk_data_isfree(tarchunkptr);
	if(resTF==TRUE)
	{
		resTF=profile_chunk_create_empty_data(tarchunkptr);
		if(resTF==FALSE)
		{
			show_error("matrix","matrix_updateI_chunk_RAID6","chunk data can't create");
			return FALSE;
		}
	}
	curstrsetblockptr=strsetblockptr;
	rowsindex=chkindex*cols;//��λ��һ��
	isfirst=TRUE;
	for(i=0;i<strsetnum;i++)
	{
		//��ȡ��ǰchunkָ��
		strsetptr=curstrsetblockptr->stripsectptr;
		
		chunkgroupptr=strsetptr->chunklist;
		curchunkptr=chunkgroupptr->ckgroup;

		souchunkptr=profile_get_chunkposition_ptr(i,0,chunkpositionblockgroupptr);
		if(souchunkptr==NULL)
		{
			souchunkptr=curchunkptr;
			resTF=profile_chunk_data_isfree(souchunkptr);
			if(resTF==TRUE)//��ǰ�����ǿյ�
			{
				//������ͬ�����ڴ�
				resTF=profile_chunk_data_read(souchunkptr);
				if(resTF==FALSE)
				{
					show_error("matrix","matrix_updateI_chunk_RAID6","chunk data can't read");
					return FALSE;
				}
				resTF=profile_chunkblockgroup_chunk_add(tempchunkblockgroupptr,souchunkptr);
				if(resTF==FALSE)
				{
					show_error("matrix","matrix_updateI_chunk_RAID6","chunk can't add to chunklist");
					return FALSE;
				}
			}
		}
		colsindex=i;
		curindex=rowsindex+colsindex;
		curvalue=mat[curindex];
		if(curvalue!=FALSE)
		{
			if(isfirst==TRUE)
			{
				resTF=matrix_matrix_firstchunk_handle(tarchunkptr,souchunkptr,curvalue,w);
				if(resTF==FALSE)
				{
					show_error("matrix","matrix_updateI_chunk_RAID6","first parity chunk can't calculate");
					return FALSE;
				}
				isfirst=FALSE;
			}
			else
			{
				resTF=matrix_matrix_notfirstchunk_handle(tarchunkptr,souchunkptr,curvalue,w);
				if(resTF==FALSE)
				{
					show_error("matrix","matrix_updateI_chunk_RAID6","parity chunk can't calculate");
					return FALSE;
				}
			}
		}
		curstrsetblockptr++;

	}
	resTF=profile_tempfree_chunkblock_ptr(tempchunkblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("matrix","matrix_updateI_chunk_RAID6","temp chunk list can't free");
		return FALSE;
	}
	free(tempchunkblockgroupptr);
	free(tempchunkblockptr);
	return TRUE;
}
//����У���
int matrix_matrix_updateII_chunk_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition������Ҫ���µ�У����б�
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//��ǰ����������
											CHUNK *tarchunkptr,INTMATRIX *matrix,int chkindex)//Ŀ��У��飬����Ŀ�������
{
	int i,resTF;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr,*souchunkptr;

	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	int chunknum;

	STRIPSECTBLOCK *strsetblockptr,*curstrsetblockptr;
	STRIPSECT *strsetptr;
	int strsetnum;

	CHUNKBLOCKGROUP *tempchunkblockgroupptr;
	CHUNKBLOCK *tempchunkblockptr;

	int strsetindex,chunkindex;
	int curindex,index,curvalue;
	int rows,cols,w;
	UINT32 *mat;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	chunknum=chunkpositionblockgroupptr->groupsize;

	strsetblockptr=strsetblockgroupptr->stripsectblockptr;
	strsetnum=strsetblockgroupptr->groupsize;

	tempchunkblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(tempchunkblockgroupptr==NULL)
	{
		show_error("matrix","matrix_updateII_chunk_RAID6","No memory");
		return FALSE;
	}

	tempchunkblockptr=talloc(CHUNKBLOCK,cols);
	if(tempchunkblockptr==NULL)
	{
		show_error("matrix","matrix_updateII_chunk_RAID6","No memory");
		return FALSE;
	}
	tempchunkblockgroupptr->chunkblockptr=tempchunkblockptr;
	tempchunkblockgroupptr->groupsize=0;


	resTF=profile_chunk_data_isfree(tarchunkptr);
	if(resTF==TRUE)
	{
		resTF=profile_chunk_data_read(tarchunkptr);
		if(resTF==FALSE)
		{
			show_error("matrix","matrix_updateII_chunk_RAID6","chunk data can't create");
			return FALSE;
		}
	}
	curstrsetblockptr=strsetblockptr;
	index=chkindex*cols;//����к�
	//curchunkpositionblockptr=chunkpositionblockptr;
	for(i=0;i<strsetnum;i++)//
	{
		//����ÿһ��chunk�������е�����
		//strsetindex=curchunkpositionblockptr->stripsectindex;
		//chunkindex=curchunkpositionblockptr->chunkindex;
		strsetptr=curstrsetblockptr->stripsectptr;

		chunkgroupptr=strsetptr->chunklist;
		chunkptr=chunkgroupptr->ckgroup;

		curchunkptr=chunkptr;

		
		curindex=index+i;
		curvalue=mat[curindex];
		if(curvalue!=FALSE)//��ǰ��Ҫ����
		{
			strsetindex=i;
			chunkindex=0;
			souchunkptr=profile_get_chunkposition_ptr(strsetindex,chunkindex,chunkpositionblockgroupptr);
			if(souchunkptr!=NULL)//˵����ǰ��chunk����Ҫ���µ�chunk�б���
			{
				//����
				resTF=profile_chunk_data_isfree(curchunkptr);
				if(resTF==FALSE)
				{
					resTF=profile_chunk_data_read(curchunkptr);//���㵱ǰ����
					if(resTF==FALSE)
					{
						show_error("matrix","matrix_updateII_chunk_RAID6","chunk data can't create");
						return FALSE;
					}
					resTF=profile_chunkblockgroup_chunk_add(tempchunkblockgroupptr,curchunkptr);
					if(resTF==FALSE)
					{
						show_error("matrix","matrix_updateII_chunk_RAID6","temp chunk can't add");
						return FALSE;
					}
				}
				resTF=matrix_matrix_updateII_chunk_calcaulate(tarchunkptr,curchunkptr,curvalue,w);
				if(resTF==FALSE)
				{
					show_error("matrix","matrix_updateII_chunk_RAID6","chunk data can't calculate");
					return FALSE;
				}
				resTF=matrix_matrix_updateII_chunk_calcaulate(tarchunkptr,souchunkptr,curvalue,w);
				if(resTF==FALSE)
				{
					show_error("matrix","matrix_updateII_chunk_RAID6","chunk data can't calculate");
					return FALSE;
				}
			}
			//strsetptr=curstrsetblockptr->stripsectptr;
			//chunkgroupptr=strsetptr->chunklist;
			//chunkptr=chunkgroupptr->ckgroup;
		}

		curstrsetblockptr++;
	}
	resTF=profile_tempfree_chunkblock_ptr(tempchunkblockgroupptr);
	if(resTF==FALSE)
	{
		show_error("matrix","matrix_updateI_chunk_RAID6","temp chunk list can't free");
		return FALSE;
	}
	free(tempchunkblockgroupptr);
	free(tempchunkblockptr);
	return TRUE;
}
//��ǰchunkblockgroup�е�������Ҫ��һ��strip��
int matrix_matrix_update_stripsect_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,
										CHUNKBLOCKGROUP *parityblockgroupptr,INTMATRIX *matrix)
{
	int i,resTF;
	int *pupdatelist,*qupdatelist;

	CHUNKGROUP *pchunkgroupptr;
	CHUNK *pchunkptr,*curpchunkptr;
	int pchunknum;

	CHUNKGROUP *qchunkgroupptr;
	CHUNK *qchunkptr,*curqchunkptr;
	int qchunknum;

	pupdatelist=talloc(int,2);
	if(pupdatelist==NULL)
	{
		show_error("matrix","matrix_update_stripsect_RAID6","No memory");
		return FALSE;
	}

	qupdatelist=talloc(int,2);
	if(qupdatelist==NULL)
	{
		show_error("matrix","matrix_update_stripsect_RAID6","No memory");
		return FALSE;
	}
	pchunkgroupptr=pparity->chunklist;
	pchunkptr=pchunkgroupptr->ckgroup;
	pchunknum=pchunkgroupptr->groupsize;

	qchunkgroupptr=qparity->chunklist;
	qchunkptr=qchunkgroupptr->ckgroup;
	qchunknum=qchunkgroupptr->groupsize;

	//���Ǽ��㵱ǰ����Ҫ���µķ�������Ҫ��������
	resTF=matrix_update_matrix_pqupdatenum_chunklist_create(pupdatelist,qupdatelist,
														chunkpositionblockgroupptr,strsetblockgroupptr,
														matrix);
	if(resTF==FALSE)
	{
		show_error("matrix","matrix_update_stripsect_RAID6","updatelist can't calculate");
		return FALSE;
	}
	//����һ�µ�ǰָ��
	curpchunkptr=pchunkptr;
	resTF=profile_chunk_data_isfree(curpchunkptr);
	if(resTF==TRUE)//�����ǰУ���Ϊ��
	{
		if(pupdatelist[0]<(pupdatelist[1]+1))
		{
			resTF=matrix_matrix_updateI_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
													curpchunkptr,matrix,0);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_update_stripsect_RAID6","p chunk data can't update");
				return FALSE;
			}
		}
		else
		{
			resTF=matrix_matrix_updateII_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
													curpchunkptr,matrix,0);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_update_stripsect_RAID6","p chunk data can't update");
				return FALSE;
			}
		}
	}
	else
	{
		if(pupdatelist[0]<pupdatelist[1])
		{
			resTF=matrix_matrix_updateI_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
													curpchunkptr,matrix,0);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_update_stripsect_RAID6","p chunk data can't update");
				return FALSE;
			}
		}
		else
		{
			resTF=matrix_matrix_updateII_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
													curpchunkptr,matrix,0);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_update_stripsect_RAID6","p chunk data can't update");
				return FALSE;
			}
		}
	}
	resTF=matrix_update_matrix_pqupdatenum_chunklist_create(pupdatelist,qupdatelist,
														chunkpositionblockgroupptr,strsetblockgroupptr,
														matrix);//��Ҫ���¼���
	if(resTF==FALSE)
	{
		show_error("matrix","matrix_update_stripsect_RAID6","updatelist can't calculate");
		return FALSE;
	}
	curqchunkptr=qchunkptr;
	resTF=profile_chunk_data_isfree(curqchunkptr);
	if(resTF==TRUE)//�����ǰУ���Ϊ��
	{
		if(qupdatelist[0]<(qupdatelist[1]+1))
		{
			resTF=matrix_matrix_updateI_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
													curqchunkptr,matrix,1);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_update_stripsect_RAID6","q chunk data can't update");
				return FALSE;
			}
		}
		else
		{
			resTF=matrix_matrix_updateII_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
													curqchunkptr,matrix,1);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_update_stripsect_RAID6","q chunk data can't update");
				return FALSE;
			}
		}
	}
	else
	{
		if(pupdatelist[0]<pupdatelist[1])
		{
			resTF=matrix_matrix_updateI_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
													curqchunkptr,matrix,1);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_update_stripsect_RAID6","q chunk data can't update");
				return FALSE;
			}
		}
		else
		{
			resTF=matrix_matrix_updateII_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,
													curqchunkptr,matrix,1);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_update_stripsect_RAID6","q chunk data can't update");
				return FALSE;
			}
		}
	}
	free(pupdatelist);
	free(qupdatelist);
	return TRUE;
}
int matrix_update_bitmatrix_parity_chunklist(int *updatelist,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
												BITMATRIX *matrix,int updatenum)//�ҳ���ǰ��Ҫ���и��µ��б�
{
	int i,j;
	//int stripindex,chunkindex;

	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	int chunknum;

	int tarindex,index,rowsindex,colsindex;
	int strsetindex,chunkindex;

	UINT32 *mat;
	int rows,cols,w;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	chunknum=chunkpositionblockgroupptr->groupsize;

	curchunkpositionblockptr=chunkpositionblockptr;
	for(i=0;i<chunknum;i++)
	{
		strsetindex=curchunkpositionblockptr->stripsectindex;
		chunkindex=curchunkpositionblockptr->chunkindex;
		for(j=0;j<updatenum;j++)
		{
			index=j*cols;
			
			rowsindex=strsetindex*w;
			colsindex=chunkindex;

			tarindex=index+rowsindex+colsindex;//����λ��
			if(mat[tarindex]==TRUE)
			{
				updatelist[j]=TRUE;
			}
		
		}
		curchunkpositionblockptr++;
	}
	return TRUE;
}
int matrix_update_bitmatrix_updatenum_chunklist_create(int *updatelist1,int *updatelist2,
															CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
															STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
															BITMATRIX *matrix,int updatenum)//�������ַ�����updatelist
{
	int i,j,k,resTF;
	STRIPSECTBLOCK *datastrsetblockptr,*curdatastrsetblockptr;
	STRIPSECT *datastripsectptr;
	int datastrsetnum;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;
	int chunknum;

	int rows,cols,w;
	UINT32 *mat;

	int curindex,rowsindex,colsindex,index;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	for(i=0;i<updatenum;i++)
	{
		datastrsetblockptr=datastrsetblockgroupptr->stripsectblockptr;
		datastrsetnum=datastrsetblockgroupptr->groupsize;

		curdatastrsetblockptr=datastrsetblockptr;
		datastripsectptr=curdatastrsetblockptr->stripsectptr;
		for(j=0;j<datastrsetnum;j++)
		{
			chunkgroupptr=datastripsectptr->chunklist;

			chunkptr=chunkgroupptr->ckgroup;
			chunknum=chunkgroupptr->groupsize;

			curchunkptr=chunkptr;
			for(k=0;k<chunknum;k++)
			{
				index=i*cols;

				rowsindex=j*w;//
				colsindex=k;

				curindex=index+rowsindex+colsindex;
				if(mat[curindex]==TRUE)
				{
					resTF=profile_search_chunkposition_id(j,k,chunkpositionblockgroupptr);
					if(resTF==PFALSE)
					{
						resTF=profile_chunk_should_read(curchunkptr);
						if(resTF==TRUE)
						{
							updatelist1[i]=updatelist1[i]+1;
						}
					}
					else
					{
						resTF=profile_chunk_should_read(curchunkptr);
						if(resTF==TRUE)
						{
							updatelist2[i]=updatelist2[i]+1;
						}
					}
				}
				curchunkptr++;
			}
		}
		
	}
	return TRUE;
}

int matrix_bitmatrix_updateI_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition������Ҫ���µ�У����б�
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//��ǰ����������
											CHUNK *tarchunkptr,BITMATRIX *matrix,int chkindex)//Ŀ��У��飬����Ŀ�������
{
	//��RAID-6һ��
	int resTF;
	resTF=matrix_bitmatrix_updateI_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,tarchunkptr,matrix,chkindex);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_updateI_chunk","strip can't calculate");
		return FALSE;
	}
	return TRUE;
}
int matrix_bitmatrix_updateII_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition������Ҫ���µ�У����б�
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//��ǰ����������
											CHUNK *tarchunkptr,BITMATRIX *matrix,int chkindex)//Ŀ��У��飬����Ŀ�������
{
	//��RAID-6һ��
	int resTF;
	resTF=matrix_bitmatrix_updateII_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,tarchunkptr,matrix,chkindex);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_updateI_chunk","strip can't calculate");
		return FALSE;
	}
	return TRUE;
}
int matrix_bitmatrix_RCW_update_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										STRIP *stripptr,CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix)
{
	int i,resTF,updatenum;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;
	int chunknum;

	STRIPSECTBLOCKGROUP *datastrsetblockgroupptr;
	STRIPSECTBLOCK *datastrsetblockptr;

	STRIPSECTBLOCKGROUP *codestrsetblockgroupptr;
	STRIPSECTBLOCK *codestrsetblockptr,*curcodestrsetblockptr;
	STRIPSECT *codestrsetptr;
	int codestrsetnum;

	int *updatelist;

	REGION *regionptr;
	CODEPARA *codeparamptr;
	int codenum,datanum,w;
	int codeindex;

	regionptr=stripptr->regionptr;
	codeparamptr=regionptr->codepara;

	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	w=codeparamptr->w;

	//���ռ�
	datastrsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(datastrsetblockgroupptr==NULL)
	{
		show_error("matrix","matrix_update_strip","No memory");
		return FALSE;
	}

	datastrsetblockptr=talloc(STRIPSECTBLOCK,datanum);
	if(datastrsetblockptr==NULL)
	{
		show_error("matrix","bitmatrix_update_strip","No memory");
		return FALSE;
	}
	datastrsetblockgroupptr->stripsectblockptr=datastrsetblockptr;
	datastrsetblockgroupptr->groupsize=datanum;

	codestrsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(codestrsetblockgroupptr==NULL)
	{
		show_error("matrix","bitmatrix_update_strip","No memory");
		return FALSE;
	}

	codestrsetblockptr=talloc(STRIPSECTBLOCK,codenum);
	if(codestrsetblockptr==NULL)
	{
		show_error("matrix","bitmatrix_update_strip","No memory");
		return FALSE;
	}
	codestrsetblockgroupptr->stripsectblockptr=codestrsetblockptr;
	codestrsetblockgroupptr->groupsize=codenum;

	resTF=profile_strip_into_stripsect_ptr(datastrsetblockgroupptr,codestrsetblockgroupptr,stripptr);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_update_strip","No memory");
		return FALSE;
	}

	updatenum=codenum*w;
	updatelist=talloc(int,updatenum);
	if(updatelist==NULL)
	{
		show_error("matrix","bitmatrix_update_strip","No memory");
		return FALSE;
	}
	resTF=matrix_update_bitmatrix_parity_chunklist(updatelist,chunkpositionblockgroupptr,matrix,updatenum);//�ж��ǲ�����Ҫ����
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_update_strip","parity chunklist can't create");
		return FALSE;
	}
	codestrsetblockptr=codestrsetblockgroupptr->stripsectblockptr;
	codestrsetnum=codestrsetblockgroupptr->groupsize;

	curcodestrsetblockptr=codestrsetblockptr;

	codeindex=0;
	//��ʼʹ��RCW���и���
	for(i=0;i<codestrsetnum;i++)
	{
		//�����������е�Ŀ���
		codestrsetptr=curcodestrsetblockptr->stripsectptr;
		
		chunkgroupptr=codestrsetptr->chunklist;
		chunkptr=chunkgroupptr->ckgroup;
		chunknum=chunkgroupptr->groupsize;

		curchunkptr=chunkptr;
		for(i=0;i<chunknum;i++)
		{
			if(updatelist[codeindex]==TRUE)
			{
				resTF=profile_chunkblockgroup_chunk_add(parityblockgroupptr,curchunkptr);
				if(resTF==FALSE)
				{
					show_error("matrix","bitmatrix_update_strip","chunk can't add to parityblockgroup");
					return FALSE;
				}
				//�����ǰ����Ҫ����1
				resTF=matrix_bitmatrix_updateI_chunk(chunkpositionblockgroupptr,datastrsetblockgroupptr,curchunkptr,matrix,codeindex);
				if(resTF==FALSE)
				{
					show_error("matrix","bitmatrix_update_strip","chunk data update can't calculate");
					return FALSE;
				}
			}
			curchunkptr++;
			codeindex++;
		}
		curcodestrsetblockptr++;
	}
	free(updatelist);
	free(datastrsetblockgroupptr);
	free(datastrsetblockptr);
	free(codestrsetblockgroupptr);
	free(codestrsetblockptr);
	return TRUE;
}
int matrix_bitmatrix_RMW_update_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										STRIP *stripptr,CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix)
{
	int i,resTF,updatenum;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;
	int chunknum;

	STRIPSECTBLOCKGROUP *datastrsetblockgroupptr;
	STRIPSECTBLOCK *datastrsetblockptr;

	STRIPSECTBLOCKGROUP *codestrsetblockgroupptr;
	STRIPSECTBLOCK *codestrsetblockptr,*curcodestrsetblockptr;
	STRIPSECT *codestrsetptr;
	int codestrsetnum;

	int *updatelist;

	REGION *regionptr;
	CODEPARA *codeparamptr;
	int codenum,datanum,w;
	int codeindex;

	regionptr=stripptr->regionptr;
	codeparamptr=regionptr->codepara;

	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	w=codeparamptr->w;

	//���ռ�
	datastrsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(datastrsetblockgroupptr==NULL)
	{
		show_error("matrix","matrix_update_strip","No memory");
		return FALSE;
	}

	datastrsetblockptr=talloc(STRIPSECTBLOCK,datanum);
	if(datastrsetblockptr==NULL)
	{
		show_error("matrix","bitmatrix_update_strip","No memory");
		return FALSE;
	}
	datastrsetblockgroupptr->stripsectblockptr=datastrsetblockptr;
	datastrsetblockgroupptr->groupsize=datanum;

	codestrsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(codestrsetblockgroupptr==NULL)
	{
		show_error("matrix","bitmatrix_update_strip","No memory");
		return FALSE;
	}

	codestrsetblockptr=talloc(STRIPSECTBLOCK,codenum);
	if(codestrsetblockptr==NULL)
	{
		show_error("matrix","bitmatrix_update_strip","No memory");
		return FALSE;
	}
	codestrsetblockgroupptr->stripsectblockptr=codestrsetblockptr;
	codestrsetblockgroupptr->groupsize=codenum;

	resTF=profile_strip_into_stripsect_ptr(datastrsetblockgroupptr,codestrsetblockgroupptr,stripptr);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_update_strip","No memory");
		return FALSE;
	}

	updatenum=codenum*w;
	updatelist=talloc(int,updatenum);
	if(updatelist==NULL)
	{
		show_error("matrix","bitmatrix_update_strip","No memory");
		return FALSE;
	}
	resTF=matrix_update_bitmatrix_parity_chunklist(updatelist,chunkpositionblockgroupptr,matrix,updatenum);//�ж��ǲ�����Ҫ����
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_update_strip","parity chunklist can't create");
		return FALSE;
	}
	codestrsetblockptr=codestrsetblockgroupptr->stripsectblockptr;
	codestrsetnum=codestrsetblockgroupptr->groupsize;

	curcodestrsetblockptr=codestrsetblockptr;

	codeindex=0;
	//��ʼʹ��RCW���и���
	for(i=0;i<codestrsetnum;i++)
	{
		//�����������е�Ŀ���
		codestrsetptr=curcodestrsetblockptr->stripsectptr;
		
		chunkgroupptr=codestrsetptr->chunklist;
		chunkptr=chunkgroupptr->ckgroup;
		chunknum=chunkgroupptr->groupsize;

		curchunkptr=chunkptr;
		for(i=0;i<chunknum;i++)
		{
			if(updatelist[codeindex]==TRUE)
			{
				resTF=profile_chunkblockgroup_chunk_add(parityblockgroupptr,curchunkptr);
				if(resTF==FALSE)
				{
					show_error("matrix","bitmatrix_update_strip","chunk can't add to parityblockgroup");
					return FALSE;
				}
				//�����ǰ����Ҫ����1
				resTF=matrix_bitmatrix_updateII_chunk(chunkpositionblockgroupptr,datastrsetblockgroupptr,curchunkptr,matrix,codeindex);
				if(resTF==FALSE)
				{
					show_error("matrix","bitmatrix_update_strip","chunk data update can't calculate");
					return FALSE;
				}
			}
			curchunkptr++;
			codeindex++;
		}
		curcodestrsetblockptr++;
	}
	free(updatelist);
	free(datastrsetblockgroupptr);
	free(datastrsetblockptr);
	free(codestrsetblockgroupptr);
	free(codestrsetblockptr);

	return TRUE;
}
int matrix_bitmatrix_update_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										STRIP *stripptr,CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix)
{

	int i,resTF,updatenum;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*curchunkptr;
	int chunknum;

	STRIPSECTBLOCKGROUP *datastrsetblockgroupptr;
	STRIPSECTBLOCK *datastrsetblockptr;

	STRIPSECTBLOCKGROUP *codestrsetblockgroupptr;
	STRIPSECTBLOCK *codestrsetblockptr,*curcodestrsetblockptr;
	STRIPSECT *codestrsetptr;
	int codestrsetnum;

	int *updatelist,*updatelist1,*updatelist2;

	REGION *regionptr;
	CODEPARA *codeparamptr;
	int codenum,datanum,w;
	int codeindex;

	regionptr=stripptr->regionptr;
	codeparamptr=regionptr->codepara;

	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	w=codeparamptr->w;
	//���ռ�
	datastrsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(datastrsetblockgroupptr==NULL)
	{
		show_error("matrix","matrix_update_strip","No memory");
		return FALSE;
	}

	datastrsetblockptr=talloc(STRIPSECTBLOCK,datanum);
	if(datastrsetblockptr==NULL)
	{
		show_error("matrix","bitmatrix_update_strip","No memory");
		return FALSE;
	}
	datastrsetblockgroupptr->stripsectblockptr=datastrsetblockptr;
	datastrsetblockgroupptr->groupsize=datanum;

	codestrsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(codestrsetblockgroupptr==NULL)
	{
		show_error("matrix","bitmatrix_update_strip","No memory");
		return FALSE;
	}

	codestrsetblockptr=talloc(STRIPSECTBLOCK,codenum);
	if(codestrsetblockptr==NULL)
	{
		show_error("matrix","bitmatrix_update_strip","No memory");
		return FALSE;
	}
	codestrsetblockgroupptr->stripsectblockptr=codestrsetblockptr;
	codestrsetblockgroupptr->groupsize=codenum;

	resTF=profile_strip_into_stripsect_ptr(datastrsetblockgroupptr,codestrsetblockgroupptr,stripptr);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_update_strip","No memory");
		return FALSE;
	}
	updatenum=codenum*w;
	updatelist=talloc(int,updatenum);
	if(updatelist==NULL)
	{
		show_error("matrix","bitmatrix_update_strip","No memory");
		return FALSE;
	}

	updatelist1=talloc(int,updatenum);
	if(updatelist1==NULL)
	{
		show_error("matrix","bitmatrix_update_strip","No memory");
		return FALSE;
	}

	updatelist2=talloc(int,updatenum);
	if(updatelist2==NULL)
	{
		show_error("matrix","bitmatrix_update_strip","No memory");
		return FALSE;
	}

	resTF=matrix_update_bitmatrix_parity_chunklist(updatelist,chunkpositionblockgroupptr,matrix,updatenum);//�ж��ǲ�����Ҫ����
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_update_strip","parity chunklist can't create");
		return FALSE;
	}
	resTF=matrix_update_bitmatrix_updatenum_chunklist_create(updatelist1,updatelist2,chunkpositionblockgroupptr,datastrsetblockgroupptr,matrix,updatenum);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_update_strip","parity count list can't create");
		return FALSE;
	}
	codestrsetblockptr=codestrsetblockgroupptr->stripsectblockptr;
	codestrsetnum=codestrsetblockgroupptr->groupsize;

	curcodestrsetblockptr=codestrsetblockptr;

	codeindex=0;
	for(i=0;i<codestrsetnum;i++)
	{
		//�����������е�Ŀ���
		codestrsetptr=curcodestrsetblockptr->stripsectptr;
		
		chunkgroupptr=codestrsetptr->chunklist;
		chunkptr=chunkgroupptr->ckgroup;
		chunknum=chunkgroupptr->groupsize;

		curchunkptr=chunkptr;
		for(i=0;i<chunknum;i++)
		{
			if(updatelist[codeindex]==TRUE)
			{
				resTF=profile_chunkblockgroup_chunk_add(parityblockgroupptr,curchunkptr);
				if(resTF==FALSE)
				{
					show_error("matrix","bitmatrix_update_strip","chunk can't add to parityblockgroup");
					return FALSE;
				}
				//�����ǰ����Ҫ����
				resTF=profile_chunk_should_read(curchunkptr);
				if(resTF==FALSE)
				{
					if(updatelist1[codeindex]<(updatelist2[codeindex]+1))
					{
						resTF=matrix_bitmatrix_updateI_chunk(chunkpositionblockgroupptr,datastrsetblockgroupptr,curchunkptr,matrix,codeindex);
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_update_strip","chunk data update can't calculate");
							return FALSE;
						}
					}
					else
					{
						resTF=matrix_bitmatrix_updateI_chunk(chunkpositionblockgroupptr,datastrsetblockgroupptr,curchunkptr,matrix,codeindex);
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_update_strip","");
							return FALSE;
						}
					}
				}
				else
				{
					if(updatelist1[codeindex]<updatelist2[codeindex])
					{
						resTF=matrix_bitmatrix_updateI_chunk(chunkpositionblockgroupptr,datastrsetblockgroupptr,curchunkptr,matrix,codeindex);
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_update_strip","chunk data update can't calculate");
							return FALSE;
						}
					}
					else
					{
						resTF=matrix_bitmatrix_updateI_chunk(chunkpositionblockgroupptr,datastrsetblockgroupptr,curchunkptr,matrix,codeindex);
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_update_strip","");
							return FALSE;
						}
					}
				}
				//���¼��㵱ǰ����
				resTF=matrix_update_bitmatrix_updatenum_chunklist_create(updatelist1,updatelist2,chunkpositionblockgroupptr,datastrsetblockgroupptr,matrix,updatenum);
				if(resTF==FALSE)
				{
					show_error("matrix","bitmatrix_update_strip","parity count list can't create");
					return FALSE;
				}
			}
			curchunkptr++;
			codeindex++;
		}
		curcodestrsetblockptr++;
	}

	//�������ݺ�У���б�
	free(updatelist);
	free(updatelist1);
	free(updatelist2);
	free(datastrsetblockgroupptr);
	free(datastrsetblockptr);
	free(codestrsetblockgroupptr);
	free(codestrsetblockptr);
	return TRUE;
}

int matrix_update_matrix_parity_chunklist(int *updatelist,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
													BITMATRIX *matrix,int updatenum)//�ҳ���ǰ��Ҫ���и��µ��б�
{
	int i,j;

	UINT32 *mat;
	int rows,cols,w;

	int strsetindex,chunkindex;
	
	int curindex,index,rowsindex,colsindex;

	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	int chunknum;

	mat=matrix->matrix;
	rows=matrix->xm;


	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	chunknum=chunkpositionblockgroupptr->groupsize;

	curchunkpositionblockptr=chunkpositionblockptr;
	for(i=0;i<chunknum;i++)
	{
		strsetindex=curchunkpositionblockptr->stripsectindex;
		chunkindex=curchunkpositionblockptr->chunkindex;
		for(j=0;j<updatenum;j++)
		{
			index=j*cols;
			rowsindex=strsetindex*w;
			colsindex=chunkindex;
			curindex=index+rowsindex+colsindex;
			if(mat[curindex]==TRUE)
			{
				updatelist[j]=TRUE;
			}
		}
		curchunkpositionblockptr++;
	}
	return TRUE;
}
int matrix_update_matrix_updatenum_chunklist_create(int *updatelist1,int *updatelist2,
														CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
														STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
														BITMATRIX *matrix,int updatenum)//�������ַ�����updatelist
{
	int i,j,k,resTF;
	//int tarindex,rowsindex,colsindex;

	STRIPSECTBLOCK *datastrsetblockptr,*curdatastrsetblockptr;
	STRIPSECT *datastrsetptr;
	int datastrsetnum;

	CHUNKGROUP *datachunkgroupptr;
	CHUNK *datachunkptr,*curdatachunkptr;
	int datachunknum;

	UINT32 *mat;
	int rows,cols,w;

	int curindex,index,rowsindex,colsindex;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	
	for(i=0;i<updatenum;i++)
	{
		datastrsetblockptr=datastrsetblockgroupptr->stripsectblockptr;
		datastrsetnum=datastrsetblockgroupptr->groupsize;

		curdatastrsetblockptr=datastrsetblockptr;
		for(j=0;j<datastrsetnum;j++)
		{
			datastrsetptr=curdatastrsetblockptr->stripsectptr;
			datachunkgroupptr=datastrsetptr->chunklist;

			datachunkptr=datachunkgroupptr->ckgroup;
			datachunknum=datachunkgroupptr->groupsize;

			curdatachunkptr=datachunkptr;
			for(k=0;k<datachunknum;k++)
			{
				index=i*cols;
				rowsindex=w*j;
				colsindex=k;
				curindex=index+rowsindex+colsindex;
				if(mat[curindex]==TRUE)//����matrix�ǲ���Ҫ����
				{
					resTF=profile_search_chunkposition_id(j,k,chunkpositionblockgroupptr);
					if(resTF==PFALSE)
					{
						resTF=profile_chunk_should_read(curdatachunkptr);
						if(resTF==TRUE)
						{
							updatelist1[i]=updatelist1[i]+1;
						}
					}
					else
					{
						resTF=profile_chunk_should_read(curdatachunkptr);
						if(resTF==TRUE)
						{
							updatelist2[i]=updatelist2[i]+1;
						}
					}
				}
				curdatachunkptr++;
			}
			curdatastrsetblockptr++;
		}
	}
	return TRUE;
}
int matrix_matrix_updateI_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition������Ҫ���µ�У����б�
										STRIPSECTBLOCKGROUP *strsetblockgroupptr,//��ǰ����������
										CHUNK *tarchunkptr,INTMATRIX *matrix,int chkindex)//Ŀ��У��飬����Ŀ�������
{
	int resTF;
	resTF=matrix_matrix_updateI_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,tarchunkptr,matrix,chkindex);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_updateI_chunk","strip can't calculate");
		return FALSE;
	}
	return TRUE;
}
int matrix_matrix_updateII_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition������Ҫ���µ�У����б�
										STRIPSECTBLOCKGROUP *strsetblockgroupptr,//��ǰ����������
										CHUNK *tarchunkptr,INTMATRIX *matrix,int chkindex)//Ŀ��У��飬����Ŀ�������
{
	int resTF;
	resTF=matrix_matrix_updateII_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,tarchunkptr,matrix,chkindex);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_updateI_chunk","strip can't calculate");
		return FALSE;
	}
	return TRUE;
}
int matrix_matrix_update_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
								STRIP *stripptr,CHUNKBLOCKGROUP *parityblockgroupptr,INTMATRIX *matrix)
{
	int i,resTF;
	STRIPSECTBLOCKGROUP *datastrsetblockgroupptr;
	STRIPSECTBLOCK *datastrsetblockptr;

	STRIPSECTBLOCKGROUP *codestrsetblockgroupptr;
	STRIPSECTBLOCK *codestrsetblockptr,*curcodestrsetblockptr;
	STRIPSECT *codestrsetptr;
	int codestrsetnum;


	CHUNKGROUP *codechunkgroupptr;
	CHUNK *codechunkptr;
	int codechunknum;

	REGION *regionptr;
	CODEPARA *codeparamptr;
	int codenum,datanum;

	int *updatelist,*updatelist1,*updatelist2;

	regionptr=stripptr->regionptr;
	codeparamptr=regionptr->codepara;

	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	//���ռ�
	datastrsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(datastrsetblockgroupptr==NULL)
	{
		show_error("matrix","matrix_update_strip","No memory");
		return FALSE;
	}

	datastrsetblockptr=talloc(STRIPSECTBLOCK,datanum);
	if(datastrsetblockptr==NULL)
	{
		show_error("matrix","matrix_update_strip","No memory");
		return FALSE;
	}
	datastrsetblockgroupptr->stripsectblockptr=datastrsetblockptr;
	datastrsetblockgroupptr->groupsize=datanum;

	codestrsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(codestrsetblockgroupptr==NULL)
	{
		show_error("matrix","matrix_update_strip","No memory");
		return FALSE;
	}

	codestrsetblockptr=talloc(STRIPSECTBLOCK,codenum);
	if(codestrsetblockptr==NULL)
	{
		show_error("matrix","matrix_update_strip","No memory");
		return FALSE;
	}
	codestrsetblockgroupptr->stripsectblockptr=codestrsetblockptr;
	codestrsetblockgroupptr->groupsize=codenum;

	resTF=profile_strip_into_stripsect_ptr(datastrsetblockgroupptr,codestrsetblockgroupptr,stripptr);
	if(resTF==FALSE)
	{
		show_error("matrix","matrix_update_strip","No memory");
		return FALSE;
	}
	updatelist=talloc(int,codenum);
	if(updatelist==NULL)
	{
		show_error("matrix","matrix_update_strip","No memory");
		return FALSE;
	}
	updatelist1=talloc(int,codenum);
	if(updatelist1==NULL)
	{
		show_error("matrix","matrix_update_strip","No memory");
		return FALSE;
	}
	updatelist2=talloc(int,codenum);
	if(updatelist2==NULL)
	{
		show_error("matrix","matrix_update_strip","No memory");
		return FALSE;
	}

	resTF=matrix_update_matrix_parity_chunklist(updatelist,chunkpositionblockgroupptr,matrix,codenum);
	if(resTF==FALSE)
	{
		show_error("matrix","matrix_update_strip","parity list can't calculate");
		return FALSE;
	}

	resTF=matrix_update_matrix_updatenum_chunklist_create(updatelist1,updatelist2,chunkpositionblockgroupptr,datastrsetblockgroupptr,matrix,codenum);
	if(resTF==FALSE)
	{
		show_error("matrix","matrix_update_strip","update count list can't calculate");
		return FALSE;
	}
	codestrsetblockptr=codestrsetblockgroupptr->stripsectblockptr;
	codestrsetnum=codestrsetblockgroupptr->groupsize;

	curcodestrsetblockptr=codestrsetblockptr;
	for(i=0;i<codestrsetnum;i++)
	{
		if(updatelist[i]==TRUE)
		{
			codestrsetptr=curcodestrsetblockptr->stripsectptr;
			codechunkgroupptr=codestrsetptr->chunklist;
			codechunkptr=codechunkgroupptr->ckgroup;
			resTF=profile_chunkblockgroup_chunk_add(parityblockgroupptr,codechunkptr);
			if(resTF==FALSE)
			{
				show_error("matrix","bitmatrix_update_strip","chunk can't add to parityblockgroup");
				return FALSE;
			}
			//�������ж�һ�µ�ǰ��chunk�ǲ�����Ҫ���ڴ��ȡ
			resTF=profile_chunk_should_read(codechunkptr);
			if(resTF==FALSE)
			{
				//�����Ҫ��ȡ
				if(updatelist1[i]<(updatelist2[i]+1))
				{
					resTF=matrix_matrix_updateI_chunk(chunkpositionblockgroupptr,datastrsetblockgroupptr,codechunkptr,matrix,i);
					if(resTF==FALSE)
					{
						show_error("matrix","matrix_update_strip","parity chunk update list can't calculate");
						return FALSE;
					}
				}
				else
				{
					resTF=matrix_matrix_updateI_chunk(chunkpositionblockgroupptr,datastrsetblockgroupptr,codechunkptr,matrix,i);
					if(resTF==FALSE)
					{
						show_error("matrix","matrix_update_strip","parity chunk update list can't calculate");
						return FALSE;
					}
				}
			}
			else
			{
				if(updatelist1[i]<updatelist2[i])
				{
					resTF=matrix_matrix_updateI_chunk(chunkpositionblockgroupptr,datastrsetblockgroupptr,codechunkptr,matrix,i);
					if(resTF==FALSE)
					{
						show_error("matrix","matrix_update_strip","parity chunk update list can't calculate");
						return FALSE;
					}
				}
				else
				{
					resTF=matrix_matrix_updateI_chunk(chunkpositionblockgroupptr,datastrsetblockgroupptr,codechunkptr,matrix,i);
					if(resTF==FALSE)
					{
						show_error("matrix","matrix_update_strip","parity chunk update list can't calculate");
						return FALSE;
					}
				}
			}
			resTF=matrix_update_matrix_updatenum_chunklist_create(updatelist1,updatelist2,chunkpositionblockgroupptr,datastrsetblockgroupptr,matrix,codenum);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_update_strip","update count list can't calculate");
				return FALSE;
			}
		}
		curcodestrsetblockptr++;
	}

	//�������ݺ�У���б�
	free(datastrsetblockgroupptr);
	free(datastrsetblockptr);
	free(codestrsetblockgroupptr);
	free(codestrsetblockptr);
	return TRUE;
}
//����bit�����share
int matrix_matrix_calculate_share(BITMATRIX *matrixptr,CODEPARA *codeptr,AONTSHAREGROUP *sharegroupptr,int sharesize)
{
//��һ��
	int datanum,codenum,totnum,w;
	int i,j,k,groupsize,chunksize,index,resTF;
	BYTE *conptr,*curconptr,*souptr;
	UINT32 *mat;
	int rows,cols;
	CHUNK *chunkptr,*curchunkptr,*tmpchunkptr;//����һ��chunkָ��
	CHUNKGROUP *chunkgroupptr;
	AONTSHARE *shareptr,*curshareptr;
	rows=matrixptr->xm;
	cols=matrixptr->ym;
	
	codenum=codeptr->codenum;
	datanum=codeptr->datanum;
	totnum=codeptr->totnum;
	w=codeptr->w;

	groupsize=datanum*w;
	chunkgroupptr=talloc(CHUNKGROUP,1);
	if(chunkgroupptr==NULL)
	{
		show_error("matrix","matrix_calculate_share","No memory");
		return FALSE;
	}

	chunkptr=talloc(CHUNK,groupsize);
	if(chunkptr==NULL)
	{
		show_error("matrix","matrix_calculate_share","No memory");
		return FALSE;
	}

	chunkgroupptr->ckgroup=chunkptr;
	curchunkptr=chunkptr;


	shareptr=sharegroupptr->sharegroupptr;
	sharesize=shareptr->sizenum;
	chunksize=sharesize/w;
	
	curshareptr=shareptr;
	//��ʼ����
	for(i=0;i<datanum;i++)
	{
		souptr=curshareptr->content;
		conptr=souptr;
		//��ʼ�������chunkgroup
		for(j=0;j<w;j++)
		{
			/*conptr=talloc(char,chunksize);//�ȸ���ռ�
			if(conptr==NULL)
			{
				show_error("matrix","matrix_calculate_share","No memory");
				return FALSE;
			}
			mcpy(conptr,souptr,char,chunksize);//��ʼ��������*/
			curchunkptr->chunkcontent=conptr;
			curchunkptr->sizenum=chunksize;
			curchunkptr++;//һ��chunk�������Ѿ�����������һ��
			conptr=conptr+chunksize;//�ƶ�һ��chunksize
		}
		
		curshareptr++;//�����Ȼ�ȡ��һ��share
	}

	//�ֻ����ڽ��г˷�
	tmpchunkptr=talloc(CHUNK,1);//������һ��chunk����ס�м���
	if(tmpchunkptr==NULL)
	{
		show_error("matrix","matrix_calculate_share","No memory");
		return FALSE;
	}
	souptr=talloc(BYTE,chunksize);//�ȸ���ռ�
	if(souptr==NULL)
	{
		show_error("matrix","matrix_calculate_share","No memory");
		return FALSE;
	}

	index=0;
	curshareptr=shareptr+datanum;
	tmpchunkptr->chunkcontent=souptr;
	tmpchunkptr->sizenum=chunksize;
	chunkptr=chunkgroupptr->ckgroup;
	mat=matrixptr->matrix;
	//���ڵ����һ���˶��ھ����ÿһ��ʹ��һ���˷�
	for(i=0;i<codenum;i++)//
	{
		conptr=curshareptr->content;
		curconptr=conptr;

		for(j=0;j<w;j++)
		{
			//��ʼһ�н�ָ��ָ���ͷ
			curchunkptr=chunkptr;
			bzero(souptr,BYTE,chunksize);//chunk����
			for(k=0;k<cols;k++)
			{
				
				if(mat[index]==1)
				{
					//����
					resTF=matrix_CHUNK_add_data(tmpchunkptr,curchunkptr);
					if(resTF==FALSE)
					{
						show_error("PAONTRS","PAONTRS_RS","XOR cannot calculate");
						return FALSE;
					}
				}
				curchunkptr++;
				index++;
				
			}
			//һ��chunk�����˿��Կ�����
			mcpy(curconptr,souptr,BYTE,chunksize);//�����ݿ���һ��
			curconptr=curconptr+chunksize;//����ƶ�һ��chunksize
		}
		curshareptr++;
	}
	chunkptr=chunkgroupptr->ckgroup;//��һ���ڴ�     
	free(chunkptr);
	free(chunkgroupptr);
	return TRUE;
}


//����
//raid-5����
int matrix_do_deparity(CHUNKGROUP* ckgroup,CHUNK *lost,int TFparity)
{
	//����raid5����ֻ����򼴿�
	int soudvnum,csize,lsize,i;
	CHUNK* chklist;
	BYTE* ldata;
	chklist=ckgroup->ckgroup;//���и�ֵ
	soudvnum=ckgroup->groupsize;
	csize=chklist->sizenum;//��ȡchunk��С
	lsize=lost->sizenum;//ʧЧ���ݽ��и�ֵ
	ldata=lost->chunkcontent;
	if(ldata==NULL)//�����ǲ���Ϊ��
	{
		//�����ڴ�
		ldata=talloc(BYTE,csize);//�ռ䲻���ڷ���֮
		if(ldata==NULL)
		{
			show_error("matrix","lost","no memory");
			return FALSE;
		}
		lost->chunkcontent=ldata;
	}
	else
	{
		if(lsize<csize)//�ռ䲻�����·���
		{
			free(ldata);//��Ϊ���ͷ�
			if(ldata==NULL)
			{
				show_error("matrix","lost","no memory");
				return FALSE;
			}
			ldata=talloc(BYTE,csize);//����洢�ռ�
			lost->chunkcontent=ldata;//���¸�ֵ��ȥ
		}
	}
	matrix_CHUNK_copy_data(lost,chklist);//ͳͳ��򼴿�
	for(i=1;i<soudvnum;i++)
	{
		//�������
		chklist++;
		matrix_CHUNK_add_data(lost,chklist);
	}
	lost->isparity=TFparity;
	lost->regionid=chklist->regionid;
	lost->sizenum=chklist->sizenum;
	lost->stripid=chklist->stripid;//��Ȼ�е���൫��Ϊ�˰�ȫ
	return TRUE;
}
//matrix����
int matrix_matrix_decode(CHUNKGROUP *lostgroup,CHUNKGROUP *ckgroup,INTMATRIX *matrix,ERASES *erarray)//
{
	//����erase��matrix�е����ݣ��ָ���ʧ���ݿ�
	int i,lsizenum,chknum,rows,cols,w;//��Ҫ��ȡ����
	int *erarr,codenum,datanum,totnum;
	CHUNK *chklist,*lostlist;
	UINT32 *mat;

	//��ʼ��ȡ����
	mat=matrix->matrix;
	w=matrix->w;
	rows=matrix->xm;
	cols=matrix->ym;

	lostlist=lostgroup->ckgroup;
	lsizenum=lostgroup->groupsize;

	chklist=ckgroup->ckgroup;
	chknum=ckgroup->groupsize;

	erarr=erarray->erases;
	codenum=erarray->codenum;
	datanum=erarray->datanum;
	totnum=erarray->totnum;

	//����һͨ�Ϸ��Լ��
	if(w!=8&&w!=16&&w!=32)
	{
		show_error("matrix","matrix decoder","w is illegal");
		return FALSE;
	}
	if(erarr==NULL)
	{
		show_error("matrix","matrix decoder","erarr==NULL");
		return FALSE;
	}
	if(mat==NULL)
	{
		show_error("matrix","matrix decoder","mat==NULL");
		return FALSE;
	}
	if(chklist==NULL)
	{
		show_error("matrix","matrix decoder","souchunk==NULL");
		return FALSE;
	}
	if(lostlist!=NULL)
	{
		free(lostlist);
	}
	lostlist=talloc(CHUNK,codenum);//���ɿռ�
	if(lostlist==NULL)
	{
		show_error("matrix","matrix decoder","No memory");
		return FALSE;
	}
	return TRUE;
}
//BLOCK����������
int matrix_matrix_decode_BLOCK(CHUNKBLOCKGROUP *lostgroup,CHUNKBLOCKGROUP *ckgroup,INTMATRIX *matrix,ERASES *erarry)
{
	//����erase��matrix�е����ݣ��ָ���ʧ���ݿ�
	int i,lsizenum,chknum,rows,cols,w,resTF;//��Ҫ��ȡ����
	int *erarr,codenum,datanum,totnum;
	CHUNKBLOCKGROUP *eraseblockgroupptr;
	CHUNKBLOCK *datachunkblockptr,*lostchunkblockptr;
	CHUNK *datachunkptr,*lostchunkptr;
	INTMATRIX *dematrix;
	DM_IDS *dmids;
	UINT32 *mat;

	//��ʼ��ȡ����
	mat=matrix->matrix;
	w=matrix->w;
	rows=matrix->xm;
	cols=matrix->ym;

	lostchunkblockptr=lostgroup->chunkblockptr;
	lsizenum=lostgroup->groupsize;

	datachunkblockptr=ckgroup->chunkblockptr;
	chknum=ckgroup->groupsize;

	erarr=erarry->erases;
	datanum=erarry->datanum;
	codenum=erarry->codenum;
	totnum=erarry->totnum;
	//����һͨ�Ϸ��Լ��
	if(w!=8&&w!=16&&w!=32)
	{
		show_error("matrix","matrix decoder","w is illegal");
		return FALSE;
	}
	if(erarr==NULL)
	{
		show_error("matrix","matrix decoder","erarr==NULL");
		return FALSE;
	}
	if(mat==NULL)
	{
		show_error("matrix","matrix decoder","mat==NULL");
		return FALSE;
	}
	if(datachunkblockptr==NULL)
	{
		show_error("matrix","matrix decoder","souchunk==NULL");
		return FALSE;
	}
	dematrix=talloc(INTMATRIX,1);
	if(dematrix==NULL)
	{
		show_error("matrix","matrix decoder","No memory");
		return FALSE;
	}
	//���������
	resTF=matrix_make_decoding_matrix_only(dematrix,matrix,erarry);
	if(resTF==FALSE)
	{
		show_error("matrix","matrix_decode_BLOCK","decoding matrix can't create");
		return FALSE;
	}
	eraseblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(eraseblockgroupptr==NULL)
	{
		show_error("matrix","matrix decoder","No memory");
		return FALSE;
	}
	eraseblockgroupptr->chunkblockptr=NULL;
	eraseblockgroupptr->groupsize=datanum;
	//���������ɾ��
	resTF=matrix_make_decoding_chunkblockgroup(eraseblockgroupptr,ckgroup,erarry);
	if(resTF==FALSE)
	{
		show_error("matrix","matrix decoder","error group can't ");
		return FALSE;
	}
	return TRUE;
}
int matrix_bitmatrix_decode(CHUNKGROUP *lostgroup,CHUNKGROUP *ckgroup,BITMATRIX *matrix,ERASES *erarray)
{
	return TRUE;
}
;//BLOCK����У��
int matrix_bitmatrix_encode_BLOCK(CHUNKBLOCKGROUP *pargroup,CHUNKBLOCKGROUP *ckgroup,BITMATRIX *matrix,int packetsize)
{
	return TRUE;
}

//scheudle���뷽��
int matrix_schedule_decode_lazy()
{
	return TRUE;
}
int matrix_schedule_decode_cache()
{
	return TRUE;
}
int matrix_make_decoding_matrix_only(INTMATRIX *decoding_matrix,INTMATRIX *matrix,ERASES *erarray)
{
	DM_IDS *dmids=NULL;
	int resTF;
	/*dmids=talloc(DM_IDS,1);
	if(dmids==NULL)
	{
		show_error("matrix","make_decoding_matrix_only","No memory");
		return FALSE;
	}*/
	resTF=matrix_make_decoding_matrix(decoding_matrix,matrix,erarray,dmids);
	if(resTF==FALSE)
	{
		show_error("matrix","make_decoding_matrix_only","decode matrix can't create");
		return FALSE;
	}
	free(dmids);
	return TRUE;
}
//������Ӧ�������
int matrix_make_decoding_matrix(INTMATRIX *decoding_matrix,INTMATRIX *matrix,ERASES *erarray,DM_IDS *dmids)
{
	//����һ���������
	int i,j,w,rows,cols,drows,dcols,datanum,codenum,totnum,dmnum,resTF;
	UINT32 *mat,*dmat;
	int *erar,*dmi;
	
	//������ȥ����
	INTMATRIX eramatrix;

	//�����þ���Ҫ����
	//INTMATRIX testmatrix,testmatrix1;
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	dmat=decoding_matrix->matrix;//�Ƚ���һ��֮�����ȥ����
	drows=decoding_matrix->xm;
	dcols=decoding_matrix->ym;

	erar=erarray->erases;
	codenum=erarray->codenum;
	datanum=erarray->datanum;
	totnum=erarray->totnum;

	dmi=dmids->dm_ids;
	dmnum=dmids->size;
	if(w!=8&&w!=16&&w!=32)
	{
		show_error("matrix","make_decoding_matrix","w is illegal");
		return FALSE;
	}
	if(datanum!=cols)//�����������Ҫ����
	{
		show_error("matrix","make_decoding_matrix","datanum!=cols");
		return FALSE;
	}
	if(mat==NULL)
	{
		show_error("matrix","make_decoding_matrix","mat==NULL");
		return FALSE;
	}
	if(erar==NULL)
	{
		show_error("matrix","make_decoding_matrix","erase==NULL");
		return FALSE;
	}
	//�ж�Ŀ��ռ����
	if(dmat!=NULL)//�ͷ�decoding_matrix
	{
		free(dmat);
	}
	dmat=talloc(UINT32,cols*cols);//���ռ�����������������cols*cols
	if(dmat==NULL)
	{
		show_error("matrix","make_decoding_matrix","No memory");
		return FALSE;
	}
	//decoding_matrix->matrix=dmat;
	//��eramatrix�����ݸ�ֵ
	matrix_set_data(&eramatrix,dmat,cols,cols,w);
	//���ɳ���k�ı���array
	if(dmi!=NULL)
	{
		free(dmi);
	}
	dmi=talloc(int,datanum);//ʹ��������޽������
	if(dmi==NULL)
	{
		show_error("matrix","make_decoding_matrix","NO memory");
		return FALSE;
	}
	dmids->dm_ids=dmi;//�������¸�ֵ
	//���Կ�ʼ����dm_ids
	j=0;//��j��0
	for(i=0;j<datanum;i++)
	{
		if(erar[i]==FALSE)//��ǰ�豸����
		{
			dmi[j]=i;
			j++;
		}
		if(i>totnum)//���������ű���û���㹻������
		{
			show_error("matrix","make_decoding_bitmatrix","erases is illegal");
			return FALSE;
		}
	}
	dmnum=j;
	dmids->size=j;
	for(i=0;i<dmnum;i++)//��ʼ������ȥ�ľ���
	{
		if(dmi[i]<datanum)//���ж��ǲ��Ǳ����
		{
			for(j=0;j<datanum;j++)
			{
				dmat[i*cols+j]=0;
			}
			dmat[i*cols+dmi[i]]=1;
		}
		else
		{
			for(j=0;j<cols;j++)
			{
				dmat[i*cols+j]=mat[(dmi[i]-datanum)*cols+j];//�����ڱ������е�λ�ò���ֵ
			}
		}
	}
	//������������
	//matrix_print_matrix(&eramatrix);
	//testmatrix1=matrix_duplicate(&eramatrix);
	resTF=matrix_invert(&eramatrix,decoding_matrix);//������������
	//����һ���ǲ���ΪE
	//matrix_set_data(&testmatrix,NULL,cols,cols,w);
	//matrix_matrix_multiply(decoding_matrix,&testmatrix1,&testmatrix);
	//matrix_print_matrix(&testmatrix);
	if(resTF==FALSE)
	{
		show_error("matrix","make_decoding_bitmatrix","matrix invertable");
		return FALSE;
	}
	return TRUE;
}
int matrix_make_decoding_bitmatrix(BITMATRIX *decoding_matrix,BITMATRIX *matrix,ERASES *erarray,DM_IDS *dmids)
{
	int i,j,rows,cols,w,drows,dcols,codenum,datanum,totnum,dmnum,index,mindex,resTF;
	int *erar,*dmi;
	UINT32 *mat,*dmat;

	//������ɾ����
	BITMATRIX eramatrix;//������һ��
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	dmat=decoding_matrix->matrix;
	drows=decoding_matrix->xm;
	dcols=decoding_matrix->ym;

	erar=erarray->erases;
	codenum=erarray->codenum;
	datanum=erarray->datanum;
	totnum=erarray->totnum;
	
	dmi=dmids->dm_ids;
	dmnum=dmids->size;
	//��ȫ�Լ��
	if((datanum*w)!=cols)
	{
		show_error("matrix","make_decoding_bitmatrix","cols should equal to datanum*w");
		return  FALSE;
	}
	if(mat==NULL)
	{
		show_error("matrix","make_decoding_bitmatrix","mat==NULL");
		return FALSE;
	}
	if(erar==NULL)
	{
		show_error("matrix","make_decoding_bitmatrix","erase==NULL");
		return FALSE;
	}
	//��ʼ����ռ�
	if(dmat!=NULL)
	{
		free(dmat);
	}
	dmat=talloc(UINT32,cols*cols);
	if(dmat==NULL)//û�пռ�
	{
		show_error("matrix","make_decoding_bitmatrix","NO memory");
		return FALSE;
	}
	matrix_set_data(&eramatrix,dmat,cols,cols,w);//��ɾ�����趨��ֵ
	//dm_ids����ռ�
	if(dmi!=NULL)
	{
		free(dmi);
	}
	dmi=talloc(int,datanum);
	if(dmi==NULL)
	{
		show_error("matrix","make_decoding_bitmatrix","NO memory");
		return FALSE;
	}
	//�����Ͽ��Կ�ʼ������ɾ������
	j=0;
	for(i=0;j<datanum;i++)
	{
		if(erar[i]==FALSE)
		{
			dmi[j]=i;
			j++;
		}
		if(i>totnum)
		{
			show_error("matrix","make_decoding_bitmatrix","erases is illegal");
			return FALSE;
		}
	}
	dmnum=j;
	dmids->size=dmnum;
	//׼������������ɿ�ʼ���ɾ�ɾ����
	for(i=0;i<datanum;i++)
	{
		if(dmi[i]<datanum)//��ǰ��λ��������������
		{
			//��Ҫ�������б��ָ���ĵ�λ��
			index=i*cols*w;//��λ����ǰ��
			for(j=0;j<cols*w;j++)//����֮���w�н��и�ֵ
			{
				dmat[index+j]=0;//��ֵ0
			}
			index=i*cols*w+dmi[w]*w;//��λ����ǰλ��
			for(j=0;j<w;j++)
			{
				dmat[index]=1;
				index+=(cols+1);
			}
		}
		else
		{
			//���������ݸ�ֵ
			index=i*cols*w;//��λ��ǰλ��
			mindex=(dmi[i]-datanum)*cols*w;//��λ�������λ��
			for(j=0;j<cols*w;j++)
			{
				dmat[index+j]=mat[mindex+j];
			}
		}
	}
	resTF=matrix_invert_bitmatrix(&eramatrix,decoding_matrix);
	if(resTF==FALSE)
	{
		show_error("matrix","make_decoding_bitmatrix","");
		return FALSE;
	}
	return TRUE;
}

//��˴�ȫ//����һ��chunk����
//����parchunkΪ���
int matrix_matrix_dotprod_BLOCK(INTMATRIX *matrix,CHUNKBLOCKGROUP *ckgroup,CHUNK *parchunk,DOTINF *dotin)
{
	//���о��������ݿ�
	UINT32 *mat;

	int i,w,linenum,chknum,rows,cols,colsnum,srcindex,chksize,parityTF,multindex;
	//UINT64 regionid,stripid;
	UINT32 multby;
	int *srcids,resTF;

	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *chunkptr;
	BYTE *newptr;
	//��ȡ����
	mat=matrix->matrix;
	w=matrix->w;
	rows=matrix->xm;
	cols=matrix->ym;
	
	srcids=dotin->src_ids;
	colsnum=dotin->colsnum;//��Ҫ���м���ľ�������rows��group����cols
	linenum=dotin->linenum;//��Ҫ����ľ�������
	parityTF=dotin->parityTF;//��ȡ�ǲ���parityTF
	//��ʼ����BLOCK���и�ֵ
	chknum=ckgroup->groupsize;
	chunkblockptr=ckgroup->chunkblockptr;
	
	if(w!=8&&w!=16&&w!=32)
	{
		show_error("matrix","dotprod","w is illegal");
		return FALSE;
	}
	if(colsnum!=rows)
	{
		//������޷����
		show_error("matrix","dotprot","rowes!=cols");
		return FALSE;
	}
	//�������
	
	newptr=parchunk->chunkcontent;
	if(newptr!=NULL)
	{
		free(newptr);
	}
	chksize=parchunk->sizenum;//��ȡ��С
	newptr=talloc(BYTE,chksize);//����ռ�

	parchunk->chunkcontent=newptr;
	//��һ���ȿ�����һ����
	curchunkblockptr=chunkblockptr;
	chunkptr=curchunkblockptr->chunkptr;
	resTF=matrix_CHUNK_copy_data(parchunk,chunkptr);//��������
	if(resTF==FALSE)
	{
		show_error("matrix","matrix_dotprod_BLOCK","chunkdata can't copy");
		return FALSE;
	}
	for(i=1;i<chknum;i++)//�����һ���Ѿ�����
	{
		if(srcids==NULL)//��Ҫȫ������
		{
			curchunkblockptr++;
			chunkptr=curchunkblockptr->chunkptr;
			if(mat[linenum*rows+i]==1)//ֱ�����
			{
				matrix_CHUNK_add_data(parchunk,chunkptr);
			}
			else//��Ҫ�˷�
			{
				multindex=rows*linenum+i;//������Ҫ�����λ��
				multby=mat[multindex];
				switch(w)//����w������Ӧ����ֵ
				{
				case 8:
					matrix_CHUNK_w08_multiply_add(parchunk,chunkptr,multby);
					break;
				case 16:
					matrix_CHUNK_w16_multiply_add(parchunk,chunkptr,multby);
					break;
				case 32:
					matrix_CHUNK_w32_multiply_add(parchunk,chunkptr,multby);
					break;
				}
			}
		}
		else
		{
			//�϶�Ҫ�ȶ�λ
			srcindex=srcids[i];
			//����˷�
			curchunkblockptr=chunkblockptr+srcindex;//���¶�λ
			chunkptr=curchunkblockptr->chunkptr;
			if(mat[linenum*rows+i]==1)//ֱ�����
			{
				
				matrix_CHUNK_add_data(parchunk,chunkptr);//�����ۼ�
			}
			else//��Ҫ�˷�
			{
				switch(w)//����w������Ӧ����ֵ
				{
				case 8:
					matrix_CHUNK_w08_multiply_add(parchunk,chunkptr,multby);
					break;
				case 16:
					matrix_CHUNK_w16_multiply_add(parchunk,chunkptr,multby);
					break;
				case 32:
					matrix_CHUNK_w32_multiply_add(parchunk,chunkptr,multby);
					break;
				}
			}
		}
		
	}
	return TRUE;
}

//����erases����
int matrix_make_decoding_chunkblockgroup(CHUNKBLOCKGROUP *tarchunkptr,CHUNKBLOCKGROUP *souchunpptr,ERASES *erarry)
{
	int *err;
	int i,codenum,datanum,totnum;
	int sousize,tarsize;

	CHUNKBLOCK *tarblockptr,*curtarblockptr;
	CHUNKBLOCK *soublockptr,*cursoublockptr;

	err=erarry->erases;
	totnum=erarry->totnum;
	codenum=erarry->codenum;
	datanum=erarry->datanum;

	tarsize=tarchunkptr->groupsize;
	tarblockptr=tarchunkptr->chunkblockptr;

	sousize=souchunpptr->groupsize;
	soublockptr=souchunpptr->chunkblockptr;
	if(sousize!=totnum)
	{
		show_error("matrix","make_decoding_chunkblockgroup","");
		return FALSE;
	}
	if(souchunpptr==NULL)
	{
		show_error("matrix","make_decoding_chunkblockgroup","source chunkptr is NULL");
		return FALSE;
	}
	
	if(tarblockptr!=NULL)
	{
		free(tarblockptr);
	}
	tarblockptr=talloc(CHUNKBLOCK,datanum);
	if(tarchunkptr==NULL)
	{
		show_error("matrix","make_decoding_chunkblockgroup","No memory");
		return FALSE;
	}
	tarchunkptr->chunkblockptr=tarblockptr;
	tarchunkptr->groupsize=datanum;

	curtarblockptr=tarblockptr;
	cursoublockptr=soublockptr;
	for(i=0;i<sousize;i++)
	{
		//��������
		if(err[i]==FALSE)//�����ݸ���
		{
			curtarblockptr->chunkptr=cursoublockptr->chunkptr;
			curtarblockptr->chunkid=cursoublockptr->chunkid;
		}
		curtarblockptr++;
		cursoublockptr++;
	}
	return TRUE;
}

int matrix_matrix_dotprod(INTMATRIX *matrix,CHUNKGROUP *chkgroup,CHUNK *parchunk,DOTINF *dotin)//�������plankʵ��,һ��һ����
{
	//���о��������ݿ�
	UINT32 *mat;

	int i,w,linenum,chknum,rows,cols,colsnum,srcindex,chksize,parityTF,multindex;
	//UINT64 regionid,stripid;
	UINT32 multby;
	int *srcids;
	CHUNK *chklist;
	BYTE *newptr;
	//��ȡ����
	mat=matrix->matrix;
	w=matrix->w;
	rows=matrix->xm;
	cols=matrix->ym;
	
	srcids=dotin->src_ids;
	colsnum=dotin->colsnum;//��Ҫ���м���ľ�������rows��group����cols
	linenum=dotin->linenum;//��Ҫ����ľ�������
	parityTF=dotin->parityTF;//��ȡ�ǲ���parityTF
	
	chknum=chkgroup->groupsize;//chunk��
	chklist=chkgroup->ckgroup;//��ȡchunk�б�
	chksize=chklist->sizenum;//ÿһ�����С
	//regionid=chklist->regionid;//��ȡregionid
	//stripid=chklist->stripid;//��ȡstripid

	if(w!=8&&w!=16&&w!=32)
	{
		show_error("matrix","dotprod","w is illegal");
		return FALSE;
	}
	if(colsnum!=rows)
	{
		//������޷����
		show_error("matrix","dotprot","rowes!=cols");
		return FALSE;
	}
	newptr=parchunk->chunkcontent;
	//���paritychunk��ָ�����
	if(newptr!=NULL)
	{
		free(newptr);
	}
	newptr=talloc(BYTE,chksize);//ֻ��Ҫ���з��伴��
	if(newptr==NULL)
	{
		show_error("matrix","dotprot","no memory");
		return FALSE;
	}
	//Ϊ��ͳһ���������ֽ�����ͳһΪ0
	for(i=0;i<chksize;i++)
	{
		newptr[i]=0;
	}
	parchunk->chunkcontent=newptr;
	//parchunk->isparity=parityTF;//��Ҫdotinf��ȡ
	//parchunk->regionid=regionid;
	//parchunk->sizenum=chksize;
	//parchunk->stripid=stripid;
	//������һ��ʼ����
	for(i=0;i<colsnum;i++)//��Ϊ�ڼ��������srcid��ֵ����������迼��chklistָ������
	{
		if(srcids==NULL)//ȫ������
		{
			if(mat[linenum*rows+i]==1)//ֱ�����
			{
				matrix_CHUNK_add_data(parchunk,chklist);
			}
			else//��Ҫ�˷�
			{
				multindex=rows*linenum+i;//������Ҫ�����λ��
				multby=mat[multindex];
				switch(w)//����w������Ӧ����ֵ
				{
				case 8:
					matrix_CHUNK_w08_multiply_add(parchunk,chklist,multby);
					break;
				case 16:
					matrix_CHUNK_w16_multiply_add(parchunk,chklist,multby);
					break;
				case 32:
					matrix_CHUNK_w32_multiply_add(parchunk,chklist,multby);
					break;
				}
			}
			chklist++;//ת����һ��chunk
		}
		else//��Ҫsrcids��λ
		{
			//�϶�Ҫ�ȶ�λ
			srcindex=srcids[i];
			//����˷�
			chklist=chkgroup->ckgroup+srcindex;//���¶�λ
			if(mat[linenum*rows+i]==1)//ֱ�����
			{
				
				matrix_CHUNK_add_data(parchunk,chklist);//�����ۼ�
			}
			else//��Ҫ�˷�
			{
				switch(w)//����w������Ӧ����ֵ
				{
				case 8:
					matrix_CHUNK_w08_multiply_add(parchunk,chklist,multby);
					break;
				case 16:
					matrix_CHUNK_w16_multiply_add(parchunk,chklist,multby);
					break;
				case 32:
					matrix_CHUNK_w32_multiply_add(parchunk,chklist,multby);
					break;
				}
			}
		}
	}
	return TRUE;
}

int matrix_bitmatrix_dotprod_BLOCK(BITMATRIX *matrix,CHUNKBLOCKGROUP *ckgroup,CHUNK *parchunk,DOTINF *dotin)
{
	//��ȡ����
	int x,y,j,w,datanum,linenum,rows,cols,colsnum,parityTF,chksize,chknum,packetsize,sindex,index,pstarted,tindex;
	//UINT64 regionid,stripid;
	BITMATRIX *mat;
	int *srcids;
	CHUNK *chklist;
	BYTE *dptr,*pptr,*bdptr,*bpptr;//�ȶ���һ����ָ��


	return TRUE;
}

int matrix_bitmatrix_dotprod(BITMATRIX *matrix,CHUNKGROUP *chkgroup,CHUNK *parchunk,DOTINF *dotin)//���ﻹ����Plank��ʦ�ķ�����bit�������ҵĴ�chunk����Ϊ��
{
	//��ȡ����
	int x,y,j,w,datanum,linenum,rows,cols,colsnum,parityTF,chksize,chknum,packetsize,sindex,index,pstarted,tindex;
	//UINT64 regionid,stripid;
	UINT32 *mat;
	int *srcids;
	CHUNK *chklist;
	BYTE *dptr,*pptr,*bdptr,*bpptr;//�ȶ���һ����ָ��
	
	srcids=dotin->src_ids;
	linenum=dotin->linenum;
	colsnum=dotin->colsnum;
	packetsize=dotin->packetsize;
	parityTF=dotin->parityTF;

	chklist=chkgroup->ckgroup;
	chknum=chkgroup->groupsize;
	
	//regionid=chklist->regionid;
	//stripid=chklist->stripid;
	chksize=chklist->sizenum;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;
	//��Ϊ��Ҫʹ��cauchy������ﲻ��w�Ϸ��Լ��
	//��Ҫ���С�Ƿ�Ϸ�
	if(chksize%(w*packetsize)!=0)
	{
		show_error("matrix","bitmatrix_dotprod","chksize%(w*packetsize)!=0");
		return FALSE;
	}
	//�趨Ŀ��ָ��
	bpptr=parchunk->chunkcontent;//�趨Ŀ��ָ��������Ϯplank��ʦ��������ʽ��p�Ʋ���parity����˼
	if(bpptr!=NULL)
	{
		//ԭ����һ�㲻��
		free(bpptr);
	}
	bpptr=talloc(BYTE,chksize);//���ɴ洢�ռ�
	if(bpptr==NULL)
	{
		show_error("matrix","bitmatrix_dotprod","No memory");
		return FALSE;
	}
	parchunk->chunkcontent=bpptr;//��ָ����
	for(sindex=0;sindex<chksize;sindex+=(packetsize*w))
	{
		index=0;
		for(j=0;j<w;j++)//����ÿһ����Ƭ�м������
		{
			pstarted=0;
			pptr=bpptr+sindex+j*packetsize;//���㵱ǰĿ��λ�õ�ƫ����
			for(x=0;x<colsnum;x++)
			{
				if(srcids==NULL)//���������
				{
					bdptr=chklist[x].chunkcontent;//ָ��Դ����
				}
				else
				{
					tindex=srcids[x];//Ŀ�����ݿ�
					bdptr=chklist[tindex].chunkcontent;//ָ��Դ����
				}
				for(y=0;y<w;y++)
				{
					dptr=bdptr+sindex+y*packetsize;
					if(!pstarted)
					{
						memcpy(pptr,dptr,packetsize);//��ʼʱֻ�����copy
						set_state_memcpynum_add(packetsize);
					}
					else
					{
						galois_region_xor(dptr,pptr,dptr,packetsize);
						set_state_xor_add(packetsize);
					}
				}
			}
		}
	}
	return TRUE;
}

int matrix_do_scheduled_operations()//����һ��Schedule����
{
	return TRUE;
}
//����matrix bitmatrix��scheduleת��
int matrix_matrix_to_bitmatrix(INTMATRIX *matrix,BITMATRIX *bitmatrix)//��INTMATRIX����һ��BITMATRIX
{
	UINT32 *bitmat,*mat;
	int rowelts,rowindex,colindex,elt,i,j,m,k,w,l,x;
	//int dm,dk,ssize,dsize;
	bitmat=bitmatrix->matrix;
	m=matrix->xm;
	k=matrix->ym;
	w=matrix->w;
	if(bitmat==NULL)
	{
		bitmat=talloc(UINT32,(k*m*w*w));//�����С����ռ����˷ѣ�����������Ҫ����
		if(matrix==NULL) 
		{
			show_error("matrix","matrix_to_bitmatrix","No memory");
			return FALSE;
		}
	}
	mat=matrix->matrix;
	if(mat==NULL)
	{
		show_error("matrix","matrix_to_bitmatrix","int matrix is NULL");
		return FALSE;
	}
	rowelts=k*w;//������κ��б�
	rowindex=0;

	for(i=0;i<m;i++)
	{
		colindex=rowindex;
		for(j=0;j<k;j++)
		{
			elt=mat[i*k+j];//��Ҫת����Ԫ��
			for(x=0;x<w;x++)
			{
				for(l=0;l<w;l++)
				{
					bitmat[colindex+x+l*rowelts]=((elt&1<<l)?1:0);
				}
				elt=galois_single_multiply(elt,2,w);
			}
			colindex+=w;//������һ����
		}
		rowindex+=rowelts*w;
	}
	//���¸�ֵ
	bitmatrix->matrix=bitmat;
	bitmatrix->xm=m*w;
	bitmatrix->ym=k*w;
	bitmatrix->w=w;//���¸�ֵ
	return TRUE;
}

extern int matrix_dumb_bitmatrix_to_schedule(BITMATRIX *matrix,SCHEDULE *sch)//����ת������
{
	SCHEDOP *schop;
	int i,j,paranum,schsize,optodo,index;
	int rows,cols,w;
	UINT32 *mat;
	//��ȡ����
	mat=matrix->matrix;
	w=matrix->w;
	rows=matrix->xm;
	cols=matrix->ym;
	paranum=rows;//���Ǽ����Ǳ�����

	schop=sch->schedlist;
	schsize=sch->size;
	if(rows<cols)
	{
		show_error("matrix","dumb_bitmatrix_to_schedule","rows<cols");
		return FALSE;
	}
	//rows-cols;
	if(mat==NULL)
	{
		show_error("matrix","dumb_bitmatrix_to_schedule","mat==NUL");
		return FALSE;
	}
	
	if(schop!=NULL)
	{
		free(schop);
	}
	schop=talloc(SCHEDOP,rows*paranum*w*w+1);//�����Ҫ�Ŀռ�
	//����ռ�
	//��һ������ռ������ܵĲ�����rows*cols*w*w
	if(schop==NULL)
	{
		show_error("matrix","dumb_bitmatrix_to_schedule","No memory");
		return FALSE;
	}
	sch->schedlist=schop;
	index=0;
	for(i=0;i<(paranum*w);i++)
	{
		optodo=0;//��һ����copy
		for(j=0;j<(cols*w);j++)
		{
			if(mat[index]==1)//�����Ҫ����
			{
				matrix_SCHUDOP_set_data(schop,optodo,j/w,j%w,cols+i/w,i%w,FALSE,NULL,0);
				optodo=1;
				schop++;
			}
			index++;
		}
	}
	//���w���ݸ���
	sch->w=w;
	return TRUE;
	
}
int matrix_smart_bitmatrix_to_schedule(BITMATRIX *matrix,SCHEDULE *sch)
{
	SCHEDOP *schop;
	int paranum,schsize;
	int rows,cols,w;
	UINT32 *mat;
	//��ȡ����
	mat=matrix->matrix;
	w=matrix->w;
	rows=matrix->xm;
	cols=matrix->ym;
	paranum=rows-cols;

	schop=sch->schedlist;
	schsize=sch->size;
	if(rows<cols)
	{
		show_error("matrix","dumb_bitmatrix_to_schedule","rows<cols");
		return FALSE;
	}
	//rows-cols;
	if(mat==NULL)
	{
		show_error("matrix","dumb_bitmatrix_to_schedule","mat==NUL");
		return FALSE;
	}
	
	if(schop!=NULL)
	{
		free(schop);
	}
	schop=talloc(SCHEDOP,rows*paranum*w*w+1);//�����Ҫ�Ŀռ�
	//����ռ�
	//��һ������ռ������ܵĲ�����rows*cols*w*w
	if(schop==NULL)
	{
		show_error("matrix","dumb_bitmatrix_to_schedule","No memory");
		return FALSE;
	}
	return TRUE;
}
//����ͳ��
int matrix_get_stats(STATSITEM *fill_in)
{
	//��ȡϵͳͳ������
	fill_in=&systemstatic;//�򵥷���ָ��
	return TRUE;
}

//������Ӧ��schedule











