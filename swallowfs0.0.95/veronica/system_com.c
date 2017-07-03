#include "system_com.h"
//创建一个区域
int systemcom_REGION_create(REGION *regionptr)
{
	int resTF;
	
	resTF=profile_region_format_PTR(regionptr);//建立相应结构
	if(resTF==FALSE)
	{
		show_error("systemcom","REGION_create","region can't format");
		return FALSE;
	}
	//将建立完成的数据进行拷贝
	resTF=set_state_gloregiongroup_add(regionptr);
	if(resTF==FALSE)
	{
		show_error("systemcom","REGION_create","region can't add into system");
		return FALSE;
	}
	//将数据同步到当前的元数据区域
	resTF=profile_region_sync(regionptr);
	if(resTF==FALSE)
	{
		show_error("systemcom","REGION_create","region can't sync");
		return FALSE;
	}
	return TRUE;
}
//通过ptr删除region
int systemcom_REGION_delete_ptr(REGION *regionptr)
{
	return TRUE;
}
//通过id删除region	
int systemcom_REGION_delete_id(UINT64 regionid)
{
	return TRUE;
}

//
//创建一个device
int systemcom_DEVICE_create(DEVICE *deviceptr)
{
	
	return TRUE;
}
//删除一个device
int systemcom_DEVICE_delete_ptr(DEVICE *deviceptr)
{ 
	return TRUE;
}
//删除一个device
int systemcom_DEVICE_delete_ID(UINT64 deviceid)
{
	return TRUE;
}
//同步disk
//创建一个disk
int systemcom_DISK_create(DISK *diskptr)
{
	return TRUE;
}
//删除一个disk
int systemcom_DISK_delete_PTR(DISK *diskptr)
{
	return TRUE;
}
//删除一个disk 
int systemcom_DISK_delete_ID(UINT64 diskid)
{
	return TRUE;
}

//用户指令
//创建相应用户
int systemcom_USER_create(USERPROFILE *userptr)
{
	return TRUE; 
}
//删除系统用户
int systemcom_USER_delete_PTR(USERPROFILE *userptr)
{
	return TRUE;
}
//删除系统用户
int systemcom_USER_delete_ID(UINT64 userid)
{
	return TRUE;
}



