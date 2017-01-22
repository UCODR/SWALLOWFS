#include "global_define.h"
#include "file.h"

#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD ""
#define DBNAME "swallow"
#define DBPORT 3306

//计算
static int mysql_intial;
static MYSQL mysqlptr;

extern MYSQL_RES *mysql_FILELAYER_select_query(char *querystr);//返回当前列表信息
extern int mysql_FILELAYER_notselect_query(char *querystr);
extern int mysql_FILELAYER_update_query(char *querystr);
extern int mysql_FILELAYER_insert_query(char *querystr);
extern int mysql_FILELAYER_delete_query(char *querystr);

extern int mysql_FILELAYER_invert_DB_string(char *scrstr);

//所有表格的接口
//这里update的定义是有就改没有就创建=delete+invert
extern int mysql_FILELAYER_chunk_select(CHUNK *chunkptr);//查询
extern int mysql_FILELAYER_chunk_update(CHUNK *chunkptr);//更新
extern int mysql_FILELAYER_chunk_insert(CHUNK *chunkptr);//插入
extern int mysql_FILELAYER_chunk_delete(UINT64 chunkid);//删除
extern int mysql_FILELAYER_chunk_delete_all();//全部删除

extern int mysql_FILELAYER_device_select(DEVICE *deviceptr);
extern int mysql_FILELAYER_device_update(DEVICE *deviceptr);
extern int mysql_FILELAYER_device_insert(DEVICE *deviceptr);
extern int mysql_FILELAYER_device_delete(UINT64 deviceid);
extern int mysql_FILELAYER_device_delete_all();

extern int mysql_FILELAYER_devicediskid_select(UINT64 *diskid,UINT64 deviceid);
extern int mysql_FILELAYER_devicediskid_update(UINT64 *diskid,int disknum,UINT64 deviceid);
extern int mysql_FILELAYER_devicediskid_insert(UINT64 *diskid,int disknum,UINT64 deviceid);
extern int mysql_FILELAYER_devicediskid_delete(UINT64 deviceid);
extern int mysql_FILELAYER_devicediskid_delete_all();

extern int mysql_FILELAYER_deviceprocessid_select(int *process,UINT64 deviceid);
extern int mysql_FILELAYER_deviceprocessid_update(int *process,int processnum,UINT64 deviceid);
extern int mysql_FILELAYER_deviceprocessid_insert(int *process,int processnum,UINT64 deviceid);
extern int mysql_FILELAYER_deviceprocessid_delete(UINT64 deviceid);
extern int mysql_FILELAYER_deviceprocessid_delete_all();

extern int mysql_FILELAYER_deviceregionid_select(UINT64 *regionid,UINT64 deviceid);
extern int mysql_FILELAYER_deviceregionid_update(UINT64 *regionid,int regionum,UINT64 deviceid);
extern int mysql_FILELAYER_deviceregionid_insert(UINT64 *regionid,int regionum,UINT64 deviceid);
extern int mysql_FILELAYER_deviceregionid_delete(UINT64 deviceid);
extern int mysql_FILELAYER_deviceregionid_delete_all();//x

extern int mysql_FILELAYER_disk_select(DISK *diskptr);//
extern int mysql_FILELAYER_disk_update(DISK *diskptr);
extern int mysql_FILELAYER_disk_insert(DISK *diskptr);
extern int mysql_FILELAYER_disk_delete(UINT64 diskid);
extern int mysql_FILELAYER_disk_delete_all();

extern int mysql_FILELAYER_diskregionid_select(UINT64 *regionid,UINT64 diskid);
extern int mysql_FILELAYER_diskregionid_update(UINT64 *regionid,int regionnum,UINT64 diskid);
extern int mysql_FILELAYER_diskregionid_insert(UINT64 *regionid,int regionnum,UINT64 diskid);
extern int mysql_FILELAYER_diskregionid_delete(UINT64 diskid);
extern int mysql_FILELAYER_diskregionid_delete_all();

extern int mysql_FILELAYER_filechunkid_select(UINT64 *chunkid,UINT64 fileid);
extern int mysql_FILELAYER_filechunkid_update(UINT64 *chunkid,int chunknum,UINT64 fileid);
extern int mysql_FILELAYER_filechunkid_insert(UINT64 *chunkid,int chunknum,UINT64 fileid);
extern int mysql_FILELAYER_filechunkid_delete(UINT64 fileid);
extern int mysql_FILELAYER_filechunkid_delete_all();

