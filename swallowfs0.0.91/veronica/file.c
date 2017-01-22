#include "file.h"
//filelayer
int file_FILELAYER_intial()
{
	return TRUE;
}
//�ײ�
int file_FILELAYER_device_available(DISK *diskptr)
{
	int resTF;
	char *pathstr;
	pathstr=diskptr->diskpath;
	resTF=access(pathstr,0);
	if(resTF!=-1)
	{
		return TRUE;
	}
	return FALSE;
}
//����������·����ƫ����λ�ö�ȡ
int file_FILELAYER_BYTE_READER(char *filepath,BYTESTREAM *bstream,long offset)//��������д���ƶ�·������,�ļ��Ѿ�����
{
	FILE *pfile;
	int bytesize,readsize,resTF;
	BYTE *bytestream;//���ص���Ӧ�����ݴ�
	//��ȡ��Ӧ������
	bytestream=bstream->BYTEcontent;
	bytesize=bstream->bytessize;
	//�ȴ�һ���ļ�������
	//���仺��ռ�
	if(bytestream!=NULL)
	{
		free(bytestream);

	}
	bytestream=talloc(BYTE,bytesize);//�����ڴ�����
	if(bytestream==NULL)
	{
		show_error("file_FILELAYER","BYTE_READER","No memory");
		return FALSE;
	}
	pfile=fopen(filepath,"rb+");
	if(pfile==NULL)
	{
		show_error("file_FILELAYER","BYTE_READER","file isn't exist");
		return FALSE;
	}
	//�趨ƫ����
	resTF=fseek(pfile,offset,SEEK_SET);
	if(resTF!=0)
	{
		show_error("file_FILELAYER","BYTE_READER","offset is wrong");
		return FALSE;
	}
	//�����ݶ�����Ӧλ��
	readsize=fread(bytestream,sizeof(BYTE),bytesize,pfile);
	if(readsize!=bytesize)
	{
		show_error("file_FILELAYER","BYTE_READER","reading process wrong");
		return FALSE;
	}
	bstream->BYTEcontent=bytestream;
	fclose(pfile);//�������Ұָ��
	return TRUE;
}
//��������д���ƶ�·��ƫ��������
int file_FILELAYER_BYTE_WRITER(char *filepath,BYTESTREAM *bstream,long offset)//��������д���ƶ�·��ƫ��������,�ļ��Ѿ�����
{
	FILE *pfile;
	int bytesize,writesize,resTF;
	BYTE *bytestream;//���ص���Ӧ�����ݴ�
	//��ȡ��Ӧ������
	bytestream=bstream->BYTEcontent;
	bytesize=bstream->bytessize;
	pfile=fopen(filepath,"rb+");
	if(pfile==NULL)
	{
		show_error("file","FILELAYER_BYTE_WRITER","FILE handle can't open");
		return FALSE;
	}
	//�趨ƫ����
	resTF=fseek(pfile,offset,SEEK_SET);
	if(resTF!=0)
	{
		show_error("file_FILELAYER","BYTE_READER","offset is wrong");
		return FALSE;
	}
	//������д�뵽��Ӧλ��
	writesize=fwrite(bytestream,sizeof(BYTE),bytesize,pfile);
	
	if(writesize!=bytesize)
	{
		show_error("file_FILELAYER","BYTE_WRITER","write process failed");
		return FALSE;
	}
	fclose(pfile);
	return TRUE;
}
int file_FILELAYER_BYTE_CREATE(char *filepath,BYTESTREAM *bstream)
{
	FILE *pfile;
	int bytesize,writesize;
	BYTE *bytestream;//���ص���Ӧ�����ݴ�
	//��ȡ��Ӧ������
	bytestream=bstream->BYTEcontent;
	bytesize=bstream->bytessize;
	pfile=fopen(filepath,"wb");
	//������д�뵽��Ӧλ��
	//writesize=fwrite(bytestream,sizeof(BYTE),bytesize,pfile);
	//��췽����ֱ�ӹ�ƫ����
	writesize=fseek(pfile,bytesize,SEEK_SET);
	if(writesize!=0)
	{
		show_error("file_FILELAYER","BYTE_WRITER","write process failed");
		return FALSE;
	}
	fputc(0,pfile);//����һ��0

	fclose(pfile);
	return TRUE;
}
//region,strip,stripsect�ֿ������
int file_glostr(char *gloname,char *glokind,char *gloid,char *finalitem)
{
	strcat(gloname,glokind);
	strcat(gloname,gloid);
	strcat(gloname,finalitem);
	return TRUE;
}
int file_regionstr(char *regname,char *regid)
{
	file_glostr(regname,"region",regid,"\\");
	return TRUE;
}
int file_regionstr_name(char *regname,char *regid)
{
	file_glostr(regname,"region",regid,".txt");
	return TRUE;
}
int file_stripstr(char *strname,char *strid)
{
	file_glostr(strname,"strip",strid,"\\");
	return TRUE;
}
int file_stripstr_name(char *strname,char *strid)
{
	file_glostr(strname,"strip",strid,".txt");
	return TRUE;
}
int file_stripsectstr(char *strsetname,char *strsetid)
{
	file_glostr(strsetname,"stripsect",strsetid,"\\");
	return TRUE;
}
int file_stripsectstr_name(char *strsetname,char *strsetid)
{
	file_glostr(strsetname,"stripsect",strsetid,".txt");
	return TRUE;
}
int file_chunkstr_name(char *chkname,char *chkid)
{
	file_glostr(chkname,"chunk",chkid,".txt");
	return TRUE;
}
int file_filemetastr(char *filemetaname,char *filemetaid)
{
	file_glostr(filemetaname,"filemeta","","\\");
	return TRUE;
}
int file_filemetastr_name(char *filemetaname,char *filemetaid)
{
	file_glostr(filemetaname,"filemeta",filemetaid,".txt");
	return TRUE;
}
int file_userprofilestr(char *username,char *userid)
{
	file_glostr(username,"userprofile","","\\");
	return TRUE;
}
int file_userprofilestr_name(char *username,char *userid)
{
	file_glostr(username,"userprofile",userid,".txt");
	return TRUE;
}
int file_devicestr(char *devicename,char *deviceid)
{
	file_glostr(devicename,"device",deviceid,"\\");
	return TRUE;
}
int file_devicestr_name(char *devicename,char *deviceid)
{
	file_glostr(devicename,"device",deviceid,".txt");
	return TRUE;
}
int file_diskstr_name(char *diskname,char *diskid)
{
	file_glostr(diskname,"disk",diskid,".txt");
	return TRUE;
}
int file_globaldeine_name(char *glodepath)
{
	file_glostr(glodepath,"global_define","",".txt");
	return TRUE;
}
//���ݲ��� 
//��������������Ҫ�Ǹ���id����д
//����chunk��д����������������Ҫ�������
//��CHUNK�������а�����·����������Ӧ������,Ԫ���ݲ���
//��CHUNK����ȫ��·����chunkpath��ȡԪ����
int file_FILELAYER_CHUNK_READER_META(CHUNK *chk)
{
	UINT64 regionid;//chunk����region���
	UINT64 stripid;//chunk����strip���
	UINT64 stripsectid;//chunk����stripsect���
	UINT64 diskid;//chunk����disk���
	UINT64 deviceid;//chunk����device���
	UINT64 fileid;//chunk����file���
	CHUNKPATH *chkpath;
	//�ϼ�ָ��
	UINT64 chunkid;
	REGION *regionptr;
	STRIP *stripptr;
	STRIPSECT *strsetptr;
	char *metapath;//chunkԪ����
	char *glometapath;//ȫ��Ԫ���ݵ�ַ

	char regionidstr[20]="";
	char stripidstr[20]="";
	char strsetidstr[20]="";
	char chunkidstr[20]="";
	char regionidnamestr[30]="",stripidnamestr[30]="",strsetidnamestr[30]="",chunkfilenamestr[40]="";//����Ϊ30λstripset+/��10���ַ�
	int isparity,sizenum,storestate;//һЩ����
	FILE *flin;//�����ļ�ָ��
	//��ʼ��ֵ
	/*sizenum=chk->sizenum;
	isparity=chk->isparity;
	regionid=chk->regionid;
	regionptr=chk->regionptr;
	stripid=chk->stripid;
	diskid=chk->diskid;
	deviceid=chk->deviceid;
	fileid=chk->fileid;

	stripptr=chk->stripptr;
	stripsectid=chk->stripsectid;
	strsetptr=chk->stripsectptr;
	chunkid=chk->ChunkID;

	storestate=chk->storestate;*/
	chunkid=chk->ChunkID;
	chkpath=chk->chkpath;
	regionid=chkpath->regionid;
	regionptr=chkpath->regionptr;
	stripptr=chkpath->stripptr;
	stripid=chkpath->stripid;
	stripsectid=chkpath->stripsectid;
	strsetptr=chkpath->stripsectptr;
	stripsectid=chkpath->stripsectid;
	//��ȫ�Լ��
	if(regionptr==NULL)
	{
		show_error("file_FILELAYER","CHUNK_READER","region point is not exist");
		return FALSE;
	}
	if(stripptr==NULL)
	{
		show_error("file_FILELAYER","CHUNK_READER","strip point is not exist");
		return FALSE;
	}
	if(strsetptr==NULL)
	{
		show_error("file_FILELAYER","CHUNK_READER","stripsect point is not exist");
		return FALSE;
	}
	//��ʼ���д洢״̬���
	/*if(regionptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","CHUNK_READER","region state is empty");
		return FALSE;
	}
	if(stripptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","CHUNK_READER","strip state is empty");
		return FALSE;
	}
	if(strsetptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","CHUNK_READER","strip state is empty");
		return FALSE;
	}*/
	//�ҵ�ȫ��Ԫ���ݵ�ַ
	glometapath=get_state_glometapath();//��ȡȫ��Ԫ����ָ��
	metapath=talloc(char,(1000+30+30+30+40));//60λ��·��
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//�����ַ���
	//����·��
	U64toSTR(regionidstr,regionid);
	U64toSTR(stripidstr,stripid);
	U64toSTR(strsetidstr,stripsectid);
	U64toSTR(chunkidstr,chunkid);
	//������Ӧ���ַ���
	file_regionstr(regionidnamestr,regionidstr);//����region�ַ���
	file_stripstr(stripidnamestr,stripidstr);//����strip�ַ���
	file_stripsectstr(strsetidnamestr,strsetidstr);//����stripsect�ַ���
	file_chunkstr_name(chunkfilenamestr,chunkidstr);//����stripsect�ַ���

	//·��������һ��
	strcat(metapath,glometapath);//��Ԫ����·��ƴ����ȥ
	strcat(metapath,regionidnamestr);//��region�ַ���ƴ����ȥ
	strcat(metapath,stripidnamestr);//��strip�ַ���ƴ����ȥ
	strcat(metapath,strsetidnamestr);//��stripsect�ַ���ƴ����ȥ
	strcat(metapath,chunkfilenamestr);//��stripsect�ַ���ƴ����ȥ
	//��ʼ��д
	
	flin=fopen(metapath,"r+");
	if(flin==NULL)
	{
		show_error("file_FILELAYER","CHUNK_READER","file can't open");
		return FALSE;
	}
	//��ʼ�Ӷ�ȡԪ����
	//��Ҫ�Ա������д��
	/*
	fprintf(flout,"chunk id:%I64d\n",chkid);
	fprintf(flout,"the chunk is parity(0:FALSE,1:TRUE):%d\n",isparity);
	//·�����Բ������
	fprintf(flout,"the chunk size:%d\n",sizenum);
	fprintf(flout,"region id:%I64d\n",regionid);
	fprintf(flout,"strip id:%I64d\n",stripid);
	fprintf(flout,"stripsect id:%I64d\n",stripsectid);
	fprintf(flout,"disk id:%I64d\n",diskid);
	fprintf(flout,"device id:%I64d\n",deviceid);
	fprintf(flout,"file id:%%I64d\n",fileid);
	//��ǰ�洢״̬
	fprintf(flout,"stripsect state(countnum):%d\n",storestate);
	*/
	fscanf(flin,"chunk id:%I64d\n",&chunkid);
	fscanf(flin,"the chunk is parity(0:FALSE,>0:TRUE):%d\n",&isparity);
	//·�����Բ������
	fscanf(flin,"the chunk size:%d\n",&sizenum);
	fscanf(flin,"region id:%I64d\n",&regionid);
	fscanf(flin,"strip id:%I64d\n",&stripid);
	fscanf(flin,"stripsect id:%I64d\n",&stripsectid);
	fscanf(flin,"disk id:%I64d\n",&diskid);
	fscanf(flin,"device id:%I64d\n",&deviceid);
	fscanf(flin,"file id:%I64d\n",&fileid);
	//��ǰ�洢״̬
	fscanf(flin,"chunk state(countnum):%d\n",&storestate);
	//����ȡԪ����д��
	chk->ChunkID=chunkid;

	chk->isparity=isparity;
	chk->sizenum=sizenum;
	chk->regionid=regionid;
	chk->stripid=stripid;
	chk->diskid=diskid;
	chk->deviceid=deviceid;
	chk->fileid=fileid;

	chk->storestate=storestate;
	fclose(flin);
	free(metapath);//�ͷ�Ԫ����·��
	return TRUE;
}
//��CHUNK�������а�����·����������Ӧ������,���ݲ���
int file_FILELAYER_CHUNK_READER_DATA(CHUNK *chk)
{
	CHUNKPATH *chkpath;//���ڼ�¼��ǰchunk��·��
	UINT64 chkid;//�û����ҵ�ǰ�ڿ����ļ��е�ƫ����
	char *strsetpath;//stripsect���ļ�ϵͳ�е�·��
	int resTF;//stripsect�еڼ������Լ���Ӧ��ƫ����
	long offset;//ƫ����
	REGION *regionptr;//��ǰchunk����regionָ��
	STRIP *stripptr;//��ǰchunk����stripָ��
	STRIPSECT *strsetptr;//��ǰCHUNK����������
	int i,chkindex,chunksize;//ÿһ��chunk�Ĵ�С
	BYTESTREAM chkcontent; //chunk��ȡ����
	int chunknum;//��ǰstripsect�е�chunk��
	UINT64 *chkidlist;//��ǰchunk����б�
	UINT64 currentid;
	//����ָ����и�ֵ
	chkpath=chk->chkpath;
	regionptr=chkpath->regionptr;
	stripptr=chkpath->stripptr;
	strsetptr=chkpath->stripsectptr;

	//��ȫ�Լ��
	if(regionptr==NULL)
	{
		show_error("file_FILELAYER","CHUNK_READER","region point is not exist");
		return FALSE;
	}
	if(stripptr==NULL)
	{
		show_error("file_FILELAYER","CHUNK_READER","strip point is not exist");
		return FALSE;
	}
	if(strsetptr==NULL)
	{
		show_error("file_FILELAYER","CHUNK_READER","stripsect point is not exist");
		return FALSE;
	}
	//��ʼ���д洢״̬���
	/*if(regionptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","CHUNK_READER","region state is empty");
		return FALSE;
	}
	if(stripptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","CHUNK_READER","strip state is empty");
		return FALSE;
	}
	if(strsetptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","CHUNK_READER","strip state is empty");
		return FALSE;
	}*/
	if(chk->storestate==EMPTY)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","chunk state is empty");
		return FALSE;
	}
	//��ʼ��ֵ
	chkid=chk->ChunkID;

	strsetpath=strsetptr->filepath;//��ȡ�ļ�·��
	chunksize=chk->sizenum;
	chkcontent.bytessize=chk->sizenum;//����Ҫ��ȡ������
	chunknum=strsetptr->chunknum;
	chkidlist=strsetptr->chunkid;
	//��ʼ�����ڴ��ȡ����
	chkcontent.BYTEcontent=talloc(BYTE,chunksize);
	//���¾߱�����ʼ����ƫ����
	chkindex=chkpath->chunkarrayid;//����ƫ����
	/*for(i=0;i<chunknum;i++)
	{
		currentid=chkidlist[i];//��ȡ��ǰid
		if(currentid==chkid)
		{
			break;//����
		}
		chkindex++;//chkindex�ۼ�
	}*/
	if(chkindex==chunknum)
	{
		show_error("file_FILELAYER","CHUNK_READER","chunk id can't find out");
		return FALSE;
	}
	//��ʼ����ƫ����
	offset=chkindex*chunksize;
	resTF=file_FILELAYER_BYTE_READER(strsetpath,&chkcontent,offset);//׼����϶�ȡ
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","CHUNK_READER","can't read chunk content");
		return FALSE;
	}
	chk->chunkcontent=chkcontent.BYTEcontent;//����ȡ�����ݽ��и�ֵ
	return TRUE;
}

