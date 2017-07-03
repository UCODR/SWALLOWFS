//这里主要实现int矩阵，因为编解码一般不涉及到浮点数
#include "matrix.h"
//统计当前矩阵中1的个数
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
//统计当前矩阵中0的个数
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


INTMATRIX matrix_create_w08(UINT32 *matrix,int rows,int cols)//生成相应8位，进行mat赋值上去,c无法处理二维函数传递只能一维
{
	INTMATRIX res;
	res.matrix=(UINT32 *)matrix;
	res.w=8;
	res.xm=rows;
	res.ym=cols;
	return res;
	//for(i=0;i<;i++)
}
INTMATRIX matrix_create_w16(UINT32 *matrix,int rows,int cols)//生成16位
{
	INTMATRIX res;
	res.matrix=(UINT32 *)matrix;
	res.w=16;
	res.xm=rows;
	res.ym=cols;
	return res;
}
INTMATRIX matrix_create_w32(UINT32 *matrix,int rows,int cols)//生成32位
{
	INTMATRIX res;
	res.matrix=matrix;
	res.w=32;
	res.xm=rows;
	res.ym=cols;
	return res;
}

INTMATRIX matrix_create_NULL()//创建一个空的INTMATRIX
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
int matrix_set_data(INTMATRIX *matrix,UINT32 *mat,int rows,int cols,int w)//设定数
{
	matrix->matrix=mat;
	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w=w;
	return TRUE;
}
INTMATRIX matrix_duplicate(INTMATRIX *matrix)//复制矩阵
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
	//拷贝矩阵数据
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
int matrix_destroy(INTMATRIX *matrix)//销毁一个矩阵
{
	free(matrix->matrix);
	matrix->matrix=NULL;
	matrix->w=NOSIZE;
	matrix->xm=NOSIZE;
	matrix->ym=NOSIZE;
	return TRUE;
}
void matrix_print_matrix_outcheck(INTMATRIX *matrix)//显示10进制相应矩阵内容,其中w为相应的字长
{
	int i,j,fw,w;
	char s[30];
	unsigned int w2;
	int rows,cols;
	int *mat;
	mat=matrix->matrix;
	w=matrix->w;
	rows=matrix->xm;//先将行列数据读出
	cols=matrix->ym;
	if(w==32)
	{
		fw=11;//32位统一显示为11位
	}
	else
	{
		w2=(1<<w);
		sprintf(s,"%u",w2-1);
		fw=strlen(s)+1;//多加1位
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
void matrix_print_matrix(INTMATRIX *matrix)//显示10进制相应矩阵内容,其中w为相应的字长
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
	rows=matrix->xm;//先将行列数据读出
	cols=matrix->ym;
	//mat=matrix.matrix;
	if(w!=8&&w!=16&&w!=32)
	{
		show_error("matrix","w","outofrage");
		return;
	}
	//根据域大小变化指针
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
	}*///最后还是用共用体
	if(w==32)
	{
		fw=11;//32位统一显示为11位
	}
	else
	{
		w2=(1<<w);
		sprintf(s,"%u",w2-1);
		fw=strlen(s)+1;//多加1位
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
			}*///*号下一个参数width
		}
		printf("\n");
	}
}
void matrix_print_16Xmatrix(INTMATRIX *matrix)//显示16进制相应矩阵内容,其中w为相应的字长
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
	rows=matrix->xm;//先将行列数据读出
	cols=matrix->ym;
	//mat=matrix.matrix;
	if(w!=8&&w!=16&&w!=32)
	{
		show_error("matrix","w","outofrage");
		return;
	}
	//根据域大小变化指针
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
		fw=9;//32位统一显示为9位
	}
	else
	{
		w2=(1<<w);
		sprintf(s,"%X",w2-1);
		fw=strlen(s)+1;//多加1位
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
			}*///*号下一个参数width
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

int matrix_invert(INTMATRIX *matrix,INTMATRIX *invmatrix)//实现逆矩阵
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
	if(cols!=rows)//如果行不等于列直接返回
	{
		show_error("matrix","invert","rows!=cols");
		return FALSE;
	}
	if(invmatrix->matrix==NULL||(dsize<ssize))//看看目标矩阵是不是为空,或是空间是否够用
	{
		inv=(UINT32 *)malloc(sizeof(UINT32)*rows*cols);
	}
	else
	{
		//够用用原来的空间
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
	//转化为上三角阵
	for(i=0;i<cols;i++)
	{
		row_start=cols*i;
		//化简后对角i,i如果为0，那么不可逆
		if(mat[row_start+i]==0)
		{
			for(j=i+1;j<rows&&mat[cols*j+i]==0;j++) ;//搜索不是0的
			if(j==rows) return FALSE;//搜索到最后还没有返回FALSE
			rs2=j*cols;
			for(k=0;k<cols;k++)//找到后交换两行所有的元素
			{
				//同步更新
				tmp=mat[row_start+k];
				mat[row_start+k]=mat[rs2+k];
				mat[rs2+k]=tmp;
				tmp=inv[row_start+k];
				inv[row_start+k]=inv[rs2+k];
				inv[rs2+k]=tmp;
			}
		}
		
		tmp=mat[row_start+i];
		//需要*(i,i)的逆元化为1
		if(tmp!=1)
		{
			inverse=galois_inverse(tmp,w);
			for(j=0;j<cols;j++)//计算mat和相应的逆矩阵
			{
				mat[row_start+j]=galois_single_multiply(mat[row_start+j],inverse,w);
				inv[row_start+j]=galois_single_multiply(inv[row_start+j],inverse,w);
			}
		}
		//所有的j>i,进行乘加
		k=row_start+i;
		for(j=i+1;j!=cols;j++)
		{
			k+=cols;
			if(mat[k]!=0)//如果不为0则要消减
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
					tmp=mat[k];//当前需要进行乘法的元素
					rs2=cols*j;
					for(x=0;x<cols;x++)
					{
						mat[rs2+x]^=galois_single_multiply(tmp,mat[row_start+x],w);
						inv[rs2+x]^=galois_single_multiply(tmp,inv[row_start+x],w);//扫描一把
					}
				}
			}	
		}
	}
	//将生成上三角阵化成单位阵
	for(i=rows-1;i>=0;i--)
	{
		row_start=i*cols;
		for(j=0;j<i;j++)
		{
			rs2=j*cols;//定位元素
			if(mat[rs2+i]!=0)
			{
				tmp=mat[rs2+i];//找出相应需要乘的数据
				mat[rs2+i]=0;
				for(k=0;k<cols;k++)
				{
					inv[rs2+k]^=galois_single_multiply(tmp,inv[row_start+k],w);//等于（i,i）行乘加tmp（mat上的数值）加到inv对应位置
				}
			}
		}
	}
	//最后将数据写回invmatrix
	invmatrix->matrix=inv;
	invmatrix->xm=rows;
	invmatrix->ym=cols;
	invmatrix->w=w;
	return TRUE;
}
int matrix_invertible_matrix(INTMATRIX *matrix)
{
	//计算矩阵是否可逆
	int i,j,k,w,x,rows,cols,row_start,rs2,tmp,inverse;
	UINT32 *mat;
	w=matrix->w;rows=matrix->xm;cols=matrix->ym;
	if(cols!=rows)//如果行不等于列直接返回
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
	/*k=0;//建立相应的单位阵
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			inv[k]=(i==j)?1:0;
			k++;
		}
	}*/
	//转化为上三角阵
	for(i=0;i<cols;i++)
	{
		row_start=cols*i;
		//化简后对角i,i如果为0，那么不可逆
		if(mat[row_start+i]==0)
		{
			for(j=i+1;j<rows&&mat[cols*j+i]==0;j++) ;//搜索不是0的
			if(j==rows) return FALSE;//搜索到最后还没有返回FALSE
			rs2=j*cols;
			for(k=0;k<cols;k++)//找到后交换两行所有的元素
			{
				//同步更新
				tmp=mat[row_start+k];
				mat[row_start+k]=mat[rs2+k];
				mat[rs2+k]=tmp;
				//tmp=inv[row_start+k];
				//inv[row_start+k]=inv[rs2+k];
				//inv[rs2+k]=tmp;
			}
		}
		
		tmp=mat[row_start+i];
		//需要*(i,i)的逆元化为1
		if(tmp!=1)
		{
			inverse=galois_inverse(tmp,w);
			for(j=0;j<cols;j++)//计算mat和相应的逆矩阵
			{
				mat[row_start+j]=galois_single_multiply(mat[row_start+j],inverse,w);
				//inv[row_start+j]=galois_single_multiply(inv[row_start+j],inverse,w);
			}
		}
		//所有的j>i,进行乘加
		k=row_start+i;
		for(j=i+1;j!=cols;j++)
		{
			k+=cols;
			if(mat[k]!=0)//如果不为0则要消减
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
					tmp=mat[k];//当前需要进行乘法的元素
					rs2=cols*j;
					for(x=0;x<cols;x++)
					{
						mat[rs2+x]^=galois_single_multiply(tmp,mat[row_start+x],w);
						//inv[rs2+x]^=galois_single_multiply(tmp,inv[row_start+x],w);//扫描一把
					}
				}
			}	
		}
	}
	//由于无需计算逆矩阵因此这个通过了就可逆
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
	dsize=rows3*cols3;//目标区域
	ssize=rows1*cols2;// 原区域
	//首先需要检查w和是否符合乘法条件
	if(cols1!=rows2||w1!=w2)
	{
		show_error("matrix","multiply","unmultipliable");
		return FALSE;
	}
	//检查mat1,mat2
	if(m1==NULL||m2==NULL)
	{
		show_error("matrix","multiply","MatrixNULL");
		return FALSE;
	}
	//检查invmatrix
	if(res->matrix==NULL||(dsize<ssize))//看看目标矩阵是不是为空,或是空间是否够用
	{
		pro=(UINT32 *)malloc(sizeof(UINT32)*rows1*cols2);
	}
	else
	{
		//够用用原来的空间
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

int matrix_invert_bitmatrix(BITMATRIX *matrix,BITMATRIX *invmatrix)//生成bitmatrix的逆矩阵
{
	//bitmatrix加速版求逆
	int cols,rows,w,drows,dcols,dw,i,j,k;
	int tmp,ssize,dsize;
	int *mat,*inv;//原始和逆矩阵
	
	rows=matrix->xm;//数值初始化
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
	if(rows!=cols)//检测rows和cols是否相等
	{
		show_error("matrix","invert","rows!=cols");
		return FALSE;
	}
	
	if(invmatrix->matrix==NULL||(dsize<ssize))//看看目标矩阵是不是为空,或是空间是否够用
	{
		inv=(UINT32 *)malloc(sizeof(UINT32)*rows*cols);
	}
	else
	{
		//够用用原来的空间
		inv=invmatrix->matrix;
	}
	k=0;
	//初始化inv
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			inv[k]=(i==j)?1:0;
			k++;
		}
	}
	//转上三角
	for(i=0;i<cols;i++)
	{
		//主对角线不存在，则不可逆
		if((mat[i*cols+i])==0)
		{
			for(j=i+1;j<rows&&(mat[j*cols+i])==0;j++) ;//老方法解问题
			if(j==rows) return -1;
			for(k=0;k<cols;k++)//计算上三角阵
			{
				tmp=mat[i*cols+k];mat[i*cols+k]=mat[j*cols+k];mat[j*cols+k]=tmp;
				tmp=inv[i*cols+k];inv[i*cols+k]=inv[j*cols+k];inv[j*cols+k]=tmp;
			}
		}
		//现在对于所有的j>i,只需异或就行清零
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
	//将上三角阵转化为单位阵
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

int matrix_invertable_bitmatrix(BITMATRIX *matrix)//bitmatrix是否可逆
{
	//bitmatrix加速版求逆
	int cols,rows,w,i,j,k;//计算数据
	int tmp;
	int *mat;//原始和逆矩阵

	rows=matrix->xm;//数值初始化
	cols=matrix->ym;//
	w=matrix->w;
	mat=matrix->matrix;

	if(mat==NULL)
	{
		show_error("matrix","matrix","NULL");
		return FALSE;
	}
	if(rows!=cols)//检测rows和cols是否相等
	{
		show_error("matrix","invert","rows!=cols");
		return FALSE;
	}
	//生成上三角
	for(i=0;i<cols;i++)
	{
		//主对角线不存在，则不可逆
		if((mat[i*cols+i])==0)
		{
			for(j=i+1;j<rows&&(mat[j*cols+i])==0;j++) ;
			if(j==rows) return FALSE;
			for(k=0;k<cols;k++)
			{
				tmp=mat[i*cols+k];mat[i*cols+k]=mat[j*cols+k];mat[j*cols+k]=tmp;
			}
		}
		//对于进行累加计算
		for(j=i+1;j!=rows;j++)
		{
			if(mat[j*cols+i]!=0)
			{
				for(k=0;k<cols;k++)//扫描一下
				{
					mat[j*cols+k]^=mat[i*cols+k];
				}
			}
		}
	}
	return TRUE;
}

//chunk构建
CHUNK matrix_CHUNK_create_NULL()
{
	//初始化
	CHUNK ck;
	ck.chunkcontent=NULL;
	ck.isparity=NOVALUE;
	ck.regionid=NODEVICE;
	ck.stripid=NODEVICE;
	ck.sizenum=NOSIZE;
	return ck;
}
CHUNKGROUP matrix_CHUNKGROUP_create_NULL()//创建数据组块
{
	//初始化
	CHUNKGROUP ckgroup;
	ckgroup.ckgroup=NULL;
	ckgroup.groupsize=NOSIZE;
	return ckgroup;
}

int matrix_CHUNK_print_data(CHUNK *ck,int cols)//输出chunk的数据
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
	if(size<cols)//只需单行显示
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

int matrix_CHUNK_copy_meta(CHUNK *desck,CHUNK *souck)//将原数据进行拷贝
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
	desck->chunkcontent=NULL;//当前chunkcontent数据为空
	return TRUE;
}

