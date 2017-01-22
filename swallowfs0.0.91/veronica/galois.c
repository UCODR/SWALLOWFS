/*
This program is created by Jiajie Shen 
2014.11.23
��ѽܴ���2014.11.23
*/
/*
reference FAST08 Plank Galois lab
�ο�FAST08 Plank Galois ����Ҫʵ��GF������
ѡ��ο���������Ҫԭ��������Ч��
ʹ��log���ƺͲ����ɵ�Galois��ҪЧ���������������������
*/
#include "galois.h"
//����˷�����
//�˷���ѯ�б�
static UINT32 mult_type[33] = 
{ NONE, 
/*  1 */   TABLE, 
/*  2 */   TABLE,
/*  3 */   TABLE,
/*  4 */   TABLE,
/*  5 */   TABLE,
/*  6 */   TABLE,
/*  7 */   TABLE,
/*  8 */   TABLE,
/*  9 */   TABLE,
/* 10 */   LOGS,
/* 11 */   LOGS,
/* 12 */   LOGS,
/* 13 */   LOGS,
/* 14 */   LOGS,
/* 15 */   LOGS,
/* 16 */   LOGS,
/* 17 */   LOGS,
/* 18 */   LOGS,
/* 19 */   LOGS,
/* 20 */   LOGS,
/* 21 */   LOGS,
/* 22 */   LOGS,
/* 23 */   SHIFT,
/* 24 */   SHIFT,
/* 25 */   SHIFT,
/* 26 */   SHIFT,
/* 27 */   SHIFT,
/* 28 */   SHIFT,
/* 29 */   SHIFT,
/* 30 */   SHIFT,
/* 31 */   SHIFT,
/* 32 */   SPLITW8 };

