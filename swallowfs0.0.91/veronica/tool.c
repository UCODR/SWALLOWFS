#include "tool.h"
int TOOL_create_test_Dictionary(char *dicpath,int filenum,int fhighsize,int flowsize,int updatenum,int uhighsize,int ulowsize)
{
	//生成路径
	int resTF;
	
	if(dicpath==NULL)
	{ 
		show_error("TOOL","create_test_Dictionary","dicpath is no memory");
		return FALSE;
	}
	sprintf(dicpath,".\\test\\%d-%d-%d-%d-%d-%d",filenum,fhighsize,flowsize,updatenum,uhighsize,ulowsize);
	resTF=file_FILELAYER_dictionary_exists(dicpath);
	if(resTF==FALSE)
	{
		show_error("TOOL","create_test_Dictionary","dictionary can't create");
		return FALSE;
	}
	return TRUE;
}
int TOOL_create_update_test_simple(int filenum,int fhighsize,int flowsize,int updatenum,int uhighsize,int ulowsize)
{
	//判断目标文件夹是否存在
	int i,resTF;
	int filesize,fileindex,updateoffset,updatesize;
	int *filesizelist;
	FILE *dicfileptr,*fileptr,*filedataptr;
	char *dicpath,*dicdatapath,*filepath,*filedatapath;
	BYTESTREAM *contentptr;
	
	dicpath=talloc(char,100);
	if(dicpath==NULL)
	{
		show_error("TOOL","create_update_test_simple","No memory");
		return FALSE;
	}
	dicdatapath=talloc(char,100);
	if(dicdatapath==NULL)
	{
		show_error("TOOL","create_update_test_simple","No memory");
		return FALSE;
	}
	resTF=TOOL_create_test_Dictionary(dicpath,filenum,fhighsize,flowsize,updatenum,uhighsize,ulowsize);
	if(resTF==FALSE)
	{
		show_error("TOOL","create_update_test_simple","disctionary can't create");
		return FALSE;
	}
	sprintf(dicdatapath,".\\test\\testdes.txt");
	//开启文件指针
	dicfileptr=fopen(dicdatapath,"a+");
	if(dicfileptr==NULL)
	{
		show_error("TOOL","update_test_simple","file handle can't open");
		return FALSE;
	}
	fprintf(dicfileptr,"%d-%d-%d-%d-%d-%d\n",filenum,fhighsize,flowsize,updatenum,uhighsize,ulowsize);
	fclose(dicfileptr);

	filepath=talloc(char,200);
	if(filepath==NULL)
	{
		show_error("TOOL","create_update_test_simple","no memory");
		return FALSE;
	}

	sprintf(filepath,"%s//updatedes.txt",dicpath);
	fileptr=fopen(filepath,"wb");
	if(fileptr==NULL)
	{
		show_error("TOOL","create_update_test_simple","file handle can't open");
		return FALSE;
	}

	filedatapath=talloc(char,200);
	if(filedatapath==NULL)
	{
		show_error("TOOL","create_update_test_simple","no memory");
		return FALSE;
	}

	fprintf(fileptr,"there are %d test file\n",filenum);
	filesizelist=talloc(int,filenum);
	if(filesizelist==NULL)
	{
		show_error("TOOL","create_update_test_simple","No memory");
		return FALSE;
	}

	contentptr=talloc(BYTESTREAM,1);
	if(contentptr==NULL)
	{
		show_error("TOOL","create_update_test_simple","No memory");
		return FALSE;
	}

	//将文件创建文件数据路径
	for(i=0;i<filenum;i++)//依次生成测试文件
	{
		//计算当前
		filesize=(int)(((float)fhighsize-(float)flowsize+1)*(float)randomnumber01+(float)flowsize);//生成文件大小
		//开始计算路径
		contentptr->BYTEcontent=NULL;
		contentptr->bytessize=filesize;

		sprintf(filedatapath,"%s\\%d.txt",dicpath,i);//输出文件路径

		resTF=file_FILELAYER_BYTE_CREATE(filedatapath,contentptr);//创建文件
		if(resTF==FALSE)
		{
			show_error("TOOL","create_update_test_simple","file can't create");
			return FALSE;
		}
		fprintf(fileptr,"file %d:file size %d\n",i,filesize);//将文件数据写入文件描述文件
		filesizelist[i]=filesize;//将他记录下来
	}

	fprintf(fileptr,"there are %d update operations\n",updatenum);
	for(i=0;i<updatenum;i++)
	{
		//第一步随机生成一个文件编号
		fileindex=filenum*randomnumber01;
		filesize=filesizelist[fileindex];
		//更具文件大小，随机生成偏移量
		updateoffset=(int)((float)randomnumber01*(float)(filesize-uhighsize));//在最后一个区域之前生成偏移量
		updatesize=(int)(((float)uhighsize-(float)ulowsize+1)*(float)randomnumber01+(float)ulowsize);//生成更新数据
		//将数据写入文件
		fprintf(fileptr,"update operation %d:file %d,offset %d,update size %d\n",i,fileindex,updateoffset,updatesize);
	}
	free(dicpath);
	free(dicdatapath);
	free(filepath);
	fclose(fileptr);
	return TRUE;
}

int TOOL_create_update_test_set()
{
	//
	int i,j,resTF,updatesize,filenum,fhighsize,flowsize,updatanum,uhighsize,ulowsize;
	filenum=20;
	updatanum=1000;
	resTF=remove(".\\test\\testdes.txt");
	if(resTF==PFALSE)
	{
		printf("testdes is now exist");
	}
	
	for(i=0;i<7;i++)//
	{
		switch(i)//
		{
		case 0:
			flowsize=chksize_KB(1);
			fhighsize=chksize_KB(4);
			break;
		case 1:
			flowsize=chksize_KB(8);
			fhighsize=chksize_KB(32);
			break;
		case 2:
			flowsize=chksize_KB(64);
			fhighsize=chksize_KB(256);
			break;
		case 3:
			flowsize=chksize_KB(512);
			fhighsize=chksize_MB(1);
			break;
		case 4:
			flowsize=chksize_MB(2);
			fhighsize=chksize_MB(8);
			break;
		case 5:
			flowsize=chksize_MB(16);
			fhighsize=chksize_MB(64);
			break;
		case 6:
			flowsize=chksize_MB(128);
			fhighsize=chksize_GB(1);
			break;
		}
		for(j=0;j<5;j++)
		{
			ulowsize=1;
			uhighsize=flowsize*j*0.2;
			resTF=TOOL_create_update_test_simple(filenum,fhighsize,flowsize,updatanum,uhighsize,ulowsize);
			if(resTF==FALSE)
			{
				show_error("TOOL","create_update_test_set","the update test data can't create");
				return FALSE;
			}
			
		}
	}
	return TRUE;
}