int matrix_CHUNK_set_data(CHUNK *ck,BYTE* data,UINT64 regionid,int isparity,UINT64 stripid,int sizenum)//设置数据块内容
{
	//开始进行设置
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

int matrix_CHUNK_copy_data(CHUNK *desck,CHUNK *souck)//将chunk之间相互拷贝
{
	BYTE* soudata;
	BYTE* desdata;
	int sizenum;
	soudata=souck->chunkcontent;
	sizenum=souck->sizenum;

	desdata=desck->chunkcontent;
	if(soudata==NULL)
	{
		//如果元数据不存在
		show_error("matrix","souchunk","NULL");
		return FALSE;
	}
	/*if(desdata==NULL)//如果不为空则释放指针
	{
		free(desdata);
	}*/
	if(desdata==NULL)
	{
		desdata=talloc(BYTE,sizenum);//分配空间
		if(desdata==NULL)
		{
			show_error("matrix","CHUNK_copy_data","No memory");
			return FALSE;
		}
		desck->chunkcontent=desdata;
	}
	memcpy(desdata,soudata,sizenum);//数据拷贝过去
	set_state_memcpynum_add((UINT64)sizenum);
	
	/*
	//将其它数据复制//发现没必要
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
	//将数据
	//galois_region_add(soudata,desdata,ssize);
	for(i=0;i<ssize;i++)
	{
		(*desdata)=((*soudata)^(*desdata));
		desdata++;
		soudata++;
	}
	//更新统计值
	set_state_xor_add((UINT64)ssize);
	return TRUE;
}
int matrix_CHUNK_w08_multiply(CHUNK *souck,UINT32 multby)//计算在08环境下，乘法
{
	//使用galois进行乘法
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
int matrix_CHUNK_w16_multiply(CHUNK *souck,UINT32 multby)//计算在16环境下，乘法
{
	//使用galois进行乘法
	BYTE *soudata;
	int size;
	soudata=souck->chunkcontent;
	size=souck->sizenum;
	if(soudata==NULL||size<0)
	{
		show_error("matrix","multiply","souchunk==NULL");
		return FALSE;
	}
	if(size%2!=0)//检查是否可以进行计算
	{
		show_error("matrix","w16","should be 16x");
		return FALSE;
	}
	galois_w16_region_multiply(soudata,multby,size,NULL,FALSE);
	set_state_w16_add(size);
	return TRUE;
}
int matrix_CHUNK_w32_multiply(CHUNK *souck,UINT32 multby)//计算在32环境下，乘法
{
	//使用galois进行乘法
	BYTE *soudata;
	int size;
	soudata=souck->chunkcontent;
	size=souck->sizenum;
	if(soudata==NULL||size<0)
	{
		show_error("matrix","multiply","souchunk==NULL");
		return FALSE;
	}
	if(size%4!=0)//检查是否可以进行计算
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
	//使用galois进行乘法
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
		desdata=talloc(BYTE,size);//分配空间
		if(desdata==NULL)
		{
			show_error("matrix","mutiply","no memory");
			return FALSE;
		}
		desck->chunkcontent=desdata;
	}
	galois_w08_region_multiply(soudata,multby,size,desdata,TRUE);//重新调用域累加函数
	set_state_w08_add(size);
	set_state_xor_add(size);
	//desck->isparity=isparity;
	//desck->regionid=regionid;
	//desck->stripid=stripid;
	//desck->sizenum=size;
	return TRUE;
}
//将源CHUNK块乘加到目标块
int matrix_CHUNK_w16_multiply_add(CHUNK *desck,CHUNK *souck,UINT32 multby)
{
	//使用galois进行乘法
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
		desdata=talloc(BYTE,size);//分配空间
		if(desdata==NULL)
		{
			show_error("matrix","mutiply","no memory");
			return FALSE;
		}
		desck->chunkcontent=desdata;
	}
	if(size%2!=0)//检查是否可以进行计算
	{
		show_error("matrix","w16","should be 16x");
		return FALSE;
	}
	galois_w16_region_multiply(soudata,multby,size,desdata,TRUE);//重新调用域累加函数
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
	//使用galois进行乘法
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
		desdata=talloc(BYTE,size);//分配空间
		if(desdata==NULL)
		{
			show_error("matrix","mutiply","no memory");
			return FALSE;
		}
		desck->chunkcontent=desdata;
	}
	if(size%4!=0)//检查是否可以进行计算
	{
		show_error("matrix","w32","should be 32x");
		return FALSE;
	}
	galois_w32_region_multiply(soudata,multby,size,desdata,TRUE);//重新调用域累加函数
	set_state_w32_add(size);
	set_state_xor_add(size);
	//desck->isparity=isparity;
	//desck->regionid=regionid;
	//desck->stripid=stripid;
	//desck->sizenum=size;
	return TRUE;
}

//将desck制空，并将souck运算结果赋值到desck上
int matrix_CHUNK_w08_multiply_empty_add(CHUNK *desck,CHUNK *souck,UINT32 multby)
{
	//使用galois进行乘法
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
		desdata=talloc(BYTE,size);//分配空间
		if(desdata==NULL)
		{
			show_error("matrix","mutiply","no memory");
			return FALSE;
		}
	}
	galois_w08_region_multiply(soudata,multby,size,desdata,FALSE);//重新调用域累加函数
	set_state_w08_add(size);
	set_state_memcpynum_add(size);
	//desck->isparity=isparity;
	//desck->regionid=regionid;
	//desck->stripid=stripid;
	//desck->sizenum=size;
	return TRUE;
}
//将desck制空，并将souck运算结果赋值到desck上
int matrix_CHUNK_w16_multiply_empty_add(CHUNK *desck,CHUNK *souck,UINT32 multby)
{
	//使用galois进行乘法
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
		desdata=talloc(BYTE,size);//分配空间
		if(desdata==NULL)
		{
			show_error("matrix","mutiply","no memory");
			return FALSE;
		}
	}
	galois_w16_region_multiply(soudata,multby,size,desdata,FALSE);//重新调用域累加函数
	set_state_w16_add(size);
	set_state_memcpynum_add(size);
	//desck->isparity=isparity;
	//desck->regionid=regionid;
	//desck->stripid=stripid;
	//desck->sizenum=size;
	return TRUE;
}
//将desck制空，并将souck运算结果赋值到desck上
int matrix_CHUNK_w32_multiply_empty_add(CHUNK *desck,CHUNK *souck,UINT32 multby)
{//使用galois进行乘法
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
		desdata=talloc(BYTE,size);//分配空间
		if(desdata==NULL)
		{
			show_error("matrix","mutiply","no memory");
			return FALSE;
		}
	}
	galois_w32_region_multiply(soudata,multby,size,desdata,FALSE);//重新调用域累加函数
	set_state_w32_add(size);
	set_state_memcpynum_add(size);
	//desck->isparity=isparity;
	//desck->regionid=regionid;
	//desck->stripid=stripid;
	//desck->sizenum=size;
	return TRUE;
}

int matrix_CHUNKGROUP_set_data(CHUNKGROUP* ckgroup,CHUNK* chunklist,int size)//设置chunk组列表
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
int matrix_CHUNKGROUP_add_CHUNK(CHUNKGROUP *ckgroup,CHUNK *ck)//向CHUNKGROUP中加入CHUNK
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
	size++;//需要增加一位
	
	if(size==0)//说明没有只需要创建一个就行,用size防野
	{
		//chunklist=talloc(CHUNK,size);//分配空间
		tmplist=talloc(CHUNK,size);//分配空间	
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
		//chunklist=talloc(CHUNK,size);//重新分配空间
		tmplist=talloc(CHUNK,size);//分配空间
		if(tmplist==NULL)
		{
			show_error("matrix","chunklist","no memory");
			return FALSE;
		}
		memcpy(tmplist,chunklist,(size-1)*sizeof(CHUNK));//现将之前的数据copy过去
		index=tmplist+size-1;//向后计算size-1为
		index->chunkcontent=ck->chunkcontent;//将数据copy过来
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
int matrix_CHUNKGROUP_del_CHUNK(CHUNKGROUP *ckgroup,int index)//删除index块
{
	//只需要将后排指针上移并且改变带下即可
	
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
	ckgroup->ckgroup=chklist;//小心使得万年船
	ckgroup->groupsize=size;
	return TRUE;
}
//信息设置函数
DOTINF matrix_DOTINF_create_NULL()//创建一个dotinf
{
	DOTINF dotin;
	dotin.linenum=NODEVICE;
	dotin.colsnum=NOSIZE;
	dotin.src_ids=NULL;
	dotin.packetsize=NOSIZE;
	dotin.parityTF=NOSIZE;
	return dotin;
}
int matrix_DOTINF_set_data(DOTINF *dotin,int *src_ids,int linenum,int colsnum,int packetsize,int parityTF)//设置dotinf数据
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
ENDECODEPARA matrix_ENDECODEPARA_create_NULL()//生成一个空的papra
{
	ENDECODEPARA para;
	para.matrix=NULL;
	para.w=NOSIZE;
	return para;
}
int matrix_ENDECODEPARA_set_data(ENDECODEPARA *endecpara,int w,INTMATRIX *matrix)//设置para数据
{
	endecpara->matrix=matrix;
	endecpara->w=w;
	return TRUE;
}
//schedule相关操作
SCHEDOP matrix_SCHUDOP_create_NULL()//创建一个SCHUDOP
{
	SCHEDOP schop;
	schop.db=NOSIZE;
	schop.dd=NOSIZE;
	schop.op=NOSIZE;
	schop.sb=NOSIZE;
	schop.sd=NOSIZE;
	return schop;
}
int matrix_SCHUDOP_set_data(SCHEDOP *schedop,int op,int sd,int sb,int dd,int db,int istareget,CHUNK *tarchunkptr,UINT64 chunkid)//设置SCHUDOP数据
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

SCHEDULE matrix_SCHEDULE_create_NULL()//创建一个SCHUDOP
{
	SCHEDULE schud;
	schud.schedlist=NULL;
	schud.size=NOSIZE;
	return schud;
}
int matrix_SCHEDULE_set_data(SCHEDULE *sched,SCHEDOP *schudlist,int size,int w)//设置SCHEDULE数据
{
	sched->schedlist=schudlist;
	sched->size=size;
	sched->w=w;
	return TRUE;
}

extern DM_IDS matrix_DM_IDS_create_NULL()//指示纠删设备号
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

//编码矩阵
int matrix_do_parity(CHUNKGROUP* ckgroup,CHUNK* parity)//计算校验块
{
	//计算RAID-5校验块
	int soudvnum,csize,psize,i;//原设备数量
	BYTE* pdata;
	CHUNK* chklist;
	CHUNK* souchunk;
	soudvnum=ckgroup->groupsize;
	chklist=ckgroup->ckgroup;
	souchunk=chklist;
	csize=souchunk->sizenum;
	//将检验的原始数据读出
	pdata=parity->chunkcontent;
	psize=parity->sizenum;
	if(pdata==NULL)//看看是不是为空
	{
		pdata=talloc(BYTE,csize);//空间不存在分配之
		if(pdata==NULL)
		{
			show_error("matrix","parity","no memory");
			return FALSE;
		}
		parity->chunkcontent=pdata;//重新赋值回去
	}
	else
	{
		if(psize<csize)//空间不足重新分配
		{
			free(pdata);//不为空释放
			pdata=talloc(BYTE,csize);//分配存储空间
			if(pdata==NULL)
			{
				show_error("matrix","parity","no memory");
				return FALSE;
			}
			parity->chunkcontent=pdata;//重新赋值回去
		}
	}
	//计算parity取值
	matrix_CHUNK_copy_data(parity,souchunk);
	for(i=1;i<soudvnum;i++)
	{
		//计算异或
		souchunk++;
		matrix_CHUNK_add_data(parity,souchunk);
	}	
	parity->isparity=TRUE;
	parity->regionid=souchunk->regionid;
	parity->sizenum=souchunk->sizenum;
	parity->stripid=souchunk->stripid;//虽然有点多余但是为了安全
	return TRUE;
}
int matrix_matrix_encode(CHUNKGROUP *pargroup,CHUNKGROUP *ckgroup,INTMATRIX *matrix)//生成编码块
{
	//进行INT矩阵编码
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
		//矩阵不足以进行乘法
		show_error("matrix","encode","rows is not enough");
		return FALSE;
	}
	//需要设置成
	dotin=matrix_DOTINF_create_NULL();//创建一个dotinf
	for(i=0;i<parnum;i++)
	{
		matrix_DOTINF_set_data(&dotin,NULL,i,chknum,NOSIZE,TRUE);
		matrix_matrix_dotprod(matrix,ckgroup,parlist,&dotin);
		parlist++;
	}
	return TRUE;
}
//chunkblock进行编码
int matrix_matrix_encode_BLOCK(CHUNKBLOCKGROUP *pargroup,CHUNKBLOCKGROUP *ckgroup,INTMATRIX *matrix)
{
	//进行INT矩阵编码
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
		//矩阵不足以进行乘法
		show_error("matrix","encode","rows is not enough");
		return FALSE;
	}

	dotin=matrix_DOTINF_create_NULL();//创建一个dotinf
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
//使用bit阵进行编码
int matrix_bitmatrix_encode(CHUNKGROUP *pargroup,CHUNKGROUP *ckgroup,BITMATRIX *matrix,int packetsize)
{
	//计算bitmatrix进行编码
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
	//开始进入检查环节
	if(chklist==NULL)
	{
		show_error("matrix","bitmatrix_encode","chklist==NULL");
		return FALSE;
	}
	if(packetsize%sizeof(UINT32)!=0)
	{
		//为了保证数据完整性规定32位整数倍
		show_error("matrix","bitmatrix_encode","the packetsize should be 32x");
		return FALSE;
	}
	if(size%(packetsize*w)!=0)
	{
		show_error("matrix","bitmatrix_encode","size%(packetsize*w)!=0");
		return FALSE;
	}
	if(parlist!=NULL)//空间不要
	{
		free(parlist);
	}
	parlist=talloc(CHUNK,parnum);
	if(parlist==NULL)
	{
		show_error("matrix","bitmatrix_encode","No memory");
		return FALSE;
	}
	//可以开始计算了
	for(i=0;i<parnum;i++)
	{
		matrix_DOTINF_set_data(&dotin,NULL,i,chknum,packetsize,TRUE);
		matrix_bitmatrix_dotprod(matrix,ckgroup,parlist,&dotin);
		parlist++;
	}
	return TRUE;
}
//使用schedule进行编码
int matrix_schedule_encode(CHUNKGROUP *pargroup,CHUNKGROUP *ckgroup,SCHEDULE *sched,int packetsize)
{
	//实现schedule编码
	
	int i,schsize,w,chknum,parnum,size;
	CHUNK *chklist,*parlist;
	SCHEDOP *schopp;

	//抽取数据
	parlist=pargroup->ckgroup;
	parnum=pargroup->groupsize;

	chklist=ckgroup->ckgroup;
	chknum=ckgroup->groupsize;

	size=chklist->sizenum;//读出大小

	schsize=sched->size;
	w=sched->w;
	schopp=sched->schedlist;

	//开始检查
	if(chklist==NULL)
	{
		show_error("matrix","SCHEDULE_encode","chklist==NULL");
		return TRUE;
	}
	if(packetsize%sizeof(UINT32)!=0)
	{
		//为了保证数据完整性规定32位整数倍
		show_error("matrix","SCHEDULE_encode","the packetsize should be 32x");
		return FALSE;
	}
	if(size%(packetsize*w)!=0)
	{
		show_error("matrix","SCHEDULE_encodee","size%(packetsize*w)!=0");
		return FALSE;
	}
	if(parlist!=NULL)//空间不要
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
					//仅仅需要数据复制
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
		//仅仅需要异或
		resTF=matrix_CHUNK_add_data(parityptr,chunkptr);
		if(resTF==FALSE)
		{
			show_error("matrix","matrix_notfirstchunk_handle","chunk data can't add");
			return FALSE;
		}
	}
	else
	{
		//需要进行计算
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
	int pisfirst,qisfirst;//代表p,q中数据是否是以一个

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
	curpchunkptr=pchunkptr;//将数据定位到相应位置
	curqchunkptr=qchunkptr;
	for(i=0;i<(rows/2);i++)//每一个盘有rows/2行，即w行,每一行计算一个p chunk和一个q chunk
	{
		curdatastrsetblockptr=datastrsetblockptr;//将指针调回第一个
		//处理一行
		for(j=0;j<strsetnum;j++)//当前存在多少个stripnum
		{
			strsetptr=curdatastrsetblockptr->stripsectptr;
			chunkgroupptr=strsetptr->chunklist;

			chunkptr=chunkgroupptr->ckgroup;
			chunknum=chunkgroupptr->groupsize;

			curchunkptr=chunkptr;
		

		
			for(k=0;k<chunknum;k++)
			{
				
				/*resTF=profile_chunk_data_isfree(curchunkptr);
				if(resTF==TRUE)//如果是空的
				{
					resTF=profile_chunk_data_haswrited(curchunkptr);
					if(resTF==TRUE)//写过可以读了
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
				contentptr=curpchunkptr->chunkcontent;//防止空指针
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

				//定位当前数据位置
				//q盘
				index=0;
				rowsindex=i*cols;
				colsindex=j*w;
				curindex=index+rowsindex+colsindex+k;

			
				resTF=mat[curindex];
				if(resTF==TRUE)//说明当前位置
				{
					//如果数据当前的数据不再内存同步
					resTF=profile_chunk_data_read(curchunkptr);
					if(resTF==FALSE)
					{
						show_error("matrix","bitmatrix_encode_stripsect","chunk data can't read");
						return FALSE;
					}
					//对于当前数据进行
					if(pisfirst==TRUE)
					{
						resTF=matrix_CHUNK_copy_data(curpchunkptr,curchunkptr);//将数据拷贝
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_encode_stripsect","p parity can't copy");
							return FALSE;
						}
						pisfirst=FALSE;//初始化这个块完成
					}
					else
					{
						resTF=matrix_CHUNK_add_data(curpchunkptr,curchunkptr);//将数据累加
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_encode_stripsect","p parity can't calculate");
							return FALSE;
						}
					}
				}
				//Q盘
				contentptr=curqchunkptr->chunkcontent;//防止空指针
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
				//定位计算的位置
				index=w*cols;
				rowsindex=i*cols;
				colsindex=j*w;
				curindex=index+rowsindex+colsindex+k;

				resTF=mat[curindex];
				
				if(resTF==TRUE)//说明当前位置
				{
					//如果数据当前的数据不再内存同步
					resTF=profile_chunk_data_read(curchunkptr);
					if(resTF==FALSE)
					{
						show_error("matrix","bitmatrix_encode_stripsect","chunk data can't read");
						return FALSE;
					}
					if(qisfirst==TRUE)
					{
						resTF=matrix_CHUNK_copy_data(curqchunkptr,curchunkptr);//将数据拷贝
						if(resTF==FALSE)
						{
							show_error("matrix","bitmatrix_encode_stripsect","q parity can't copy");
							return FALSE;
						}
						qisfirst=FALSE;
					}
					else
					{
						resTF=matrix_CHUNK_add_data(curqchunkptr,curchunkptr);//将数据累加
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

	//开始计算
	pisfirst=TRUE;
	qisfirst=TRUE;
	for(i=0;i<strsetnum;i++)
	{
		strsetptr=curdatastrsetblockptr->stripsectptr;
		//计算数据
		chunkgroupptr=strsetptr->chunklist;
		chunkptr=chunkgroupptr->ckgroup;

		curchunkptr=chunkptr;
		//不再内存同步一开始就同步原因是在RS和编码举证情况下为0的情况很少
		resTF=profile_chunk_data_read(curchunkptr);
		if(resTF==FALSE)
		{
			show_error("matrix","matrix_encode_stripsect","chunk data can't read");
			return FALSE;
		}
		index=0;
		curindex=index+i;
		curvalue=mat[curindex];
		if(curvalue!=0)//如果当前需要进行计算
		{
			resTF=profile_chunk_data_read(curchunkptr);
			if(resTF==FALSE)
			{
				show_error("matrix","matrix_encode_stripsect","chunk data can't read");
				return FALSE;
			}
			//计算P盘
			if(pisfirst==TRUE)
			{
				//计算第一个
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
				//说明已经不是第一个
				//curvalue=mat[curindex];
				resTF=matrix_matrix_notfirstchunk_handle(curpchunkptr,curchunkptr,curvalue,w);
				if(resTF==FALSE)
				{
					show_error("matrix","matrix_encode_stripsect","chunk data can't calculate");
					return FALSE;
				}

			}
		}
		//计算Q盘
		index=cols;//
		curindex=index+i;//定位到当前的
		curvalue=mat[curindex];
		if(curvalue!=0)//如果当前需要进行计算
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
				}																																									//计算第一个
			
			/*if(curvalue==1)将其抽象为函数减少代码量
			{
				//仅仅需要数据复制
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
				}																																										//说明已经不是第一个
			//curvalue=mat[curindex];将其抽象为函数减少代码量
			/*if(curvalue==1)
			{
				//仅仅需要异或
				resTF=matrix_CHUNK_add_data(curqchunkptr,curchunkptr);
				if(resTF==FALSE)
				{
					show_error("matrix","matrix_encode_stripsect","chunk data can't add");
					return FALSE;
				}
			}
			else
			{
				//需要进行计算
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
		curdatastrsetblockptr++;//将指针下数据
	}
	return TRUE;
}
//一般编码算法的矩阵编码
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
	//开空间
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
					
					strsetindex=i*cols*w;//计算codestripsect位置
					chunkindex=j*cols;//计算codechunk矩阵位置
					colsindex=strsetindex+chunkindex;
					rowsindex=k*w;
					windex=l;
					curindex=colsindex+rowsindex+windex;
					resTF=mat[curindex];
					if(resTF==TRUE)
					{
						//进行内存同步
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
	//开空间
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



//找出当前需要进行更新的列表
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

	//找出在编码下需要更新的p和q块
	curchunkpositionblockptr=chunkpositionblockptr;//由于所有的块都是在文件中不存在没写过的问题
	for(i=0;i<chunknum;i++)
	{
		curstripsectindex=curchunkpositionblockptr->stripsectindex;
		curchunkindex=curchunkpositionblockptr->chunkindex;
		//对于每一个校验盘当前块会不会引起更新
		for(j=0;j<(rows/2);j++)
		{
			//计算当前chunk需要的P校验块
			pindex=j*cols;
			pwindex=curstripsectindex*w;
			tarpindex=pindex+pwindex+curchunkindex;
			if(mat[tarpindex]==TRUE)//如果在这个位置的数据需要更新
			{
				//记录状态
				pupdatelist[j]=TRUE;
			}


			//计算当前chunk需要的Q校验块
			qindex=w*cols+j*cols;
			qwindex=curstripsectindex*w;
			tarqindex=qindex+qwindex+curchunkindex;
			if(mat[tarqindex]==TRUE)
			{
				//记录状态
				qupdatelist[j]=TRUE;
			}
		}
		curchunkpositionblockptr++;
	}
	return TRUE;
}
//找出当前需要进行更新的列表
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

	for(i=0;i<w;i++)//对于当前校验块进行统计
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
			//计算条带中缓冲的chunk数
			strsetptr=curstrsetblockptr->stripsectptr;
			chunkgroupptr=strsetptr->chunklist;

			chunkptr=chunkgroupptr->ckgroup;
			chunknum=chunkgroupptr->groupsize;

			curchunkptr=chunkptr;
			for(k=0;k<chunknum;k++)
			{
				//计算矩阵当前位置是不是为1
				pindex=i*cols;
				pwindex=j*w;//计算当前w位置
				tarpindex=pindex+pwindex+k;
				resTF=mat[tarpindex];
				if(resTF==TRUE)//当前的位置需要计算
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
			//计算条带中缓冲的chunk数
			strsetptr=curstrsetblockptr->stripsectptr;
			chunkgroupptr=strsetptr->chunklist;

			chunkptr=chunkgroupptr->ckgroup;
			chunknum=chunkgroupptr->groupsize;

			curchunkptr=chunkptr;
			for(k=0;k<chunknum;k++)
			{
				qindex=w*cols+i*cols;
				qwindex=j*w;//计算当前w位置
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
//方案1是重新算法
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
	
	int tempchunknum;//并且当buff用

	CHUNKBLOCKGROUP *soubuffblockgroup;//为了并行化需要开一个缓冲记住所有需要并行化的块好
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

	chunksize=tarchunkptr->sizenum;//获取大小
	contentptr=tarchunkptr->chunkcontent;
	if(contentptr==NULL)
	{
		//由于重新计算只需要进行开空间即可
		contentptr=talloc(BYTE,chunksize);
		if(contentptr==NULL)
		{
			show_error("matrix","bitmatrix_updateI_chunk","No memory");
			return FALSE;
		}
		tarchunkptr->chunkcontent=contentptr;
	}

	index=chkindex*cols;//找到当前的index
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

		//注释为串行划代码
		for(j=0;j<chunknum;j++)
		{
			tarindex=index+windex+j;
			//当前数据需要重新计算
			if(mat[tarindex]==TRUE)
			{
				//计算数据
				souchunkptr=profile_get_chunkposition_ptr(i,j,chunkpositionblockgroupptr);//找找当前的更新数据中有chunk不
				if(souchunkptr==NULL)//当前不存在
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
						//如果在不同读直接加上即可
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
	resTF=profile_XOR_CHUNKBLOCK_CHUNK_DATA_XOR(tarchunkptr,soubuffblockgroup);//之前有数据了因此需要第一步是亦或
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


//方案2是使用当前的校验块来算
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

	//开始检测当前的数据的目标校验块在不在内存
	contentptr=tarchunkptr->chunkcontent;
	if(contentptr==NULL)
	{
		resTF=profile_chunk_data_read(tarchunkptr);//将数据读进内存
		//resTF=FILELAYER_CHUNK_READER_DATA(tarchunkptr);//将数据读进内存
		if(resTF==FALSE)
		{
			show_error("matrix","bitmatrix_updateII_chunk_RAID6","chunk data can't read");
			return FALSE;
		}
		//由于目标块最后要写入数据不可以释放
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
		//注释为串行代码
		for(j=0;j<chunknum;j++)
		{
			//我们先计算当前是不是需要计算
			tarindex=index+windex+j;
			if(mat[tarindex]==TRUE)//在路径上
			{
				souchunkptr=profile_get_chunkposition_ptr(i,j,chunkpositionblockgroupptr);
				if(souchunkptr!=NULL)//当然如果有数据
				{
					//当前有数据需要修正
					contentptr=curchunkptr->chunkcontent;
					if(contentptr==NULL)
					{
						//当前数据说明不在内存
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
					
					/*//将数据进行异或
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
	//读取数据
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
	
	
	//方案1是重新算法，方案2是使用当前的校验块来算
	int *pupdatelist1,*pupdatelist2;
	int *qupdatelist1,*qupdatelist2;
	int *pupdatelist,*qupdatelist;


	BYTE *contentptr;
	//float poccupyrate,qoccupyrate;
	
	//获取矩阵数据
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	//获取p和q盘列表
	pchunkgroupptr=pparity->chunklist;
	pchunkptr=pchunkgroupptr->ckgroup;
	pchunknum=pchunkgroupptr->groupsize;

	pupdatelist=talloc(int,pchunknum);
	if(pupdatelist==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist,int,pchunknum);//将数据清0，即所有的都是FALSE

	pupdatelist1=talloc(int,pchunknum);
	if(pupdatelist1==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist1,int,pchunknum);//将数据清0，即所有的都是FALSE

	pupdatelist2=talloc(int,pchunknum);
	if(pupdatelist2==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist2,int,pchunknum);//制0


	qchunkgroupptr=qparity->chunklist;
	qchunkptr=qchunkgroupptr->ckgroup;
	qchunknum=qchunkgroupptr->groupsize;

	qupdatelist=talloc(int,qchunknum);
	if(qupdatelist==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist,int,qchunknum);//将数据清0，即所有的都是FALSE

	qupdatelist1=talloc(int,qchunknum);
	if(qupdatelist1==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist1,int,qchunknum);//将数据清0，即所有的都是FALSE

	qupdatelist2=talloc(int,qchunknum);
	if(qupdatelist2==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist2,int,qchunknum);//制0
	//计算需要更新的校验块
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
	

	

	//我们已经知道了需要更新的块现在可以计算了
	curpchunkptr=pchunkptr;
	curqchunkptr=qchunkptr;
	for(i=0;i<(rows/2);i++)
	{
		//计算P盘
		if(pupdatelist[i]!=FALSE)//当前的块需要重新算法
		{
			//第一步线判断当的校验块在不在内存
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
		//计算Q盘
		if(qupdatelist[i]!=FALSE)
		{
			//第一步线判断当的校验块在不在内存
			//第一步线判断当的校验块在不在内存
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
	
	
	//方案1是重新算法，方案2是使用当前的校验块来算
	int *pupdatelist1,*pupdatelist2;
	int *qupdatelist1,*qupdatelist2;
	int *pupdatelist,*qupdatelist;


	BYTE *contentptr;
	//float poccupyrate,qoccupyrate;
	
	//获取矩阵数据
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	//获取p和q盘列表
	pchunkgroupptr=pparity->chunklist;
	pchunkptr=pchunkgroupptr->ckgroup;
	pchunknum=pchunkgroupptr->groupsize;

	pupdatelist=talloc(int,pchunknum);
	if(pupdatelist==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist,int,pchunknum);//将数据清0，即所有的都是FALSE

	pupdatelist1=talloc(int,pchunknum);
	if(pupdatelist1==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist1,int,pchunknum);//将数据清0，即所有的都是FALSE

	pupdatelist2=talloc(int,pchunknum);
	if(pupdatelist2==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist2,int,pchunknum);//制0


	qchunkgroupptr=qparity->chunklist;
	qchunkptr=qchunkgroupptr->ckgroup;
	qchunknum=qchunkgroupptr->groupsize;

	qupdatelist=talloc(int,qchunknum);
	if(qupdatelist==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist,int,qchunknum);//将数据清0，即所有的都是FALSE

	qupdatelist1=talloc(int,qchunknum);
	if(qupdatelist1==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist1,int,qchunknum);//将数据清0，即所有的都是FALSE

	qupdatelist2=talloc(int,qchunknum);
	if(qupdatelist2==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist2,int,qchunknum);//制0
	//计算需要更新的校验块
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
	

	

	//我们已经知道了需要更新的块现在可以计算了
	curpchunkptr=pchunkptr;
	curqchunkptr=qchunkptr;
	for(i=0;i<(rows/2);i++)
	{
		//计算P盘
		if(pupdatelist[i]!=FALSE)//当前的块需要重新算法
		{
			//第一步线判断当的校验块在不在内存
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
		//计算Q盘
		if(qupdatelist[i]!=FALSE)
		{
			//第一步线判断当的校验块在不在内存
			//第一步线判断当的校验块在不在内存
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
//当前chunkblockgroup中的数据需要在一个strip中
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
	
	
	//方案1是重新算法，方案2是使用当前的校验块来算
	int *pupdatelist1,*pupdatelist2;
	int *qupdatelist1,*qupdatelist2;
	int *pupdatelist,*qupdatelist;


	BYTE *contentptr;
	//float poccupyrate,qoccupyrate;
	
	//获取矩阵数据
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	//获取p和q盘列表
	pchunkgroupptr=pparity->chunklist;
	pchunkptr=pchunkgroupptr->ckgroup;
	pchunknum=pchunkgroupptr->groupsize;

	pupdatelist=talloc(int,pchunknum);
	if(pupdatelist==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist,int,pchunknum);//将数据清0，即所有的都是FALSE

	pupdatelist1=talloc(int,pchunknum);
	if(pupdatelist1==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist1,int,pchunknum);//将数据清0，即所有的都是FALSE

	pupdatelist2=talloc(int,pchunknum);
	if(pupdatelist2==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(pupdatelist2,int,pchunknum);//制0


	qchunkgroupptr=qparity->chunklist;
	qchunkptr=qchunkgroupptr->ckgroup;
	qchunknum=qchunkgroupptr->groupsize;

	qupdatelist=talloc(int,qchunknum);
	if(qupdatelist==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist,int,qchunknum);//将数据清0，即所有的都是FALSE

	qupdatelist1=talloc(int,qchunknum);
	if(qupdatelist1==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist1,int,qchunknum);//将数据清0，即所有的都是FALSE

	qupdatelist2=talloc(int,qchunknum);
	if(qupdatelist2==NULL)
	{
		show_error("matrix","bitmatrix_update_stripsect","No memory");
		return FALSE;
	}
	bzero(qupdatelist2,int,qchunknum);//制0
	//计算需要更新的校验块
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
	

	

	//我们已经知道了需要更新的块现在可以计算了
	curpchunkptr=pchunkptr;
	curqchunkptr=qchunkptr;
	for(i=0;i<(rows/2);i++)
	{
		//计算P盘
		if(pupdatelist[i]!=FALSE)//当前的块需要重新算法
		{
			//第一步线判断当的校验块在不在内存
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
				//不存在先把校验
				if(pupdatelist1[i]<(pupdatelist2[i]+1))//需要多读一个
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
				//存在
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
		//计算Q盘
		if(qupdatelist[i]!=FALSE)
		{
			//第一步线判断当的校验块在不在内存
			//第一步线判断当的校验块在不在内存
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
				//不存在
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
				//存在
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
		//仅仅需要异或
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

int matrix_update_matrix_pqupdatenum_chunklist_create(int *pupdatelist,int *qupdatelist,//updatelist第一行为第一个方案，第二行为第二方案
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
		//计算p盘
		resTF=mat[tarindex];
		if(resTF!=FALSE)//当前需要计算
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

		//计算q盘
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
//1重算
int matrix_matrix_updateI_chunk_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition代表需要更新的校验块列表
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//当前的数据条带
											CHUNK *tarchunkptr,INTMATRIX *matrix,int chkindex)//目标校验块，矩阵，目标块索引
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
	rowsindex=chkindex*cols;//定位到一行
	isfirst=TRUE;
	for(i=0;i<strsetnum;i++)
	{
		//获取当前chunk指针
		strsetptr=curstrsetblockptr->stripsectptr;
		
		chunkgroupptr=strsetptr->chunklist;
		curchunkptr=chunkgroupptr->ckgroup;

		souchunkptr=profile_get_chunkposition_ptr(i,0,chunkpositionblockgroupptr);
		if(souchunkptr==NULL)
		{
			souchunkptr=curchunkptr;
			resTF=profile_chunk_data_isfree(souchunkptr);
			if(resTF==TRUE)//当前数据是空的
			{
				//将数据同步到内存
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
//利用校验块
int matrix_matrix_updateII_chunk_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition代表需要更新的校验块列表
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//当前的数据条带
											CHUNK *tarchunkptr,INTMATRIX *matrix,int chkindex)//目标校验块，矩阵，目标块索引
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
	index=chkindex*cols;//算出行号
	//curchunkpositionblockptr=chunkpositionblockptr;
	for(i=0;i<strsetnum;i++)//
	{
		//计算每一个chunk的数据中的数据
		//strsetindex=curchunkpositionblockptr->stripsectindex;
		//chunkindex=curchunkpositionblockptr->chunkindex;
		strsetptr=curstrsetblockptr->stripsectptr;

		chunkgroupptr=strsetptr->chunklist;
		chunkptr=chunkgroupptr->ckgroup;

		curchunkptr=chunkptr;

		
		curindex=index+i;
		curvalue=mat[curindex];
		if(curvalue!=FALSE)//当前需要计算
		{
			strsetindex=i;
			chunkindex=0;
			souchunkptr=profile_get_chunkposition_ptr(strsetindex,chunkindex,chunkpositionblockgroupptr);
			if(souchunkptr!=NULL)//说明当前的chunk在需要更新的chunk列表中
			{
				//计算
				resTF=profile_chunk_data_isfree(curchunkptr);
				if(resTF==FALSE)
				{
					resTF=profile_chunk_data_read(curchunkptr);//计算当前数据
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
//当前chunkblockgroup中的数据需要在一个strip中
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

	//我们计算当前的需要更新的方案的需要更新数量
	resTF=matrix_update_matrix_pqupdatenum_chunklist_create(pupdatelist,qupdatelist,
														chunkpositionblockgroupptr,strsetblockgroupptr,
														matrix);
	if(resTF==FALSE)
	{
		show_error("matrix","matrix_update_stripsect_RAID6","updatelist can't calculate");
		return FALSE;
	}
	//调整一下当前指针
	curpchunkptr=pchunkptr;
	resTF=profile_chunk_data_isfree(curpchunkptr);
	if(resTF==TRUE)//如果当前校验块为空
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
														matrix);//需要重新计算
	if(resTF==FALSE)
	{
		show_error("matrix","matrix_update_stripsect_RAID6","updatelist can't calculate");
		return FALSE;
	}
	curqchunkptr=qchunkptr;
	resTF=profile_chunk_data_isfree(curqchunkptr);
	if(resTF==TRUE)//如果当前校验块为空
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
												BITMATRIX *matrix,int updatenum)//找出当前需要进行更新的列表
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

			tarindex=index+rowsindex+colsindex;//计算位置
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
															BITMATRIX *matrix,int updatenum)//计算两种方案的updatelist
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

int matrix_bitmatrix_updateI_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition代表需要更新的校验块列表
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//当前的数据条带
											CHUNK *tarchunkptr,BITMATRIX *matrix,int chkindex)//目标校验块，矩阵，目标块索引
{
	//和RAID-6一致
	int resTF;
	resTF=matrix_bitmatrix_updateI_chunk_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,tarchunkptr,matrix,chkindex);
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_updateI_chunk","strip can't calculate");
		return FALSE;
	}
	return TRUE;
}
int matrix_bitmatrix_updateII_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition代表需要更新的校验块列表
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//当前的数据条带
											CHUNK *tarchunkptr,BITMATRIX *matrix,int chkindex)//目标校验块，矩阵，目标块索引
{
	//和RAID-6一致
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

	//开空间
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
	resTF=matrix_update_bitmatrix_parity_chunklist(updatelist,chunkpositionblockgroupptr,matrix,updatenum);//判断是不是需要更新
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_update_strip","parity chunklist can't create");
		return FALSE;
	}
	codestrsetblockptr=codestrsetblockgroupptr->stripsectblockptr;
	codestrsetnum=codestrsetblockgroupptr->groupsize;

	curcodestrsetblockptr=codestrsetblockptr;

	codeindex=0;
	//开始使用RCW进行更新
	for(i=0;i<codestrsetnum;i++)
	{
		//计算所有所有的目标块
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
				//如果当前块需要更新1
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

	//开空间
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
	resTF=matrix_update_bitmatrix_parity_chunklist(updatelist,chunkpositionblockgroupptr,matrix,updatenum);//判断是不是需要更新
	if(resTF==FALSE)
	{
		show_error("matrix","bitmatrix_update_strip","parity chunklist can't create");
		return FALSE;
	}
	codestrsetblockptr=codestrsetblockgroupptr->stripsectblockptr;
	codestrsetnum=codestrsetblockgroupptr->groupsize;

	curcodestrsetblockptr=codestrsetblockptr;

	codeindex=0;
	//开始使用RCW进行更新
	for(i=0;i<codestrsetnum;i++)
	{
		//计算所有所有的目标块
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
				//如果当前块需要更新1
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
	//开空间
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

	resTF=matrix_update_bitmatrix_parity_chunklist(updatelist,chunkpositionblockgroupptr,matrix,updatenum);//判断是不是需要更新
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
		//计算所有所有的目标块
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
				//如果当前块需要更新
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
				//重新计算当前数据
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

	//生成数据和校验列表
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
													BITMATRIX *matrix,int updatenum)//找出当前需要进行更新的列表
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
														BITMATRIX *matrix,int updatenum)//计算两种方案的updatelist
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
				if(mat[curindex]==TRUE)//计算matrix是不是要计算
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
int matrix_matrix_updateI_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition代表需要更新的校验块列表
										STRIPSECTBLOCKGROUP *strsetblockgroupptr,//当前的数据条带
										CHUNK *tarchunkptr,INTMATRIX *matrix,int chkindex)//目标校验块，矩阵，目标块索引
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
int matrix_matrix_updateII_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition代表需要更新的校验块列表
										STRIPSECTBLOCKGROUP *strsetblockgroupptr,//当前的数据条带
										CHUNK *tarchunkptr,INTMATRIX *matrix,int chkindex)//目标校验块，矩阵，目标块索引
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
	//开空间
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
			//现在来判断一下当前的chunk是不是需要从内存读取
			resTF=profile_chunk_should_read(codechunkptr);
			if(resTF==FALSE)
			{
				//如果需要读取
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

	//生成数据和校验列表
	free(datastrsetblockgroupptr);
	free(datastrsetblockptr);
	free(codestrsetblockgroupptr);
	free(codestrsetblockptr);
	return TRUE;
}
//根据bit阵计算share
int matrix_matrix_calculate_share(BITMATRIX *matrixptr,CODEPARA *codeptr,AONTSHAREGROUP *sharegroupptr,int sharesize)
{
//第一步
	int datanum,codenum,totnum,w;
	int i,j,k,groupsize,chunksize,index,resTF;
	BYTE *conptr,*curconptr,*souptr;
	UINT32 *mat;
	int rows,cols;
	CHUNK *chunkptr,*curchunkptr,*tmpchunkptr;//创建一个chunk指针
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
	//开始迭代
	for(i=0;i<datanum;i++)
	{
		souptr=curshareptr->content;
		conptr=souptr;
		//开始将其组成chunkgroup
		for(j=0;j<w;j++)
		{
			/*conptr=talloc(char,chunksize);//先给点空间
			if(conptr==NULL)
			{
				show_error("matrix","matrix_calculate_share","No memory");
				return FALSE;
			}
			mcpy(conptr,souptr,char,chunksize);//开始拷贝数据*/
			curchunkptr->chunkcontent=conptr;
			curchunkptr->sizenum=chunksize;
			curchunkptr++;//一个chunk的数据已经到手了再来一个
			conptr=conptr+chunksize;//移动一个chunksize
		}
		
		curshareptr++;//我们先获取下一个share
	}

	//分换后在进行乘法
	tmpchunkptr=talloc(CHUNK,1);//先申请一个chunk来记住中间结果
	if(tmpchunkptr==NULL)
	{
		show_error("matrix","matrix_calculate_share","No memory");
		return FALSE;
	}
	souptr=talloc(BYTE,chunksize);//先给点空间
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
	//终于到最后一步了对于矩阵的每一行使用一个乘法
	for(i=0;i<codenum;i++)//
	{
		conptr=curshareptr->content;
		curconptr=conptr;

		for(j=0;j<w;j++)
		{
			//开始一行将指针指向队头
			curchunkptr=chunkptr;
			bzero(souptr,BYTE,chunksize);//chunk清零
			for(k=0;k<cols;k++)
			{
				
				if(mat[index]==1)
				{
					//计算
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
			//一个chunk算完了可以拷贝了
			mcpy(curconptr,souptr,BYTE,chunksize);//把数据拷贝一下
			curconptr=curconptr+chunksize;//向后移动一个chunksize
		}
		curshareptr++;
	}
	chunkptr=chunkgroupptr->ckgroup;//清一下内存     
	free(chunkptr);
	free(chunkgroupptr);
	return TRUE;
}


//解码
//raid-5解码
int matrix_do_deparity(CHUNKGROUP* ckgroup,CHUNK *lost,int TFparity)
{
	//进行raid5解码只需异或即可
	int soudvnum,csize,lsize,i;
	CHUNK* chklist;
	BYTE* ldata;
	chklist=ckgroup->ckgroup;//进行赋值
	soudvnum=ckgroup->groupsize;
	csize=chklist->sizenum;//获取chunk大小
	lsize=lost->sizenum;//失效数据进行赋值
	ldata=lost->chunkcontent;
	if(ldata==NULL)//看看是不是为空
	{
		//生成内存
		ldata=talloc(BYTE,csize);//空间不存在分配之
		if(ldata==NULL)
		{
			show_error("matrix","lost","no memory");
			return FALSE;
		}
		lost->chunkcontent=ldata;
	}
	else
	{
		if(lsize<csize)//空间不足重新分配
		{
			free(ldata);//不为空释放
			if(ldata==NULL)
			{
				show_error("matrix","lost","no memory");
				return FALSE;
			}
			ldata=talloc(BYTE,csize);//分配存储空间
			lost->chunkcontent=ldata;//重新赋值回去
		}
	}
	matrix_CHUNK_copy_data(lost,chklist);//统统异或即可
	for(i=1;i<soudvnum;i++)
	{
		//计算异或
		chklist++;
		matrix_CHUNK_add_data(lost,chklist);
	}
	lost->isparity=TFparity;
	lost->regionid=chklist->regionid;
	lost->sizenum=chklist->sizenum;
	lost->stripid=chklist->stripid;//虽然有点多余但是为了安全
	return TRUE;
}
//matrix解码
int matrix_matrix_decode(CHUNKGROUP *lostgroup,CHUNKGROUP *ckgroup,INTMATRIX *matrix,ERASES *erarray)//
{
	//根据erase和matrix中的内容，恢复丢失数据块
	int i,lsizenum,chknum,rows,cols,w;//需要读取数据
	int *erarr,codenum,datanum,totnum;
	CHUNK *chklist,*lostlist;
	UINT32 *mat;

	//开始读取数据
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

	//先来一通合法性检查
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
	lostlist=talloc(CHUNK,codenum);//生成空间
	if(lostlist==NULL)
	{
		show_error("matrix","matrix decoder","No memory");
		return FALSE;
	}
	return TRUE;
}
//BLOCK计算矩阵解码
int matrix_matrix_decode_BLOCK(CHUNKBLOCKGROUP *lostgroup,CHUNKBLOCKGROUP *ckgroup,INTMATRIX *matrix,ERASES *erarry)
{
	//根据erase和matrix中的内容，恢复丢失数据块
	int i,lsizenum,chknum,rows,cols,w,resTF;//需要读取数据
	int *erarr,codenum,datanum,totnum;
	CHUNKBLOCKGROUP *eraseblockgroupptr;
	CHUNKBLOCK *datachunkblockptr,*lostchunkblockptr;
	CHUNK *datachunkptr,*lostchunkptr;
	INTMATRIX *dematrix;
	DM_IDS *dmids;
	UINT32 *mat;

	//开始读取数据
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
	//先来一通合法性检查
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
	//生成逆矩阵
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
	//整个计算纠删组
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
;//BLOCK计算校验
int matrix_bitmatrix_encode_BLOCK(CHUNKBLOCKGROUP *pargroup,CHUNKBLOCKGROUP *ckgroup,BITMATRIX *matrix,int packetsize)
{
	return TRUE;
}

//scheudle解码方案
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
//生成相应解码矩阵
int matrix_make_decoding_matrix(INTMATRIX *decoding_matrix,INTMATRIX *matrix,ERASES *erarray,DM_IDS *dmids)
{
	//创建一个解码矩阵
	int i,j,w,rows,cols,drows,dcols,datanum,codenum,totnum,dmnum,resTF;
	UINT32 *mat,*dmat;
	int *erar,*dmi;
	
	//建立滑去矩阵
	INTMATRIX eramatrix;

	//测试用矩阵不要在意
	//INTMATRIX testmatrix,testmatrix1;
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	dmat=decoding_matrix->matrix;//先借用一下之后代表滑去矩阵
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
	if(datanum!=cols)//矩阵的列数需要等于
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
	//判断目标空间情况
	if(dmat!=NULL)//释放decoding_matrix
	{
		free(dmat);
	}
	dmat=talloc(UINT32,cols*cols);//开空间由于是逆矩阵因此是cols*cols
	if(dmat==NULL)
	{
		show_error("matrix","make_decoding_matrix","No memory");
		return FALSE;
	}
	//decoding_matrix->matrix=dmat;
	//将eramatrix的数据赋值
	matrix_set_data(&eramatrix,dmat,cols,cols,w);
	//生成长度k的编码array
	if(dmi!=NULL)
	{
		free(dmi);
	}
	dmi=talloc(int,datanum);//使用最大上限建立表格
	if(dmi==NULL)
	{
		show_error("matrix","make_decoding_matrix","NO memory");
		return FALSE;
	}
	dmids->dm_ids=dmi;//将其重新赋值
	//可以开始生成dm_ids
	j=0;//将j置0
	for(i=0;j<datanum;i++)
	{
		if(erar[i]==FALSE)//当前设备存在
		{
			dmi[j]=i;
			j++;
		}
		if(i>totnum)//搜索完整张表还是没有足够的数据
		{
			show_error("matrix","make_decoding_bitmatrix","erases is illegal");
			return FALSE;
		}
	}
	dmnum=j;
	dmids->size=j;
	for(i=0;i<dmnum;i++)//开始建立滑去的矩阵
	{
		if(dmi[i]<datanum)//先判断是不是编码块
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
				dmat[i*cols+j]=mat[(dmi[i]-datanum)*cols+j];//计算在编码阵中的位置并赋值
			}
		}
	}
	//进行逆矩阵求解
	//matrix_print_matrix(&eramatrix);
	//testmatrix1=matrix_duplicate(&eramatrix);
	resTF=matrix_invert(&eramatrix,decoding_matrix);//进行逆矩阵计算
	//测试一下是不是为E
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

	//建立纠删矩阵
	BITMATRIX eramatrix;//本身是一个
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
	//安全性检查
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
	//开始申请空间
	if(dmat!=NULL)
	{
		free(dmat);
	}
	dmat=talloc(UINT32,cols*cols);
	if(dmat==NULL)//没有空间
	{
		show_error("matrix","make_decoding_bitmatrix","NO memory");
		return FALSE;
	}
	matrix_set_data(&eramatrix,dmat,cols,cols,w);//纠删矩阵设定数值
	//dm_ids分配空间
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
	//检查完毕可以开始建立纠删矩阵了
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
	//准备工作工作完成开始生成纠删矩阵
	for(i=0;i<datanum;i++)
	{
		if(dmi[i]<datanum)//当前的位置在数据区域内
		{
			//需要将数据行变成指定的单位阵
			index=i*cols*w;//定位到当前行
			for(j=0;j<cols*w;j++)//对于之后的w行进行赋值
			{
				dmat[index+j]=0;//赋值0
			}
			index=i*cols*w+dmi[w]*w;//定位到当前位置
			for(j=0;j<w;j++)
			{
				dmat[index]=1;
				index+=(cols+1);
			}
		}
		else
		{
			//将编码数据赋值
			index=i*cols*w;//定位当前位置
			mindex=(dmi[i]-datanum)*cols*w;//定位编码矩阵位置
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

//点乘大全//计算一个chunk数据
//其中parchunk为输出
int matrix_matrix_dotprod_BLOCK(INTMATRIX *matrix,CHUNKBLOCKGROUP *ckgroup,CHUNK *parchunk,DOTINF *dotin)
{
	//进行矩阵点乘数据块
	UINT32 *mat;

	int i,w,linenum,chknum,rows,cols,colsnum,srcindex,chksize,parityTF,multindex;
	//UINT64 regionid,stripid;
	UINT32 multby;
	int *srcids,resTF;

	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *chunkptr;
	BYTE *newptr;
	//提取数据
	mat=matrix->matrix;
	w=matrix->w;
	rows=matrix->xm;
	cols=matrix->ym;
	
	srcids=dotin->src_ids;
	colsnum=dotin->colsnum;//需要进行计算的矩阵列数rows或group行数cols
	linenum=dotin->linenum;//需要计算的矩阵行数
	parityTF=dotin->parityTF;//读取是不是parityTF
	//开始对于BLOCK进行赋值
	chknum=ckgroup->groupsize;
	chunkblockptr=ckgroup->chunkblockptr;
	
	if(w!=8&&w!=16&&w!=32)
	{
		show_error("matrix","dotprod","w is illegal");
		return FALSE;
	}
	if(colsnum!=rows)
	{
		//不相等无法相乘
		show_error("matrix","dotprot","rowes!=cols");
		return FALSE;
	}
	//检测数据
	
	newptr=parchunk->chunkcontent;
	if(newptr!=NULL)
	{
		free(newptr);
	}
	chksize=parchunk->sizenum;//获取大小
	newptr=talloc(BYTE,chksize);//分配空间

	parchunk->chunkcontent=newptr;
	//第一步先拷贝第一个块
	curchunkblockptr=chunkblockptr;
	chunkptr=curchunkblockptr->chunkptr;
	resTF=matrix_CHUNK_copy_data(parchunk,chunkptr);//拷贝数据
	if(resTF==FALSE)
	{
		show_error("matrix","matrix_dotprod_BLOCK","chunkdata can't copy");
		return FALSE;
	}
	for(i=1;i<chknum;i++)//这里第一个已经拷贝
	{
		if(srcids==NULL)//需要全局搜索
		{
			curchunkblockptr++;
			chunkptr=curchunkblockptr->chunkptr;
			if(mat[linenum*rows+i]==1)//直接异或
			{
				matrix_CHUNK_add_data(parchunk,chunkptr);
			}
			else//需要乘法
			{
				multindex=rows*linenum+i;//生成需要计算的位置
				multby=mat[multindex];
				switch(w)//根据w计算相应的数值
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
			//肯定要先定位
			srcindex=srcids[i];
			//计算乘法
			curchunkblockptr=chunkblockptr+srcindex;//重新定位
			chunkptr=curchunkblockptr->chunkptr;
			if(mat[linenum*rows+i]==1)//直接异或
			{
				
				matrix_CHUNK_add_data(parchunk,chunkptr);//重新累加
			}
			else//需要乘法
			{
				switch(w)//根据w计算相应的数值
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

//生成erases数据
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
		//计算数据
		if(err[i]==FALSE)//将数据复制
		{
			curtarblockptr->chunkptr=cursoublockptr->chunkptr;
			curtarblockptr->chunkid=cursoublockptr->chunkid;
		}
		curtarblockptr++;
		cursoublockptr++;
	}
	return TRUE;
}

int matrix_matrix_dotprod(INTMATRIX *matrix,CHUNKGROUP *chkgroup,CHUNK *parchunk,DOTINF *dotin)//这里采用plank实现,一行一行做
{
	//进行矩阵点乘数据块
	UINT32 *mat;

	int i,w,linenum,chknum,rows,cols,colsnum,srcindex,chksize,parityTF,multindex;
	//UINT64 regionid,stripid;
	UINT32 multby;
	int *srcids;
	CHUNK *chklist;
	BYTE *newptr;
	//提取数据
	mat=matrix->matrix;
	w=matrix->w;
	rows=matrix->xm;
	cols=matrix->ym;
	
	srcids=dotin->src_ids;
	colsnum=dotin->colsnum;//需要进行计算的矩阵列数rows或group行数cols
	linenum=dotin->linenum;//需要计算的矩阵行数
	parityTF=dotin->parityTF;//读取是不是parityTF
	
	chknum=chkgroup->groupsize;//chunk数
	chklist=chkgroup->ckgroup;//提取chunk列表
	chksize=chklist->sizenum;//每一个块大小
	//regionid=chklist->regionid;//读取regionid
	//stripid=chklist->stripid;//读取stripid

	if(w!=8&&w!=16&&w!=32)
	{
		show_error("matrix","dotprod","w is illegal");
		return FALSE;
	}
	if(colsnum!=rows)
	{
		//不相等无法相乘
		show_error("matrix","dotprot","rowes!=cols");
		return FALSE;
	}
	newptr=parchunk->chunkcontent;
	//检测paritychunk中指针情况
	if(newptr!=NULL)
	{
		free(newptr);
	}
	newptr=talloc(BYTE,chksize);//只需要进行分配即可
	if(newptr==NULL)
	{
		show_error("matrix","dotprot","no memory");
		return FALSE;
	}
	//为了统一运算我们现将数据统一为0
	for(i=0;i<chksize;i++)
	{
		newptr[i]=0;
	}
	parchunk->chunkcontent=newptr;
	//parchunk->isparity=parityTF;//需要dotinf读取
	//parchunk->regionid=regionid;
	//parchunk->sizenum=chksize;
	//parchunk->stripid=stripid;
	//编码阵一开始就是
	for(i=0;i<colsnum;i++)//因为在计算过程中srcid的值不变因此无需考虑chklist指针问题
	{
		if(srcids==NULL)//全部计算
		{
			if(mat[linenum*rows+i]==1)//直接异或
			{
				matrix_CHUNK_add_data(parchunk,chklist);
			}
			else//需要乘法
			{
				multindex=rows*linenum+i;//生成需要计算的位置
				multby=mat[multindex];
				switch(w)//根据w计算相应的数值
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
			chklist++;//转到下一个chunk
		}
		else//需要srcids定位
		{
			//肯定要先定位
			srcindex=srcids[i];
			//计算乘法
			chklist=chkgroup->ckgroup+srcindex;//重新定位
			if(mat[linenum*rows+i]==1)//直接异或
			{
				
				matrix_CHUNK_add_data(parchunk,chklist);//重新累加
			}
			else//需要乘法
			{
				switch(w)//根据w计算相应的数值
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
	//读取参数
	int x,y,j,w,datanum,linenum,rows,cols,colsnum,parityTF,chksize,chknum,packetsize,sindex,index,pstarted,tindex;
	//UINT64 regionid,stripid;
	BITMATRIX *mat;
	int *srcids;
	CHUNK *chklist;
	BYTE *dptr,*pptr,*bdptr,*bpptr;//先定义一竿子指针


	return TRUE;
}

int matrix_bitmatrix_dotprod(BITMATRIX *matrix,CHUNKGROUP *chkgroup,CHUNK *parchunk,DOTINF *dotin)//这里还是用Plank老师的方法，bit级操作我的大chunk无能为力
{
	//读取参数
	int x,y,j,w,datanum,linenum,rows,cols,colsnum,parityTF,chksize,chknum,packetsize,sindex,index,pstarted,tindex;
	//UINT64 regionid,stripid;
	UINT32 *mat;
	int *srcids;
	CHUNK *chklist;
	BYTE *dptr,*pptr,*bdptr,*bpptr;//先定义一竿子指针
	
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
	//因为主要使用cauchy因此这里不做w合法性检查
	//需要块大小是否合法
	if(chksize%(w*packetsize)!=0)
	{
		show_error("matrix","bitmatrix_dotprod","chksize%(w*packetsize)!=0");
		return FALSE;
	}
	//设定目标指针
	bpptr=parchunk->chunkcontent;//设定目标指针这里沿袭plank老师的命名方式，p推测是parity的意思
	if(bpptr!=NULL)
	{
		//原数据一点不留
		free(bpptr);
	}
	bpptr=talloc(BYTE,chksize);//生成存储空间
	if(bpptr==NULL)
	{
		show_error("matrix","bitmatrix_dotprod","No memory");
		return FALSE;
	}
	parchunk->chunkcontent=bpptr;//将指针存回
	for(sindex=0;sindex<chksize;sindex+=(packetsize*w))
	{
		index=0;
		for(j=0;j<w;j++)//对于每一个麻片中间的数据
		{
			pstarted=0;
			pptr=bpptr+sindex+j*packetsize;//计算当前目标位置的偏移量
			for(x=0;x<colsnum;x++)
			{
				if(srcids==NULL)//如果代表了
				{
					bdptr=chklist[x].chunkcontent;//指向源数据
				}
				else
				{
					tindex=srcids[x];//目标数据块
					bdptr=chklist[tindex].chunkcontent;//指向源数据
				}
				for(y=0;y<w;y++)
				{
					dptr=bdptr+sindex+y*packetsize;
					if(!pstarted)
					{
						memcpy(pptr,dptr,packetsize);//开始时只需进行copy
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

int matrix_do_scheduled_operations()//继续一步Schedule计算
{
	return TRUE;
}
//进行matrix bitmatrix和schedule转化
int matrix_matrix_to_bitmatrix(INTMATRIX *matrix,BITMATRIX *bitmatrix)//从INTMATRIX生成一个BITMATRIX
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
		bitmat=talloc(UINT32,(k*m*w*w));//计算大小分配空间是浪费，但是数据需要分配
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
	rowelts=k*w;//计算变形后列标
	rowindex=0;

	for(i=0;i<m;i++)
	{
		colindex=rowindex;
		for(j=0;j<k;j++)
		{
			elt=mat[i*k+j];//需要转化的元素
			for(x=0;x<w;x++)
			{
				for(l=0;l<w;l++)
				{
					bitmat[colindex+x+l*rowelts]=((elt&1<<l)?1:0);
				}
				elt=galois_single_multiply(elt,2,w);
			}
			colindex+=w;//进行下一个字
		}
		rowindex+=rowelts*w;
	}
	//重新赋值
	bitmatrix->matrix=bitmat;
	bitmatrix->xm=m*w;
	bitmatrix->ym=k*w;
	bitmatrix->w=w;//重新赋值
	return TRUE;
}

extern int matrix_dumb_bitmatrix_to_schedule(BITMATRIX *matrix,SCHEDULE *sch)//两种转化方法
{
	SCHEDOP *schop;
	int i,j,paranum,schsize,optodo,index;
	int rows,cols,w;
	UINT32 *mat;
	//读取参数
	mat=matrix->matrix;
	w=matrix->w;
	rows=matrix->xm;
	cols=matrix->ym;
	paranum=rows;//我们假设是编码阵

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
	schop=talloc(SCHEDOP,rows*paranum*w*w+1);//最多需要的空间
	//分配空间
	//第一步申请空间最多可能的操作是rows*cols*w*w
	if(schop==NULL)
	{
		show_error("matrix","dumb_bitmatrix_to_schedule","No memory");
		return FALSE;
	}
	sch->schedlist=schop;
	index=0;
	for(i=0;i<(paranum*w);i++)
	{
		optodo=0;//第一步是copy
		for(j=0;j<(cols*w);j++)
		{
			if(mat[index]==1)//如果需要操作
			{
				matrix_SCHUDOP_set_data(schop,optodo,j/w,j%w,cols+i/w,i%w,FALSE,NULL,0);
				optodo=1;
				schop++;
			}
			index++;
		}
	}
	//最后将w数据附上
	sch->w=w;
	return TRUE;
	
}
int matrix_smart_bitmatrix_to_schedule(BITMATRIX *matrix,SCHEDULE *sch)
{
	SCHEDOP *schop;
	int paranum,schsize;
	int rows,cols,w;
	UINT32 *mat;
	//读取参数
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
	schop=talloc(SCHEDOP,rows*paranum*w*w+1);//最多需要的空间
	//分配空间
	//第一步申请空间最多可能的操作是rows*cols*w*w
	if(schop==NULL)
	{
		show_error("matrix","dumb_bitmatrix_to_schedule","No memory");
		return FALSE;
	}
	return TRUE;
}
//性能统计
int matrix_get_stats(STATSITEM *fill_in)
{
	//读取系统统计数据
	fill_in=&systemstatic;//简单返回指正
	return TRUE;
}

//生成相应的schedule











