#include "FILELAYER.h"
int FILELAYER_intial()
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_intial();
		if(resTF==FALSE)
		{
			show_error("FILELAYER","intial","file interface can't intial");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_intial();
		if(resTF==FALSE)
		{
			show_error("FILELAYER","intial","file interface can't intial");
			return FALSE;
		}
		break;
	}
	return TRUE;
}

int FILELAYER_CHUNK_READER_META(CHUNK *chk)//将CHUNK根据全局路径和chunkpath读取元数据
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_CHUNK_READER_META(chk);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","intial","chunk meta can't read");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_CHUNK_READER_META(chk);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","intial","chunk meta can't read");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_CHUNK_READER_DATA(CHUNK *chk)//将CHUNK根据其中包含的路径读出到相应的区域,数据部分，调用条件stripsect文件必须存在
{
	int resTF;
	resTF=file_FILELAYER_CHUNK_READER_DATA(chk);
	if(resTF==FALSE)
	{
		show_error("FILELAYER","CHUNK_READER_DATA","chunk data can't read");
		return FALSE;
	}
	return TRUE;
}
int FILELAYER_STRIPSECT_READER(STRIPSECT *strset)//将STRIPSECT根据其中包含的路径读出到相应的区域
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_STRIPSECT_READER(strset);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","STRIPSECT_READER","stripsect can't read");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_STRIPSECT_READER(strset);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","STRIPSECT_READER","stripsect can't read");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_STRIP_READER(STRIP *str)//将STRIP根据其中包含的路径读出到相应的区域;这里需要通过region到disk中查找
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_STRIP_READER(str);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","STRIP_READER","strip can't read");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_STRIP_READER(str);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","STRIP_READER","strip can't read");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_REGION_READER(REGION *reg)//将REGION读取相应数据
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_REGION_READER(reg);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","REGION_READER","region can't read");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_REGION_READER(reg);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","REGION_READER","region can't read");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_DISK_READER(DISK *disk)//将DISK读取到相应数据
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_DISK_READER(disk);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","DISK_READER","disk can't read");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_DISK_READER(disk);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","DISK_READER","disk can't read");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_DEVICE_READER(DEVICE *device)//将DISK读取到相应数据
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_DEVICE_READER(device);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","DEVICE_READER","device can't read");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_DEVICE_READER(device);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","DEVICE_READER","device can't read");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_FILEMETA_READER(FILEMETA *fmeta)//将DEVICE读取到相应数据
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_FILEMETA_READER(fmeta);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","FILEMETA_READER","filemeta can't read");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_FILEMETA_READER(fmeta);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","FILEMETA_READER","filemeta can't read");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_USERPROFILE_READER(USERPROFILE *pfile)//将USERPROFILE读取到相应数据
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_USERPROFILE_READER(pfile);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","USERPROFILE_READER","userprofile can't read");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_USERPROFILE_READER(pfile);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","USERPROFILE_READER","userprofile can't read");
			return FALSE;
		}
		break;
	}
	return TRUE;
}


extern int FILELAYER_GLOSYSTEMID_READER(GLOSYSTEMID *glosysid)//将用户信息读取到相应数据
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_GLOSYSTEMID_READER(glosysid);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","GLOSYSTEMID_READER","glosystemid can't read");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_GLOSYSTEMID_READER(glosysid);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","GLOSYSTEMID_READER","glosystemid can't read");
			return FALSE;
		}
		break;
	}
	return TRUE;
}

