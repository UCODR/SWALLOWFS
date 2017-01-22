#ifndef _PROFILE_H
#define _PROFILE_H
#include "file.h"
#include "FILELAYER.h"
#include "global_define.h"
#include "matrix.h"
//updateelemnent中chunkptr
extern int profile_updateelement_updatelist_countnum(int *updatelist,int updatenum);
extern CHUNK *profile_updateelement_chunk_ptr(UPDATEELEMENT *updateelementptr);
extern CHUNK *profile_updateelement_temp_chunk_ptr(UPDATEELEMENT *updateelementptr);
//判断当前updateelement数据
extern int profile_updateelement_bitelement_equal(UPDATEELEMENT *updateelementptr,BITELEMENT *bitelementptr);
extern int profile_updateelement_updateelement_equal(UPDATEELEMENT *tarupdateelementptr,UPDATEELEMENT *souupdateelementptr);

extern UPDATEELEMENT *profile_updateelement_search_ptr(UPDATEELEMENTGROUP *updateelementgroupptr,int stripsectindex,int chunkindex);//计算出当前的updateelement
extern int profile_updateelement_is_exist(UPDATEELEMENTGROUP *updateelementgroupptr,int stripsectindex,int chunkindex); //判断一个元素在不在updateelement组中

//bitelemet和updateelement之间的距离
extern int profile_matrix1_matrix2_update_distance(BITMATRIX *matrix1,BITMATRIX *matrix2,BITMATRIX *readmapmatrix);

extern int profile_updateelement_updatelement_updateI_distance(UPDATEELEMENT *tarupdateelement,UPDATEELEMENT *souupdateelement,BITMATRIX *readmapmatrix);
extern int profile_updateelement_updatelement_updateII_distance(UPDATEELEMENT *tarupdateelement,UPDATEELEMENT *souupdateelement,BITMATRIX *readmapmatrix);
extern int profile_updateelement_updatelement_distance(UPDATEELEMENT *tarupdateelement,UPDATEELEMENT *souupdateelement,BITMATRIX *readmapmatrix);//返回两个updateelement的距离，其中souupdateelement为源模式，计算与当前结果距离

extern int profile_updateelememt_bitelement_updateI_distance(UPDATEELEMENT *tarupdateelement,BITELEMENT *soubitelement,BITMATRIX *readmapmatrix);//返回updateelement的距离
extern int profile_updateelememt_bitelement_updateII_distance(UPDATEELEMENT *tarupdateelement,BITELEMENT *soubitelement,BITMATRIX *readmapmatrix);//返回updateelement的距离
extern int profile_updateelememt_bitelement_distance(UPDATEELEMENT *tarupdateelement,BITELEMENT *soubitelement,BITMATRIX *readmapmatrix);//返回updateelement的距离
//计算当前内存地图
extern int profile_memory_map_is_exist(BITMATRIX *readmapmatrixptr,int stripsectindex,int chunkindex);//判断一个元素在不在内存地图内
extern int profile_memory_map_add_element(BITMATRIX *readmapmatrixptr,int stripsectindex,int chunkindex);//想内存地图中加入一个元素

//计算时间间隙
extern double profile_calculate_time_diff(long starttick,long endtick);//返回sec描述
//生成全局element,其中rowsindex，colsindex是指在read map中的位置
extern int profile_bitelement_dataelement(int stripsectindex,int chunkindex,BITELEMENT *bitelementptr,BITMATRIX *matrix,REGION *regionptr);//生成相应的数据块模式
extern int profile_bitelement_codeelement(int stripsectindex,int chunkindex,BITELEMENT *bitelementptr,BITMATRIX *matrix,REGION *regionptr);//将数据中一行进行拷贝

//生成全局错误模式
extern int profile_create_global_errorpattern(ERRORPATTERN *errormatrix);
extern int profile_set_disk_available_state();
extern int profile_create_global_errorpattern_global_errorpattern(ERRORPATTERN *errormatrix);
//产生人工错误
extern int profile_set_global_disk_error(ERRORPATTERN *errormatrix);

