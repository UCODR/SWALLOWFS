#include "file.h"
//filelayer
int file_FILELAYER_intial()
{
	return TRUE;
}
//底层
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
//将数据流从路径的偏移量位置读取
int file_FILELAYER_BYTE_READER(char *filepath,BYTESTREAM *bstream,long offset)//将数据流写入制定路径插入,文件已经存在
{
	FILE *pfile;
	int bytesize,readsize,resTF;
	BYTE *bytestream;//返回到相应的数据串
	//读取相应的数据
	bytestream=bstream->BYTEcontent;
	bytesize=bstream->bytessize;
	//先打开一个文件用来读
	//分配缓冲空间
	if(bytestream!=NULL)
	{
		free(bytestream);

	}
	bytestream=talloc(BYTE,bytesize);//分配内存区域
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
	//设定偏移量
	resTF=fseek(pfile,offset,SEEK_SET);
	if(resTF!=0)
	{
		show_error("file_FILELAYER","BYTE_READER","offset is wrong");
		return FALSE;
	}
	//将数据读入相应位置
	readsize=fread(bytestream,sizeof(BYTE),bytesize,pfile);
	if(readsize!=bytesize)
	{
		show_error("file_FILELAYER","BYTE_READER","reading process wrong");
		return FALSE;
	}
	bstream->BYTEcontent=bytestream;
	fclose(pfile);//以免出现野指针
	return TRUE;
}
//将数据流写入制定路径偏移量插入
int file_FILELAYER_BYTE_WRITER(char *filepath,BYTESTREAM *bstream,long offset)//将数据流写入制定路径偏移量插入,文件已经存在
{
	FILE *pfile;
	int bytesize,writesize,resTF;
	BYTE *bytestream;//返回到相应的数据串
	//读取相应的数据
	bytestream=bstream->BYTEcontent;
	bytesize=bstream->bytessize;
	pfile=fopen(filepath,"rb+");
	if(pfile==NULL)
	{
		show_error("file","FILELAYER_BYTE_WRITER","FILE handle can't open");
		return FALSE;
	}
	//设定偏移量
	resTF=fseek(pfile,offset,SEEK_SET);
	if(resTF!=0)
	{
		show_error("file_FILELAYER","BYTE_READER","offset is wrong");
		return FALSE;
	}
	//将数据写入到相应位置
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
	BYTE *bytestream;//返回到相应的数据串
	//读取相应的数据
	bytestream=bstream->BYTEcontent;
	bytesize=bstream->bytessize;
	pfile=fopen(filepath,"wb");
	//将数据写入到相应位置
	//writesize=fwrite(bytestream,sizeof(BYTE),bytesize,pfile);
	//最快方法是直接攻偏移量
	writesize=fseek(pfile,bytesize,SEEK_SET);
	if(writesize!=0)
	{
		show_error("file_FILELAYER","BYTE_WRITER","write process failed");
		return FALSE;
	}
	fputc(0,pfile);//输入一个0

	fclose(pfile);
	return TRUE;
}
//region,strip,stripsect分块的生成
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
//数据操作 
//单个读操作，主要是根据id来读写
//其中chunk读写由于性能相关因此需要独立设计
//将CHUNK根据其中包含的路径读出到相应的区域,元数据部分
//将CHUNK根据全局路径和chunkpath读取元数据
int file_FILELAYER_CHUNK_READER_META(CHUNK *chk)
{
	UINT64 regionid;//chunk所在region编号
	UINT64 stripid;//chunk所在strip编号
	UINT64 stripsectid;//chunk所在stripsect编号
	UINT64 diskid;//chunk所在disk编号
	UINT64 deviceid;//chunk所在device编号
	UINT64 fileid;//chunk所在file编号
	CHUNKPATH *chkpath;
	//上级指针
	UINT64 chunkid;
	REGION *regionptr;
	STRIP *stripptr;
	STRIPSECT *strsetptr;
	char *metapath;//chunk元数据
	char *glometapath;//全局元数据地址

	char regionidstr[20]="";
	char stripidstr[20]="";
	char strsetidstr[20]="";
	char chunkidstr[20]="";
	char regionidnamestr[30]="",stripidnamestr[30]="",strsetidnamestr[30]="",chunkfilenamestr[40]="";//定义为30位stripset+/是10个字符
	int isparity,sizenum,storestate;//一些常量
	FILE *flin;//输入文件指针
	//开始赋值
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
	//安全性检查
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
	//开始进行存储状态监测
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
	//找到全局元数据地址
	glometapath=get_state_glometapath();//获取全局元数据指针
	metapath=talloc(char,(1000+30+30+30+40));//60位给路径
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//定义字符串
	//生成路径
	U64toSTR(regionidstr,regionid);
	U64toSTR(stripidstr,stripid);
	U64toSTR(strsetidstr,stripsectid);
	U64toSTR(chunkidstr,chunkid);
	//生成相应的字符串
	file_regionstr(regionidnamestr,regionidstr);//生成region字符串
	file_stripstr(stripidnamestr,stripidstr);//生成strip字符串
	file_stripsectstr(strsetidnamestr,strsetidstr);//生成stripsect字符串
	file_chunkstr_name(chunkfilenamestr,chunkidstr);//生成stripsect字符串

	//路径捆绑在一起
	strcat(metapath,glometapath);//将元数据路径拼接上去
	strcat(metapath,regionidnamestr);//将region字符串拼接上去
	strcat(metapath,stripidnamestr);//将strip字符串拼接上去
	strcat(metapath,strsetidnamestr);//将stripsect字符串拼接上去
	strcat(metapath,chunkfilenamestr);//将stripsect字符串拼接上去
	//开始读写
	
	flin=fopen(metapath,"r+");
	if(flin==NULL)
	{
		show_error("file_FILELAYER","CHUNK_READER","file can't open");
		return FALSE;
	}
	//开始从读取元数据
	//需要对比输入的写法
	/*
	fprintf(flout,"chunk id:%I64d\n",chkid);
	fprintf(flout,"the chunk is parity(0:FALSE,1:TRUE):%d\n",isparity);
	//路径可以不必输出
	fprintf(flout,"the chunk size:%d\n",sizenum);
	fprintf(flout,"region id:%I64d\n",regionid);
	fprintf(flout,"strip id:%I64d\n",stripid);
	fprintf(flout,"stripsect id:%I64d\n",stripsectid);
	fprintf(flout,"disk id:%I64d\n",diskid);
	fprintf(flout,"device id:%I64d\n",deviceid);
	fprintf(flout,"file id:%%I64d\n",fileid);
	//当前存储状态
	fprintf(flout,"stripsect state(countnum):%d\n",storestate);
	*/
	fscanf(flin,"chunk id:%I64d\n",&chunkid);
	fscanf(flin,"the chunk is parity(0:FALSE,>0:TRUE):%d\n",&isparity);
	//路径可以不必输出
	fscanf(flin,"the chunk size:%d\n",&sizenum);
	fscanf(flin,"region id:%I64d\n",&regionid);
	fscanf(flin,"strip id:%I64d\n",&stripid);
	fscanf(flin,"stripsect id:%I64d\n",&stripsectid);
	fscanf(flin,"disk id:%I64d\n",&diskid);
	fscanf(flin,"device id:%I64d\n",&deviceid);
	fscanf(flin,"file id:%I64d\n",&fileid);
	//当前存储状态
	fscanf(flin,"chunk state(countnum):%d\n",&storestate);
	//将读取元数据写回
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
	free(metapath);//释放元数据路径
	return TRUE;
}
//将CHUNK根据其中包含的路径读出到相应的区域,数据部分
int file_FILELAYER_CHUNK_READER_DATA(CHUNK *chk)
{
	CHUNKPATH *chkpath;//用于记录当前chunk的路径
	UINT64 chkid;//用户查找当前在块在文件中的偏移量
	char *strsetpath;//stripsect在文件系统中的路径
	int resTF;//stripsect中第几个块以及相应的偏移量
	long offset;//偏移量
	REGION *regionptr;//当前chunk所在region指针
	STRIP *stripptr;//当前chunk所在strip指针
	STRIPSECT *strsetptr;//当前CHUNK的条带分区
	int i,chkindex,chunksize;//每一个chunk的大小
	BYTESTREAM chkcontent; //chunk读取内容
	int chunknum;//当前stripsect中的chunk数
	UINT64 *chkidlist;//当前chunk编号列表
	UINT64 currentid;
	//对于指针进行赋值
	chkpath=chk->chkpath;
	regionptr=chkpath->regionptr;
	stripptr=chkpath->stripptr;
	strsetptr=chkpath->stripsectptr;

	//安全性检查
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
	//开始进行存储状态监测
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
	//开始赋值
	chkid=chk->ChunkID;

	strsetpath=strsetptr->filepath;//获取文件路径
	chunksize=chk->sizenum;
	chkcontent.bytessize=chk->sizenum;//将需要读取的数量
	chunknum=strsetptr->chunknum;
	chkidlist=strsetptr->chunkid;
	//开始分配内存读取区域
	chkcontent.BYTEcontent=talloc(BYTE,chunksize);
	//万事具备，开始计算偏移量
	chkindex=chkpath->chunkarrayid;//计算偏移量
	/*for(i=0;i<chunknum;i++)
	{
		currentid=chkidlist[i];//获取当前id
		if(currentid==chkid)
		{
			break;//跳出
		}
		chkindex++;//chkindex累加
	}*/
	if(chkindex==chunknum)
	{
		show_error("file_FILELAYER","CHUNK_READER","chunk id can't find out");
		return FALSE;
	}
	//开始计算偏移量
	offset=chkindex*chunksize;
	resTF=file_FILELAYER_BYTE_READER(strsetpath,&chkcontent,offset);//准备完毕读取
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","CHUNK_READER","can't read chunk content");
		return FALSE;
	}
	chk->chunkcontent=chkcontent.BYTEcontent;//将读取出数据进行赋值
	return TRUE;
}

