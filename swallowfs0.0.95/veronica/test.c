#include "test.h"
void main()
{
	//update_RCW_trace_test();//实测一下log机制
	update_RMW_trace_test();
	//测一下数据库
	/*CHECKPOINT *checkpointptr,*checkpointptr2;
	CHECKPOINTINF *checkinf;
	checkinf=talloc(CHECKPOINTINF,1);

	checkpointptr=talloc(CHECKPOINT,1);
	checkpointptr->RecordID=1;
	checkpointptr->requestID=1;

	checkpointptr->regionID=1;
	checkpointptr->stripID=1;
	checkpointptr->strsetID=1;
	checkpointptr->chunkID=1;

	checkpointptr->regionoffset=1;
	checkpointptr->stripoffset=1;
	checkpointptr->strsetoffset=1;
	checkpointptr->chunkoffset=1;

	checkpointptr->chunksize=3;

	checkpointptr->orgcontent=(char *)"12";
	//mcpy(checkpointptr->orgcontent,"12",BYTE,2);
	checkpointptr->upcontent=(char *)"12";
	//mcpy(checkpointptr->upconten,"12",BYTE,2);;

	checkpointptr2=talloc(CHECKPOINT,1);
	checkpointptr2->RecordID=1;
	checkpointptr2->upcontent=talloc(BYTE,3);
	checkpointptr2->orgcontent=talloc(BYTE,3);

	mysql_FILELAYER_checkpoint_delete_all();
	mysql_FILELAYER_checkpoint_insert(checkpointptr);
	mysql_FILELAYER_checkpoint_select(checkpointptr2);
	mysql_FILELAYER_checkpoint_select_request_max_indexandcount(checkinf);
	//mysql_FILELAYER_checkpoint_delete_request(1);
	//mysql_FILELAYER_checkpoint_delete_all();
	
	//update_RCW_trace_test();
	//update_RMW_trace_test();
	//update_RMW_update_test();
	//update_RCW_update_test();
	/*UINT32 i,i1,i2,i3,x,y;
	UINT32 *r1;
	UINT32 **m1;
	UINT8 t1[2]={8,9};
	UINT8 *t2,*t3;
	UINT16 u2[2]={8,9},*tar1;
	UINT32 u3[2]={8,9},*tar2;
	UINT8 *target;
	UINT32 mt1[4]={19,13,14,15};
	UINT32 mt2[4]={8,9,15,15};
	UINT32 mt3[4]={8,9,8,9};
	INTMATRIX matrix,matrix1,matrix2,c3;
	i1=3;
	i2=4;
	i3=5;
	t2=(UINT8 *)u2;//规则化格式
	t3=(UINT8 *)u3;	
	target=(UINT8 *)malloc(sizeof(UINT32)*2);//计算
	m1=(UINT32 **)mt1;*/
	//测试底层文件系统
/*	BYTESTREAM bstream;
	bstream.BYTEcontent="abcd";
	bstream.bytessize=5;
	file_FILELAYER_BYTE_CREATE("c:\\1\\1.txt",&bstream);
	bstream.BYTEcontent=NULL;
	bstream.bytessize=1;
	file_FILELAYER_BYTE_READER("c:\\11.txt",&bstream,1);
	file_FILELAYER_BYTE_WRITER("c:\\11.txt",&bstream,3);*/
	//printf("%I64d",3213213213213);
	
	//测试柯西矩阵
	/*INTMATRIX chmatrix,chbitmatrix;
	chmatrix=matrix_create_NULL();
	matrix_set_data(&chmatrix,NULL,3,5,4);
	matrix_set_data(&chbitmatrix,NULL,0,0,3);
	cauchy_orgininal_coding_matrix(&chmatrix);
	matrix_print_matrix_outcheck(&chmatrix);
	matrix_matrix_to_bitmatrix(&chmatrix,&chbitmatrix);
	matrix_print_bitmatrix(&chbitmatrix);
	cauchy_good_general_coding_matrix(&chmatrix);
	matrix_print_matrix_outcheck(&chmatrix);
	matrix_matrix_to_bitmatrix(&chmatrix,&chbitmatrix);
	matrix_print_bitmatrix(&chbitmatrix);
	getchar();
	/*BYTESTREAM bstream;
	bstream.BYTEcontent="abcd";
	bstream.bytessize=5;
	file_FILELAYER_BYTE_CREATE(".\\metadata\\2.txt",&bstream);
	//mkdir("c:\\2\\");*/

	/*int i;
	BITMATRIX matrix;
	//matrix=talloc(BITMATRIX,1);
	matrix.matrix=talloc(UINT32,10*10*2*10);
	matrix.w=5;
	matrix.ym=3*5;
	matrix.xm=2*5;*/
	/*BITMATRIX matrix;
	//matrix=talloc(BITMATRIX,1);
	matrix.matrix=talloc(UINT32,10*10*2*10);
	matrix.w=8;
	matrix.ym=5*8;
	matrix.xm=8;
	MDRII_create_encode_matrix_B(&matrix);
	matrix_print_bitmatrix(&matrix);*/

	//TOOL_create_update_test_set();
	//CHUNK chunkptr;
	//mysql_FILELAYER_chunktable_insert(&chunkptr);
	/*UINT64 deviceid;
	UINT64 diskid[2];
	char r1[10]="10"
			"10";
	deviceid=2;
	diskid[0]=0;
	diskid[1]=1;*/
	
	///mysql_FILELAYER_devicediskid_update(diskid,2,deviceid);
	//mysql_FILELAYER_devicediskid_select(diskid,deviceid);
	/*BITMATRIX matrix;
	///matrix=talloc(BITMATRIX,1);
	matrix.matrix=talloc(UINT32,10*10*2*10);
	matrix.w=4;
	matrix.ym=5*4;
	matrix.xm=3*4;
	//GENRDP_create_encode_matrix(&matrix);
	//matrix_print_bitmatrix(&matrix);

	//MDRI_create_encode_matrix(&matrix);
	//matrix_print_bitmatrix(&matrix);
	//MDRII_create_encode_matrix(&matrix);
	//matrix_print_bitmatrix(&matrix);
	STAR_create_encode_matrix(&matrix);
	matrix_print_bitmatrix(&matrix);
	//XCODE_create_encode_matrix(&matrix);
	//matrix_print_bitmatrix(&matrix);
	//RDP_create_encode_matrix(&matrix);
	//matrix_print_bitmatrix(&matrix);
	//EVENODD_create_encode_matrix(&matrix);
	//matrix_print_bitmatrix(&matrix);
	//printf("%d",1);
	//liberation_create_encode_matrix(&matrix);
	//printf("%d",1);
	//i=matrix->matrix[1];
	//matrix_print_bitmatrix(&matrix);
	//liberation_liber8tion_create_encode_matrix(&matrix);
	//matrix_print_bitmatrix(&matrix);

	
	
	//system（"pause"）;

















	//系统功能测试
	/*ERRORPATTERN *errormatrix;
	BITMATRIX *bitmatrixptr;
	UINT32 *errarry;
	int i;

	errormatrix=talloc(ERRORPATTERN,1);
	if(errormatrix==NULL)
	{
		show_error("test","part","NO memory");
		//return FALSE;
	}

	bitmatrixptr=talloc(BITMATRIX,1);
	if(bitmatrixptr==NULL)
	{
		show_error("test","part","NO memory");
	}

	errarry=talloc(UINT32,6);//开一个6位的存储空间
	if(errarry==NULL)
	{
		show_error("test","part","NO memory");
	}

	errormatrix->bitmatrix=bitmatrixptr;
	errormatrix->errordisknum=1;//有一个磁盘出错
	errormatrix->errorchunknum=NOVALUE;

	bitmatrixptr->matrix=errarry;
	bitmatrixptr->xm=6;
	bitmatrixptr->ym=NOVALUE;
	for(i=0;i<6;i++)
	{
		if(i==1)//假设第二盘坏了
		{
			errarry[i]=TRUE;
		}
		else
		{
			errarry[i]=FALSE;
		}
	}*/
	/*int i,j,k,index,filenumber;
	char *str;
	//double *number;
	FILE *fileptr;
	FILE *fileoutptr;
	double minvalue,maxvalue,avgvalue,sumvalue,number;
	str=talloc(char,200);
	//number=talloc(double,35000);
	index=0;
	
	filenumber=32;
	for(k=0;k<5;k++)
	{
		sprintf(str,"schupdate\\%d.txt",filenumber);
		fileptr=fopen(str,"r");
		sprintf(str,"schupdate\\output%d.txt",filenumber);
		fileoutptr=fopen(str,"w");
		filenumber=filenumber*2;
		for(i=0;i<25;i++)
		{
			minvalue=MAXVALUE;
			maxvalue=PFALSE;
			avgvalue=0;
			sumvalue=0;
			fscanf(fileptr,"%s\n",str);
			for(j=0;j<1000;j++)
			{
				fscanf(fileptr,"%lf\n",&number);
				index++;
				if(number<minvalue)
				{
					minvalue=number;
				}
				if(maxvalue<number)
				{
					maxvalue=number;
				}
				sumvalue=sumvalue+number;
			}
			avgvalue=sumvalue/1000;
			fprintf(fileoutptr,"%lf,%lf,%lf,\n",minvalue,maxvalue,avgvalue);
		}
		
		fclose(fileptr);
		fclose(fileoutptr);
	}*/

	//AONTRS_test();
	//CAONTRS_test();
	//PCAONTRS_test();
	//PAONTRS_test();
	
	//update_data_update_test();
	///update_sch_update_test();
	/*BYTESTREAM *updatestream;
	BYTE *contentptr;
	//systemcom_system_reset_format();
	updatestream=talloc(BYTESTREAM,1);
	if(updatestream==NULL)
	{
		show_error("","","");
	}
	contentptr=talloc(BYTE,chksize_KB(200));
	if(contentptr==NULL)
	{
		show_error("","","");
	}
	mset(contentptr,BYTE,34,chksize_KB(200));
	updatestream->BYTEcontent=contentptr;
	updatestream->bytessize=chksize_KB(200);
	profile_global_system_intial_without_datafile();
	//profile_global_system_intial();
	//encoder_filestore_API_update("region0\\1.rmvb",updatestream,1);
	//encoder_filestore_API_path("region5\\1.txt","D:\\1.txt");//测试一下raid5和raid6编码
	//decoder_filestore_API_path("D:\\2.txt","region5\\1.txt");
	encoder_filestore_API_update("region5\\1.txt",updatestream,400);
	decoder_filestore_API_path("D:\\3.txt","region5\\1.txt");
	//encoder_filestore_API_path("region10\\1.rmvb","D:\\1.rmvb");
	//decoder_filestore_API_path("D:\\2.rmvb","region10\\1.rmvb");
	//encoder_filestore_API_path("region0\\1.txt","D:\\011.txt");
	//decoder_filestore_API_path("D:\\012.txt","region0\\1.txt");//其中BYTESTREAM filecontent代表文件内容，tarpath是文件系统路径
	//先建立一个错误模式

	//decoder_filestore_API_path_degrade("D:\\013.txt","region0\\1.txt",errormatrix);//将数据进行degrade read*/





	//decoder_filestore_API_recover_ID(NULL,errormatrix,0);//计算数据
	//systemcom_metadata_sync();
	//systemcom_system_inital();

	/*__int64 a;
	a=512*(UINT64)1073741824;
	printf("%I64d",a);*/

	//开始测试CHUNK矩阵运算
	/*int i,rows,cols;
	INTMATRIX matrix;
	INTMATRIX decodemat;//解码矩阵
	ERASES erarray;
	int t[10]={TRUE,FALSE,TRUE,FALSE,TRUE,FALSE,FALSE,TRUE,FALSE,FALSE};
	DM_IDS dmids;
	//测试vandermonde矩阵
	rows=10;
	cols=6;
	matrix=matrix_create_w16(NULL,rows,cols);
	//matrix_set_data(&matrix,NULL,rows,cols,11);
	reed_sol_extended_vandermonde_matrix(&matrix);
	matrix_print_matrix(&matrix);
	reed_sol_big_vandermonde_distribution_matrix(&matrix);
	matrix_print_matrix(&matrix);
	rows=4;
	cols=6;//10+4
	matrix=matrix_create_w16(NULL,rows,cols);
	reed_sol_vandermonde_coding_matrix(&matrix);
	matrix_print_matrix(&matrix);*/
	//纠删矩阵

	//计算解码矩阵
	/*decodemat=matrix_create_NULL();//创建一个空解码阵
	erarray=matrix_ERASES_create_NULL();
	matrix_ERASES_set_data(&erarray,t,4,6);
	dmids=matrix_DM_IDS_create_NULL();
	matrix_make_decoding_matrix(&decodemat,&matrix,&erarray,&dmids);
	matrix_print_matrix(&decodemat);*/





	//测试r6编码阵
	/*INTMATRIX mat;
	//计算矩阵
	mat=matrix_create_NULL();
	mat=matrix_create_w16(NULL,2,6);
	reed_sol_r6_matrix(&mat);
	matrix_print_matrix(&mat);*/
	/*int i;
	BYTE a1[4]={1,2,3,4};
	BYTE b1[4]={2,3,5,6};
	BYTE *a;
	BYTE *b;

	CHUNK *chunklist;
	//char *a1;
	CHUNK chk1,chk2,pchk,lost;
	CHUNKGROUP chkg;
	a=talloc(BYTE,4);
	b=talloc(BYTE,4);
	for(i=0;i<4;i++)
	{
		a[i]=a1[i];
		b[i]=b1[i];
	}
	chunklist=talloc(CHUNK,2);
	chk1=matrix_CHUNK_create_NULL();//创建两个
	chk2=matrix_CHUNK_create_NULL();
	pchk=matrix_CHUNK_create_NULL();
	lost=matrix_CHUNK_create_NULL();
	matrix_CHUNK_set_data(&chk1,a,1,0,1,4);
	matrix_CHUNK_set_data(&chk2,b,1,0,1,4);
	chkg=matrix_CHUNKGROUP_create_NULL();
	chunklist[0]=chk1;
	chunklist[1]=chk2;
	matrix_CHUNK_print_data(&chk1,10);
	matrix_CHUNK_print_data(&chk2,10);
	matrix_CHUNKGROUP_set_data(&chkg,chunklist,2);
	//计算校验块
	matrix_do_parity(&chkg,&pchk);
	matrix_CHUNK_print_data(&pchk,10);
	matrix_CHUNKGROUP_add_CHUNK(&chkg,&pchk);
	matrix_CHUNKGROUP_del_CHUNK(&chkg,1);//删除一个设备
	matrix_do_deparity(&chkg,&lost,FALSE);
	matrix_CHUNK_print_data(&lost,10);
	/*matrix_CHUNK_w08_multiply(&lost,8);
	matrix_CHUNK_print_data(&lost,10);
	matrix_CHUNK_w16_multiply(&lost,8);
	matrix_CHUNK_print_data(&lost,10);
	matrix_CHUNK_w32_multiply(&lost,8);
	matrix_CHUNK_print_data(&lost,10);*/
	/*matrix.w=8;
	matrix.xm=2;
	matrix.ym=2;
	matrix=matrix_create_w08(mt1,2,2);
	matrix1=matrix_create_NULL();
	matrix2=matrix_create_NULL();
	c3=matrix_create_NULL();
	c3=matrix_duplicate(&matrix);
	matrix_invert(&c3,&matrix1);
	matrix_matrix_multiply(&matrix,&matrix1,&matrix2);
	matrix_print_matrix(&matrix2);*/
	/*
	//matrix.matrix.matrix8=(UINT8 *)malloc(sizeof(UINT8*2)
	matrix_print_matrix(&matrix);
	matrix_print_bitmatrix(&matrix);
	/*matrix=matrix_create_w16(mt2,2,2);
	matrix_print_matrix(matrix);
	matrix_print_bitmatrix(matrix);
	matrix=matrix_create_w32(mt3,2,2);
	matrix_print_matrix(matrix);
	matrix_print_bitmatrix(matrix);*/
	//带入测试计算公式
	/*galois_w08_region_multiply(t1,8,2,target,FALSE);
	for(i=0;i<2;i++)
	{
		//输出连个数
		printf("%d\n",target[i]);
	}
	target[0]=galois_multtable_multiply(8,8,8);
	target[1]=galois_multtable_multiply(8,9,8);
	for(i=0;i<2;i++)
	{
		//输出连个数
		printf("%d\n",target[i]);
	}
	target[0]=(UINT8)3;
	target[1]=(UINT8)5;
	galois_w08_region_multiply(t1,8,2,target,TRUE);
	for(i=0;i<2;i++)
	{
		printf("%d\n",target[i]);
	}
	target[0]=galois_multtable_multiply(8,8,8)^3;
	target[1]=galois_multtable_multiply(8,9,8)^5;
	for(i=0;i<2;i++)
	{
		printf("%d\n",target[i]);
	}*/
	//测试w32的region
	/*tar2=(UINT32 *)target;
	galois_w32_region_multiply(t3,8,8,target,FALSE);
	for(i=0;i<2;i++)
	{
		printf("%d\n",tar2[i]);
	}
	tar2[0]=galois_split_w8_multiply(8,8);
	tar2[1]=galois_split_w8_multiply(8,9);
	for(i=0;i<2;i++)
	{
		printf("%d\n",tar2[i]);
	}
	tar2[0]=3;
	tar2[1]=5;
	galois_w32_region_multiply(t3,8,8,target,TRUE);
	for(i=0;i<2;i++)
	{
		printf("%d\n",tar2[i]);
	}
	tar2[0]=galois_split_w8_multiply(8,8)^3;
	tar2[1]=galois_split_w8_multiply(8,9)^5;
	for(i=0;i<2;i++)
	{
		printf("%d\n",tar2[i]);
	}*/
	//测试w16的region
	
	/*galois_w16_region_multiply(t2,8,4,target,FALSE);
	tar1=(UINT16 *)target;//转化为16位型
	for(i=0;i<2;i++)
	{
		printf("%d\n",tar1[i]);
	}
	tar1[0]=galois_log_multiply(8,8,16);
	tar1[1]=galois_log_multiply(8,9,16);
	for(i=0;i<2;i++)
	{
		printf("%d\n",tar1[i]);
	}
	target[0]=3;//因为是8为
	target[1]=0;
	target[2]=5;
	target[3]=0;
	galois_w16_region_multiply(t2,8,4,target,TRUE);
	for(i=0;i<2;i++)
	{
		printf("%d\n",tar1[i]);
	}
	tar1[1]=galois_log_multiply(8,8,16)^3;
	tar1[1]=galois_log_multiply(8,9,16)^5;
	for(i=0;i<2;i++)
	{
		printf("%d\n",tar1[i]);
	}*/
	
	//galois_region_xor(&i1,&i2,&i3,1);
	//printf("%d",i3);
	//i3=galois_region_subtract(i1,i2,1);
	//i3=galois_region_add(i1,i2,1);
	//printf("%d",i3);
	//galois_log_intial();
	//show_error("sa","asa","sa");
	/*
	r1=galois_ilog_table(4);
	for(i=0;i<(1<<4);i++)
	{
		printf("%d\n",r1[i]);
	}*/
	//i1=galois_log_multiply(3,7,4);
	//printf("%d\n",i1);
	//i1=galois_log_divide(9,7,4);
	//printf("%d\n",i1);
	//galois_multtable_intial();
	//i1=galois_multtable_multiply(3,7,4);
	//printf("%d\n",i1);
	//i2=i1=galois_multtable_divide(1,7,4);
	//printf("%d\n",i2);
	/*r1=galois_log_table(4);
	for(i=0;i<(1<<4);i++)
	{
		printf("%d\n",r1[i]);
	}*/
	/*m1=galois_mult_table(3);
	for(x=0;x<(1<<3);x++)
	{
		for(y=0;y<(1<<3);y++)
		{
			printf("%d*%d=%d ",x,y,m1[x][y]);
		}
		printf("\n");
	}*/
	/*m1=galois_div_table(3);
	for(x=0;x<(1<<3);x++)
	{
		for(y=0;y<(1<<3);y++)
		{
			printf("%d/%d=%d ",x,y,m1[x][y]);
		}
		printf("\n");
	}
	for(x=0;x<(1<<3);x++)
	{
		for(y=0;y<(1<<3);y++)
		{
			printf("%d/%d=%d ",x,y,galois_shift_divide(x,y,3));
		}
		printf("\n");
	}*/
	//i1=galois_shift_multiply(9,6,4);
	//printf("%d\n",i1);
	//i1=galois_shift_divide(9,7,4);
	//printf("%d\n",i1);
	//int i1;
	//i1=galois_multtable_multiply(9,6,4);
	//printf("%d\n",i1);
	//i1=galois_shift_inverse(3,4);
	///printf("%d\n",i1);
	//galois_create_split_w8_table();
	//i1=galois_split_w8_multiply(25,26);
	//i2=galois_shift_multiply(25,26,32);
	//printf("%d  %d",i1,i2);
	//i1=galois_single_multiply(14,251,8);
	//printf("%d\n",i1);
	//i1=galois_single_multiply(14,251,16);
	//printf("%d\n",i1);
	//i1=galois_single_multiply(200,200,32);
	//printf("%d\n",i1);
	//i1=galois_shift_multiply(200,200,32);
	//printf("%d\n",i1);
	//i2=galois_shift_divide(i1,200,32);
	//printf("%d\n",i2);
	//i2=galois_single_divide(i1,20,32);
	//i2=sizeof(int);
	//printf("%d\n",i2);
	//i1=galois_shift_inverse(24,14);
	//printf("%d\n",i1);
	//i1=galois_inverse(24,14);
	//i2=galois_shift_multiply(12,24,32);
	//i1=galois_shift_divide(i2,12,32);
	//printf("%d\n",i1);
	/*i1=galois_single_multiply(120,90,8);
	i2=galois_single_divide(i1,90,8);
	printf("%d\n",i2);
	i1=galois_single_multiply(120,90,16);
	i2=galois_single_divide(i1,90,16);
	printf("%d\n",i2);
	i1=galois_single_multiply(120,90,24);
	i2=galois_single_divide(i1,90,24);
	printf("%d\n",i2);
	i1=galois_single_multiply(120,90,32);
	i2=galois_single_divide(i1,90,32);
	printf("%d\n",i2);*/
	getchar();

}