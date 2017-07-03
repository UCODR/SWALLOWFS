#include "reed_sol_classic.h"
int reed_sol_r6_matrix(INTMATRIX *matrix)//��Ҫ����������RAID-6��vandermonder��
{
	//��Ҫ����������RAID-6��vandermonder��
	int i,w,tmp,rows,cols;
	UINT32 *mat;
	//erarray->datanum;//������Ӧ����
	//erarray->codenum;
	
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;
	if(w!=8&&w!=16&&w!=32)//���w����
	{
		show_error("reed_sol","matrix-r6","number w is illegal");
		return FALSE;
	}
	if(rows!=2)
	{
		show_error("reed_sol","matrix-r6","RAID-6 codenum should be 2");
		return FALSE;
	}
	if(mat!=NULL)
	{
		free(mat);
	}
	mat=talloc(UINT32,2*cols);//����һ��2�еľ���
	if(mat==NULL)
	{
		show_error("reed_sol","matrix-r6","no memory");
		return FALSE;
	}
	for(i=0;i<cols;i++)//���ڵ�һ�н���ȫ1����
	{
		mat[i]=1;
	}
	tmp=1;
	//���ɵڶ���
	for(i=0;i<cols;i++)
	{
		tmp=galois_single_multiply(tmp,2,w);
		mat[cols+i]=tmp;
	}
	//�����ݸ�ֵ����ֵ��
	matrix->matrix=mat;
	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w=w;
	return TRUE;
}
int reed_sol_vandermonde_coding_matrix(INTMATRIX *matrix)//��Ҫ��������������vandermonder����
{
	//��Ҫ��������������vandermonder����
	int i,j,w,tmp,rows,cols,resTF;
	UINT32 *mat,*vdm;//���ڴ�vandermonde�󵽱�������Ҫѹ���������洢
	INTMATRIX bigvdm;
	//erarray->datanum;//������Ӧ����
	//erarray->codenum;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;
	mat=matrix->matrix;
	if(w!=8&&w!=16&&w!=32)//���w����
	{
		show_error("reed_sol","matrix-vandermonde","number w is illegal");
		return FALSE;
	}

	//�����½�һ��matrix
	bigvdm=matrix_create_NULL();//����һ��big_vandermonde_matrix
	matrix_set_data(&bigvdm,NULL,rows+cols,cols,w);
	resTF=reed_sol_big_vandermonde_distribution_matrix(&bigvdm);//����������
	if(resTF==FALSE)//����������ʧ��
	{
		show_error("reed_sol","vandermonde_coding","big vandermonde doesn't break");
		return FALSE;
	}
	vdm=bigvdm.matrix;
	//��������Ϊ��Ҫ����big��extendedʱ����
	if(mat!=NULL)
	{
		free(mat);
	}
	mat=talloc(UINT32,rows*cols);//����һ��2�еľ���
	if(mat==NULL)
	{
		show_error("reed_sol","matrix-vandermonde","no memory");
		return FALSE;
	}
	//����
	i=cols*cols;
	for(j=0;j<rows*cols;j++)//��ȡ��Ҫ������
	{
		mat[j]=vdm[i];
		i++;
	}
	//���Թ��Ӳ�����
	matrix_destroy(&bigvdm);//�ͷſռ�
	matrix->matrix=mat;
	return TRUE;
}
int reed_sol_big_vandermonde_distribution_matrix(INTMATRIX *matrix)//����vandermonder�ֲ�����
{
	UINT32 *mat;
	UINT32 i,j,k;
	int rows,cols,w;
	UINT32 sindex,srindex,siindex,tmp;
	int resTF;
	//�����
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;
	//�ж����л�ϲ
	if(cols<rows)
	{
		show_error("reed_sol","big_vandermonde","cols<rows");
		return FALSE;
	}
	//���ɶ�Ӧ����չ����
	resTF=reed_sol_extended_vandermonde_matrix(matrix);
	if(resTF==FALSE)
	{
		show_error("reed_sol","big_vandermonde","extended matrix failed");
		return FALSE;
	}
	
	mat=matrix->matrix;//��ȡ��Ӧ����չ����
	sindex=0;
	for(i=1;i<cols;i++)//��ÿһ�л�Ϊ0
	{
		sindex+=cols;
		//�ҵ�һ�����жԽ��ߣ�i,i����Ϊ0
		srindex=sindex+i;//��λ����һλ
		for(j=i;j<rows&&mat[srindex]==0;j++) srindex+=cols;//��λ��
		if(j>=rows)//���󲻿��棬���vandermonde������ȷ�����ܳ���
		{
			show_error("reed_sol","big_vandermonde","matrix is invertible");
			return FALSE;
		}
		//�����Ҫ��������
		if(j!=i)
		{
			srindex-=i;//���˵����
			for(k=0;k<cols;k++)
			{
				tmp=mat[srindex+k];
				mat[srindex+k]=mat[sindex+k];
				mat[sindex+k]=tmp;
			}
		}
		//�����i,i������1��Ҫ������Ԫ,��ס�ǰ��б仯
		if(mat[sindex+i]!=1)
		{
			tmp=galois_inverse(mat[sindex+i],w);
			srindex=i;
			for(j=0;j<rows;j++)
			{
				mat[srindex]=galois_single_multiply(tmp,mat[srindex],w);
				srindex+=cols;
			}
		}
		//���ڵ�i���в���1��Ԫ�ض���Ҫ��0,
		//�����Ҫ���г˼�����֤0
		for(j=0;j<cols;j++)
		{
			tmp=mat[sindex+j];
			if(j!=i&&tmp!=0)
			{
				srindex=j;
				siindex=i;
				for(k=0;k<rows;k++)//��ûһ�н��е���
				{
					mat[srindex]=mat[srindex]^galois_single_multiply(tmp,mat[siindex],w);//��ԭʼ�����ݳ˼ӵ�Ŀ������
					srindex+=cols;
					siindex+=cols;
				}
			}
		}
	}
	//ϣ����k�ж���1���б任
	sindex=cols*cols;//��λ��ʼ��
	for(j=0;j<cols;j++)
	{
		tmp=mat[sindex];
		if(tmp!=1)
		{	
			if(tmp!=1)
			{
				//��֮���ͨͨ������Ԫ
				tmp=galois_inverse(tmp,w);
				srindex=sindex;
				for(i=cols;i<rows;i++)
				{
					mat[srindex]=galois_single_multiply(tmp,mat[srindex],w);//��֮������ݽ��б任
					srindex+=cols;
				}
			}
		}
		sindex++;
	}
	//�������ϣ����һ�ж���1
	sindex=cols*(cols+1);
	for(i=cols+1;i<rows;i++)
	{
		tmp=mat[sindex];
		if(tmp!=1)
		{
			tmp=galois_inverse(tmp,w);
			for(j=0;j<cols;j++)
			{
				mat[sindex+j]=galois_single_multiply(mat[sindex+j],tmp,w);
			}
		}
		sindex+=cols;
	}
	matrix->matrix=mat;//��˽���matrix��ֵ
	return TRUE;
}
int reed_sol_extended_vandermonde_matrix(INTMATRIX *matrix)//���ݾ����������ɷ���������ʽ
{
	int rows,cols,w;
	UINT32 i,j,k;
	UINT32 *mat;
	rows=matrix->xm;
	cols=matrix->ym;
	mat=matrix->matrix;
	w=matrix->w;
	if(w!=8&&w!=16&&w!=32)//���w����
	{
		show_error("reed_sol","extended_vandermonde","number w is illegal");
		return FALSE;
	}
	//�������w����
	//��Ȼ������ʵ�����Ƕ��һ�ٵ���Ϊ���ۻ��Ǽ��һ��
	if(w<31&&(1<<w)<cols)
	{
		show_error("reed_sol","extended_vandermonde","number w is not enough");
		return FALSE;
	}
	if(w<31&&(1<<w)<rows)
	{
		show_error("reed_sol","extended_vandermonde","number w is not enough");
		return FALSE;
	}
	
	if(mat!=NULL)
	{
		free(mat);
	}
	mat=talloc(UINT32,rows*cols);
	if(mat==NULL)
	{
		show_error("reed_sol","extended_vandermonde","no memory");
		return FALSE;
	}
	matrix->matrix=mat;
	mat[0]=1;//��һ�е�һ��Ϊ1����Ϊ0
	for(j=1;j<cols;j++) mat[j]=0;
	if(rows==1)//���ֻ��һ��ֱ�ӷ���
	{
		matrix->matrix=mat;
		return TRUE;
	}
	//�����������Ͼͽ����һ����Ϊ���һ����1
	i=(rows-1)*cols;//��λ�����һ��
	for(j=0;j<cols-1;j++)
	{
		mat[i+j]=0;
	}
	mat[i+j]=1;
	if(rows==2)
	{
		matrix->matrix=mat;
		return TRUE;
	}
	for(i=1;i<rows-1;i++)//�м�����vandermonde����
	{
		k=1;
		for(j=0;j<cols;j++)
		{
			mat[i*cols+j]=k;//���η��������
			k=galois_single_multiply(k,i,w);
		}
	}
	matrix->matrix=mat;
	return TRUE;
}