extern int mysql_FILELAYER_filechunkpath_select(CHUNKPATH *chunkpath,UINT64 fileid);
extern int mysql_FILELAYER_filechunkpath_update(CHUNKPATH *chunkpath,int chunknum,UINT64 fileid);
extern int mysql_FILELAYER_filechunkpath_insert(CHUNKPATH *chunkpath,int chunknum,UINT64 fileid);
extern int mysql_FILELAYER_filechunkpath_delete(UINT64 fileid);
extern int mysql_FILELAYER_filechunkpath_delete_all();

extern int mysql_FILELAYER_filedeviceid_select(UINT64 *deviceid,UINT64 fileid);
extern int mysql_FILELAYER_filedeviceid_update(UINT64 *deviceid,int devicenum,UINT64 fileid);
extern int mysql_FILELAYER_filedeviceid_insert(UINT64 *deviceid,int devicenum,UINT64 fileid);
extern int mysql_FILELAYER_filedeviceid_delete(UINT64 fileid);
extern int mysql_FILELAYER_filedeviceid_delete_all();

extern int mysql_FILELAYER_filediskid_select(UINT64 *diskid,UINT64 fileid);
extern int mysql_FILELAYER_filediskid_update(UINT64 *diskid,int disknum,UINT64 fileid);
extern int mysql_FILELAYER_filediskid_insert(UINT64 *diskid,int disknum,UINT64 fileid);
extern int mysql_FILELAYER_filediskid_delete(UINT64 fileid);
extern int mysql_FILELAYER_filediskid_delete_all();

extern int mysql_FILELAYER_filemeta_select(FILEMETA *fmetaptr);
extern int mysql_FILELAYER_filemeta_update(FILEMETA *fmetaptr);
extern int mysql_FILELAYER_filemeta_insert(FILEMETA *fmetaptr);
extern int mysql_FILELAYER_filemeta_delete(UINT64 fileid);
extern int mysql_FILELAYER_filemeta_delete_all();

extern int mysql_FILELAYER_filestripid_select(UINT64 *stripid,UINT64 fileid);
extern int mysql_FILELAYER_filestripid_update(UINT64 *stripid,int stripnum,UINT64 fileid);
extern int mysql_FILELAYER_filestripid_insert(UINT64 *stripid,int stripnum,UINT64 fileid);
extern int mysql_FILELAYER_filestripid_delete(UINT64 fileid);
extern int mysql_FILELAYER_filestripid_delete_all();

extern int mysql_FILELAYER_filestripsectid_select(UINT64 *stripsectid,UINT64 fileid);
extern int mysql_FILELAYER_filestripsectid_update(UINT64 *stripsectid,int stripsectnum,UINT64 fileid);
extern int mysql_FILELAYER_filestripsectid_insert(UINT64 *stripsectid,int stripsectnum,UINT64 fileid);
extern int mysql_FILELAYER_filestripsectid_delete(UINT64 fileid);
extern int mysql_FILELAYER_filestripsectid_all();

extern int mysql_FILELAYER_filesubfileid_select(UINT64 *subfileid,UINT64 fileid);
extern int mysql_FILELAYER_filesubfileid_update(UINT64 *subfileid,int filenum,UINT64 fileid);
extern int mysql_FILELAYER_filesubfileid_insert(UINT64 *subfileid,int filenum,UINT64 fileid);
extern int mysql_FILELAYER_filesubfileid_delete(UINT64 fileid);
extern int mysql_FILELAYER_filesubfileid_delete_all();

extern int mysql_FILELAYER_glosystemdeviceid_select(UINT64 *deviceid);
extern int mysql_FILELAYER_glosystemdeviceid_update(UINT64 *deviceid,int devicenum);
extern int mysql_FILELAYER_glosystemdeviceid_insert(UINT64 *deviceid,int devicenum);
extern int mysql_FILELAYER_glosystemdeviceid_delete_all();

extern int mysql_FILELAYER_glosystemdiskid_select(UINT64 *diskid);
extern int mysql_FILELAYER_glosystemdiskid_update(UINT64 *diskid,int disknum);
extern int mysql_FILELAYER_glosystemdiskid_insert(UINT64 *diskid,int disknum);
extern int mysql_FILELAYER_glosystemdiskid_delete_all();

extern int mysql_FILELAYER_glosystemid_select(GLOSYSTEMID *systemid);
extern int mysql_FILELAYER_glosystemid_update(GLOSYSTEMID *systemid);
extern int mysql_FILELAYER_glosystemid_insert(GLOSYSTEMID *systemid);
extern int mysql_FILELAYER_glosystemid_delete_all();