//将STRIPSECT根据其中包含的路径读出到相应的区域
int file_FILELAYER_STRIPSECT_READER(STRIPSECT *strset)
{
		//仅仅需要读取元数据即可
	int i,chunksize;
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
	//UINT64 regionid,stripid,strsectid;//各种实体的编号
	UINT64 strsetid;//strset的编号
	REGION *regionptr;//区域指针
	STRIP *stripptr;//条带指针
	char regoinidstr[20]="",stripidstr[20]="",strsetidstr[20]="";//定义为20位的原因是2^64次方1.8*19^19
	char regionidnamestr[30]="",stripidnamestr[30]="",strsetidnamestr[30]="";//定义为30位stripset+/是10个字符
	char strsetfilename[40]="";
	/*
	UINT64 StripsectID;//STRIPSECT的id

	UINT64 *chunkid;//	其中包含的chunkid
	CHUNKGROUP *chunklist;//定义一个chunkgroup用具记录chunk组,作为一级chunk指针
	int chunksize;//chunk大小
	int chunknum;//包含的chunk数量总数

	UINT64 regionid;///属于的region编号
	struct REGION *regionptr;//上一级region指针

	UINT64 stripid;//属于的strip编号
	struct STRIP *stripptr;//上一级strip指针

	UINT64 diskid;//属于的disk编号
	struct DISK *diskptr;//上一级disk指针

	UINT64 deviceid;//属于的device编号
	struct DEVICE *deviceptr;//上一级device指针

	char *filename;//文件名
	//veronica中
	char *filepath;//文件名完整路径，这里等于disk中的路径和filename相加

	int storestate;//当前存储状态
	*/
	UINT64 *chunkid;//当前chunk的指针组
	int chunknum;//chunk数量
	int isparity;//校验位

	UINT64 regionid;//region编号

	UINT64 stripid;//strip编号

	UINT64 diskid;//当前存储器编号

	UINT64 deviceid;//设备编号

	char *filename;//文件名
	char *filepath;//文件路径

	int storestate; //当前存储状态

	FILE *flin;
	//先申请空间
	filename=talloc(char,60);//文件名
	if(filename==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_READER","no memory");
		return FALSE;
	}
	filepath=talloc(char,200);//文件路径
	if(filepath==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_READER","no memory");
		return FALSE;
	}
	//指针赋值
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
	//开始进行存储状态监测
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
	//找到全局元数据地址
	glometapath=get_state_glometapath();//获取全局元数据指针
	//元数据位置
	metapath=talloc(char,(30+30+30+40+1000));//1000位给路径
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_READER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//定义字符串
	//开始进行文件元数据路径计算
	U64toSTR(regoinidstr,regionid);//生成区域id
	U64toSTR(stripidstr,stripid);//生成条带id
	U64toSTR(strsetidstr,strsetid);//生成条带分区id

	file_regionstr(regionidnamestr,regoinidstr);//生成region字符串
	file_stripstr(stripidnamestr,stripidstr);//生成strip字符串
	file_stripsectstr(strsetidnamestr,strsetidstr);//生成stripsect字符串
	file_stripsectstr_name(strsetfilename,strsetidstr);//生成stripsect的文件名

	//路径捆绑在一起
	strcat(metapath,glometapath);//将元数据路径拼接上去
	strcat(metapath,regionidnamestr);//将region字符串拼接上去
	strcat(metapath,stripidnamestr);//将strip字符串拼接上去
	strcat(metapath,strsetidnamestr);//将stripsect字符串拼接上去
	strcat(metapath,strsetfilename);//将stripsect的文件名拼接上去

	flin=fopen(metapath,"r+");//打开元数据用于读取
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
		fprintf(flout,"%I64d\n",chunkid[i]);//将chunk编号输出到元数据文件中
	}
	//上层id号写入
	fprintf(flout,"region id:%I64d\n",regionid);
	fprintf(flout,"strip id:%I64d\n",stripid);
	fprintf(flout,"disk id:%I64d\n",diskid);
	fprintf(flout,"device id:%I64d\n",deviceid);

	//将数据文件路径写入
	fprintf(flout,"store filename:%s\n",filename);
	fprintf(flout,"store filepath:%s\n",filepath);
	//当前存储状态
	fprintf(flout,"stripsect state(countnum):%d\n",storestate);
	fclose(flout);
	free(metapath);//最后释放路径信息*/
	//参考输出生成输入
	fscanf(flin,"the stripset id: %I64d\n",&strsetid);//chunk的基本信息
	fscanf(flin,"the stripsect is parity(0:FALSE,>0:TRUE):%d\n",&isparity);
	fscanf(flin,"the chunksize:%d\n",&chunksize);
	fscanf(flin,"there are: %d chunks, chunk id list:\n",&chunknum);
	chunkid=talloc(UINT64,chunknum);
	for(i=0;i<chunknum;i++)
	{
		fscanf(flin,"%I64d\n",&chunkid[i]);//将chunk编号输出到元数据文件中
	}
	//上层id号写入
	fscanf(flin,"region id:%I64d\n",&regionid);
	fscanf(flin,"strip id:%I64d\n",&stripid);
	fscanf(flin,"disk id:%I64d\n",&diskid);
	fscanf(flin,"device id:%I64d\n",&deviceid);
	//将数据文件路径写入
	fscanf(flin,"store filename:%s\n",filename);
	fscanf(flin,"store filepath:%s\n",filepath);
	//当前存储状态
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
	free(metapath);//最后释放路径信息
	return TRUE;
}

//将STRIP根据其中包含的路径读出到相应的区域;这里需要通过stripdes中查找
int file_FILELAYER_STRIP_READER(STRIP *str)
{
	//读取一个条带信息
	UINT64 stripid,*diskid,*deviceid,*strsetid,*chunkid,regionid;
	int i,disknum,devicenum,strsetnum,chunknum,storestate;
	//REGION *regionptr;
	STRIPDES *strdes;
	char regoinidstr[20]="",stripidstr[20]="";
	char regionidnamestr[30]="",stripidnamestr[30]="";
	char stripfilenamestr[40]="";
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
	FILE *flin;
	
	strdes=talloc(STRIPDES,1);
	if(strdes==NULL)
	{
		show_error("file_FILELAYER","STRIP_READER","No memory");
		return FALSE;
	}

	glometapath=get_state_glometapath();//获取全局元数据指针
	//元数据位置
	metapath=talloc(char,(30+30+40+1000));//1000位给路径
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","STRIP_READER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//定义字符串
	regionid=str->regionid;
	stripid=str->StripID;
	//开始进行文件元数据路径计算
	U64toSTR(regoinidstr,regionid);//生成区域id
	U64toSTR(stripidstr,stripid);//生成条带id

	file_regionstr(regionidnamestr,regoinidstr);//生成region字符串
	file_stripstr(stripidnamestr,stripidstr);//上层strip文件夹
	file_stripstr_name(stripfilenamestr,stripidstr);//生成strip字符串

	//路径捆绑在一起
	strcat(metapath,glometapath);//将元数据路径拼接上去
	strcat(metapath,regionidnamestr);//将region字符串拼接上去
	strcat(metapath,stripidnamestr);//将strip字符串拼接上去
	strcat(metapath,stripfilenamestr);//strip文件名拼接上去
	//生成句柄
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
	diskid=talloc(UINT64,disknum);//开空间
	if(diskid==NULL)
	{
		show_error("file_FILELAYER","STRIP_READER","No memory");
		return FALSE;
	}
	for(i=0;i<disknum;i++)//由于des中内容与strip中相同写一个分
	{
		fscanf(flin,"%I64d\n",&diskid[i]);
	}
	fscanf(flin,"there are %d devices,device id list:\n",&devicenum);
	deviceid=talloc(UINT64,devicenum);//开空间
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
	strsetid=talloc(UINT64,strsetnum);//开空间
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
	chunkid=talloc(UINT64,chunknum);//开空间
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
	free(metapath);//最后释放路径信息
	return TRUE;
}

