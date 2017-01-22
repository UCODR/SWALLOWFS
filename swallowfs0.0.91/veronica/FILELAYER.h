#include "global_define.h"
#include "mysql.h"
#include "file.h"
//根据据全局定义决定交给那个接口函数处理
//调试交给file，运行交给access
extern int FILELAYER_intial();

extern int FILELAYER_CHUNK_READER_META(CHUNK *chk);//将CHUNK根据全局路径和chunkpath读取元数据
extern int FILELAYER_CHUNK_READER_DATA(CHUNK *chk);//将CHUNK根据其中包含的路径读出到相应的区域,数据部分，调用条件stripsect文件必须存在
extern int FILELAYER_STRIPSECT_READER(STRIPSECT *strset);//将STRIPSECT根据其中包含的路径读出到相应的区域
extern int FILELAYER_STRIP_READER(STRIP *str);//将STRIP根据其中包含的路径读出到相应的区域;这里需要通过region到disk中查找
extern int FILELAYER_REGION_READER(REGION *reg);//将REGION读取相应数据
extern int FILELAYER_DISK_READER(DISK *disk);//将DISK读取到相应数据
extern int FILELAYER_DEVICE_READER(DEVICE *device);//将DISK读取到相应数据
extern int FILELAYER_FILEMETA_READER(FILEMETA *fmeta);//将DEVICE读取到相应数据
extern int FILELAYER_USERPROFILE_READER(USERPROFILE *pfile);//将USERPROFILE读取到相应数据


extern int FILELAYER_GLOSYSTEMID_READER(GLOSYSTEMID *glosysid);//将用户信息读取到相应数据

extern int FILELAYER_CHUNKGROUP_READER_META(CHUNKGROUP *chkgroup);//将CHUNKGROUP根据其中包含的路径读取到相应的区域,元数据部分
extern int FILELAYER_CHUNKGROUP_READER_DATA(CHUNKGROUP *chkgroup);//将CHUNKGROUP根据其中包含的路径读取到相应的区域,数据部分
extern int FILELAYER_STRIPSECTGROUP_READER(STRIPSECTGROUP *strsetgroup);//将STRIPSECTGROUP根据其中包含的路径读取到相应的区域
extern int FILELAYER_STRIPGROUP_READER(STRIPGROUP *strgroup);//将STRIPGROUP根据其中包含的路径读取到相应的区域;这里需要通过region到disk中查找
extern int FILELAYER_REGIONGROUP_READER(REGIONGROUP *reggroup);//将REGIONGROUP读取到相应位置
extern int FILELAYER_DISKGROUP_READER(DISKGROUP *diskgroup);//将DISKGROUP读取到相应位置
extern int FILELAYER_DEVICEGROUP_READER(DEVICEGROUP *devicegroup);//将DEVICEGROUP读取到相应位置
extern int FILELAYER_FILEMETAGROUP_READER(FILEMETAGROUP *fmetagroup);//将FILEMETAGROUP读取到相应位置
extern int FILELAYER_USERPROFILEGROUP_READER(USERGROUP *ugroup);//将USERGROUP读取相应数据


//单个写操作,写入磁盘
extern int FILELAYER_CHUNK_WRITER_META(CHUNK *chk);//将CHUNK根据其中包含的路径写入到相应的区域,元数据部分
extern int FILELAYER_CHUNK_WRITER_DATA(CHUNK *chk);//将CHUNK根据其中包含的路径写入到相应的区域,数据部分
extern int FILELAYER_STRIPSECT_CREATE(STRIPSECT *strset);//创建一个strset组块
extern int FILELAYER_STRIPSECT_WRITER(STRIPSECT *strset);//将STRIPSECT根据其中包含的路径写入到相应的区域
extern int FILELAYER_STRIP_WRITER(STRIP *str);//将STRIPSECT根据其中包含的路径写入到相应的区域;这里需要通过region到disk中查找
extern int FILELAYER_REGION_WRITER(REGION *reg);//将region写入相应位置;这里需要通过region到disk中查找
extern int FILELAYER_DISK_WRITER(DISK *disk);//将DISK的元数据写入磁盘
extern int FILELAYER_DEVICE_WRITER(DEVICE *device);//将DEVICE的元数据写入磁盘
extern int FILELAYER_FILEMETA_WRITER(FILEMETA *fmeta);//将文件的元数据息写入磁盘
extern int FILELAYER_USERPROFILE_WRITER(USERPROFILE *pfile);//将用户信息的元数据写入磁盘
//由于全局文件只有一个无需group处理
extern int FILELAYER_GLOSYSTEMID_WRITER(GLOSYSTEMID *glosysid);//将用户信息的元数据写入磁盘

extern int FILELAYER_CHUNKGROUP_WRITER_META(CHUNKGROUP *chkgroup);//将CHUNKGROUP根据其中包含的路径写入到相应的区域,元数据部分
extern int FILELAYER_CHUNKGROUP_WRITER_DATA(CHUNKGROUP *chkgroup);//将CHUNKGROUP根据其中包含的路径写入到相应的区域,数据部分
extern int FILELAYER_STRIPSECTGROUP_CREATE(STRIPSECTGROUP *strsetgroup);//将STRIPSECTGROUP根据内部信息在对应位置创建相应的stripsect
extern int FILELAYER_STRIPSECTGROUP_WRITER(STRIPSECTGROUP *strsetgroup);//将STRIPSECTGROUP根据其中包含的路径写入到相应的区域
extern int FILELAYER_STRIPGROUP_WRITER(STRIPGROUP *strgroup);//将STRIPGROUP根据其中包含的路径写入到相应的区域;这里需要通过region到disk中查找
extern int FILELAYER_REGIONGROUP_WRITER(REGIONGROUP *reggroup);//将REGIONGROUP写入相应数据
extern int FILELAYER_DISKGROUP_WRITER(DISKGROUP *diskgroup);//将DISKGROUP写入相应数据
extern int FILELAYER_DEVICEGROUP_WRITER(DEVICEGROUP *devicegroup);//将DEVICEGROUP写入相应数据
extern int FILELAYER_FILEMETAGROUP_WRITER(FILEMETAGROUP *fmetagroup);//将FILEMETAGROUP写入相应数据
extern int FILELAYER_USERPROFILEGROUP_WRITER(USERGROUP *ugroup);//将USERGROUP写入到相应位置