extern int mysql_FILELAYER_glosystemkindid_select(int *kindid);
extern int mysql_FILELAYER_glosystemkindid_update(int *kindid,int kindnum);
extern int mysql_FILELAYER_glosystemkindid_insert(int *kindid,int kindnum);
extern int mysql_FILELAYER_glosystemkindid_delete_all();

extern int mysql_FILELAYER_glosystemregionid_select(UINT64 *regionid);
extern int mysql_FILELAYER_glosystemregionid_update(UINT64 *regionid,int regionnum);
extern int mysql_FILELAYER_glosystemregionid_insert(UINT64 *regionid,int regionnum);
extern int mysql_FILELAYER_glosystemregionid_delete_all();

extern int mysql_FILELAYER_glosystemuserid_select(UINT64 *userid);
extern int mysql_FILELAYER_glosystemuserid_update(UINT64 *userid,int usernum);
extern int mysql_FILELAYER_glosystemuserid_insert(UINT64 *userid,int usernum);
extern int mysql_FILELAYER_glosystemuserid_delete_all();

extern int mysql_FILELAYER_region_select(REGION *regionptr);
extern int mysql_FILELAYER_region_update(REGION *regionptr);
extern int mysql_FILELAYER_region_insert(REGION *regionptr);
extern int mysql_FILELAYER_region_delete(UINT64 regionid);
extern int mysql_FILELAYER_region_delete_all();

extern int mysql_FILELAYER_regiondeviceid_select(UINT64 *deviceid,UINT64 regionid);
extern int mysql_FILELAYER_regiondeviceid_update(UINT64 *deviceid,int devicenum,UINT64 regionid);
extern int mysql_FILELAYER_regiondeviceid_insert(UINT64 *deviceid,int devicenum,UINT64 regionid);
extern int mysql_FILELAYER_regiondeviceid_delete(UINT64 regionid);
extern int mysql_FILELAYER_regiondeviceid_delete_all();

extern int mysql_FILELAYER_regiondiskid_select(UINT64 *diskid,UINT64 regionid);
extern int mysql_FILELAYER_regiondiskid_update(UINT64 *diskid,int disknum,UINT64 regionid);
extern int mysql_FILELAYER_regiondiskid_insert(UINT64 *diskid,int disknum,UINT64 regionid);
extern int mysql_FILELAYER_regiondiskid_delete(UINT64 regionid);
extern int mysql_FILELAYER_regiondiskid_delete_all();

extern int mysql_FILELAYER_regionfileid_select(UINT64 *fileid,UINT64 regionid);
extern int mysql_FILELAYER_regionfileid_update(UINT64 *fileid,int filenum,UINT64 regionid);
extern int mysql_FILELAYER_regionfileid_insert(UINT64 *fileid,int filenum,UINT64 regionid);
extern int mysql_FILELAYER_regionfileid_delete(UINT64 regionid);
extern int mysql_FILELAYER_regionfileid_delete_all();

extern int mysql_FILELAYER_regionstripid_select(UINT64 *stripid,UINT64 regionid);
extern int mysql_FILELAYER_regionstripid_update(UINT64 *stripid,int stripnum,UINT64 regionid);
extern int mysql_FILELAYER_regionstripid_insert(UINT64 *stripid,int stripnum,UINT64 regionid);
extern int mysql_FILELAYER_regionstripid_delete(UINT64 regionid);
extern int mysql_FILELAYER_regionstripid_delete_all();

extern int mysql_FILELAYER_strip_select(STRIP *stripptr);
extern int mysql_FILELAYER_strip_update(STRIP *stripptr);
extern int mysql_FILELAYER_strip_insert(STRIP *stripptr);
extern int mysql_FILELAYER_strip_delete(UINT64 stripid);
extern int mysql_FILELAYER_strip_delete_all();

extern int mysql_FILELAYER_stripchunkid_select(UINT64 *chunkid,UINT64 stripid);
extern int mysql_FILELAYER_stripchunkid_update(UINT64 *chunkid,int chunknum,UINT64 stripid);
extern int mysql_FILELAYER_stripchunkid_insert(UINT64 *chunkid,int chunknum,UINT64 stripid);
extern int mysql_FILELAYER_stripchunkid_delete(UINT64 stripid);
extern int mysql_FILELAYER_stripchunkid_delete_all();