//文件基本操作
//文件创建
FILEMETA *systemcom_FILE_create_handle(char *filepath)
{
	FILEMETA *resfilemetaptr=NULL;
	//FILEMETA *regionroot;
	//第一步先解析当前的路径
	REGIONGROUP *regiongroupptr;
	REGION *regionptr;

	FILEMETA *filemetaptr,*parentfilemetaptr;
	FILEMETABLOCK *fileblockptr;

	USERPROFILE *userprofileptr;//获取当前用户指针

	//time_t rawtime;
	struct tm *createtime;
	struct tm *updatetime;

	char *filemetaname;
	int filenum;

	char *curfilenamepart,*nextfileptr;//假设每一个

	int j,strindex,resTF;//i用于记录文件分块的数据
	//int regiongroupsize;
	UINT64 regionindex,currentid;
	UINT64 perantid,userid,regionid;
	/*//第一步找到当前
	strindex=7;
	i=0;
	curchar=filepath[strindex];
	strindex++;
	while(curchar!='\\')
	{
		curchar=filepath[strindex];
		curfilenamepart[i]=curchar;
		i++;
		strindex++;
	}
	curfilenamepart[i]='\0';//补上尾部标记
	STRTOINT64(curfilenamepart,regionindex);//将字符串转化为数值
	//找出目标区域提取文件指针
	regiongroupptr=get_state_gloregiongroup_PTR();
	regionptr=regiongroupptr->regiongroup;
	regiongroupsize=regiongroupptr->groupsize;
	for(i=0;i<regiongroupsize;i++)
	{
		currentid=regionptr->RegionID;
		if(currentid==regionindex)
		{
			//获取数据
			filemetaptr=regionptr->fileroot;
			break;
		}
		regionptr++;
	}
	if(i==regiongroupsize)
	{
		show_error("systemcom","FILE_create_handle","region can't find");
		return FALSE;
	}*/
	regionindex=profile_get_region_id(filepath);
	regionptr=profile_region_search_ptr(regionindex);
	if(regionptr==NULL)
	{
		show_error("systemcom","FILE_create_handle","regionptr can't find");
		return FALSE;
	}
	

	//既然已将找到了根指针就可继续往下了计算数据了
	//i=0;
	filemetaptr=regionptr->fileroot;//提取更目录
	curfilenamepart=strstr(filepath,"\\");//寻找第一个位置省去region
	curfilenamepart=curfilenamepart+1;//会把\计算在内因此需要去除
	parentfilemetaptr=filemetaptr;
	while(curfilenamepart!=NULL)
	{
		nextfileptr=strstr(curfilenamepart,"\\");//找到下一个位置
		
		if(nextfileptr==NULL)//已经到底
		{
			fileblockptr=filemetaptr->subfilelist;
			filenum=filemetaptr->subfilenum;//查一查有多少个子文件夹
			parentfilemetaptr=filemetaptr;//记住以备后用
			if(fileblockptr!=NULL)
			{
				for(j=0;j<filenum;j++)
				{
				
					filemetaptr=fileblockptr->filemetaptr;
					currentid=filemetaptr->FileID;
					filemetaname=filemetaptr->filename;//获取当前文件夹名
					resTF=strcmp(curfilenamepart,filemetaname);
					if(currentid!=NOVALUE)//如果当前目录没有没删除
					{
						if(resTF==0)
						{
							//如果数据一致，就是这一级目录无疑
							curfilenamepart=nextfileptr;//赋值为NULL
							break;
						}
					}
					fileblockptr++;
				}
			}
			else
			{
				j=filenum;
			}
			resfilemetaptr=filemetaptr;//我们假设已经找到
			if(j==filenum)//没找到穿件一个空的并且将指针进行赋值
			{
				resfilemetaptr=talloc(FILEMETA,1);//没有找到的话就来个新的
				if(filemetaptr==NULL)
				{
					show_error("systemcom","FILE_create_handle","No memory");
					return NULL;
				}
				perantid=parentfilemetaptr->FileID;//将上级的id进行赋值
				//获取当前用户
				userprofileptr=get_state_glosysuserptr_userprofile();
				userid=userprofileptr->UserID;
				//获取当前region编号
				regionid=regionptr->RegionID;
				//获取当前时间
				//time(&rawtime);
				createtime=get_system_time();//转化当前时间
				updatetime=get_system_time();
				//开始赋值
				//当前还没有这个指针
				resfilemetaptr->FileID=get_state_glofileid();//获取系统fileid
				set_state_glofileid_add(1);//对于系统fileid增加
				GLOBAL_set_FILEMETA_data(resfilemetaptr,curfilenamepart,NOVALUE,NOVALUE,FILEKIND,
									regionptr,regionid,//上层region指针
									userprofileptr,userid,//文件所有者
									perantid,parentfilemetaptr,//上一层文件夹
									NULL,NULL,NONE,//文件块指针主要指向当前目录下一级元数据块
									createtime,
									updatetime,
									NULL//用于存放数据块信息
									);//设定FILEMETA数据值 
				curfilenamepart=nextfileptr;
			}
		}
		else
		{
			//当前为文件夹
			fileblockptr=filemetaptr->subfilelist;
			filenum=filemetaptr->subfilenum;
			if((fileblockptr==NULL)||(filenum=0))
			{
				show_error("systemcom","FILE_create_handle","dictionary have no subfile");
				return NULL;

			}
			for(j=0;j<filenum;j++)
			{
				
				filemetaptr=fileblockptr->filemetaptr;
				parentfilemetaptr=filemetaptr;//将指针数据
				currentid=filemetaptr->FileID;
				filemetaname=filemetaptr->filename;//获取当前文件夹名
				resTF=strcmp(curfilenamepart,filemetaname);
				if(currentid!=NOVALUE)//如果当前目录没有没删除
				{
					if(resTF==0)
					{
						//如果数据一致，就是这一级目录无疑
						break;
					}
				}
				fileblockptr++;
			}
			if(j==filenum)
			{
				show_error("systemcom","FILE_create_handle","the dictionary can't find");
				return NULL;
			}
			//i=0;//寻找完成将part指针置0
			break;
			nextfileptr=nextfileptr+1;
			curfilenamepart=nextfileptr;//将指针向下移动一个位置
		}
	}
	/*while(curchar!='/0')//扫描到文件尾
	{
		curchar=filepath[strindex];//向后计算
		switch(curchar)
		{
		case '\\':
			//说明之前的数据已经完成
			fileblockptr=filemetaptr->subfilelist;
			filenum=filemetaptr->subfilenum;
			for(j=0;j<filenum;j++)
			{
				
				filemetaptr=fileblockptr->filemetaptr;
				currentid=filemetaptr->FileID;
				filemetaname=filemetaptr->filename;//获取当前文件夹名
				resTF=strcmp(curfilenamepart,filemetaname);
				if(currentid!=NOVALUE)//如果当前目录没有没删除
				{
					if(resTF==0)
					{
						//如果数据一致，就是这一级目录无疑
						break;
					}
				}
				fileblockptr++;
			}
			if(j==filenum)
			{
				show_error("systemcom","FILE_create_handle","the dictionary can't find");
				return FALSE;
			}
			i=0;//寻找完成将part指针置0
			break;
		case '\0':
			//当前数据已经到底了,判断是不是当前的有这个文件有的话，返回当前文件元数据句柄，没有就创建一个
			fileblockptr=filemetaptr->subfilelist;
			parentfilemetaptr=filemetaptr;//记住以备后用
			for(j=0;j<filenum;j++)
			{
				
				filemetaptr=fileblockptr->filemetaptr;
				currentid=filemetaptr->FileID;
				filemetaname=filemetaptr->filename;//获取当前文件夹名
				resTF=strcmp(curfilenamepart,filemetaname);
				if(currentid!=NOVALUE)//如果当前目录没有没删除
				{
					if(resTF==0)
					{
						//如果数据一致，就是这一级目录无疑
						break;
					}
				}
				fileblockptr++;
			}
			resfilemetaptr=filemetaptr;//我们假设已经找到
			if(j==filenum)//没找到穿件一个空的并且将指针进行赋值
			{
				resfilemetaptr=talloc(FILEMETA,1);//没有找到的话就来个新的
				if(filemetaptr==NULL)
				{
					show_error("systemcom","FILE_create_handle","No memory");
					return FALSE;
				}
				perantid=parentfilemetaptr->FileID;//将上级的id进行赋值
				//获取当前用户
				userprofileptr=get_state_glosysuserptr_userprofile();
				userid=userprofileptr->UserID;
				//获取当前region编号
				regionid=regionptr->RegionID;
				//获取当前时间
				//time(&rawtime);
				createtime=get_system_time();//转化当前时间
				updatetime=get_system_time();
				//开始赋值
				resfilemetaptr->FileID=NOVALUE;//当前还没有这个指针
				GLOBAL_set_FILEMETA_data(resfilemetaptr,curfilenamepart,NOVALUE,NOVALUE,FILEKIND,
									regionptr,regionid,//上层region指针
									userprofileptr,userid,//文件所有者
									perantid,parentfilemetaptr,//上一层文件夹
									NULL,NULL,NOVALUE,//文件块指针主要指向当前目录下一级元数据块
									createtime,
									updatetime,
									NULL//用于存放数据块信息
									);//设定FILEMETA数据值
			}
			break;
		default:
			//两者都不是
			curfilenamepart[i]=curchar;
			//i++;
			break;
		}
		strindex++;
	}*/
	return resfilemetaptr;
}
//文件删除
int systemcom_FILE_delete(FILEMETA *fmeta)
{
	return TRUE;
}
//文件读取
int systemcom_FILE_read(FILEMETA *fmeta,BYTESTREAM *bstream)
{
	return TRUE;
}
//文件覆盖写相当于"w"
int systemcom_FILE_write_overwrite(FILEMETA *fmeta,BYTESTREAM *bstream)
{
	return TRUE;
}
//非覆盖写
int systemcom_FILE_write_change(FILEMETA *fmeta,BYTESTREAM *bstream,int offset)
{
	return TRUE;
}
//文件添加
int systemcom_FILE_append(FILEMETA *fmeta,BYTESTREAM *bstream)
{
	return TRUE;
}
//文件从一个区域拷贝到另一路径
int systemcom_FILE_duplicate(FILEMETA *soufmeta,FILEMETA *desfmeta)
{
	return TRUE;
}
//属性修改
//更新当前文件的
extern int systemcom_FILE_ACLMOD(int ACList)
{
	return TRUE;
}