//��STRIPSECT�������а�����·����������Ӧ������
int file_FILELAYER_STRIPSECT_READER(STRIPSECT *strset)
{
		//������Ҫ��ȡԪ���ݼ���
	int i,chunksize;
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	//UINT64 regionid,stripid,strsectid;//����ʵ��ı��
	UINT64 strsetid;//strset�ı��
	REGION *regionptr;//����ָ��
	STRIP *stripptr;//����ָ��
	char regoinidstr[20]="",stripidstr[20]="",strsetidstr[20]="";//����Ϊ20λ��ԭ����2^64�η�1.8*19^19
	char regionidnamestr[30]="",stripidnamestr[30]="",strsetidnamestr[30]="";//����Ϊ30λstripset+/��10���ַ�
	char strsetfilename[40]="";
	/*
	UINT64 StripsectID;//STRIPSECT��id

	UINT64 *chunkid;//	���а�����chunkid
	CHUNKGROUP *chunklist;//����һ��chunkgroup�þ߼�¼chunk��,��Ϊһ��chunkָ��
	int chunksize;//chunk��С
	int chunknum;//������chunk��������

	UINT64 regionid;///���ڵ�region���
	struct REGION *regionptr;//��һ��regionָ��

	UINT64 stripid;//���ڵ�strip���
	struct STRIP *stripptr;//��һ��stripָ��

	UINT64 diskid;//���ڵ�disk���
	struct DISK *diskptr;//��һ��diskָ��

	UINT64 deviceid;//���ڵ�device���
	struct DEVICE *deviceptr;//��һ��deviceָ��

	char *filename;//�ļ���
	//veronica��
	char *filepath;//�ļ�������·�����������disk�е�·����filename���

	int storestate;//��ǰ�洢״̬
	*/
	UINT64 *chunkid;//��ǰchunk��ָ����
	int chunknum;//chunk����
	int isparity;//У��λ

	UINT64 regionid;//region���

	UINT64 stripid;//strip���

	UINT64 diskid;//��ǰ�洢�����

	UINT64 deviceid;//�豸���

	char *filename;//�ļ���
	char *filepath;//�ļ�·��

	int storestate; //��ǰ�洢״̬

	FILE *flin;
	//������ռ�
	filename=talloc(char,60);//�ļ���
	if(filename==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_READER","no memory");
		return FALSE;
	}
	filepath=talloc(char,200);//�ļ�·��
	if(filepath==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_READER","no memory");
		return FALSE;
	}
	//ָ�븳ֵ
	regionptr=strset->regionptr;
	regionid=strset->regionid;
	stripptr=strset->stripptr;
	stripid=strset->stripid;
	strsetid=strset->StripsectID;
	if(regionptr==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_READER","region point is not exist");
		return FALSE;
	}
	if(stripptr==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_READER","strip point is not exist");
		return FALSE;
	}
	//��ʼ���д洢״̬���
	/*if(regionptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","STRIPSECT_READER","region state is empty");
		return FALSE;
	}
	if(stripptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","STRIPSECT_READER","strip state is empty");
		return FALSE;
	}*/
	//�ҵ�ȫ��Ԫ���ݵ�ַ
	glometapath=get_state_glometapath();//��ȡȫ��Ԫ����ָ��
	//Ԫ����λ��
	metapath=talloc(char,(30+30+30+40+1000));//1000λ��·��
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_READER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//�����ַ���
	//��ʼ�����ļ�Ԫ����·������
	U64toSTR(regoinidstr,regionid);//��������id
	U64toSTR(stripidstr,stripid);//��������id
	U64toSTR(strsetidstr,strsetid);//������������id

	file_regionstr(regionidnamestr,regoinidstr);//����region�ַ���
	file_stripstr(stripidnamestr,stripidstr);//����strip�ַ���
	file_stripsectstr(strsetidnamestr,strsetidstr);//����stripsect�ַ���
	file_stripsectstr_name(strsetfilename,strsetidstr);//����stripsect���ļ���

	//·��������һ��
	strcat(metapath,glometapath);//��Ԫ����·��ƴ����ȥ
	strcat(metapath,regionidnamestr);//��region�ַ���ƴ����ȥ
	strcat(metapath,stripidnamestr);//��strip�ַ���ƴ����ȥ
	strcat(metapath,strsetidnamestr);//��stripsect�ַ���ƴ����ȥ
	strcat(metapath,strsetfilename);//��stripsect���ļ���ƴ����ȥ

	flin=fopen(metapath,"r+");//��Ԫ�������ڶ�ȡ
	if(flin==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_READER","fptr can't create");
		return FALSE;
	}
	/*fprintf(flout,"the stripset id: %I64d\n",strsetid);//
	fprintf(flout,"the chunksize:%d",chunksize);//
	fprintf(flout,"there are: %d chunks\n, chunk id list:\n",chunknum);
	for(i=0;i<chunknum;i++)
	{
		fprintf(flout,"%I64d\n",chunkid[i]);//��chunk��������Ԫ�����ļ���
	}
	//�ϲ�id��д��
	fprintf(flout,"region id:%I64d\n",regionid);
	fprintf(flout,"strip id:%I64d\n",stripid);
	fprintf(flout,"disk id:%I64d\n",diskid);
	fprintf(flout,"device id:%I64d\n",deviceid);

	//�������ļ�·��д��
	fprintf(flout,"store filename:%s\n",filename);
	fprintf(flout,"store filepath:%s\n",filepath);
	//��ǰ�洢״̬
	fprintf(flout,"stripsect state(countnum):%d\n",storestate);
	fclose(flout);
	free(metapath);//����ͷ�·����Ϣ*/
	//�ο������������
	fscanf(flin,"the stripset id: %I64d\n",&strsetid);//chunk�Ļ�����Ϣ
	fscanf(flin,"the stripsect is parity(0:FALSE,>0:TRUE):%d\n",&isparity);
	fscanf(flin,"the chunksize:%d\n",&chunksize);
	fscanf(flin,"there are: %d chunks, chunk id list:\n",&chunknum);
	chunkid=talloc(UINT64,chunknum);
	for(i=0;i<chunknum;i++)
	{
		fscanf(flin,"%I64d\n",&chunkid[i]);//��chunk��������Ԫ�����ļ���
	}
	//�ϲ�id��д��
	fscanf(flin,"region id:%I64d\n",&regionid);
	fscanf(flin,"strip id:%I64d\n",&stripid);
	fscanf(flin,"disk id:%I64d\n",&diskid);
	fscanf(flin,"device id:%I64d\n",&deviceid);
	//�������ļ�·��д��
	fscanf(flin,"store filename:%s\n",filename);
	fscanf(flin,"store filepath:%s\n",filepath);
	//��ǰ�洢״̬
	fscanf(flin,"stripsect state(countnum):%d\n",&storestate);

	strset->StripsectID=strsetid;

	strset->isparity=isparity;
	strset->chunksize=chunksize;

	strset->chunknum=chunknum;
	strset->chunkid=chunkid;

	strset->regionid=regionid;
	strset->stripid=stripid;

	strset->deviceid=deviceid;
	strset->diskid=diskid;

	strset->filename=filename;
	strset->filepath=filepath;

	strset->storestate=storestate;
	fclose(flin);
	free(metapath);//����ͷ�·����Ϣ
	return TRUE;
}

//��STRIP�������а�����·����������Ӧ������;������Ҫͨ��stripdes�в���
int file_FILELAYER_STRIP_READER(STRIP *str)
{
	//��ȡһ��������Ϣ
	UINT64 stripid,*diskid,*deviceid,*strsetid,*chunkid,regionid;
	int i,disknum,devicenum,strsetnum,chunknum,storestate;
	//REGION *regionptr;
	STRIPDES *strdes;
	char regoinidstr[20]="",stripidstr[20]="";
	char regionidnamestr[30]="",stripidnamestr[30]="";
	char stripfilenamestr[40]="";
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	FILE *flin;
	
	strdes=talloc(STRIPDES,1);
	if(strdes==NULL)
	{
		show_error("file_FILELAYER","STRIP_READER","No memory");
		return FALSE;
	}

	glometapath=get_state_glometapath();//��ȡȫ��Ԫ����ָ��
	//Ԫ����λ��
	metapath=talloc(char,(30+30+40+1000));//1000λ��·��
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","STRIP_READER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//�����ַ���
	regionid=str->regionid;
	stripid=str->StripID;
	//��ʼ�����ļ�Ԫ����·������
	U64toSTR(regoinidstr,regionid);//��������id
	U64toSTR(stripidstr,stripid);//��������id

	file_regionstr(regionidnamestr,regoinidstr);//����region�ַ���
	file_stripstr(stripidnamestr,stripidstr);//�ϲ�strip�ļ���
	file_stripstr_name(stripfilenamestr,stripidstr);//����strip�ַ���

	//·��������һ��
	strcat(metapath,glometapath);//��Ԫ����·��ƴ����ȥ
	strcat(metapath,regionidnamestr);//��region�ַ���ƴ����ȥ
	strcat(metapath,stripidnamestr);//��strip�ַ���ƴ����ȥ
	strcat(metapath,stripfilenamestr);//strip�ļ���ƴ����ȥ
	//���ɾ��
	flin=fopen(metapath,"r+");
	if(flin==NULL)
	{
		show_error("file_FILELAYER","STRIP_READER","fptr can't create");
		return FALSE;
	}
	fscanf(flin,"strip id:%I64d\n",&stripid);
	//fprintf(flout,"strip description:\n");
	fscanf(flin,"chunknum of each stripsect:%d\n",&strdes->chunknum);
	fscanf(flin,"chunksize is:%d\n",&strdes->chunksize);
	fscanf(flin,"there are %d disks,disk id list:\n",&disknum);
	diskid=talloc(UINT64,disknum);//���ռ�
	if(diskid==NULL)
	{
		show_error("file_FILELAYER","STRIP_READER","No memory");
		return FALSE;
	}
	for(i=0;i<disknum;i++)//����des��������strip����ͬдһ����
	{
		fscanf(flin,"%I64d\n",&diskid[i]);
	}
	fscanf(flin,"there are %d devices,device id list:\n",&devicenum);
	deviceid=talloc(UINT64,devicenum);//���ռ�
	if(deviceid==NULL)
	{
		show_error("file_FILELAYER","STRIP_READER","No memory");
		return FALSE;
	}
	for(i=0;i<devicenum;i++)
	{
		fscanf(flin,"%I64d\n",&deviceid[i]);
	}
	fscanf(flin,"there are %d stripsects,stripsect id list:\n",&strsetnum);
	strsetid=talloc(UINT64,strsetnum);//���ռ�
	if(strsetid==NULL)
	{
		show_error("file_FILELAYER","STRIP_READER","No memory");
		return FALSE;
	}
	for(i=0;i<strsetnum;i++)
	{
		fscanf(flin,"%I64d\n",&strsetid[i]);
	}
	fscanf(flin,"there are %d chunks,chunk id list:\n",&chunknum);
	chunkid=talloc(UINT64,chunknum);//���ռ�
	if(chunkid==NULL)
	{
		show_error("file_FILELAYER","STRIP_READER","No memory");
		return FALSE;
	}
	for(i=0;i<chunknum;i++)
	{
		fscanf(flin,"%I64d\n",&chunkid[i]);
	}
	fscanf(flin,"region id:%I64d\n",&regionid);
	fscanf(flin,"strip state(countnum):%d\n",&storestate);
	str->StripID=stripid;

	strdes->diskid=diskid;
	strdes->disknum=disknum;
	str->strdes=strdes;

	str->disknum=disknum;
	str->diskid=diskid;

	str->devicenum=devicenum;
	str->deviceid=deviceid;

	str->strsetnum=strsetnum;
	str->stripsectid=strsetid;

	str->chunknum=chunknum;
	str->chunkid=chunkid;

	str->regionid=regionid;

	str->storestate=storestate;

	fclose(flin);
	free(metapath);//����ͷ�·����Ϣ
	return TRUE;
}

//��REGION��ȡ��Ӧ����
int file_FILELAYER_REGION_READER(REGION *reg)
{
	//��ȡһ��region����Ϣ
	UINT64 regionid;
	CODEPARA *codepara;
	UINT64 *fileid,*diskid,*deviceid,*stripid,rootfileid,totalsize,chunknum,stripsectnum;//��ͬ��ȫ��
	int i,codetype,filenum,disknum,devicenum,stripnum,storestate;
	STRIPDES *strdes;
	//CODEPARA *codepara;
	char regoinidstr[20]="";
	char regionidnamestr[30]="";
	char regionfilenamestr[40]="";
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	FILE *flin;
	codepara=talloc(CODEPARA,1);
	if(codepara==NULL)
	{
		show_error("file_FILELAYER","REGION_READER","No memory");
		return FALSE;
	}
	strdes=talloc(STRIPDES,1);
	if(strdes==NULL)
	{
		show_error("file_FILELAYER","REGION_READER","No memory");
		return FALSE;
	}
	//�����ַ
	glometapath=get_state_glometapath();//��ȡȫ��Ԫ����ָ��
	//Ԫ����λ��
	metapath=talloc(char,(30+40+1000));//1000λ��·��
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","REGION_READER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//�����ַ���
	regionid=reg->RegionID;
	//��ʼ�����ļ�Ԫ����·������
	U64toSTR(regoinidstr,regionid);//��������id

	file_regionstr(regionidnamestr,regoinidstr);//����region�ַ���
	file_regionstr_name(regionfilenamestr,regoinidstr);//�ϲ�strip�ļ���

	//·��������һ��
	strcat(metapath,glometapath);//��Ԫ����·��ƴ����ȥ
	strcat(metapath,regionidnamestr);//��region�ַ���ƴ����ȥ
	strcat(metapath,regionfilenamestr);//��region���ļ���ƴ����ȥ
	//���ļ����
	flin=fopen(metapath,"r+");
	if(flin==NULL)
	{
		show_error("file_FILELAYER","REGION_READER","fptr can't create");
		return FALSE;
	}
	//��ʼ���
	fscanf(flin,"region id:%I64d\n",&regionid);
	//��ʼ�������
	fscanf(flin,"code type(code):%d,the parameter list:\n",&codetype);
	fscanf(flin,"the galois field:%d\n",&codepara->w);
	fscanf(flin,"data disk num:%d\n",&codepara->datanum);
	fscanf(flin,"code disk num:%d\n",&codepara->codenum);
	fscanf(flin,"total disk num:%d\n",&codepara->totnum);
	fscanf(flin,"provider num:%d\n",&codepara->pronum);
	fscanf(flin,"sector number:%d\n",&codepara->sectornum);
	//�ܴ�С
	fscanf(flin,"total size of region:%I64d\n",&totalsize);
	fscanf(flin,"there are %d files,file id list:\n",&filenum);
	fileid=talloc(UINT64,filenum);//���ռ�
	if(fileid==NULL)
	{
		show_error("file_FILELAYER","REGION_READER","No memory");
		return FALSE;
	}
	for(i=0;i<filenum;i++)
	{
		fscanf(flin,"%I64d\n",&fileid[i]);
	}
	fscanf(flin,"there are %d disks,disk id list:\n",&disknum);
	diskid=talloc(UINT64,disknum);//���ռ�
	if(diskid==NULL)
	{
		show_error("file_FILELAYER","REGION_READER","No memory");
		return FALSE;
	}
	for(i=0;i<disknum;i++)
	{
		fscanf(flin,"%I64d\n",&diskid[i]);
	}
	fscanf(flin,"there are %d devices,device id list:\n",&devicenum);
	deviceid=talloc(UINT64,devicenum);//���ռ�
	if(deviceid==NULL)
	{
		show_error("file_FILELAYER","REGION_READER","No memory");
		return FALSE;
	}
	for(i=0;i<devicenum;i++)
	{
		fscanf(flin,"%I64d\n",&deviceid[i]);
	}
	fscanf(flin,"stripsect has %d chunks,each chunk is %d bytes\n",&strdes->chunknum,&strdes->chunksize);
	fscanf(flin,"there are %d strips,strip id list:\n",&stripnum);
	stripid=talloc(UINT64,stripnum);//���ռ�
	if(stripid==NULL)
	{
		show_error("file_FILELAYER","REGION_READER","No memory");
		return FALSE;
	}
	for(i=0;i<stripnum;i++)
	{
		fscanf(flin,"%I64d\n",&stripid[i]);
	}

	fscanf(flin,"total chunk number:%I64d\n",&chunknum);
	fscanf(flin,"total stripsect number:%I64d\n",&stripsectnum);

	fscanf(flin,"root file id:%I64d\n",&rootfileid);
	fscanf(flin,"region state(countnum):%d\n",&storestate);
	//��ʼ��ֵ
	reg->RegionID=regionid;
	reg->codetype=codetype;
	reg->codepara=codepara;
	reg->totalsize=totalsize;

	reg->filenum=filenum;
	reg->fileid=fileid;

	reg->disknum=disknum;
	reg->diskid=diskid;

	reg->devicenum=devicenum;
	reg->deviceid=deviceid;

	strdes->diskid=diskid;
	strdes->disknum=disknum;

	reg->strdes=strdes;
	reg->stripnum=stripnum;
	reg->stripid=stripid;

	reg->chunknum=chunknum;
	reg->stripsectnum=stripsectnum;

	reg->rootfileid=rootfileid;
	reg->storestate=storestate;

	fclose(flin);
	free(metapath);//����ͷ�·����Ϣ
	return TRUE;
}

