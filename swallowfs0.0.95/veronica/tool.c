#include "tool.h"
int TOOL_create_test_Dictionary(char *dicpath,int filenum,int fhighsize,int flowsize,int updatenum,int uhighsize,int ulowsize)
{
	//����·��
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
	//�ж�Ŀ���ļ����Ƿ����
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
	//�����ļ�ָ��
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

	//���ļ������ļ�����·��
	for(i=0;i<filenum;i++)//�������ɲ����ļ�
	{
		//���㵱ǰ
		filesize=(int)(((float)fhighsize-(float)flowsize+1)*(float)randomnumber01+(float)flowsize);//�����ļ���С
		//��ʼ����·��
		contentptr->BYTEcontent=NULL;
		contentptr->bytessize=filesize;

		sprintf(filedatapath,"%s\\%d.txt",dicpath,i);//����ļ�·��

		resTF=file_FILELAYER_BYTE_CREATE(filedatapath,contentptr);//�����ļ�
		if(resTF==FALSE)
		{
			show_error("TOOL","create_update_test_simple","file can't create");
			return FALSE;
		}
		fprintf(fileptr,"file %d:file size %d\n",i,filesize);//���ļ�����д���ļ������ļ�
		filesizelist[i]=filesize;//������¼����
	}

	fprintf(fileptr,"there are %d update operations\n",updatenum);
	for(i=0;i<updatenum;i++)
	{
		//��һ���������һ���ļ����
		fileindex=filenum*randomnumber01;
		filesize=filesizelist[fileindex];
		//�����ļ���С���������ƫ����
		updateoffset=(int)((float)randomnumber01*(float)(filesize-uhighsize));//�����һ������֮ǰ����ƫ����
		updatesize=(int)(((float)uhighsize-(float)ulowsize+1)*(float)randomnumber01+(float)ulowsize);//���ɸ�������
		//������д���ļ�
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