//将REGION读取相应数据
int file_FILELAYER_REGION_READER(REGION *reg)
{
	//读取一个region的信息
	UINT64 regionid;
	CODEPARA *codepara;
	UINT64 *fileid,*diskid,*deviceid,*stripid,rootfileid,totalsize,chunknum,stripsectnum;//不同的全局
	int i,codetype,filenum,disknum,devicenum,stripnum,storestate;
	STRIPDES *strdes;
	//CODEPARA *codepara;
	char regoinidstr[20]="";
	char regionidnamestr[30]="";
	char regionfilenamestr[40]="";
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
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
	//计算地址
	glometapath=get_state_glometapath();//获取全局元数据指针
	//元数据位置
	metapath=talloc(char,(30+40+1000));//1000位给路径
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","REGION_READER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//定义字符串
	regionid=reg->RegionID;
	//开始进行文件元数据路径计算
	U64toSTR(regoinidstr,regionid);//生成区域id

	file_regionstr(regionidnamestr,regoinidstr);//生成region字符串
	file_regionstr_name(regionfilenamestr,regoinidstr);//上层strip文件夹

	//路径捆绑在一起
	strcat(metapath,glometapath);//将元数据路径拼接上去
	strcat(metapath,regionidnamestr);//将region字符串拼接上去
	strcat(metapath,regionfilenamestr);//将region的文件名拼接上去
	//打开文件句柄
	flin=fopen(metapath,"r+");
	if(flin==NULL)
	{
		show_error("file_FILELAYER","REGION_READER","fptr can't create");
		return FALSE;
	}
	//开始输出
	fscanf(flin,"region id:%I64d\n",&regionid);
	//开始输出内容
	fscanf(flin,"code type(code):%d,the parameter list:\n",&codetype);
	fscanf(flin,"the galois field:%d\n",&codepara->w);
	fscanf(flin,"data disk num:%d\n",&codepara->datanum);
	fscanf(flin,"code disk num:%d\n",&codepara->codenum);
	fscanf(flin,"total disk num:%d\n",&codepara->totnum);
	fscanf(flin,"provider num:%d\n",&codepara->pronum);
	fscanf(flin,"sector number:%d\n",&codepara->sectornum);
	//总大小
	fscanf(flin,"total size of region:%I64d\n",&totalsize);
	fscanf(flin,"there are %d files,file id list:\n",&filenum);
	fileid=talloc(UINT64,filenum);//开空间
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
	diskid=talloc(UINT64,disknum);//开空间
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
	deviceid=talloc(UINT64,devicenum);//开空间
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
	stripid=talloc(UINT64,stripnum);//开空间
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
	//开始赋值
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
	free(metapath);//最后释放路径信息
	return TRUE;
}

