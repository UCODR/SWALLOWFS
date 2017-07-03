#include "reed_sol_classic.h"
int reed_sol_r6_matrix(INTMATRIX *matrix)//主要是用于生成RAID-6的vandermonder阵
{
	//主要是用于生成RAID-6的vandermonder阵
	int i,w,tmp,rows,cols;
	UINT32 *mat;
	//erarray->datanum;//读出相应数据
	//erarray->codenum;
	
	mat=matrix->matrix;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;
	if(w!=8&&w!=16&&w!=32)//检测w数据
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
	mat=talloc(UINT32,2*cols);//分配一个2行的矩阵
	if(mat==NULL)
	{
		show_error("reed_sol","matrix-r6","no memory");
		return FALSE;
	}
	for(i=0;i<cols;i++)//对于第一行进行全1分配
	{
		mat[i]=1;
	}
	tmp=1;
	//生成第二行
	for(i=0;i<cols;i++)
	{
		tmp=galois_single_multiply(tmp,2,w);
		mat[cols+i]=tmp;
	}
	//将数据赋值回数值行
	matrix->matrix=mat;
	matrix->xm=rows;
	matrix->ym=cols;
	matrix->w=w;
	return TRUE;
}
int reed_sol_vandermonde_coding_matrix(INTMATRIX *matrix)//主要是用于任意生成vandermonder矩阵
{
	//主要是用于任意生成vandermonder矩阵
	int i,j,w,tmp,rows,cols,resTF;
	UINT32 *mat,*vdm;//由于大vandermonde阵到编码阵需要压缩，另立存储
	INTMATRIX bigvdm;
	//erarray->datanum;//读出相应数据
	//erarray->codenum;
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;
	mat=matrix->matrix;
	if(w!=8&&w!=16&&w!=32)//检测w数据
	{
		show_error("reed_sol","matrix-vandermonde","number w is illegal");
		return FALSE;
	}

	//进行新建一个matrix
	bigvdm=matrix_create_NULL();//创建一个big_vandermonde_matrix
	matrix_set_data(&bigvdm,NULL,rows+cols,cols,w);
	resTF=reed_sol_big_vandermonde_distribution_matrix(&bigvdm);//可以生成了
	if(resTF==FALSE)//不可以生成失败
	{
		show_error("reed_sol","vandermonde_coding","big vandermonde doesn't break");
		return FALSE;
	}
	vdm=bigvdm.matrix;
	//无需检查因为需要调用big和extended时会检查
	if(mat!=NULL)
	{
		free(mat);
	}
	mat=talloc(UINT32,rows*cols);//分配一个2行的矩阵
	if(mat==NULL)
	{
		show_error("reed_sol","matrix-vandermonde","no memory");
		return FALSE;
	}
	//计算
	i=cols*cols;
	for(j=0;j<rows*cols;j++)//提取需要的数据
	{
		mat[j]=vdm[i];
		i++;
	}
	//可以过河拆桥了
	matrix_destroy(&bigvdm);//释放空间
	matrix->matrix=mat;
	return TRUE;
}
int reed_sol_big_vandermonde_distribution_matrix(INTMATRIX *matrix)//生成vandermonder分布矩阵
{
	UINT32 *mat;
	UINT32 i,j,k;
	int rows,cols,w;
	UINT32 sindex,srindex,siindex,tmp;
	int resTF;
	//提参数
	rows=matrix->xm;
	cols=matrix->ym;
	w=matrix->w;
	//判断行列欢喜
	if(cols<rows)
	{
		show_error("reed_sol","big_vandermonde","cols<rows");
		return FALSE;
	}
	//生成对应的扩展矩阵
	resTF=reed_sol_extended_vandermonde_matrix(matrix);
	if(resTF==FALSE)
	{
		show_error("reed_sol","big_vandermonde","extended matrix failed");
		return FALSE;
	}
	
	mat=matrix->matrix;//提取相应的扩展矩阵
	sindex=0;
	for(i=1;i<cols;i++)//将每一行化为0
	{
		sindex+=cols;
		//找到一行其中对角线（i,i）不为0
		srindex=sindex+i;//定位到那一位
		for(j=i;j<rows&&mat[srindex]==0;j++) srindex+=cols;//求位置
		if(j>=rows)//矩阵不可逆，如果vandermonde生成正确不可能出现
		{
			show_error("reed_sol","big_vandermonde","matrix is invertible");
			return FALSE;
		}
		//如果需要交换两行
		if(j!=i)
		{
			srindex-=i;//回退到起点
			for(k=0;k<cols;k++)
			{
				tmp=mat[srindex+k];
				mat[srindex+k]=mat[sindex+k];
				mat[sindex+k]=tmp;
			}
		}
		//如果（i,i）不是1则要除以逆元,记住是按列变化
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
		//对于第i行中不是1的元素都需要置0,
		//因此需要进行乘加来保证0
		for(j=0;j<cols;j++)
		{
			tmp=mat[sindex+j];
			if(j!=i&&tmp!=0)
			{
				srindex=j;
				siindex=i;
				for(k=0;k<rows;k++)//将没一列进行叠加
				{
					mat[srindex]=mat[srindex]^galois_single_multiply(tmp,mat[siindex],w);//将原始的数据乘加到目标列中
					srindex+=cols;
					siindex+=cols;
				}
			}
		}
	}
	//希望第k行都是1进行变换
	sindex=cols*cols;//定位初始点
	for(j=0;j<cols;j++)
	{
		tmp=mat[sindex];
		if(tmp!=1)
		{	
			if(tmp!=1)
			{
				//将之后的通通乘以逆元
				tmp=galois_inverse(tmp,w);
				srindex=sindex;
				for(i=cols;i<rows;i++)
				{
					mat[srindex]=galois_single_multiply(tmp,mat[srindex],w);//将之后的数据进行变换
					srindex+=cols;
				}
			}
		}
		sindex++;
	}
	//最后，我们希望第一列都是1
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
	matrix->matrix=mat;//因此进行matrix赋值
	return TRUE;
}
int reed_sol_extended_vandermonde_matrix(INTMATRIX *matrix)//根据矩阵数据生成范的蒙行列式
{
	int rows,cols,w;
	UINT32 i,j,k;
	UINT32 *mat;
	rows=matrix->xm;
	cols=matrix->ym;
	mat=matrix->matrix;
	w=matrix->w;
	if(w!=8&&w!=16&&w!=32)//检测w数据
	{
		show_error("reed_sol","extended_vandermonde","number w is illegal");
		return FALSE;
	}
	//检测生成w条件
	//虽然基本在实验上是多次一举但是为理论还是检查一下
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
	mat[0]=1;//第一行第一个为1其余为0
	for(j=1;j<cols;j++) mat[j]=0;
	if(rows==1)//如果只有一行直接返回
	{
		matrix->matrix=mat;
		return TRUE;
	}
	//存在两行以上就将最后一行设为最后一个是1
	i=(rows-1)*cols;//定位到最后一行
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
	for(i=1;i<rows-1;i++)//中间生成vandermonde矩阵
	{
		k=1;
		for(j=0;j<cols;j++)
		{
			mat[i*cols+j]=k;//将次方结果保存
			k=galois_single_multiply(k,i,w);
		}
	}
	matrix->matrix=mat;
	return TRUE;
}