//��Ӧ��Ӧ��r6ϵͳ���б���
int reed_sol_r6_encode_w(CHUNKBLOCKGROUP *datachk,CHUNK *pchunkptr,CHUNK *qchunkptr,int w)
{
	int i,datanum,paranum,resTF;
	CHUNKBLOCK *datachklist,*curdatachklist;
	CHUNK *datachunkptr;

	//��ȡ����
	datachklist=datachk->chunkblockptr;//��ȡchunk�б�ָ��
	//parachklist=parachk->chunkblockptr;
	datanum=datachk->groupsize;
	//paranum=parachk->groupsize;
	
	if(datachklist==NULL)
	{
		show_error("reed_sol","r6_encode","datachunk==NULL");
		return FALSE;
	}
	if(paranum!=2)
	{
		show_error("reed_sol","r6_encode","r6 should be 2 parity chunk");
		return FALSE;
	}
	if(pchunkptr==NULL)//��Ȼ��̫���ܻ���Ҫ����
	{
		pchunkptr=talloc(CHUNK,1);
		if(pchunkptr==NULL)
		{
			show_error("reed_sol","r6_encode","No memory");
			return FALSE;
		}
	}
	if(qchunkptr==NULL)
	{
		qchunkptr=talloc(CHUNK,1);
		if(qchunkptr==NULL)
		{
			show_error("reed_sol","r6_encode","No memory");
			return FALSE;
		}
	}

	if(w!=8&&w!=16&&w!=32)
	{
		show_error("reed_sol","r6_encode","w should be 8,16 or 32");
		return FALSE;
	}
	curdatachklist=datachklist;
	//��ʼ�����������Ϊ�򵥲��ü���
	datachunkptr=curdatachklist->chunkptr;
	//��ʼ�����һ��,������Ҫ����
	resTF=matrix_CHUNK_copy_data(pchunkptr,datachunkptr);//����һ��chunk���п���
	if(resTF==FALSE)
	{
		show_error("reed_sol","r6_encode","chunk data can't copy");
		return FALSE;
	}
	for(i=1;i<datanum;i++)
	{
		curdatachklist++;//����һλ
		datachunkptr=curdatachklist->chunkptr;
		resTF=matrix_CHUNK_add_data(pchunkptr,datachunkptr);
		if(resTF==FALSE)
		{
			show_error("reed_sol","r6_encode","chunk data can't add");
			return FALSE;
		}
	}
	curdatachklist=datachklist;
	//parachklist++;//��ָ�붨λ����һ��λ��
	datachunkptr=curdatachklist->chunkptr;
	//����Ŀ��chunk2
	resTF=matrix_CHUNK_copy_data(qchunkptr,datachunkptr);//����һ��chunk���п���
	if(resTF==FALSE)
	{
		show_error("reed_sol","r6_encode_w","chunk data can't copy");
		return FALSE;
	}
	//�������CHUNK���г�2��
	for(i=1;i<datanum;i++)
	{
		curdatachklist++;
		datachunkptr=curdatachklist->chunkptr;
		switch(w)
		{
		//��У���*2+������
		case 8: matrix_CHUNK_w08_multiply(qchunkptr,2);break;
		case 16:matrix_CHUNK_w16_multiply(qchunkptr,2);break;
		case 32:matrix_CHUNK_w32_multiply(qchunkptr,2);break;
		}
		matrix_CHUNK_add_data(qchunkptr,datachunkptr);
	}
}
//��Ӧ��Ӧ��r6ϵͳ���б��벢�ҽ�r6���󱣴���para��
int reed_sol_r6_encode(CHUNKBLOCKGROUP *datachk,CHUNK *pchunkptr,CHUNK *qchunkptr,ENDECODEPARA *para)//��Ӧ��Ӧ��r6ϵͳ���б��벢�ҽ�r6���󱣴���para��
{
	int datanum,w,resTF;
	INTMATRIX *mat; 
	//������Ӧ�ľ��󲢼�¼
	//��ȡ����������raid-6ֻ��w
	w=para->w;
	resTF=reed_sol_r6_encode_w(datachk,pchunkptr,qchunkptr,w);
	if(resTF==FALSE)
	{
		show_error("reed_sol","r6_encode","data can't encode");
		return FALSE;
	}

	para->matrix=talloc(INTMATRIX,1);//����һ���ռ�
	mat=para->matrix;
	datanum=datachk->groupsize;
	//��Ҫ����mat�趨��ʼ������
	matrix_set_data(mat,NULL,2,datanum,w);
	resTF=reed_sol_r6_matrix(mat);
	if(resTF==FALSE)//�������ʧ����ô�ͱ���
	{
		show_error("reed_sol","r6_encode","can't create r6 matrix");
		return FALSE;
	}
	para->matrix=mat;
	return TRUE;
}
//��ͬ��Plank��ʦ������Ҫ�����ݷ�װ��API
//������Ӧ��r6���н���
int reed_sol_r6_decode_w(CHUNKBLOCKGROUP *datachk,CHUNKBLOCKGROUP *parachk,int w,ERASES *erarray)
{
	//����r6�����ָ�
	return TRUE;
}
//������Ӧ��r6���н��벢�ҽ�������󱣴���para��
int reed_sol_r6_decode(CHUNKBLOCKGROUP *datachk,CHUNK *pchunkptr,CHUNK *qchunkptr,ENDECODEPARA *para,ERASES *erarray)
{
	
	return TRUE;
}