//将DISK读取到相应数据
int file_FILELAYER_DISK_READER(DISK *disk)
{
	//读取一个disk的信息
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

	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
	FILE *flin;

	diskid=disk->DiskID;
	deviceid=disk->deviceid;
	diskpath=talloc(char,1000);
	if(diskpath==NULL)
	{
		show_error("file_FILELAYER","DISK_WRITER","No memory");
		return FALSE;
	}
	//开始disk读取
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
	regionid=talloc(UINT64,regionnum);//开空间
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

//将DISK读取到相应数据
int file_FILELAYER_DEVICE_READER(DEVICE *device)
{
	//读取一个device的信息
	UINT64 deviceid,*diskid,*regionid;
	int devicetype,processnum,disknum,regionnum;
	int *speed;
	int i,storestate;
	char deviceidstr[20]="";
	char deviceidnamestr[30]="";
	char devicefilenamestr[40]="";
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
	FILE *flin;

	deviceid=device->DeviceID;
	//开始读取数据
	//由于是磁盘文件是全局性的,因此metapath=glometapath
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

//将DEVICE读取到相应数据
int file_FILELAYER_FILEMETA_READER(FILEMETA *fmeta)
{
	//读取一个filemeta的信息
	//fmeta信息
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

	//filechunkinf信息
	//FILEINF *filechunkinf;
	UINT64 *chunkid;
	CHUNKPATH *chunkpath,*curchunkpath;
	int chunknum;//chunk数量

	UINT64 regionid;//属于的region的编号

	UINT64 *deviceid;//设备id
	int devicenum;//设备数

	UINT64 *diskid;//存储器id列表
	int disknum;//存储器数量

	UINT64 *stripid;//条带id列表
	int stripnum;//条带数量

	UINT64 *stripsectid;///条带分区id列表
	int stripsectnum;//条带分区数量

	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
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
	filechunkinf=talloc(FILEINF,1);//分配一个空间
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
	
	//读取必要信息
	fileid=fmeta->FileID;
	regionid=fmeta->regionid;
	glometapath=get_state_glometapath();//获取全局元数据指针
	//开始计算路径
	metapath=talloc(char,1000+30+30+40);
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//定义字符串
	//flin=fopen(metapath,"r+");
	//生成路径
	U64toSTR(regionidstr,regionid);
	U64toSTR(fileidstr,fileid);
	
	//生成相应的字符串
	file_regionstr(regionidnamestr,regionidstr);//生成region字符串
	file_filemetastr(filemetaidnamestr,fileidstr);
	file_filemetastr_name(filemetafilenamestr,fileidstr);//filemeta文件名

	//路径捆绑在一起
	strcat(metapath,glometapath);//将元数据路径拼接上去
	strcat(metapath,regionidnamestr);//将region字符串拼接上去
	strcat(metapath,filemetaidnamestr);//将filemeta号拼接上去
	strcat(metapath,filemetafilenamestr);//将filename字符串拼接上去

	flin=fopen(metapath,"r+");//打开元数据用于读取
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
	//创建修改时间
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
	//创建修改时间
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
			//这里同时也输出chunkpath
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
		fprintf(flout,"%I64d\n",stripid);//条带id列表
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
		//不存在存储数据直接返回即可
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
		filechunkinf=NULL;//直接写上没有
		fmeta->filechunkinf=filechunkinf;//将最后一个赋值回去
		free(metapath);
		fclose(flin);//释放不必要的指针
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
		//这里同时也读取chunkpath
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
		fscanf(flin,"%I64d\n",&stripid[i]);//条带id列表
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

	fmeta->filechunkinf=filechunkinf;//将最后一个赋值回去
	free(metapath);
	fclose(flin);//释放不必要的指针
	return TRUE;
}

//将USERPROFILE读取到相应数据
int file_FILELAYER_USERPROFILE_READER(USERPROFILE *pfile)
{
	UINT64 userid,DICid;
	char *username,*password,*DICpath;
	//USERLOCATION *userlocinf;
	int userprivil;
	struct tm *createtime;
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
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
	//读取全局元数据
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
//由于全局文件只有一个无需group处理
//将用户信息读取到相应数据
int file_FILELAYER_GLOSYSTEMID_READER(GLOSYSTEMID *glosysid)
{
	UINT64 *regionidlist,*useridlist,*deviceidlist,*diskidlist,glomaxbuffersize;
	int i,regionnum,usernum,devicenum,disknum;

	IDITEM *systemnextid;
	//UINT64 chunkidlist;
	int *availkind;//现存编码类型
	int availnum,glopushtime;//编码类型总数

	char glofilename[40]="";
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
	FILE *flin;
	//获取元数据地址
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
	//输出当前id号
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
	//输出类别数
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

	//输出push时间
	//glopushtime=get_state_buffer_push_time();
	fscanf(flin,"the push time of system is %d time uints\n",&glopushtime);
	fscanf(flin,"the push maximum buffer size is %I64d BYTE\n",&glomaxbuffersize);
	//开始赋值
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

//组块读取
//将CHUNKGROUP根据其中包含的路径读取到相应的区域,元数据部分
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
//将CHUNKGROUP根据其中包含的路径读取到相应的区域,数据部分
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
//将STRIPSECTGROUP根据其中包含的路径读取到相应的区域
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
//将STRIPGROUP根据其中包含的路径读取到相应的区域;这里需要通过stripdes中查找
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
//将REGIONGROUP读取到相应位置
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
//将DISKGROUP读取到相应位置
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
//将DEVICEGROUP读取到相应位置
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
//将FILEMETAGROUP读取到相应位置
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
//将USERPROFILEGROUP读取相应数据
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



//单个写操作,写入磁盘
//将CHUNK根据其中包含的路径写入到相应的区域
int file_FILELAYER_CHUNK_WRITER_META(CHUNK *chk)
{
	/*	
	UINT64 ChunkID;//块编号

	int isparity;//是否是校验块
	struct CHUNKPATH *chkpath;//chunk路径

	int sizenum;//字节数
	BYTE* chunkcontent;//主要原因是chunk的大小是以byte为单位

	UINT64 regionid;//属于的region编号
	struct REGION *regionptr;//上一级region的指针

	UINT64 stripid;//条带id号
	struct STRIP *stripptr;//上一级strip的指针

	UINT64 stripsectid;//条带分区id号
	struct STRIPSECT *stripsectptr;//上一级stripsect的指针

	UINT64 diskid;//属于磁盘的ID
	struct DISK *diskptr;//上一级disk的指针

	UINT64 deviceid;//属于设备的ID
	struct DEVICE *deviceptr;//上一级device的指针

	UINT64 fileid;//文件序号
	struct FILEMETA *fmeta;//文件元数据

	int storestate;//当前块存储状态
	*/
	UINT64 chkid;//chunk编号
	CHUNKPATH *chkpath;//路径
	UINT64 regionid,stripid,stripsectid,deviceid,diskid,fileid;//id大全
	int resTF,isparity,sizenum,storestate;
	REGION *regionptr;//区域指针
	STRIP *stripptr;//条带指针
	STRIPSECT *strsetptr;//条带分片指针
	char regoinidstr[20]="",stripidstr[20]="",strsetidstr[20]="",chkidstr[20]="";//id号字符串区域
	char regionnamestr[30]="",stripidnamestr[30]="",strsetidnamestr[30]="",chkfilenamestr[40]="";//当前各个分片
	char *glometapath;// 生成全局
	char *metapath;
	FILE *flout;
	//获取指正
	chkpath=chk->chkpath;
	regionptr=chkpath->regionptr;
	stripptr=chkpath->stripptr;
	strsetptr=chkpath->stripsectptr;
	//开始进行安全监测
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
	//开始进行存储状态监测
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
	//开始赋值
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
	//当前数据写入元数据
	//计算元数据位置
	glometapath=get_state_glometapath();//获取全局元数据指针
	metapath=talloc(char,(30+30+30+40+1000));//1000位给路径
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//定义字符串
	U64toSTR(regoinidstr,regionid);//生成区域id
	U64toSTR(stripidstr,stripid);//生成条带id
	U64toSTR(strsetidstr,stripsectid);//生成条带分区id
	U64toSTR(chkidstr,chkid);//生成条带分区id

	file_regionstr(regionnamestr,regoinidstr);//生成region字符串
	file_stripstr(stripidnamestr,stripidstr);//生成strip字符串
	file_stripsectstr(strsetidnamestr,strsetidstr);//生成stripsect字符串
	file_chunkstr_name(chkfilenamestr,chkidstr);//生成

	//路径捆绑在一起
	strcat(metapath,glometapath);//将元数据路径拼接上去
	strcat(metapath,regionnamestr);//将region字符串拼接上去
	strcat(metapath,stripidnamestr);//将strip字符串拼接上去
	strcat(metapath,strsetidnamestr);//将stripsect字符串拼接上去
	strcat(metapath,chkfilenamestr);//将stripsect字符串拼接上去
	resTF=file_FILELAYER_dictionary_stripsect_exists(regionid,stripid,stripsectid);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","dictionary can't create");
		return FALSE;
	}
	flout=fopen(metapath,"w+");//打开元数据用于写入
	if(flout==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","fptr can't create");
		return FALSE;
	}
	/*	
	UINT64 ChunkID;//块编号

	int isparity;//是否是校验块
	struct CHUNKPATH *chkpath;//chunk路径

	int sizenum;//字节数
	BYTE* chunkcontent;//主要原因是chunk的大小是以byte为单位

	UINT64 regionid;//属于的region编号
	struct REGION *regionptr;//上一级region的指针

	UINT64 stripid;//条带id号
	struct STRIP *stripptr;//上一级strip的指针

	UINT64 stripsectid;//条带分区id号
	struct STRIPSECT *stripsectptr;//上一级stripsect的指针

	UINT64 diskid;//属于磁盘的ID
	struct DISK *diskptr;//上一级disk的指针

	UINT64 deviceid;//属于设备的ID
	struct DEVICE *deviceptr;//上一级device的指针

	UINT64 fileid;//文件序号
	struct FILEMETA *fmeta;//文件元数据

	int storestate;//当前块存储状态
	*/
	fprintf(flout,"chunk id:%I64d\n",chkid);
	fprintf(flout,"the chunk is parity(0:FALSE,>0:TRUE):%d\n",isparity);
	//路径可以不必输出
	fprintf(flout,"the chunk size:%d\n",sizenum);
	fprintf(flout,"region id:%I64d\n",regionid);
	fprintf(flout,"strip id:%I64d\n",stripid);
	fprintf(flout,"stripsect id:%I64d\n",stripsectid);
	fprintf(flout,"disk id:%I64d\n",diskid);
	fprintf(flout,"device id:%I64d\n",deviceid);
	fprintf(flout,"file id:%I64d\n",fileid);
	//当前存储状态
	fprintf(flout,"chunk state(countnum):%d\n",storestate);
	free(metapath);
	fclose(flout);
	return TRUE;
}
int file_FILELAYER_CHUNK_WRITER_DATA(CHUNK *chk)
{
	CHUNKPATH *chkpath;//用于记录当前chunk的路径
	UINT64 chkid;//用户查找当前在块在文件中的偏移量
	char *strsetpath;//stripsect在文件系统中的路径
	int resTF;//stripsect中第几个块以及相应的偏移量
	long offset;//偏移量
	REGION *regionptr;//当前chunk所在region指针
	STRIP *stripptr;//当前chunk所在strip指针
	STRIPSECT *strsetptr;//当前CHUNK的条带分区
	int i,chkindex,chunksize;//每一个chunk的大小
	BYTESTREAM chkcontent; //chunk写入内容
	int chunknum;//当前stripsect中的chunk数
	UINT64 *chkidlist;//当前chunk编号列表
	UINT64 currentid;
	//读取数据
	chkid=chk->ChunkID;//找到CHUNK编号
	chkpath=chk->chkpath;//先将chunk路径取出
	chkcontent.BYTEcontent=chk->chunkcontent;//chunk内容
	chkcontent.bytessize=chk->sizenum;//中间信息数量
	//需要写入的数据串
	regionptr=chkpath->regionptr;
	stripptr=chkpath->stripptr;
	strsetptr=chkpath->stripsectptr;
	//开始进行安全监测
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
	//开始进行存储状态监测
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
	strsetpath=strsetptr->filepath;//获取stripsect中文件存储路径
	chunknum=strsetptr->chunknum;//获取chunk数
	chkidlist=strsetptr->chunkid;//获取chunkid
	chunksize=chk->sizenum;//当前chunk字节数
	chkindex=chkpath->chunkarrayid;//因为从0开始
	/*for(i=0;i<chunknum;i++)
	{
		currentid=chkidlist[i];//获取当前id
		if(currentid==chkid)
		{
			break;//跳出
		}
		chkindex++;//chkindex累加
	}*/
	if(chkindex==chunknum)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","chunk id can't find out");
		return FALSE;
	}
	//开始计算偏移量
	offset=chkindex*chunksize;
	resTF=file_FILELAYER_BYTE_WRITER(strsetpath,&chkcontent,offset);//准备完毕写入
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","CHUNK_WRITER","can't write chunk content");
		return FALSE;
	}
	return TRUE;
}
int file_FILELAYER_STRIPSECT_CREATE(STRIPSECT *strset)
{
	UINT64 regionid,stripid,strsetid;//各种实体的编号
	BYTESTREAM bstream;//byte串
	REGION *regionptr;//区域指针
	STRIP *stripptr;//条带指针
	char *pathstr;//当前stripsect的路径
	int chunknum,chunksize,strsetsize;//用于计算strset大小
	//开始赋值
	strsetid=strset->StripsectID;
	regionid=strset->regionid;
	regionptr=strset->regionptr;
	stripid=strset->stripid;
	stripptr=strset->stripptr;
	//计算stripsect大小
	chunknum=strset->chunknum;
	chunksize=strset->chunksize;
	strsetsize=chunknum*chunksize;
	//安全性检测
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
	//读取路径
	pathstr=strset->filepath;
	//计算文件大小
	bstream.BYTEcontent=NULL;
	bstream.bytessize=strsetsize;
	//开始生成相应的文件块
	file_FILELAYER_BYTE_CREATE(pathstr,&bstream);
	return TRUE;
}
//将STRIPSECT根据其中包含的路径写入到相应的区域
int file_FILELAYER_STRIPSECT_WRITER(STRIPSECT *strset)
{
	//仅仅需要读取元数据即可
	int i,chunksize;
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
	//UINT64 regionid,stripid,strsectid;//各种实体的编号
	UINT64 strsetid;//strset的编号
	REGION *regionptr;//区域指针
	STRIP *stripptr;//条带指针
	char regoinidstr[20]="",stripidstr[20]="",strsetidstr[20]="";//定义为20位的原因是2^64次方1.8*19^19
	char regionnamestr[30]="",stripidnamestr[30]="",stripsectnamestr[30]="",strsetfilename[40]="";//定义为30位stripset+/是10个字符
	/*
	UINT64 StripsectID;//STRIPSECT的id

	UINT64 *chunkid;//	其中包含的chunkid
	CHUNKGROUP *chunklist;//定义一个chunkgroup用具记录chunk组,作为一级chunk指针
	int chunksize;//chunk大小
	int chunknum;//包含的chunk数量总数

	UINT64 regionid;///属于的region编号
	struct REGION *regionptr;//上一级region指针

	UINT64 stripid;//属于的strip编号
	struct STRIP *stripptr;//上一级strip指针

	UINT64 diskid;//属于的disk编号
	struct DISK *diskptr;//上一级disk指针

	UINT64 deviceid;//属于的device编号
	struct DEVICE *deviceptr;//上一级device指针

	char *filename;//文件名
	//veronica中
	char *filepath;//文件名完整路径，这里等于disk中的路径和filename相加

	int storestate;//当前存储状态
	*/
	//相关元数据信息
	UINT64 *chunkid;//当前chunk的指针组
	int chunknum,isparity;//chunk数量

	UINT64 regionid;//region编号

	UINT64 stripid;//strip编号

	UINT64 diskid;//当前存储器编号

	UINT64 deviceid;//设备编号

	char *filename;//文件名
	char *filepath;//文件路径

	int resTF,storestate; //当前存储状态

	FILE *flout;
	

	//计算当前元数位置
	strsetid=strset->StripsectID;
	//块id列表
	isparity=strset->isparity;
	chunkid=strset->chunkid;
	chunksize=strset->chunksize;
	chunknum=strset->chunknum;
	//获取相应的信息
	regionid=strset->regionid;
	stripid=strset->stripid;
	regionptr=strset->regionptr;
	stripptr=strset->stripptr;
	diskid=strset->diskid;
	deviceid=strset->deviceid;
	//文件路径
	filename=strset->filename;
	filepath=strset->filepath;
	//存储状态
	storestate=strset->storestate;
	//安全性检测
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
	//开始进行存储状态监测
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

	//找到全局元数据地址
	glometapath=get_state_glometapath();//获取全局元数据指针
	//元数据位置
	metapath=talloc(char,(30+30+30+40+1000));//1000位给路径
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//定义字符串
	//开始进行文件元数据路径计算
	U64toSTR(regoinidstr,regionid);//生成区域id
	U64toSTR(stripidstr,stripid);//生成条带id
	U64toSTR(strsetidstr,strsetid);//生成条带分区id

	file_regionstr(regionnamestr,regoinidstr);//生成region字符串
	file_stripstr(stripidnamestr,stripidstr);//生成strip字符串
	file_stripsectstr(stripsectnamestr,strsetidstr);//生成stripsect字符串
	file_stripsectstr_name(strsetfilename,strsetidstr);//生成文件名

	//路径捆绑在一起
	strcat(metapath,glometapath);//将元数据路径拼接上去
	strcat(metapath,regionnamestr);//将region字符串拼接上去
	strcat(metapath,stripidnamestr);//将strip字符串拼接上去
	strcat(metapath,stripsectnamestr);//将stripsect字符串拼接上去
	strcat(metapath,strsetfilename);//将文件名加上
	
	//现在metapath有了那么就可以
	/*
	UINT64 StripsectID;//STRIPSECT的id

	UINT64 *chunkid;//	其中包含的chunkid
	CHUNKGROUP *chunklist;//定义一个chunkgroup用具记录chunk组,作为一级chunk指针
	int chunksize;//chunk大小
	int chunknum;//包含的chunk数量总数

	UINT64 regionid;///属于的region编号
	struct REGION *regionptr;//上一级region指针

	UINT64 stripid;//属于的strip编号
	struct STRIP *stripptr;//上一级strip指针

	UINT64 diskid;//属于的disk编号
	struct DISK *diskptr;//上一级disk指针

	UINT64 deviceid;//属于的device编号
	struct DEVICE *deviceptr;//上一级device指针

	char *filename;//文件名
	//veronica中
	char *filepath;//文件名完整路径，这里等于disk中的路径和filename相加

	int storestate;//当前存储状态
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
	fprintf(flout,"the stripset id: %I64d\n",strsetid);//当前stripsect的编号
	fprintf(flout,"the stripsect is parity(0:FALSE,>0:TRUE):%d\n",isparity);
	fprintf(flout,"the chunksize:%d\n",chunksize);//其中每一个chunk的大小
	fprintf(flout,"there are: %d chunks, chunk id list:\n",chunknum);
	for(i=0;i<chunknum;i++)
	{
		fprintf(flout,"%I64d\n",chunkid[i]);//将chunk编号输出到元数据文件中
	}
	//上层id号写入
	fprintf(flout,"region id:%I64d\n",regionid);
	fprintf(flout,"strip id:%I64d\n",stripid);
	fprintf(flout,"disk id:%I64d\n",diskid);
	fprintf(flout,"device id:%I64d\n",deviceid);

	//将数据文件路径写入
	fprintf(flout,"store filename:%s\n",filename);
	fprintf(flout,"store filepath:%s\n",filepath);
	//当前存储状态
	fprintf(flout,"stripsect state(countnum):%d\n",storestate);
	fclose(flout);
	free(metapath);//最后释放路径信息
	return TRUE;
}
//将STRIPSECT根据其中包含的路径写入到相应的区域;这里需要通过stripdes中查找
int file_FILELAYER_STRIP_WRITER(STRIP *str)
{
	/*
	UINT64 StripID;//信息

	STRIPDES *strdes;//条带描述，stripdes中chunk数*stripdes中磁盘数=整体包含的chunk数
	
	struct DISKGROUP *disklist;//存储器列表
	UINT64 *diskid;//包含的存储器id
	int disknum;//包含存储器个数
	
	struct DEVICEGROUP *devicelist;//设备列表
	UINT64 *deviceid;//设备id
	int devicenum;//设备数

	STRIPSECTGROUP *stripsectlist;//stripsect指针
	UINT64 *stripsectid;//stripsect的id
	int strsetnum;//Strset的数量

	CHUNKGROUP *chunklist;//定义一个chunkgroup用具记录chunk组,作为一级chunk指针
	UINT64 *chunkid;//	其中包含的chunkid
	int chunknum;//包含的chunk数量

	UINT64 regionid;//属于的region编号
	struct REGION *regionptr;//上一级region指针

	int storestate;//当前存储状态
	*/
	UINT64 stripid,*diskid,*deviceid,*strsetid,*chunkid,regionid;
	int i,disknum,devicenum,strsetnum,chunknum,storestate,resTF;
	REGION *regionptr;
	STRIPDES *strdes;
	char regoinidstr[20]="",stripidstr[20]="";
	char regionidnamestr[30]="",stripidnamestr[30]="";
	char stripfilenamestr[40]="";
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
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
	//现在开始赋值
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
	//存储状态
	storestate=str->storestate;

	glometapath=get_state_glometapath();//获取全局元数据指针
	//元数据位置
	metapath=talloc(char,(30+30+40+1000));//1000位给路径
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//定义字符串
	//开始进行文件元数据路径计算
	U64toSTR(regoinidstr,regionid);//生成区域id
	U64toSTR(stripidstr,stripid);//生成条带id

	file_regionstr(regionidnamestr,regoinidstr);//生成region字符串
	file_stripstr(stripidnamestr,stripidstr);//上层strip文件夹
	file_stripstr_name(stripfilenamestr,stripidstr);//生成strip字符串

	//路径捆绑在一起
	strcat(metapath,glometapath);//将元数据路径拼接上去
	strcat(metapath,regionidnamestr);//将region字符串拼接上去
	strcat(metapath,stripidnamestr);//将strip字符串拼接上去
	strcat(metapath,stripfilenamestr);//strip文件名拼接上去
	
	//可以开始写入元数据了
	/*
	UINT64 StripID;//信息

	STRIPDES *strdes;//条带描述，stripdes中chunk数*stripdes中磁盘数=整体包含的chunk数
	
	struct DISKGROUP *disklist;//存储器列表
	UINT64 *diskid;//包含的存储器id
	int disknum;//包含存储器个数

	struct DEVICEGROUP *devicelist;//设备列表
	UINT64 *deviceid;//设备id
	int devicenum;//设备数

	STRIPSECTGROUP *stripsectlist;//stripsect指针
	UINT64 *stripsectid;//stripsect的id
	int strsetnum;//Strset的数量

	CHUNKGROUP *chunklist;//定义一个chunkgroup用具记录chunk组,作为一级chunk指针
	UINT64 *chunkid;//	其中包含的chunkid
	int chunknum;//包含的chunk数量

	UINT64 regionid;//属于的region编号
	struct REGION *regionptr;//上一级region指针

	int storestate;//当前存储状态
	*/
	//需要先检测文件夹是否存在
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
	for(i=0;i<disknum;i++)//由于des中内容与strip中相同写一个分
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
	free(metapath);//最后释放路径信息
	return TRUE;
}
//将region写入相应位置;这里需要通过region到disk中查找
int file_FILELAYER_REGION_WRITER(REGION *reg)
{
	/*
	UINT64 RegionID;//region的id
	int codetype;//编码类型
	CODEPARA *codepara;//编码参数
	UINT64 totalsize;//总存储空间大小字节为大小，NODEF代表无限大直至占满

	struct FILEMETAGROUP *filemetalist;//文件元数据列表
	UINT64 *fileid;//包括的file的编号列表
	int filenum;//strip数量

	DISKGROUP *disklist;//Disk列表
	UINT64 *diskid;//Disk的编号列表
	int disknum;//磁盘的个数

	DEVICEGROUP *devicelist;//device列表
	UINT64 *deviceid;//设备id列表
	int devicenum;//设备数量

	STRIPDES *strdes;//对于条带的描述
	STRIPGROUP *striplist;//Strip列表
	UINT64 *stripid;//条带id列表
	int stripnum;//条带个数

	struct FILEMETA *fileroot;//当前区域的文件的根指针
	UINT64 rootfileid;//根文件编号

	int storestate;//当前存储状态
	*/
	UINT64 regionid;
	CODEPARA *codepara;
	UINT64 *fileid,*diskid,*deviceid,*stripid,rootfileid,totalsize,chunknum,stripsectnum;//不同的全局
	int i,codetype,filenum,disknum,devicenum,stripnum,storestate,resTF;
	STRIPDES *strdes;
	char regoinidstr[20]="";
	char regionidnamestr[30]="";
	char regionfilenamestr[40]="";
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
	FILE *flout;

	//region无需安全性检查
	//开始赋值
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

	glometapath=get_state_glometapath();//获取全局元数据指针
	//元数据位置
	metapath=talloc(char,(30+40+1000));//1000位给路径
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","STRIPSECT_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//定义字符串
	//开始进行文件元数据路径计算
	//printf("%I64d",regionid);
	U64toSTR(regoinidstr,regionid);//生成区域id
	
	file_regionstr(regionidnamestr,regoinidstr);//生成region字符串
	file_regionstr_name(regionfilenamestr,regoinidstr);//上层strip文件夹

	//路径捆绑在一起
	strcat(metapath,glometapath);//将元数据路径拼接上去
	strcat(metapath,regionidnamestr);//将region字符串拼接上去
	strcat(metapath,regionfilenamestr);//将region的文件名拼接上去
	
	//需要先检测文件夹是否存在
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
	UINT64 RegionID;//region的id
	int codetype;//编码类型
	CODEPARA *codepara;//编码参数
	UINT64 totalsize;//总存储空间大小字节为大小，NODEF代表无限大直至占满

	struct FILEMETAGROUP *filemetalist;//文件元数据列表
	UINT64 *fileid;//包括的file的编号列表
	int filenum;//strip数量

	DISKGROUP *disklist;//Disk列表
	UINT64 *diskid;//Disk的编号列表
	int disknum;//磁盘的个数

	DEVICEGROUP *devicelist;//device列表
	UINT64 *deviceid;//设备id列表
	int devicenum;//设备数量

	STRIPDES *strdes;//对于条带的描述
	STRIPGROUP *striplist;//Strip列表
	UINT64 *stripid;//条带id列表
	int stripnum;//条带个数

	struct FILEMETA *fileroot;//当前区域的文件的根指针
	UINT64 rootfileid;//根文件编号

	int storestate;//当前存储状态
	*/
	//开始输出
	fprintf(flout,"region id:%I64d\n",regionid);
	//开始输出内容
	fprintf(flout,"code type(code):%d,the parameter list:\n",codetype);
	fprintf(flout,"the galois field:%d\n",codepara->w);
	fprintf(flout,"data disk num:%d\n",codepara->datanum);
	fprintf(flout,"code disk num:%d\n",codepara->codenum);
	fprintf(flout,"total disk num:%d\n",codepara->totnum);
	fprintf(flout,"provider num:%d\n",codepara->pronum);
	fprintf(flout,"sector number:%d\n",codepara->sectornum);
	//总大小
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
	free(metapath);//最后释放路径信息
	return TRUE;

}
//将DISK的元数据写入磁盘
int file_FILELAYER_DISK_WRITER(DISK *disk)
{
	/*	
	UINT64 DiskID;//存储器编号
	int DiskTYPE;//存储器类型
	int capability;//性能能力
	int volumn;//存储器容量

	struct REGIONGROUP *regionlist;//指向其中包括的region的指针
	UINT64 *regionid;//存储器上涉及到的region数
	int regionnum;//存储器上包括的region数量

	struct DEVICE *deviceptr;//指向上级device列表
	UINT64 deviceid;//上一层的device编号
	
	char *diskpath;//关键信息当前磁盘的物理路径

	int storestate;//当前存储状态
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

	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
	FILE *flout;

	deviceptr=disk->deviceptr;
	//安全性检测
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
	//先赋值
	diskid=disk->DiskID;
	disktype=disk->DiskTYPE;
	capability=disk->capability;
	volumn=disk->volumn;

	regionid=disk->regionid;
	regionnum=disk->regionnum;

	deviceid=disk->deviceid;

	diskpath=disk->diskpath;

	storestate=disk->storestate;
	//由于是磁盘文件是全局性的,也要生成路径
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

	//检查目录
	resTF=file_FILELAYER_dictionary_disk_exists(deviceid,diskid);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","DISK_WRITER","dictionary can't create");
		return FALSE;
	}
	//文件指针
	flout=fopen(metapath,"w+");
	if(flout==NULL)
	{
		show_error("file_FILELAYER","DISK_WRITER","fptr can't create");
		return FALSE;
	}
	/*	
	UINT64 DiskID;//存储器编号
	int DiskTYPE;//存储器类型
	int capability;//性能能力
	int volumn;//存储器容量

	struct REGIONGROUP *regionlist;//指向其中包括的region的指针
	UINT64 *regionid;//存储器上涉及到的region数
	int regionnum;//存储器上包括的region数量

	struct DEVICE *deviceptr;//指向上级device列表
	UINT64 deviceid;//上一层的device编号
	
	char *diskpath;//关键信息当前磁盘的物理路径

	int storestate;//当前存储状态
	*/
	//开始输出
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
	free(metapath);//最后释放路径信息
	return TRUE;
}
//将DEVICE的元数据写入磁盘
int file_FILELAYER_DEVICE_WRITER(DEVICE *device)
{
	/*UINT64 DeviceID;//设备编号
	int Devicetype;//设备类别
	int processnum;//处理器数量
	int *speed;//GHZ

	
	UINT64 *diskid;//设备中存在的存储器
	DISKGROUP *disklist;//存储设备列表
	int disknum;//存储几个存储器

	struct REGIONGROUP *regionlist;//region列表
	UINT64 *regionid;//region编号
	int regionnum;//region数量

	int storestate;//当前存储状态*/
	UINT64 deviceid,*diskid,*regionid;
	int devicetype,processnum,disknum,regionnum;
	int *speed;
	int i,storestate,resTF;
	char deviceidstr[20]="";
	char deviceidnamestr[30]="";
	char devicefilenamestr[40]="";
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
	FILE *flout;
	//device赋值
	deviceid=device->DeviceID;
	devicetype=device->Devicetype;
	processnum=device->processnum;
	speed=device->speed;
	//disk的id
	diskid=device->diskid;
	disknum=device->disknum;
	//region的id
	regionid=device->regionid;
	regionnum=device->regionnum;
	//存储状态
	storestate=device->storestate;
	//由于是磁盘文件是全局性的，但是还是放在文件夹中
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
	//设备目录
	resTF=file_FILELAYER_dictionary_device_exists(deviceid);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","DEVICE_WRITER","dictionary can't create");
		return FALSE;
	}
	//打开文件指针
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
	free(metapath);//最后释放路径信息
	return TRUE;
}
//将文件的元数据息写入磁盘
int file_FILELAYER_FILEMETA_WRITER(FILEMETA *fmeta)
{
	/*
	UINT64 FileID;//文件ID
	char *filename;//文件名或是目录名
	int filesize;//文件大小
	int ACList;//文件访问标识
	int filetype;//文件类型,文件还是目录,文件类型,只读归档还是系统

	struct USERPROFILE *userinf;//文件所有者
	UINT64 userid;//文件所有者id

	UINT64 parentid;//上一级文件夹id
	struct FILEMETA *parentptr;//上一次文件夹
	
	UINT64 *subfileidlist;//子目录列表这里主要仿照linux思想
	struct FILEMETA *subfilelist;//文件块指针主要指向当前目录下一级元数据块，为了加速
	int subfilenum;//子目录和文件数量

	struct tm *createtime;//创建时间
	struct tm *updatetime;//更新时间

	FILEINF *filechunkinf;//用于存放数据块信息
	*/
	//fmeta信息
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

	//filechunkinf信息
	UINT64 *chunkid;
	CHUNKPATH *chunkpath;
	int chunknum;//chunk数量

	UINT64 regionid;//属于的region的编号

	UINT64 *deviceid;//设备id
	int devicenum;//设备数

	UINT64 *diskid;//存储器id列表
	int disknum;//存储器数量

	UINT64 *stripid;//条带id列表
	int stripnum;//条带数量

	UINT64 *stripsectid;///条带分区id列表
	int stripsectnum;//条带分区数量

	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
	FILE *flout;
	/*
	UINT64 fileid;//文件ID
	struct FILEMETA *filemeta;//文件元数据返回指针
	int *chunkid;//源码块列表
	CHUNKPATH *chkpath;//所有chunk的path
	CHUNKGROUP *chunklist;//块列表
	int chunknum;//chunk数量

	REGION *regoinptr;//region指针
	UINT64 regionid;//属于的region的编号
	
	DEVICEGROUP *devicelist;//设备列表
	UINT64 *deviceid;//设备id
	int devicenum;//设备数
	
	DISKGROUP *disklist;//存储器列表
	UINT64 *diskid;//存储器id列表
	int disknum;//存储器数量

	STRIPGROUP *striplist;//条带列表
	UINT64 *stripid;//条带id列表
	int stripnum;//条带数量

	STRIPSECT *stripsectlist;//条带区域列表
	UINT64 *stripsectid;///条带分区id列表
	int stripsectnum;//条带分区数量
	*/
	//fmeta+filechunkinf
	//先赋值
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
	//两种情况第一种没有非配地址空间，NULL，NOVALUE处理
	if(filechunkinf==NULL)
	{
		chunkid=NULL;
		chunkpath=NULL;
		chunknum=0;

		regionid=fmeta->regionid;//属于的region的编号

		deviceid=NULL;//设备id
		devicenum=0;//设备数

		diskid=NULL;//存储器id列表
		disknum=0;//存储器数量

		stripid=NULL;//条带id列表
		stripnum=0;//条带数量
		

		stripsectid=NULL;///条带分区id列表
		stripsectnum=0;//条带分区数量
	}
	else
	{
		chunkid=filechunkinf->chunkid;
		chunkpath=filechunkinf->chkpath;
		chunknum=filechunkinf->chunknum;//chunk数量

		regionid=filechunkinf->regionid;//属于的region的编号

		deviceid=filechunkinf->deviceid;//设备id
		devicenum=filechunkinf->devicenum;//设备数

		diskid=filechunkinf->diskid;//存储器id列表
		disknum=filechunkinf->disknum;//存储器数量

		stripid=filechunkinf->stripid;//条带id列表
		stripnum=filechunkinf->stripnum;//条带数量
		

		stripsectid=filechunkinf->stripsectid;///条带分区id列表
		stripsectnum=filechunkinf->stripsectnum;//条带分区数量
	}


	//下一步需要读取位置信息
	//由于是磁盘文件是region级的,因此需要
	glometapath=get_state_glometapath();
	metapath=talloc(char,(30+30+40+1000));//1000位给路径
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","FILEMETA_WRITER","No memory");
		return FALSE;
	}
	metapath[0]='\0';//定义字符串
	U64toSTR(regionidstr,regionid);//生成区域id
	U64toSTR(fileidstr,fileid);

	file_regionstr(regionidnamestr,regionidstr);//生成region字符串
	file_filemetastr(filemetaidnamestr,fileidstr);
	file_filemetastr_name(filemetafilenamestr,fileidstr);//filemeta文件名

	//路径捆绑在一起
	strcat(metapath,glometapath);//将元数据路径拼接上去
	strcat(metapath,regionidnamestr);//将region字符串拼接上去
	strcat(metapath,filemetaidnamestr);//将filemeta号拼接上去
	strcat(metapath,filemetafilenamestr);//将filename字符串拼接上去
	//检测目录存在性
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
	//创建修改时间
	fprintf(flout,"create time:%d/%d/%d/%d/%d,%d/%d/%d,%d\n",
		createtime->tm_year,createtime->tm_mon,createtime->tm_yday,createtime->tm_mday,createtime->tm_wday,
		createtime->tm_hour,createtime->tm_min,createtime->tm_sec,
		createtime->tm_isdst);
	fprintf(flout,"update time:%d/%d/%d/%d/%d,%d/%d/%d,%d\n",
		updatetime->tm_year,updatetime->tm_mon,updatetime->tm_yday,updatetime->tm_mday,updatetime->tm_wday,
		updatetime->tm_hour,updatetime->tm_min,updatetime->tm_sec,
		updatetime->tm_isdst);
	//filechunkinf数据
	fprintf(flout,"storage information,there are %d chunks,chunk id list:\n",chunknum);
	for(i=0;i<chunknum;i++)
	{
		fprintf(flout,"%I64d\n",chunkid[i]);
		//这里同时也输出chunkpath
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
		fprintf(flout,"%I64d\n",stripid[i]);//条带id列表
	}
	fprintf(flout,"there are %d stripsects,stripsect id list:\n",stripsectnum);
	for(i=0;i<stripsectnum;i++)
	{
		fprintf(flout,"%I64d\n",stripsectid[i]);
	}
	fclose(flout);
	free(metapath);//最后释放路径信息
	return TRUE;
}
//将用户信息的元数据写入磁盘
int file_FILELAYER_USERPROFILE_WRITER(USERPROFILE *pfile)
{
	/*UINT64 UserID;//用户id
	USERLOCATION *userlocinf;//用户目录位置
	int userprivil;//用户权限
	struct tm *createtime;//账户创建时间*/
	UINT64 userid,DICid,resTF;
	char *username,*password,*DICpath;
	USERLOCATION *userlocinf;
	int userprivil;
	struct tm *createtime;
	char userprofileidstr[20]="";
	char userprofileidnamestr[40]="";
	char userprofilefilenamestr[50]="";
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
	FILE *flout;
	//赋值
	userid=pfile->UserID;
	username=pfile->username;
	password=pfile->password;
	userlocinf=pfile->userlocinf;
	DICid=userlocinf->DICid;
	DICpath=userlocinf->DICpath;
	userprivil=pfile->userprivil;
	createtime=pfile->createtime;
	//获取元数据地址
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
	//创建目录
	resTF=file_FILELAYER_dictionary_userprofile_exists(userid);
	if(resTF==FALSE)
	{
		show_error("file_FILELAYER","USERPROFILE_WRITER","dictionary can't create");
		return FALSE;
	}
	//打开文件句柄
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
	//free(metapath);//最后释放路径信息
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

//由于全局文件只有一个无需group处理
//将用户信息的元数据写入磁盘
int file_FILELAYER_GLOSYSTEMID_WRITER(GLOSYSTEMID *glosysid)
{
	UINT64 *regionidlist,*useridlist,*deviceidlist,*diskidlist,glomaxbuffersize;
	int i,regionnum,usernum,devicenum,disknum;

	IDITEM *systemnextid;
	//UINT64 chunkidlist;
	int *availkind;//现存编码类型
	int availnum,glopushtime;//编码类型总数

	char glofilename[40]="";
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
	FILE *flout;
	regionidlist=glosysid->regionid;
	regionnum=glosysid->regionnum;

	useridlist=glosysid->userid;
	usernum=glosysid->usernum;

	deviceidlist=glosysid->deviceid;
	devicenum=glosysid->devicenum;

	diskidlist=glosysid->diskid;
	disknum=glosysid->disknum;
	//获取元数据地址
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
	//输出当前id号
	systemnextid=glosysid->systemnextid;
	fprintf(flout,"next step region id:%I64d,strip id:%I64d,stripsect id:%I64d,chunk id:%I64d\n",
		systemnextid->gloregionid,systemnextid->glostripid,systemnextid->glostripsectid,systemnextid->glochunkid);
	fprintf(flout,"device id:%I64d,disk id:%I64d,file id:%I64d,user id:%I64d\n",
		systemnextid->glodeviceid,systemnextid->glodiskid,systemnextid->glofileid,systemnextid->glouserid);
	//输出类别数
	availnum=glosysid->availnum;
	availkind=glosysid->availkind;
	fprintf(flout,"there are %d kinds code,the id list of code:\n",availnum);
	for(i=0;i<availnum;i++)
	{
		fprintf(flout,"%d\n",availkind[i]);
	}

	//输出push时间
	glopushtime=glosysid->glopushtime;
	glomaxbuffersize=glosysid->glomaxbuffersize;
	fprintf(flout,"the push time of system is %d time uints\n",glopushtime);
	fprintf(flout,"the push maximum buffer size is %I64d BYTE\n",glomaxbuffersize);
	free(metapath);
	fclose(flout);
	return TRUE;
}
//组块写入,写入磁盘
//将CHUNKGROUP根据其中包含的路径写入到相应的区域
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
//将CHUNKGROUP根据其中包含的路径写入到相应的区域,数据部分
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
//将STRIPSECTGROUP根据内部信息在对应位置创建相应的stripsect
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
//将STRIPSECTGROUP根据其中包含的路径写入到相应的区域
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
//将STRIPGROUP根据其中包含的路径写入到相应的区域;这里需要通过region到disk中查找
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
//将REGIONGROUP写入相应数据
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
//将DISKGROUP写入相应数据
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
//将DEVICEGROUP写入相应数据
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
//将FILEMETAGROUP写入相应数据
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
//将USERGROUP写入到相应位置
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
		//如果不存在创建之
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
	//第一步先
	int resTF;
	char regionidstr[20]="";
	char regionidnamestr[30]="";
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
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
	//第一步先
	int resTF;
	char regionidstr[20]="",stripidstr[20]="";
	char regionidnamestr[30]="",stripidnamestr[30]="";
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
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
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
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
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址

	glometapath=get_state_glometapath();
	metapath=talloc(char,1000+30+30);
	if(metapath==NULL)
	{
		show_error("file_FILELAYER","dictionary_filemeta_exists","NO memory");
		return FALSE;
	}
	//metapath[0]='\0';
	//计算路径
	metapath[0]='\0';//定义字符串
	U64toSTR(regionidstr,regionid);//生成区域id
	U64toSTR(fileidstr,fileid);

	file_regionstr(regionidnamestr,regionidstr);//生成region字符串
	file_filemetastr(filemetaidnamestr,fileidstr);
	//file_filemetastr_name(filemetafilenamestr,fileidstr);//filemeta文件名

	//路径捆绑在一起
	strcat(metapath,glometapath);//将元数据路径拼接上去
	strcat(metapath,regionidnamestr);//将region字符串拼接上去
	strcat(metapath,filemetaidnamestr);//将filemeta号拼接上去
	//strcat(metapath,filemetafilenamestr);//将filename字符串拼接上去
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
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
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
	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址
	
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

	char *metapath;//当前元数据位置
	char *glometapath;//全局元数据地址

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
//辅助函数
//获取文件获取文件大小，指针在文件顶端
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
	resTF=fseek(fp,0L,SEEK_SET);//调整会头部
	if(resTF==-1)
	{
		show_error("encoder","METALAYER_matedata","fseek fail");
		return FALSE;
	}
	return filesize;
}