//对应相应的r6系统进行编码
int reed_sol_r6_encode_w(CHUNKBLOCKGROUP *datachk,CHUNK *pchunkptr,CHUNK *qchunkptr,int w)
{
	int i,datanum,paranum,resTF;
	CHUNKBLOCK *datachklist,*curdatachklist;
	CHUNK *datachunkptr;

	//提取数据
	datachklist=datachk->chunkblockptr;//获取chunk列表指针
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
	if(pchunkptr==NULL)//虽然不太可能还是要保险
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
	//开始计算参数，因为简单不用计算
	datachunkptr=curdatachklist->chunkptr;
	//开始计算第一个,仅仅需要拷贝
	resTF=matrix_CHUNK_copy_data(pchunkptr,datachunkptr);//将第一个chunk进行拷贝
	if(resTF==FALSE)
	{
		show_error("reed_sol","r6_encode","chunk data can't copy");
		return FALSE;
	}
	for(i=1;i<datanum;i++)
	{
		curdatachklist++;//后移一位
		datachunkptr=curdatachklist->chunkptr;
		resTF=matrix_CHUNK_add_data(pchunkptr,datachunkptr);
		if(resTF==FALSE)
		{
			show_error("reed_sol","r6_encode","chunk data can't add");
			return FALSE;
		}
	}
	curdatachklist=datachklist;
	//parachklist++;//将指针定位到下一个位置
	datachunkptr=curdatachklist->chunkptr;
	//计算目标chunk2
	resTF=matrix_CHUNK_copy_data(qchunkptr,datachunkptr);//将第一个chunk进行拷贝
	if(resTF==FALSE)
	{
		show_error("reed_sol","r6_encode_w","chunk data can't copy");
		return FALSE;
	}
	//将后面的CHUNK进行乘2加
	for(i=1;i<datanum;i++)
	{
		curdatachklist++;
		datachunkptr=curdatachklist->chunkptr;
		switch(w)
		{
		//将校验块*2+数据项
		case 8: matrix_CHUNK_w08_multiply(qchunkptr,2);break;
		case 16:matrix_CHUNK_w16_multiply(qchunkptr,2);break;
		case 32:matrix_CHUNK_w32_multiply(qchunkptr,2);break;
		}
		matrix_CHUNK_add_data(qchunkptr,datachunkptr);
	}
}
//对应相应的r6系统进行编码并且将r6矩阵保存在para中
int reed_sol_r6_encode(CHUNKBLOCKGROUP *datachk,CHUNK *pchunkptr,CHUNK *qchunkptr,ENDECODEPARA *para)//对应相应的r6系统进行编码并且将r6矩阵保存在para中
{
	int datanum,w,resTF;
	INTMATRIX *mat; 
	//生成相应的矩阵并记录
	//读取参数这里是raid-6只有w
	w=para->w;
	resTF=reed_sol_r6_encode_w(datachk,pchunkptr,qchunkptr,w);
	if(resTF==FALSE)
	{
		show_error("reed_sol","r6_encode","data can't encode");
		return FALSE;
	}

	para->matrix=talloc(INTMATRIX,1);//分配一个空间
	mat=para->matrix;
	datanum=datachk->groupsize;
	//需要对于mat设定初始化参数
	matrix_set_data(mat,NULL,2,datanum,w);
	resTF=reed_sol_r6_matrix(mat);
	if(resTF==FALSE)//如果生成失败那么就报错
	{
		show_error("reed_sol","r6_encode","can't create r6 matrix");
		return FALSE;
	}
	para->matrix=mat;
	return TRUE;
}
//不同于Plank老师我们需要将数据封装成API
//对于相应的r6进行解码
int reed_sol_r6_decode_w(CHUNKBLOCKGROUP *datachk,CHUNKBLOCKGROUP *parachk,int w,ERASES *erarray)
{
	//计算r6再生恢复
	return TRUE;
}
//对于相应的r6进行解码并且将解码矩阵保存在para中
int reed_sol_r6_decode(CHUNKBLOCKGROUP *datachk,CHUNK *pchunkptr,CHUNK *qchunkptr,ENDECODEPARA *para,ERASES *erarray)
{
	
	return TRUE;
}