//����datachk��parachk�Ĵ�С���б��벢�ҽ�������󱣴���para��
int reed_sol_van_encode(CHUNKBLOCKGROUP *datachk,CHUNKBLOCKGROUP *parachk,ENDECODEPARA *para)
{
	//���������
	INTMATRIX *enmatrix;
	int w,resTF;
	int datanum,codenum,totnum;

	w=para->w;
	
	datanum=datachk->groupsize;
	codenum=parachk->groupsize;
	totnum=datanum+codenum;
	
	enmatrix=talloc(INTMATRIX,1);
	if(enmatrix==NULL)
	{
		show_error("reed_sol","van_encode","No memory");
		return FALSE;
	}
	//enmatrix=matrix_create_NULL();
	matrix_set_data(enmatrix,NULL,codenum,datanum,w);//�趨�������Ĳ���
	resTF=reed_sol_vandermonde_coding_matrix(enmatrix);//����һ���������
	if(resTF==FALSE)
	{
		show_error("eed_sol","van_encode","coding matrix can't create");
		return FALSE;
	}
	resTF=matrix_matrix_encode_BLOCK(parachk,datachk,enmatrix);
	if(resTF==FALSE)
	{
		show_error("reed_sol","van_encode","No memory");
		return FALSE;
	}
	return TRUE;
}