//������Ӧ������λ��
static UINT32 nw[33]={0, (1 << 1), (1 << 2), (1 << 3), (1 << 4), 
(1 << 5), (1 << 6), (1 << 7), (1 << 8), (1 << 9), (1 << 10),
(1 << 11), (1 << 12), (1 << 13), (1 << 14), (1 << 15), (1 << 16),
(1 << 17), (1 << 18), (1 << 19), (1 << 20), (1 << 21), (1 << 22),
(1 << 23), (1 << 24), (1 << 25), (1 << 26), (1 << 27), (1 << 28),
(1 << 29), (1 << 30), (1 << 31), -1};
//������Ӧ������
static UINT32 nwml[33]={0, (1 << 1)-1, (1 << 2)-1, (1 << 3)-1, (1 << 4)-1, 
(1 << 5)-1, (1 << 6)-1, (1 << 7)-1, (1 << 8)-1, (1 << 9)-1, (1 << 10)-1,
(1 << 11)-1, (1 << 12)-1, (1 << 13)-1, (1 << 14)-1, (1 << 15)-1, (1 << 16)-1,
(1 << 17)-1, (1 << 18)-1, (1 << 19)-1, (1 << 20)-1, (1 << 21)-1, (1 << 22)-1,
(1 << 23)-1, (1 << 24)-1, (1 << 25)-1, (1 << 26)-1, (1 << 27)-1, (1 << 28)-1,
(1 << 29)-1, (1 << 30)-1, 0x7fffffff, 0xffffffff};
//����logtable
static UINT32 *galois_log_tables[33]={NULL, NULL, NULL, NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
//����ilogtable
static UINT32 *galois_ilog_tables[33]={NULL, NULL, NULL, NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
//���ɳ˷���
static UINT32 **galois_mult_tables[33]={NULL, NULL, NULL, NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
//���ɳ�����
static UINT32 **galois_div_tables[33]={NULL, NULL, NULL, NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
//��¼w8���ݱ�
static UINT32 *galois_split_w8[8]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
//��¼���е�����
static UINT32 prim_poly[33] = 
{ 0, 
/*  1 */     1, 
/*  2 */    07,
/*  3 */    013,
/*  4 */    023,
/*  5 */    045,
/*  6 */    0103,
/*  7 */    0211,
/*  8 */    0435,
/*  9 */    01021,
/* 10 */    02011,
/* 11 */    04005,
/* 12 */    010123,
/* 13 */    020033,
/* 14 */    042103,
/* 15 */    0100003,
/* 16 */    0210013,
/* 17 */    0400011,
/* 18 */    01000201,
/* 19 */    02000047,
/* 20 */    04000011,
/* 21 */    010000005,
/* 22 */    020000003,
/* 23 */    040000041,
/* 24 */    0100000207,
/* 25 */    0200000011,
/* 26 */    0400000107,
/* 27 */    01000000047,
/* 28 */    02000000011,
/* 29 */    04000000005,
/* 30 */    010040000007,
/* 31 */    020000000011, 
/* 32 */    040020000007 }; //��סC��0��ͷ��8�˽�����
//��֤galois�ϱ��������
void galois_region_xor(           char *r1,         /* Region 1 */
                                  char *r2,         /* Region 2 */
                                  char *target,         /* Sum region (r3 = r1 ^ r2) -- can be r1 or r2 ����*/
                                  UINT32 nbytes)       /* Number of bytes in region ���ٸ��ֽڽ������*/
{
	//����xor����
	short *s1;//8Ϊһ��Դ�ļ�Ϊlong����һ�����㲻ͬ������
	short *s2;
	short *s3;
	short *stop;
	char *ctop;
	//�����ַλ��
	ctop = r1 + nbytes;
	stop = (short *) ctop;
	s1 = (short *) r1;
	s2 = (short *) r2;
	s3 = (short *) target;
 
	 while (s1 < stop)
	 {
		*s3 = ((*s1)  ^ (*s2));
		s1++;
		s2++;
		s3++;
	 }
}
//�Ӽ���ֱ�������
UINT32 galois_region_subtract(BYTE *des,BYTE *sou,UINT32 nbytes)
{
	//char res;
	//char r1,r2,target;
	//r1=x;
	//r2=y;
	galois_region_xor(des,sou,des,nbytes);
	//res=target;
	return TRUE;
}
UINT32 galois_region_add(BYTE *des,BYTE *sou,UINT32 nbytes)
{
	//char res;
	//char r1,r2,target;
	//r1=x;
	//r2=y;
	galois_region_xor(des,sou,des,nbytes);
	//res=target;
	return TRUE;
}



//��plank�㷨��log��multtable
//ʵ��log���ĳ˳���
void galois_log_intial()
{
	//����log��ilog��
	UINT32 i=0;
	for(i=0;i<25;i++)
	{
		//����0-22
		UINT32 j=galois_logtable_create(i);
		//printf("%d",j);
	}

}
UINT32 galois_logtable_create(UINT32 w)//������w�µ�log��ilog��
{
	//������Ӧ��log��ilog��
	UINT32 i=0,b=1;
	if(w>32) return FALSE;
	if(galois_log_tables[w]!=NULL) return TRUE;//�Ѿ�����
	galois_log_tables[w]=(UINT32 *)malloc(sizeof(UINT32)*nw[w]);//������ش洢����
	if(galois_log_tables[w]==NULL) return FALSE;
	
	galois_ilog_tables[w]=(UINT32 *)malloc(sizeof(UINT32)*nw[w]*3);//�ռ���������
	if(galois_ilog_tables[w]==NULL)
	{
		//�ع�
		free(galois_log_tables[w]);
		galois_log_tables[w]=NULL;
		return FALSE;
	}
	for(i=0;i<nw[w];i++)
	{
		galois_log_tables[w][i]=nwml[w];
		galois_ilog_tables[w][i]=0;
	}
	b=1;
	for(i=0;i<nwml[w];i++)
	{
		//������Ӧ��
		//���������λ�Ƿ����
		if(galois_log_tables[w][b]!=nwml[w])//���λ���ǷǱ�ռ
		{
			show_error("galois","logtables","nwoccupy");
			return FALSE;
		}
		galois_log_tables[w][b]=i;
		galois_ilog_tables[w][i]=b;
		b=b<<1;//����1λ
		if(b&nw[w])
		{
			//���bֵ�Ѿ�������������Ҫ����
			b=(b^prim_poly[w])&nwml[w];//ʹ������Ԫ����
		}
	}
	for(i=0;i<nwml[w];i++)//��ԭ��������
	{
		galois_ilog_tables[w][i+nwml[w]]=galois_ilog_tables[w][i];
		galois_ilog_tables[w][i+nwml[w]*2]=galois_ilog_tables[w][i];
	}
	galois_ilog_tables[w]+=nwml[w];//���ݱ�ָ���������ǰ����nwml[w]λ�ˡ�
	return TRUE;
}
//��ȡw��ilogtable
UINT32* galois_ilog_table(UINT32 w)
{
	if(galois_ilog_tables[w]==NULL)//���û��
	{
		if(galois_logtable_create(w)==FALSE)//���û�д����ɹ�
		{
			show_error("galois","ilogtables","toobig");
			return FALSE;
		}
	}
	return galois_ilog_tables[w];
}
//��ȡw��logtable
UINT32* galois_log_table(UINT32 w)
{
	if(galois_log_tables[w]==NULL)//���û��
	{
		if(galois_logtable_create(w)==FALSE)//���û�д����ɹ�
		{
			show_error("galois","logtables","toobig");
			return FALSE;
		}
	}
	return galois_log_tables[w];
}

UINT32 galois_log_multiply(UINT32 x,UINT32 y,UINT32 w)//ʵ��logtable�˷�
{
	int sum_log;//���ڴ洢
	if(x==0||y==0) return 0;//�������0Ԫ���򷵻�0
	if(galois_ilog_tables[w]==NULL)//���û��
	{
		if(galois_logtable_create(w)==FALSE)//���û�д����ɹ�
		{
			show_error("galois","logtables","toobig");
			return FALSE;
		}
	}
	if(x>nwml[w]||y>nwml[w])//�������Ԫ��Χ
	{
		show_error("galois","multiply","outrange");
		return FALSE;
	}
	sum_log=galois_log_tables[w][x]+galois_log_tables[w][y];

	return galois_ilog_tables[w][sum_log];
}

UINT32 galois_log_divide(UINT32 x,UINT32 y,UINT32 w)//ʵ��logtable����
{
	int minus_log;//���ڴ洢
	if(x==0||y==0) return 0;//�������0Ԫ���򷵻�0
	if(galois_ilog_tables[w]==NULL)//���û��
	{
		if(galois_logtable_create(w)==FALSE)//���û�д����ɹ�
		{
			show_error("galois","logtables","toobig");
		}
	}
	if(x>nwml[w]||y>nwml[w])//�������Ԫ��Χ
	{
		show_error("galois","divide","outrange");
		return FALSE;
	}
	minus_log=galois_log_tables[w][x]-galois_log_tables[w][y];

	return galois_ilog_tables[w][minus_log];
}

//��ʵ�ֲ��˷�
//��ʼ���������˷���
void galois_multtable_intial()
{
	UINT32 i=0,res;//��ʼ���˷����
	for(i=0;i<10;i++)
	{
		res=galois_multtable_create(i);
		//printf("%d",res);
	}
}
UINT32 galois_multtable_create(UINT32 w)//����w�˷���
{
	//��ʼ��w��mult��divide
	UINT32 i,x,y,logx,res;
	if (w>14) return FALSE;//̫��
	if(galois_mult_tables[w]!=NULL) return TRUE;//�Ѿ�������
	galois_mult_tables[w]=(UINT32 **)malloc(sizeof(UINT32 *)*nw[w]);//���ɳ˷���
	if(galois_mult_tables[w]==NULL) return FALSE;
	for(i=0;i<nw[w];i++)
	{
		galois_mult_tables[w][i]=(UINT32 *)malloc(sizeof(UINT32)*nw[w]);
		if(galois_mult_tables[w][i]==NULL) return FALSE;
	}
	

	galois_div_tables[w]=(UINT32 **)malloc(sizeof(UINT32 *)*nw[w]);//���ɳ�����
	if(galois_mult_tables[w]==NULL) return FALSE;
	for(i=0;i<nw[w];i++)
	{
		galois_div_tables[w][i]=(UINT32 *)malloc(sizeof(UINT32)*nw[w]);
		if(galois_div_tables[w][i]==NULL) return FALSE;
	}

	if(galois_div_tables[w]==NULL)//����ʧ��
	{
		//�ع�
		free(galois_mult_tables[w]);
		galois_mult_tables[w]=NULL;
		return FALSE;
	}
	if(galois_log_tables[w]==NULL)//�����������
	{
		//������Ӧlog��
		res=galois_logtable_create(w);
		if(res==FALSE) return FALSE;//δ���ɳɹ�����FLASE
	}
	//���¾㱸��ʼ����
	for(x=0;x<nw[w];x++)
	{
		for(y=0;y<nw[w];y++)
		{
			
			//�˷������ж�0Ԫ
			if(x==0||y==0)
			{
				galois_mult_tables[w][x][y]=0;
				galois_div_tables[w][x][y]=0;
			}
			else
			{
				galois_mult_tables[w][x][y]=galois_log_multiply(x,y,w);//���ɶ�ӦԪ��
				galois_div_tables[w][x][y]=galois_log_divide(x,y,w);
			}
		}
	}
	return TRUE;
}
UINT32 galois_multtable_multiply(UINT32 x,UINT32 y,UINT32 w)//ʹ��multibale���г˷�
{
	//���˳�
	UINT32 res=0;
	if(x==0||y==0)
	{
		return 0;
	}
	if(galois_mult_tables[w]==NULL)
	{
		//�˷�������
		res=galois_multtable_create(w);
		if(res==FALSE)//�������ʧ��
		{
			show_error("galois","multiply","tablecreatefail");
			return FALSE;
		}
	}
	if(x>nwml[w]||y>nwml[w])//�������Ԫ��Χ
	{
		show_error("galois","multiply","outrange");
		return FALSE;
	}
	res=galois_mult_tables[w][x][y];
	return res;
}
UINT32 galois_multtable_divide(UINT32 x,UINT32 y,UINT32 w)
{
	UINT32 res=0;
	if(x==0||y==0)
	{
		return 0;
	}
	if(galois_div_tables[w]==NULL)
	{
		//�˷�������
		res=galois_multtable_create(w);
		if(res==FALSE)//�������ʧ��
		{
			show_error("galois","divide","tablecreatefail");
			return FALSE;
		}
	}
	if(x>nwml[w]||y>nwml[w])//�������Ԫ��Χ
	{
		show_error("galois","divide","outrange");
		return FALSE;
	}
	res=galois_div_tables[w][x][y];
	return res;
}
UINT32** galois_mult_table(UINT32 w)//��ȡ�˷���
{
	UINT32 res=0;
	if(galois_mult_tables[w]==NULL)
	{
		//�˷�������
		res=galois_multtable_create(w);
		if(res==FALSE)//�������ʧ��
		{
			show_error("galois","multiply","tablecreatefail");
			return FALSE;
		}
	}
	return galois_mult_tables[w];
}
UINT32** galois_div_table(UINT32 w)//��ȡ������
{
	UINT32 res=0;
	if(galois_div_tables[w]==NULL)
	{
		//�˷�������
		res=galois_multtable_create(w);
		if(res==FALSE)//�������ʧ��
		{
			show_error("galois","divide","tablecreatefail");
			return FALSE;
		}
	}
	return galois_div_tables[w];
}


//shift�˷�
void galois_shift_intial()//�����ƶ����������ʼ��
{}
UINT32 galois_shift_multiply(UINT32 x,UINT32 y,UINT32 w)//shift����
{
	UINT32 prod;
	UINT32 i,j,ind;
	UINT32 k;
	UINT32 scratch[33];//��¼��λ����

	prod=0;
	if(w!=32)
	{
		if(x>nwml[w]||y>nwml[w])
		{
			show_error("galois","multiply","outrange");
			return FALSE;
		}
	}
	
	for(i=0;i<w;i++)
	{
		scratch[i]=y;
		if(y&(1<<(w-1)))//��������н�λҪ����
		{
			y=y<<1;//��Ҫ����
			y=(y^prim_poly[w])&nwml[w];
		}
		else
		{
			y=y<<1;
		}
	}
	for(i=0;i<w;i++)//��ʼѰ�Ҵ��ڵ�xλ
	{
		ind=(1<<i);
		if(ind&x)
		{
			prod=(prod^scratch[i])&nwml[w];
			/*j=1;
			//for(k=0;k<w;k++)
			{
				prod=prod^(j&scratch[i]);
				j=(j<<1);
			}*/
		}
	}
	return prod;
}
//ʹ�����������Ԫ
void galois_inv_binary_matrix(UINT32 *mat,UINT32 *inv,UINT32 rows)//���ﻹ����Mr. plank���㷨��������
{
	INT32 cols,i,j,k;
	UINT32 tmp;

	cols=rows;//�����ǶԳ���

	for(i=0;i<rows;i++) inv[i]=(1<<i);//���ɵ�λ��λ��

	//������������
	for(i=0;i<cols;i++)
	{
		//��������������(i,i)�û������������һ��
		if((mat[i]&(1<<i))==0)//���Խ���
		{
			for(j=i+1;(j<rows)&&((mat[j]&(1<<i))==0);j++);//���������е�ǰ��Ϊ0��
			if(j==rows)
			{
				show_error("galois","binarymatrix","invertible");
			}
			tmp=mat[i];mat[i]=mat[j];mat[j]=tmp;
			tmp=inv[i];inv[i]=inv[j];inv[j]=tmp;
		}
		//���о�����������������
		for(j=i+1;j!=rows;j++)
		{
			if((mat[j]&(1<<i))!=0)
			{
				//��һ��������������0
				if(((mat[j])&(1<<i))!=0)
				{
					mat[j]^=mat[i];
					inv[j]^=inv[i];
				}
			}
		}
	}
	
	//���ھ����Ѿ����������������ڻ��ɵ�λ��
	for(i=rows-1;i>=0;i--)
	{
		for(j=0;j<i;j++)
		{
			if(mat[j]&(1<<i)) inv[j]^=inv[i];//������е���
		}
	}
}
//��invԪ����Ҫ��ʹ�����������Ϊ�ǻ����������inv[0]=�ұ�һ��Ϊ��Ԫ
UINT32 galois_shift_inverse(UINT32 y,UINT32 w)//����w��y����Ԫ
{
	UINT32 mat[32];UINT32 inv[32];//ԭʼ�������Ӧ�������
	UINT32 i=0;
	if(y==0) return FALSE;//��������Ϊ0
	for(i=0;i<w;i++)
	{
		mat[i]=y;
		if(y&nw[w-1])//�жϽ�λ
		{
			y=y<<1;
			y=(y^prim_poly[w])&nwml[w];
		}
		else
		{
			y=y<<1;
		}
	}
	galois_inv_binary_matrix(mat,inv,w);

	return inv[0];//��һ��Ԫ�ض�Ӧ����Ԫ�ص���Ԫ
}
//shift����
UINT32 galois_shift_divide(UINT32 x,UINT32 y,UINT32 w)//shift����
{
	UINT32 inverse;//��Ԫ
	
	if(y==0) return FALSE;
	if(x==0) return 0;
	inverse=galois_shift_inverse(y,w);
	return galois_shift_multiply(x,inverse,w);
}


//split�˷�
void galois_split_intial()//��ʼ��split�㷨
{
	galois_create_split_w8_table();
}
//����w8����Ҫ˼���ǽ�һ��32λ�ĳ˷���ֳ�7����ʽ���Ȼ�����P(3,2)��8,16,24��+1��0,0����
UINT32 galois_create_split_w8_table()//����7��split��
{
	UINT32 res,p1,p2,i,j,p1elt,p2elt,index,ishift,jshift,*table;

	if(galois_split_w8[0]!=NULL) return TRUE;//˵���Ѿ�������

	if(galois_mult_tables[8]==NULL)
	{
		res=galois_multtable_create(8);
		if(res==FALSE)
		{
			return FALSE;//ֻ��ʧ��ʱ����
		}
	}

	for(i=0;i<7;i++)//������16λ���ӱ�
	{
		galois_split_w8[i]=(UINT32 *)malloc(sizeof(UINT32)*(1<<16));
		if(galois_split_w8[i]==NULL)//�������ʧ�������
		{
			for(i--;i>=0;i--) free(galois_split_w8[i]);
			return FALSE;
		}
	}
	for(i=0;i<4;i+=3)
	{
		ishift=i*8;
		for(j=((i==0)?0:1);j<4;j++)
		{
			jshift=j*8;
			table=galois_split_w8[i+j];//��tableָ��λ�ý��ж�λ
			index=0;
			for(p1=0;p1<256;p1++)
			{
				p1elt=(p1<<ishift);
				for(p2=0;p2<256;p2++)
				{
					p2elt=(p2<<jshift);
					table[index]=galois_shift_multiply(p1elt,p2elt,32);
					index++;
				}
			}
		}
	}
	return TRUE;
}

//split�˷�
UINT32 galois_split_w8_multiply(UINT32 x,UINT32 y)//split�˷�
{
	UINT32 i,j,a,b,accumulator,i8,j8;
	accumulator=0;
	if(galois_split_w8[0]==NULL)//���û������
	{
		galois_create_split_w8_table();
	}
	i8=0;
	for(i=0;i<4;i++)
	{
		a=(((x>>i8)&255)<<8);
		j8=0;
		for(j=0;j<4;j++)
		{
			b=((y>>j8)&255);
			accumulator^=galois_split_w8[i+j][a|b];
			j8+=8;
		}
		i8+=8;
	}
	return accumulator;
}
//split����
UINT32 galois_split_w8_divide(UINT32 x,UINT32 y)//split����ֱ�ӵ���shift����
{
	return galois_shift_divide(x,y,32);
}
//����ȡ��Ԫ
//��Ԫ����
UINT32 galois_inverse(UINT32 y,UINT32 w)//��Ԫ����
{
	if(y==0) return FALSE;
	//��ʼ��������Ԫ
	if(mult_type[w]==SHIFT||mult_type[w]==SPLITW8) return galois_shift_inverse(y,w);//ֱ����λ����
	return galois_single_divide(1,y,w);
}

//����˷��ӿ�
UINT32 galois_single_multiply(UINT32 x,UINT32 y,UINT32 w)//����˷��ӿ�
{
	UINT32 sindex,res;
	if(x==0||y==0) return 0;
	sindex=mult_type[w];
	switch(sindex)
	{
	case TABLE:
		//���multable�����
		if(galois_mult_tables[w]==NULL)//���������
		{
			res=galois_multtable_create(w);
			if(res==FALSE)//����ʧ��
			{
				show_error("galois","multiply","tablecreatefail");
				return FALSE;
			}
		}
		return galois_multtable_multiply(x,y,w);
		break;
	case LOGS:
		if(galois_log_tables[w]==NULL)
		{
			res=galois_logtable_create(w);
			if(res==FALSE)
			{
				show_error("galois","logtables","toobig");
				return FALSE;
			}
		}
		return galois_log_multiply(x,y,w);
		break;
	case SHIFT:
		return galois_shift_multiply(x,y,w);
		break;
	case SPLITW8:
		if(galois_split_w8[0]==NULL)//������Ĳ���һ��
		{ 
			res=galois_create_split_w8_table();
			if(res==NULL)
			{
				show_error("galois","splittables","toobig");
				return FALSE;
			}
		}
		return galois_split_w8_multiply(x,y);
		break;
	}
}
//��������ӿ�
UINT32 galois_single_divide(UINT32 x,UINT32 y,UINT32 w)//��������ӿ�
{
	UINT32 sindex,res;
	if(x==0) return 0;
	if(y==0) return FALSE;
	sindex=mult_type[w];
	switch(sindex)
	{
	case TABLE:
		//���divable�����
		if(galois_div_tables[w]==NULL)//���������
		{
			res=galois_multtable_create(w);
			if(res==FALSE)//����ʧ��
			{
				show_error("galois","divide","tablecreatefail");
				return FALSE;
			}
		}
		return galois_multtable_divide(x,y,w);
		break;
	case LOGS:
		if(galois_log_tables[w]==NULL)
		{
			res=galois_logtable_create(w);
			if(res==FALSE)
			{
				show_error("galois","logtables","toobig");
				return FALSE;
			}
		}
		return galois_log_divide(x,y,w);
		break;
	case SHIFT:
		return galois_shift_divide(x,y,w);
		break;
	case SPLITW8:
		return galois_split_w8_divide(x,y);
		break;
	}
	
}
//���ݿ�˷�����
void galois_w08_region_multiply(char *region,//��Ҫ���г˷�������
								int multby,//����
								int nbytes,//��Ҫ���г˷��ı�����
								char *target,//Ŀ������.
								int XORTF//Ŀ�������ǲ���Ҫ������target�����ݲ���ΪTRUE����ԭ����XOR������overwrite
								//����Ϊ(target!=NULL)&&(XORTF=TRUE)���
								)//���һ������w8��galois�˷�
{
	//��ʼ������������
	UINT8 *usou,*udes,*cp;//Ҫ8��λ����
	UINT8 prod;//
	UINT32 i,srow,j;
	UINT32 l,*lp2,res;//Ϊ�˼�������32λ����һ�����
	UINT8 *lp;
	UINT8 sol;
	int multnum;
	usou=(UINT8*)region;
	udes=(target==NULL)?usou:(UINT8 *)target;
	if(galois_mult_tables[8]==NULL)//���û��
	{
		res=galois_multtable_create(8);
		if(res==FALSE)
		{
				show_error("galois","region","tablecreatefail");
				return FALSE;
		}
	}
	//������8λ�����ֻ��Ҫ���
	if((target!=NULL)&&(XORTF==TRUE))
	{
		sol=sizeof(UINT32);//��Ȼ�е�ɵ���ǻ�����һ��
		lp2=&l;//lp2��Ϊһ��ת��
		lp=(UINT8 *)lp2;
		for(i=0;i<nbytes;i+=sol)
		{
			cp=udes+i;//��λ����ǰλ��
			lp2=(UINT32 *)cp;
			for(j=0;j<sol;j++)
			{
				multnum=(int)usou[i+j];//����ת��Ϊ32λ����
				prod=(UINT8)galois_mult_tables[8][multby][multnum];//ת��Ϊ�޷���8λ
				lp[j]=prod;
			}
			(*lp2)=(*lp2)^l;
		}
	}
	else
	{
		for(i=0;i<nbytes;i++)
		{
			multnum=(int)usou[i];//����ת��Ϊ32λ����
			prod=(UINT8)galois_mult_tables[8][multby][multnum];//ת��Ϊ�޷���8λ
			udes[i]=prod;//���ǵ�Ŀ������
		}
	}
	return;
}
void galois_w16_region_multiply(char *region,//��Ҫ���г˷�������
								int multby,//����
								int nbytes,//��Ҫ���г˷��ı�����
								char *target,//Ŀ������
								int XORTF//Ŀ�������ǲ���Ҫ������target�����ݲ���ΪTRUE����ԭ����XOR������overwrite
								//����Ϊ(target!=NULL)&&(XORTF=TRUE)���
								)//���һ������w8��galois�˷�
{
	UINT16 *usou,*udes,*cp;
	INT32 prod,i,log1,j,log2;//ԭ�����м�Ҫ��Ϊ����ʹ��
	UINT32 l,*lp2,*lptop,res;
	UINT16 *lp;
	INT32 sol;
	INT32 word16;

	usou=(UINT16 *)region;
	udes=(target==NULL)?usou:(UINT16 *)target;
	word16=nbytes/2;
	if(multby==0)
	{
		if(!XORTF)//�ڲ���Ҫ���
		{
			lp2=(UINT32 *)udes;
			udes+=word16;
			lptop=(UINT32 *)udes;
			while(lp2<lptop){*lp2=0;lp2++;}
		}
		return;
	}
	if(galois_log_tables[16]==NULL)//��ʼ���16Ϊlogtable׼�����
	{
		res=galois_logtable_create(16);
		if(res==FALSE)
		{
			show_error("galois","region","tablecreatefail");
			return FALSE;
		}
	}
	log1=galois_log_tables[16][multby];

	if((target!=NULL)&&(XORTF==TRUE))
	{
		sol=sizeof(UINT32)/2;//��Ϊ�����16λ
		lp2=&l;
		lp=(UINT16 *)lp2;
		for(i=0;i<word16;i+=sol)
		{
			cp=udes+i;//16λ�ƶ�����ǰλ��
			lp2=(UINT32 *)cp;
			for(j=0;j<sol;j++)//����һ��
			{
				if(usou[i+j]==0)
				{
					lp[j]=0;
				}
				else
				{
					log2=galois_log_tables[16][usou[i+j]];//���
					prod=log1+log2;
					lp[j]=galois_ilog_tables[16][prod];
				}
			}
			*lp2=(*lp2)^l;
		}
	}
	else
	{
		for(i=0;i<word16;i++)
		{
			if(usou[i]==0)
			{
				udes[i]=0;//��������
			}
			else//�����
			{
				log2=galois_log_tables[16][usou[i]];
				prod=log1+log2;
				udes[i]=galois_ilog_tables[16][prod];
			}
		}
	}
	return;
}
void galois_w32_region_multiply(char *region,//��Ҫ���г˷�������
								int multby,//����
								int nbytes,//��Ҫ���г˷��ı�����
								char *target,//Ŀ������
								int XORTF//Ŀ�������ǲ���Ҫ������target�����ݲ���ΪTRUE����ԭ����XOR������overwrite
								//����Ϊ(target!=NULL)&&(XORTF=TRUE)���
								)//���һ������w8��galois�˷�
{
	UINT32 *usou,*udes,*cp,*udes2top;
	UINT32 *lp2,*lptop;
	INT32 i,j,a,b,i8,j8,k,word32,res;
	UINT32 accumulator;
	int acache[4];
	
	usou=(UINT32 *)region;
	udes=(target==NULL)?usou:(UINT32 *)target;
	word32=nbytes/4;
	//����Ŀ�������Ͻ�
	if(galois_split_w8[0]==NULL)
	{
		res=galois_create_split_w8_table();
		if(res==FALSE)
		{
			show_error("galois","region","tablecreatefail");
			return FALSE;
		}
	}
	//���������Ҫ��дudes�����ǽ����ڲ�ʵ�ִӶ���С����
	i8=0;
	for(i=0;i<4;i++)
	{
		acache[i]=(((multby>>i8)&255)<<8);//�������ֳ�4�ݣ�ÿ��8λ
		i8+=8;
	}
	if((target!=NULL)&&(XORTF==TRUE))//�����Ҫ���
	{
		for(k=0;k<word32;k++)
		{
			accumulator=0;
			for(i=0;i<4;i++)
			{
				a=acache[i];
				j8=0;
				for(j=0;j<4;j++)
				{
					b=((usou[k]>>j8)&255);
					accumulator^=galois_split_w8[i+j][a|b];
					j8+=8;//ȡ��һ���ֽڲ��
				}
			}
			udes[k]=(udes[k]^accumulator);
		}
	}
	else
	{
		for(k=0;k<word32;k++)
		{
			accumulator=0;
			for(i=0;i<4;i++)
			{
				a=acache[i];
				j8=0;
				for(j=0;j<4;j++)
				{
					b=((usou[k]>>j8)&255);
					accumulator^=galois_split_w8[i+j][a|b];
					j8+=8;
				}
			}
			udes[k]=accumulator;
		}
	}
	return;
}
//intial GALOIS
void galois_intial()
{
	//��ʼ���ĸ�ģ��
	galois_log_intial();
	galois_multtable_intial();
	galois_shift_intial();
	galois_split_intial();
}