//��DISK��ȡ����Ӧ����
int file_FILELAYER_DISK_READER(DISK *disk)
{
	//��ȡһ��disk����Ϣ
	UINT64 diskid,deviceid,volumn;
	int disktype,capability;
	UINT64 *regionid;
	int i,regionnum,storestate;
	char *diskpath;
	//DEVICE *deviceptr;
	char deviceidstr[20]="";
	char diskidstr[20]="";

	char deviceidnamestr[30]="";
	char diskfilenamestr[40]="";

	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	FILE *flin;

	diskid=disk->DiskID;
	deviceid=disk->deviceid;
	diskpath=talloc(char,1000);
	if(diskpath==NULL)
	{
		show_error("file_FILELAYER","DISK_WRITER","No memory");
		return FALSE;
	}
	//��ʼdisk��ȡ
	glometapath=get_state_glometapath();
	//metapath=glometapath;
	metapath=talloc(char,1000+30+40);
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","DISK_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';

	U64toSTR(deviceidstr,deviceid);
	U64toSTR(diskidstr,diskid);

	file_devicestr(deviceidnamestr,deviceidstr);
	file_diskstr_name(diskfilenamestr,diskidstr);

	strcat(metapath,glometapath);
	strcat(metapath,deviceidnamestr);
	strcat(metapath,diskfilenamestr);
	flin=fopen(metapath,"r+");
	if(flin==NULL)
	{
		show_error("file_FILELAYER","DISK_READER","fptr can't create");
		return FALSE;
	}
	/*
	fprintf(flout,"disk id:%I64d\n",diskid);
	fprintf(flout,"disk type(0:NORHDD,1:HIGHHD,2:SSD):%d\n",disktype);
	fprintf(flout,"disk capability(0:NONCAP,1:LOWCAP,2:MIDCAP,3:HIGHCAP):%d",capability);
	fprintf(flout,"disk volumn:%d",volumn);
	fprintf(flout,"there are %d regions,region id list:",regionnum);
	for(i=0;i<regionnum;i++)
	{
		fprintf(flout,"%I64d",regionid[i]);
	}
	fprintf(flout,"device id:%I64d",deviceid);
	fprintf(flout,"disk path:%s",diskpath);*/
	fscanf(flin,"disk id:%I64d\n",&diskid);
	fscanf(flin,"disk type(0:NORHDD,1:SSHD,2:SSD):%d\n",&disktype);
	fscanf(flin,"disk capability(0:NONCAP,1:LOWCAP,2:MIDCAP,3:HIGHCAP):%d\n",&capability);
	fscanf(flin,"disk volumn:%I64d\n",&volumn);
	fscanf(flin,"there are %d regions,region id list:\n",&regionnum);
	regionid=talloc(UINT64,regionnum);//���ռ�
	if(regionid==NULL)
	{
		show_error("file_FILELAYER","REGION_READER","No memory");
		return FALSE;
	}
	for(i=0;i<regionnum;i++)
	{
		fscanf(flin,"%I64d\n",&regionid[i]);
	}
	fscanf(flin,"device id:%I64d\n",&deviceid);
	fscanf(flin,"disk path:%s\n",diskpath);

	fscanf(flin,"disk state(countnum):%d\n",&storestate);
	disk->DiskID=diskid;
	disk->DiskTYPE=disktype;
	disk->capability=capability;
	disk->volumn=volumn;
	disk->regionnum=regionnum;
	disk->regionid=regionid;
	disk->deviceid=deviceid;
	disk->diskpath=diskpath;
	disk->storestate=storestate;
	free(metapath);
	fclose(flin);
	return TRUE;
}

//��DISK��ȡ����Ӧ����
int file_FILELAYER_DEVICE_READER(DEVICE *device)
{
	//��ȡһ��device����Ϣ
	UINT64 deviceid,*diskid,*regionid;
	int devicetype,processnum,disknum,regionnum;
	int *speed;
	int i,storestate;
	char deviceidstr[20]="";
	char deviceidnamestr[30]="";
	char devicefilenamestr[40]="";
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	FILE *flin;

	deviceid=device->DeviceID;
	//��ʼ��ȡ����
	//�����Ǵ����ļ���ȫ���Ե�,���metapath=glometapath
	glometapath=get_state_glometapath();
	metapath=talloc(char,(1000+30+40));
	//metapath=glometapath;
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","DEVICE_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';
	U64toSTR(deviceidstr,deviceid);

	file_devicestr(deviceidnamestr,deviceidstr);
	file_devicestr_name(devicefilenamestr,deviceidstr);

	strcat(metapath,glometapath);
	strcat(metapath,deviceidnamestr);
	strcat(metapath,devicefilenamestr);
	flin=fopen(metapath,"r+");
	if(flin==NULL)
	{
		show_error("file_FILELAYER","DEVICE_READER","fptr can't create");
		return FALSE;
	}
	fscanf(flin,"device id:%I64d\n",&deviceid);
	fscanf(flin,"device type(0:RACKMAC,1:PCMAC,2:NASMAC):%d\n",&devicetype);
	fscanf(flin,"there are %d processors,speed list:\n",&processnum);
	speed=talloc(int,processnum);
	if(speed==NULL)
	{
		show_error("file_FILELAYER","DEVICE_READER","No memory");
		return FALSE;
	}
	for(i=0;i<processnum;i++)
	{
		fscanf(flin,"%I64d\n",&speed[i]);
	}
	fscanf(flin,"there are %d disks,disk id list:\n",&disknum);
	diskid=talloc(UINT64,disknum);
	if(diskid==NULL)
	{
		show_error("file_FILELAYER","DEVICE_READER","No memory");
		return FALSE;
	}
	for(i=0;i<disknum;i++)
	{
		fscanf(flin,"%I64d\n",&diskid[i]);
	}
	fscanf(flin,"there are %d regions,region id list:\n",&regionnum);
	regionid=talloc(UINT64,regionnum);
	if(regionid==NULL)
	{
		show_error("file_FILELAYER","DEVICE_READER","No memory");
		return FALSE;
	}
	for(i=0;i<regionnum;i++)
	{
		fscanf(flin,"%I64d\n",&regionid[i]);
	}
	fscanf(flin,"device state(countnum):%d\n",&storestate);
	device->DeviceID=deviceid;
	device->Devicetype=devicetype;
	device->processnum=processnum;
	device->speed=speed;
	device->disknum=disknum;
	device->diskid=diskid;
	device->regionnum=regionnum;
	device->regionid=regionid;
	device->storestate=storestate;
	free(metapath);
	fclose(flin);
	return TRUE;
}

