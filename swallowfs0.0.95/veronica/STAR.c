#include "STAR.h"
//将第二个祖母块加到第三个矩阵上
int STAR_add_second_grandmother(BITMATRIX *matrix)
{
	int resTF,isprime,x,k;
	int i,j,windex,index;

	UINT32 *mat;
	int rows,cols,w;

	int tarx,tary,tarindex;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	x=caldevice(rows,w);
	k=caldevice(cols,w);

	if(x!=3)
	{
		show_error("STAR","create_encode_matrix","STAR code three parity devices");
		return FALSE;
	}
	if((w+1)!=k)
	{
		show_error("STAR","create_encode_matrix","STAR code should be r+1=k");
		return FALSE;
	}
	isprime=profile_is_prime(w+1);
	if(isprime==FALSE)
	{
		show_error("STAR","create_encode_matrix","Generalized RDP code w+1 should be prime");
		return FALSE;
	}
	for(i=0;i<w;i++)
	{
		index=2*w*cols+i*cols;//跳开当前的矩阵
		for(j=0;j<(w+1);j++)//w
		{
			tarx=profile_mod_number(j-1,w+1);
			tary=j;
			if(tarx==w)
			{
				continue;
			}
			tarindex=index+tarx+tary*w;
			mat[tarindex]=mat[tarindex]^1;
		}
	}
	return TRUE;
}
//计算matrix相应的第三个校验块
int STAR_calculate_third_parity_matrix(BITMATRIX *matrix)
{
	int resTF,isprime,x,k;
	int i,j,windex,index;

	UINT32 *mat;
	int rows,cols,w;

	int tarx,tary,tarindex;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	x=caldevice(rows,w);
	k=caldevice(cols,w);

	if(x!=3)
	{
		show_error("STAR","create_encode_matrix","STAR code three parity devices");
		return FALSE;
	}
	if((w+1)!=k)
	{
		show_error("STAR","create_encode_matrix","STAR code should be r+1=k");
		return FALSE;
	}
	isprime=profile_is_prime(w+1);
	if(isprime==FALSE)
	{
		show_error("STAR","create_encode_matrix","Generalized RDP code w+1 should be prime");
		return FALSE;
	}

	for(i=0;i<w;i++)
	{
		index=2*w*cols+i*cols;//跳开当前的矩阵
		for(j=0;j<(w+1);j++)//w
		{
			tarx=profile_mod_number(i+j,w+1);
			tary=j;
			if(tarx==w)
			{
				continue;
			}
			tarindex=index+tarx+tary*w;
			mat[tarindex]=1;
		}
	}
	resTF=STAR_add_second_grandmother(matrix);
	if(resTF==FALSE)
	{
		show_error("STAR","calculate_third_parity_matrix","matrix can't grandfather");
		return FALSE;
	}
	return TRUE;
}
//生成相应的STAR编码矩阵
int STAR_create_encode_matrix(BITMATRIX *matrix)
{
	int isprime,resTF;
	int rows,cols,w;
	UINT32 *mat;

	BITMATRIX *evenoddmatrix;
	UINT32 *evenoddmat;
	int evenrows,evencols;

	int k,x;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	x=caldevice(rows,w);
	k=caldevice(cols,w);

	if(x!=3)
	{
		show_error("STAR","create_encode_matrix","STAR code three parity devices");
		return FALSE;
	}
	if((w+1)!=k)
	{
		show_error("STAR","create_encode_matrix","STAR code should be r+1=k");
		return FALSE;
	}
	isprime=profile_is_prime(w+1);
	if(isprime==FALSE)
	{
		show_error("STAR","create_encode_matrix","Generalized RDP code w+1 should be prime");
		return FALSE;
	}
	if(mat==NULL)
	{
		mat=talloc(UINT32,rows*cols);
		if(mat==NULL)
		{
			show_error("STAR","create_encode_matrix","No memory");
			return FALSE;
		}
		matrix->matrix=mat;
	}
	bzero(mat,UINT32,rows*cols);//将内存空间清0
	matrix->matrix=mat;//调整指针
	//下一步先生成EVENODD编码阵
	evenoddmatrix=talloc(BITMATRIX,1);
	if(evenoddmatrix==NULL)
	{
		show_error("STAR","create_encode_matrix","No memory");
		return FALSE;
	}
	evenrows=2*w;
	evencols=cols;

	evenoddmat=talloc(UINT32,evenrows*evencols);
	if(evenoddmat==NULL)
	{
		show_error("STAR","create_encode_matrix","No memory");
		return FALSE;
	}
	evenoddmatrix->matrix=evenoddmat;
	evenoddmatrix->xm=evenrows;
	evenoddmatrix->ym=evencols;
	evenoddmatrix->w=w;
	resTF=EVENODD_create_encode_matrix(evenoddmatrix);
	if(resTF==FALSE)
	{
		show_error("STAR","create_encode_matrix","EVENODD matrix can't create");
		return FALSE;
	}
	resTF=matrix_bitmatrix_data_copy(matrix,evenoddmatrix,0,evenrows*evencols);
	if(resTF==FALSE)
	{
		show_error("STAR","create_encode_matrix","bitmatrix can't copy");
		return FALSE;
	}
	resTF=STAR_calculate_third_parity_matrix(matrix);
	if(resTF==FALSE)
	{
		show_error("STAR","create_encode_matrix","third parity bitmatrix can't create");
		return FALSE;
	}
	free(evenoddmatrix);
	free(evenoddmat);
	return TRUE;
}
//计算一个条带中的校验块
extern int STAR_API(STRIP *stripptr)
{
	int resTF;
	BITMATRIX *matrix;

	UINT32 *mat;
	int rows,cols,w;

	REGION *regionptr;
	CODEPARA *codeparamptr;

	int datanum,codenum;

	regionptr=stripptr->regionptr;
	codeparamptr=regionptr->codepara;

	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	w=codeparamptr->w;

	if(w!=(datanum-1))
	{
		datanum=w+1;//重新定位
	}
	rows=codenum*w;
	cols=datanum*w;
	mat=talloc(UINT32,rows*cols);
	if(mat==NULL)
	{
		show_error("STAR","API","No memory");
		return FALSE;
	}
	matrix->matrix=mat;
	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w=w;

	resTF=STAR_create_encode_matrix(matrix);
	if(resTF==FALSE)
	{
		show_error("STAR","API","matrix can't create");
		return FALSE;
	}
	resTF=matrix_bitmatrix_encode_strip(stripptr,matrix);
	if(resTF==FALSE)
	{
		show_error("STAR","API","STAR code can't calculate");
		return FALSE;
	}
	resTF=matrix_destroy(matrix);
	if(resTF==FALSE)
	{
		show_error("STAR","API","matrix can't free");
		return FALSE;
	}
	return TRUE;
}
//降级读
extern int STAR_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix)
{
	return TRUE;
}
//实现更新
extern int STAR_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr)
{
	//
	//UINT32 *mat;

	return TRUE;
}