//根据datachk和parachk的大小进行编码并且将编码矩阵保存在para中
int reed_sol_van_encode(CHUNKBLOCKGROUP *datachk,CHUNKBLOCKGROUP *parachk,ENDECODEPARA *para)
{
	//计算编码阵
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
	matrix_set_data(enmatrix,NULL,codenum,datanum,w);//设定编码矩阵的参数
	resTF=reed_sol_vandermonde_coding_matrix(enmatrix);//生成一个编码矩阵
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

//根据datachk和parachk的大小进行编码
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
//对于相应的van进行解码
int reed_sol_van_decode(CHUNKBLOCKGROUP *datachk,CHUNKBLOCKGROUP *parachk,ENDECODEPARA *para,ERASES *erarray)
{
	INTMATRIX *enmatrix;//编码矩阵
	INTMATRIX *dematrix;//解码矩阵

	int w;
	//计算解码
	return TRUE;
}
//classic RS编码raid6接口
int reed_sol_API_RAID6(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr)
{
	INTMATRIX *matrix;//用记录当前当前数据
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
	//获取伽罗华大小
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
	//读取数据指针
	chunkgroupptr=pparityptr->chunklist;
	pchunkptr=chunkgroupptr->ckgroup;//取出数据

	chunkgroupptr=qparityptr->chunklist;
	qchunkptr=chunkgroupptr->ckgroup;
	
	//计算chunk指针
	//调用内部的编码函数
	stripsectblockptr=strsetblockgroupptr->stripsectblockptr;
	//将指针调试到开始位置
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
	//可以开始调用数据块进行计算了
	resTF=reed_sol_r6_encode_w(datachunkgroupptr,pchunkptr,qchunkptr,w);
	if(resTF==FALSE)
	{
		show_error("reed_sol","API_RAID6","CLASSIC RS can't calculate");
		return FALSE;
	}
	return TRUE;
}
//经典RS编码接口
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
	chunkptr=chunkgroupptr->ckgroup;//当前校验块
	//搜索数据块指针
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

//RAID6的update操作
int reed_sol_update_API_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr)
{
	return TRUE;
}
//update操作
extern int reed_sol_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr)
{
	return TRUE;
}
//解码API
int reed_sol_decoder_API_strip(STRIP *stripptr,ERRORPATTERN *errormatrix)
{
	return TRUE;
}
//经典RS解码接口
int reed_sol_decoder_API_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix)
{
	return TRUE;
}