//��DEVICE��ȡ����Ӧ����
int file_FILELAYER_FILEMETA_READER(FILEMETA *fmeta)
{
	//��ȡһ��filemeta����Ϣ
	//fmeta��Ϣ
	UINT64 fileid;
	char *filename;
	int i,ACList,filetype,subfilenum;
	UINT64 filesize,userid,parentid;
	UINT64 *subfileidlist;
	struct tm *createtime,*updatetime;
	FILEINF *filechunkinf;
	char regionidstr[20]="",fileidstr[20]="";
	char regionidnamestr[30]="";
	char filemetaidnamestr[30]="";
	char filemetafilenamestr[40]="";

	//filechunkinf��Ϣ
	//FILEINF *filechunkinf;
	UINT64 *chunkid;
	CHUNKPATH *chunkpath,*curchunkpath;
	int chunknum;//chunk����

	UINT64 regionid;//���ڵ�region�ı��

	UINT64 *deviceid;//�豸id
	int devicenum;//�豸��

	UINT64 *diskid;//�洢��id�б�
	int disknum;//�洢������

	UINT64 *stripid;//����id�б�
	int stripnum;//��������

	UINT64 *stripsectid;///��������id�б�
	int stripsectnum;//������������

	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	FILE *flin;
	
	filechunkinf=talloc(FILEINF,1);
	createtime=talloc(struct tm,1);
	if(createtime==NULL)
	{
		show_error("file_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	updatetime=talloc(struct tm,1);
	if(updatetime==NULL)
	{
		show_error("file_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	filechunkinf=talloc(FILEINF,1);//����һ���ռ�
	if(filechunkinf==NULL)
	{
		show_error("file_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	filename=talloc(char,1000);
	if(filename==NULL)
	{
		show_error("file_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	
	//��ȡ��Ҫ��Ϣ
	fileid=fmeta->FileID;
	regionid=fmeta->regionid;
	glometapath=get_state_glometapath();//��ȡȫ��Ԫ����ָ��
	//��ʼ����·��
	metapath=talloc(char,1000+30+30+40);
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//�����ַ���
	//flin=fopen(metapath,"r+");
	//����·��
	U64toSTR(regionidstr,regionid);
	U64toSTR(fileidstr,fileid);
	
	//������Ӧ���ַ���
	file_regionstr(regionidnamestr,regionidstr);//����region�ַ���
	file_filemetastr(filemetaidnamestr,fileidstr);
	file_filemetastr_name(filemetafilenamestr,fileidstr);//filemeta�ļ���

	//·��������һ��
	strcat(metapath,glometapath);//��Ԫ����·��ƴ����ȥ
	strcat(metapath,regionidnamestr);//��region�ַ���ƴ����ȥ
	strcat(metapath,filemetaidnamestr);//��filemeta��ƴ����ȥ
	strcat(metapath,filemetafilenamestr);//��filename�ַ���ƴ����ȥ

	flin=fopen(metapath,"r+");//��Ԫ�������ڶ�ȡ
	if(flin==NULL)
	{
		show_error("file_FILELAYER","FILEMETA_READER","fptr can't create");
		return FALSE;
	}
	/*
	fprintf(flout,"filemeta id:%I64d\n",fileid);
	fprintf(flout,"file name:%s\n",filename);
	fprintf(flout,"file size:%d\n",filesize);
	fprintf(flout,"Access Control list:%d\n",ACList);
	fprintf(flout,"file type:%d\n",filetype);

	fprintf(flout,"user id:%I64d\n",userid);

	fprintf(flout,"parent dictionary id:%I64d\n",parentid);
	fprintf(flout,"there are %d subfile,filemeta id list:%\n",subfilenum);
	for(i=0;i<subfilenum;i++)
	{
		fprintf(flout,"%I64d\n",subfileidlist[i]);
	}
	//�����޸�ʱ��
	fprintf(flout,"create time:%d/%d/%d/%d/%d,%d/%d/%d,%d\n",
		createtime->tm_year,createtime->tm_mon,createtime->tm_yday,createtime->tm_mday,createtime->tm_wday,
		createtime->tm_hour,createtime->tm_min,createtime->tm_sec,
		createtime->tm_isdst);
	fprintf(flout,"create time:%d/%d/%d/%d/%d,%d/%d/%d,%d\n",
		updatetime->tm_year,updatetime->tm_mon,updatetime->tm_yday,updatetime->tm_mday,updatetime->tm_wday,
		updatetime->tm_hour,updatetime->tm_min,updatetime->tm_sec,
		updatetime->tm_isdst);
	*/
	fscanf(flin,"filemeta id:%I64d\n",&fileid);
	fscanf(flin,"file name:%s\n",filename);
	fscanf(flin,"file size:%I64d\n",&filesize);
	fscanf(flin,"Access Control list:%d\n",&ACList);
	fscanf(flin,"file type:%d\n",&filetype);
	
	fscanf(flin,"user id:%I64d\n",&userid);

	fscanf(flin,"parent dictionary id:%I64d\n",&parentid);

	fscanf(flin,"there are %d subfile,filemeta id list:\n",&subfilenum);

	if(subfilenum==0)
	{
		subfileidlist=NULL;
		fmeta->subfilelist=NULL;
	}
	else
	{
		subfileidlist=talloc(UINT64,subfilenum);
		if(subfileidlist==NULL)
		{
			show_error("file_FILELAYER","FILEMETA_READER","No memory");
			return FALSE;
		}
		for(i=0;i<subfilenum;i++)
		{
			fscanf(flin,"%I64d\n",&subfileidlist[i]);
		}
	}
	//�����޸�ʱ��
	fscanf(flin,"create time:%d/%d/%d/%d/%d,%d/%d/%d,%d\n",
		&createtime->tm_year,&createtime->tm_mon,&createtime->tm_yday,&createtime->tm_mday,&createtime->tm_wday,
		&createtime->tm_hour,&createtime->tm_min,&createtime->tm_sec,
		&createtime->tm_isdst);
	fscanf(flin,"update time:%d/%d/%d/%d/%d,%d/%d/%d,%d\n",
		&updatetime->tm_year,&updatetime->tm_mon,&updatetime->tm_yday,&updatetime->tm_mday,&updatetime->tm_wday,
		&updatetime->tm_hour,&updatetime->tm_min,&updatetime->tm_sec,
		&updatetime->tm_isdst);
	/*
	fprintf(flout,"there are %d chunks,chunk id list:\n",chunknum);
	for(i=0;i<chunknum;i++)
	{
		fprintf(flout,"%I64d\n",chunkid[i]);
		for(i=0;i<chunknum;i++)
		{
			fprintf(flout,"%I64d\n",chunkid[i]);
			//����ͬʱҲ���chunkpath
			fprintf(flout,"chunk id:%I64d,chunk array id:%d",chunkpath->chunkid,chunkpath->chunkarrayid);
			fprintf(flout,"stripsect id:%I64d,stripsect array id:%d",chunkpath->stripsectid,chunkpath->stripsectarrayid);
			fprintf(flout,"strip id:%I64d,strip array id:%d",chunkpath->stripid,chunkpath->striparrayid);
			fprintf(flout,"region id:%I64d,region array id:%d",chunkpath->regionid,chunkpath->regionarrayid);
		}
	}
	fprintf(flout,"region id:%I64d\n",regionid);
	fprintf(flout,"there are %d devices,device id list:\n",devicenum);
	for(i=0;i<devicenum;i++)
	{
		fprintf(flout,"%I64d\n",deviceid[i]);
	}
	fprintf(flout,"there are %d disks,disk id list:\n",disknum);
	for(i=0;i<disknum;i++)
	{ 
		fprintf(flout,"%I64d\n",diskid[i]);
	}
	fprintf(flout,"there are % strips,strip id list:\n",stripnum);
	for(i=0;i<stripnum;i++)
	{
		fprintf(flout,"%I64d\n",stripid);//����id�б�
	}
	fprintf(flout,"there are % stripsects,stripsect id list:\n",stripsectnum);
	for(i=0;i<stripsectnum;i++)
	{
		fprintf(flout,"%I64d\n",stripsectid[i]);
	}
	*/
	//filechunkinf
	fscanf(flin,"storage information,there are %d chunks,chunk id list:\n",&chunknum);
	if(chunknum==0)
	{
		//�����ڴ洢����ֱ�ӷ��ؼ���
		fmeta->FileID=fileid;
	
		fmeta->filename=filename;
		fmeta->filesize=filesize;
		fmeta->ACList=ACList;
		fmeta->filetype=filetype;

		fmeta->userid=userid;
	
		fmeta->parentid=parentid;

		fmeta->subfilenum=subfilenum;
		fmeta->subfileidlist=subfileidlist;

		fmeta->createtime=createtime;
		fmeta->updatetime=updatetime;
		//filechunkinf
		free(filechunkinf);
		filechunkinf=NULL;//ֱ��д��û��
		fmeta->filechunkinf=filechunkinf;//�����һ����ֵ��ȥ
		free(metapath);
		fclose(flin);//�ͷŲ���Ҫ��ָ��
		return TRUE;
	}
	chunkid=talloc(UINT64,chunknum);
	if(chunkid==NULL)
	{
		show_error("file_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	chunkpath=talloc(CHUNKPATH,chunknum);
	if(chunkpath==NULL)
	{
		show_error("file_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	curchunkpath=chunkpath;
	for(i=0;i<chunknum;i++)
	{
		fscanf(flin,"%I64d\n",&chunkid[i]);
		//����ͬʱҲ��ȡchunkpath
		fscanf(flin,"chunk id:%I64d,chunk array id:%d;",&curchunkpath->chunkid,&curchunkpath->chunkarrayid);
		fscanf(flin,"stripsect id:%I64d,stripsect array id:%d;",&curchunkpath->stripsectid,&curchunkpath->stripsectarrayid);
		fscanf(flin,"strip id:%I64d,strip array id:%d;",&curchunkpath->stripid,&curchunkpath->striparrayid);
		fscanf(flin,"region id:%I64d,region array id:%d\n",&curchunkpath->regionid,&curchunkpath->regionarrayid);
		curchunkpath++;
	}

	fscanf(flin,"region id:%I64d\n",&regionid);

	fscanf(flin,"there are %d devices,device id list:\n",&devicenum);
	deviceid=talloc(UINT64,devicenum);
	if(deviceid==NULL)
	{
		show_error("file_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	for(i=0;i<devicenum;i++)
	{
		fscanf(flin,"%I64d\n",&deviceid[i]);
	}
	fscanf(flin,"there are %d disks,disk id list:\n",&disknum);
	diskid=talloc(UINT64,disknum);
	if(diskid==NULL)
	{
		show_error("file_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	for(i=0;i<disknum;i++)
	{ 
		fscanf(flin,"%I64d\n",&diskid[i]);
	}
	fscanf(flin,"there are %d strips,strip id list:\n",&stripnum);
	stripid=talloc(UINT64,stripnum);
	if(stripid==NULL)
	{
		show_error("file_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	for(i=0;i<stripnum;i++)
	{
		fscanf(flin,"%I64d\n",&stripid[i]);//����id�б�
	}
	fscanf(flin,"there are %d stripsects,stripsect id list:\n",&stripsectnum);
	stripsectid=talloc(UINT64,stripsectnum);
	if(stripsectid==NULL)
	{
		show_error("file_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	for(i=0;i<stripsectnum;i++)
	{
		fscanf(flin,"%I64d\n",&stripsectid[i]);
	}
	fmeta->FileID=fileid;
	
	fmeta->filename=filename;
	fmeta->filesize=filesize;
	fmeta->ACList=ACList;
	fmeta->filetype=filetype;

	fmeta->userid=userid;
	
	fmeta->parentid=parentid;

	fmeta->subfilenum=subfilenum;
	fmeta->subfileidlist=subfileidlist;

	fmeta->createtime=createtime;
	fmeta->updatetime=updatetime;
	//filechunkinf
	filechunkinf->chunknum=chunknum;
	filechunkinf->chunkid=chunkid;
	filechunkinf->chkpath=chunkpath;

	filechunkinf->regionid=regionid;

	filechunkinf->devicenum=devicenum;
	filechunkinf->deviceid=deviceid;

	filechunkinf->disknum=disknum;
	filechunkinf->diskid=diskid;

	filechunkinf->stripnum=stripnum;
	filechunkinf->stripid=stripid;

	filechunkinf->stripsectnum=stripsectnum;
	filechunkinf->stripsectid=stripsectid;

	fmeta->filechunkinf=filechunkinf;//�����һ����ֵ��ȥ
	free(metapath);
	fclose(flin);//�ͷŲ���Ҫ��ָ��
	return TRUE;
}

//��USERPROFILE��ȡ����Ӧ����
int file_FILELAYER_USERPROFILE_READER(USERPROFILE *pfile)
{
	UINT64 userid,DICid;
	char *username,*password,*DICpath;
	//USERLOCATION *userlocinf;
	int userprivil;
	struct tm *createtime;
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	USERLOCATION *userlocinf;
	FILE *flin;
	char userprofileidstr[20]="";
	char userprofileidnamestr[40]="";
	char userprofilefilenamestr[50]="";

	userid=pfile->UserID;

	username=talloc(char,1000);
	if(username==NULL)
	{
		show_error("file_FILELAYER","USERPROFILE_READER","No memory");
		return FALSE;
	}
	password=talloc(char,1000);
	if(password==NULL)
	{
		show_error("file_FILELAYER","USERPROFILE_READER","No memory");
		return FALSE;
	}
	DICpath=talloc(char,1000);
	if(DICpath==NULL)
	{
		show_error("file_FILELAYER","USERPROFILE_READER","No memory");
		return FALSE;
	}
	userlocinf=talloc(USERLOCATION,1);
	if(userlocinf==NULL)
	{
		show_error("file_FILELAYER","USERPROFILE_READER","No memory");
		return FALSE;
	}
	createtime=talloc(struct tm,1);
	if(createtime==NULL)
	{
		show_error("file_FILELAYER","USERPROFILE_READER","No memory");
		return FALSE;
	}
	//��ȡȫ��Ԫ����
	glometapath=get_state_glometapath();
	//metapath=glometapath;
	metapath=talloc(char,1000+40+50);
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","USERPROFILE_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';
	U64toSTR(userprofileidstr,userid);

	file_userprofilestr(userprofileidnamestr,userprofileidstr);
	file_userprofilestr_name(userprofilefilenamestr,userprofileidstr);

	strcat(metapath,glometapath);
	strcat(metapath,userprofileidnamestr);
	strcat(metapath,userprofilefilenamestr);
	flin=fopen(metapath,"r+");
	if(flin==NULL)
	{
		show_error("file_FILELAYER","USERPROFILE_READER","fptr can't create");
		return FALSE;
	}
	/*printf(flout,"user id:%I64d\n",userid);
	fprintf(flout,"username:%s\n",username);
	fprintf(flout,"password:%s\n",password);
	fprintf(flout,"user dictionary id:%I64d\n",DICid);
	fprintf(flout,"user dictionary path:%s\n",DICpath);
	fprintf(flout,"user privilege:%d\n",userprivil);
	//int tm_sec;     /* seconds after the minute - [0,59] */
    //   int tm_min;     /* minutes after the hour - [0,59] */
    //    int tm_hour;    /* hours since midnight - [0,23] */
    //    int tm_mday;    /* day of the month - [1,31] */
    //    int tm_mon;     /* months since January - [0,11] */
    //    int tm_year;    /* years since 1900 */
    //    int tm_wday;    /* days since Sunday - [0,6] */
    //    int tm_yday;    /* days since January 1 - [0,365] */
    //    int tm_isdst;   /* daylight savings time flag */
	/*fprintf(flout,"create time:%d/%d/%d/%d/%d,%d/%d/%d,%d",
		createtime->tm_year,createtime->tm_mon,createtime->tm_yday,createtime->tm_mday,createtime->tm_wday,
		createtime->tm_hour,createtime->tm_min,createtime->tm_sec,
		createtime->tm_isdst);*/
	fscanf(flin,"user id:%I64d\n",&userid);
	fscanf(flin,"username:%s\n",username);
	fscanf(flin,"password:%s\n",password);
	fscanf(flin,"user dictionary id:%I64d\n",&DICid);
	fscanf(flin,"user dictionary path:%s\n",DICpath);
	fscanf(flin,"user privilege:%d\n",&userprivil);
	fscanf(flin,"create time:%d/%d/%d/%d/%d,%d/%d/%d,%d\n",
		&createtime->tm_year,&createtime->tm_mon,&createtime->tm_yday,&createtime->tm_mday,&createtime->tm_wday,
		&createtime->tm_hour,&createtime->tm_min,&createtime->tm_sec,
		&createtime->tm_isdst);
	pfile->UserID=userid;
	pfile->username=username;
	pfile->password=password;
	userlocinf->DICid=DICid;
	userlocinf->DICpath=DICpath;
	pfile->userlocinf=userlocinf;
	pfile->userprivil=userprivil;
	pfile->createtime=createtime;
	free(metapath);
	fclose(flin);
	return TRUE;
}
//����ȫ���ļ�ֻ��һ������group����
//���û���Ϣ��ȡ����Ӧ����
int file_FILELAYER_GLOSYSTEMID_READER(GLOSYSTEMID *glosysid)
{
	UINT64 *regionidlist,*useridlist,*deviceidlist,*diskidlist,glomaxbuffersize;
	int i,regionnum,usernum,devicenum,disknum;

	IDITEM *systemnextid;
	//UINT64 chunkidlist;
	int *availkind;//�ִ��������
	int availnum,glopushtime;//������������

	char glofilename[40]="";
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	FILE *flin;
	//��ȡԪ���ݵ�ַ
	glometapath=get_state_glometapath();
	metapath=talloc(char,(1000+40));
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","USERPROFILE_READER","No memory");
		return FALSE;
	}
	metapath[0]='\0';

	file_globaldeine_name(glofilename);

	strcat(metapath,glometapath);
	strcat(metapath,glofilename);
	flin=fopen(metapath,"r+");
	if(flin==NULL)
	{
		show_error("file_FILELAYER","GLOSYSTEMID_READER","fptr can't create");
		return FALSE;
	}
	/*fprintf(flout,"there are %d regions,region id list:\n",regionnum);
	for(i=0;i<regionnum;i++)
	{
		fprintf(flout,"%I64d\n",regionidlist[i]);
	}
	fprintf(flout,"there are %d users,user id list:\n",usernum);
	for(i=0;i<usernum;i++)
	{
		fprintf(flout,"%I64d\n",useridlist[i]);
	}
	fprintf(flout,"there are %d devices,device id list:\n",devicenum);
	for(i=0;i<devicenum;i++)
	{
		fprintf(flout,"%I64d\n",deviceidlist[i]);
	}
	fprintf(flout,"there are %d disks,disk id list:\n",disknum);
	for(i=0;i<disknum;i++)
	{
		fprintf(flout,"%I64d\n",diskidlist[i]);
	}*/
	fscanf(flin,"there are %d regions,region id list:\n",&regionnum);
	regionidlist=talloc(UINT64,regionnum);
	if(regionidlist==NULL)
	{
		show_error("file_FILELAYE","GLOSYSTEMID_READER","No memory");
		return FALSE;
	}
	for(i=0;i<regionnum;i++)
	{
		fscanf(flin,"%I64d\n",&regionidlist[i]);
	}
	fscanf(flin,"there are %d users,user id list:\n",&usernum);
	useridlist=talloc(UINT64,usernum);
	if(useridlist==NULL)
	{
		show_error("file_FILELAYE","GLOSYSTEMID_READER","No memory");
		return FALSE;
	}
	for(i=0;i<usernum;i++)
	{
		fscanf(flin,"%I64d\n",&useridlist[i]);
	}
	fscanf(flin,"there are %d devices,device id list:\n",&devicenum);
	deviceidlist=talloc(UINT64,devicenum);
	if(deviceidlist==NULL)
	{
		show_error("file_FILELAYE","GLOSYSTEMID_READER","No memory");
		return FALSE;
	}
	if(deviceidlist==NULL)
	{
		show_error("file_FILELAYE","GLOSYSTEMID_READER","No memory");
		return FALSE;
	}
	for(i=0;i<devicenum;i++)
	{
		fscanf(flin,"%I64d\n",&deviceidlist[i]);
	}
	fscanf(flin,"there are %d disks,disk id list:\n",&disknum);
	diskidlist=talloc(UINT64,disknum);
	if(diskidlist==NULL)
	{
		show_error("file_FILELAYE","GLOSYSTEMID_READER","No memory");
		return FALSE;
	}
	for(i=0;i<disknum;i++)
	{
		fscanf(flin,"%I64d\n",&diskidlist[i]);
	}
	//�����ǰid��
	//systemnextid=glosysid->systemnextid;
	systemnextid=talloc(IDITEM,1);
	if(systemnextid==NULL)
	{
		show_error("file_FILELAYE","GLOSYSTEMID_READER","No memory");
		return FALSE;
	}
	/*
		fprintf(flout,"next step region id:%I64d,strip id:%I64d,stripsect id:%I64d,chunk id:%I64d\n",
		systemnextid->gloregionid,systemnextid->glostripid,systemnextid->glostripsectid,systemnextid->glochunkid);
	fprintf(flout,"device id:%I64d,disk id:%I64d,file id:%I64d,user id:%I64d\n",
		systemnextid->glodeviceid,systemnextid->glodiskid,systemnextid->glofileid,systemnextid->glouserid);
		fscanf(flin,"next step region id:%I64d,strip id:%I64d,stripsect id:%I64d,chunk id:%d,device id:%I64d,disk id:%I64d,file id:%I64d,user id:%I64d\n",
		&systemnextid->gloregionid,&systemnextid->glostripid,&systemnextid->glostripsectid,&systemnextid->glochunkid,
		&systemnextid->glodeviceid,&systemnextid->glodiskid,
		&systemnextid->glofileid,&systemnextid->glouserid);
	*/
	fscanf(flin,"next step region id:%I64d,strip id:%I64d,stripsect id:%I64d,chunk id:%I64d\n",
		&systemnextid->gloregionid,&systemnextid->glostripid,&systemnextid->glostripsectid,&systemnextid->glochunkid);
	fscanf(flin,"device id:%I64d,disk id:%I64d,file id:%I64d,user id:%I64d\n",
		&systemnextid->glodeviceid,&systemnextid->glodiskid,&systemnextid->glofileid,&systemnextid->glouserid);
	//��������
	//availnum=get_state_avail_kind_number();
	//availkind=get_state_avail_kind();
	fscanf(flin,"there are %d kinds code,the id list of code:\n",&availnum);
	availkind=talloc(int,availnum);
	if(availkind==NULL)
	{
		show_error("file_FILELAYE","GLOSYSTEMID_READER","No memory");
		return FALSE;
	}
	for(i=0;i<availnum;i++)
	{
		fscanf(flin,"%d\n",&availkind[i]);
	}

	//���pushʱ��
	//glopushtime=get_state_buffer_push_time();
	fscanf(flin,"the push time of system is %d time uints\n",&glopushtime);
	fscanf(flin,"the push maximum buffer size is %I64d BYTE\n",&glomaxbuffersize);
	//��ʼ��ֵ
	glosysid->regionid=regionidlist;
	glosysid->regionnum=regionnum;

	glosysid->userid=useridlist;
	glosysid->usernum=usernum;

	glosysid->deviceid=deviceidlist;
	glosysid->devicenum=devicenum;

	glosysid->diskid=diskidlist;
	glosysid->disknum=disknum;

	glosysid->systemnextid=systemnextid;

	glosysid->availkind=availkind;
	glosysid->availnum=availnum;

	glosysid->glopushtime=glopushtime;
	glosysid->glomaxbuffersize=glomaxbuffersize;
	free(metapath);
	fclose(flin);
	return TRUE;
}

//����ȡ
//��CHUNKGROUP�������а�����·����ȡ����Ӧ������,Ԫ���ݲ���
int file_FILELAYER_CHUNKGROUP_READER_META(CHUNKGROUP *chkgroup)
{
	int i,groupsize,resTF;
	CHUNK *chunkptr;
	chunkptr=chkgroup->ckgroup;
	groupsize=chkgroup->groupsize;
	for(i=0;i<groupsize;i++)
	{
		resTF=file_FILELAYER_CHUNK_READER_META(chunkptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","CHUNKGROUP_READER","chunk reader failed");
			return FALSE;
		}
		chunkptr++;
	}
	
	return TRUE;
}
//��CHUNKGROUP�������а�����·����ȡ����Ӧ������,���ݲ���
int file_FILELAYER_CHUNKGROUP_READER_DATA(CHUNKGROUP *chkgroup)
{
	int i,groupsize,resTF;
	CHUNK *chunkptr;
	chunkptr=chkgroup->ckgroup;
	groupsize=chkgroup->groupsize;
	for(i=0;i<groupsize;i++)
	{
		resTF=file_FILELAYER_CHUNK_READER_DATA(chunkptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","CHUNKGROUP_READER","chunk reader failed");
			return FALSE;
		}
		chunkptr++;
	}
	return TRUE;
}
//��STRIPSECTGROUP�������а�����·����ȡ����Ӧ������
int file_FILELAYER_STRIPSECTGROUP_READER(STRIPSECTGROUP *strsetgroup)
{
	int i,groupsize,resTF;
	STRIPSECT *strsetptr;
	strsetptr=strsetgroup->stripsectgroup;
	groupsize=strsetgroup->groupsize;
	for(i=0;i<groupsize;i++)
	{
		resTF=file_FILELAYER_STRIPSECT_READER(strsetptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","STRIPSECTGROUP_READER","stripsect reader failed");
			return FALSE;
		}
		strsetptr++;
	}
	return TRUE;
}
//��STRIPGROUP�������а�����·����ȡ����Ӧ������;������Ҫͨ��stripdes�в���
int file_FILELAYER_STRIPGROUP_READER(STRIPGROUP *strgroup)
{
	int i,groupsize,resTF;
	STRIP *stripptr;
	stripptr=strgroup->stripgroup;
	groupsize=strgroup->groupsize;
	for(i=0;i<groupsize;i++)
	{
		resTF=file_FILELAYER_STRIP_READER(stripptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","STRIPGROUP_READER","strip reader failed");
			return FALSE;
		}
		stripptr++;
	}
	return TRUE;
}
//��REGIONGROUP��ȡ����Ӧλ��
int file_FILELAYER_REGIONGROUP_READER(REGIONGROUP *reggroup)
{
	int i,groupsize,resTF;
	REGION *regionptr;
	regionptr=reggroup->regiongroup;
	groupsize=reggroup->groupsize;
	for(i=0;i<groupsize;i++)
	{
		resTF=file_FILELAYER_REGION_READER(regionptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","REGIONGROUP_READER","region reader failed");
			return FALSE;
		}
		regionptr++;
	}
	return TRUE;
}
//��DISKGROUP��ȡ����Ӧλ��
int file_FILELAYER_DISKGROUP_READER(DISKGROUP *diskgroup)
{
	int i,groupsize,resTF;
	DISK *diskptr;
	diskptr=diskgroup->diskgroup;
	groupsize=diskgroup->groupsize;
	for(i=0;i<groupsize;i++)
	{
		resTF=file_FILELAYER_DISK_READER(diskptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","DISKGROUP_READER","disk reader failed");
			return FALSE;
		}
		diskptr++;
	}
	return TRUE;
}
//��DEVICEGROUP��ȡ����Ӧλ��
int file_FILELAYER_DEVICEGROUP_READER(DEVICEGROUP *devicegroup)
{
	int i,groupsize,resTF;
	DEVICE *deviceptr;
	deviceptr=devicegroup->devicegroup;
	groupsize=devicegroup->groupsize;
	for(i=0;i<groupsize;i++)
	{
		resTF=file_FILELAYER_DEVICE_READER(deviceptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","DEVICEGROUP_READER","device reader failed");
			return FALSE;
		}
		deviceptr++;
	}
	return TRUE;
}
//��FILEMETAGROUP��ȡ����Ӧλ��
int file_FILELAYER_FILEMETAGROUP_READER(FILEMETAGROUP *fmetagroup)
{
	int i,groupsize,resTF;
	FILEMETA *fileptr;
	fileptr=fmetagroup->filemetagroup;
	groupsize=fmetagroup->grouposize;
	for(i=0;i<groupsize;i++)
	{
		resTF=file_FILELAYER_FILEMETA_READER(fileptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","FILEMETAGROUP_READER","filemeta reader failed");
			return FALSE;
		}
		fileptr++;
	}
	return TRUE;
}
//��USERPROFILEGROUP��ȡ��Ӧ����
int file_FILELAYER_USERPROFILEGROUP_READER(USERGROUP *ugroup)
{
	int i,groupsize,resTF;
	USERPROFILE *userproptr;
	userproptr=ugroup->userlist;
	groupsize=ugroup->groupsize;
	for(i=0;i<groupsize;i++)
	{
		resTF=file_FILELAYER_USERPROFILE_READER(userproptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","USERPROFILEGROUP_READER","userprofile reader failed");
			return FALSE;
		}
		userproptr++;
	}
	return TRUE;
}



//����д����,д�����
//��CHUNK�������а�����·��д�뵽��Ӧ������
int file_FILELAYER_CHUNK_WRITER_META(CHUNK *chk)
{
	/*	
	UINT64 ChunkID;//����

	int isparity;//�Ƿ���У���
	struct CHUNKPATH *chkpath;//chunk·��

	int sizenum;//�ֽ���
	BYTE* chunkcontent;//��Ҫԭ����chunk�Ĵ�С����byteΪ��λ

	UINT64 regionid;//���ڵ�region���
	struct REGION *regionptr;//��һ��region��ָ��

	UINT64 stripid;//����id��
	struct STRIP *stripptr;//��һ��strip��ָ��

	UINT64 stripsectid;//��������id��
	struct STRIPSECT *stripsectptr;//��һ��stripsect��ָ��

	UINT64 diskid;//���ڴ��̵�ID
	struct DISK *diskptr;//��һ��disk��ָ��

	UINT64 deviceid;//�����豸��ID
	struct DEVICE *deviceptr;//��һ��device��ָ��

	UINT64 fileid;//�ļ����
	struct FILEMETA *fmeta;//�ļ�Ԫ����

	int storestate;//��ǰ��洢״̬
	*/
	UINT64 chkid;//chunk���
	CHUNKPATH *chkpath;//·��
	UINT64 regionid,stripid,stripsectid,deviceid,diskid,fileid;//id��ȫ
	int resTF,isparity,sizenum,storestate;
	REGION *regionptr;//����ָ��
	STRIP *stripptr;//����ָ��
	STRIPSECT *strsetptr;//������Ƭָ��
	char regoinidstr[20]="",stripidstr[20]="",strsetidstr[20]="",chkidstr[20]="";//id���ַ�������
	char regionnamestr[30]="",stripidnamestr[30]="",strsetidnamestr[30]="",chkfilenamestr[40]="";//��ǰ������Ƭ
	char *glometapath;// ����ȫ��
	char *metapath;
	FILE *flout;
	//��ȡָ��
	chkpath=chk->chkpath;
	regionptr=chkpath->regionptr;
	stripptr=chkpath->stripptr;
	strsetptr=chkpath->stripsectptr;
	//��ʼ���а�ȫ���
	if(regionptr==NULL)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","region point is not exist");
		return FALSE;
	}
	if(stripptr==NULL)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","strip point is not exist");
		return FALSE;
	}
	if(strsetptr==NULL)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","stripsect point is not exist");
		return FALSE;
	}
	//��ʼ���д洢״̬���
	/*if(regionptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","region state is empty");
		return FALSE;
	}
	if(stripptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","strip state is empty");
		return FALSE;
	}
	if(strsetptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","strip state is empty");
		return FALSE;
	}*/
	//��ʼ��ֵ
	chkid=chk->ChunkID;
	sizenum=chk->sizenum;
	regionid=chk->regionid;
	stripid=chk->stripid;
	stripsectid=chk->stripsectid;
	deviceid=chk->deviceid;
	diskid=chk->diskid;
	fileid=chk->fileid;
	regionid=chk->regionid;
	isparity=chk->isparity;
	storestate=chk->storestate;
	//��ǰ����д��Ԫ����
	//����Ԫ����λ��
	glometapath=get_state_glometapath();//��ȡȫ��Ԫ����ָ��
	metapath=talloc(char,(30+30+30+40+1000));//1000λ��·��
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//�����ַ���
	U64toSTR(regoinidstr,regionid);//��������id
	U64toSTR(stripidstr,stripid);//��������id
	U64toSTR(strsetidstr,stripsectid);//������������id
	U64toSTR(chkidstr,chkid);//������������id

	file_regionstr(regionnamestr,regoinidstr);//����region�ַ���
	file_stripstr(stripidnamestr,stripidstr);//����strip�ַ���
	file_stripsectstr(strsetidnamestr,strsetidstr);//����stripsect�ַ���
	file_chunkstr_name(chkfilenamestr,chkidstr);//����

	//·��������һ��
	strcat(metapath,glometapath);//��Ԫ����·��ƴ����ȥ
	strcat(metapath,regionnamestr);//��region�ַ���ƴ����ȥ
	strcat(metapath,stripidnamestr);//��strip�ַ���ƴ����ȥ
	strcat(metapath,strsetidnamestr);//��stripsect�ַ���ƴ����ȥ
	strcat(metapath,chkfilenamestr);//��stripsect�ַ���ƴ����ȥ
	resTF=file_FILELAYER_dictionary_stripsect_exists(regionid,stripid,stripsectid);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","dictionary can't create");
		return FALSE;
	}
	flout=fopen(metapath,"w+");//��Ԫ��������д��
	if(flout==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","fptr can't create");
		return FALSE;
	}
	/*	
	UINT64 ChunkID;//����

	int isparity;//�Ƿ���У���
	struct CHUNKPATH *chkpath;//chunk·��

	int sizenum;//�ֽ���
	BYTE* chunkcontent;//��Ҫԭ����chunk�Ĵ�С����byteΪ��λ

	UINT64 regionid;//���ڵ�region���
	struct REGION *regionptr;//��һ��region��ָ��

	UINT64 stripid;//����id��
	struct STRIP *stripptr;//��һ��strip��ָ��

	UINT64 stripsectid;//��������id��
	struct STRIPSECT *stripsectptr;//��һ��stripsect��ָ��

	UINT64 diskid;//���ڴ��̵�ID
	struct DISK *diskptr;//��һ��disk��ָ��

	UINT64 deviceid;//�����豸��ID
	struct DEVICE *deviceptr;//��һ��device��ָ��

	UINT64 fileid;//�ļ����
	struct FILEMETA *fmeta;//�ļ�Ԫ����

	int storestate;//��ǰ��洢״̬
	*/
	fprintf(flout,"chunk id:%I64d\n",chkid);
	fprintf(flout,"the chunk is parity(0:FALSE,>0:TRUE):%d\n",isparity);
	//·�����Բ������
	fprintf(flout,"the chunk size:%d\n",sizenum);
	fprintf(flout,"region id:%I64d\n",regionid);
	fprintf(flout,"strip id:%I64d\n",stripid);
	fprintf(flout,"stripsect id:%I64d\n",stripsectid);
	fprintf(flout,"disk id:%I64d\n",diskid);
	fprintf(flout,"device id:%I64d\n",deviceid);
	fprintf(flout,"file id:%I64d\n",fileid);
	//��ǰ�洢״̬
	fprintf(flout,"chunk state(countnum):%d\n",storestate);
	free(metapath);
	fclose(flout);
	return TRUE;
}
int file_FILELAYER_CHUNK_WRITER_DATA(CHUNK *chk)
{
	CHUNKPATH *chkpath;//���ڼ�¼��ǰchunk��·��
	UINT64 chkid;//�û����ҵ�ǰ�ڿ����ļ��е�ƫ����
	char *strsetpath;//stripsect���ļ�ϵͳ�е�·��
	int resTF;//stripsect�еڼ������Լ���Ӧ��ƫ����
	long offset;//ƫ����
	REGION *regionptr;//��ǰchunk����regionָ��
	STRIP *stripptr;//��ǰchunk����stripָ��
	STRIPSECT *strsetptr;//��ǰCHUNK����������
	int i,chkindex,chunksize;//ÿһ��chunk�Ĵ�С
	BYTESTREAM chkcontent; //chunkд������
	int chunknum;//��ǰstripsect�е�chunk��
	UINT64 *chkidlist;//��ǰchunk����б�
	UINT64 currentid;
	//��ȡ����
	chkid=chk->ChunkID;//�ҵ�CHUNK���
	chkpath=chk->chkpath;//�Ƚ�chunk·��ȡ��
	chkcontent.BYTEcontent=chk->chunkcontent;//chunk����
	chkcontent.bytessize=chk->sizenum;//�м���Ϣ����
	//��Ҫд������ݴ�
	regionptr=chkpath->regionptr;
	stripptr=chkpath->stripptr;
	strsetptr=chkpath->stripsectptr;
	//��ʼ���а�ȫ���
	if(regionptr==NULL)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","region point is not exist");
		return FALSE;
	}
	if(stripptr==NULL)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","strip point is not exist");
		return FALSE;
	}
	if(strsetptr==NULL)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","stripsect point is not exist");
		return FALSE;
	}
	//��ʼ���д洢״̬���
	/*if(regionptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","region state is empty");
		return FALSE;
	}
	if(stripptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","strip state is empty");
		return FALSE;
	}
	if(strsetptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","strip state is empty");
		return FALSE;
	}*/
	if(chk->storestate==EMPTY)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","chunk state is empty");
		return FALSE;
	}
	strsetpath=strsetptr->filepath;//��ȡstripsect���ļ��洢·��
	chunknum=strsetptr->chunknum;//��ȡchunk��
	chkidlist=strsetptr->chunkid;//��ȡchunkid
	chunksize=chk->sizenum;//��ǰchunk�ֽ���
	chkindex=chkpath->chunkarrayid;//��Ϊ��0��ʼ
	/*for(i=0;i<chunknum;i++)
	{
		currentid=chkidlist[i];//��ȡ��ǰid
		if(currentid==chkid)
		{
			break;//����
		}
		chkindex++;//chkindex�ۼ�
	}*/
	if(chkindex==chunknum)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","chunk id can't find out");
		return FALSE;
	}
	//��ʼ����ƫ����
	offset=chkindex*chunksize;
	resTF=file_FILELAYER_BYTE_WRITER(strsetpath,&chkcontent,offset);//׼�����д��
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","can't write chunk content");
		return FALSE;
	}
	return TRUE;
}
int file_FILELAYER_STRIPSECT_CREATE(STRIPSECT *strset)
{
	UINT64 regionid,stripid,strsetid;//����ʵ��ı��
	BYTESTREAM bstream;//byte��
	REGION *regionptr;//����ָ��
	STRIP *stripptr;//����ָ��
	char *pathstr;//��ǰstripsect��·��
	int chunknum,chunksize,strsetsize;//���ڼ���strset��С
	//��ʼ��ֵ
	strsetid=strset->StripsectID;
	regionid=strset->regionid;
	regionptr=strset->regionptr;
	stripid=strset->stripid;
	stripptr=strset->stripptr;
	//����stripsect��С
	chunknum=strset->chunknum;
	chunksize=strset->chunksize;
	strsetsize=chunknum*chunksize;
	//��ȫ�Լ��
	if(regionptr==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_CREATE","region point is not exist");
		return FALSE;
	}
	if(stripptr==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_CREATE","strip point is not exist");
		return FALSE;
	}/*
	if(regionptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","STRIPSECT_CREATE","region state is empty");
		return FALSE;
	}
	if(stripptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","STRIPSECT_CREATE","strip state is empty");
		return FALSE;
	}*/
	//��ȡ·��
	pathstr=strset->filepath;
	//�����ļ���С
	bstream.BYTEcontent=NULL;
	bstream.bytessize=strsetsize;
	//��ʼ������Ӧ���ļ���
	file_FILELAYER_BYTE_CREATE(pathstr,&bstream);
	return TRUE;
}
//��STRIPSECT�������а�����·��д�뵽��Ӧ������
int file_FILELAYER_STRIPSECT_WRITER(STRIPSECT *strset)
{
	//������Ҫ��ȡԪ���ݼ���
	int i,chunksize;
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	//UINT64 regionid,stripid,strsectid;//����ʵ��ı��
	UINT64 strsetid;//strset�ı��
	REGION *regionptr;//����ָ��
	STRIP *stripptr;//����ָ��
	char regoinidstr[20]="",stripidstr[20]="",strsetidstr[20]="";//����Ϊ20λ��ԭ����2^64�η�1.8*19^19
	char regionnamestr[30]="",stripidnamestr[30]="",stripsectnamestr[30]="",strsetfilename[40]="";//����Ϊ30λstripset+/��10���ַ�
	/*
	UINT64 StripsectID;//STRIPSECT��id

	UINT64 *chunkid;//	���а�����chunkid
	CHUNKGROUP *chunklist;//����һ��chunkgroup�þ߼�¼chunk��,��Ϊһ��chunkָ��
	int chunksize;//chunk��С
	int chunknum;//������chunk��������

	UINT64 regionid;///���ڵ�region���
	struct REGION *regionptr;//��һ��regionָ��

	UINT64 stripid;//���ڵ�strip���
	struct STRIP *stripptr;//��һ��stripָ��

	UINT64 diskid;//���ڵ�disk���
	struct DISK *diskptr;//��һ��diskָ��

	UINT64 deviceid;//���ڵ�device���
	struct DEVICE *deviceptr;//��һ��deviceָ��

	char *filename;//�ļ���
	//veronica��
	char *filepath;//�ļ�������·�����������disk�е�·����filename���

	int storestate;//��ǰ�洢״̬
	*/
	//���Ԫ������Ϣ
	UINT64 *chunkid;//��ǰchunk��ָ����
	int chunknum,isparity;//chunk����

	UINT64 regionid;//region���

	UINT64 stripid;//strip���

	UINT64 diskid;//��ǰ�洢�����

	UINT64 deviceid;//�豸���

	char *filename;//�ļ���
	char *filepath;//�ļ�·��

	int resTF,storestate; //��ǰ�洢״̬

	FILE *flout;
	

	//���㵱ǰԪ��λ��
	strsetid=strset->StripsectID;
	//��id�б�
	isparity=strset->isparity;
	chunkid=strset->chunkid;
	chunksize=strset->chunksize;
	chunknum=strset->chunknum;
	//��ȡ��Ӧ����Ϣ
	regionid=strset->regionid;
	stripid=strset->stripid;
	regionptr=strset->regionptr;
	stripptr=strset->stripptr;
	diskid=strset->diskid;
	deviceid=strset->deviceid;
	//�ļ�·��
	filename=strset->filename;
	filepath=strset->filepath;
	//�洢״̬
	storestate=strset->storestate;
	//��ȫ�Լ��
	if(regionptr==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","region point is not exist");
		return FALSE;
	}
	if(stripptr==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","strip point is not exist");
		return FALSE;
	}
	//��ʼ���д洢״̬���
	/*if(regionptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","region state is empty");
		return FALSE;
	}
	if(stripptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","strip state is empty");
		return FALSE;
	}*/

	//�ҵ�ȫ��Ԫ���ݵ�ַ
	glometapath=get_state_glometapath();//��ȡȫ��Ԫ����ָ��
	//Ԫ����λ��
	metapath=talloc(char,(30+30+30+40+1000));//1000λ��·��
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//�����ַ���
	//��ʼ�����ļ�Ԫ����·������
	U64toSTR(regoinidstr,regionid);//��������id
	U64toSTR(stripidstr,stripid);//��������id
	U64toSTR(strsetidstr,strsetid);//������������id

	file_regionstr(regionnamestr,regoinidstr);//����region�ַ���
	file_stripstr(stripidnamestr,stripidstr);//����strip�ַ���
	file_stripsectstr(stripsectnamestr,strsetidstr);//����stripsect�ַ���
	file_stripsectstr_name(strsetfilename,strsetidstr);//�����ļ���

	//·��������һ��
	strcat(metapath,glometapath);//��Ԫ����·��ƴ����ȥ
	strcat(metapath,regionnamestr);//��region�ַ���ƴ����ȥ
	strcat(metapath,stripidnamestr);//��strip�ַ���ƴ����ȥ
	strcat(metapath,stripsectnamestr);//��stripsect�ַ���ƴ����ȥ
	strcat(metapath,strsetfilename);//���ļ�������
	
	//����metapath������ô�Ϳ���
	/*
	UINT64 StripsectID;//STRIPSECT��id

	UINT64 *chunkid;//	���а�����chunkid
	CHUNKGROUP *chunklist;//����һ��chunkgroup�þ߼�¼chunk��,��Ϊһ��chunkָ��
	int chunksize;//chunk��С
	int chunknum;//������chunk��������

	UINT64 regionid;///���ڵ�region���
	struct REGION *regionptr;//��һ��regionָ��

	UINT64 stripid;//���ڵ�strip���
	struct STRIP *stripptr;//��һ��stripָ��

	UINT64 diskid;//���ڵ�disk���
	struct DISK *diskptr;//��һ��diskָ��

	UINT64 deviceid;//���ڵ�device���
	struct DEVICE *deviceptr;//��һ��deviceָ��

	char *filename;//�ļ���
	//veronica��
	char *filepath;//�ļ�������·�����������disk�е�·����filename���

	int storestate;//��ǰ�洢״̬
	*/
	//
	resTF=file_FILELAYER_dictionary_stripsect_exists(regionid,stripid,strsetid);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","dictionary can't create");
		return FALSE;
	}
	flout=fopen(metapath,"w+");
	if(flout==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","fptr can't create");
		return FALSE;
	}
	fprintf(flout,"the stripset id: %I64d\n",strsetid);//��ǰstripsect�ı��
	fprintf(flout,"the stripsect is parity(0:FALSE,>0:TRUE):%d\n",isparity);
	fprintf(flout,"the chunksize:%d\n",chunksize);//����ÿһ��chunk�Ĵ�С
	fprintf(flout,"there are: %d chunks, chunk id list:\n",chunknum);
	for(i=0;i<chunknum;i++)
	{
		fprintf(flout,"%I64d\n",chunkid[i]);//��chunk��������Ԫ�����ļ���
	}
	//�ϲ�id��д��
	fprintf(flout,"region id:%I64d\n",regionid);
	fprintf(flout,"strip id:%I64d\n",stripid);
	fprintf(flout,"disk id:%I64d\n",diskid);
	fprintf(flout,"device id:%I64d\n",deviceid);

	//�������ļ�·��д��
	fprintf(flout,"store filename:%s\n",filename);
	fprintf(flout,"store filepath:%s\n",filepath);
	//��ǰ�洢״̬
	fprintf(flout,"stripsect state(countnum):%d\n",storestate);
	fclose(flout);
	free(metapath);//����ͷ�·����Ϣ
	return TRUE;
}
//��STRIPSECT�������а�����·��д�뵽��Ӧ������;������Ҫͨ��stripdes�в���
int file_FILELAYER_STRIP_WRITER(STRIP *str)
{
	/*
	UINT64 StripID;//��Ϣ

	STRIPDES *strdes;//����������stripdes��chunk��*stripdes�д�����=���������chunk��
	
	struct DISKGROUP *disklist;//�洢���б�
	UINT64 *diskid;//�����Ĵ洢��id
	int disknum;//�����洢������
	
	struct DEVICEGROUP *devicelist;//�豸�б�
	UINT64 *deviceid;//�豸id
	int devicenum;//�豸��

	STRIPSECTGROUP *stripsectlist;//stripsectָ��
	UINT64 *stripsectid;//stripsect��id
	int strsetnum;//Strset������

	CHUNKGROUP *chunklist;//����һ��chunkgroup�þ߼�¼chunk��,��Ϊһ��chunkָ��
	UINT64 *chunkid;//	���а�����chunkid
	int chunknum;//������chunk����

	UINT64 regionid;//���ڵ�region���
	struct REGION *regionptr;//��һ��regionָ��

	int storestate;//��ǰ�洢״̬
	*/
	UINT64 stripid,*diskid,*deviceid,*strsetid,*chunkid,regionid;
	int i,disknum,devicenum,strsetnum,chunknum,storestate,resTF;
	REGION *regionptr;
	STRIPDES *strdes;
	char regoinidstr[20]="",stripidstr[20]="";
	char regionidnamestr[30]="",stripidnamestr[30]="";
	char stripfilenamestr[40]="";
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	FILE *flout;
	regionptr=str->regionptr;
	if(regionptr==NULL)
	{
		show_error("file_FILELAYER","STRIP_WRITER","region point is not exist");
		return FALSE;
	}
	/*if(regionptr->storestate==EMPTY)
	{
		show_error("file_FILELAYER","STRIP_WRITER","region state is empty");
		return FALSE;
	}*/
	//���ڿ�ʼ��ֵ
	stripid=str->StripID;

	strdes=str->strdes;

	diskid=str->diskid;
	disknum=str->disknum;

	deviceid=str->deviceid;
	devicenum=str->devicenum;

	strsetid=str->stripsectid;
	strsetnum=str->strsetnum;

	chunkid=str->chunkid;
	chunknum=str->chunknum;

	regionid=str->regionid;
	//�洢״̬
	storestate=str->storestate;

	glometapath=get_state_glometapath();//��ȡȫ��Ԫ����ָ��
	//Ԫ����λ��
	metapath=talloc(char,(30+30+40+1000));//1000λ��·��
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//�����ַ���
	//��ʼ�����ļ�Ԫ����·������
	U64toSTR(regoinidstr,regionid);//��������id
	U64toSTR(stripidstr,stripid);//��������id

	file_regionstr(regionidnamestr,regoinidstr);//����region�ַ���
	file_stripstr(stripidnamestr,stripidstr);//�ϲ�strip�ļ���
	file_stripstr_name(stripfilenamestr,stripidstr);//����strip�ַ���

	//·��������һ��
	strcat(metapath,glometapath);//��Ԫ����·��ƴ����ȥ
	strcat(metapath,regionidnamestr);//��region�ַ���ƴ����ȥ
	strcat(metapath,stripidnamestr);//��strip�ַ���ƴ����ȥ
	strcat(metapath,stripfilenamestr);//strip�ļ���ƴ����ȥ
	
	//���Կ�ʼд��Ԫ������
	/*
	UINT64 StripID;//��Ϣ

	STRIPDES *strdes;//����������stripdes��chunk��*stripdes�д�����=���������chunk��
	
	struct DISKGROUP *disklist;//�洢���б�
	UINT64 *diskid;//�����Ĵ洢��id
	int disknum;//�����洢������

	struct DEVICEGROUP *devicelist;//�豸�б�
	UINT64 *deviceid;//�豸id
	int devicenum;//�豸��

	STRIPSECTGROUP *stripsectlist;//stripsectָ��
	UINT64 *stripsectid;//stripsect��id
	int strsetnum;//Strset������

	CHUNKGROUP *chunklist;//����һ��chunkgroup�þ߼�¼chunk��,��Ϊһ��chunkָ��
	UINT64 *chunkid;//	���а�����chunkid
	int chunknum;//������chunk����

	UINT64 regionid;//���ڵ�region���
	struct REGION *regionptr;//��һ��regionָ��

	int storestate;//��ǰ�洢״̬
	*/
	//��Ҫ�ȼ���ļ����Ƿ����
	resTF=file_FILELAYER_dictionary_strip_exists(regionid,stripid);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","STRIP_WRITER","dictionary can't create");
		return FALSE;
	}
	flout=fopen(metapath,"w+");
	if(flout==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","fptr can't create");
		return FALSE;
	}
	fprintf(flout,"strip id:%I64d\n",stripid);
	//fprintf(flout,"strip description:\n");
	fprintf(flout,"chunknum of each stripsect:%d\n",strdes->chunknum);
	fprintf(flout,"chunksize is:%d\n",strdes->chunksize);
	fprintf(flout,"there are %d disks,disk id list:\n",disknum);
	for(i=0;i<disknum;i++)//����des��������strip����ͬдһ����
	{
		fprintf(flout,"%I64d\n",diskid[i]);
	}
	fprintf(flout,"there are %d devices,device id list:\n",devicenum);
	for(i=0;i<devicenum;i++)
	{
		fprintf(flout,"%I64d\n",deviceid[i]);
	}
	fprintf(flout,"there are %d stripsects,stripsect id list:\n",strsetnum);
	for(i=0;i<strsetnum;i++)
	{
		fprintf(flout,"%I64d\n",strsetid[i]);
	}
	fprintf(flout,"there are %d chunks,chunk id list:\n",chunknum);
	for(i=0;i<chunknum;i++)
	{
		fprintf(flout,"%I64d\n",chunkid[i]);
	}
	fprintf(flout,"region id:%I64d\n",regionid);
	fprintf(flout,"strip state(countnum):%d\n",storestate);
	fclose(flout);
	free(metapath);//����ͷ�·����Ϣ
	return TRUE;
}
//��regionд����Ӧλ��;������Ҫͨ��region��disk�в���
int file_FILELAYER_REGION_WRITER(REGION *reg)
{
	/*
	UINT64 RegionID;//region��id
	int codetype;//��������
	CODEPARA *codepara;//�������
	UINT64 totalsize;//�ܴ洢�ռ��С�ֽ�Ϊ��С��NODEF�������޴�ֱ��ռ��

	struct FILEMETAGROUP *filemetalist;//�ļ�Ԫ�����б�
	UINT64 *fileid;//������file�ı���б�
	int filenum;//strip����

	DISKGROUP *disklist;//Disk�б�
	UINT64 *diskid;//Disk�ı���б�
	int disknum;//���̵ĸ���

	DEVICEGROUP *devicelist;//device�б�
	UINT64 *deviceid;//�豸id�б�
	int devicenum;//�豸����

	STRIPDES *strdes;//��������������
	STRIPGROUP *striplist;//Strip�б�
	UINT64 *stripid;//����id�б�
	int stripnum;//��������

	struct FILEMETA *fileroot;//��ǰ������ļ��ĸ�ָ��
	UINT64 rootfileid;//���ļ����

	int storestate;//��ǰ�洢״̬
	*/
	UINT64 regionid;
	CODEPARA *codepara;
	UINT64 *fileid,*diskid,*deviceid,*stripid,rootfileid,totalsize,chunknum,stripsectnum;//��ͬ��ȫ��
	int i,codetype,filenum,disknum,devicenum,stripnum,storestate,resTF;
	STRIPDES *strdes;
	char regoinidstr[20]="";
	char regionidnamestr[30]="";
	char regionfilenamestr[40]="";
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	FILE *flout;

	//region���谲ȫ�Լ��
	//��ʼ��ֵ
	regionid=reg->RegionID;

	codetype=reg->codetype;
	codepara=reg->codepara;
	totalsize=reg->totalsize;

	fileid=reg->fileid;
	filenum=reg->filenum;

	diskid=reg->diskid;
	disknum=reg->disknum;

	deviceid=reg->deviceid;
	devicenum=reg->devicenum;
	
	strdes=reg->strdes;
	stripid=reg->stripid;
	stripnum=reg->stripnum;

	chunknum=reg->chunknum;
	stripsectnum=reg->stripsectnum;
	
	rootfileid=reg->rootfileid;

	storestate=reg->storestate;

	glometapath=get_state_glometapath();//��ȡȫ��Ԫ����ָ��
	//Ԫ����λ��
	metapath=talloc(char,(30+40+1000));//1000λ��·��
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//�����ַ���
	//��ʼ�����ļ�Ԫ����·������
	//printf("%I64d",regionid);
	U64toSTR(regoinidstr,regionid);//��������id
	
	file_regionstr(regionidnamestr,regoinidstr);//����region�ַ���
	file_regionstr_name(regionfilenamestr,regoinidstr);//�ϲ�strip�ļ���

	//·��������һ��
	strcat(metapath,glometapath);//��Ԫ����·��ƴ����ȥ
	strcat(metapath,regionidnamestr);//��region�ַ���ƴ����ȥ
	strcat(metapath,regionfilenamestr);//��region���ļ���ƴ����ȥ
	
	//��Ҫ�ȼ���ļ����Ƿ����
	resTF=file_FILELAYER_dictionary_region_exists(regionid);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","dictionary can't create");
		return FALSE;
	}
	flout=fopen(metapath,"w+");
	if(flout==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","fptr can't create");
		return FALSE;
	}
	/*
	UINT64 RegionID;//region��id
	int codetype;//��������
	CODEPARA *codepara;//�������
	UINT64 totalsize;//�ܴ洢�ռ��С�ֽ�Ϊ��С��NODEF�������޴�ֱ��ռ��

	struct FILEMETAGROUP *filemetalist;//�ļ�Ԫ�����б�
	UINT64 *fileid;//������file�ı���б�
	int filenum;//strip����

	DISKGROUP *disklist;//Disk�б�
	UINT64 *diskid;//Disk�ı���б�
	int disknum;//���̵ĸ���

	DEVICEGROUP *devicelist;//device�б�
	UINT64 *deviceid;//�豸id�б�
	int devicenum;//�豸����

	STRIPDES *strdes;//��������������
	STRIPGROUP *striplist;//Strip�б�
	UINT64 *stripid;//����id�б�
	int stripnum;//��������

	struct FILEMETA *fileroot;//��ǰ������ļ��ĸ�ָ��
	UINT64 rootfileid;//���ļ����

	int storestate;//��ǰ�洢״̬
	*/
	//��ʼ���
	fprintf(flout,"region id:%I64d\n",regionid);
	//��ʼ�������
	fprintf(flout,"code type(code):%d,the parameter list:\n",codetype);
	fprintf(flout,"the galois field:%d\n",codepara->w);
	fprintf(flout,"data disk num:%d\n",codepara->datanum);
	fprintf(flout,"code disk num:%d\n",codepara->codenum);
	fprintf(flout,"total disk num:%d\n",codepara->totnum);
	fprintf(flout,"provider num:%d\n",codepara->pronum);
	fprintf(flout,"sector number:%d\n",codepara->sectornum);
	//�ܴ�С
	fprintf(flout,"total size of region:%I64d\n",totalsize);
	fprintf(flout,"there are %d files,file id list:\n",filenum);
	for(i=0;i<filenum;i++)
	{
		fprintf(flout,"%I64d\n",fileid[i]);
	}
	fprintf(flout,"there are %d disks,disk id list:\n",disknum);
	for(i=0;i<disknum;i++)
	{
		fprintf(flout,"%I64d\n",diskid[i]);
	}
	fprintf(flout,"there are %d devices,device id list:\n",devicenum);
	for(i=0;i<devicenum;i++)
	{
		fprintf(flout,"%I64d\n",deviceid[i]);
	}
	fprintf(flout,"stripsect has %d chunks,each chunk is %d bytes\n",strdes->chunknum,strdes->chunksize);
	fprintf(flout,"there are %d strips,strip id list:\n",stripnum);
	for(i=0;i<stripnum;i++)
	{
		fprintf(flout,"%I64d\n",stripid[i]);
	}
	fprintf(flout,"total chunk number:%I64d\n",chunknum);
	fprintf(flout,"total stripsect number:%I64d\n",stripsectnum);

	fprintf(flout,"root file id:%I64d\n",rootfileid);
	fprintf(flout,"region state(countnum):%d\n",storestate);
	fclose(flout);
	free(metapath);//����ͷ�·����Ϣ
	return TRUE;

}
//��DISK��Ԫ����д�����
int file_FILELAYER_DISK_WRITER(DISK *disk)
{
	/*	
	UINT64 DiskID;//�洢�����
	int DiskTYPE;//�洢������
	int capability;//��������
	int volumn;//�洢������

	struct REGIONGROUP *regionlist;//ָ�����а�����region��ָ��
	UINT64 *regionid;//�洢�����漰����region��
	int regionnum;//�洢���ϰ�����region����

	struct DEVICE *deviceptr;//ָ���ϼ�device�б�
	UINT64 deviceid;//��һ���device���
	
	char *diskpath;//�ؼ���Ϣ��ǰ���̵�����·��

	int storestate;//��ǰ�洢״̬
	*/
	UINT64 diskid,deviceid,volumn;
	int disktype,capability;
	UINT64 *regionid;
	int i,regionnum,storestate,resTF;
	char *diskpath;
	DEVICE *deviceptr;
	char deviceidstr[20]="";
	char diskidstr[20]="";

	char deviceidnamestr[30]="";
	char diskfilenamestr[40]="";

	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	FILE *flout;

	deviceptr=disk->deviceptr;
	//��ȫ�Լ��
	if(deviceptr==NULL)
	{
		show_error("file_FILELAYER","DISK_WRITER","device point is not exist");
		return FALSE;
	}
	if(deviceptr->storestate=EMPTY)
	{
		show_error("file_FILELAYER","DISK_WRITER","device state is empty");
		return FALSE;
	}
	//�ȸ�ֵ
	diskid=disk->DiskID;
	disktype=disk->DiskTYPE;
	capability=disk->capability;
	volumn=disk->volumn;

	regionid=disk->regionid;
	regionnum=disk->regionnum;

	deviceid=disk->deviceid;

	diskpath=disk->diskpath;

	storestate=disk->storestate;
	//�����Ǵ����ļ���ȫ���Ե�,ҲҪ����·��
	glometapath=get_state_glometapath();
	//metapath=glometapath;
	metapath=talloc(char,1000+30+40);
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","DISK_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';

	U64toSTR(deviceidstr,deviceid);
	U64toSTR(diskidstr,diskid);

	file_devicestr(deviceidnamestr,deviceidstr);
	file_diskstr_name(diskfilenamestr,diskidstr);

	strcat(metapath,glometapath);
	strcat(metapath,deviceidnamestr);
	strcat(metapath,diskfilenamestr);

	//���Ŀ¼
	resTF=file_FILELAYER_dictionary_disk_exists(deviceid,diskid);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","DISK_WRITER","dictionary can't create");
		return FALSE;
	}
	//�ļ�ָ��
	flout=fopen(metapath,"w+");
	if(flout==NULL)
	{
		show_error("file_FILELAYER","DISK_WRITER","fptr can't create");
		return FALSE;
	}
	/*	
	UINT64 DiskID;//�洢�����
	int DiskTYPE;//�洢������
	int capability;//��������
	int volumn;//�洢������

	struct REGIONGROUP *regionlist;//ָ�����а�����region��ָ��
	UINT64 *regionid;//�洢�����漰����region��
	int regionnum;//�洢���ϰ�����region����

	struct DEVICE *deviceptr;//ָ���ϼ�device�б�
	UINT64 deviceid;//��һ���device���
	
	char *diskpath;//�ؼ���Ϣ��ǰ���̵�����·��

	int storestate;//��ǰ�洢״̬
	*/
	//��ʼ���
	fprintf(flout,"disk id:%I64d\n",diskid);
	fprintf(flout,"disk type(0:NORHDD,1:SSHD,2:SSD):%d\n",disktype);
	fprintf(flout,"disk capability(0:NONCAP,1:LOWCAP,2:MIDCAP,3:HIGHCAP):%d\n",capability);
	fprintf(flout,"disk volumn:%I64d\n",volumn);
	fprintf(flout,"there are %d regions,region id list:\n",regionnum);
	for(i=0;i<regionnum;i++)
	{
		fprintf(flout,"%I64d\n",regionid[i]);
	}
	fprintf(flout,"device id:%I64d\n",deviceid);
	fprintf(flout,"disk path:%s\n",diskpath);
	
	fprintf(flout,"disk state(countnum):%d\n",storestate);
	fclose(flout);
	free(metapath);//����ͷ�·����Ϣ
	return TRUE;
}
//��DEVICE��Ԫ����д�����
int file_FILELAYER_DEVICE_WRITER(DEVICE *device)
{
	/*UINT64 DeviceID;//�豸���
	int Devicetype;//�豸���
	int processnum;//����������
	int *speed;//GHZ

	
	UINT64 *diskid;//�豸�д��ڵĴ洢��
	DISKGROUP *disklist;//�洢�豸�б�
	int disknum;//�洢�����洢��

	struct REGIONGROUP *regionlist;//region�б�
	UINT64 *regionid;//region���
	int regionnum;//region����

	int storestate;//��ǰ�洢״̬*/
	UINT64 deviceid,*diskid,*regionid;
	int devicetype,processnum,disknum,regionnum;
	int *speed;
	int i,storestate,resTF;
	char deviceidstr[20]="";
	char deviceidnamestr[30]="";
	char devicefilenamestr[40]="";
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	FILE *flout;
	//device��ֵ
	deviceid=device->DeviceID;
	devicetype=device->Devicetype;
	processnum=device->processnum;
	speed=device->speed;
	//disk��id
	diskid=device->diskid;
	disknum=device->disknum;
	//region��id
	regionid=device->regionid;
	regionnum=device->regionnum;
	//�洢״̬
	storestate=device->storestate;
	//�����Ǵ����ļ���ȫ���Եģ����ǻ��Ƿ����ļ�����
	glometapath=get_state_glometapath();
	metapath=talloc(char,(1000+30+40));
	//metapath=glometapath;
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","DEVICE_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';
	U64toSTR(deviceidstr,deviceid);

	file_devicestr(deviceidnamestr,deviceidstr);
	file_devicestr_name(devicefilenamestr,deviceidstr);

	strcat(metapath,glometapath);
	strcat(metapath,deviceidnamestr);
	strcat(metapath,devicefilenamestr);
	//�豸Ŀ¼
	resTF=file_FILELAYER_dictionary_device_exists(deviceid);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","DEVICE_WRITER","dictionary can't create");
		return FALSE;
	}
	//���ļ�ָ��
	flout=fopen(metapath,"w+");
	if(flout==NULL)
	{
		show_error("file_FILELAYER","DEVICE_WRITER","fptr can't create");
		return FALSE;
	}
	fprintf(flout,"device id:%I64d\n",deviceid);
	fprintf(flout,"device type(0:RACKMAC,1:PCMAC,2:NASMAC):%d\n",devicetype);
	fprintf(flout,"there are %d processors,speed list:\n",processnum);
	for(i=0;i<processnum;i++)
	{
		fprintf(flout,"%I64d\n",speed[i]);
	}
	fprintf(flout,"there are %d disks,disk id list:\n",disknum);
	for(i=0;i<disknum;i++)
	{
		fprintf(flout,"%I64d\n",diskid[i]);
	}
	fprintf(flout,"there are %d regions,region id list:\n",regionnum);
	for(i=0;i<regionnum;i++)
	{
		fprintf(flout,"%I64d\n",regionid[i]);
	}
	fprintf(flout,"device state(countnum):%d\n",storestate);
	fclose(flout);
	free(metapath);//����ͷ�·����Ϣ
	return TRUE;
}
//���ļ���Ԫ����Ϣд�����
int file_FILELAYER_FILEMETA_WRITER(FILEMETA *fmeta)
{
	/*
	UINT64 FileID;//�ļ�ID
	char *filename;//�ļ�������Ŀ¼��
	int filesize;//�ļ���С
	int ACList;//�ļ����ʱ�ʶ
	int filetype;//�ļ�����,�ļ�����Ŀ¼,�ļ�����,ֻ���鵵����ϵͳ

	struct USERPROFILE *userinf;//�ļ�������
	UINT64 userid;//�ļ�������id

	UINT64 parentid;//��һ���ļ���id
	struct FILEMETA *parentptr;//��һ���ļ���
	
	UINT64 *subfileidlist;//��Ŀ¼�б�������Ҫ����linux˼��
	struct FILEMETA *subfilelist;//�ļ���ָ����Ҫָ��ǰĿ¼��һ��Ԫ���ݿ飬Ϊ�˼���
	int subfilenum;//��Ŀ¼���ļ�����

	struct tm *createtime;//����ʱ��
	struct tm *updatetime;//����ʱ��

	FILEINF *filechunkinf;//���ڴ�����ݿ���Ϣ
	*/
	//fmeta��Ϣ
	UINT64 fileid;
	char *filename;
	int i,ACList,filetype,subfilenum,resTF;
	UINT64 userid,parentid,filesize;
	UINT64 *subfileidlist;
	struct tm *createtime,*updatetime;
	FILEINF *filechunkinf;
	char regionidstr[20]="",fileidstr[20]="";
	char regionidnamestr[30]="";
	char filemetaidnamestr[30]="";
	char filemetafilenamestr[40]="";

	//filechunkinf��Ϣ
	UINT64 *chunkid;
	CHUNKPATH *chunkpath;
	int chunknum;//chunk����

	UINT64 regionid;//���ڵ�region�ı��

	UINT64 *deviceid;//�豸id
	int devicenum;//�豸��

	UINT64 *diskid;//�洢��id�б�
	int disknum;//�洢������

	UINT64 *stripid;//����id�б�
	int stripnum;//��������

	UINT64 *stripsectid;///��������id�б�
	int stripsectnum;//������������

	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	FILE *flout;
	/*
	UINT64 fileid;//�ļ�ID
	struct FILEMETA *filemeta;//�ļ�Ԫ���ݷ���ָ��
	int *chunkid;//Դ����б�
	CHUNKPATH *chkpath;//����chunk��path
	CHUNKGROUP *chunklist;//���б�
	int chunknum;//chunk����

	REGION *regoinptr;//regionָ��
	UINT64 regionid;//���ڵ�region�ı��
	
	DEVICEGROUP *devicelist;//�豸�б�
	UINT64 *deviceid;//�豸id
	int devicenum;//�豸��
	
	DISKGROUP *disklist;//�洢���б�
	UINT64 *diskid;//�洢��id�б�
	int disknum;//�洢������

	STRIPGROUP *striplist;//�����б�
	UINT64 *stripid;//����id�б�
	int stripnum;//��������

	STRIPSECT *stripsectlist;//���������б�
	UINT64 *stripsectid;///��������id�б�
	int stripsectnum;//������������
	*/
	//fmeta+filechunkinf
	//�ȸ�ֵ
	fileid=fmeta->FileID;
	filename=fmeta->filename;
	filesize=fmeta->filesize;
	ACList=fmeta->ACList;
	filetype=fmeta->filetype;

	userid=fmeta->userid;

	parentid=fmeta->parentid;

	subfileidlist=fmeta->subfileidlist;
	subfilenum=fmeta->subfilenum;

	createtime=fmeta->createtime;
	updatetime=fmeta->updatetime;

	filechunkinf=fmeta->filechunkinf;
	//filechunkinf
	//���������һ��û�з����ַ�ռ䣬NULL��NOVALUE����
	if(filechunkinf==NULL)
	{
		chunkid=NULL;
		chunkpath=NULL;
		chunknum=0;

		regionid=fmeta->regionid;//���ڵ�region�ı��

		deviceid=NULL;//�豸id
		devicenum=0;//�豸��

		diskid=NULL;//�洢��id�б�
		disknum=0;//�洢������

		stripid=NULL;//����id�б�
		stripnum=0;//��������
		

		stripsectid=NULL;///��������id�б�
		stripsectnum=0;//������������
	}
	else
	{
		chunkid=filechunkinf->chunkid;
		chunkpath=filechunkinf->chkpath;
		chunknum=filechunkinf->chunknum;//chunk����

		regionid=filechunkinf->regionid;//���ڵ�region�ı��

		deviceid=filechunkinf->deviceid;//�豸id
		devicenum=filechunkinf->devicenum;//�豸��

		diskid=filechunkinf->diskid;//�洢��id�б�
		disknum=filechunkinf->disknum;//�洢������

		stripid=filechunkinf->stripid;//����id�б�
		stripnum=filechunkinf->stripnum;//��������
		

		stripsectid=filechunkinf->stripsectid;///��������id�б�
		stripsectnum=filechunkinf->stripsectnum;//������������
	}


	//��һ����Ҫ��ȡλ����Ϣ
	//�����Ǵ����ļ���region����,�����Ҫ
	glometapath=get_state_glometapath();
	metapath=talloc(char,(30+30+40+1000));//1000λ��·��
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","FILEMETA_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//�����ַ���
	U64toSTR(regionidstr,regionid);//��������id
	U64toSTR(fileidstr,fileid);

	file_regionstr(regionidnamestr,regionidstr);//����region�ַ���
	file_filemetastr(filemetaidnamestr,fileidstr);
	file_filemetastr_name(filemetafilenamestr,fileidstr);//filemeta�ļ���

	//·��������һ��
	strcat(metapath,glometapath);//��Ԫ����·��ƴ����ȥ
	strcat(metapath,regionidnamestr);//��region�ַ���ƴ����ȥ
	strcat(metapath,filemetaidnamestr);//��filemeta��ƴ����ȥ
	strcat(metapath,filemetafilenamestr);//��filename�ַ���ƴ����ȥ
	//���Ŀ¼������
	resTF=file_FILELAYER_dictionary_filemeta_exists(regionid,fileid);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","FILEMETA_WRITER","dictionary can't create");
		return FALSE;
	}
	//metapath=glometapath;
	flout=fopen(metapath,"w+");
	if(flout==NULL)
	{
		show_error("file_FILELAYER","FILEMETA_WRITER","fptr can't create");
		return FALSE;
	}
	fprintf(flout,"filemeta id:%I64d\n",fileid);
	fprintf(flout,"file name:%s\n",filename);
	fprintf(flout,"file size:%I64d\n",filesize);
	fprintf(flout,"Access Control list:%d\n",ACList);
	fprintf(flout,"file type:%d\n",filetype);

	fprintf(flout,"user id:%I64d\n",userid);

	fprintf(flout,"parent dictionary id:%I64d\n",parentid);
	fprintf(flout,"there are %d subfile,filemeta id list:%\n",subfilenum);
	for(i=0;i<subfilenum;i++)
	{
		fprintf(flout,"%I64d\n",subfileidlist[i]);
	}
	//�����޸�ʱ��
	fprintf(flout,"create time:%d/%d/%d/%d/%d,%d/%d/%d,%d\n",
		createtime->tm_year,createtime->tm_mon,createtime->tm_yday,createtime->tm_mday,createtime->tm_wday,
		createtime->tm_hour,createtime->tm_min,createtime->tm_sec,
		createtime->tm_isdst);
	fprintf(flout,"update time:%d/%d/%d/%d/%d,%d/%d/%d,%d\n",
		updatetime->tm_year,updatetime->tm_mon,updatetime->tm_yday,updatetime->tm_mday,updatetime->tm_wday,
		updatetime->tm_hour,updatetime->tm_min,updatetime->tm_sec,
		updatetime->tm_isdst);
	//filechunkinf����
	fprintf(flout,"storage information,there are %d chunks,chunk id list:\n",chunknum);
	for(i=0;i<chunknum;i++)
	{
		fprintf(flout,"%I64d\n",chunkid[i]);
		//����ͬʱҲ���chunkpath
		fprintf(flout,"chunk id:%I64d,chunk array id:%d;",chunkpath->chunkid,chunkpath->chunkarrayid);
		fprintf(flout,"stripsect id:%I64d,stripsect array id:%d;",chunkpath->stripsectid,chunkpath->stripsectarrayid);
		fprintf(flout,"strip id:%I64d,strip array id:%d;",chunkpath->stripid,chunkpath->striparrayid);
		fprintf(flout,"region id:%I64d,region array id:%d\n",chunkpath->regionid,chunkpath->regionarrayid);
		chunkpath++;
	}

	fprintf(flout,"region id:%I64d\n",regionid);
	fprintf(flout,"there are %d devices,device id list:\n",devicenum);
	for(i=0;i<devicenum;i++)
	{
		fprintf(flout,"%I64d\n",deviceid[i]);
	}
	fprintf(flout,"there are %d disks,disk id list:\n",disknum);
	for(i=0;i<disknum;i++)
	{ 
		fprintf(flout,"%I64d\n",diskid[i]);
	}
	fprintf(flout,"there are %d strips,strip id list:\n",stripnum);
	for(i=0;i<stripnum;i++)
	{
		fprintf(flout,"%I64d\n",stripid[i]);//����id�б�
	}
	fprintf(flout,"there are %d stripsects,stripsect id list:\n",stripsectnum);
	for(i=0;i<stripsectnum;i++)
	{
		fprintf(flout,"%I64d\n",stripsectid[i]);
	}
	fclose(flout);
	free(metapath);//����ͷ�·����Ϣ
	return TRUE;
}
//���û���Ϣ��Ԫ����д�����
int file_FILELAYER_USERPROFILE_WRITER(USERPROFILE *pfile)
{
	/*UINT64 UserID;//�û�id
	USERLOCATION *userlocinf;//�û�Ŀ¼λ��
	int userprivil;//�û�Ȩ��
	struct tm *createtime;//�˻�����ʱ��*/
	UINT64 userid,DICid,resTF;
	char *username,*password,*DICpath;
	USERLOCATION *userlocinf;
	int userprivil;
	struct tm *createtime;
	char userprofileidstr[20]="";
	char userprofileidnamestr[40]="";
	char userprofilefilenamestr[50]="";
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	FILE *flout;
	//��ֵ
	userid=pfile->UserID;
	username=pfile->username;
	password=pfile->password;
	userlocinf=pfile->userlocinf;
	DICid=userlocinf->DICid;
	DICpath=userlocinf->DICpath;
	userprivil=pfile->userprivil;
	createtime=pfile->createtime;
	//��ȡԪ���ݵ�ַ
	glometapath=get_state_glometapath();
	//metapath=glometapath;
	metapath=talloc(char,(1000+40+50));
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","USERPROFILE_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';
	U64toSTR(userprofileidstr,userid);

	file_userprofilestr(userprofileidnamestr,userprofileidstr);
	file_userprofilestr_name(userprofilefilenamestr,userprofileidstr);

	strcat(metapath,glometapath);
	strcat(metapath,userprofileidnamestr);
	strcat(metapath,userprofilefilenamestr);
	//����Ŀ¼
	resTF=file_FILELAYER_dictionary_userprofile_exists(userid);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","USERPROFILE_WRITER","dictionary can't create");
		return FALSE;
	}
	//���ļ����
	flout=fopen(metapath,"w+");
	if(flout==NULL)
	{
		show_error("file_FILELAYER","USERPROFILE_WRITER","fptr can't create");
		return FALSE;
	}
	fprintf(flout,"user id:%I64d\n",userid);
	fprintf(flout,"username:%s\n",username);
	fprintf(flout,"password:%s\n",password);
	fprintf(flout,"user dictionary id:%I64d\n",DICid);
	fprintf(flout,"user dictionary path:%s\n",DICpath);
	fprintf(flout,"user privilege:%d\n",userprivil);
	//int tm_sec;     /* seconds after the minute - [0,59] */
    //   int tm_min;     /* minutes after the hour - [0,59] */
    //    int tm_hour;    /* hours since midnight - [0,23] */
    //    int tm_mday;    /* day of the month - [1,31] */
    //    int tm_mon;     /* months since January - [0,11] */
    //    int tm_year;    /* years since 1900 */
    //    int tm_wday;    /* days since Sunday - [0,6] */
    //    int tm_yday;    /* days since January 1 - [0,365] */
    //    int tm_isdst;   /* daylight savings time flag */
	fprintf(flout,"create time:%d/%d/%d/%d/%d,%d/%d/%d,%d",
		createtime->tm_year,createtime->tm_mon,createtime->tm_yday,createtime->tm_mday,createtime->tm_wday,
		createtime->tm_hour,createtime->tm_min,createtime->tm_sec,
		createtime->tm_isdst);
	fclose(flout);
	//free(metapath);//����ͷ�·����Ϣ
	return TRUE;
}
int file_FILELAYER_SHARE_WRITER(AONTSHARE *share)
{
	char *filepath;
	BYTE *bytestream; 
	int writesize,sizenum;
	FILE *flout;
	bytestream=share->content;
	filepath=share->storepath;
	sizenum=share->sizenum;
	flout=fopen(filepath,"w");
	if(flout==NULL)
	{
		show_error("file","file_FILELAYER_SHARE_WRITER","file handle cannot open");
		return FALSE;
	}
	writesize=fwrite(bytestream,sizeof(BYTE),sizenum,flout);
	if(writesize!=sizenum)
	{
		show_error("file_FILELAYER","SHARE_WRITER","the share can't write to the disks");
		return FALSE;
	}
	fclose(flout);
	return TRUE;
}

//����ȫ���ļ�ֻ��һ������group����
//���û���Ϣ��Ԫ����д�����
int file_FILELAYER_GLOSYSTEMID_WRITER(GLOSYSTEMID *glosysid)
{
	UINT64 *regionidlist,*useridlist,*deviceidlist,*diskidlist,glomaxbuffersize;
	int i,regionnum,usernum,devicenum,disknum;

	IDITEM *systemnextid;
	//UINT64 chunkidlist;
	int *availkind;//�ִ��������
	int availnum,glopushtime;//������������

	char glofilename[40]="";
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	FILE *flout;
	regionidlist=glosysid->regionid;
	regionnum=glosysid->regionnum;

	useridlist=glosysid->userid;
	usernum=glosysid->usernum;

	deviceidlist=glosysid->deviceid;
	devicenum=glosysid->devicenum;

	diskidlist=glosysid->diskid;
	disknum=glosysid->disknum;
	//��ȡԪ���ݵ�ַ
	glometapath=get_state_glometapath();
	metapath=talloc(char,(1000+40));
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","USERPROFILE_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';

	file_globaldeine_name(glofilename);

	strcat(metapath,glometapath);
	strcat(metapath,glofilename);

	flout=fopen(metapath,"w+");
	if(flout==NULL)
	{
		show_error("file_FILELAYER","GLOSYSTEMID_WRITER","fptr can't create");
		return FALSE;
	}
	fprintf(flout,"there are %d regions,region id list:\n",regionnum);
	for(i=0;i<regionnum;i++)
	{
		fprintf(flout,"%I64d\n",regionidlist[i]);
	}
	fprintf(flout,"there are %d users,user id list:\n",usernum);
	for(i=0;i<usernum;i++)
	{
		fprintf(flout,"%I64d\n",useridlist[i]);
	}
	fprintf(flout,"there are %d devices,device id list:\n",devicenum);
	for(i=0;i<devicenum;i++)
	{
		fprintf(flout,"%I64d\n",deviceidlist[i]);
	}
	fprintf(flout,"there are %d disks,disk id list:\n",disknum);
	for(i=0;i<disknum;i++)
	{
		fprintf(flout,"%I64d\n",diskidlist[i]);
	}
	//�����ǰid��
	systemnextid=glosysid->systemnextid;
	fprintf(flout,"next step region id:%I64d,strip id:%I64d,stripsect id:%I64d,chunk id:%I64d\n",
		systemnextid->gloregionid,systemnextid->glostripid,systemnextid->glostripsectid,systemnextid->glochunkid);
	fprintf(flout,"device id:%I64d,disk id:%I64d,file id:%I64d,user id:%I64d\n",
		systemnextid->glodeviceid,systemnextid->glodiskid,systemnextid->glofileid,systemnextid->glouserid);
	//��������
	availnum=glosysid->availnum;
	availkind=glosysid->availkind;
	fprintf(flout,"there are %d kinds code,the id list of code:\n",availnum);
	for(i=0;i<availnum;i++)
	{
		fprintf(flout,"%d\n",availkind[i]);
	}

	//���pushʱ��
	glopushtime=glosysid->glopushtime;
	glomaxbuffersize=glosysid->glomaxbuffersize;
	fprintf(flout,"the push time of system is %d time uints\n",glopushtime);
	fprintf(flout,"the push maximum buffer size is %I64d BYTE\n",glomaxbuffersize);
	free(metapath);
	fclose(flout);
	return TRUE;
}
//���д��,д�����
//��CHUNKGROUP�������а�����·��д�뵽��Ӧ������
int file_FILELAYER_CHUNKGROUP_WRITER_META(CHUNKGROUP *chkgroup)
{
	int i,groupsize,resTF;
	CHUNK *chunkptr;
	chunkptr=chkgroup->ckgroup;
	groupsize=chkgroup->groupsize;
	for(i=0;i<groupsize;i++)
	{
		resTF=file_FILELAYER_CHUNK_WRITER_META(chunkptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","CHUNKGROUP_WRITER","chunk writer failed");
			return FALSE;
		}
		chunkptr++;
	}
	return TRUE;
}
//��CHUNKGROUP�������а�����·��д�뵽��Ӧ������,���ݲ���
int file_FILELAYER_CHUNKGROUP_WRITER_DATA(CHUNKGROUP *chkgroup)
{
	int i,groupsize,resTF;
	CHUNK *chunkptr;
	chunkptr=chkgroup->ckgroup;
	groupsize=chkgroup->groupsize;
	for(i=0;i<groupsize;i++)
	{
		resTF=file_FILELAYER_CHUNK_WRITER_DATA(chunkptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","CHUNKGROUP_WRITER","chunk writer failed");
			return FALSE;
		}
		chunkptr++;
	}
	return TRUE;
}
//��STRIPSECTGROUP�����ڲ���Ϣ�ڶ�Ӧλ�ô�����Ӧ��stripsect
int file_FILELAYER_STRIPSECTGROUP_CREATE(STRIPSECTGROUP *strsetgroup)
{
	int i,groupsize,resTF;
	STRIPSECT *strsetptr;
	strsetptr=strsetgroup->stripsectgroup;
	groupsize=strsetgroup->groupsize;
	for(i=0;i<groupsize;i++)
	{
		resTF=file_FILELAYER_STRIPSECT_CREATE(strsetptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","STRIPSECTGROUP_CREATE","stripsect create failed");
			return FALSE;
		}
		strsetptr++;
	}
	return TRUE;
}
//��STRIPSECTGROUP�������а�����·��д�뵽��Ӧ������
int file_FILELAYER_STRIPSECTGROUP_WRITER(STRIPSECTGROUP *strsetgroup)
{
	int i,groupsize,resTF;
	STRIPSECT *strsetptr;
	strsetptr=strsetgroup->stripsectgroup;
	groupsize=strsetgroup->groupsize;
	for(i=0;i<groupsize;i++)
	{
		resTF=file_FILELAYER_STRIPSECT_WRITER(strsetptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","STRIPSECTGROUP_CREATE","stripsect writer failed");
			return FALSE;
		}
		strsetptr++;
	}
	return TRUE;
}
//��STRIPGROUP�������а�����·��д�뵽��Ӧ������;������Ҫͨ��region��disk�в���
int file_FILELAYER_STRIPGROUP_WRITER(STRIPGROUP *strgroup)
{
	int i,groupsize,resTF;
	STRIP *stripptr;
	stripptr=strgroup->stripgroup;
	groupsize=strgroup->groupsize;
	for(i=0;i<groupsize;i++)
	{
		resTF=file_FILELAYER_STRIP_WRITER(stripptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","STRIPGROUP_WRITER","strip writer failed");
			return FALSE;
		}
		stripptr++;

	}
	return TRUE;
}
//��REGIONGROUPд����Ӧ����
int file_FILELAYER_REGIONGROUP_WRITER(REGIONGROUP *reggroup)
{
	int i,groupsize,resTF;
	REGION *regionptr;
	regionptr=reggroup->regiongroup;
	groupsize=reggroup->groupsize;
	for(i=0;i<groupsize;i++)
	{ 
		resTF=file_FILELAYER_REGION_WRITER(regionptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","REGIONGROUP_WRITER","region writer failed");
			return FALSE;
		}
		regionptr++;
	}
	return TRUE;
}
//��DISKGROUPд����Ӧ����
int file_FILELAYER_DISKGROUP_WRITER(DISKGROUP *diskgroup)
{
	int i,groupsize,resTF;
	DISK *diskptr;
	diskptr=diskgroup->diskgroup;
	groupsize=diskgroup->groupsize;
	for(i=0;i<groupsize;i++)
	{ 
		resTF=file_FILELAYER_DISK_WRITER(diskptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","DISKGROUP_WRITER","disk writer failed");
			return FALSE;
		}
		diskptr++;
	}
	return TRUE;
}
//��DEVICEGROUPд����Ӧ����
int file_FILELAYER_DEVICEGROUP_WRITER(DEVICEGROUP *devicegroup)
{
	int i,groupsize,resTF;
	DEVICE *deviceptr;
	deviceptr=devicegroup->devicegroup;
	groupsize=devicegroup->groupsize;
	for(i=0;i<groupsize;i++)
	{
		resTF=file_FILELAYER_DEVICE_WRITER(deviceptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","DEVICEGROUP_WRITER","device writer failed");
			return FALSE;
		}
		deviceptr++;
	}
	return TRUE;
}
//��FILEMETAGROUPд����Ӧ����
int file_FILELAYER_FILEMETAGROUP_WRITER(FILEMETAGROUP *fmetagroup)
{
	int i,groupsize,resTF;
	FILEMETA *fileptr;
	fileptr=fmetagroup->filemetagroup;
	groupsize=fmetagroup->grouposize;
	for(i=0;i<groupsize;i++)
	{
		resTF=file_FILELAYER_FILEMETA_WRITER(fileptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","FILEMETAGROUP_WRITER","filemeta writer failed");
			return FALSE;
		}
		fileptr++;
	}
	return TRUE;
}
//��USERGROUPд�뵽��Ӧλ��
int file_FILELAYER_USERPROFILEGROUP_WRITER(USERGROUP *ugroup)
{
	int i,groupsize,resTF;
	USERPROFILE *userproptr;
	userproptr=ugroup->userlist;
	groupsize=ugroup->groupsize;
	for(i=0;i<groupsize;i++)
	{
		resTF=file_FILELAYER_USERPROFILE_WRITER(userproptr);
		if(resTF==FALSE)
		{
			show_error("file_FILELAYER","USERPROFILEGROUP_WRITER","userprofile writer failed");
			return FALSE;
		}
		userproptr++;
	}
	return TRUE;
}


int file_FILELAYER_dictionary_exists(char *dicpath)
{
	int resTF;
	resTF=access(dicpath,0);
	if(resTF!=-1)
	{
		return TRUE;
	}
	else
	{
		//��������ڴ���֮
		resTF=mkdir(dicpath);
		if(resTF==-1)
		{
			show_error("file_FILELAYER","dictionary_exists","dictionary can't create");
			return FALSE;
		}
	}
	return TRUE;
}
int file_FILELAYER_dictionary_region_exists(UINT64 regionid)
{
	//��һ����
	int resTF;
	char regionidstr[20]="";
	char regionidnamestr[30]="";
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	glometapath=get_state_glometapath();
	metapath=talloc(char,1000+30);
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","dictionary_region_exists","NO memory");
		return FALSE;
	}
	metapath[0]='\0';
	U64toSTR(regionidstr,regionid);

	file_regionstr(regionidnamestr,regionidstr);
	
	strcat(metapath,glometapath);
	strcat(metapath,regionidnamestr);
	resTF=file_FILELAYER_dictionary_exists(metapath);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","dictionary_region_exists","DICpath can't create");
		return FALSE;
	}
	free(metapath);
	return TRUE;
}
int file_FILELAYER_dictionary_strip_exists(UINT64 regionid,UINT64 stripid)
{
	//��һ����
	int resTF;
	char regionidstr[20]="",stripidstr[20]="";
	char regionidnamestr[30]="",stripidnamestr[30]="";
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	glometapath=get_state_glometapath();
	metapath=talloc(char,1000+30+30);
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","dictionary_strip_exists","NO memory");
		return FALSE;
	}
	metapath[0]='\0';
	U64toSTR(regionidstr,regionid);
	U64toSTR(stripidstr,stripid);

	file_regionstr(regionidnamestr,regionidstr);
	file_stripstr(stripidnamestr,stripidstr);

	strcat(metapath,glometapath);
	strcat(metapath,regionidnamestr);
	strcat(metapath,stripidnamestr);
	resTF=file_FILELAYER_dictionary_exists(metapath);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","dictionary_strip_exists","DICpath can't create");
		return FALSE;
	}
	free(metapath);
	return TRUE;
}
int file_FILELAYER_dictionary_stripsect_exists(UINT64 regionid,UINT64 stripid,UINT64 strsetid)
{
	int resTF;
	char regionidstr[20]="",stripidstr[20]="",strsetidstr[20]="";
	char regionidnamestr[30]="",stripidnamestr[30]="",strsetidnamestr[30]="";
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	glometapath=get_state_glometapath();
	metapath=talloc(char,1000+30+30+30);
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","dictionary_stripsect_exists","NO memory");
		return FALSE;
	}
	metapath[0]='\0';
	U64toSTR(regionidstr,regionid);
	U64toSTR(stripidstr,stripid);
	U64toSTR(strsetidstr,strsetid);

	file_regionstr(regionidnamestr,regionidstr);
	file_stripstr(stripidnamestr,stripidstr);
	file_stripsectstr(strsetidnamestr,strsetidstr);

	strcat(metapath,glometapath);
	strcat(metapath,regionidnamestr);
	strcat(metapath,stripidnamestr);
	strcat(metapath,strsetidnamestr);
	resTF=file_FILELAYER_dictionary_exists(metapath);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","dictionary_stripsect_exists","DICpath can't create");
		return FALSE;
	}
	free(metapath);
	return TRUE;
}
int file_FILELAYER_dictionary_filemeta_exists(UINT64 regionid,UINT64 fileid)
{
	int resTF;
	char fileidstr[20]="",regionidstr[20]="",regionidnamestr[30]="",filemetaidnamestr[30]="";
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ

	glometapath=get_state_glometapath();
	metapath=talloc(char,1000+30+30);
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","dictionary_filemeta_exists","NO memory");
		return FALSE;
	}
	//metapath[0]='\0';
	//����·��
	metapath[0]='\0';//�����ַ���
	U64toSTR(regionidstr,regionid);//��������id
	U64toSTR(fileidstr,fileid);

	file_regionstr(regionidnamestr,regionidstr);//����region�ַ���
	file_filemetastr(filemetaidnamestr,fileidstr);
	//file_filemetastr_name(filemetafilenamestr,fileidstr);//filemeta�ļ���

	//·��������һ��
	strcat(metapath,glometapath);//��Ԫ����·��ƴ����ȥ
	strcat(metapath,regionidnamestr);//��region�ַ���ƴ����ȥ
	strcat(metapath,filemetaidnamestr);//��filemeta��ƴ����ȥ
	//strcat(metapath,filemetafilenamestr);//��filename�ַ���ƴ����ȥ
	resTF=file_FILELAYER_dictionary_exists(metapath);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","dictionary_filemeta_exists","DICpath can't create");
		return FALSE;
	}
	free(metapath);
	return TRUE;
}
int file_FILELAYER_dictionary_userprofile_exists(UINT64 userid)
{
	int resTF;
	char userprofileidstr[20]="";
	char userprofileidnamestr[40]="";
	//char userprofilefilenamestr[50];
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	glometapath=get_state_glometapath();
	metapath=talloc(char,1000+40);
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","dictionary_userprofile_exists","NO memory");
		return FALSE;
	}
	metapath[0]='\0';
	U64toSTR(userprofileidstr,userid);

	file_userprofilestr(userprofileidnamestr,userprofileidstr);
	//file_userprofilestr_name(userprofilefilenamestr,userprofileidstr);

	strcat(metapath,glometapath);
	strcat(metapath,userprofileidnamestr);
	//strcat(metapath,userprofilefilenamestr);
	resTF=file_FILELAYER_dictionary_exists(metapath);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","dictionary_userprofile_exists","DICpath can't create");
		return FALSE;
	}
	free(metapath);
	return TRUE;
}
int file_FILELAYER_dictionary_device_exists(UINT64 deviceid)
{
	int resTF;
	char deviceidstr[20]="";
	char deviceidnamestr[30]="";
	//char devicefilenamestr[40];
	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ
	
	glometapath=get_state_glometapath();
	metapath=talloc(char,(1000+30+40));
	//metapath=glometapath;
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","dictionary_device_exist","No memory");
		return FALSE;
	}
	metapath[0]='\0';
	U64toSTR(deviceidstr,deviceid);

	file_devicestr(deviceidnamestr,deviceidstr);
	//file_devicestr_name(devicefilenamestr,deviceidstr);

	strcat(metapath,glometapath);
	strcat(metapath,deviceidnamestr);
	//strcat(metapath,devicefilenamestr);
	resTF=file_FILELAYER_dictionary_exists(metapath);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","dictionary_device_exist","DICpath can't create");
		return FALSE;
	}
	free(metapath);
	return TRUE;
}
int file_FILELAYER_dictionary_disk_exists(UINT64 deviceid,UINT64 diskid)
{
	int resTF;
	char deviceidstr[20]="";
	//char diskidstr[20];

	char deviceidnamestr[30]="";
	//char diskfilenamestr[40];

	char *metapath;//��ǰԪ����λ��
	char *glometapath;//ȫ��Ԫ���ݵ�ַ

	glometapath=get_state_glometapath();
	metapath=talloc(char,1000+40);
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","dictionary_disk_exists","NO memory");
		return FALSE;
	}
	metapath[0]='\0';
	
	U64toSTR(deviceidstr,deviceid);
	//U64toSTR(diskidstr,diskid);

	file_devicestr(deviceidnamestr,deviceidstr);
	//file_diskstr_name(diskfilenamestr,diskidstr);

	strcat(metapath,glometapath);
	strcat(metapath,deviceidnamestr);
	//strcat(metapath,diskfilenamestr);

	resTF=file_FILELAYER_dictionary_exists(metapath);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","dictionary_disk_exists","DICpath can't create");
		return FALSE;
	}
	free(metapath);
	return TRUE;
}
//��������
//��ȡ�ļ���ȡ�ļ���С��ָ�����ļ�����
INT64 file_FILELAYER_get_filesize(FILE *fp)
{
	UINT64 filesize;
	int resTF;
	resTF=fseek(fp,0L,SEEK_END);
	if(resTF==-1)
	{
		show_error("encoder","METALAYER_matedata","fseek fail");
		return FALSE;
	}
	filesize=ftell(fp);
	resTF=fseek(fp,0L,SEEK_SET);//������ͷ��
	if(resTF==-1)
	{
		show_error("encoder","METALAYER_matedata","fseek fail");
		return FALSE;
	}
	return filesize;
}