//生成相应的地图//其中countnum代笔1,0的数量
extern int profile_create_memory_map(BITMATRIX *matrix,STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
									STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,int *countnum,REGION *regionptr);
extern int profile_create_memory_map_RAID6(BITMATRIX *matrix,STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
									STRIPSECT *pparity,STRIPSECT *qparity,int *countnum,REGION *regionptr);

//分割函数
extern int profile_strip_into_stripsect_ptr(STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,STRIP *stripptr);

//判断一个数是不是素数
extern int profile_is_prime(int w);//判断当前的数据是不是素数
extern int profile_next_prime(int datanum);//获取之后的以第一个素数
//找数据找出当前chunk的位置
extern int profile_chunk_to_chunkposition_ptr(CHUNKPOSITIONBLOCK *chunkpositionblockptr,CHUNK *chunkptr);//通过指针来判断位置
//块处理函数
extern int profile_chunk_should_read(CHUNK *chunkptr);//判断一个chunk如果要读取是不是需要从硬盘读
extern int profile_chunk_create_empty_data(CHUNK *chunkptr);//创建一个空块
extern int profile_chunk_data_read(CHUNK *chunkptr);//如果数据不在内存将chunkdata同步数据到内存，如果没有写创建一个空块

//判断一个chunk是否为为空
extern int profile_chunk_data_haswrited(CHUNK *chunkptr);
extern int profile_chunk_data_isfree(CHUNK *chunkptr);
//创建一个除REGION
extern int profile_region_setup_without_filemeta(REGION *regionptr,int codetype,CODEPARA *codepara,STRIPDES *strdes,UINT64 totalsize,
										UINT64 *glodeviceidlist,DEVICEBLOCK *glodeviceblockptr,int devicenum,
										UINT64 *glodiskidlist,DISKBLOCK *glodiskblockptr,int disknum);//创建region并且进行格式化
extern int profile_region_setup_rootdictionary_filemeta(FILEMETA *rootdicptr,char *filename,USERPROFILE *userprofileptr,REGION *regionptr);//创建相应的rootdictionary
extern int profile_region_setup(REGION *regionptr,int codetype,CODEPARA *codepara,STRIPDES *strdes,UINT64 totalsize,
								UINT64 *glodeviceidlist,DEVICEBLOCK *glodeviceblockptr,int devicenum,
								UINT64 *glodiskidlist,DISKBLOCK *glodiskblockptr,int disknum,
								char *filename,USERPROFILE *userprofileptr);//计算当前的数据

//计算上下界偏移量
extern int profile_update_startoffset(int chunksize,int offset);//计算firstoffset
extern int profile_update_lastoffset(int chunksize,int offset,int updatesize);//计算lastoffset

//释放空间
extern int profile_free_chunk_data(CHUNK *chunkptr);
extern int profile_free_chunkgroup_data(CHUNKGROUP *chunkgroupptr);
extern int profile_free_chunkblockgroup_data(CHUNKBLOCKGROUP *chunkblockgroupptr);
extern int profile_free_chunkpositionblockgroup_data(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgrouipptr);

extern int profile_tempfree_chunk_ptr(CHUNK *chunkptr);//将数据块记录到tempreelist
extern int profile_tempfree_chunkblock_ptr(CHUNKBLOCKGROUP *chunkblockgroupptr);//将数据块组记录到tempfreelist
extern int profile_tempfree_free();//释放当前的free列表

//计算函数
extern int profile_mod_number(int m,int n);//除余数(带负数)（m mod n）

//主要需要初始化的参数,显示不同信息
extern int profile_chkpath_to_chunk_stripsectnum(CHUNKPATH *chkpathptr);//当前chunk所在stripsec中的位置
extern int profile_chkpath_to_chunk_stripnum(CHUNKPATH *chkpathptr);//当前chunk所在stripsec中的位置
extern int profile_chkpath_to_chunk_regionnum(CHUNKPATH *chkpathptr);//当前chunk所在stripsec中的位置