int FILELAYER_CHUNKGROUP_READER_META(CHUNKGROUP *chkgroup)//将CHUNKGROUP根据其中包含的路径读取到相应的区域,元数据部分
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_CHUNKGROUP_READER_META(chkgroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","CHUNKGROUP_READER_META","chunkgroup can't read");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_CHUNKGROUP_READER_META(chkgroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","CHUNKGROUP_READER_META","chunkgroup can't read");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_CHUNKGROUP_READER_DATA(CHUNKGROUP *chkgroup)//将CHUNKGROUP根据其中包含的路径读取到相应的区域,数据部分
{
	int resTF;
	resTF=file_FILELAYER_CHUNKGROUP_READER_META(chkgroup);
	if(resTF==FALSE)
	{
		show_error("FILELAYER","CHUNKGROUP_READER_DATA","chunkgroup can't read");
		return FALSE;
	}
	return TRUE;
}
int FILELAYER_STRIPSECTGROUP_READER(STRIPSECTGROUP *strsetgroup)//将STRIPSECTGROUP根据其中包含的路径读取到相应的区域
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_STRIPSECTGROUP_READER(strsetgroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","STRIPSECTGROUP_READER","stripsectgroup can't read");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_STRIPSECTGROUP_READER(strsetgroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","STRIPSECTGROUP_READER","stripsectgroup can't read");
			return FALSE;
		}
		break;
	}

	return TRUE;
}
int FILELAYER_STRIPGROUP_READER(STRIPGROUP *strgroup)//将STRIPGROUP根据其中包含的路径读取到相应的区域;这里需要通过region到disk中查找
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_STRIPGROUP_READER(strgroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","STRIPGROUP_READER","stripgroup can't read");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=mysql_FILELAYER_STRIPGROUP_READER(strgroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","STRIPGROUP_READER","stripgroup can't read");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_REGIONGROUP_READER(REGIONGROUP *reggroup)//将REGIONGROUP读取到相应位置
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_REGIONGROUP_READER(reggroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","REGIONGROUP_READER","regiongroup can't read");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_REGIONGROUP_READER(reggroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","REGIONGROUP_READER","regiongroup can't read");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_DISKGROUP_READER(DISKGROUP *diskgroup)//将DISKGROUP读取到相应位置
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_DISKGROUP_READER(diskgroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","DISKGROUP_READER","diskgroup can't read");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_DISKGROUP_READER(diskgroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","DISKGROUP_READER","diskgroup can't read");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_DEVICEGROUP_READER(DEVICEGROUP *devicegroup)//将DEVICEGROUP读取到相应位置
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_DEVICEGROUP_READER(devicegroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","DEVICEGROUP_READER","device can't read");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_DEVICEGROUP_READER(devicegroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","DEVICEGROUP_READER","device can't read");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_FILEMETAGROUP_READER(FILEMETAGROUP *fmetagroup)//将FILEMETAGROUP读取到相应位置
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_FILEMETAGROUP_READER(fmetagroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","FILEMETAGROUP_READER","filemeta can't read");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_FILEMETAGROUP_READER(fmetagroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","FILEMETAGROUP_READER","filemeta can't read");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_USERPROFILEGROUP_READER(USERGROUP *ugroup)//将USERGROUP读取相应数据
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_USERPROFILEGROUP_READER(ugroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","USERPROFILEGROUP_READER","usergroup can't read");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_USERPROFILEGROUP_READER(ugroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","USERPROFILEGROUP_READER","usergroup can't read");
			return FALSE;
		}
		break;
	}
	return TRUE;
}


//单个写操作,写入磁盘
int FILELAYER_CHUNK_WRITER_META(CHUNK *chk)//将CHUNK根据其中包含的路径写入到相应的区域,元数据部分
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_CHUNK_WRITER_META(chk);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","CHUNK_WRITER_META","chunk meta can't write");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_CHUNK_WRITER_META(chk);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","CHUNK_WRITER_META","chunk meta can't write");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_CHUNK_WRITER_DATA(CHUNK *chk)//将CHUNK根据其中包含的路径写入到相应的区域,数据部分
{
	int resTF,selectindex;
	resTF=file_FILELAYER_CHUNK_WRITER_DATA(chk);
	if(resTF==FALSE)
	{
		show_error("FILELAYER","_CHUNK_WRITER_DATA","chunk data can't write");
		return FALSE;
	}
	return TRUE;
}
int FILELAYER_STRIPSECT_CREATE(STRIPSECT *strset)//创建一个strset组块
{
	int resTF;
	resTF=file_FILELAYER_STRIPSECT_CREATE(strset);
	if(resTF==FALSE)
	{
		show_error("FILELAYER","STRIPSECT_CREATE","stripsect can't create");
		return FALSE;
	}
	
	return TRUE;
}
int FILELAYER_STRIPSECT_WRITER(STRIPSECT *strset)//将STRIPSECT根据其中包含的路径写入到相应的区域
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_STRIPSECT_WRITER(strset);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","STRIPSECT_WRITER","stripsect can't write");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_STRIPSECT_WRITER(strset);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","STRIPSECT_WRITER","stripsect can't write");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_STRIP_WRITER(STRIP *str)//将STRIPSECT根据其中包含的路径写入到相应的区域;这里需要通过region到disk中查找
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_STRIP_WRITER(str);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","STRIP_WRITER","strip can't write");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_STRIP_WRITER(str);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","STRIP_WRITER","strip can't write");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_REGION_WRITER(REGION *reg)//将region写入相应位置;这里需要通过region到disk中查找
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_REGION_WRITER(reg);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","REGION_WRITER","region can't write");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_REGION_WRITER(reg);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","REGION_WRITER","region can't write");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_DISK_WRITER(DISK *disk)//将DISK的元数据写入磁盘
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_DISK_WRITER(disk);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","DISK_WRITER","disk can't write");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_DISK_WRITER(disk);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","DISK_WRITER","disk can't write");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_DEVICE_WRITER(DEVICE *device)//将DEVICE的元数据写入磁盘
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_DEVICE_WRITER(device);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","DEVICE_WRITER","device can't write");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_DEVICE_WRITER(device);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","DEVICE_WRITER","device can't write");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_FILEMETA_WRITER(FILEMETA *fmeta)//将文件的元数据息写入磁盘
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_FILEMETA_WRITER(fmeta);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","FILEMETA_WRITER","filemeta can't write");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_FILEMETA_WRITER(fmeta);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","FILEMETA_WRITER","filemeta can't write");
			return FALSE;
		}
		break;
	}
	return TRUE;
}

int FILELAYER_USERPROFILE_WRITER(USERPROFILE *pfile)//将用户信息的元数据写入磁盘
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_USERPROFILE_WRITER(pfile);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","USERPROFILE_WRITER","userprofile can't write");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_USERPROFILE_WRITER(pfile);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","USERPROFILE_WRITER","userprofile can't write");
			return FALSE;
		}
		break;
	}
	return TRUE;
}

