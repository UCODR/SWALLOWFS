#include "RDP.h"
int RDP_add_rowparity(BITMATRIX *matrix)
{
	//ÿһ��Q�̼���һ����һ�е���У��
	UINT32 *mat;
	int rows,cols,w;
	
	int i,j,tarindex,souindex,x,k;
	int isprime;
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;

	x=caldevice(rows,w);
	k=caldevice(cols,w);

	if(x!=2)
	{
		show_error("RDP","create_encode_matrix","RAID-6 two parity device");
		return FALSE;
	}
	isprime=profile_is_prime(w+1);
	if(isprime==FALSE)
	{
		show_error("EVENODD","create_encode_matrix","EVENODD code w+1 should be prime");
		return FALSE;
	}
	if(w!=k)
	{
		show_error("RDP","create_encode_matrix","RDP code w>=k");
		return FALSE;
	}
	//��ԭ�����ϴ���
	for(i=0;i<w-1;i++)//����ǰ��w-1�н��б��봦��
	{
		//һ��һ������
		tarindex=cols*w+i*cols;
		souindex=(i+1)*cols;
		for(j=0;j<cols;j++)
		{
			mat[tarindex]=mat[tarindex]^mat[souindex];
			tarindex++;
			souindex++;
		}
	}
	return TRUE;
}
int RDP_create_encode_matrix(BITMATRIX *matrix)
{
	UINT32 *mat;
	int isprime;
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
		show_error("RDP","create_encode_matrix","RAID-6 two parity devices");
		return FALSE;
	}
	
	if(w!=k)
	{
		show_error("RDP","create_encode_matrix","RDP code w!=k");
		return FALSE;
	}

	isprime=profile_is_prime(w+1);
	if(isprime==FALSE)
	{
		show_error("RDP","create_encode_matrix","RDP code w+1 should be prime number");
		return FALSE;
	}
	if(mat==NULL)
	{
		mat=talloc(UINT32,rows*cols);//���ռ�
		if(mat==NULL)
		{
			show_error("RDP","create_encode_matrix","No memory");
			return FALSE;
		}
	}
	bzero(mat,UINT32,rows*cols);//���ڴ�ռ���0
	matrix->matrix=mat;//����ָ��
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
	//����Q��
	
	for(i=0;i<w;i++)
	{
		//һ��һ������
		index=cols*w+i*cols;
		//jcount=0;//������Ҫ����
		for(j=0;j<k;j++)//����P��һ����
		{
			tarx=profile_mod_number(i-j,w+1);
			tary=j;//�ڼ����豸
			if(tarx==w)//���λ���������
			{
				continue;
			}
			tarindex=index+tarx+tary*w;
			mat[tarindex]=1;	
		}
	}
	//matrix_print_bitmatrix(matrix);
	resTF=RDP_add_rowparity(matrix);
	if(resTF==FALSE)
	{
		show_error("RDP","create_encode_matrix","row parity can't");
		return FALSE;
	}
	return TRUE;
}
int RDP_API(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr)
{
	//
	UINT32 *mat;
	BITMATRIX *matrix;

	CODEPARA *codeparamptr;
	REGION *regionptr;
	int datanum,codenum;
	int rows,cols,w,resTF;
	matrix=talloc(BITMATRIX,1);
	if(matrix==NULL)
	{
		show_error("RDP","API","No memory");
		return FALSE;
	}
	regionptr=pparityptr->regionptr;
	codeparamptr=regionptr->codepara;

	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	w=codeparamptr->w;

	rows=codenum*w;
	if(w!=datanum)
	{
		datanum=w;//�����ǰ�����ݲ����Ͼ���Ҫ�����¶���
	}
	cols=datanum*w;

	mat=talloc(UINT32,rows*cols);
	if(mat==NULL)
	{
		show_error("RDP","API","No memory");
		return FALSE;
	}

	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w=w;
	matrix->matrix=mat;

	resTF=RDP_create_encode_matrix(matrix);
	if(resTF==FALSE)
	{
		show_error("RDP","API","matrix can't create");
		return FALSE;
	}

	resTF=matrix_bitmatrix_encode_stripsect_RAID6(strsetblockgroupptr,pparityptr,qparityptr,matrix);
	if(resTF==FALSE)
	{
		show_error("RDP","API","EVENODD RAID6 can't calculate");
		return FALSE;
	}
	resTF=matrix_destroy(matrix);
	if(resTF==FALSE)
	{
		show_error("RDP","API","matrix can't free");
		return FALSE;
	}
	free(matrix);
	return TRUE;
}

int RDP_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix)
{
	return TRUE;
}

int RDP_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr)
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
		show_error("RDP","API","No memory");
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
		show_error("RDP","API","No memory");
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
		show_error("RDP","API","No memory");
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

	resTF=RDP_create_encode_matrix(matrix);
	if(resTF==FALSE)
	{
		show_error("RDP","API","matrix can't create");
		return FALSE;
	}

	resTF=UPDATE_API_bitmatrix_update_RAID6(chunkpositionblockgroupptr,
													strsetblockgroupptr,pparityptr,qparityptr,
													parityblockgroupptr,matrix);
	if(resTF==FALSE)
	{
		show_error("RDP","API","data can't update");
		return FALSE;
	}
	return TRUE;
}