extern int profile_chkpath_to_stripsect_stripnum(CHUNKPATH *chkpathptr);//当前chunk所在的stripsect在strip中的位置
extern int profile_chkpath_to_stripsect_regionnum(CHUNKPATH *chkpathptr);//当前chunk所在的stripsect在region中的位置

extern int profile_chkpath_to_strip_regionnum(CHUNKPATH *chkpathptr);//当前chunk所在的strip在region中的位置

//转化函数
extern int profile_stripblock_to_datachunkblock(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr);//将当前的数据中的data chunk进行提取
extern int profile_stripblock_to_paritychunkblock(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr);//将当前的数据中的parity datachunk进行提取
extern int profile_chunkblock_to_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr);//找出chunkblock对应的stripblock

//加入指针
extern int profile_chunkblockpositiongroup_from_chunkblockpositiongroup_search_ptr(CHUNKPOSITIONBLOCKGROUP *tarchunkblockpositiongroupptr,
																		CHUNKPOSITIONBLOCKGROUP *souchunkpositionblockgroupptr,
																		STRIP *stripptr);//在chunkpositionblockgroup找到对应strip的chunk并且进行填写，返回TRUE和FALSE

extern int profile_chunkblockstripgroup_search_ptr(CHUNKBLOCKSTRIPGROUP *chunkblockstripgroupptr,STRIP *stripptr);//找到相应的strip的数据
extern int profile_stripblockgroup_search_ptr(STRIPBLOCKGROUP *stripblockgroupptr,STRIP *stripptr);//找stripptr的指针数据位置，没找到返回-1
extern int profile_stripsectblockgroup_search_ptr(STRIPSECTBLOCKGROUP *stripsetblockgroupptr,STRIPSECT *stripsectptr);//找stripptr的指针数据位置，没找到返回-1
extern int profile_chunkblockgroup_search_ptr(CHUNKBLOCKGROUP *chunkblockgroupptr,CHUNK *chunkptr);//找chunkptr的指针数据位置，没找到返回-1

extern int profile_region_filemeta_add(REGION *regionptr,FILEMETA *filemetaptr);
//下面三个函数使用前需要预先分配空间
extern int profile_stripblockstripgroup_chunk_add(CHUNKBLOCKSTRIPGROUP *chunkblockstripgroupptr,CHUNK *chunkptr,STRIP *stripptr);//计算当前
extern int profile_stripblockgroup_strip_add(STRIPBLOCKGROUP *stripblockgroupptr,STRIP *stripptr);//在stripblockgroupptr中加入一个strip
extern int profile_stripsetblockgroup_stripsect_add(STRIPSECTBLOCKGROUP *stripsectblockgrouptr,STRIPSECT *stripsectptr); //在stripsectblockgroupptr中加入一个stripsect
extern int profile_chunkblockgroup_chunk_add(CHUNKBLOCKGROUP *chunkblockgroupptr,CHUNK *chunkptr);//在chunkblockgroupptr中加入一个chunk

//将存储信息进行设置
extern int profile_set_file_storage_information(FILEINF *fileinfptr,
												CHUNKBLOCKGROUP *chunkblockgroupptr,STRIPSECTBLOCKGROUP *stripsectblockgroupptr,
												STRIPBLOCKGROUP *stripblockgroupptr,REGION *regionptr,
												CHUNKPATH *chunkpathlist,FILEMETA *filemetaptr
												);
//计算文件与上一级指针
extern int profile_set_parent_filemeta_ptr(FILEMETA *filemetaptr);

//搜索函数,将数据从全局列表中找出指针

extern int profile_filemeta_filemetablock_search(FILEMETABLOCK *filemetablockptr,UINT64 *fileidlist,int filenum,FILEMETABLOCKGROUP *filemetablockgroupptr);

extern int profile_chunk_chunkpath_search(CHUNKBLOCK *chunkblockptr,UINT64 *chunkidlist,CHUNKPATH *chkpathptr,int chunknum);
extern int profile_stripsect_chunkpath_search(STRIPSECTBLOCK *stripsectblockptr,UINT64 *stripsectidlist,int stripsectnum,CHUNKPATH *chkpathptr,int chunknum);
extern int profile_strip_chunkpath_search(STRIPBLOCK *stripblockptr,UINT64 *stripidlist,int stripnum,CHUNKPATH *chkpathptr,int chunknum);