//由于全局文件只有一个无需group处理
extern int FILELAYER_GLOSYSTEMID_WRITER(GLOSYSTEMID *glosysid)//将用户信息的元数据写入磁盘
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_GLOSYSTEMID_WRITER(glosysid);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","GLOSYSTEMID_WRITER","glosystemid can't write");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_GLOSYSTEMID_WRITER(glosysid);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","GLOSYSTEMID_WRITER","glosystemid can't write");
			return FALSE;
		}
		break;
	}
	return TRUE;
}

int FILELAYER_CHUNKGROUP_WRITER_META(CHUNKGROUP *chkgroup)//将CHUNKGROUP根据其中包含的路径写入到相应的区域,元数据部分
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_CHUNKGROUP_WRITER_META(chkgroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","CHUNKGROUP_WRITER_META","");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_CHUNKGROUP_WRITER_META(chkgroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","CHUNKGROUP_WRITER_META","");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_CHUNKGROUP_WRITER_DATA(CHUNKGROUP *chkgroup)//将CHUNKGROUP根据其中包含的路径写入到相应的区域,数据部分
{
	int resTF;
	resTF=file_FILELAYER_CHUNKGROUP_WRITER_DATA(chkgroup);
	if(resTF==FALSE)
	{
		show_error("FILELAYER","CHUNKGROUP_WRITER_DATA","chunk data can't write");
	}
	return TRUE;
}
int FILELAYER_STRIPSECTGROUP_CREATE(STRIPSECTGROUP *strsetgroup)//将STRIPSECTGROUP根据内部信息在对应位置创建相应的stripsect
{
	int resTF;
	resTF=file_FILELAYER_STRIPSECTGROUP_CREATE(strsetgroup);
	if(resTF==FALSE)
	{
		show_error("FILELAYER","STRIPSECTGROUP_CREATE","stripsectgroup can't create");
		return FALSE;
	}
	return TRUE;
}
int FILELAYER_STRIPSECTGROUP_WRITER(STRIPSECTGROUP *strsetgroup)//将STRIPSECTGROUP根据其中包含的路径写入到相应的区域
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_STRIPSECTGROUP_WRITER(strsetgroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","STRIPSECTGROUP_WRITER","stripsect group can't write");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_STRIPSECTGROUP_WRITER(strsetgroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","STRIPSECTGROUP_WRITER","stripsect group can't write");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_STRIPGROUP_WRITER(STRIPGROUP *strgroup)//将STRIPGROUP根据其中包含的路径写入到相应的区域;这里需要通过region到disk中查找
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_STRIPGROUP_WRITER(strgroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","STRIPGROUP_WRITER","stripgroup can't write");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_STRIPGROUP_WRITER(strgroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","STRIPGROUP_WRITER","stripgroup can't write");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_REGIONGROUP_WRITER(REGIONGROUP *reggroup)//将REGIONGROUP写入相应数据
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_REGIONGROUP_WRITER(reggroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","REGIONGROUP_WRITER","regiongroup can't create");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_REGIONGROUP_WRITER(reggroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","REGIONGROUP_WRITER","regiongroup can't create");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_DISKGROUP_WRITER(DISKGROUP *diskgroup)//将DISKGROUP写入相应数据
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_DISKGROUP_WRITER(diskgroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","DISKGROUP_WRITER","disk group can't write");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_DISKGROUP_WRITER(diskgroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","DISKGROUP_WRITER","disk group can't write");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_DEVICEGROUP_WRITER(DEVICEGROUP *devicegroup)//将DEVICEGROUP写入相应数据
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_DEVICEGROUP_WRITER(devicegroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","DEVICEGROUP_WRITER","device group can't write");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_DEVICEGROUP_WRITER(devicegroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","DEVICEGROUP_WRITER","device group can't write");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_FILEMETAGROUP_WRITER(FILEMETAGROUP *fmetagroup)//将FILEMETAGROUP写入相应数据
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_FILEMETAGROUP_WRITER(fmetagroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","FILEMETAGROUP_WRITER","filemeta group can't write");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_FILEMETAGROUP_WRITER(fmetagroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","FILEMETAGROUP_WRITER","filemeta group can't write");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int FILELAYER_USERPROFILEGROUP_WRITER(USERGROUP *ugroup)//将USERGROUP写入到相应位置
{
	int resTF,selectindex;
	selectindex=FILESELECT;
	switch(selectindex)
	{
	case MYSQLINTERFACE:
		resTF=mysql_FILELAYER_USERPROFILEGROUP_WRITER(ugroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","USERPROFILEGROUP_WRITER","usergroup can't write");
			return FALSE;
		}
		break;
	case FILEINTERFACE:
		resTF=file_FILELAYER_USERPROFILEGROUP_WRITER(ugroup);
		if(resTF==FALSE)
		{
			show_error("FILELAYER","USERPROFILEGROUP_WRITER","usergroup can't write");
			return FALSE;
		}
		break;
	}
	return TRUE;
}