//����datachk��parachk�Ĵ�С���б���
int reed_sol_van_encode_w(CHUNKBLOCKGROUP *datachk,CHUNKBLOCKGROUP *parachk,int w)
{
	
	//INTMATRIX enmatrix;
	int resTF;
	ENDECODEPARA *para;
	para=talloc(ENDECODEPARA,1);
	if(para==NULL)
	{
		show_error("reed_sol","van_encode_w","No memory");
		return FALSE;
	}
	para->w=w;

	resTF=reed_sol_van_encode(datachk,parachk,para);
	if(resTF==FALSE)
	{
		show_error("reed_sol","van_encode_w","RS code can't run");
	}
	free(para);
	return TRUE;
}

int reed_sol_van_decode_w(CHUNKBLOCKGROUP *datachk,CHUNKBLOCKGROUP *parachk,int w,ERASES *erarray)
{
	return TRUE;
}
//������Ӧ��van���н���
int reed_sol_van_decode(CHUNKBLOCKGROUP *datachk,CHUNKBLOCKGROUP *parachk,ENDECODEPARA *para,ERASES *erarray)
{
	INTMATRIX *enmatrix;//�������
	INTMATRIX *dematrix;//�������

	int w;
	//�������
	return TRUE;
}
//classic RS����raid6�ӿ�
int reed_sol_API_RAID6(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr)
{
	INTMATRIX *matrix;//�ü�¼��ǰ��ǰ����
	CODEPARA *codeparam;

	REGION *regionptr;
	//STRIP *stripptr;

	//CHUNK *pchunkptr,*qchunkptr;
	CHUNKBLOCK *datachklist,*curdatachklist;
	CHUNKBLOCKGROUP *datachunkgroupptr;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr,*pchunkptr,*qchunkptr;

	STRIPSECTBLOCK *stripsectblockptr,*curstripsectblockptr;
	STRIPSECT *strsetptr;

	int i,w,datanum,resTF;

	datanum=strsetblockgroupptr->groupsize;
	//��ȡ٤�޻���С
	regionptr=pparityptr->regionptr;
	codeparam=regionptr->codepara;
	w=codeparam->w;
	//codenum=2;
	datachklist=talloc(CHUNKBLOCK,datanum);
	if(datachklist==NULL)
	{
		show_error("reed","sol_API_RAID6","No memory");
		return FALSE;
	}
	datachunkgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(datachunkgroupptr==NULL)
	{
		show_error("reed","sol_API_RAID6","No memory");
		return FALSE;
	}
	datachunkgroupptr->chunkblockptr=datachklist;
	datachunkgroupptr->groupsize=datanum;
	//��ȡ����ָ��
	chunkgroupptr=pparityptr->chunklist;
	pchunkptr=chunkgroupptr->ckgroup;//ȡ������

	chunkgroupptr=qparityptr->chunklist;
	qchunkptr=chunkgroupptr->ckgroup;
	
	//����chunkָ��
	//�����ڲ��ı��뺯��
	stripsectblockptr=strsetblockgroupptr->stripsectblockptr;
	//��ָ����Ե���ʼλ��
	curstripsectblockptr=stripsectblockptr;
	curdatachklist=datachklist;
	for(i=0;i<datanum;i++)
	{
		strsetptr=curstripsectblockptr->stripsectptr;

		chunkgroupptr=strsetptr->chunklist;
		chunkptr=chunkgroupptr->ckgroup;

		curdatachklist->chunkptr=chunkptr;
		curdatachklist->chunkid=chunkptr->ChunkID;

		curdatachklist++;
		curstripsectblockptr++;
	}
	//���Կ�ʼ�������ݿ���м�����
	resTF=reed_sol_r6_encode_w(datachunkgroupptr,pchunkptr,qchunkptr,w);
	if(resTF==FALSE)
	{
		show_error("reed_sol","API_RAID6","CLASSIC RS can't calculate");
		return FALSE;
	}
	return TRUE;
}
//����RS����ӿ�
int reed_sol_API(STRIP *stripptr)
{
	INTMATRIX *matrix;
	//CODEPARA *codeparam;

	REGION *regionptr;
	CODEPARA *codeparam;

	CHUNKBLOCK *codeblockptr,*curcodeblockptr;
	CHUNKBLOCKGROUP *codeblockgroupptr;

	CHUNKBLOCK *datablockptr,*curdatablockptr;
	CHUNKBLOCKGROUP *datablockgroupptr;

	CHUNKGROUP *chunkgroupptr;
	CHUNK *chunkptr;

	int i,resTF,datanum,codenum,totnum,w,isparity;

	regionptr=stripptr->regionptr;
	codeparam=regionptr->codepara;

	datanum=codeparam->datanum;
	codenum=codeparam->codenum;
	totnum=datanum+codenum;
	w=codeparam->w;

	chunkgroupptr=stripptr->chunklist;
	totnum=chunkgroupptr->groupsize;

	datablockptr=talloc(CHUNKBLOCK,datanum);
	if(datablockptr==NULL)
	{
		show_error("reed_sol","API","No memory");
		return FALSE;
	}

	datablockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(datablockgroupptr==NULL)
	{
		show_error("reed_sol","API","No memory");
		return FALSE;
	}
	datablockgroupptr->chunkblockptr=datablockptr;
	datablockgroupptr->groupsize=datanum;

	codeblockptr=talloc(CHUNKBLOCK,codenum);
	if(codeblockptr==NULL)
	{
		show_error("reed_sol","API","No memory");
		return FALSE;
	}
	codeblockgroupptr=talloc(CHUNKBLOCKGROUP,1);
	if(codeblockgroupptr==NULL)
	{
		show_error("reed_sol","API","No memory");
		return FALSE;
	}
	codeblockgroupptr->chunkblockptr=codeblockptr;
	codeblockgroupptr->groupsize=codenum;


	curdatablockptr=datablockptr;
	curcodeblockptr=codeblockptr;
	chunkptr=chunkgroupptr->ckgroup;//��ǰУ���
	//�������ݿ�ָ��
	for(i=0;i<totnum;i++)
	{
		isparity=chunkptr->isparity;
		if(isparity==FALSE)
		{
			curdatablockptr->chunkptr=chunkptr;
			curdatablockptr->chunkid=chunkptr->ChunkID;
			curdatablockptr++;
		}
		else
		{
			curcodeblockptr->chunkptr=chunkptr;
			curcodeblockptr->chunkid=chunkptr->ChunkID;
			curcodeblockptr++;
		}
		chunkptr++;
	}
	
	resTF=reed_sol_van_encode_w(datablockgroupptr,codeblockgroupptr,w);
	if(resTF==FALSE)
	{
		show_error("reed_sol","API","codeblock can't encode");
		return FALSE;
	}
	return TRUE;
}

int reed_sol_degrade_API_RAID6(CHUNK *chunkptr,ERRORPATTERN *errormatrix)
{
	return TRUE;
}
int reed_sol_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix)
{
	return TRUE;
}

//RAID6��update����
int reed_sol_update_API_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr)
{
	return TRUE;
}
//update����
extern int reed_sol_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr)
{
	return TRUE;
}
//����API
int reed_sol_decoder_API_strip(STRIP *stripptr,ERRORPATTERN *errormatrix)
{
	return TRUE;
}
//����RS����ӿ�
int reed_sol_decoder_API_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix)
{
	return TRUE;
}