extern USERPROFILE *profile_get_usergroup_ptr(UINT64 userid,USERGROUP *usergroupptr);

extern FILEMETA *profile_get_filemetablock_ptr(UINT64 fileid,FILEMETABLOCKGROUP *filemetablockgroupptr);//找到对应的filemeta



extern CHUNK *profile_get_chunkblock_ptr(UINT64 chunkid,CHUNKBLOCKGROUP *chunkblockgroupptr);//找到相应chunk
extern CHUNK *profile_get_chunkposition_ptr(int stripsectindex,int chunkindex,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr);//找出当前stripsectnum和chunknum的指针
extern int profile_search_chunkposition_id(int stripsectindex,int chunkindex,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr);//找出当前stripsectnum和chunknum的编号
extern UINT64 profile_get_region_id(char *filepath);//生成id号
extern REGION *profile_region_search_ptr(UINT64 regionid);//查找当前regionid的REGION指针

extern int profile_device_search(DEVICEBLOCK *deviceblockptr,UINT64 *deviceidlist,int devicenum);//找到当前id列表中device指针
extern int profile_disk_search(DISKBLOCK *diskblockptr,UINT64 *diskidlsit,int disknum);//找到当前id列表中的disk指针
extern int profile_region_search(REGION *regionptr);//返回region号
extern DEVICE *profile_device_ptr_search(UINT64 deviceid,DEVICEBLOCK *deviceblockptr,int devicenum);//找到当前列表中deviceid
extern DISK *profile_disk_ptr_search(UINT64 diskid,DISKBLOCK *diskblockptr,int disknum);//找到当前列表中deviceid


//显示实体数据
extern int profile_region_info_ID(UINT64 regionid);//根据regionid显示数据
extern int profile_region_info(REGION *regionptr);//根据region指针显示数据
extern int profile_strip_info(STRIP *stripptr);//根据strip指针显示数据
extern int profile_stripsect_info(STRIPSECT *stripsectptr);//根据stripsect指针显示数据
extern int profile_chunk_info(CHUNK *chunkptr);//根据chunk指针显示数据
extern int profile_disk_info(DISK *diskptr);//根据disk指针显示数据
extern int profile_device_info(DEVICE *deviceptr);//根据device指针显示数据
extern int profile_filemeta_info(FILEMETA *filemetaptr);//根据filemeta指针显示数据
extern int profile_userprofile_info(USERPROFILE *useprofileptr);//根据useprofile指针显示数据

extern int profile_global_define_reader();//将全局定义数据读入

extern int profile_region_reader();//获取全局区域元数据
extern int profile_userprofile_reader();//获取全局用户信息
extern int profile_device_reader();//获取设备元数据
extern int profile_disk_reader();//获取存储器元数据
extern int profile_dirtydata_intial();//初始化dirtydata数据组
//这个函数较为特殊
extern int profile_map_define_intial(REGION *regionptr);//根据region中的raid定义来分配修改相应的校验信息


extern int profile_device_disk_setup(DEVICE *deviceptr,DISK *diskptr,int index);//建立device以及disk指针关系

extern int profile_region_format_PTR(REGION *regionptr);//格式化region指针数据
extern int profile_region_reader_PTR(REGION *regionptr);//读取当前region数据


extern int profile_chunk_fileinf(CHUNKBLOCK *chunkblockptr,FILEMETA *filemetaptr,int chunknum);

extern int profile_setup_file_fullchkpath(CHUNKPATH *chkpathptr,REGION *regionptr);

