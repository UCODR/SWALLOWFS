#include "mysql.h"
MYSQL_RES *mysql_FILELAYER_select_query(char *querystr)
{
	int resTF;
	int qlength;
	MYSQL_RES *mysqlresptr;
	mysqlresptr=NULL;
	//先检测一下有没有初始化
	/*if(mysqlresptr==NULL)
	{
		mysqlresptr=talloc(MYSQL_RES,1);
		if(mysqlresptr==NULL)
		{
			show_error("mysql_FILELAYER","select_query","No memory");
			return FALSE;
		}
	}*/
	resTF=mysql_FILELAYER_check_intial();
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","select_query","mysql can't intial");
		return FALSE;
	}
	qlength=strlen(querystr)+1;
	resTF=mysql_real_query(&mysqlptr,querystr,qlength);
	if(resTF!=QTRUE)
	{
		show_error("mysql_FILELAYER","select_query","mysql can't execute");
		return NULL;
	}
	mysqlresptr=mysql_store_result(&mysqlptr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","select_query","result can't create");
		return NULL;
	}
	return mysqlresptr;
}
int mysql_FILELAYER_notselect_query(char *querystr)
{
	int resTF;
	int qlength;
	resTF=mysql_FILELAYER_check_intial();
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","notselect_query","mysql can't intial");
		return FALSE;
	}
	qlength=strlen(querystr);
	resTF=mysql_real_query(&mysqlptr,querystr,qlength);
	if(resTF!=QTRUE)
	{
		show_error("mysql_FILELAYER","notselect_query","query can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_update_query(char *querystr)
{
	int resTF;
	resTF=mysql_FILELAYER_notselect_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","update_query","update can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_insert_query(char *querystr)
{
	int resTF;
	resTF=mysql_FILELAYER_notselect_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","insert_query","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_delete_query(char *querystr)
{
	int resTF;
	resTF=mysql_FILELAYER_notselect_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","delete_query","delete can't execute");
		return FALSE;
	}
	return TRUE;
}

int mysql_FILELAYER_invert_DB_string(char *scrstr)
{
	int scrstrlength;	
	char *endstr;
	char *curscrstr,*nextstr;
	int ncopy;//需要拷贝的数据量
	scrstrlength=strlen(scrstr);
	endstr=scrstr+scrstrlength;
	curscrstr=scrstr;
	while((*curscrstr)!='\0')
	{
		if(*curscrstr=='\\')
		{
			ncopy=endstr-curscrstr+1;
			nextstr=curscrstr+1;
			mcpy(nextstr,curscrstr,char,ncopy);
			endstr++;
			curscrstr++;
		}
		curscrstr++;
	}
	return TRUE;
}


int mysql_FILELAYER_chunk_select(CHUNK *chunkptr)//查询
{
	//int resTF;
	int isparity,sizenum,storestate;
	UINT64 chunkid,regionid,stripid,stripsectid,diskid,deviceid,fileid;
	CHUNKPATH *chkpath;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;

	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","chunktable_select","No memory");
		return FALSE;
	}
	/*mysqlresptr=talloc(MYSQL_RES,1);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","chunktable_select","No memory");
		return FALSE;
	}*/
	chkpath=chunkptr->chkpath;
	chunkid=chunkptr->ChunkID;
	sprintf(querystr,"SELECT chunkid,isparity,sizenum,regionid,stripid,stripsectid,diskid,deviceid,fileid,storestate FROM chunk WHERE chunkid=%I64d",chunkid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","chunktable_select","chunk can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","chunktable_select","mysqlrow can't create");
		return FALSE;
	}
	STRTOINT64(mysqlrow[0],chunkid);
	STRTOINT32(mysqlrow[1],isparity);
	STRTOINT32(mysqlrow[2],sizenum);
	STRTOINT64(mysqlrow[3],regionid);
	STRTOINT64(mysqlrow[4],stripid);
	STRTOINT64(mysqlrow[5],stripsectid);
	STRTOINT64(mysqlrow[6],diskid);
	STRTOINT64(mysqlrow[7],deviceid);
	STRTOINT64(mysqlrow[8],fileid);
	STRTOINT32(mysqlrow[9],storestate);
	GLOBAL_set_CHUNK_data(chunkptr,isparity,
						chkpath,sizenum,NULL,
						regionid,NULL,stripid,NULL,stripsectid,NULL,
						diskid,NULL,deviceid,NULL,
						fileid,NULL,storestate);
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_chunk_update(CHUNK *chunkptr)//更新
{
	int resTF;
	UINT64 chunkid;
	chunkid=chunkptr->ChunkID;
	resTF=mysql_FILELAYER_chunk_delete(chunkid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","chunktable_update","chunk can't delete");
		return FALSE;
	}
	resTF=mysql_FILELAYER_chunk_insert(chunkptr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","chunktable_update","chunk can't insert");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_chunk_insert(CHUNK *chunkptr)//插入
{
	int resTF;
	int isparity,sizenum,storestate;
	UINT64 chunkid,regionid,stripid,stripsectid,diskid,deviceid,fileid;
	char *querystr;
	
	chunkid=chunkptr->ChunkID;
	isparity=chunkptr->isparity;
	sizenum=chunkptr->sizenum;
	regionid=chunkptr->regionid;
	stripid=chunkptr->stripid;
	stripsectid=chunkptr->stripsectid;
	diskid=chunkptr->diskid;
	deviceid=chunkptr->deviceid;
	fileid=chunkptr->fileid;
	storestate=chunkptr->storestate;
	//
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","chunktable_insert","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"insert delayed into chunk(ChunkID,isparity,sizenum,regionid,stripid,stripsectid,diskid,deviceid,fileid,storestate) values (%I64d,%d,%d,%I64d,%I64d,%I64d,%I64d,%I64d,%I64d,%d)",
		chunkid,isparity,sizenum,regionid,stripid,stripsectid,diskid,deviceid,fileid,storestate);
	resTF=mysql_FILELAYER_insert_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","chunktable_insert","chunk can't insert");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_chunk_delete(UINT64 chunkid)//删除
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","chunktable_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from chunk where ChunkID=%I64d",chunkid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","chunktable_delete","chunk can't delete");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_chunk_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","chunktable_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from chunk");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","chunktable_delete","chunk can't delete");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_device_select(DEVICE *deviceptr)
{
	//int resTF;
	UINT64 DeviceID;
	int Devicetype,processnum,disknum,regionnum,storestate;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	DeviceID=deviceptr->DeviceID;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","devicetable_select","No memory");
		return FALSE;
	}
	/*mysqlresptr=talloc(MYSQL_RES,1);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","devicetable_select","No memory");
		return FALSE;
	}*/
	sprintf(querystr,
		"select DeviceID,Devicetype,processnum,disknum,regionnum,storestate from device where DeviceID=%I64d",
		DeviceID);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","devicetable_select","query can't execute");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","devicetable_select","mysqlrow can't create");
		return FALSE;
	}
	STRTOINT64(mysqlrow[0],DeviceID);
	STRTOINT32(mysqlrow[1],Devicetype);
	STRTOINT32(mysqlrow[2],processnum);
	STRTOINT32(mysqlrow[3],disknum);
	STRTOINT32(mysqlrow[4],regionnum);
	STRTOINT32(mysqlrow[5],storestate);

	GLOBAL_set_DEVICE_data(deviceptr,Devicetype,
							processnum,NULL,
							NULL,NULL,disknum,
							NULL,NULL,regionnum,
							storestate);

	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_device_update(DEVICE *deviceptr)
{
	int resTF;
	UINT64 DeviceID;
	DeviceID=deviceptr->DeviceID;
	resTF=mysql_FILELAYER_device_delete(DeviceID);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","devicetable_update","device can't delete");
		return FALSE;
	}
	resTF=mysql_FILELAYER_device_insert(deviceptr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","devicetable_update","device can't insert");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_device_insert(DEVICE *deviceptr)
{
	int resTF;
	UINT64 DeviceID;
	int Devicetype,processnum,disknum,regionnum,storestate;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","devicetable_insert","No memory");
		return FALSE;
	}
	DeviceID=deviceptr->DeviceID;
	Devicetype=deviceptr->Devicetype;
	processnum=deviceptr->processnum;
	disknum=deviceptr->disknum;
	regionnum=deviceptr->regionnum;
	storestate=deviceptr->storestate;
	sprintf(querystr,
		"insert delayed into device(DeviceID,Devicetype,processnum,disknum,regionnum,storestate) values (%I64d,%d,%d,%d,%d,%d)",
		DeviceID,Devicetype,processnum,disknum,regionnum,storestate);
	resTF=mysql_FILELAYER_insert_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","devicetable_insert","device can't insert");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_device_delete(UINT64 deviceid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","devicetable_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from device where DeviceID=%I64d",deviceid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","devicetable_delete","device can't delete");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_device_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","devicetable_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from device");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","devicetable_delete","device can't delete");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_devicediskid_select(UINT64 *diskid,UINT64 deviceid)
{
	//int resTF;
	int diskindex;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;

	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","devicediskid_select","No memory");
		return FALSE;
	}
	/*mysqlresptr=talloc(MYSQL_RES,1);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","devicediskid_select","No memory");
		return FALSE;
	}*/
	sprintf(querystr,
		"select diskid from devicediskid where deviceid=%I64d order by diskid asc",
		deviceid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==FALSE)
	{
		show_error("mysql_FILELAYER","devicediskid_select","select can't execute");
		return	FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","devicetable_select","mysqlrow can't create");
		return FALSE;
	}
	diskindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],diskid[diskindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		diskindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_devicediskid_update(UINT64 *diskid,int disknum,UINT64 deviceid)
{
	int resTF;
	resTF=mysql_FILELAYER_devicediskid_delete(deviceid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","devicediskid_update","devicediskid can't delete");
		return FALSE;
	}
	resTF=mysql_FILELAYER_devicediskid_insert(diskid,disknum,deviceid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","devicediskid_update","devicediskid can't insert");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_devicediskid_insert(UINT64 *diskid,int disknum,UINT64 deviceid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","devicediskid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<disknum;i++)
	{
		sprintf(querystr,
			"insert delayed into devicediskid(deviceid,diskid) values (%I64d,%I64d)",
			deviceid,diskid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","devicediskid_update","devicediskid can't insert");
			return FALSE;
		}
	}
	return TRUE;
}
int mysql_FILELAYER_devicediskid_delete(UINT64 deviceid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","devicediskid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from devicediskid where deviceid=%I64d",
		deviceid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","devicediskid_delete","device can't delete");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_devicediskid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","devicediskid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from devicediskid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","devicediskid_delete_all","device can't delete");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_deviceprocessid_select(int *process,UINT64 deviceid)
{
	//int resTF;
	int processindex;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","deviceprocessid_select","No memory");
		return FALSE;
	}
	/*mysqlresptr=talloc(MYSQL_RES,1);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","deviceprocessid_select","No memory");
		return FALSE;
	}*/
	sprintf(querystr,"select process from deviceprocessid where deviceid=%I64d order by process acs",deviceid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","deviceprocessid_select","No memory");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","deviceprocessid_select","mysqlrow can't create");
		return FALSE;
	}
	processindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT32(mysqlrow[0],process[processindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		processindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_deviceprocessid_update(int *process,int processnum,UINT64 deviceid)
{
	int resTF;
	resTF=mysql_FILELAYER_deviceprocessid_delete(deviceid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","deviceprocessid_update","deviceprocessid can't delete");
		return FALSE;
	}
	resTF=mysql_FILELAYER_deviceprocessid_insert(process,processnum,deviceid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","deviceprocessid_update","deviceprocessid can't insert");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_deviceprocessid_insert(int *process,int processnum,UINT64 deviceid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","deviceprocessid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<processnum;i++)
	{
		sprintf(querystr,
			"insert delayed into deviceprocessid(deviceid,process) value (%I64d,%I64d)",
			deviceid,process[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","deviceprocessid_insert","deviceprocessid can't insert");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_deviceprocessid_delete(UINT64 deviceid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","deviceprocessid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from deviceprocessid where deviceid=%I64d",deviceid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","deviceprocessid_delete","deviceprocessid can't delete");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_deviceprocessid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","deviceprocessid_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from deviceprocessid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","deviceprocessid_delete","deviceprocessid can't delete");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_deviceregionid_select(UINT64 *regionid,UINT64 deviceid)
{
	//int resTF;
	int regionindex;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","deviceprocessid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select regionid from deviceregionid where deviceid=%I64d order by regionid",deviceid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","deviceprocessid_select","query can't excute");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","deviceprocessid_select","mysqlrow can't create");
		return FALSE;
	}
	regionindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],regionid[regionindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		regionindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_deviceregionid_update(UINT64 *regionid,int regionum,UINT64 deviceid)
{
	int resTF;
	resTF=mysql_FILELAYER_deviceregionid_delete(deviceid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","deviceregionid_update","deviceregionid can't delete");
		return FALSE;
	}
	resTF=mysql_FILELAYER_deviceregionid_insert(regionid,regionum,deviceid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","deviceregionid_update","deviceregionid can't insert");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_deviceregionid_insert(UINT64 *regionid,int regionum,UINT64 deviceid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","deviceregionid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<regionum;i++)
	{
		sprintf(querystr,
			"insert delayed into deviceregionid(deviceid,regionid) values (%I64d,%I64d)",
			deviceid,regionid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","deviceregionid_insert","deviceregionid can't insert");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_deviceregionid_delete(UINT64 deviceid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","deviceregionid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from deviceregionid where deviceid=%I64d",
		deviceid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","deviceregionid_delete","deviceregionid can't delete");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_deviceregionid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","deviceregionid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from deviceregionid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","deviceregionid_delete","deviceregionid can't delete");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_disk_select(DISK *diskptr)
{
	UINT64 DiskID;
	int disktype,capability;
	UINT64 volumn;
	int regionnum;
	UINT64 deviceid;
	char *diskpath;
	int diskpathlength;
	int storestate;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	char *querystr;
	
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","disk_select","No memory");
		return FALSE;
	}
	DiskID=diskptr->DiskID;
	sprintf(querystr,"select DiskID,disktype,capability,volumn,regionnum,"
			"deviceid,diskpath,storestate from disk where DiskID=%I64d",DiskID);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","disk_select","query can't excute");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","disk_select","mysqlrow can't create");
		return FALSE;
	}
	STRTOINT32(mysqlrow[1],disktype);
	STRTOINT32(mysqlrow[2],capability);
	STRTOINT64(mysqlrow[3],volumn);
	STRTOINT32(mysqlrow[4],regionnum);

	STRTOINT64(mysqlrow[5],deviceid);
	diskpathlength=strlen(mysqlrow[6])+1;

	diskpath=talloc(char,diskpathlength);
	if(diskpath==NULL)
	{
		show_error("mysql_FILELAYER","disk_select","No memory");
		return FALSE;
	}
	STRTOINT32(mysqlrow[7],storestate);
	GLOBAL_set_DISK_data(diskptr,disktype,capability,volumn,
						NULL,NULL,regionnum,NULL,deviceid,
						diskpath,storestate);
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_disk_update(DISK *diskptr)
{
	int resTF;
	UINT64 diskid;
	diskid=diskptr->DiskID;
	resTF=mysql_FILELAYER_disk_delete(diskid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","disk_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_disk_insert(diskptr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","disk_insert","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_disk_insert(DISK *diskptr)
{
	int resTF;
	char *querystr;
	UINT64 DiskID;
	int disktype,capability;
	UINT64 volumn;
	int regionnum;
	UINT64 deviceid;
	char *diskpath;
	int storestate;
	//UINT64 deviceid;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","disk_insert","No memory");
		return FALSE;
	}
	DiskID=diskptr->DiskID;
	disktype=diskptr->DiskTYPE;
	capability=diskptr->capability;
	volumn=diskptr->volumn;
	regionnum=diskptr->regionnum;
	deviceid=diskptr->deviceid;
	diskpath=diskptr->diskpath;
	storestate=diskptr->storestate;

	sprintf(querystr,"insert delayed into disk(DiskID,disktype,capability,volumn,regionnum"
			",deviceid,diskpath,storestate) values (%I64d,%d,%d,%I64d,%d,%I64d,'%s',%d)"
			,DiskID,disktype,capability,volumn,regionnum,deviceid,diskpath,storestate);
	mysql_FILELAYER_invert_DB_string(querystr);
	resTF=mysql_FILELAYER_insert_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","disk_insert","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_disk_delete(UINT64 diskid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","disk_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from disk where DiskID=%I64d",diskid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","disk_delete","delete can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_disk_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","disk_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from disk");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","disk_delete_all","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_diskregionid_select(UINT64 *regionid,UINT64 diskid)
{
	//int resTF;
	int regionindex;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","diskregionid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"select regionid from diskregionid where diskid=%I64d order by regionid asc",
		diskid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","diskregionid_select","select can't execute");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","diskregionid_select","mysqlrow can't create");
		return FALSE;
	}
	regionindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],regionid[regionindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		regionindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_diskregionid_update(UINT64 *regionid,int regionnum,UINT64 diskid)
{
	int resTF;
	resTF=mysql_FILELAYER_diskregionid_delete(diskid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","diskregionid_update","diskregionid can't delete");
		return FALSE;
	}
	resTF=mysql_FILELAYER_diskregionid_insert(regionid,regionnum,diskid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","diskregionid_update","diskregionid can't insert");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_diskregionid_insert(UINT64 *regionid,int regionnum,UINT64 diskid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","diskregionid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<regionnum;i++)
	{
		sprintf(querystr,"insert delayed into diskregionid(diskid,regionid) values (%I64d,%I64d)",
				diskid,regionid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","diskregionid_insert","diskregionid can't insert");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_diskregionid_delete(UINT64 diskid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","diskregionid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from diskregionid where diskid=%I64d",
		diskid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","diskregionid_delete","dalete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_diskregionid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","diskregionid_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from diskregionid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","diskregionid_delete_all","dalete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_filechunkid_select(UINT64 *chunkid,UINT64 fileid)
{
	//int resTF;
	int chunkindex;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filechunkid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select chunkid from filechunkid where fileid=%I64d order by findex asc",fileid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","filechunkid_select","chunkfileid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","devicetable_select","mysqlrow can't create");
		return FALSE;
	}
	chunkindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],chunkid[chunkindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		chunkindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filechunkid_update(UINT64 *chunkid,int chunknum,UINT64 fileid)
{
	int resTF;
	resTF=mysql_FILELAYER_filechunkid_delete(fileid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filechunkid_update","filechunkid can't delete");
		return FALSE;
	}
	resTF=mysql_FILELAYER_filechunkid_insert(chunkid,chunknum,fileid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filechunkid_update","filechunkid can't insert");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_filechunkid_insert(UINT64 *chunkid,int chunknum,UINT64 fileid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filechunkid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<chunknum;i++)
	{
		sprintf(querystr,
			"insert delayed into filechunkid(fileid,chunkid,findex) values (%I64d,%I64d,%d)",
			fileid,chunkid[i],i);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","filechunkid_select","insert can't execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filechunkid_delete(UINT64 fileid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filechunkid_insert","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from filechunkid where fileid=%I64d",
		fileid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filechunkid_delete","delete can;t execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filechunkid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filechunkid_insert","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from filechunkid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filechunkid_delete","delete can;t execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_filechunkpath_select(CHUNKPATH *chunkpath,UINT64 fileid)
{
	CHUNKPATH *curchunkpath;
	char *querystr;
	UINT64 chunkid,stripsectid,stripid,regionid;
	int chunkarrayid,stripsectarrayid,striparrayid,regionarrayid;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filechunkpath_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select chunkid,chunkarrayid,stripsectid,stripsectarrayid,"
					 "stripid,striparrayid,regionid,regionarrayid"
					 " from filechunkpath where fileid=%I64d order by findex asc",fileid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","filechunkpath_select","chunkfileid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","devicetable_select","mysqlrow can't create");
		return FALSE;
	}
	curchunkpath=chunkpath;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],chunkid);
		STRTOINT32(mysqlrow[1],chunkarrayid);
		STRTOINT64(mysqlrow[2],stripsectid);
		STRTOINT32(mysqlrow[3],stripsectarrayid);
		STRTOINT64(mysqlrow[4],stripid);
		STRTOINT32(mysqlrow[5],striparrayid);
		STRTOINT64(mysqlrow[6],regionid);
		STRTOINT32(mysqlrow[7],regionarrayid);
		GLOBAL_set_CHUNKPATH_data(curchunkpath,regionid,regionarrayid,NULL,
								stripid,striparrayid,NULL,stripsectid,stripsectarrayid,NULL,
								chunkid,chunkarrayid,NULL);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		curchunkpath++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filechunkpath_update(CHUNKPATH *chunkpath,int chunknum,UINT64 fileid)
{
	int resTF;
	resTF=mysql_FILELAYER_filechunkpath_delete(fileid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filechunkpath_update","delete can't execute");
		return FALSE; 
	}
	resTF=mysql_FILELAYER_filechunkpath_insert(chunkpath,chunknum,fileid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filechunkpath_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_filechunkpath_insert(CHUNKPATH *chunkpath,int chunknum,UINT64 fileid)
{
	int i,resTF;
	UINT64 chunkid,stripsectid,stripid,regionid;
	int chunkarrayid,stripsectarrayid,striparrayid,regionarrayid;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filechunkpath_insert","No memory");
		return FALSE;
	}
	for(i=0;i<chunknum;i++)
	{
		chunkid=chunkpath->chunkid;
		chunkarrayid=chunkpath->chunkarrayid;

		stripsectid=chunkpath->stripsectid;
		stripsectarrayid=chunkpath->stripsectarrayid;

		stripid=chunkpath->stripid;
		striparrayid=chunkpath->striparrayid;

		regionid=chunkpath->regionid;
		regionarrayid=chunkpath->regionarrayid;

		sprintf(querystr,"insert delayed into filechunkpath(fileid,chunkid,chunkarrayid,"
						 "stripsectid,stripsectarrayid,stripid,striparrayid,"
						 "regionid,regionarrayid,findex) values (%I64d,%I64d,%d,"
						 "%I64d,%d,%I64d,%d,%I64d,%d,%d)",
						 fileid,chunkid,chunkarrayid,stripsectid,stripsectarrayid,
						 stripid,striparrayid,regionid,regionarrayid,i);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","filechunkpath_insert","insert can't execute");
			return FALSE;
		}
		chunkpath++;
	}
	return TRUE;
}
int mysql_FILELAYER_filechunkpath_delete(UINT64 fileid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filechunkpath_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from filechunkpath where fileid=%I64d",fileid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filechunkpath_delete_all","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filechunkpath_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filechunkpath_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from filechunkpath");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filechunkpath_delete_all","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_filedeviceid_select(UINT64 *deviceid,UINT64 fileid)
{
	//int resTF;
	int deviceindex;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filedeviceid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select deviceid from filedeviceid where fileid=%I64d order by deviceid asc",fileid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","filedeviceid_select","fileid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","filedeviceid_select","mysqlrow can't create");
		return FALSE;
	}
	deviceindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],deviceid[deviceindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		deviceindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filedeviceid_update(UINT64 *deviceid,int devicenum,UINT64 fileid)
{
	int resTF;
	resTF=mysql_FILELAYER_filedeviceid_delete(fileid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filedeviceid_update","filedeviceid can't delete");
		return FALSE;
	}
	resTF=mysql_FILELAYER_filedeviceid_insert(deviceid,devicenum,fileid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filedeviceid_update","filedeviceid can't insert");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_filedeviceid_insert(UINT64 *deviceid,int devicenum,UINT64 fileid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filedeviceid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<devicenum;i++)
	{
		sprintf(querystr,
			"insert delayed into filedeviceid(fileid,deviceid) values (%I64d,%I64d)",
			fileid,deviceid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","filedeviceid_select","insert can't execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filedeviceid_delete(UINT64 fileid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filedeviceid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from filedeviceid where fileid=%I64d",
		fileid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filedeviceid_select","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filedeviceid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filedeviceid_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from filedeviceid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filedeviceid_select","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_filediskid_select(UINT64 *diskid,UINT64 fileid)
{
	//int resTF;
	int diskindex;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filediskid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select diskid from filediskid where fileid=%I64d order by diskid asc",fileid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","filediskid_select","filediskid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","filediskid_select","mysqlrow can't create");
		return FALSE;
	}
	diskindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],diskid[diskindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		diskindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filediskid_update(UINT64 *diskid,int disknum,UINT64 fileid)
{
	int resTF;
	
	resTF=mysql_FILELAYER_filediskid_delete(fileid);
	if(resTF==FALSE)
	{
		show_error(" mysql_FILELAYER","filediskid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_filediskid_insert(diskid,disknum,fileid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filediskid_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_filediskid_insert(UINT64 *diskid,int disknum,UINT64 fileid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filediskid_insert","No meomory");
		return FALSE;
	}
	for(i=0;i<disknum;i++)
	{
		sprintf(querystr,
			"insert delayed into filediskid(fileid,diskid) values (%I64d,%I64d)",
			fileid,diskid[i]);
		resTF=mysql_FILELAYER_delete_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","filediskid_insert","delete can't execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filediskid_delete(UINT64 fileid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filediskid_delete","No meomory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from filediskid where fileid=%I64d",
		fileid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filediskid_delete","delete can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_filediskid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filedeviceid_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from filediskid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filediskid_delete_all","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_filemeta_select(FILEMETA *fmetaptr)
{
	//int resTF;
	//FILEINF *filechunkinf;
	UINT64 FileID;
	char *filename;
	int filenamelength;
	UINT64 filesize;
	int ACList,filetype,subfilenum;
	UINT64 userid,parentid;
	struct tm *createtime,*updatetime;
	int createtime1,createtime2,createtime3,createtime4,createtime5;
	int createtime6,createtime7,createtime8,createtime9;
	int updatetime1,updatetime2,updatetime3,updatetime4,updatetime5;
	int updatetime6,updatetime7,updatetime8,updatetime9;
	UINT64 regionid;
	int chunknum,devicenum,disknum,stripsectnum,stripnum;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	//struct tm *createtime,*updatetime;
	FILEINF *filechunkinf;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filemeta_select","No memory");
		return FALSE;
	}
	createtime=talloc(struct tm,1);
	if(createtime==NULL)
	{
		show_error("mysql_FILELAYER","filemeta_select","No memory");
		return FALSE;
	}
	updatetime=talloc(struct tm,1);
	if(updatetime==NULL)
	{
		show_error("mysql_FILELAYER","filemeta_select","No memory");
		return FALSE;
	}
	filechunkinf=talloc(FILEINF,1);
	if(filechunkinf==NULL)
	{
		show_error("mysql_FILELAYER","filemeta_select","No memory");
		return FALSE;
	}
	FileID=fmetaptr->FileID;
	sprintf(querystr,"select FileID,filename,filesize,ACList,filetype,"
					 "subfilenum,userid,parentid,"
					 "createtime1,createtime2,createtime3,createtime4,createtime5,"
					 "createtime6,createtime7,createtime8,createtime9,"
					 "updatetime1,updatetime2,updatetime3,updatetime4,updatetime5,"
					 "updatetime6,updatetime7,updatetime8,updatetime9,"
					 "regionid,chunknum,devicenum,disknum,"
					 "stripnum,stripsectnum from filemeta where FileID=%I64d",FileID);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","filemeta_select","filediskid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","filemeta_select","mysqlrow can't create");
		return FALSE;
	}
	STRTOINT64(mysqlrow[0],FileID);
	
	filenamelength=strlen(mysqlrow[1])+1;
	filename=talloc(char,filenamelength);
	if(filename==NULL)
	{
		show_error("mysql_FILELAYER","filemeta_select","No memory");
		return FALSE;
	}
	mcpy(filename,mysqlrow[1],char,filenamelength);

	STRTOINT64(mysqlrow[2],filesize);
	STRTOINT32(mysqlrow[3],ACList);
	STRTOINT32(mysqlrow[4],filetype);

	STRTOINT32(mysqlrow[5],subfilenum);
	STRTOINT64(mysqlrow[6],userid);
	STRTOINT64(mysqlrow[7],parentid);

	STRTOINT32(mysqlrow[8],createtime1);
	STRTOINT32(mysqlrow[9],createtime2);
	STRTOINT32(mysqlrow[10],createtime3);
	STRTOINT32(mysqlrow[11],createtime4);
	STRTOINT32(mysqlrow[12],createtime5);

	STRTOINT32(mysqlrow[13],createtime6);
	STRTOINT32(mysqlrow[14],createtime7);
	STRTOINT32(mysqlrow[15],createtime8);
	STRTOINT32(mysqlrow[16],createtime9);

	STRTOINT32(mysqlrow[17],updatetime1);
	STRTOINT32(mysqlrow[18],updatetime2);
	STRTOINT32(mysqlrow[19],updatetime3);
	STRTOINT32(mysqlrow[20],updatetime4);
	STRTOINT32(mysqlrow[21],updatetime5);

	STRTOINT32(mysqlrow[22],updatetime6);
	STRTOINT32(mysqlrow[23],updatetime7);
	STRTOINT32(mysqlrow[24],updatetime8);
	STRTOINT32(mysqlrow[25],updatetime9);

	STRTOINT64(mysqlrow[26],regionid);

	STRTOINT32(mysqlrow[27],chunknum);
	STRTOINT32(mysqlrow[28],devicenum);
	STRTOINT32(mysqlrow[29],disknum);
	STRTOINT32(mysqlrow[30],stripnum)
	STRTOINT32(mysqlrow[31],stripsectnum);
	
	GLOBAL_set_time(createtime,createtime1,createtime2,createtime3,createtime4,createtime5,
					createtime6,createtime7,createtime8,createtime9);
	GLOBAL_set_time(updatetime,updatetime1,updatetime2,updatetime3,updatetime4,updatetime5,
					updatetime6,updatetime7,updatetime8,updatetime9);
	GLOBAL_set_FILEINF_data(filechunkinf,FileID,NULL,fmetaptr,NULL,NULL,chunknum,
							NULL,regionid,NULL,NULL,devicenum,
							NULL,NULL,disknum,NULL,NULL,stripnum,
							NULL,NULL,stripsectnum);
	GLOBAL_set_FILEMETA_data(fmetaptr,filename,filesize,ACList,filetype,
							NULL,regionid,NULL,userid,parentid,NULL,
							NULL,NULL,subfilenum,createtime,updatetime,filechunkinf);
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filemeta_update(FILEMETA *fmetaptr)
{
	int resTF;
	UINT64 fileid;
	fileid=fmetaptr->FileID;
	resTF=mysql_FILELAYER_filemeta_delete(fileid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filemeta_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_filemeta_insert(fmetaptr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filemeta_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_filemeta_insert(FILEMETA *fmetaptr)
{
	int resTF;
	FILEINF *filechunkinf;
	UINT64 FileID;
	char *filename;
	UINT64 filesize;
	int ACList,filetype,subfilenum;
	UINT64 userid,parentid;
	struct tm *createtime,*updatetime;
	int createtime1,createtime2,createtime3,createtime4,createtime5;
	int createtime6,createtime7,createtime8,createtime9;
	int updatetime1,updatetime2,updatetime3,updatetime4,updatetime5;
	int updatetime6,updatetime7,updatetime8,updatetime9;
	UINT64 regionid;
	int chunknum,devicenum,disknum,stripsectnum,stripnum;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filemeta_insert","No memory");
		return FALSE;
	}
	FileID=fmetaptr->FileID;
	filename=fmetaptr->filename;
	filesize=fmetaptr->filesize;
	ACList=fmetaptr->ACList;
	filetype=fmetaptr->filetype;
	subfilenum=fmetaptr->subfilenum;
	userid=fmetaptr->userid;
	parentid=fmetaptr->parentid;
	createtime=fmetaptr->createtime;
	updatetime=fmetaptr->updatetime;

	createtime1=createtime->tm_yday;
	createtime2=createtime->tm_mon;
	createtime3=createtime->tm_yday;
	createtime4=createtime->tm_mday;
	createtime5=createtime->tm_wday;

	createtime6=createtime->tm_hour;
	createtime7=createtime->tm_min;
	createtime8=createtime->tm_sec;

	createtime9=createtime->tm_isdst;

	updatetime1=updatetime->tm_yday;
	updatetime2=updatetime->tm_mon;
	updatetime3=updatetime->tm_yday;
	updatetime4=updatetime->tm_mday;
	updatetime5=updatetime->tm_wday;

	updatetime6=updatetime->tm_hour;
	updatetime7=updatetime->tm_min;
	updatetime8=updatetime->tm_sec;

	updatetime9=updatetime->tm_isdst;

	regionid=fmetaptr->regionid;

	filechunkinf=fmetaptr->filechunkinf;

	chunknum=filechunkinf->chunknum;
	devicenum=filechunkinf->devicenum;
	disknum=filechunkinf->disknum;
	stripnum=filechunkinf->stripnum;
	stripsectnum=filechunkinf->stripsectnum;
	sprintf(querystr,"insert delayed into filemeta(FileID,filename,filesize,ACList,filetype,"
					 "subfilenum,userid,parentid,"
					 "createtime1,createtime2,createtime3,createtime4,createtime5,"
					 "createtime6,createtime7,createtime8,createtime9,"
					 "updatetime1,updatetime2,updatetime3,updatetime4,updatetime5,"
					 "updatetime6,updatetime7,updatetime8,updatetime9,"
					 "regionid,chunknum,devicenum,disknum,stripnum,stripsectnum)"
					 " values (%I64d,'%s',%I64d,%d,%d,%d,%I64d,%I64d,"
					 "%d,%d,%d,%d,%d,%d,%d,%d,%d,"
					 "%d,%d,%d,%d,%d,%d,%d,%d,%d,"
					 "%d,%d,%d,%d,%d,%d)",FileID,filename,filesize,ACList,filetype,
					 subfilenum,userid,parentid,
					 createtime1,createtime2,createtime3,createtime4,createtime5,
					 createtime6,createtime7,createtime8,createtime9,
					 updatetime1,updatetime2,updatetime3,updatetime4,updatetime5,
					 updatetime6,updatetime7,updatetime8,updatetime9,
					 regionid,chunknum,devicenum,disknum,stripnum,stripsectnum);
	//执行插入
	mysql_FILELAYER_invert_DB_string(querystr);
	resTF=mysql_FILELAYER_insert_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filemeta_insert","insert can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filemeta_delete(UINT64 fileid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filemeta_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from filemeta where FileID=%I64d",fileid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filemeta_delete_all","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filemeta_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filemeta_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from filemeta");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filemeta_delete_all","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_filestripid_select(UINT64 *stripid,UINT64 fileid)
{
	//int resTF;
	int stripindex;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filestripid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select stripid from filestripid where fileid=%I64d order by findex asc",fileid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","filestripid_select","filestripid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","filestripid_select","mysqlrow can't create");
		return FALSE;
	}
	stripindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],stripid[stripindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		stripindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filestripid_update(UINT64 *stripid,int stripnum,UINT64 fileid)
{
	int resTF;
	resTF=mysql_FILELAYER_filestripid_delete(fileid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filestripid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_filestripid_insert(stripid,stripnum,fileid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filestripid_insert","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_filestripid_insert(UINT64 *stripid,int stripnum,UINT64 fileid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filestripid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<stripnum;i++)
	{
		sprintf(querystr,
			"insert delayed into filestripid(fileid,stripid,findex) values (%I64d,%I64d,%d)",
			fileid,stripid[i],i);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","filestripid_insert","insert can'rt execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filestripid_delete(UINT64 fileid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filestripid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from filestripid where fileid=%I64d",
		fileid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filestripid_delete","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filestripid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filestripid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from filestripid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filestripid_delete","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_filestripsectid_select(UINT64 *stripsectid,UINT64 fileid)
{	
	int strsetindex;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filestripsectid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select stripsectid from filestripsectid where fileid=%I64d order by findex asc",fileid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","filestripsectid_select","filestripsectid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","filestripsectid_select","mysqlrow can't create");
		return FALSE;
	}
	strsetindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],stripsectid[strsetindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		strsetindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filestripsectid_update(UINT64 *stripsectid,int stripsectnum,UINT64 fileid)
{
	int resTF;
	resTF=mysql_FILELAYER_filestripsectid_delete(fileid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filestripsectid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_filestripsectid_insert(stripsectid,stripsectnum,fileid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filestripsectid_update","insert can't insert");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_filestripsectid_insert(UINT64 *stripsectid,int stripsectnum,UINT64 fileid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filestripid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<stripsectnum;i++)
	{
		sprintf(querystr,
			"insert delayed into filestripsectid(fileid,stripsectid,findex) values (%I64d,%I64d,%d)",
			fileid,stripsectid[i],i);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","filestripid_insert","insert can't execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filestripsectid_delete(UINT64 fileid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filestripid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from filestripsectid where fileid=%I64d",
		fileid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filestripsectid_delete","delete can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_filestripsectid_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filestripid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from filestripsectid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filestripsectid_delete","delete can't execute");
		return FALSE;
	}
	return TRUE;
}

int mysql_FILELAYER_filesubfileid_select(UINT64 *subfileid,UINT64 fileid)
{
	int fileindex;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filesubfileid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select subfileid from filesubfileid where fileid=%I64d order by subfileid asc",fileid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","filesubfileid_select","filesubfileid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","filesubfileid_select","mysqlrow can't create");
		return FALSE;
	}
	fileindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],subfileid[fileindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		fileindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filesubfileid_update(UINT64 *subfileid,int filenum,UINT64 fileid)
{
	int resTF;
	resTF=mysql_FILELAYER_filesubfileid_delete(fileid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filesubfileid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_filesubfileid_insert(subfileid,filenum,fileid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filesubfileid_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_filesubfileid_insert(UINT64 *subfileid,int filenum,UINT64 fileid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filesubfileid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<filenum;i++)
	{
		sprintf(querystr,
			"insert delayed into filesubfileid(fileid,subfileid) values (%I64d,%I64d)",
			fileid,subfileid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","filesubfileid_insert","insert can't execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filesubfileid_delete(UINT64 fileid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filesubfileid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from filesubfileid where fileid=%I64d",fileid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filesubfileid_delete","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_filesubfileid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","filesubfileid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from filesubfileid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filesubfileid_delete","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_glosystemdeviceid_select(UINT64 *deviceid)
{
	char *querystr;
	int deviceindex;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemdeviceid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select deviceid from glosystemdeviceid order by deviceid");
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemdeviceid_select","deviceid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","filesubfileid_select","mysqlrow can't create");
		return FALSE;
	}
	deviceindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],deviceid[deviceindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		deviceindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_glosystemdeviceid_update(UINT64 *deviceid,int devicenum)
{
	int resTF;
	resTF=mysql_FILELAYER_glosystemdeviceid_delete_all();
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","_glosystemdeviceid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_glosystemdeviceid_insert(deviceid,devicenum);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","_glosystemdeviceid_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_glosystemdeviceid_insert(UINT64 *deviceid,int devicenum)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemdeviceid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<devicenum;i++)
	{
		sprintf(querystr,
			"insert delayed into glosystemdeviceid(deviceid) values (%I64d)",
			deviceid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","glosystemdeviceid_insert","insert can't execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_glosystemdeviceid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemdeviceid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from glosystemdeviceid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","glosystemdeviceid_delete","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_glosystemdiskid_select(UINT64 *diskid)
{
	char *querystr;
	int diskindex;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemdiskid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select diskid from glosystemdiskid order by diskid asc");
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemdiskid_select","diskid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","filesubfileid_select","mysqlrow can't create");
		return FALSE;
	}
	diskindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],diskid[diskindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		diskindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_glosystemdiskid_update(UINT64 *diskid,int disknum)
{
	int resTF;
	resTF=mysql_FILELAYER_glosystemdiskid_delete_all();
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filesubfileid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_glosystemdiskid_insert(diskid,disknum);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","filesubfileid_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_glosystemdiskid_insert(UINT64 *diskid,int disknum)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemdiskid_insert","");
		return FALSE;
	}
	for(i=0;i<disknum;i++)
	{
		sprintf(querystr,"insert delayed into glosystemdiskid(diskid) values (%I64d)",diskid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","glosystemdiskid_insert","insert can't execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_glosystemdiskid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemdiskid_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from glosystemdiskid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","glosystemdiskid_delete_all","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_glosystemid_select(GLOSYSTEMID *systemid)
{
	int regionnum,usernum,devicenum,disknum;
	IDITEM *systemnextid;
	UINT64 nextregionid,nextstripid,nextstripsectid,nextchunkid,nextdeviceid,nextdiskid,nextfileid,nextuserid;
	int kindnum,pushtime;
	UINT64 pmaxbuffersize;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;

	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemid_insert","No memory");
		return FALSE;
	}
	systemnextid=talloc(IDITEM,1);
	if(systemnextid==NULL)
	{
		show_error("mysql_FILELAYER","glosystemid_insert","No memory");
		return FALSE;
	}
	sprintf(querystr,"select regionnum,usernum,devicenum,disknum,nextregionid,nextstripid,nextstripsectid,nextchunkid,nextdeviceid,nextdiskid,nextdiskid,nextfileid,nextuserid,kindnum,pushtime,pmaxbuffersize from glosystemid");
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemid_select","diskid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","glosystemid_select","mysqlrow can't create");
		return FALSE;
	}
	STRTOINT32(mysqlrow[0],regionnum);
	STRTOINT32(mysqlrow[1],usernum);
	STRTOINT32(mysqlrow[2],devicenum);
	STRTOINT32(mysqlrow[3],disknum);
	STRTOINT64(mysqlrow[4],nextregionid);
	STRTOINT64(mysqlrow[5],nextstripid);
	STRTOINT64(mysqlrow[6],nextstripsectid);
	STRTOINT64(mysqlrow[7],nextchunkid);
	STRTOINT64(mysqlrow[8],nextdeviceid);
	STRTOINT64(mysqlrow[9],nextdiskid);
	STRTOINT64(mysqlrow[10],nextdiskid);
	STRTOINT64(mysqlrow[11],nextfileid);
	STRTOINT64(mysqlrow[12],nextuserid);
	STRTOINT32(mysqlrow[13],kindnum);
	STRTOINT32(mysqlrow[14],pushtime);
	STRTOINT64(mysqlrow[15],pmaxbuffersize);

	GLOABL_set_SYSTEMNEXTID_data(systemnextid,
								nextregionid,nextstripid,nextstripsectid,nextchunkid,
								nextdeviceid,nextdiskid,
								nextfileid,nextuserid);
	GLOBAL_set_GLOSYSTEMID_data(systemid,
								NULL,NULL,regionnum,
								NULL,NULL,usernum,
								NULL,NULL,devicenum,
								NULL,NULL,disknum,
								systemnextid,
								pushtime,pmaxbuffersize,
								NULL,kindnum);
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_glosystemid_update(GLOSYSTEMID *systemid)
{
	int resTF;
	resTF=mysql_FILELAYER_glosystemid_delete_all();
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","glosystemid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_glosystemid_insert(systemid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","glosystemid_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_glosystemid_insert(GLOSYSTEMID *systemid)
{
	int resTF;
	int regionnum,usernum,devicenum,disknum;
	IDITEM *systemnextid;
	UINT64 nextregionid,nextstripid,nextstripsectid,nextchunkid,nextdeviceid,nextdiskid,nextfileid,nextuserid;
	int kindnum,pushtime;
	UINT64 pmaxbuffersize;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemid_insert","No memory");
		return FALSE;
	}

	regionnum=systemid->regionnum;
	usernum=systemid->usernum;
	devicenum=systemid->devicenum;
	disknum=systemid->disknum;

	systemnextid=systemid->systemnextid;

	nextregionid=systemnextid->gloregionid;
	nextstripid=systemnextid->glostripid;
	nextstripsectid=systemnextid->glostripsectid;
	nextchunkid=systemnextid->glochunkid;
	nextdeviceid=systemnextid->glodeviceid;
	nextdiskid=systemnextid->glodiskid;
	nextfileid=systemnextid->glofileid;
	nextuserid=systemnextid->glouserid;

	kindnum=systemid->availnum;
	pushtime=systemid->glopushtime;
	pmaxbuffersize=systemid->glomaxbuffersize;

	sprintf(querystr,
		"insert delayed into glosystemid(regionnum,usernum,devicenum,disknum,nextregionid,nextstripid,nextstripsectid,nextchunkid,nextdeviceid,nextdiskid,nextfileid,nextuserid,kindnum,pushtime,pmaxbuffersize) values (%d,%d,%d,%d,%I64d,%I64d,%I64d,%I64d,%I64d,%I64d,%I64d,%I64d,%d,%d,%I64d)",
		regionnum,usernum,devicenum,disknum,
		nextregionid,nextstripid,nextstripsectid,nextchunkid,
		nextdeviceid,nextdiskid,nextfileid,nextuserid,
		kindnum,pushtime,pmaxbuffersize);
	resTF=mysql_FILELAYER_insert_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","glosystemid_insert","insert can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_glosystemid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemid_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from glosystemid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","glosystemid_delete_all","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_glosystemkindid_select(int *avalkind)
{
	char *querystr;
	int kindindex;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemkindid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select availkind from glosystemkindid order by availkind asc");
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemkindid_select","availkind can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","glosystemkindid_select","mysqlrow can't create");
		return FALSE;
	}
	kindindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],avalkind[kindindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		kindindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_glosystemkindid_update(int *kindid,int kindnum)
{
	int resTF;
	resTF=mysql_FILELAYER_glosystemkindid_delete_all();
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","glosystemkindid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_glosystemkindid_insert(kindid,kindnum);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","glosystemkindid_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_glosystemkindid_insert(int *availkind,int kindnum)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemkindid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<kindnum;i++)
	{
		sprintf(querystr,"insert delayed into glosystemkindid(availkind) values (%I64d)",availkind[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","glosystemkindid_insert","insert can't execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_glosystemkindid_delete_all()
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemkindid_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from glosystemkindid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","glosystemkindid_insert","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_glosystemregionid_select(UINT64 *regionid)
{
	char *querystr;
	int regionindex;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemregionid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select regionid from glosystemregionid order by regionid asc");
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemregionid_select","regionid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","glosystemregionid_select","mysqlrow can't create");
		return FALSE;
	}
	regionindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],regionid[regionindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		regionindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_glosystemregionid_update(UINT64 *regionid,int regionnum)
{
	int resTF;
	resTF=mysql_FILELAYER_glosystemregionid_delete_all();
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","glosystemregionid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_glosystemregionid_insert(regionid,regionnum);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","glosystemregionid_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_glosystemregionid_insert(UINT64 *regionid,int regionnum)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemregionid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<regionnum;i++)
	{
		sprintf(querystr,
			"insert delayed into glosystemregionid(regionid) values (%I64d)",
			regionid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","glosystemregionid_insert","insert can't execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_glosystemregionid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemregionid_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from glosystemregionid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","glosystemregionid_delete_all","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_glosystemuserid_select(UINT64 *userid)
{
	char *querystr;
	int userindex;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemuserid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select userid from glosystemuserid order by userid asc");
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemuserid_select","userid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","glosystemuserid_select","mysqlrow can't create");
		return FALSE;
	}
	userindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],userid[userindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		userindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_glosystemuserid_update(INT64 *userid,int usernum)
{
	int resTF;
	resTF=mysql_FILELAYER_glosystemuserid_delete_all();
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","glosystemuserid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_glosystemuserid_insert(userid,usernum);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","glosystemuserid_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_glosystemuserid_insert(INT64 *userid,int usernum)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemuserid_select","No memory");
		return FALSE;
	}
	for(i=0;i<usernum;i++)
	{
		sprintf(querystr,"insert delayed into glosystemuserid(userid) values (%I64d)",userid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","glosystemuserid_insert","insert can't execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_glosystemuserid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","glosystemuserid_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from glosystemuserid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","glosystemuserid_delete_all","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_region_select(REGION *regionptr)
{
	int resTF;
	STRIPDES *strdes;
	CODEPARA *codeparamptr;
	UINT64 RegionID;
	int codetype,w,datanum,codenum,pronum,sectornum;
	UINT64 totalsize;
	int filenum,disknum,devicenum,chunknum,chunksize,stripnum;
	UINT64 totalchunknum,totalstripsectnum,rootfileid;
	int storestate;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;

	//开空间
	strdes=talloc(STRIPDES,1);
	if(strdes==NULL)
	{
		show_error("mysql_FILELAYER","region_select","No memory");
		return FALSE;
	}
	codeparamptr=talloc(CODEPARA,1);
	if(codeparamptr==NULL)
	{
		show_error("mysql_FILELAYER","region_select","No memory");
		return FALSE;
	}
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","region_select","No memory");
		return FALSE;
	}
	RegionID=regionptr->RegionID;
	sprintf(querystr,
		"select RegionID,codetype,w,datanum,codenum,pronum,sectornum,totalsize,filenum,disknum,devicenum,chunknum,chunksize,stripnum,totalchunknum,totalstrsetnum,rootfileid,storestate from region where RegionID=%I64d",
		RegionID);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","region_select","select can't execute");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","region_select","mysqlrow can't create");
		return FALSE;
	}
	STRTOINT64(mysqlrow[0],RegionID);
	STRTOINT32(mysqlrow[1],codetype);
	STRTOINT32(mysqlrow[2],w);
	STRTOINT32(mysqlrow[3],datanum);
	STRTOINT32(mysqlrow[4],codenum);
	STRTOINT32(mysqlrow[5],pronum);
	STRTOINT32(mysqlrow[6],sectornum);
	STRTOINT64(mysqlrow[7],totalsize);
	STRTOINT32(mysqlrow[8],filenum);
	STRTOINT32(mysqlrow[9],disknum);
	STRTOINT32(mysqlrow[10],devicenum);
	STRTOINT32(mysqlrow[11],chunknum);
	STRTOINT32(mysqlrow[12],chunksize);
	STRTOINT32(mysqlrow[13],stripnum);
	STRTOINT64(mysqlrow[14],totalchunknum);
	STRTOINT64(mysqlrow[15],totalstripsectnum);
	STRTOINT64(mysqlrow[16],rootfileid);
	STRTOINT32(mysqlrow[17],storestate);
	GLOBAL_set_STRIPDES_data(strdes,chunknum,NULL,NULL,disknum,chunksize);

	GLOBAL_set_CODEPARA_data(codeparamptr,w,datanum,codenum,datanum+codenum,pronum,sectornum);
	
	GLOBAL_set_REGION_data(regionptr,codetype,codeparamptr,totalsize,
							NULL,NULL,filenum,
							NULL,NULL,disknum,
							NULL,NULL,devicenum,
							strdes,
							NULL,NULL,stripnum,
							totalchunknum,totalstripsectnum,
							NULL,rootfileid,storestate);
	return TRUE;
}
int mysql_FILELAYER_region_update(REGION *regionptr)
{
	int resTF;
	UINT64 regionid;
	regionid=regionptr->RegionID;
	resTF=mysql_FILELAYER_region_delete(regionid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","region_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_region_insert(regionptr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","region_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_region_insert(REGION *regionptr)
{
	int resTF;
	STRIPDES *strdes;
	CODEPARA *codeparamptr;
	UINT64 RegionID;
	int codetype,w,datanum,codenum,pronum,sectornum;
	UINT64 totalsize;
	int filenum,disknum,devicenum,chunknum,chunksize,stripnum;
	UINT64 totalchunknum,totalstrsetnum;
	UINT64 rootfileid;
	int storestate;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","region_insert","No memory");
		return FALSE;
	}
	strdes=regionptr->strdes;
	codeparamptr=regionptr->codepara;
	RegionID=regionptr->RegionID;
	codetype=regionptr->codetype;
	codeparamptr=regionptr->codepara;
	w=codeparamptr->w;
	datanum=codeparamptr->datanum;
	codenum=codeparamptr->codenum;
	pronum=codeparamptr->pronum;
	sectornum=codeparamptr->sectornum;
	totalsize=regionptr->totalsize;
	filenum=regionptr->filenum;
	disknum=regionptr->disknum;
	devicenum=regionptr->devicenum;
	chunknum=strdes->chunknum;
	chunksize=strdes->chunksize;
	stripnum=regionptr->stripnum;
	totalchunknum=regionptr->chunknum;
	totalstrsetnum=regionptr->stripsectnum;
	rootfileid=regionptr->rootfileid;
	storestate=regionptr->storestate;
	//数据准备完毕可以写入
	sprintf(querystr,
		"insert delayed into region(RegionID,codetype,w,datanum,codenum,pronum,sectornum,totalsize,filenum,disknum,devicenum,chunknum,chunksize,stripnum,totalchunknum,totalstrsetnum,rootfileid,storestate) values (%I64d,%d,%d,%d,%d,%d,%d,%I64d,%d,%d,%d,%d,%d,%d,%I64d,%I64d,%I64d,%d)",
		RegionID,codetype,w,datanum,codenum,pronum,sectornum,totalsize,filenum,disknum,devicenum,chunknum,chunksize,stripnum,totalchunknum,totalstrsetnum,rootfileid,storestate);
	resTF=mysql_FILELAYER_insert_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","insert_query","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_region_delete(UINT64 regionid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","region_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from region where RegionID=%I64d",regionid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","region_delete_all","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_region_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","region_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from region");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","region_delete_all","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_regiondeviceid_select(UINT64 *deviceid,UINT64 regionid)
{
	char *querystr;
	int deviceindex;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","regiondeviceid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select deviceid from regiondeviceid where regionid=%I64d order by deviceid asc",regionid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","regiondeviceid_select","select can't execute");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","regiondeviceid_select","mysqlrow can't create");
		return FALSE;
	}
	deviceindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],deviceid[deviceindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		deviceindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);

	return TRUE;
}
int mysql_FILELAYER_regiondeviceid_update(UINT64 *deviceid,int devicenum,UINT64 regionid)
{
	int resTF;
	resTF=mysql_FILELAYER_regiondeviceid_delete(regionid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","regiondeviceid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_regiondeviceid_insert(deviceid,devicenum,regionid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","regiondeviceid_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_regiondeviceid_insert(UINT64 *deviceid,int devicenum,UINT64 regionid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","regiondeviceid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<devicenum;i++)
	{
		sprintf(querystr,
			"insert delayed into regiondeviceid(regionid,deviceid) values (%I64d,%I64d)",
			regionid,deviceid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","regiondeviceid_insert","insert can't execute");
			return FALSE;
		}
	}

	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_regiondeviceid_delete(UINT64 regionid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","regiondeviceid_insert","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from regiondeviceid where regionid=%I64d",regionid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","regiondeviceid_insert","No memory");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_regiondeviceid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","regiondeviceid_insert","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from regiondeviceid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","regiondeviceid_insert","No memory");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_regiondiskid_select(UINT64 *diskid,UINT64 regionid)
{
	char *querystr;
	int diskindex;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","regiondiskid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select diskid from regiondiskid where regionid=%I64d order by diskid asc",regionid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","regiondiskid_select","select can't execute");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","regiondiskid_select","mysqlrow can't create");
		return FALSE;
	}
	diskindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],diskid[diskindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		diskindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_regiondiskid_update(UINT64 *diskid,int disknum,UINT64 regionid)
{
	int resTF;
	resTF=mysql_FILELAYER_regiondiskid_delete(regionid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","regiondiskid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_regiondiskid_insert(diskid,disknum,regionid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","regiondiskid_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_regiondiskid_insert(UINT64 *diskid,int disknum,UINT64 regionid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","regiondiskid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<disknum;i++)
	{
		sprintf(querystr,
			"insert delayed into regiondiskid(regionid,diskid) values (%I64d,%I64d)",
			regionid,diskid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","regiondiskid_insert","insert can't execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_regiondiskid_delete(UINT64 regionid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","regiondiskid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from regiondiskid where regionid=%I64d",
		regionid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","regiondiskid_delete","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_regiondiskid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","regiondiskid_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from regiondiskid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","regiondiskid_delete_all","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_regionfileid_select(UINT64 *fileid,UINT64 regionid)
{
	char *querystr;
	int fileindex;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","regionfileid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select fileid from regionfileid where regionid=%I64d order by fileid asc",regionid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","regionfileid_select","select can't execute");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","regionfileid_select","mysqlrow can't create");
		return FALSE;
	}
	fileindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],fileid[fileindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		fileindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_regionfileid_update(UINT64 *fileid,int filenum,UINT64 regionid)
{
	int resTF;
	resTF=mysql_FILELAYER_regionfileid_delete(regionid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","regionfileid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_regionfileid_insert(fileid,filenum,regionid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","regionfileid_update","insert can't execute");
	}
	return TRUE;
}
int mysql_FILELAYER_regionfileid_insert(UINT64 *fileid,int filenum,UINT64 regionid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","regionfileid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<filenum;i++)
	{
		sprintf(querystr,"insert delayed into regionfileid(regionid,fileid) values (%I64d,%I64d)",
			regionid,fileid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","regionfileid_insert","insert can't execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_regionfileid_delete(UINT64 regionid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","regionfileid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from regionfileid where regionid=%I64d",regionid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","regionfileid_delete","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_regionfileid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr=NULL)
	{
		show_error("mysql_FILELAYER","regionfileid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete form regionfileid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","insert_query","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_regionstripid_select(UINT64 *stripid,UINT64 regionid)
{
	char *querystr;
	int stripindex;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","regionstripid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select stripid from regionstripid where regionid=%I64d order by stripid asc",regionid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","regionstripid_select","select can't execute");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","regionstripid_select","mysqlrow can't create");
		return FALSE;
	}
	stripindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],stripid[stripindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		stripindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_regionstripid_update(UINT64 *stripid,int stripnum,UINT64 regionid)
{
	int resTF;
	resTF=mysql_FILELAYER_regionstripid_delete(regionid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","regionstripid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_regionstripid_insert(stripid,stripnum,regionid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","regionstripid_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_regionstripid_insert(UINT64 *stripid,int stripnum,UINT64 regionid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","regionstripid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<stripnum;i++)
	{
		sprintf(querystr,"insert delayed into regionstripid(regionid,stripid) values (%I64d,%I64d)",
			regionid,stripid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","regionstripid_insert","delete can't insert");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_regionstripid_delete(UINT64 regionid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","regionstripid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from regionstripid where regionid=%I64d",regionid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","regionstripid_delete","delete can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_regionstripid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","regionstripid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from regionstripid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","regionstripid_delete","delete can't execute");
		return FALSE;
	}
	return TRUE;
}


int mysql_FILELAYER_strip_select(STRIP *stripptr)
{
	STRIPDES *strdes;
	UINT64 StripID;
	int strsetchunknum,chunksize,disknum,devicenum;
	int stripsectnum,chunknum;
	UINT64 regionid;
	int storestate;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;

	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","strip_select","No memory");
		return FALSE;
	}
	strdes=talloc(STRIPDES,1);
	if(strdes==NULL)
	{
		show_error("mysql_FILELAYER","strip_select","No memory");
		return FALSE;
	}
	StripID=stripptr->StripID;
	sprintf(querystr,"select StripID,strsetchunknum,chunksize,disknum,devicenum,stripsectnum,chunknum,regionid,storestate from strip where StripID=%I64d",StripID);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","strip_select","select can't execute");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","strip_select","mysqlrow can't create");
		return FALSE;
	}
	STRTOINT64(mysqlrow[0],StripID);
	STRTOINT32(mysqlrow[1],strsetchunknum);
	STRTOINT32(mysqlrow[2],chunksize);
	STRTOINT32(mysqlrow[3],disknum);
	STRTOINT32(mysqlrow[4],devicenum);
	STRTOINT32(mysqlrow[5],stripsectnum);
	STRTOINT32(mysqlrow[6],chunknum);
	STRTOINT64(mysqlrow[7],regionid);
	STRTOINT32(mysqlrow[8],storestate);

	GLOBAL_set_STRIPDES_data(strdes,strsetchunknum
						,NULL,NULL,disknum,
						chunksize);
	
	GLOBAL_set_STRIP_data(stripptr,strdes,
				NULL,NULL,disknum,
				NULL,NULL,devicenum,
				NULL,NULL,stripsectnum,
				NULL,NULL,chunknum,
				regionid,NULL,
				storestate);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_strip_update(STRIP *stripptr)
{
	int resTF;
	UINT64 stripid;
	stripid=stripptr->StripID;
	resTF=mysql_FILELAYER_strip_delete(stripid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","strip_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_strip_insert(stripptr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","strip_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_strip_insert(STRIP *stripptr)
{
	int resTF;
	STRIPDES *strdes;
	UINT64 StripID,regionid;
	int strsetchunknum,chunksize,disknum,devicenum,stripsectnum,chunknum,storestate;
	char *querystr;
	StripID=stripptr->StripID;
	strdes=stripptr->strdes;
	strsetchunknum=strdes->chunknum;
	chunksize=strdes->chunksize;
	disknum=strdes->disknum;

	devicenum=stripptr->devicenum;
	stripsectnum=stripptr->strsetnum;

	chunknum=stripptr->chunknum;
	regionid=stripptr->regionid;

	storestate=stripptr->storestate;

	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","strip_insert","No memory");
		return FALSE;
	}
	sprintf(querystr,"insert delayed into strip(StripID,strsetchunknum,chunksize,disknum,devicenum,stripsectnum,chunknum,regionid,storestate) values (%I64d,%d,%d,%d,%d,%d,%d,%I64d,%d)",
		StripID,strsetchunknum,chunksize,disknum,devicenum,stripsectnum,chunknum,regionid,storestate);
	resTF=mysql_FILELAYER_insert_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","strip_insert","strip can't insert");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_strip_delete(UINT64 stripid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","strip_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from strip where StripID=%I64d",stripid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","strip_delete","delete can't execute");
		return FALSE;
	}

	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_strip_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","strip_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from strip");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","strip_delete_all","delete can't execute");
		return FALSE;
	}

	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_stripchunkid_select(UINT64 *chunkid,UINT64 stripid)
{
	int chunkindex;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripchunkid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select chunkid from stripchunkid where stripid=%I64d order by chunkid asc",stripid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","stripchunkid_select","stripchunkid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","stripchunkid_select","mysqlrow can't create");
		return FALSE;
	}
	chunkindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],chunkid[chunkindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		chunkindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripchunkid_update(UINT64 *chunkid,int chunknum,UINT64 stripid)
{
	int resTF;
	resTF=mysql_FILELAYER_stripchunkid_delete(stripid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER_","stripchunkid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_stripchunkid_insert(chunkid,chunknum,stripid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripchunkid_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_stripchunkid_insert(UINT64 *chunkid,int chunknum,UINT64 stripid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripchunkid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<chunknum;i++)
	{
		sprintf(querystr,
			"insert stripchunkid(stripid,chunkid) values (%I64d,%I64d)",
			stripid,chunkid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","stripchunkid_delete_all","insert can't execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripchunkid_delete(UINT64 stripid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripchunkid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from stripchunkid where stripid=%I64d",stripid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripchunkid_delete","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripchunkid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripchunkid_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from stripchunkid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripchunkid_delete_all","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_stripdeviceid_select(UINT64 *deviceid,UINT64 stripid)
{
	int deviceindex;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripdeviceid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select deviceid from stripdeviceid where stripid=%I64d order by deviceid asc",stripid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","stripdeviceid_select","stripdeviceid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","stripdeviceid_select","mysqlrow can't create");
		return FALSE;
	}
	deviceindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],deviceid[deviceindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		deviceindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripdeviceid_update(UINT64 *deviceid,int devicenum,UINT64 stripid)
{
	int resTF;
	resTF=mysql_FILELAYER_stripdeviceid_delete(stripid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripdeviceid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_stripdeviceid_insert(deviceid,devicenum,stripid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripdeviceid_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_stripdeviceid_insert(UINT64 *deviceid,int devicenum,UINT64 stripid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripdeviceid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<devicenum;i++)
	{
		sprintf(querystr,
			"insert delayed into stripdeviceid(stripid,deviceid) values (%I64d,%I64d)",
			stripid,deviceid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","stripdeviceid_insert","insert can't execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripdeviceid_delete(UINT64 stripid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripdeviceid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from stripdeviceid where stripid=%I64d",stripid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripdeviceid_delete","insert can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripdeviceid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripdeviceid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from stripdeviceid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripdeviceid_delete","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_stripdiskid_select(UINT64 *diskid,UINT64 stripid)
{
	int diskindex;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripdiskid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select diskid from stripdiskid where stripid=%I64d order by diskid asc",stripid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","stripdiskid_select","stripdiskid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","stripdeviceid_select","mysqlrow can't create");
		return FALSE;
	}
	diskindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],diskid[diskindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		diskindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripdiskid_update(UINT64 *diskid,int disknum,UINT64 stripid)
{
	int resTF;
	resTF=mysql_FILELAYER_stripdiskid_delete(stripid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripdiskid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_stripdiskid_insert(diskid,disknum,stripid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripdiskid_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_stripdiskid_insert(UINT64 *diskid,int disknum,UINT64 stripid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripdiskid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<disknum;i++)
	{
		sprintf(querystr,
			"insert delayed into stripdiskid(stripid,diskid) values (%I64d,%I64d)",
			stripid,diskid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","stripdiskid_insert","insert can't execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripdiskid_delete(UINT64 stripid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripdiskid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from stripdiskid where stripid=%I64d",
		stripid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF=FALSE)
	{
		show_error("mysql_FILELAYER","stripdiskid_delete","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripdiskid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripdiskid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from stripdiskid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF=FALSE)
	{
		show_error("mysql_FILELAYER","stripdiskid_delete","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_stripsect_select(STRIPSECT *stripsectptr)
{
	UINT64 StripsectID,regionid,stripid,diskid,deviceid;
	int chunknum,chunksize;
	int isparity,storestate;
	char *filepath,*filename;
	int filepathlength,filenamelength;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;

	char *querystr;
	StripsectID=stripsectptr->StripsectID;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripsect_select","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"select StripsectID,isparity,chunksize,chunknum,regionid,stripid,diskid,deviceid,filename,filepath,storestate from stripsect where StripsectID=%I64d",
		StripsectID);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","stripsect_select","select can't execute");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","chunktable_select","mysqlrow can't create");
		return FALSE;
	}
	STRTOINT64(mysqlrow[0],StripsectID);
	STRTOINT32(mysqlrow[1],isparity);
	STRTOINT32(mysqlrow[2],chunksize);
	STRTOINT32(mysqlrow[3],chunknum);
	STRTOINT64(mysqlrow[4],regionid);
	STRTOINT64(mysqlrow[5],stripid);
	STRTOINT64(mysqlrow[6],diskid);
	STRTOINT64(mysqlrow[7],deviceid);

	filenamelength=strlen(mysqlrow[8])+1;
	filename=talloc(char,filenamelength);
	if(filename==NULL)
	{
		show_error("mysql_FILELAYER","stripsect_select","No memory");
		return FALSE;
	}
	mcpy(filename,mysqlrow[8],char,filenamelength);

	filepathlength=strlen(mysqlrow[9])+1;
	filepath=talloc(char,filepathlength);
	if(filepath==NULL)
	{
		show_error("mysql_FILELAYER","stripsect_select","No memory");
		return FALSE;
	}
	mcpy(filepath,mysqlrow[9],char,filepathlength);

	STRTOINT32(mysqlrow[10],storestate);
	GLOBAL_set_STRIPSECT_data(stripsectptr,isparity,
							NULL,NULL,chunksize,chunknum,
							regionid,NULL,
							stripid,NULL,
							diskid,NULL,
							deviceid,NULL,
							filename,filepath,
							storestate);

	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripsect_update(STRIPSECT *stripsectptr)
{
	int resTF;
	int stripsectid;
	stripsectid=stripsectptr->StripsectID;
	resTF=mysql_FILELAYER_stripsect_delete(stripsectid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripsect_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_stripsect_insert(stripsectptr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripsect_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_stripsect_insert(STRIPSECT *stripsectptr)
{
	int resTF;
	UINT64 StripsectID,regionid,stripid,diskid,deviceid;
	int chunknum,chunksize;
	int isparity,storestate;
	char *filepath,*filename;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripsect_insert","No memory");
		return FALSE;
	}
	StripsectID=stripsectptr->StripsectID;
	isparity=stripsectptr->isparity;
	chunksize=stripsectptr->chunksize;
	chunknum=stripsectptr->chunknum;
	regionid=stripsectptr->regionid;
	stripid=stripsectptr->stripid;
	diskid=stripsectptr->diskid;
	deviceid=stripsectptr->deviceid;
	filename=stripsectptr->filename;
	filepath=stripsectptr->filepath;
	storestate=stripsectptr->storestate;
	sprintf(querystr,
		"insert delayed into stripsect(StripsectID,isparity,chunksize,chunknum,regionid,stripid,diskid,deviceid,filename,filepath,storestate) values (%I64d,%d,%d,%d,%I64d,%I64d,%I64d,%I64d,'%s','%s',%d)",
		StripsectID,isparity,chunksize,chunknum,regionid,stripid,diskid,deviceid,filename,filepath,storestate);
	mysql_FILELAYER_invert_DB_string(querystr);
	resTF=mysql_FILELAYER_insert_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripsect_insert","insert can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripsect_delete(UINT64 stripsectid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripsect_insert","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from stripsect where StripsectID=%I64d",
		stripsectid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripsect_insert","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripsect_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripsect_insert","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from stripsect");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripsect_insert","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_stripsectchunkid_select(UINT64 *chunkid,UINT64 stripsectid)
{
	int chunkindex;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripdiskid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select chunkid from stripsectchunkid where stripsectid=%I64d order by chunkid asc",stripsectid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","stripsectchunkid_select","stripsectchunkid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","stripsectchunkid_select","mysqlrow can't create");
		return FALSE;
	}
	chunkindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],chunkid[chunkindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		chunkindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripsectchunkid_update(UINT64 *chunkid,int chunknum,UINT64 stripsectid)
{
	int resTF;
	resTF=mysql_FILELAYER_stripsectchunkid_delete(stripsectid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripsectchunkid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_stripsectchunkid_insert(chunkid,chunknum,stripsectid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripsectchunkid_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_stripsectchunkid_insert(UINT64 *chunkid,int chunknum,UINT64 stripsectid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripsectchunkid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<chunknum;i++)
	{
		sprintf(querystr,
			"insert delayed into stripsectchunkid(stripsectid,chunkid) values (%I64d,%I64d)",
			stripsectid,chunkid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","stripsectchunkid_insert","insert can't execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripsectchunkid_delete(UINT64 stripsectid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripsectchunkid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from stripsectchunkid where stripsectid=%I64d",
		stripsectid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripsectchunkid_delete","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripsectchunkid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripsectchunkid_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from stripsectchunkid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripsectchunkid_delete_all","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_stripstripsectid_select(UINT64 *stripsectid,UINT64 stripid)
{
	int stripsectindex;
	char *querystr;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripstripsectid_select","No memory");
		return FALSE;
	}
	sprintf(querystr,"select stripsectid from stripstripsectid where stripid=%I64d order by stripsectid asc",stripid);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","stripstripsectid_select","stripstripsectid can't select");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","stripstripsectid_select","mysqlrow can't create");
		return FALSE;
	}
	stripsectindex=0;
	while(mysqlrow!=NULL)
	{
		STRTOINT64(mysqlrow[0],stripsectid[stripsectindex]);
		mysqlrow=mysql_fetch_row(mysqlresptr);
		stripsectindex++;
	}
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripstripsectid_update(UINT64 *stripsectid,int stripsectnum,UINT64 stripid)
{
	int resTF;
	resTF=mysql_FILELAYER_stripstripsectid_delete(stripid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripstripsectid_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_stripstripsectid_insert(stripsectid,stripsectnum,stripid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripstripsectid_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_stripstripsectid_insert(UINT64 *stripsectid,int stripsectnum,UINT64 stripid)
{
	int i,resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripstripsectid_insert","No memory");
		return FALSE;
	}
	for(i=0;i<stripsectnum;i++)
	{
		sprintf(querystr,
			"insert delayed into stripstripsectid(stripid,stripsectid) values (%I64d,%I64d)",
			stripid,stripsectid[i]);
		resTF=mysql_FILELAYER_insert_query(querystr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","stripstripsectid_insert","insert can't execute");
			return FALSE;
		}
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripstripsectid_delete(UINT64 stripid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripstripsectid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from stripstripsectid where stripid=%I64d",
		stripid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripstripsectid_delete_all","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_stripstripsectid_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","stripstripsectid_delete","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from stripstripsectid");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","stripstripsectid_delete","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}

int mysql_FILELAYER_userprofile_select(USERPROFILE *userprofileptr)
{
	UINT64 UserID,DICid;
	char *querystr;
	char *username,*password,*DICpath;
	int userprivil,
		createtime1,createtime2,createtime3,createtime4,createtime5,
		createtime6,createtime7,createtime8,createtime9;
	int userlength,passlength,DIClength;
	USERLOCATION *userlocinf;
	struct tm *createtime;
	MYSQL_RES *mysqlresptr;
	MYSQL_ROW mysqlrow;

	createtime=talloc(struct tm,1);
	if(createtime==NULL)
	{
		show_error("mysql_FILELAYER","userprofile_select","No memory");
		return FALSE;
	}

	userlocinf=talloc(USERLOCATION,1);
	if(userlocinf==NULL)
	{
		show_error("mysql_FILELAYER","userprofile_select","No memory");
		return FALSE;
	}

	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","userprofile_select","No memory");
		return FALSE;
	}

	UserID=userprofileptr->UserID;
	sprintf(querystr,
		"select UserID,username,password,DICid,DICpath,userprivil,createtime1,createtime2,createtime3,createtime4,createtime5,createtime6,createtime7,createtime8,createtime9 from userprofile where UserID=%I64d",
		UserID);
	mysqlresptr=mysql_FILELAYER_select_query(querystr);
	if(mysqlresptr==NULL)
	{
		show_error("mysql_FILELAYER","userprofile_select","select can't execute");
		return FALSE;
	}
	mysqlrow=mysql_fetch_row(mysqlresptr);
	if(mysqlrow==NULL)
	{
		show_error("mysql_FILELAYER","stripstripsectid_select","mysqlrow can't create");
		return FALSE;
	}
	STRTOINT64(mysqlrow[0],UserID);
	userlength=strlen(mysqlrow[1])+1;//还有一个空位
	username=talloc(char,userlength);
	if(username==NULL)
	{
		show_error("mysql_FILELAYER","stripstripsectid_select","No memory");
		return FALSE;
	}
	mcpy(username,mysqlrow[1],char,userlength);

	passlength=strlen(mysqlrow[2])+1;
	password=talloc(char,passlength);
	if(password==NULL)
	{
		show_error("mysql_FILELAYER","stripstripsectid_select","No memory");
		return FALSE;
	}
	mcpy(password,mysqlrow[2],char,passlength);

	STRTOINT64(mysqlrow[3],DICid);

	DIClength=strlen(mysqlrow[4])+1;
	DICpath=talloc(char,DIClength);
	if(DICpath==NULL)
	{
		show_error("mysql_FILELAYER","stripstripsectid_select","No memory");
		return FALSE;
	}
	mcpy(DICpath,mysqlrow[4],char,passlength);

	STRTOINT32(mysqlrow[5],userprivil);

	STRTOINT32(mysqlrow[6],createtime1);
	STRTOINT32(mysqlrow[7],createtime2);
	STRTOINT32(mysqlrow[8],createtime3);
	STRTOINT32(mysqlrow[9],createtime4);
	STRTOINT32(mysqlrow[10],createtime5);

	STRTOINT32(mysqlrow[11],createtime6);
	STRTOINT32(mysqlrow[12],createtime7);
	STRTOINT32(mysqlrow[13],createtime8);

	STRTOINT32(mysqlrow[14],createtime9);
	GLOBAL_set_USERLOCATION_data(userlocinf,DICid,NULL,DICpath);

	GLOBAL_set_time(createtime,createtime1,createtime2,createtime3,createtime4,createtime5,
							createtime6,createtime7,createtime8,
							createtime9);
	
	GLOBAL_set_USERPROFILE_data(userprofileptr,username,password,userlocinf,userprivil,createtime);
	
	mysql_free_result(mysqlresptr);
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_userprofile_update(USERPROFILE *userprofileptr)
{
	int resTF;
	UINT64 userid;
	userid=userprofileptr->UserID;
	resTF=mysql_FILELAYER_userprofile_delete(userid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","userprofile_update","delete can't execute");
		return FALSE;
	}
	resTF=mysql_FILELAYER_userprofile_insert(userprofileptr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","userprofile_update","insert can't execute");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_userprofile_insert(USERPROFILE *userprofileptr)
{
	int resTF;
	UINT64 UserID,DICid;
	struct tm *createtime;
	USERLOCATION *userlocation;
	char *username,*password,*DICpath;
	int userprivil,createtime1,createtime2,createtime3,
		createtime4,createtime5,createtime6,createtime7,
		createtime8,createtime9;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","userprofile_insert","No memory");
		return FALSE;
	}
	userlocation=userprofileptr->userlocinf;
	createtime=userprofileptr->createtime;

	UserID=userprofileptr->UserID;
	username=userprofileptr->username;
	password=userprofileptr->password;

	DICid=userlocation->DICid;
	DICpath=userlocation->DICpath;

	userprivil=userprofileptr->userprivil;

	createtime1=createtime->tm_year;
	createtime2=createtime->tm_mon;
	createtime3=createtime->tm_yday;
	createtime4=createtime->tm_mday;
	createtime5=createtime->tm_wday;

	createtime6=createtime->tm_hour;
	createtime7=createtime->tm_min;
	createtime8=createtime->tm_sec;

	createtime9=createtime->tm_isdst;

	sprintf(querystr,
		"insert delayed into userprofile(UserID,username,password,DICid,DICpath,userprivil,createtime1,createtime2,createtime3,createtime4,createtime5,createtime6,createtime7,createtime8,createtime9) values (%I64d,'%s','%s',%I64d,'%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)",
		UserID,username,password,DICid,DICpath,userprivil,createtime1,createtime2,createtime3,createtime4,createtime5,createtime6,createtime7,createtime8,createtime9);
	mysql_FILELAYER_invert_DB_string(querystr);
	resTF=mysql_FILELAYER_insert_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","userprofile_insert","insert can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_userprofile_delete(UINT64 userid)
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","userprofile_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,
		"delete from userprofile where UserID=%I64d",
		userid);
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","userprofile_delete","delete can't execute");
		return FALSE;
	}
	free(querystr);
	return TRUE;
}
int mysql_FILELAYER_userprofile_delete_all()
{
	int resTF;
	char *querystr;
	querystr=talloc(char,1024);
	if(querystr==NULL)
	{
		show_error("mysql_FILELAYER","userprofile_delete_all","No memory");
		return FALSE;
	}
	sprintf(querystr,"delete from userprofile");
	resTF=mysql_FILELAYER_delete_query(querystr);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","userprofile_delete_all","delete can't execute");
		return FALSE;
	}
	return TRUE;
}

int mysql_FILELAYER_mysql_delete_all()
{
	int resTF;
	resTF=mysql_FILELAYER_chunk_delete_all();
	if(resTF==FALSE)
	{

	}
	resTF=mysql_FILELAYER_device_delete_all();
	if(resTF==FALSE)
	{

	}
	resTF=mysql_FILELAYER_devicediskid_delete_all();
	if(resTF==FALSE)
	{

	}
	resTF=mysql_FILELAYER_deviceprocessid_delete_all();
	if(resTF==FALSE)
	{

	}
	resTF=mysql_FILELAYER_deviceregionid_delete_all();
	if(resTF==FALSE)
	{

	}
	resTF=mysql_FILELAYER_disk_delete_all();
	if(resTF==FALSE)
	{

	}
	resTF=mysql_FILELAYER_diskregionid_delete_all();
	if(resTF==FALSE)
	{

	}
	return TRUE;
}





int mysql_FILELAYER_intial()
{
	MYSQL *resTF;
	/*mysqlptr=talloc(MYSQL,1);
	if(mysqlptr==NULL)
	{
		show_error("mysql","FILELAYER_intial","");
		return FALSE;
	}*/
	resTF=mysql_init(&mysqlptr);
	if(resTF==NULL)
	{
		show_error("mysql_FILELAYER","intial","mysql pointer can't create");
		return FALSE;
	}
	resTF=mysql_real_connect(&mysqlptr,HOST,USERNAME,PASSWORD,DBNAME,DBPORT,NULL,0);
	if(resTF==NULL)
	{
		show_error("mysql_FILELAYER","intial","mysql pointer can't connect");
		return FALSE;
	}
	mysql_intial=TRUE;
	return TRUE;
}
int mysql_FILELAYER_check_intial()//检查
{
	int resTF;
	if(mysql_intial!=TRUE)
	{
		resTF=mysql_FILELAYER_intial();
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","check_intial","database can't intialize");
			return FALSE;
		}
		mysql_intial=TRUE;
	}
	return TRUE;
}
int mysql_FILELAYER_CHUNK_READER_META(CHUNK *chk)
{
	int resTF;
	resTF=mysql_FILELAYER_chunk_select(chk);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","CHUNK_READER_META","chunk can't select");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_STRIPSECT_READER(STRIPSECT *strset)
{
	int resTF;
	int chunknum;
	UINT64 stripsectid;
	UINT64 *chunkid;
	resTF=mysql_FILELAYER_stripsect_select(strset);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","STRIPSECT_READER","stripsect can't read");
		return FALSE;
	}
	chunknum=strset->chunknum;
	chunkid=talloc(UINT64,chunknum);
	if(chunkid==NULL)
	{
		show_error("mysql_FILELAYER","STRIPSECT_READER","No memory");
		return FALSE;
	}
	stripsectid=strset->StripsectID;
	resTF=mysql_FILELAYER_stripsectchunkid_select(chunkid,stripsectid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","STRIPSECT_READER","chunkid can't select");
		return FALSE;
	}
	strset->chunkid=chunkid;
	return TRUE;
}
int mysql_FILELAYER_STRIP_READER(STRIP *str)
{
	int resTF;
	UINT64 StripID;
	UINT64 *chunkid,*strsetid,*diskid,*deviceid;
	int chunknum,strsetnum,disknum,devicenum;
	StripID=str->StripID;
	resTF=mysql_FILELAYER_strip_select(str);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","STRIP_READER","strip can't select");
		return FALSE;
	}
	chunknum=str->chunknum;
	chunkid=talloc(UINT64,chunknum);
	if(chunkid==NULL)
	{
		show_error("mysql_FILELAYER","STRIP_READER","No memory");
		return FALSE;
	}
	strsetnum=str->strsetnum;
	strsetid=talloc(UINT64,strsetnum);
	if(strsetid==NULL)
	{
		show_error("mysql_FILELAYER","STRIP_READER","No memory");
		return FALSE;
	}
	disknum=str->disknum;
	diskid=talloc(UINT64,disknum);
	if(diskid==NULL)
	{
		show_error("mysql_FILELAYER","STRIP_READER","No memory");
		return FALSE;
	}
	devicenum=str->devicenum;
	deviceid=talloc(UINT64,devicenum);
	if(deviceid==NULL)
	{
		show_error("mysql_FILELAYER","STRIP_READER","No memory");
		return FALSE;
	}
	resTF=mysql_FILELAYER_stripchunkid_select(chunkid,StripID);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","STRIP_READER","chunkid can't select");
		return FALSE;
	}
	resTF=mysql_FILELAYER_stripstripsectid_select(strsetid,StripID);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","STRIP_READER","stripsectid can't select");
		return FALSE;
	}
	resTF=mysql_FILELAYER_stripdiskid_select(diskid,StripID);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","STRIP_READER","stripdiskid can't select");
		return FALSE;
	}
	resTF=mysql_FILELAYER_stripdeviceid_select(deviceid,StripID);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","STRIP_READER","stripdeviceid can't select");
		return FALSE;
	}
	str->chunkid=chunkid;
	str->stripsectid=strsetid;
	str->deviceid=deviceid;
	str->diskid=diskid;
	return TRUE;
}
extern int mysql_FILELAYER_REGION_READER(REGION *reg)
{
	int resTF;
	UINT64 RegionID;
	int disknum,devicenum,filenum,stripnum;
	UINT64 *diskid,*deviceid,*fileid,*stripid;
	RegionID=reg->RegionID;
	
	resTF=mysql_FILELAYER_region_select(reg);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","REGION_READER","region can't select");
		return FALSE;
	}
	disknum=reg->disknum;
	diskid=talloc(UINT64,disknum);
	if(diskid==NULL)
	{
		show_error("mysql_FILELAYER","REGION_READER","diskid can't select");
		return FALSE;
	}
	devicenum=reg->devicenum;
	deviceid=talloc(UINT64,devicenum);
	if(deviceid==NULL)
	{
		show_error("mysql_FILELAYER","REGION_READER","deviceid can't select");
		return FALSE;
	}
	filenum=reg->filenum;
	fileid=talloc(UINT64,filenum);
	if(fileid==NULL)
	{
		show_error("mysql_FILELAYER","REGION_READER","fileid can't select");
		return FALSE;
	}
	stripnum=reg->stripnum;
	stripid=talloc(UINT64,stripnum);
	if(stripid==NULL)
	{
		show_error("mysql_FILELAYER","REGION_READER","stripid can't select");
		return FALSE;
	}
	resTF=mysql_FILELAYER_regiondiskid_select(diskid,RegionID);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","REGION_READER","diskid can't select");
		return FALSE;
	}
	resTF=mysql_FILELAYER_regiondeviceid_select(deviceid,RegionID);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","REGION_READER","deviceid can't select");
		return FALSE;
	}
	resTF=mysql_FILELAYER_regionfileid_select(fileid,RegionID);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","REGION_READER","fileid can't select");
		return FALSE;
	}
	resTF=mysql_FILELAYER_regionstripid_select(stripid,RegionID);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","REGION_READER","stripid can't select");
		return FALSE;
	}
	reg->diskid=diskid;
	reg->deviceid=deviceid;
	reg->fileid=fileid;
	reg->stripid=stripid;
	return TRUE;
}
int mysql_FILELAYER_DISK_READER(DISK *disk)
{
	int resTF;
	UINT64 DiskID;
	UINT64 *regionid;
	int regionum;

	DiskID=disk->DiskID;
	resTF=mysql_FILELAYER_disk_select(disk);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","DISK_READER","disk can't select");
		return FALSE;
	}
	regionum=disk->regionnum;
	regionid=talloc(UINT64,regionum);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","DISK_READER","No memory");
		return FALSE;
	}
	resTF=mysql_FILELAYER_diskregionid_select(regionid,DiskID);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","DISK_READER","regionid can't select");
		return FALSE;
	}
	disk->regionid=regionid;
	return TRUE;
}
int mysql_FILELAYER_DEVICE_READER(DEVICE *device)
{
	int resTF;
	UINT64 DeviceID;
	UINT64 *diskid,*regionid;
	int *speed;
	int disknum,regionnum,processnum;
	DeviceID=device->DeviceID;
	resTF=mysql_FILELAYER_device_select(device);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","DEVICE_READER","Device can't select");
		return FALSE;
	}
	disknum=device->disknum;
	diskid=talloc(UINT64,disknum);
	if(diskid==NULL)
	{
		show_error("mysql_FILELAYER","DEVICE_READER","No memory");
		return FALSE;
	}
	regionnum=device->regionnum;
	regionid=talloc(UINT64,regionnum);
	if(regionid==NULL)
	{
		show_error("mysql_FILELAYER","DEVICE_READER","No memory");
		return FALSE;
	}
	processnum=device->processnum;
	speed=talloc(int,processnum);
	if(speed==NULL)
	{
		show_error("mysql_FILELAYER","DEVICE_READER","No memory");
		return FALSE;
	}

	resTF=mysql_FILELAYER_devicediskid_select(diskid,DeviceID);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","DEVICE_READER","diskid can't select");
		return FALSE;
	}
	if(processnum!=0)
	{
		resTF=mysql_FILELAYER_deviceprocessid_select(speed,DeviceID);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","DEVICE_READER","processid can't select");
			return FALSE;
		}
	}
	else
	{
		speed=NULL;
	}
	if(regionnum!=0)
	{
		resTF=mysql_FILELAYER_deviceregionid_select(regionid,DeviceID);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","DEVICE_READER","regionid can't select");
			return FALSE;
		}
	}
	else
	{
		regionid=NULL;
	}
	device->diskid=diskid;
	device->speed=speed;
	device->regionid=regionid;

	return TRUE;
}
//将DEVICE读取到相应数据
int mysql_FILELAYER_FILEMETA_READER(FILEMETA *fmeta)
{
	int resTF;
	UINT64 FileID;
	FILEINF *filechunkinf;
	CHUNKPATH *chunkpath;
	UINT64 *chunkid,*deviceid,*diskid,*stripid,*stripsectid;
	int chunknum,devicenum,disknum,stripnum,stripsectnum;
	UINT64 *subfileid;
	int subfilenum;
	resTF=mysql_FILELAYER_filemeta_select(fmeta);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","FILEMETA_READER","filemeta can't select");
		return FALSE;
	}
	FileID=fmeta->FileID;

	subfilenum=fmeta->subfilenum;
	if(subfilenum!=0)
	{
		subfileid=talloc(UINT64,subfilenum);
		if(subfileid==NULL)
		{
			show_error("mysql_FILELAYER","FILEMETA_READER","No memory");
			return FALSE;
		}
		resTF=mysql_FILELAYER_filesubfileid_select(subfileid,FileID);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","FILEMETA_READER","subfileid can't select");
			return FALSE;
		}
		fmeta->subfileidlist=subfileid;
	}
	else
	{
		subfileid=NULL;
	}
	filechunkinf=fmeta->filechunkinf;
	chunknum=filechunkinf->chunknum;
	//说明了没有存储数据
	if(chunknum==0)
	{
		free(filechunkinf);//释放即可
		fmeta->filechunkinf=NULL;
		return TRUE;
	}
	chunkid=talloc(UINT64,chunknum);
	if(chunkid==NULL)
	{
		show_error("mysql_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	chunkpath=talloc(CHUNKPATH,chunknum);
	if(chunkpath==NULL)
	{
		show_error("mysql_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	devicenum=filechunkinf->devicenum;
	deviceid=talloc(UINT64,devicenum);
	if(deviceid==NULL)
	{
		show_error("mysql_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	disknum=filechunkinf->disknum;
	diskid=talloc(UINT64,disknum);
	if(diskid==NULL)
	{
		show_error("mysql_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	stripnum=filechunkinf->stripnum;
	stripid=talloc(UINT64,stripnum);
	if(stripid==NULL)
	{
		show_error("mysql_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	stripsectnum=filechunkinf->stripsectnum;
	stripsectid=talloc(UINT64,stripsectnum);
	if(stripsectid==NULL)
	{
		show_error("mysql_FILELAYER","FILEMETA_READER","No memory");
		return FALSE;
	}
	resTF=mysql_FILELAYER_filechunkid_select(chunkid,FileID);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","FILEMETA_READER","chunkid can't select");
		return FALSE;
	}
	resTF=mysql_FILELAYER_filechunkpath_select(chunkpath,FileID);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","FILEMETA_READER","chunkpath can't select");
		return FALSE;
	}
	resTF=mysql_FILELAYER_filedeviceid_select(deviceid,FileID);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","FILEMETA_READER","deviceid can't select");
		return FALSE;
	}
	resTF=mysql_FILELAYER_filediskid_select(diskid,FileID);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","FILEMETA_READER","diskid can't select");
		return FALSE;
	}
	resTF=mysql_FILELAYER_filestripid_select(stripid,FileID);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","FILEMETA_READER","stripid can't select");
		return FALSE;
	}
	resTF=mysql_FILELAYER_filestripsectid_select(stripsectid,FileID);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","FILEMETA_READER","stripsectid can't select");
		return FALSE;
	}
	filechunkinf->chunkid=chunkid;
	filechunkinf->chkpath=chunkpath;
	filechunkinf->deviceid=deviceid;
	filechunkinf->diskid=diskid;
	filechunkinf->stripid=stripid;
	filechunkinf->stripsectid=stripsectid;
	return TRUE;
}
int mysql_FILELAYER_USERPROFILE_READER(USERPROFILE *pfile)//将USERPROFILE读取到相应数据
{
	int resTF;
	resTF=mysql_FILELAYER_userprofile_select(pfile);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","USERPROFILE_READER","userprofile can't select");
		return FALSE;
	}
	return TRUE;
}

int mysql_FILELAYER_GLOSYSTEMID_READER(GLOSYSTEMID *glosysid)//将用户信息读取到相应数据
{
	int resTF;
	int *availkind;
	UINT64 *deviceid,*diskid,*regionid,*userid;
	int devicenum,disknum,kindnum,regionnum,usernum;

	resTF=mysql_FILELAYER_glosystemid_select(glosysid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","GLOSYSTEMID_READER","glosysid can't select");
		return FALSE;
	}
	devicenum=glosysid->devicenum;
	deviceid=talloc(UINT64,devicenum);
	if(deviceid==NULL)
	{
		show_error("mysql_FILELAYER","GLOSYSTEMID_READER","No memory");
		return FALSE;
	}
	disknum=glosysid->disknum;
	diskid=talloc(UINT64,disknum);
	if(diskid==NULL)
	{
		show_error("mysql_FILELAYER","GLOSYSTEMID_READER","No memory");
		return FALSE;
	}
	kindnum=glosysid->availnum;
	availkind=talloc(int,kindnum);
	if(availkind==NULL)
	{
		show_error("mysql_FILELAYER","GLOSYSTEMID_READER","No memory");
		return FALSE;
	}
	regionnum=glosysid->regionnum;
	regionid=talloc(UINT64,regionnum);
	if(regionid==NULL)
	{
		show_error("mysql_FILELAYER","GLOSYSTEMID_READER","No memory");
		return FALSE;
	}
	usernum=glosysid->usernum;
	userid=talloc(UINT64,usernum);
	if(userid==NULL)
	{
		show_error("mysql_FILELAYER","GLOSYSTEMID_READER","No memory");
		return FALSE;
	}

	resTF=mysql_FILELAYER_glosystemdeviceid_select(deviceid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","GLOSYSTEMID_READER","deviceid can't select");
		return FALSE;
	}
	resTF=mysql_FILELAYER_glosystemdiskid_select(diskid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","GLOSYSTEMID_READER","diskid can't select");
		return FALSE;
	}
	resTF=mysql_FILELAYER_glosystemkindid_select(availkind);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","GLOSYSTEMID_READER","availkind can't select");
		return FALSE;
	}
	resTF=mysql_FILELAYER_glosystemregionid_select(regionid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","GLOSYSTEMID_READER","regionid can't select");
		return FALSE;
	}
	resTF=mysql_FILELAYER_glosystemuserid_select(userid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","GLOSYSTEMID_READER","userid can't select");
		return FALSE;
	}
	glosysid->deviceid=deviceid;
	glosysid->diskid=diskid;
	glosysid->availkind=availkind;
	glosysid->regionid=regionid;
	glosysid->userid=userid;
	return TRUE;
}



int mysql_FILELAYER_CHUNKGROUP_READER_META(CHUNKGROUP *chkgroup)//将CHUNKGROUP根据其中包含的路径读取到相应的区域,元数据部分
{
	int i,chunknum,resTF;
	CHUNK *chunkptr,*curchunkptr;
	chunkptr=chkgroup->ckgroup;
	chunknum=chkgroup->groupsize;

	curchunkptr=chunkptr;

	for(i=0;i<chunknum;i++)
	{
		resTF=mysql_FILELAYER_CHUNK_READER_META(curchunkptr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","CHUNKGROUP_READER_META","chunk data can't read");
			return FALSE;
		}
		curchunkptr++;
	}
	return TRUE;
}
int mysql_FILELAYER_STRIPSECTGROUP_READER(STRIPSECTGROUP *strsetgroup)//将STRIPSECTGROUP根据其中包含的路径读取到相应的区域
{
	int i,resTF;
	int strsetnum;
	STRIPSECT *strsetptr,*curstrsetptr;

	strsetptr=strsetgroup->stripsectgroup;
	strsetnum=strsetgroup->groupsize;
	curstrsetptr=strsetptr;
	for(i=0;i<strsetnum;i++)
	{
		resTF=mysql_FILELAYER_STRIPSECT_READER(curstrsetptr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","STRIPSECTGROUP_READER","stripsect data can't read");
			return FALSE;
		}
		curstrsetptr++;
	}
	return TRUE;
}
int mysql_FILELAYER_STRIPGROUP_READER(STRIPGROUP *strgroup)//将STRIPGROUP根据其中包含的路径读取到相应的区域;这里需要通过region到disk中查找
{
	int i,resTF;
	int stripnum;
	STRIP *stripptr,*curstripptr;

	stripptr=strgroup->stripgroup;
	stripnum=strgroup->groupsize;

	curstripptr=stripptr;
	for(i=0;i<stripnum;i++)
	{
		resTF=mysql_FILELAYER_STRIP_READER(curstripptr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","STRIPSECTGROUP_READER","stripsect data can't read");
			return FALSE;
		}
		curstripptr++;
	}
	return TRUE;
}
int mysql_FILELAYER_REGIONGROUP_READER(REGIONGROUP *reggroup)//将REGIONGROUP读取到相应位置
{
	int i,resTF;
	int regnum;
	REGION *regionptr,*curregionptr;

	regionptr=reggroup->regiongroup;
	regnum=reggroup->groupsize;

	curregionptr=regionptr;
	for(i=0;i<regnum;i++)
	{
		resTF=mysql_FILELAYER_REGION_READER(regionptr);
		if(resTF==FALSE)
		{
			show_error("","","");
			return FALSE;
		}
		curregionptr++;
	}
	return TRUE;
}
int mysql_FILELAYER_DISKGROUP_READER(DISKGROUP *diskgroup)//将DISKGROUP读取到相应位置
{
	int i,resTF;
	int disknum;
	DISK *diskptr,*curdiskptr;
	diskptr=diskgroup->diskgroup;
	disknum=diskgroup->groupsize;

	curdiskptr=diskptr;
	for(i=0;i<disknum;i++)
	{
		resTF=mysql_FILELAYER_DISK_READER(curdiskptr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","DISKGROUP_READER","diskgroup can't read");
			return FALSE;
		}
		curdiskptr++;
	}
	return TRUE;
}
int mysql_FILELAYER_DEVICEGROUP_READER(DEVICEGROUP *devicegroup)//将DEVICEGROUP读取到相应位置
{
	int i,resTF;
	int devicenum;
	DEVICE *deviceptr,*curdeviceptr;

	deviceptr=devicegroup->devicegroup;
	devicenum=devicegroup->groupsize;

	curdeviceptr=deviceptr;
	for(i=0;i<devicenum;i++)
	{
		resTF=mysql_FILELAYER_DEVICE_READER(curdeviceptr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","DEVICEGROUP_READER","devicegroup can't read");
			return FALSE;
		}
		curdeviceptr++;
	}
	return TRUE;
}
int mysql_FILELAYER_FILEMETAGROUP_READER(FILEMETAGROUP *fmetagroup)//将FILEMETAGROUP读取到相应位置
{
	int i,resTF;
	int filenum;
	FILEMETA *fmetaptr,*curfmetaptr;
	fmetaptr=fmetagroup->filemetagroup;
	filenum=fmetagroup->grouposize;

	curfmetaptr=fmetaptr;
	for(i=0;i<filenum;i++)
	{
		resTF=mysql_FILELAYER_FILEMETA_READER(curfmetaptr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","FILEMETAGROUP_READER","filemetagroup can't read");
			return FALSE;
		}
		curfmetaptr++;
	}
	return TRUE;
}
int mysql_FILELAYER_USERPROFILEGROUP_READER(USERGROUP *ugroup)//将USERGROUP读取相应数据
{
	int i,resTF;
	int usernum;
	USERPROFILE *userprofileptr,*curuserprofileptr;

	userprofileptr=ugroup->userlist;
	usernum=ugroup->groupsize;

	curuserprofileptr=userprofileptr;
	for(i=0;i<usernum;i++)
	{
		resTF=mysql_FILELAYER_USERPROFILE_READER(curuserprofileptr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","USERPROFILEGROUP_READER","usergroup can't read");
			return FALSE;
		}
		curuserprofileptr++;
	}
	return TRUE;
}



int mysql_FILELAYER_CHUNK_WRITER_META(CHUNK *chk)
{
	int resTF;
	resTF=mysql_FILELAYER_chunk_update(chk);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","CHUNK_WRITER_META","chunk can't select");
		return FALSE;
	}
	return TRUE;
}

int mysql_FILELAYER_STRIPSECT_WRITER(STRIPSECT *strset)//将STRIPSECT根据其中包含的路径写入到相应的区域
{
	int resTF;
	UINT64 strsetid;
	UINT64 *chunkid;
	int chunknum;

	resTF=mysql_FILELAYER_stripsect_update(strset);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","STRIPSECT_WRITER","stripsect can't update");
		return FALSE;
	}
	strsetid=strset->StripsectID;
	chunkid=strset->chunkid;
	chunknum=strset->chunknum;
	resTF=mysql_FILELAYER_stripsectchunkid_update(chunkid,chunknum,strsetid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","STRIPSECT_WRITER","stripsectid can't update");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_STRIP_WRITER(STRIP *str)//将STRIPSECT根据其中包含的路径写入到相应的区域;这里需要通过region到disk中查找
{
	int resTF;
	UINT64 stripid;
	UINT64 *chunkid,*deviceid,*diskid,*strsetid;
	int chunknum,devicenum,disknum,strsetnum;

	stripid=str->StripID;
	resTF=mysql_FILELAYER_strip_update(str);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","STRIP_WRITER","strip can't update");
		return FALSE;
	}
	chunkid=str->chunkid;
	chunknum=str->chunknum;
	resTF=mysql_FILELAYER_stripchunkid_update(chunkid,chunknum,stripid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","STRIP_WRITER","chunkid can't update");
		return FALSE;
	}
	deviceid=str->deviceid;
	devicenum=str->devicenum;
	resTF=mysql_FILELAYER_stripdeviceid_update(deviceid,devicenum,stripid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","STRIP_WRITER","deviceid can't update");
		return FALSE;
	}
	diskid=str->diskid;
	disknum=str->disknum;
	resTF=mysql_FILELAYER_stripdiskid_update(diskid,disknum,stripid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","STRIP_WRITER","diskid can't update");
		return FALSE;
	}
	strsetid=str->stripsectid;
	strsetnum=str->strsetnum;
	resTF=mysql_FILELAYER_stripstripsectid_update(strsetid,strsetnum,stripid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","STRIP_WRITER","stripsectid can't update");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_REGION_WRITER(REGION *reg)//将region写入相应位置;这里需要通过region到disk中查找
{
	int resTF;
	UINT64 regionid;
	UINT64 *deviceid,*diskid,*fileid,*stripid;
	int devicenum,disknum,filenum,stripnum;

	regionid=reg->RegionID;
	resTF=mysql_FILELAYER_region_update(reg);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","REGION_WRITER","region can't update");
		return FALSE;
	}
	devicenum=reg->devicenum;
	deviceid=reg->deviceid;
	
	disknum=reg->disknum;
	diskid=reg->diskid;

	filenum=reg->filenum;
	fileid=reg->fileid;

	stripnum=reg->stripnum;
	stripid=reg->stripid;

	resTF=mysql_FILELAYER_regiondeviceid_update(deviceid,devicenum,regionid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","REGION_WRITER","deviceid can't update");
		return FALSE;
	}
	resTF=mysql_FILELAYER_regiondiskid_update(diskid,disknum,regionid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","REGION_WRITER","diskid can't update");
		return FALSE;
	}
	resTF=mysql_FILELAYER_regionfileid_update(fileid,filenum,regionid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","REGION_WRITER","fileid can't update");
		return FALSE;
	}
	resTF=mysql_FILELAYER_regionstripid_update(stripid,stripnum,regionid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","REGION_WRITER","stripid can't update");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_DISK_WRITER(DISK *disk)//将DISK的元数据写入磁盘
{
	int resTF;
	UINT64 diskid;
	UINT64 *regionid;
	int regionnum;
	diskid=disk->DiskID;
	resTF=mysql_FILELAYER_disk_update(disk);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","DISK_WRITER","disk can't update");
		return FALSE;
	}
	regionid=disk->regionid;
	regionnum=disk->regionnum;
	resTF=mysql_FILELAYER_diskregionid_update(regionid,regionnum,diskid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","DISK_WRITER","regionid can't update");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_DEVICE_WRITER(DEVICE *device)//将DEVICE的元数据写入磁盘
{
	int resTF;
	UINT64 *diskid,*regionid;
	int *speed;
	int disknum,regionnum,processnum;
	UINT64 deviceid;
	deviceid=device->DeviceID;
	resTF=mysql_FILELAYER_device_update(device);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","DEVICE_WRITER","device can't update");
		return FALSE;
	}
	diskid=device->diskid;
	disknum=device->disknum;

	speed=device->speed;
	processnum=device->processnum;

	regionid=device->regionid;
	regionnum=device->regionnum;

	resTF=mysql_FILELAYER_devicediskid_update(diskid,disknum,deviceid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","DEVICE_WRITER","diskid can't update");
		return FALSE;
	}
	resTF=mysql_FILELAYER_deviceprocessid_update(speed,processnum,deviceid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","DEVICE_WRITER","process can't update");
		return FALSE;
	}
	resTF=mysql_FILELAYER_deviceregionid_update(regionid,regionnum,deviceid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","DEVICE_WRITER","regionid can't update");
		return FALSE;
	}
	return TRUE;
}
int mysql_FILELAYER_FILEMETA_WRITER(FILEMETA *fmeta)//将文件的元数据息写入磁盘
{
	int resTF;
	UINT64 FileID,regionid;
	UINT64 *subfileid;
	int subfilenum;

	CHUNKPATH *chunkpath;
	UINT64 *chunkid,*deviceid,*diskid,*stripid,*strsetid;
	int chunknum,devicenum,disknum,stripnum,strsetnum;

	FILEINF *filechunkinf;

	FileID=fmeta->FileID;
	filechunkinf=fmeta->filechunkinf;
	if(filechunkinf==NULL)
	{
		filechunkinf=talloc(FILEINF,1);
		if(filechunkinf==NULL)
		{
			show_error("mysql_FILELAYER","FILEMETA_WRITER","No memory");
			return FALSE;
		}
		regionid=fmeta->regionid;
		GLOBAL_set_FILEINF_data(filechunkinf,FileID,NULL,fmeta,
								NULL,NULL,0,
								NULL,regionid,
								NULL,NULL,0,NULL,NULL,0,
								NULL,NULL,0,NULL,NULL,0);
		fmeta->filechunkinf=filechunkinf;
		resTF=mysql_FILELAYER_filemeta_update(fmeta);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","FILEMETA_WRITER","filemeta can't update");
			return FALSE;
		}
		free(filechunkinf);
		fmeta->filechunkinf=NULL;
	}
	else
	{
		resTF=mysql_FILELAYER_filemeta_update(fmeta);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","FILEMETA_WRITER","filemeta can't update");
			return FALSE;
		}
		chunkid=filechunkinf->chunkid;
		chunkpath=filechunkinf->chkpath;
		chunknum=filechunkinf->chunknum;

		resTF=mysql_FILELAYER_filechunkid_update(chunkid,chunknum,FileID);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","FILEMETA_WRITER","chunkid can't update");
			return FALSE;
		}

		resTF=mysql_FILELAYER_filechunkpath_update(chunkpath,chunknum,FileID);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","FILEMETA_WRITER","chunkpath can't update");
			return FALSE;
		}

		deviceid=filechunkinf->deviceid;
		devicenum=filechunkinf->devicenum;

		resTF=mysql_FILELAYER_filedeviceid_update(deviceid,devicenum,FileID);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","FILEMETA_WRITER","deviceid can't update");
			return FALSE;
		}

		diskid=filechunkinf->diskid;
		disknum=filechunkinf->disknum;

		resTF=mysql_FILELAYER_filediskid_update(diskid,disknum,FileID);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","FILEMETA_WRITER","diskid can't update");
			return FALSE;
		}

		stripid=filechunkinf->stripid;
		stripnum=filechunkinf->stripnum;

		resTF=mysql_FILELAYER_filestripid_update(stripid,stripnum,FileID);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","FILEMETA_WRITER","stripid can't update");
			return FALSE;
		}

		strsetid=filechunkinf->stripsectid;
		strsetnum=filechunkinf->stripsectnum;

		resTF=mysql_FILELAYER_filestripsectid_update(strsetid,strsetnum,FileID);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","FILEMETA_WRITER","stripsectid can't update");
			return FALSE;
		}
	}

	subfilenum=fmeta->subfilenum;
	if(subfilenum!=0)
	{
		subfileid=fmeta->subfileidlist;
		resTF=mysql_FILELAYER_filesubfileid_update(subfileid,subfilenum,FileID);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","FILEMETA_WRITER","subfile can't update");
			return FALSE;
		}
	}
	return TRUE;
}
int mysql_FILELAYER_USERPROFILE_WRITER(USERPROFILE *pfile)//将用户信息的元数据写入磁盘
{
	int resTF;
	resTF=mysql_FILELAYER_userprofile_update(pfile);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","USERPROFILE_WRITER","userprofile can't update");
		return FALSE;
	}
	return TRUE;
}
//由于全局文件只有一个无需group处理
int mysql_FILELAYER_GLOSYSTEMID_WRITER(GLOSYSTEMID *glosysid)//将用户信息的元数据写入磁盘
{
	int resTF;
	int *availkind;
	UINT64 *deviceid,*diskid,*regionid,*userid;
	int devicenum,disknum,kindnum,regionnum,usernum;
	resTF=mysql_FILELAYER_glosystemid_update(glosysid);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","GLOSYSTEMID_WRITER","glosystemid can't update");
		return FALSE;
	}

	deviceid=glosysid->deviceid;
	devicenum=glosysid->devicenum;

	resTF=mysql_FILELAYER_glosystemdeviceid_update(deviceid,devicenum);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","GLOSYSTEMID_WRITER","deviceid");
		return FALSE;
	}

	diskid=glosysid->diskid;
	disknum=glosysid->disknum;

	resTF=mysql_FILELAYER_glosystemdiskid_update(diskid,disknum);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","GLOSYSTEMID_WRITER","diskid can't update");
		return FALSE;
	}

	availkind=glosysid->availkind;
	kindnum=glosysid->availnum;

	resTF=mysql_FILELAYER_glosystemkindid_update(availkind,kindnum);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","GLOSYSTEMID_WRITER","kindid can't update");
		return FALSE;
	}

	regionid=glosysid->regionid;
	regionnum=glosysid->regionnum;

	resTF=mysql_FILELAYER_glosystemregionid_update(regionid,regionnum);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","GLOSYSTEMID_WRITER","regionid can't update");
		return FALSE;
	}

	userid=glosysid->userid;
	usernum=glosysid->usernum;
	
	resTF=mysql_FILELAYER_glosystemuserid_update(userid,usernum);
	if(resTF==FALSE)
	{
		show_error("mysql_FILELAYER","GLOSYSTEMID_WRITER","userid can't update");
		return FALSE;
	}

	return TRUE;
}


int mysql_FILELAYER_CHUNKGROUP_WRITER_META(CHUNKGROUP *chkgroup)//将CHUNKGROUP根据其中包含的路径写入到相应的区域,元数据部分
{
	int i,resTF;
	int chunknum;
	CHUNK *chunkptr,*curchunkptr;

	chunkptr=chkgroup->ckgroup;
	chunknum=chkgroup->groupsize;

	curchunkptr=chunkptr;
	for(i=0;i<chunknum;i++)
	{
		resTF=mysql_FILELAYER_CHUNK_WRITER_META(curchunkptr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","CHUNKGROUP_WRITER_META","chunk can't write");
			return FALSE;
		}
		curchunkptr++;
	}
	return TRUE;
}

int mysql_FILELAYER_STRIPSECTGROUP_WRITER(STRIPSECTGROUP *strsetgroup)//将STRIPSECTGROUP根据其中包含的路径写入到相应的区域
{
	int i,resTF;
	int strsetum;
	STRIPSECT *strsetptr,*curstrsetptr;

	strsetptr=strsetgroup->stripsectgroup;
	strsetum=strsetgroup->groupsize;

	curstrsetptr=strsetptr;
	for(i=0;i<strsetum;i++)
	{
		resTF=mysql_FILELAYER_STRIPSECT_WRITER(curstrsetptr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","STRIPSECTGROUP_WRITER","stripsect can't read");
			return FALSE;
		}
		curstrsetptr++;
	}
	return TRUE;
}
int mysql_FILELAYER_STRIPGROUP_WRITER(STRIPGROUP *strgroup)//将STRIPGROUP根据其中包含的路径写入到相应的区域;这里需要通过region到disk中查找
{
	int i,resTF;
	int stripnum;
	STRIP *stripptr,*curstripptr;

	stripptr=strgroup->stripgroup;
	stripnum=strgroup->groupsize;

	curstripptr=stripptr;
	for(i=0;i<stripnum;i++)
	{
		resTF=mysql_FILELAYER_STRIP_WRITER(curstripptr);
		if(resTF==FALSE)
		{
			show_error("mysql_FILELAYER","STRIPGROUP_WRITER","strip can't write");
			return FALSE;
		}
		curstripptr++;
	}
	return TRUE;
}
int mysql_FILELAYER_REGIONGROUP_WRITER(REGIONGROUP *reggroup)//将REGIONGROUP写入相应数据
{
	return TRUE;
}
int mysql_FILELAYER_DISKGROUP_WRITER(DISKGROUP *diskgroup)//将DISKGROUP写入相应数据
{
	return TRUE;
}
int mysql_FILELAYER_DEVICEGROUP_WRITER(DEVICEGROUP *devicegroup)//将DEVICEGROUP写入相应数据
{
	return TRUE;
}
int mysql_FILELAYER_FILEMETAGROUP_WRITER(FILEMETAGROUP *fmetagroup)//将FILEMETAGROUP写入相应数据
{
	return TRUE;
}
int mysql_FILELAYER_USERPROFILEGROUP_WRITER(USERGROUP *ugroup)//将USERGROUP写入到相应位置
{
	return TRUE;
}