extern int mysql_FILELAYER_stripdeviceid_select(UINT64 *deviceid,UINT64 stripid);
extern int mysql_FILELAYER_stripdeviceid_update(UINT64 *deviceid,int devicenum,UINT64 stripid);
extern int mysql_FILELAYER_stripdeviceid_insert(UINT64 *deviceid,int devicenum,UINT64 stripid);
extern int mysql_FILELAYER_stripdeviceid_delete(UINT64 stripid);
extern int mysql_FILELAYER_stripdeviceid_delete_all();

extern int mysql_FILELAYER_stripdiskid_select(UINT64 *diskid,UINT64 stripid);
extern int mysql_FILELAYER_stripdiskid_update(UINT64 *diskid,int disknum,UINT64 stripid);
extern int mysql_FILELAYER_stripdiskid_insert(UINT64 *diskid,int disknum,UINT64 stripid);
extern int mysql_FILELAYER_stripdiskid_delete(UINT64 stripid);
extern int mysql_FILELAYER_stripdiskid_delete_all();

extern int mysql_FILELAYER_stripsect_select(STRIPSECT *stripsectptr);
extern int mysql_FILELAYER_stripsect_update(STRIPSECT *stripsectptr);
extern int mysql_FILELAYER_stripsect_insert(STRIPSECT *stripsectptr);
extern int mysql_FILELAYER_stripsect_delete(UINT64 stripsectid);
extern int mysql_FILELAYER_stripsect_delete_all();

extern int mysql_FILELAYER_stripsectchunkid_select(UINT64 *chunkid,UINT64 stripsectid);
extern int mysql_FILELAYER_stripsectchunkid_update(UINT64 *chunkid,int chunknum,UINT64 stripsectid);
extern int mysql_FILELAYER_stripsectchunkid_insert(UINT64 *chunkid,int chunknum,UINT64 stripsectid);
extern int mysql_FILELAYER_stripsectchunkid_delete(UINT64 stripsectid);
extern int mysql_FILELAYER_stripsectchunkid_delete_all();

extern int mysql_FILELAYER_stripstripsectid_select(UINT64 *stripsectid,UINT64 stripid);
extern int mysql_FILELAYER_stripstripsectid_update(UINT64 *stripsectid,int stripsectnum,UINT64 stripid);
extern int mysql_FILELAYER_stripstripsectid_insert(UINT64 *stripsectid,int stripsectnum,UINT64 stripid);
extern int mysql_FILELAYER_stripstripsectid_delete(UINT64 stripid);
extern int mysql_FILELAYER_stripstripsectid_delete_all();

extern int mysql_FILELAYER_userprofile_select(USERPROFILE *userprofileptr);
extern int mysql_FILELAYER_userprofile_update(USERPROFILE *userprofileptr);
extern int mysql_FILELAYER_userprofile_insert(USERPROFILE *userprofileptr);
extern int mysql_FILELAYER_userprofile_delete(UINT64 userid);
extern int mysql_FILELAYER_userprofile_delete_all();

extern int mysql_FILELAYER_mysql_delete_all();

extern int mysql_FILELAYER_intial();
extern int mysql_FILELAYER_check_intial();//检查

extern int mysql_FILELAYER_CHUNK_READER_META(CHUNK *chk);//将CHUNK根据全局路径和chunkpath读取元数据，调用条件stripsect文件必须存在
extern int mysql_FILELAYER_STRIPSECT_READER(STRIPSECT *strset);//将STRIPSECT根据其中包含的路径读出到相应的区域
extern int mysql_FILELAYER_STRIP_READER(STRIP *str);//将STRIP根据其中包含的路径读出到相应的区域;这里需要通过region到disk中查找
extern int mysql_FILELAYER_REGION_READER(REGION *reg);//将REGION读取相应数据
extern int mysql_FILELAYER_DISK_READER(DISK *disk);//将DISK读取到相应数据
extern int mysql_FILELAYER_DEVICE_READER(DEVICE *device);//将DISK读取到相应数据
extern int mysql_FILELAYER_FILEMETA_READER(FILEMETA *fmeta);//将FILEMETA读取到相应数据//
extern int mysql_FILELAYER_USERPROFILE_READER(USERPROFILE *pfile);//将USERPROFILE读取到相应数据


extern int mysql_FILELAYER_GLOSYSTEMID_READER(GLOSYSTEMID *glosysid);//将用户信息读取到相应数据

