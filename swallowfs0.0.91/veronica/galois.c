/*
This program is created by Jiajie Shen 
2014.11.23
沈佳杰创建2014.11.23
*/
/*
reference FAST08 Plank Galois lab
参考FAST08 Plank Galois 库主要实现GF域运算
选择参考这个库的主要原因是运算效率
使用log机制和查表完成的Galois需要效率相较于其他方法。。。
*/
#include "galois.h"
//定义乘法界面
//乘法查询列表
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

//生成相应的生成位数
static UINT32 nw[33]={0, (1 << 1), (1 << 2), (1 << 3), (1 << 4), 
(1 << 5), (1 << 6), (1 << 7), (1 << 8), (1 << 9), (1 << 10),
(1 << 11), (1 << 12), (1 << 13), (1 << 14), (1 << 15), (1 << 16),
(1 << 17), (1 << 18), (1 << 19), (1 << 20), (1 << 21), (1 << 22),
(1 << 23), (1 << 24), (1 << 25), (1 << 26), (1 << 27), (1 << 28),
(1 << 29), (1 << 30), (1 << 31), -1};
//生成相应的掩码
static UINT32 nwml[33]={0, (1 << 1)-1, (1 << 2)-1, (1 << 3)-1, (1 << 4)-1, 
(1 << 5)-1, (1 << 6)-1, (1 << 7)-1, (1 << 8)-1, (1 << 9)-1, (1 << 10)-1,
(1 << 11)-1, (1 << 12)-1, (1 << 13)-1, (1 << 14)-1, (1 << 15)-1, (1 << 16)-1,
(1 << 17)-1, (1 << 18)-1, (1 << 19)-1, (1 << 20)-1, (1 << 21)-1, (1 << 22)-1,
(1 << 23)-1, (1 << 24)-1, (1 << 25)-1, (1 << 26)-1, (1 << 27)-1, (1 << 28)-1,
(1 << 29)-1, (1 << 30)-1, 0x7fffffff, 0xffffffff};
//生成logtable
static UINT32 *galois_log_tables[33]={NULL, NULL, NULL, NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
//生成ilogtable
static UINT32 *galois_ilog_tables[33]={NULL, NULL, NULL, NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
//生成乘法表
static UINT32 **galois_mult_tables[33]={NULL, NULL, NULL, NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
//生成除法表
static UINT32 **galois_div_tables[33]={NULL, NULL, NULL, NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
//记录w8数据表
static UINT32 *galois_split_w8[8]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
//记录所有的素数
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
/* 32 */    040020000007 }; //记住C中0开头是8八进制数
//验证galois上编码可行性
void galois_region_xor(           char *r1,         /* Region 1 */
                                  char *r2,         /* Region 2 */
                                  char *target,         /* Sum region (r3 = r1 ^ r2) -- can be r1 or r2 两者*/
                                  UINT32 nbytes)       /* Number of bytes in region 多少个字节进行异或*/
{
	//计算xor可以
	short *s1;//8为一算源文件为long，不一定满足不同编译器
	short *s2;
	short *s3;
	short *stop;
	char *ctop;
	//计算地址位置
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
//加减法直接做异或
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



//仿plank算法先log后multtable
//实现log法的乘除法
void galois_log_intial()
{
	//生成log，ilog表
	UINT32 i=0;
	for(i=0;i<25;i++)
	{
		//计算0-22
		UINT32 j=galois_logtable_create(i);
		//printf("%d",j);
	}

}
UINT32 galois_logtable_create(UINT32 w)//生成在w下的log和ilog表
{
	//生成相应的log，ilog表
	UINT32 i=0,b=1;
	if(w>32) return FALSE;
	if(galois_log_tables[w]!=NULL) return TRUE;//已经存在
	galois_log_tables[w]=(UINT32 *)malloc(sizeof(UINT32)*nw[w]);//生成相关存储区域
	if(galois_log_tables[w]==NULL) return FALSE;
	
	galois_ilog_tables[w]=(UINT32 *)malloc(sizeof(UINT32)*nw[w]*3);//空间提升三倍
	if(galois_ilog_tables[w]==NULL)
	{
		//回滚
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
		//生成相应的
		//检测新生成位是否存在
		if(galois_log_tables[w][b]!=nwml[w])//检测位置是非被占
		{
			show_error("galois","logtables","nwoccupy");
			return FALSE;
		}
		galois_log_tables[w][b]=i;
		galois_ilog_tables[w][i]=b;
		b=b<<1;//左移1位
		if(b&nw[w])
		{
			//如果b值已经超过了上限需要回退
			b=(b^prim_poly[w])&nwml[w];//使用生成元回退
		}
	}
	for(i=0;i<nwml[w];i++)//将原表复制两遍
	{
		galois_ilog_tables[w][i+nwml[w]]=galois_ilog_tables[w][i];
		galois_ilog_tables[w][i+nwml[w]*2]=galois_ilog_tables[w][i];
	}
	galois_ilog_tables[w]+=nwml[w];//数据表指针居中这样前后都有nwml[w]位了。
	return TRUE;
}
//获取w的ilogtable
UINT32* galois_ilog_table(UINT32 w)
{
	if(galois_ilog_tables[w]==NULL)//如果没有
	{
		if(galois_logtable_create(w)==FALSE)//如果没有创建成功
		{
			show_error("galois","ilogtables","toobig");
			return FALSE;
		}
	}
	return galois_ilog_tables[w];
}
//获取w的logtable
UINT32* galois_log_table(UINT32 w)
{
	if(galois_log_tables[w]==NULL)//如果没有
	{
		if(galois_logtable_create(w)==FALSE)//如果没有创建成功
		{
			show_error("galois","logtables","toobig");
			return FALSE;
		}
	}
	return galois_log_tables[w];
}

UINT32 galois_log_multiply(UINT32 x,UINT32 y,UINT32 w)//实现logtable乘法
{
	int sum_log;//用于存储
	if(x==0||y==0) return 0;//如果存在0元，则返回0
	if(galois_ilog_tables[w]==NULL)//如果没有
	{
		if(galois_logtable_create(w)==FALSE)//如果没有创建成功
		{
			show_error("galois","logtables","toobig");
			return FALSE;
		}
	}
	if(x>nwml[w]||y>nwml[w])//检查数据元范围
	{
		show_error("galois","multiply","outrange");
		return FALSE;
	}
	sum_log=galois_log_tables[w][x]+galois_log_tables[w][y];

	return galois_ilog_tables[w][sum_log];
}

UINT32 galois_log_divide(UINT32 x,UINT32 y,UINT32 w)//实现logtable除法
{
	int minus_log;//用于存储
	if(x==0||y==0) return 0;//如果存在0元，则返回0
	if(galois_ilog_tables[w]==NULL)//如果没有
	{
		if(galois_logtable_create(w)==FALSE)//如果没有创建成功
		{
			show_error("galois","logtables","toobig");
		}
	}
	if(x>nwml[w]||y>nwml[w])//检查数据元范围
	{
		show_error("galois","divide","outrange");
		return FALSE;
	}
	minus_log=galois_log_tables[w][x]-galois_log_tables[w][y];

	return galois_ilog_tables[w][minus_log];
}

//先实现查表乘法
//初始化，创建乘法表
void galois_multtable_intial()
{
	UINT32 i=0,res;//初始化乘法类表
	for(i=0;i<10;i++)
	{
		res=galois_multtable_create(i);
		//printf("%d",res);
	}
}
UINT32 galois_multtable_create(UINT32 w)//创建w乘法表
{
	//初始化w下mult和divide
	UINT32 i,x,y,logx,res;
	if (w>14) return FALSE;//太大
	if(galois_mult_tables[w]!=NULL) return TRUE;//已经生成了
	galois_mult_tables[w]=(UINT32 **)malloc(sizeof(UINT32 *)*nw[w]);//生成乘法表
	if(galois_mult_tables[w]==NULL) return FALSE;
	for(i=0;i<nw[w];i++)
	{
		galois_mult_tables[w][i]=(UINT32 *)malloc(sizeof(UINT32)*nw[w]);
		if(galois_mult_tables[w][i]==NULL) return FALSE;
	}
	

	galois_div_tables[w]=(UINT32 **)malloc(sizeof(UINT32 *)*nw[w]);//生成除法表
	if(galois_mult_tables[w]==NULL) return FALSE;
	for(i=0;i<nw[w];i++)
	{
		galois_div_tables[w][i]=(UINT32 *)malloc(sizeof(UINT32)*nw[w]);
		if(galois_div_tables[w][i]==NULL) return FALSE;
	}

	if(galois_div_tables[w]==NULL)//生成失败
	{
		//回滚
		free(galois_mult_tables[w]);
		galois_mult_tables[w]=NULL;
		return FALSE;
	}
	if(galois_log_tables[w]==NULL)//如果存在生成
	{
		//生成相应log表
		res=galois_logtable_create(w);
		if(res==FALSE) return FALSE;//未生成成功返回FLASE
	}
	//万事俱备开始生成
	for(x=0;x<nw[w];x++)
	{
		for(y=0;y<nw[w];y++)
		{
			
			//乘法除法判断0元
			if(x==0||y==0)
			{
				galois_mult_tables[w][x][y]=0;
				galois_div_tables[w][x][y]=0;
			}
			else
			{
				galois_mult_tables[w][x][y]=galois_log_multiply(x,y,w);//生成对应元素
				galois_div_tables[w][x][y]=galois_log_divide(x,y,w);
			}
		}
	}
	return TRUE;
}
UINT32 galois_multtable_multiply(UINT32 x,UINT32 y,UINT32 w)//使用multibale进行乘法
{
	//查表乘除
	UINT32 res=0;
	if(x==0||y==0)
	{
		return 0;
	}
	if(galois_mult_tables[w]==NULL)
	{
		//乘法表不存在
		res=galois_multtable_create(w);
		if(res==FALSE)//如果生成失败
		{
			show_error("galois","multiply","tablecreatefail");
			return FALSE;
		}
	}
	if(x>nwml[w]||y>nwml[w])//检查数据元范围
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
		//乘法表不存在
		res=galois_multtable_create(w);
		if(res==FALSE)//如果生成失败
		{
			show_error("galois","divide","tablecreatefail");
			return FALSE;
		}
	}
	if(x>nwml[w]||y>nwml[w])//检查数据元范围
	{
		show_error("galois","divide","outrange");
		return FALSE;
	}
	res=galois_div_tables[w][x][y];
	return res;
}
UINT32** galois_mult_table(UINT32 w)//获取乘法表
{
	UINT32 res=0;
	if(galois_mult_tables[w]==NULL)
	{
		//乘法表不存在
		res=galois_multtable_create(w);
		if(res==FALSE)//如果生成失败
		{
			show_error("galois","multiply","tablecreatefail");
			return FALSE;
		}
	}
	return galois_mult_tables[w];
}
UINT32** galois_div_table(UINT32 w)//获取除法表
{
	UINT32 res=0;
	if(galois_div_tables[w]==NULL)
	{
		//乘法表不存在
		res=galois_multtable_create(w);
		if(res==FALSE)//如果生成失败
		{
			show_error("galois","divide","tablecreatefail");
			return FALSE;
		}
	}
	return galois_div_tables[w];
}


//shift乘法
void galois_shift_intial()//正常移动计算无需初始化
{}
UINT32 galois_shift_multiply(UINT32 x,UINT32 y,UINT32 w)//shift计算
{
	UINT32 prod;
	UINT32 i,j,ind;
	UINT32 k;
	UINT32 scratch[33];//记录移位数据

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
		if(y&(1<<(w-1)))//如果存在有进位要回退
		{
			y=y<<1;//需要经期
			y=(y^prim_poly[w])&nwml[w];
		}
		else
		{
			y=y<<1;
		}
	}
	for(i=0;i<w;i++)//开始寻找存在的x位
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
//使用逆矩阵求逆元
void galois_inv_binary_matrix(UINT32 *mat,UINT32 *inv,UINT32 rows)//这里还是用Mr. plank的算法求矩阵的逆
{
	INT32 cols,i,j,k;
	UINT32 tmp;

	cols=rows;//由于是对称阵

	for(i=0;i<rows;i++) inv[i]=(1<<i);//生成单位单位阵

	//生成上三角阵
	for(i=0;i<cols;i++)
	{
		//首先我们先来将(i,i)置换出来，提过这一步
		if((mat[i]&(1<<i))==0)//主对角线
		{
			for(j=i+1;(j<rows)&&((mat[j]&(1<<i))==0);j++);//搜索所有中当前不为0的
			if(j==rows)
			{
				show_error("galois","binarymatrix","invertible");
			}
			tmp=mat[i];mat[i]=mat[j];mat[j]=tmp;
			tmp=inv[i];inv[i]=inv[j];inv[j]=tmp;
		}
		//进行矩阵运算生成上三角
		for(j=i+1;j!=rows;j++)
		{
			if((mat[j]&(1<<i))!=0)
			{
				//这一排下面所有行清0
				if(((mat[j])&(1<<i))!=0)
				{
					mat[j]^=mat[i];
					inv[j]^=inv[i];
				}
			}
		}
	}
	
	//现在矩阵已经是上三角阵了现在化成单位阵
	for(i=rows-1;i>=0;i--)
	{
		for(j=0;j<i;j++)
		{
			if(mat[j]&(1<<i)) inv[j]^=inv[i];//计算进行叠加
		}
	}
}
//求inv元，主要是使用你矩阵，又因为是环上生成因此inv[0]=右边一列为逆元
UINT32 galois_shift_inverse(UINT32 y,UINT32 w)//求在w下y的逆元
{
	UINT32 mat[32];UINT32 inv[32];//原始矩阵和相应的逆矩阵
	UINT32 i=0;
	if(y==0) return FALSE;//除数不能为0
	for(i=0;i<w;i++)
	{
		mat[i]=y;
		if(y&nw[w-1])//判断进位
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

	return inv[0];//第一个元素对应与是元素的逆元
}
//shift除法
UINT32 galois_shift_divide(UINT32 x,UINT32 y,UINT32 w)//shift除法
{
	UINT32 inverse;//逆元
	
	if(y==0) return FALSE;
	if(x==0) return 0;
	inverse=galois_shift_inverse(y,w);
	return galois_shift_multiply(x,inverse,w);
}


//split乘法
void galois_split_intial()//初始化split算法
{
	galois_create_split_w8_table();
}
//生成w8表主要思想是将一个32位的乘法拆分成7个公式相乘然后相加P(3,2)（8,16,24）+1（0,0）表
UINT32 galois_create_split_w8_table()//创建7张split表
{
	UINT32 res,p1,p2,i,j,p1elt,p2elt,index,ishift,jshift,*table;

	if(galois_split_w8[0]!=NULL) return TRUE;//说明已经生成了

	if(galois_mult_tables[8]==NULL)
	{
		res=galois_multtable_create(8);
		if(res==FALSE)
		{
			return FALSE;//只有失败时返回
		}
	}

	for(i=0;i<7;i++)//建立张16位连接表
	{
		galois_split_w8[i]=(UINT32 *)malloc(sizeof(UINT32)*(1<<16));
		if(galois_split_w8[i]==NULL)//如果生成失败则回收
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
			table=galois_split_w8[i+j];//将table指针位置进行定位
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

//split乘法
UINT32 galois_split_w8_multiply(UINT32 x,UINT32 y)//split乘法
{
	UINT32 i,j,a,b,accumulator,i8,j8;
	accumulator=0;
	if(galois_split_w8[0]==NULL)//如果没有生成
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
//split除法
UINT32 galois_split_w8_divide(UINT32 x,UINT32 y)//split除法直接调用shift除法
{
	return galois_shift_divide(x,y,32);
}
//整体取逆元
//逆元生成
UINT32 galois_inverse(UINT32 y,UINT32 w)//逆元生成
{
	if(y==0) return FALSE;
	//开始查表计算逆元
	if(mult_type[w]==SHIFT||mult_type[w]==SPLITW8) return galois_shift_inverse(y,w);//直接移位求倒数
	return galois_single_divide(1,y,w);
}

//整体乘法接口
UINT32 galois_single_multiply(UINT32 x,UINT32 y,UINT32 w)//整体乘法接口
{
	UINT32 sindex,res;
	if(x==0||y==0) return 0;
	sindex=mult_type[w];
	switch(sindex)
	{
	case TABLE:
		//检测multable的情况
		if(galois_mult_tables[w]==NULL)//如果不存在
		{
			res=galois_multtable_create(w);
			if(res==FALSE)//生成失败
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
		if(galois_split_w8[0]==NULL)//和上面的操作一样
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
//整体除法接口
UINT32 galois_single_divide(UINT32 x,UINT32 y,UINT32 w)//整体除法接口
{
	UINT32 sindex,res;
	if(x==0) return 0;
	if(y==0) return FALSE;
	sindex=mult_type[w];
	switch(sindex)
	{
	case TABLE:
		//检测divable的情况
		if(galois_div_tables[w]==NULL)//如果不存在
		{
			res=galois_multtable_create(w);
			if(res==FALSE)//生成失败
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
//数据块乘法运算
void galois_w08_region_multiply(char *region,//需要进行乘法的区域
								int multby,//乘数
								int nbytes,//需要进行乘法的比特数
								char *target,//目标区域.
								int XORTF//目标区域是不是要异或，如果target有内容并且为TRUE则与原内容XOR，否则overwrite
								//条件为(target!=NULL)&&(XORTF=TRUE)异或
								)//完成一个区域w8的galois乘法
{
	//开始进行区域运算
	UINT8 *usou,*udes,*cp;//要8八位运算
	UINT8 prod;//
	UINT32 i,srow,j;
	UINT32 l,*lp2,res;//为了加速运算32位进行一次异或
	UINT8 *lp;
	UINT8 sol;
	int multnum;
	usou=(UINT8*)region;
	udes=(target==NULL)?usou:(UINT8 *)target;
	if(galois_mult_tables[8]==NULL)//如果没有
	{
		res=galois_multtable_create(8);
		if(res==FALSE)
		{
				show_error("galois","region","tablecreatefail");
				return FALSE;
		}
	}
	//由于是8位，因此只需要查表
	if((target!=NULL)&&(XORTF==TRUE))
	{
		sol=sizeof(UINT32);//虽然有点傻但是还是做一下
		lp2=&l;//lp2作为一个转手
		lp=(UINT8 *)lp2;
		for(i=0;i<nbytes;i+=sol)
		{
			cp=udes+i;//定位到当前位置
			lp2=(UINT32 *)cp;
			for(j=0;j<sol;j++)
			{
				multnum=(int)usou[i+j];//将其转化为32位乘数
				prod=(UINT8)galois_mult_tables[8][multby][multnum];//转化为无符号8位
				lp[j]=prod;
			}
			(*lp2)=(*lp2)^l;
		}
	}
	else
	{
		for(i=0;i<nbytes;i++)
		{
			multnum=(int)usou[i];//将其转化为32位乘数
			prod=(UINT8)galois_mult_tables[8][multby][multnum];//转化为无符号8位
			udes[i]=prod;//覆盖到目标区域
		}
	}
	return;
}
void galois_w16_region_multiply(char *region,//需要进行乘法的区域
								int multby,//乘数
								int nbytes,//需要进行乘法的比特数
								char *target,//目标区域
								int XORTF//目标区域是不是要异或，如果target有内容并且为TRUE则与原内容XOR，否则overwrite
								//条件为(target!=NULL)&&(XORTF=TRUE)异或
								)//完成一个区域w8的galois乘法
{
	UINT16 *usou,*udes,*cp;
	INT32 prod,i,log1,j,log2;//原因是中间要作为索引使用
	UINT32 l,*lp2,*lptop,res;
	UINT16 *lp;
	INT32 sol;
	INT32 word16;

	usou=(UINT16 *)region;
	udes=(target==NULL)?usou:(UINT16 *)target;
	word16=nbytes/2;
	if(multby==0)
	{
		if(!XORTF)//在不需要异或
		{
			lp2=(UINT32 *)udes;
			udes+=word16;
			lptop=(UINT32 *)udes;
			while(lp2<lptop){*lp2=0;lp2++;}
		}
		return;
	}
	if(galois_log_tables[16]==NULL)//开始检查16为logtable准备情况
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
		sol=sizeof(UINT32)/2;//因为这次是16位
		lp2=&l;
		lp=(UINT16 *)lp2;
		for(i=0;i<word16;i+=sol)
		{
			cp=udes+i;//16位移动到当前位置
			lp2=(UINT32 *)cp;
			for(j=0;j<sol;j++)//处理一个
			{
				if(usou[i+j]==0)
				{
					lp[j]=0;
				}
				else
				{
					log2=galois_log_tables[16][usou[i+j]];//查表
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
				udes[i]=0;//不用算了
			}
			else//查表算
			{
				log2=galois_log_tables[16][usou[i]];
				prod=log1+log2;
				udes[i]=galois_ilog_tables[16][prod];
			}
		}
	}
	return;
}
void galois_w32_region_multiply(char *region,//需要进行乘法的区域
								int multby,//乘数
								int nbytes,//需要进行乘法的比特数
								char *target,//目标区域
								int XORTF//目标区域是不是要异或，如果target有内容并且为TRUE则与原内容XOR，否则overwrite
								//条件为(target!=NULL)&&(XORTF=TRUE)异或
								)//完成一个区域w8的galois乘法
{
	UINT32 *usou,*udes,*cp,*udes2top;
	UINT32 *lp2,*lptop;
	INT32 i,j,a,b,i8,j8,k,word32,res;
	UINT32 accumulator;
	int acache[4];
	
	usou=(UINT32 *)region;
	udes=(target==NULL)?usou:(UINT32 *)target;
	word32=nbytes/4;
	//计算目标区域上界
	if(galois_split_w8[0]==NULL)
	{
		res=galois_create_split_w8_table();
		if(res==FALSE)
		{
			show_error("galois","region","tablecreatefail");
			return FALSE;
		}
	}
	//如果仅仅需要重写udes，我们将在内部实现从而减小开销
	i8=0;
	for(i=0;i<4;i++)
	{
		acache[i]=(((multby>>i8)&255)<<8);//将乘数分成4份，每份8位
		i8+=8;
	}
	if((target!=NULL)&&(XORTF==TRUE))//如果需要异或
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
					j8+=8;//取下一个字节查表
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
	//初始化四个模块
	galois_log_intial();
	galois_multtable_intial();
	galois_shift_intial();
	galois_split_intial();
}