extern int profile_setup_parent_subfile_relation(FILEMETA *parentptr,FILEMETABLOCK *subfileblockptr,int subfilenum);
extern int profile_setup_file_dictionaryinformation(FILEMETA *filemetaptr,FILEMETABLOCKGROUP *filemetablockgroupptr);
extern int profile_setup_file_chunkinformation(FILEMETA *filemetaptr);
extern int profile_setup_file_diskinformation(FILEMETA *filemetaptr);
extern int profile_setup_file_deviceinformation(FILEMETA *filemetaptr);
extern int profile_setup_file_userinformation(FILEMETA *filemetaptr);
extern int profile_setup_file_storeinformation(FILEMETA *filemetaptr);//将当前的
extern int profile_region_read_filemeta(REGION *regionptr);//根据元数据文件夹中文件信息设置，文件系统逻辑结构
//主要分成三个部分1.设定全局元数据路径2.设置全局文件结构3.设置全局的块结构
//初始化region系统参数
extern int profile_global_system_intial_basic();//初始化基本数据
extern int profile_global_region_intial(REGION *regionptr);//通过regionptr的数据初始化
extern int profile_global_region_intial_without_datafile(REGION *regionptr);//通过regionptr的数据初始化
extern int profile_global_system_intial();//初始化全局接口
extern int profile_global_system_intial_without_datafile();//初始化全局接口

extern int profile_set_global_metapath(char *filename);//从当前目录中文件读出元数据文件夹位置


extern int profile_globaldefine_sync();//gloabl-define同步
extern int profile_region_sync(REGION *regionptr);//region结构元数据同步到磁盘 
extern int profile_filemeta_sync(REGION *regionptr);//将文件元数据同步
extern int profile_device_disk_sync();//将device和disk元数据同步到磁盘
extern int profile_userprofile_sync();//用户信息同步到
extern int profile_GLOBAL_chunk_data_sync();//根据元数据文件中的chunk中数据

extern int profile_metadata_sync();//元数据同步

//设置脏数据列表
extern int profile_dirtydata_set_data(CHUNKBLOCK *chunkblockptr,int chunknum,//chunk数据
										STRIPSECTBLOCK *stripsectblockptr,int stripsectnum,//stripsect数据
										STRIPBLOCK *stripblockptr,int stripnum,//strip数据
										REGIONBLOCK *regionblockptr,int regionnum,//region数据
										FILEMETABLOCK *filemetablockptr,int filemtetanum,//file数据
										DEVICEBLOCK *deviceblockptr,int devicenum,//device数据
										DISKBLOCK *diskblockptr,int disknum,//disk数据
										USERBLOCK *userblockptr,int usernum//user数据
										);//设定全局脏数据

//8个脏数据同步函数
extern int profile_dirtydata_region_sync();//region脏数据同步
extern int profile_dirtydata_strip_sync();//strip脏数据同步
extern int profile_dirtydata_stripsect_sync();//stripsect脏数据同步
extern int profile_dirtydata_chunk_sync();//chunk脏数据同步
extern int profile_dirtydata_device_sync();//device脏数据同步
extern int profile_dirtydata_disk_sync();//disk脏数据同步
extern int profile_dirtydata_userprofile_sync();//userprofile脏数据同步
extern int profile_dirtydata_filemeta_sync();//filemeta脏数据同步

extern int profile_dirtydata_sync();//总体脏数据同步


extern int profile_update_allocate_chunkstate(CHUNKPATH *chkpath);//分配更新chunkstate
extern int profile_update_free_chunkstate(CHUNKPATH *chkpath);//释放更新chunkstate

extern CHUNKPATH *profile_allocate_chunk_data(REGION *regionptr);//块分配算法,给出相应的块路径
extern int profile_free_chunk_ptr(CHUNKPATH *chkpath);//释放一个块

extern int profile_setup_file_ptr(FILEMETA *perantptr,FILEMETA *curfileptr);//建立相应的的指针
extern int profile_add_file_to_region(FILEMETA *perantptr,FILEMETA *curfileptr,REGION *regiomptr);//将一个原始region中没有的文件加入region中，并且建立相应与perant的指针
extern int profile_add_file_chunkblock_to_region(FILEMETA *perantptr,FILEMETA *curfileptr,CHUNKBLOCKGROUP *chunkblockgroupptr,REGION *regionptr);//将一个原始region中没有的文件加入region中，并且建立相应与perant的指针，建立与chunkblockgroup之间的关系
#endif