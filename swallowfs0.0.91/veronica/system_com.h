#ifndef SYSTEM_COM_H
#define SYSTEM_COM_H
#include "global_define.h"
#include "galois.h"
#include "matrix.h"
#include "file.h"
#include "profile.h"
#include "encoder.h"
#include "decoder.h"
//���������Ӧ��ϵͳ������
//��Ҫʱ���ϵͳ������API
extern int systemcom_REGION_create(REGION *regionptr);//����һ������
extern int systemcom_REGION_delete_ptr(REGION *regionptr);//ͨ��ptrɾ��region
extern int systemcom_REGION_delete_id(UINT64 regionid);//ͨ��idɾ��region

//ϵͳ״̬����
//ͬ��device
extern int systemcom_DEVICE_create(DEVICE *deviceptr);//����һ��device
extern int systemcom_DEVICE_delete_ptr(DEVICE *deviceptr);//ɾ��һ��device
extern int systemcom_DEVICE_delete_ID(UINT64 deviceid);//ɾ��һ��device

//ͬ��disk
extern int systemcom_DISK_create(DISK *diskptr);//����һ��disk
extern int systemcom_DISK_delete_PTR(DISK *diskptr);//ɾ��һ��disk
extern int systemcom_DISK_delete_ID(UINT64 diskid);//ɾ��һ��disk 

//�û�ָ��
extern int systemcom_USER_create(USERPROFILE *userptr);//������Ӧ�û�
extern int systemcom_USER_delete_PTR(USERPROFILE *userptr);//ɾ��ϵͳ�û�
extern int systemcom_USER_delete_ID(UINT64 userid);//ɾ��ϵͳ�û�


//�ļ���������
extern FILEMETA *systemcom_FILE_create_handle(char *filepath);//�ļ�����
extern int systemcom_FILE_delete(FILEMETA *fmeta);//�ļ�ɾ��
extern int systemcom_FILE_read(FILEMETA *fmeta,BYTESTREAM *bstream);//�ļ���ȡ
extern int systemcom_FILE_write_overwrite(FILEMETA *fmeta,BYTESTREAM *bstream);//�ļ�����д�൱��"w"
extern int systemcom_FILE_write_change(FILEMETA *fmeta,BYTESTREAM *bstream,int offset);//�Ļ�����
extern int systemcom_FILE_append(FILEMETA *fmeta,BYTESTREAM *bstream);//�ļ����
extern int systemcom_FILE_duplicate(FILEMETA *soufmeta,FILEMETA *desfmeta);//�ļ���һ�����򿽱�����һ·��
//�����޸�
extern int systemcom_FILE_ACLMOD(int ACList);//���µ�ǰ�ļ���


//Ŀ¼ָ��
extern int systemcom_DICT_DIR(char *dictpath);//��ʾһ��Ŀ¼
extern int systemcom_DICT_DIR_rootuser();//��ʾ�û���ǰĿ¼����
extern int systemcom_DICT_create(char *dictpath);//ϵͳĿ¼����
extern int systemcom_DICT_delete(char *dictpath);//ϵͳĿ¼ɾ��
extern int systemcom_DICT_access(char *dictpath);//�ж�һ��Ŀ¼�Ƿ����

//ϵͳ״̬���£�����
//ϵͳ״̬����
extern int systemcom_userstate_report();//�㱨�û�״̬
extern int systemcom_diskstate_report();//�㱨����״̬
extern int systemcom_devicestate_report();//�㱨�豸״̬
extern int systemcom_regionstate_report();//�㱨����״̬


//ϵͳ��ʼ��
extern int systemcom_system_inital();//ϵͳ��ʼ��,����Ԫ���ݵ�ַ��ʼ��
extern int systemcom_system_format();//ϵͳ��ʽ��,����region��Ϣ����format����
extern int systemcom_system_reset_format();//���ý�ϵͳ�ָ�����ֽ״̬


//ͬ������
extern int systemcom_metadata_sync();//ͬ��Ԫ����
extern int systemcom_chunkdata_sync();//ͬ��chunk����

//����push��Ϣָ��
extern int systemcom_push_time(int pushtime,int maxbuffersize);
int systemcom_push_time(int pushtime,int maxbuffersize);//����push��Ϣָ��
#endif