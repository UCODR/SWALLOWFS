#ifndef SYSTEM_COM_H
#define SYSTEM_COM_H
#include "global_define.h"
#include "galois.h"
#include "matrix.h"
#include "file.h"
#include "profile.h"
#include "encoder.h"
#include "decoder.h"
//不找完成相应的系统级命令
//需要时完成系统级调用API
extern int systemcom_REGION_create(REGION *regionptr);//创建一个区域
extern int systemcom_REGION_delete_ptr(REGION *regionptr);//通过ptr删除region
extern int systemcom_REGION_delete_id(UINT64 regionid);//通过id删除region

//系统状态更新
//同步device
extern int systemcom_DEVICE_create(DEVICE *deviceptr);//创建一个device
extern int systemcom_DEVICE_delete_ptr(DEVICE *deviceptr);//删除一个device
extern int systemcom_DEVICE_delete_ID(UINT64 deviceid);//删除一个device

//同步disk
extern int systemcom_DISK_create(DISK *diskptr);//创建一个disk
extern int systemcom_DISK_delete_PTR(DISK *diskptr);//删除一个disk
extern int systemcom_DISK_delete_ID(UINT64 diskid);//删除一个disk 

//用户指令
extern int systemcom_USER_create(USERPROFILE *userptr);//创建相应用户
extern int systemcom_USER_delete_PTR(USERPROFILE *userptr);//删除系统用户
extern int systemcom_USER_delete_ID(UINT64 userid);//删除系统用户


//文件基本操作
extern FILEMETA *systemcom_FILE_create_handle(char *filepath);//文件创建
extern int systemcom_FILE_delete(FILEMETA *fmeta);//文件删除
extern int systemcom_FILE_read(FILEMETA *fmeta,BYTESTREAM *bstream);//文件读取
extern int systemcom_FILE_write_overwrite(FILEMETA *fmeta,BYTESTREAM *bstream);//文件覆盖写相当于"w"
extern int systemcom_FILE_write_change(FILEMETA *fmeta,BYTESTREAM *bstream,int offset);//文化部非
extern int systemcom_FILE_append(FILEMETA *fmeta,BYTESTREAM *bstream);//文件添加
extern int systemcom_FILE_duplicate(FILEMETA *soufmeta,FILEMETA *desfmeta);//文件从一个区域拷贝到另一路径
//属性修改
extern int systemcom_FILE_ACLMOD(int ACList);//更新当前文件的


//目录指令
extern int systemcom_DICT_DIR(char *dictpath);//显示一个目录
extern int systemcom_DICT_DIR_rootuser();//显示用户当前目录内容
extern int systemcom_DICT_create(char *dictpath);//系统目录创建
extern int systemcom_DICT_delete(char *dictpath);//系统目录删除
extern int systemcom_DICT_access(char *dictpath);//判断一个目录是否存在

//系统状态更新，报告
//系统状态报告
extern int systemcom_userstate_report();//汇报用户状态
extern int systemcom_diskstate_report();//汇报磁盘状态
extern int systemcom_devicestate_report();//汇报设备状态
extern int systemcom_regionstate_report();//汇报区域状态


//系统初始化
extern int systemcom_system_inital();//系统初始化,根据元数据地址初始化
extern int systemcom_system_format();//系统格式化,根据region信息进行format操作
extern int systemcom_system_reset_format();//慎用将系统恢复到白纸状态


//同步数据
extern int systemcom_metadata_sync();//同步元数据
extern int systemcom_chunkdata_sync();//同步chunk数据

//更改push信息指令
extern int systemcom_push_time(int pushtime,int maxbuffersize);
int systemcom_push_time(int pushtime,int maxbuffersize);//更改push信息指令
#endif