//写入块数据接口API通过pushlist来决定是否延时写
//需要同步数据的指针
int file_chunk_write_API(CHUNK *chunkptr)
{
	int maxbuffersize,pushtime,resTF;

	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	//CHUNK *chunkptr;
	int chunknum,currentchunksize;
	BYTE *contentptr;

	GLOPUSHLIST *pushlistptr;
	int chunksize;

	//计算pushlist

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
	//居然有数据
	chunksize=chunkptr->sizenum;

	chunkblockptr=pushlistptr->glopushchunklist;
	chunknum=pushlistptr->chunknum;
	if(chunknum==0||chunkblockptr==NULL)//chunknum=0或是chunkgroupptr==NULL开空间
	{
		chunkblockptr=talloc(CHUNKBLOCK,chksize_MB(4));//开一个4M的缓冲空间
		if(chunkblockptr==NULL)
		{
			show_error("file","chunk_write_API","No memory");
			return FALSE;
		}
		chunkblockptr->chunkptr=chunkptr;
		chunkblockptr->chunkid=chunkptr->ChunkID;
		
		chunknum=1;
		//chunksize=chunkptr->sizenum;

		pushlistptr->currentbuffersize=chunksize;//当前数据
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
		curchunkblockptr=chunkblockptr+chunknum-1;//移动到当前位置，因为一开始已经加1了，这里要减1
		curchunkblockptr->chunkid=chunkptr->ChunkID;
		curchunkblockptr->chunkptr=chunkptr;
	}*/
	

	currentchunksize=pushlistptr->currentbuffersize;
	currentchunksize=currentchunksize+chunksize;

	
	//如果缓冲超过了那么就可以同步了
	if(currentchunksize>maxbuffersize)
	{
		resTF=file_FILELAYER_CHUNK_WRITER_DATA(chunkptr);//先将数据同步
		if(resTF==FALSE)
		{
			show_error("file","chunk_write_API","chunk can't write");
			return FALSE;
		}
		//就需要同步数据
		resTF=profile_GLOBAL_chunk_data_sync();
		if(resTF==FALSE)
		{
			show_error("file","chunk_write_API","chunk can't synchronization");
			return FALSE;
		}
		//return TRUE;//同步完成返回
	}
	else
	{
		//需要将其进行缓冲
		pushlistptr->currentbuffersize=currentchunksize;//将当前数据进行赋值

		chunknum=pushlistptr->chunknum;//计算
		
		curchunkblockptr=chunkblockptr+chunknum;//将指针
		chunknum=chunknum+1;

		curchunkblockptr->chunkptr=chunkptr;
		curchunkblockptr->chunkid=chunkptr->ChunkID;

		//将数据进行数据操作
		pushlistptr->glopushchunklist=curchunkblockptr;
		pushlistptr->chunknum=chunknum;
	}
	return TRUE;
}