//目录指令
int systemcom_DICT_DIR(char *dictpath)//显示一个目录
{
	return TRUE;
}
int systemcom_DICT_DIR_rootuser()//显示用户当前目录内容
{
	return TRUE;
}
int systemcom_DICT_create(char *dictpath)//系统目录创建
{
	return TRUE;
}
int systemcom_DICT_delete(char *dictpath)//系统目录删除
{
	return TRUE;
}
int systemcom_DICT_access(char *dictpath)//判断一个目录是否存在
{
	return TRUE;
}

//系统状态更新，报告
//系统状态报告
//汇报磁盘状态
int systemcom_userstate_report()
{
	int i;
	int usernum;
	USERPROFILE *userlist;
	USERGROUP *usergrouplist;
	usergrouplist=get_state_glousergroup_PTR();
	userlist=usergrouplist->userlist;
	usernum=usergrouplist->groupsize;
	for(i=0;i<usernum;i++)
	{
		profile_userprofile_info(userlist);
		userlist++;
	}
	return TRUE;
}
int systemcom_diskstate_report()
{
	int i;
	int disknum;
	DISK *diskptr;
	DISKGROUP *diskgroupptr;
	diskgroupptr=get_state_glodiskgroup_PTR();
	diskptr=diskgroupptr->diskgroup;
	disknum=diskgroupptr->groupsize;
	for(i=0;i<disknum;i++)
	{
		profile_disk_info(diskptr);
		diskptr++;
	}
	return TRUE;
}
//汇报设备状态
int systemcom_devicestate_report()
{
	int i;
	DEVICEGROUP *devicegroupptr;
	DEVICE *deviceptr;
	int devicegroupsize;
	devicegroupptr=get_state_glodevicegroup_PTR();
	deviceptr=devicegroupptr->devicegroup;
	devicegroupsize=devicegroupptr->groupsize;
	for(i=0;i<devicegroupsize;i++)
	{
		profile_device_info(deviceptr);
		deviceptr++;
	}
	return TRUE;
}
//汇报区域状态
int systemcom_regionstate_report()
{
	int i;
	REGIONGROUP *regiongroupptr;
	REGION *regionptr;
	int regiongroupsize;
	regiongroupptr=get_state_gloregiongroup_PTR();
	regionptr=regiongroupptr->regiongroup;
	regiongroupsize=regiongroupptr->groupsize;
	for(i=0;i<regiongroupsize;i++)
	{
		profile_region_info(regionptr);
		regionptr++;
	}
	return TRUE;
}


//系统初始化
//系统初始化,根据元数据地址初始化
int systemcom_system_inital()
{
	//直接调用系统初始化api
	profile_global_system_intial();
	return TRUE;
}
//系统格式化,根据region信息进行format操作
int systemcom_system_format()
{
	//获取region指针
	int i,regiongroupsize,resTF;
	REGIONGROUP *regiongroupptr;
	REGION *regionptr;
	//开始全员格式化即可
	regiongroupptr=get_state_gloregiongroup_PTR();
	regionptr=regiongroupptr->regiongroup;
	regiongroupsize=regiongroupptr->groupsize;
	for(i=0;i<regiongroupsize;i++)
	{
		resTF=profile_region_format_PTR(regionptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_format","region can't format");
			return FALSE;
		}
		regionptr++;
	}
	return TRUE;
}

