#include "GEN_RDP.h"
//������Ӧ��GENRDP�����������a family of MDS array codes with minimal Number 
int GENRDP_P_disk_add(BITMATRIX *matrix,int tarindex,int souindex)
{
	int i;
	UINT32 *mat;
	int rows,cols,w;

	int cursouindex,curtarindex;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;
	for(i=0;i<cols;i++)
	{
		cursouindex=souindex+i;
		curtarindex=tarindex+i;
		mat[curtarindex]=mat[curtarindex]^mat[cursouindex];
	}
	return TRUE;
}

int GENRDP_create_parity_disk(BITMATRIX *matrix,int num)//���ɵ�i��QУ����
{
	int i,j,l,k,x,resTF;

	UINT32 *mat;
	int rows,cols,w;

	int tarx,tary,tarindex,index;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	j=num+1;//��ǰλ��

	x=caldevice(rows,w);//�����豸��У�����
	k=caldevice(cols,w);

	for(i=0;i<w;i++)//����w��
	{
		//һ��һ������
		index=cols*w*j+i*cols;//���ɳ�ʼ����
		//jcount=0;//������Ҫ����
		
		
		for(l=0;l<k+1;l++)//����P��һ����
		{
			tarx=profile_mod_number(i-j*l,w+1);
			tary=l;//�ڼ����豸
			if(tarx==w)//���λ���������
			{
				continue;
			}
			if(tary==k)//˵����Ҫ���ɵ��Ǽ������P��
			{
				resTF=GENRDP_P_disk_add(matrix,index,tarx*cols);
				if(resTF==FALSE)
				{
					show_error("GENRDP","create_parity_disk","P disk parity information can't create");
					return FALSE;
				}
			}
			else
			{
				tarindex=index+tarx+tary*w;
				mat[tarindex]=1;	
			}
		}

	}
	return TRUE;
}

int GENRDP_create_encode_matrix(BITMATRIX *matrix)
{
	int i,isprime,resTF;
	int rows,cols,w;
	UINT32 *mat;
	int j,k,x;

	int index;

	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	x=caldevice(rows,w);
	k=caldevice(cols,w);

	/*if(x!=3)
	{
		show_error("GENRDP","create_encode_matrix","Generalized RDP code three parity devices");
		return FALSE;
	}*/

	isprime=profile_is_prime(w+1);
	if(isprime==FALSE)
	{
		show_error("GENRDP","create_encode_matrix","Generalized RDP code w+1 should be prime");
		return FALSE;
	}
	if(k!=w)
	{
		show_error("GENRDP","create_encode_matrix","Generalized RDP code w=k");
		return FALSE;
	}
	//��ʼ���ݶ������
	if(mat==NULL)
	{
		mat=talloc(UINT32,rows*cols);
		if(mat==NULL)
		{
			show_error("GENRDP","create_encode_matrix","No memory");
			return FALSE;
		}
	}
	bzero(mat,UINT32,rows*cols);
	//��������
	for(i=0;i<w;i++)
	{
		index=i*cols+i;
		for(j=0;j<k;j++)
		{
			mat[index]=1;
			index+=w;
		}
	}
	for(i=0;i<(x-1);i++)//����x-1��p��
	{
		resTF=GENRDP_create_parity_disk(matrix,i);
		if(resTF==FALSE)
		{
			show_error("GENRDP","create_encode_matrix","Q parity can't calculate");
			return FALSE;
		}
	}
	return TRUE;
}

//����һ�������е�У���
int GENRDP_API(STRIP *stripptr)
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

	if(w!=datanum)
	{
		datanum=w;//���¶�λ
	}
	matrix=talloc(BITMATRIX,1);
	if(matrix==NULL)
	{
		show_error("GENRDP","API","No memory");
		return FALSE;
	}
	if(datanum!=w)
	{
		datanum=w;//ǿ�����
	}
	rows=codenum*w;
	cols=datanum*w;
	mat=talloc(UINT32,rows*cols);
	if(mat==NULL)
	{
		show_error("GENRDP","API","No memory");
		return FALSE;
	}
	matrix->matrix=mat;
	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w=w;
	resTF=GENRDP_create_encode_matrix(matrix);
	if(resTF==FALSE)
	{
		show_error("GENRDP","API","matrix can't create");
		return FALSE;
	}
	free(matrix);
	free(mat);
	return TRUE;
}
//������
int GENRDP_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix)
{
	return TRUE;
}
//ʵ�ָ���
int GENRDP_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr)
{
	int resTF;
	BITMATRIX *matrix;

	REGION *regionptr;

	int datanum,codenum;
	CODEPARA *codeparamptr;

	UINT32 *mat;
	int rows,cols,w;

	regionptr=stripptr->regionptr;
	codeparamptr=regionptr->codepara;

	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	w=codeparamptr->w;

	if(w!=datanum)
	{
		datanum=w;//���¶�λ
	}
	matrix=talloc(BITMATRIX,1);
	if(matrix==NULL)
	{
		show_error("GENRDP","API","No memory");
		return FALSE;
	}
	if(datanum!=w)
	{
		datanum=w;//ǿ�����
	}
	rows=codenum*w;
	cols=datanum*w;
	mat=talloc(UINT32,rows*cols);
	if(mat==NULL)
	{
		show_error("GENRDP","API","No memory");
		return FALSE;
	}

	matrix->matrix=mat;
	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w=w;
	resTF=GENRDP_create_encode_matrix(matrix);
	if(resTF==FALSE)
	{
		show_error("GENRDP","API","matrix can't create");
		return FALSE;
	}

	resTF=matrix_bitmatrix_update_strip(chunkpositionblockgroupptr,stripptr,parityblockgroupptr,matrix);
	if(resTF==FALSE)
	{
		show_error("GENRDP","update_API","strip can't update");
		return FALSE;
	}
	free(matrix);
	free(mat);
	return TRUE;
}