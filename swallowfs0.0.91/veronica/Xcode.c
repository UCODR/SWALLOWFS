#include "Xcode.h"
//���ｫXCODE���������������
int XCODE_create_encode_matrix(BITMATRIX *matrix)
{
	UINT32 *mat;
	int rows,cols,w;
	int i,j,index,x,k,resTF;

	int tarx,tary,tarindex;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	x=caldevice(rows,w);
	k=caldevice(cols,w);

	if(x!=2)
	{
		show_error("XCODE","create_encode_matrix","RAID-6 two parity device");
		return FALSE;
	}

	if((k+2)!=w)//�����ݺ���������ͻ��������P,Q��
	{
		show_error("XCODE","create_encode_matrix","X-code matrix should k+2==x");
		return FALSE;
	}
	if(mat==NULL)
	{
		mat=talloc(UINT32,rows*cols);//���ռ�
		if(mat==NULL)
		{
			show_error("XCODE","create_encode_matrix","No memory");
			return FALSE;
		}
	}
	bzero(mat,UINT32,rows*cols);//���ڴ�ռ���0
	matrix->matrix=mat;//����ָ��
	//�Ƚ���P��
	for(i=0;i<w;i++)
	{
		index=i*cols;
		for(j=0;j<w-2;j++)//������
		{
			tarx=profile_mod_number(i+j+2,w);//���߶�������
			tary=j;
			tarindex=index+tarx+tary*w;
			mat[tarindex]=1;
		}
	}
	//�ٽ���Q��
	for(i=0;i<w;i++)
	{
		index=w*cols+i*cols;
		for(j=0;j<w-2;j++)
		{
			tarx=profile_mod_number(i-j-2,w);
			tary=j;
			tarindex=index+tarx+tary*w;
			mat[tarindex]=1;
		}
	}
	return TRUE;
}

int XCODE_API(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr)
{
	return TRUE;
}
int XCODE_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr)
{
	return TRUE;
}