//慎用将系统恢复到白纸状态
//35个region，编号如下
//0-4 RAID5（6+1）
//RAID6:（5+2）
//5-9:CAUCHY orginal RS
//10-14:CAUCHY RS
//15-19:EVENODD
//20-24:RDP
//25-30:LIBERATION CODE
//30-34:blaum-roth code
//建立一个7NAS和7disk的系统，客官要是不是这个配置自己改
int systemcom_system_reset_format()
{
	//format先建立device和disk的信息
	int i,disknum,devicenum,resTF;
	int pushtime,maxbuffersize;
	int multindex;
	//int chunksize;

	char *diskpath,*curdiskpath,*username,*curusername,*filename,*curfilename;

	UINT64 currentid;
	//全局变量是用于
	UINT64 *glodiskidlist,*glodeviceidlist,*glofileidlist;
	DEVICEBLOCK *glodeviceblockptr,*curglodeviceblockptr;
	DISKBLOCK *glodiskblockptr,*curglodiskblockptr;

	UINT64 *RDPdeviceid;
	DEVICEBLOCK *RDPdeviceblockptr,*curRDPdeviceblockptr;

	UINT64 *RDPdiskid;
	DISKBLOCK *RDPdiskblockptr,*curRDPdiskblockptr;

	CHUNKBLOCK *chunkblockbuffer;

	GLOPUSHLIST *pushlistptr;

	DEVICE *deviceptr,*curdeviceptr;
	DEVICEGROUP *devicegroupptr;
	

	DISK *diskptr,*curdiskptr;
	DISKGROUP *diskgroupptr;
	DISKBLOCK *diskblockptr;
	UINT64 *diskidlist;//用于记录指针
	UINT64 volumn;

	REGION *regionptr,*curregionptr;//指针和当前指针
	REGIONBLOCK *regionblockptr,*curregionblockptr;
	REGIONGROUP *regiongroupptr;
	UINT64 *regionidlist;
	int regionnum;
	UINT64 totalsize;

	USERPROFILE *userprofileptr,*curuserprofileptr;
	USERLOCATION *userlocationptr;
	USERGROUP *usergroupptr;

	IDITEM *systemnextid;

	CODEPARA *codepara;

	STRIPDES *strdes;//条带描述

	FILEMETA *filemetaptr;//计算
	FILEINF *fileinfptr;
	FILEMETAGROUP *filemetagroupptr;
	//UINT64 fileidlist;//仅仅需要记录一个即可
	//时间
	time_t rawtime;
	struct tm *Nowtime;

	int strindex,codetype;
	
	disknum=TOTDISKNUMBER;
	devicenum=TOTDEVICENUMBER;
	regionnum=TOTREGIONNUM;
	deviceptr=talloc(DEVICE,devicenum);
	if(deviceptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	diskptr=talloc(DISK,disknum);
	if(diskptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	//因为是手工初始化globaldefine可以省略
	//需要设定但是需要设定参数
	intial_kind();//初始化类别
	//设定缓冲区
	pushtime=0;
	/*chunkblockbuffer=talloc(CHUNKBLOCK,chksize_MB(4));//4G的存储器缓冲，因此4G/1K=最多4M个
	if(chunkblockbuffer==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}*/
	chunkblockbuffer=NULL;
	maxbuffersize=0;
	pushlistptr=talloc(GLOPUSHLIST,1);
	if(pushlistptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	pushlistptr->chunknum=0;
	pushlistptr->currentbuffersize=0;
	pushlistptr->glolastpushtime=NULL;
	pushlistptr->maxbuffersize=maxbuffersize;
	pushlistptr->glopushchunklist=chunkblockbuffer;
	pushlistptr->glopushtime=pushtime;
	//参数设定完毕赋值即可
	set_state_buffer_pushlist(pushlistptr);
	//用完可以拆了
	free(pushlistptr);
	//分空间
	systemnextid=talloc(IDITEM,1);
	if(systemnextid==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	GLOABL_set_SYSTEMNEXTID_data(systemnextid,0,0,0,0,0,0,0,0);//C从0开始
	//赋值
	set_SYSID_PTR(systemnextid);
	//用完可以拆了
	free(systemnextid);
	
	//先建立region指针和相应regionblock和regiongroup
	regionptr=talloc(REGION,regionnum);
	if(regionptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	regiongroupptr=talloc(REGIONGROUP,1);
	if(regiongroupptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	regiongroupptr->regiongroup=regionptr;
	regiongroupptr->groupsize=regionnum;
	//赋值
	set_state_gloregiongroup(regiongroupptr);
	//释放空间
	free(regiongroupptr);
	regionidlist=talloc(UINT64,regionnum);
	if(regionidlist==NULL)
	{	
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}

	regionblockptr=talloc(REGIONBLOCK,regionnum);
	if(regionblockptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	curregionblockptr=regionblockptr;
	curregionptr=regionptr;
	for(i=0;i<35;i++)
	{
		
		curregionptr->RegionID=get_state_gloregionid();
		set_state_gloregionid_add(1);
		
		curregionblockptr->regionid=regionptr->RegionID;
		curregionblockptr->regionptr=regionptr;
		
		regionidlist[i]=regionptr->RegionID;
		curregionptr++;
		curregionblockptr++;
	}
	
	

	/*deviceptr=talloc(DEVICE,devicenum);
	if(deviceptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}*/
	devicegroupptr=talloc(DEVICEGROUP,1);
	if(devicegroupptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	devicegroupptr->devicegroup=deviceptr;
	devicegroupptr->groupsize=devicenum;
	glodeviceblockptr=talloc(DEVICEBLOCK,devicenum);
	if(glodeviceblockptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	glodeviceidlist=talloc(UINT64,devicenum);
	if(glodeviceidlist==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	curglodeviceblockptr=glodeviceblockptr;
	curdeviceptr=deviceptr;
	//设定数据
	for(i=0;i<devicenum;i++)
	{
		curdeviceptr->DeviceID=get_state_glodeviceid();//对于id进行赋值
		set_state_glodeviceid_add(1);
		GLOBAL_set_DEVICE_data(curdeviceptr,NASMAC,0,NULL,
								  NULL,NULL,NOVALUE,//存储器列表
								  regionblockptr,regionidlist,1,//region列表
								  EMPTY//当前存储状态
								  );//设定当前DEVICE中的数据
		//设定全局设备编号
		glodeviceidlist[i]=curdeviceptr->DeviceID;
		//设定全局block指针
		curglodeviceblockptr->deviceptr=curdeviceptr;
		curglodeviceblockptr->deviceid=curdeviceptr->DeviceID;//处处志志
		curglodeviceblockptr++;
		curdeviceptr++;
	}
	//设定数据
	set_state_glodevicegroup(devicegroupptr);
	//释放空间
	free(devicegroupptr);


	/*diskptr=talloc(DISK,disknum);
	if(diskptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}*/
	diskgroupptr=talloc(DISKGROUP,1);
	if(diskgroupptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	glodiskblockptr=talloc(DISKBLOCK,disknum);
	if(glodiskblockptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	glodiskidlist=talloc(UINT64,disknum);
	if(glodiskidlist==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}

	

	diskgroupptr->diskgroup=diskptr;
	diskgroupptr->groupsize=disknum;

	curglodiskblockptr=glodiskblockptr;
	curdiskptr=diskptr;
	curdeviceptr=deviceptr;

	diskpath="d:\\";
	for(i=0;i<disknum;i++)
	{
		curdiskptr->DiskID=get_state_glodiskid();//对于id进行赋值
		set_state_glodiskid_add(1);
		curdiskpath=talloc(char,1000);
		if(curdiskpath==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		mcpy(curdiskpath,diskpath,char,strlen(diskpath)+1);
		curdiskpath[0]=curdiskpath[0]+i;//将盘符向后移动一格
		currentid=curdeviceptr->DeviceID;
		volumn=chksize_TB(2);
		GLOBAL_set_DISK_data(curdiskptr,NORHDD,MIDCAP,volumn,
								regionblockptr,regionidlist,1,//存储器上包括的region数量
								curdeviceptr,currentid,//上一层的device编号
								curdiskpath,//关键信息当前磁盘的物理路径
								EMPTY//当前存储状态	
								);//设定当前DISK中的数据
		//计算当前curdevice中的block信息
		diskblockptr=talloc(DISKBLOCK,1);
		if(diskblockptr==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		diskblockptr->diskptr=curdiskptr;
		diskblockptr->diskid=curdiskptr->DiskID;
		diskidlist=talloc(UINT64,1);
		if(diskidlist==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		diskidlist[0]=curdiskptr->DiskID;//将数据重新写回
		curdeviceptr->diskid=diskidlist;
		curdeviceptr->disklist=diskblockptr;
		curdeviceptr->disknum=1;

		//设定全局disk编号
		glodiskidlist[i]=curdiskptr->DiskID;
		//设定全局block指针
		curglodiskblockptr->diskptr=curdiskptr;
		curglodiskblockptr->diskid=curdiskptr->DiskID;

		curglodiskblockptr++;
		curdeviceptr++;
		curdiskptr++;
	}
	//设定数据
	set_state_glodiskgroup(diskgroupptr);
	//释放空间
	free(diskgroupptr);

	//设定user信息,这里加上两个用户
	userprofileptr=talloc(USERPROFILE,2);
	if(userprofileptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	//开group的空间
	usergroupptr=talloc(USERGROUP,1);
	if(usergroupptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	curuserprofileptr=userprofileptr;
	username="user1";
	for(i=0;i<2;i++)
	{
		curuserprofileptr->UserID=get_state_glouserid();//对于id进行赋值
		set_state_glouserid_add(1);
		userlocationptr=talloc(USERLOCATION,1);
		if(userlocationptr==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		
		GLOBAL_set_USERLOCATION_data(userlocationptr,NOVALUE,NULL,NULL);//用户的当前文件系统位置
		
		curusername=talloc(char,1000);
		if(curusername==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		//获取当前时间
		time(&rawtime);
		Nowtime=localtime(&rawtime);
		//转化当前时间
		strindex=(int)strlen(username);
		mcpy(curusername,username,char,strlen(username)+1);
		
		curusername[strindex-1]=curusername[strindex-1]+i;//主要原因是因为
		GLOBAL_set_USERPROFILE_data(curuserprofileptr,curusername,"111111",
									   userlocationptr,SYSADMIN,//用户信息
									   Nowtime//创建时间
									   );
		curuserprofileptr++;
	}
	//两个用户的
	curuserprofileptr=userprofileptr;
	for(i=0;i<2;i++)
	{
		userlocationptr=curuserprofileptr->userlocinf;
		userlocationptr->DICid=0;//将数据定位第一个文件上region0
		userlocationptr->DICpath="region0\\";
	}
	usergroupptr->userlist=userprofileptr;
	usergroupptr->groupsize=2;
	set_state_glousergroup(usergroupptr);
	free(usergroupptr);


	//建立全局region元数据
	// 一步一步来建立RAID-5
	totalsize=chksize_MB(10);

	curregionptr=regionptr;
	//index=0;
	filename="region0\\";
	multindex=1;
	for(i=0;i<5;i++)
	{
		curfilename=talloc(char,100);
		if(curfilename==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		strindex=(int)strlen(filename);
		mcpy(curfilename,filename,char,strindex+1);
		curfilename[strindex-2]=curfilename[strindex-2]+i;


		codetype=codetype(RAID5,NULLTYPE);//计算编码类型
		codepara=talloc(CODEPARA,1);
		if(codepara==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}

		GLOBAL_set_CODEPARA_data(codepara,
										8,//伽罗华域大小
										6,//k
										1,//m
										7,//n
										5,//d
										NOVALUE//针对扇区编码的块数
										);//设定CODEPARA数据值
		strdes=talloc(STRIPDES,1);
		if(strdes==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		//开始描述条带
		GLOBAL_set_STRIPDES_data(strdes,
										1,//每一个条带包括的行数,即chunk数
										glodiskblockptr,//所需的disk列表
										glodiskidlist,//当前磁盘id
										disknum,//存在的即一个条带的列数，磁盘数，通常这个数量和region的disk数一致
										chksize_KB(16*multindex)//每一个CHUNK的大小以字节为单位
										);//设定STRIPDES数据值
		multindex=multindex*2;
		resTF=profile_region_setup(curregionptr,codetype,codepara,strdes,totalsize,
									glodeviceidlist,glodeviceblockptr,devicenum,
									glodiskidlist,glodiskblockptr,disknum,
									curfilename,userprofileptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","region can't setup");
			return FALSE;
		}
		curregionptr++;
	}
	filename="region5\\";
	multindex=1;
	for(i=0;i<5;i++)
	{
		curfilename=talloc(char,100);
		if(curfilename==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		strindex=(int)strlen(filename);
		mcpy(curfilename,filename,char,strindex+1);
		curfilename[strindex-2]=curfilename[strindex-2]+i;

		codetype=codetype(RAID6,CAUCHYORGRS);//计算编码类型
		codepara=talloc(CODEPARA,1);
		if(codepara==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		GLOBAL_set_CODEPARA_data(codepara,
										8,//伽罗华域大小
										5,//k
										2,//m
										7,//n
										5,//d
										NOVALUE//针对扇区编码的块数
										);//设定CODEPARA数据值
		strdes=talloc(STRIPDES,1);
		if(strdes==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		//开始描述条带
		GLOBAL_set_STRIPDES_data(strdes,
									8,//每一个条带包括的行数,即chunk数
									glodiskblockptr,//所需的disk列表
									glodiskidlist,//当前磁盘id
									disknum,//存在的即一个条带的列数，磁盘数，通常这个数量和region的disk数一致
									chksize_KB(16*multindex)//每一个CHUNK的大小以字节为单位
									);//设定STRIPDES数据值
		multindex=multindex*2;
		resTF=profile_region_setup(curregionptr,codetype,codepara,strdes,totalsize,
									glodeviceidlist,glodeviceblockptr,devicenum,
									glodiskidlist,glodiskblockptr,disknum,
									curfilename,userprofileptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","region can't setup");
			return FALSE;
		}
		resTF=profile_map_define_intial(curregionptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","RAID5 can't define");
			return FALSE;
		}
		curregionptr++;
	}
	filename="region10\\";
	multindex=1;
	for(i=0;i<5;i++)
	{
		curfilename=talloc(char,100);
		if(curfilename==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		strindex=(int)strlen(filename);
		mcpy(curfilename,filename,char,strindex+1);
		curfilename[strindex-2]=curfilename[strindex-2]+i;

		codetype=codetype(RAID6,CAUCHYRS);//计算编码类型
		codepara=talloc(CODEPARA,1);
		if(codepara==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		GLOBAL_set_CODEPARA_data(codepara,
										8,//伽罗华域大小
										5,//k
										2,//m
										7,//n
										5,//d
										NOVALUE//针对扇区编码的块数
										);//设定CODEPARA数据值

		strdes=talloc(STRIPDES,1);
		if(strdes==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		//开始描述条带
		GLOBAL_set_STRIPDES_data(strdes,
									8,//每一个条带包括的行数,即chunk数
									glodiskblockptr,//所需的disk列表
									glodiskidlist,//当前磁盘id
									disknum,//存在的即一个条带的列数，磁盘数，通常这个数量和region的disk数一致
									chksize_KB(multindex*16)//每一个CHUNK的大小以字节为单位
									);//设定STRIPDES数据值
		multindex=multindex*2;
		resTF=profile_region_setup(curregionptr,codetype,codepara,strdes,totalsize,
									glodeviceidlist,glodeviceblockptr,devicenum,
									glodiskidlist,glodiskblockptr,disknum,
									curfilename,userprofileptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","region can't setup");
			return FALSE;
		}
		resTF=profile_map_define_intial(curregionptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","RAID5 can't define");
			return FALSE;
		}
		curregionptr++;
	}
	filename="region15\\";
	multindex=1;
	for(i=0;i<5;i++)
	{
		curfilename=talloc(char,100);
		if(curfilename==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		strindex=(int)strlen(filename);
		mcpy(curfilename,filename,char,strindex+1);
		curfilename[strindex-2]=curfilename[strindex-2]+i;

		codetype=codetype(RAID6,EVENODD);//计算编码类型
		codepara=talloc(CODEPARA,1);
		if(codepara==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		GLOBAL_set_CODEPARA_data(codepara,
										4,//伽罗华域大小
										5,//k
										2,//m
										7,//n
										5,//d
										NOVALUE//针对扇区编码的块数
										);//设定CODEPARA数据值

		strdes=talloc(STRIPDES,1);
		if(strdes==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		//开始描述条带
		GLOBAL_set_STRIPDES_data(strdes,
									4,//每一个条带包括的行数,即chunk数
									glodiskblockptr,//所需的disk列表
									glodiskidlist,//当前磁盘id
									disknum,//存在的即一个条带的列数，磁盘数，通常这个数量和region的disk数一致
									chksize_KB(multindex*16)//每一个CHUNK的大小以字节为单位
									);//设定STRIPDES数据值
		multindex=multindex*2;
		resTF=profile_region_setup(curregionptr,codetype,codepara,strdes,totalsize,
									glodeviceidlist,glodeviceblockptr,devicenum,
									glodiskidlist,glodiskblockptr,disknum,
									curfilename,userprofileptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","region can't setup");
			return FALSE;
		}
		/*resTF=profile_map_define_intial(curregionptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","RAID5 can't define");
			return FALSE;
		}*/
		curregionptr++;
	}
	/*RDPdeviceid=talloc(UINT64,6);
	if(RDPdeviceid==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	RDPdeviceblockptr=talloc(DEVICEBLOCK,6);
	if(RDPdeviceblockptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	curRDPdeviceblockptr=RDPdeviceblockptr;

	RDPdiskid=talloc(UINT64,6);
	if(RDPdiskid==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	RDPdiskblockptr=talloc(DISKBLOCK,6);
	if(RDPdiskblockptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	curRDPdiskblockptr=RDPdiskblockptr;
	curglodeviceblockptr=glodeviceblockptr;
	curglodiskblockptr=glodiskblockptr;
	for(i=0;i<6;i++)
	{
		RDPdiskid[i]=glodiskidlist[i];
		curRDPdeviceblockptr->deviceid=curglodeviceblockptr->deviceid;
		curRDPdeviceblockptr->deviceptr=curglodeviceblockptr->deviceptr;

		curRDPdiskblockptr->diskid=curglodiskblockptr->diskid;
		curRDPdiskblockptr->diskptr=curglodiskblockptr->diskptr;
	}*/
	disknum=6;
	devicenum=6;
	filename="region20\\";
	multindex=1;
	for(i=0;i<5;i++)
	{
		curfilename=talloc(char,100);
		if(curfilename==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		strindex=(int)strlen(filename);
		mcpy(curfilename,filename,char,strindex+1);
		curfilename[strindex-2]=curfilename[strindex-2]+i;

		codetype=codetype(RAID6,RDP);//计算编码类型
		codepara=talloc(CODEPARA,1);
		if(codepara==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		GLOBAL_set_CODEPARA_data(codepara,
										4,//伽罗华域大小
										4,//k
										2,//m
										6,//n
										4,//d
										NOVALUE//针对扇区编码的块数
										);//设定CODEPARA数据值
		strdes=talloc(STRIPDES,1);
		if(strdes==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		//开始描述条带
		//有一点特殊不能用全局的diskid和指针

		GLOBAL_set_STRIPDES_data(strdes,
									4,//每一个条带包括的行数,即chunk数
									glodiskblockptr,//所需的disk列表
									glodiskidlist,//当前磁盘id
									disknum,//存在的即一个条带的列数，磁盘数，通常这个数量和region的disk数一致
									chksize_KB(multindex*16)//每一个CHUNK的大小以字节为单位
									);//设定STRIPDES数据值
		multindex=multindex*2;
		resTF=profile_region_setup(curregionptr,codetype,codepara,strdes,totalsize,
									glodeviceidlist,glodeviceblockptr,devicenum,
									glodiskidlist,glodiskblockptr,disknum,
									curfilename,userprofileptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","region can't setup");
			return FALSE;
		}
		/*resTF=profile_map_define_intial(curregionptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","RAID5 can't define");
			return FALSE;
		}*/
		curregionptr++;


	}
	//liberation和bloth在生成时，会生成6个
	disknum=7;
	devicenum=7;
	filename="region25\\";
	multindex=1;
	for(i=0;i<5;i++)
	{
		curfilename=talloc(char,100);
		if(curfilename==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		strindex=(int)strlen(filename);
		mcpy(curfilename,filename,char,strindex+1);
		curfilename[strindex-2]=curfilename[strindex-2]+i;

		codetype=codetype(RAID6,LIBERATION);//计算编码类型
		codepara=talloc(CODEPARA,1);
		if(codepara==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		GLOBAL_set_CODEPARA_data(codepara,
										6,//伽罗华域大小
										5,//k
										2,//m
										7,//n
										5,//d
										NOVALUE//针对扇区编码的块数
										);//设定CODEPARA数据值
		strdes=talloc(STRIPDES,1);
		if(strdes==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		//开始描述条带
		GLOBAL_set_STRIPDES_data(strdes,
									6,//每一个条带包括的行数,即chunk数
									glodiskblockptr,//所需的disk列表
									glodiskidlist,//当前磁盘id
									disknum,//存在的即一个条带的列数，磁盘数，通常这个数量和region的disk数一致
									chksize_KB(multindex*16)//每一个CHUNK的大小以字节为单位
									);//设定STRIPDES数据值
		multindex=multindex*2;
		resTF=profile_region_setup(curregionptr,codetype,codepara,strdes,totalsize,
									glodeviceidlist,glodeviceblockptr,devicenum,
									glodiskidlist,glodiskblockptr,disknum,
									curfilename,userprofileptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","region can't setup");
			return FALSE;
		}
		curregionptr++;
	}
	filename="region30\\";
	multindex=1;
	disknum=6;
	devicenum=6;
	for(i=0;i<5;i++)
	{
		curfilename=talloc(char,100);
		if(curfilename==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		strindex=(int)strlen(filename);
		mcpy(curfilename,filename,char,strindex+1);
		curfilename[strindex-2]=curfilename[strindex-2]+i;

		codetype=codetype(RAID6,BLAUMROTH);//计算编码类型
		codepara=talloc(CODEPARA,1);
		if(codepara==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		GLOBAL_set_CODEPARA_data(codepara,
										4,//伽罗华域大小
										4,//k
										2,//m
										6,//n
										4,//d
										NOVALUE//针对扇区编码的块数
										);//设定CODEPARA数据值

		strdes=talloc(STRIPDES,1);
		if(strdes==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		//开始描述条带
		GLOBAL_set_STRIPDES_data(strdes,
									6,//每一个条带包括的行数,即chunk数
									glodiskblockptr,//所需的disk列表
									glodiskidlist,//当前磁盘id
									disknum,//存在的即一个条带的列数，磁盘数，通常这个数量和region的disk数一致
									chksize_KB(multindex*16)//每一个CHUNK的大小以字节为单位
									);//设定STRIPDES数据值
		multindex=multindex*2;
		resTF=profile_region_setup(curregionptr,codetype,codepara,strdes,totalsize,
									glodeviceidlist,glodeviceblockptr,devicenum,
									glodiskidlist,glodiskblockptr,disknum,
									curfilename,userprofileptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","region can't setup");
			return FALSE;
		}
		/*resTF=profile_map_define_intial(curregionptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","RAID5 can't define");
			return FALSE;
		}*/
		curregionptr++;
	}
	/*codetype=codetype(RAID5,Nulltype);//计算编码类型
	codepara=talloc(CODEPARA,1);
	if(codepara==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	GLOBAL_set_CODEPARA_data(codepara,
									8,//伽罗华域大小
									6,//k
									1,//m
									6,//n
									5,//d
									NOVALUE//针对扇区编码的块数
									);//设定CODEPARA数据值
	strdes=talloc(STRIPDES,1);
	if(strdes==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	//开始描述条带
	GLOBAL_set_STRIPDES_data(strdes,
									1,//每一个条带包括的行数,即chunk数
									glodiskblockptr,//所需的disk列表
									glodiskidlist,//当前磁盘id
									disknum,//存在的即一个条带的列数，磁盘数，通常这个数量和region的disk数一致
									chksize_KB(64)//每一个CHUNK的大小以字节为单位
									);//设定STRIPDES数据值
	totalsize=chksize_MB(64);
	GLOBAL_set_REGION_data(regionptr,codetype,codepara,totalsize,
								  NULL,NULL,NOVALUE,//包括的file的列表,文件中进行更新
								  glodiskblockptr,glodiskidlist,disknum,//Disk的列表
								  glodeviceblockptr,glodeviceidlist,devicenum,//device列表
								  strdes,NULL,NULL,NOVALUE,//条带个数
								  NOVALUE,NOVALUE,//chunk和stripsect总数
								  NULL,NOVALUE,//根文件指针,文件中进行更新
								  EMPTY//当前存储状态
								  );//设定当前REGION中的数据
	//信息已足可以格式化了
	resTF=profile_region_format_PTR(regionptr);
	if(resTF==FALSE)
	{
		show_error("systemcom","system_reset_format","region can't format");
		return FALSE;
	}
	//初始化filemeta
	filemetaptr=talloc(FILEMETA,1);
	if(filemetaptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	filemetagroupptr=talloc(FILEMETAGROUP,1);
	if(filemetagroupptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	glofileidlist=talloc(UINT64,1);
	if(glofileidlist==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	//设定数据
	filemetaptr->FileID=get_state_glofileid();
	currentid=get_state_glofileid();//先让我记一下
	set_state_glofileid_add(1);
	fileinfptr=NULL;//由于只有初始目录因此没有数据
	GLOBAL_set_FILEMETA_data(filemetaptr,"region0",NOVALUE,NOVALUE,DICTKIND,
									regionptr,regionptr->RegionID,//上层region指针
									userprofileptr,userprofileptr->UserID,//文件所有者，暂时设定为
									NOVALUE,NULL,//上一次文件夹，根目录为NULL
									NULL,NULL,NONE,//暂时没有数据，文件块指针主要指向当前目录下一级元数据块
									Nowtime,//将创建和更新时间都设定为当前时间
									Nowtime,
									NULL//用于存放数据块信息
									);//设定FILEMETA数据值
	//两个用户的
	curuserprofileptr=userprofileptr;
	for(i=0;i<2;i++)
	{
		userlocationptr=curuserprofileptr->userlocinf;
		userlocationptr->DICid=currentid;
		userlocationptr->DICpath="\\region0\\";
	}
	//将数据赋值会region区域
	regionptr->rootfileid=currentid;
	regionptr->fileroot=filemetaptr;
	filemetagroupptr->filemetagroup=filemetaptr;
	filemetagroupptr->grouposize=1;
	regionptr->filemetalist=filemetagroupptr;
	//还是要开空间
	glofileidlist[0]=currentid;
	regionptr->fileid=glofileidlist;
	regionptr->filenum=1;*/
	//在同步之间先将元数据地址空间写入
	set_state_glometapath(".\\metadata\\");
	//最后将数据同步到磁盘
	resTF=profile_metadata_sync();
	if(resTF==FALSE)
	{
		show_error("systemcom","system_reset_format","metadata can't snyc");
		return FALSE;
	}
	//确定校验块位置
	
	return TRUE;
}

//同步数据
//同步元数据
int systemcom_metadata_sync()
{
	profile_metadata_sync();
	return TRUE;
}
//同步chunk数据
int systemcom_chunkdata_sync()
{
	profile_GLOBAL_chunk_data_sync();
	return TRUE;
}
//将当前的
int systemcom_system_buffer_clean()
{
	GLOPUSHLIST *pushlist;
	pushlist=get_state_buffer_pushlist();
	pushlist->currentbuffersize=0;
	pushlist->currentbuffersize=0;
	return TRUE;
}
//更改push信息指令
int systemcom_push_time(int pushtime,int maxbuffersize)
{
	//仅仅直选赋值即可
	GLOPUSHLIST *pushlist;
	pushlist=get_state_buffer_pushlist();
	pushlist->glopushtime=pushtime;
	pushlist->maxbuffersize=maxbuffersize;
	return TRUE;
}