//д������ݽӿ�APIͨ��pushlist�������Ƿ���ʱд
//��Ҫͬ�����ݵ�ָ��
int file_chunk_write_API(CHUNK *chunkptr)
{
	int maxbuffersize,pushtime,resTF;

	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	//CHUNK *chunkptr;
	int chunknum,currentchunksize;
	BYTE *contentptr;

	GLOPUSHLIST *pushlistptr;
	int chunksize;

	//����pushlist

	pushlistptr=get_state_buffer_pushlist();

	maxbuffersize=pushlistptr->maxbuffersize;
	pushtime=pushlistptr->glopushtime;
	if((maxbuffersize==0)||(pushtime==0))
	{
		resTF=file_FILELAYER_CHUNK_WRITER_DATA(chunkptr);
		if(resTF==FALSE)
		{
			show_error("file","chunk_write_API","chunk can't write");
			return FALSE;
		}
		contentptr=chunkptr->chunkcontent;
		free(contentptr);
		chunkptr->chunkcontent=NULL;
		return TRUE;
	}
	//��Ȼ������
	chunksize=chunkptr->sizenum;

	chunkblockptr=pushlistptr->glopushchunklist;
	chunknum=pushlistptr->chunknum;
	if(chunknum==0||chunkblockptr==NULL)//chunknum=0����chunkgroupptr==NULL���ռ�
	{
		chunkblockptr=talloc(CHUNKBLOCK,chksize_MB(4));//��һ��4M�Ļ���ռ�
		if(chunkblockptr==NULL)
		{
			show_error("file","chunk_write_API","No memory");
			return FALSE;
		}
		chunkblockptr->chunkptr=chunkptr;
		chunkblockptr->chunkid=chunkptr->ChunkID;
		
		chunknum=1;
		//chunksize=chunkptr->sizenum;

		pushlistptr->currentbuffersize=chunksize;//��ǰ����
		pushlistptr->glopushchunklist=chunkblockptr;
		pushlistptr->chunknum=chunknum;
		
		return TRUE;
	}
	/*else
	{
		chunknum++;
		chunkblockptr=ralloc(CHUNKBLOCK,chunknum,chunkblockptr);
		if(chunkblockptr==NULL)
		{
			show_error("file","chunk_write_API","No memory");
			return FALSE;
		}
		curchunkblockptr=chunkblockptr+chunknum-1;//�ƶ�����ǰλ�ã���Ϊһ��ʼ�Ѿ���1�ˣ�����Ҫ��1
		curchunkblockptr->chunkid=chunkptr->ChunkID;
		curchunkblockptr->chunkptr=chunkptr;
	}*/
	

	currentchunksize=pushlistptr->currentbuffersize;
	currentchunksize=currentchunksize+chunksize;

	
	//������峬������ô�Ϳ���ͬ����
	if(currentchunksize>maxbuffersize)
	{
		resTF=file_FILELAYER_CHUNK_WRITER_DATA(chunkptr);//�Ƚ�����ͬ��
		if(resTF==FALSE)
		{
			show_error("file","chunk_write_API","chunk can't write");
			return FALSE;
		}
		//����Ҫͬ������
		resTF=profile_GLOBAL_chunk_data_sync();
		if(resTF==FALSE)
		{
			show_error("file","chunk_write_API","chunk can't synchronization");
			return FALSE;
		}
		//return TRUE;//ͬ����ɷ���
	}
	else
	{
		//��Ҫ������л���
		pushlistptr->currentbuffersize=currentchunksize;//����ǰ���ݽ��и�ֵ

		chunknum=pushlistptr->chunknum;//����
		
		curchunkblockptr=chunkblockptr+chunknum;//��ָ��
		chunknum=chunknum+1;

		curchunkblockptr->chunkptr=chunkptr;
		curchunkblockptr->chunkid=chunkptr->ChunkID;

		//�����ݽ������ݲ���
		pushlistptr->glopushchunklist=curchunkblockptr;
		pushlistptr->chunknum=chunknum;
	}
	return TRUE;
}