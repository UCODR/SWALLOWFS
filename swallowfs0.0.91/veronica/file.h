#ifndef _FILE_H
#define _FILE_H

#include "global_define.h"
#include "profile.h"
//filelayer
//底层
extern int file_FILELAYER_intial();
//相应的数据路径是不是可以得到
extern int file_FILELAYER_device_available(DISK *diskptr);//返回当前文件路径是否可得
//文件必须存在
extern int file_FILELAYER_BYTE_READER(char *filepath,BYTESTREAM *bstream,long offset);//将数据流从路径的偏移量位置读取
extern int file_FILELAYER_BYTE_WRITER(char *filepath,BYTESTREAM *bstream,long offset);//将数据流写入制定路径偏移量插入
//允许文件不存在
extern int file_FILELAYER_BYTE_CREATE(char *filepath,BYTESTREAM *bstream);//通过bstream创建一个文件，

//region,strip,stripsect分块的生成
extern int file_glostr(char *gloname,char *glokind,char *gloid,char *finalitem);
extern int file_regionstr(char *regname,char *regid);
extern int file_regionstr_name(char *regname,char *regid);
extern int file_stripstr(char *strname,char *strid);
extern int file_stripstr_name(char *strname,char *strid);
extern int file_stripsectstr(char *strsetname,char *strsetid);
extern int file_stripsectstr_name(char *strsetname,char *strsetid);
extern int file_chunkstr_name(char *strsetname,char *strsetid);
extern int file_filemetastr_name(char *filemetaname,char *filemetaid);
extern int file_userprofilestr(char *username,char *userid);
extern int file_userprofilestr_name(char *username,char *userid);
extern int file_devicestr(char *devicename,char *deviceid);
extern int file_devicestr_name(char *devicename,char *deviceid);
extern int file_diskstr_name(char *diskname,char *diskid);
extern int file_globaldeine_name(char *glodepath);

//数据操作 
//单个读操作，主要是根据id来读写
//其中chunk读写由于性能相关因此需要独立设计
extern int file_FILELAYER_CHUNK_READER_META(CHUNK *chk);//将CHUNK根据全局路径和chunkpath读取元数据
extern int file_FILELAYER_CHUNK_READER_DATA(CHUNK *chk);//将CHUNK根据其中包含的路径读出到相应的区域,数据部分，调用条件stripsect文件必须存在
extern int file_FILELAYER_STRIPSECT_READER(STRIPSECT *strset);//将STRIPSECT根据其中包含的路径读出到相应的区域
extern int file_FILELAYER_STRIP_READER(STRIP *str);//将STRIP根据其中包含的路径读出到相应的区域;这里需要通过region到disk中查找
extern int file_FILELAYER_REGION_READER(REGION *reg);//将REGION读取相应数据
extern int file_FILELAYER_DISK_READER(DISK *disk);//将DISK读取到相应数据
extern int file_FILELAYER_DEVICE_READER(DEVICE *device);//将DISK读取到相应数据
extern int file_FILELAYER_FILEMETA_READER(FILEMETA *fmeta);//将DEVICE读取到相应数据
extern int file_FILELAYER_USERPROFILE_READER(USERPROFILE *pfile);//将USERPROFILE读取到相应数据
//由于全局文件只有一个无需group处理
extern int file_FILELAYER_GLOSYSTEMID_READER(GLOSYSTEMID *glosysid);//将用户信息读取到相应数据

//组块读取

extern int file_FILELAYER_CHUNKGROUP_READER_META(CHUNKGROUP *chkgroup);//将CHUNKGROUP根据其中包含的路径读取到相应的区域,元数据部分
extern int file_FILELAYER_CHUNKGROUP_READER_DATA(CHUNKGROUP *chkgroup);//将CHUNKGROUP根据其中包含的路径读取到相应的区域,数据部分
extern int file_FILELAYER_STRIPSECTGROUP_READER(STRIPSECTGROUP *strsetgroup);//将STRIPSECTGROUP根据其中包含的路径读取到相应的区域
extern int file_FILELAYER_STRIPGROUP_READER(STRIPGROUP *strgroup);//将STRIPGROUP根据其中包含的路径读取到相应的区域;这里需要通过region到disk中查找
extern int file_FILELAYER_REGIONGROUP_READER(REGIONGROUP *reggroup);//将REGIONGROUP读取到相应位置
extern int file_FILELAYER_DISKGROUP_READER(DISKGROUP *diskgroup);//将DISKGROUP读取到相应位置
extern int file_FILELAYER_DEVICEGROUP_READER(DEVICEGROUP *devicegroup);//将DEVICEGROUP读取到相应位置
extern int file_FILELAYER_FILEMETAGROUP_READER(FILEMETAGROUP *fmetagroup);//将FILEMETAGROUP读取到相应位置
extern int file_FILELAYER_USERPROFILEGROUP_READER(USERGROUP *ugroup);//将USERGROUP读取相应数据