extern int mysql_FILELAYER_CHUNKGROUP_READER_META(CHUNKGROUP *chkgroup);//将CHUNKGROUP根据其中包含的路径读取到相应的区域,元数据部分
extern int mysql_FILELAYER_STRIPSECTGROUP_READER(STRIPSECTGROUP *strsetgroup);//将STRIPSECTGROUP根据其中包含的路径读取到相应的区域
extern int mysql_FILELAYER_STRIPGROUP_READER(STRIPGROUP *strgroup);//将STRIPGROUP根据其中包含的路径读取到相应的区域;这里需要通过region到disk中查找
extern int mysql_FILELAYER_REGIONGROUP_READER(REGIONGROUP *reggroup);//将REGIONGROUP读取到相应位置
extern int mysql_FILELAYER_DISKGROUP_READER(DISKGROUP *diskgroup);//将DISKGROUP读取到相应位置
extern int mysql_FILELAYER_DEVICEGROUP_READER(DEVICEGROUP *devicegroup);//将DEVICEGROUP读取到相应位置
extern int mysql_FILELAYER_FILEMETAGROUP_READER(FILEMETAGROUP *fmetagroup);//将FILEMETAGROUP读取到相应位置
extern int mysql_FILELAYER_USERPROFILEGROUP_READER(USERGROUP *ugroup);//将USERGROUP读取相应数据


extern int mysql_FILELAYER_CHUNK_WRITER_META(CHUNK *chk);
extern int mysql_FILELAYER_STRIPSECT_READER(STRIPSECT *strset);
extern int mysql_FILELAYER_STRIPSECT_CREATE(STRIPSECT *strset);//创建一个strset组块
extern int mysql_FILELAYER_STRIPSECT_WRITER(STRIPSECT *strset);//将STRIPSECT根据其中包含的路径写入到相应的区域
extern int mysql_FILELAYER_STRIP_WRITER(STRIP *str);//将STRIPSECT根据其中包含的路径写入到相应的区域;这里需要通过region到disk中查找
extern int mysql_FILELAYER_REGION_WRITER(REGION *reg);//将region写入相应位置;这里需要通过region到disk中查找
extern int mysql_FILELAYER_DISK_WRITER(DISK *disk);//将DISK的元数据写入磁盘
extern int mysql_FILELAYER_DEVICE_WRITER(DEVICE *device);//将DEVICE的元数据写入磁盘
extern int mysql_FILELAYER_FILEMETA_WRITER(FILEMETA *fmeta);//将文件的元数据息写入磁盘
extern int mysql_FILELAYER_USERPROFILE_WRITER(USERPROFILE *pfile);//将用户信息的元数据写入磁盘
//由于全局文件只有一个无需group处理
extern int mysql_FILELAYER_GLOSYSTEMID_WRITER(GLOSYSTEMID *glosysid);//将用户信息的元数据写入磁盘


extern int mysql_FILELAYER_CHUNKGROUP_WRITER_META(CHUNKGROUP *chkgroup);//将CHUNKGROUP根据其中包含的路径写入到相应的区域,元数据部分
extern int mysql_FILELAYER_STRIPSECTGROUP_CREATE(STRIPSECTGROUP *strsetgroup);//将STRIPSECTGROUP根据内部信息在对应位置创建相应的stripsect
extern int mysql_FILELAYER_STRIPSECTGROUP_WRITER(STRIPSECTGROUP *strsetgroup);//将STRIPSECTGROUP根据其中包含的路径写入到相应的区域
extern int mysql_FILELAYER_STRIPGROUP_WRITER(STRIPGROUP *strgroup);//将STRIPGROUP根据其中包含的路径写入到相应的区域;这里需要通过region到disk中查找
extern int mysql_FILELAYER_REGIONGROUP_WRITER(REGIONGROUP *reggroup);//将REGIONGROUP写入相应数据
extern int mysql_FILELAYER_DISKGROUP_WRITER(DISKGROUP *diskgroup);//将DISKGROUP写入相应数据
extern int mysql_FILELAYER_DEVICEGROUP_WRITER(DEVICEGROUP *devicegroup);//将DEVICEGROUP写入相应数据
extern int mysql_FILELAYER_FILEMETAGROUP_WRITER(FILEMETAGROUP *fmetagroup);//将FILEMETAGROUP写入相应数据
extern int mysql_FILELAYER_USERPROFILEGROUP_WRITER(USERGROUP *ugroup);//将USERGROUP写入到相应位置