//单个写操作,写入磁盘
extern int file_FILELAYER_CHUNK_WRITER_META(CHUNK *chk);//将CHUNK根据其中包含的路径写入到相应的区域,元数据部分
extern int file_FILELAYER_CHUNK_WRITER_DATA(CHUNK *chk);//将CHUNK根据其中包含的路径写入到相应的区域,数据部分
extern int file_FILELAYER_STRIPSECT_CREATE(STRIPSECT *strset);//创建一个strset组块
extern int file_FILELAYER_STRIPSECT_WRITER(STRIPSECT *strset);//将STRIPSECT根据其中包含的路径写入到相应的区域
extern int file_FILELAYER_STRIP_WRITER(STRIP *str);//将STRIPSECT根据其中包含的路径写入到相应的区域;这里需要通过region到disk中查找
extern int file_FILELAYER_REGION_WRITER(REGION *reg);//将region写入相应位置;这里需要通过region到disk中查找
extern int file_FILELAYER_DISK_WRITER(DISK *disk);//将DISK的元数据写入磁盘
extern int file_FILELAYER_DEVICE_WRITER(DEVICE *device);//将DEVICE的元数据写入磁盘
extern int file_FILELAYER_FILEMETA_WRITER(FILEMETA *fmeta);//将文件的元数据息写入磁盘
extern int file_FILELAYER_USERPROFILE_WRITER(USERPROFILE *pfile);//将用户信息的元数据写入磁盘
extern int file_FILELAYER_SHARE_WRITER(AONTSHARE *share);
//由于全局文件只有一个无需group处理
extern int file_FILELAYER_GLOSYSTEMID_WRITER(GLOSYSTEMID *glosysid);//将用户信息的元数据写入磁盘

//组块写入,写入磁盘
extern int file_FILELAYER_CHUNKGROUP_WRITER_META(CHUNKGROUP *chkgroup);//将CHUNKGROUP根据其中包含的路径写入到相应的区域,元数据部分
extern int file_FILELAYER_CHUNKGROUP_WRITER_DATA(CHUNKGROUP *chkgroup);//将CHUNKGROUP根据其中包含的路径写入到相应的区域,数据部分
extern int file_FILELAYER_STRIPSECTGROUP_CREATE(STRIPSECTGROUP *strsetgroup);//将STRIPSECTGROUP根据内部信息在对应位置创建相应的stripsect
extern int file_FILELAYER_STRIPSECTGROUP_WRITER(STRIPSECTGROUP *strsetgroup);//将STRIPSECTGROUP根据其中包含的路径写入到相应的区域
extern int file_FILELAYER_STRIPGROUP_WRITER(STRIPGROUP *strgroup);//将STRIPGROUP根据其中包含的路径写入到相应的区域;这里需要通过region到disk中查找
extern int file_FILELAYER_REGIONGROUP_WRITER(REGIONGROUP *reggroup);//将REGIONGROUP写入相应数据
extern int file_FILELAYER_DISKGROUP_WRITER(DISKGROUP *diskgroup);//将DISKGROUP写入相应数据
extern int file_FILELAYER_DEVICEGROUP_WRITER(DEVICEGROUP *devicegroup);//将DEVICEGROUP写入相应数据
extern int file_FILELAYER_FILEMETAGROUP_WRITER(FILEMETAGROUP *fmetagroup);//将FILEMETAGROUP写入相应数据
extern int file_FILELAYER_USERPROFILEGROUP_WRITER(USERGROUP *ugroup);//将USERGROUP写入到相应位置

//判断文件夹状态
extern int file_FILELAYER_dictionary_exists(char *dicpath);
extern int file_FILELAYER_dictionary_region_exists(UINT64 regionid);
extern int file_FILELAYER_dictionary_strip_exists(UINT64 regionid,UINT64 stripid);
extern int file_FILELAYER_dictionary_stripsect_exists(UINT64 regionid,UINT64 stripid,UINT64 strsetid);
extern int file_FILELAYER_dictionary_filemeta_exists(UINT64 regionid,UINT64 fileid);
extern int file_FILELAYER_dictionary_userprofile_exists(UINT64 userid);
extern int file_FILELAYER_dictionary_device_exists(UINT64 deviceid);
extern int file_FILELAYER_dictionary_disk_exists(UINT64 deviceid,UINT64 diskid);

//辅助函数
extern long file_FILELAYER_get_filesize(FILE *fp);//获取文件获取文件大小，指针在文件顶端

//写入块数据接口API通过pushlist来决定是否延时写
extern int file_chunk_write_API(CHUNK *chunkptr);//需要同步数据的指针

//定义64位数转字符串
#define U64toSTR(str,a64) sprintf(str,"%I64d",a64)//将数字转化为字符串
//#define REGIONSTR(regname,regid) strcat(strcat(strcat(regname,"region")regid),"/")//生成相应的区域字符串
//#define STRIPSTR(strname,strid) strcat(strcat(strcat(strname,"strip"),strid),"/")//生成相应的条带字符串
//使用明码块，由于元数据在在文件存在是明码，因此使用.txt作为扩展名
//#define STRIPSECTSTR(strsetname,strsetid) strcat(strcat(strcat(strsetname,"stripsect"),strsetid),".txt")//生成相应的条带分区字符串
//#define CHUNKSTR(chkname,chkid) strcat(strcat(strcat(chkname,"chunk"),chkid),".txt")//生成相应的条带分区字符串
//当前文件元数据
//#define FILEMETASTR(filename,filemetaid) strcat(strcat(strcat(fname,)))
#endif