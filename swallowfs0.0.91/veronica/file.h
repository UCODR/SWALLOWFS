#ifndef _FILE_H
#define _FILE_H

#include "global_define.h"
#include "profile.h"
//filelayer
//�ײ�
extern int file_FILELAYER_intial();
//��Ӧ������·���ǲ��ǿ��Եõ�
extern int file_FILELAYER_device_available(DISK *diskptr);//���ص�ǰ�ļ�·���Ƿ�ɵ�
//�ļ��������
extern int file_FILELAYER_BYTE_READER(char *filepath,BYTESTREAM *bstream,long offset);//����������·����ƫ����λ�ö�ȡ
extern int file_FILELAYER_BYTE_WRITER(char *filepath,BYTESTREAM *bstream,long offset);//��������д���ƶ�·��ƫ��������
//�����ļ�������
extern int file_FILELAYER_BYTE_CREATE(char *filepath,BYTESTREAM *bstream);//ͨ��bstream����һ���ļ���

//region,strip,stripsect�ֿ������
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

//���ݲ��� 
//��������������Ҫ�Ǹ���id����д
//����chunk��д����������������Ҫ�������
extern int file_FILELAYER_CHUNK_READER_META(CHUNK *chk);//��CHUNK����ȫ��·����chunkpath��ȡԪ����
extern int file_FILELAYER_CHUNK_READER_DATA(CHUNK *chk);//��CHUNK�������а�����·����������Ӧ������,���ݲ��֣���������stripsect�ļ��������
extern int file_FILELAYER_STRIPSECT_READER(STRIPSECT *strset);//��STRIPSECT�������а�����·����������Ӧ������
extern int file_FILELAYER_STRIP_READER(STRIP *str);//��STRIP�������а�����·����������Ӧ������;������Ҫͨ��region��disk�в���
extern int file_FILELAYER_REGION_READER(REGION *reg);//��REGION��ȡ��Ӧ����
extern int file_FILELAYER_DISK_READER(DISK *disk);//��DISK��ȡ����Ӧ����
extern int file_FILELAYER_DEVICE_READER(DEVICE *device);//��DISK��ȡ����Ӧ����
extern int file_FILELAYER_FILEMETA_READER(FILEMETA *fmeta);//��DEVICE��ȡ����Ӧ����
extern int file_FILELAYER_USERPROFILE_READER(USERPROFILE *pfile);//��USERPROFILE��ȡ����Ӧ����
//����ȫ���ļ�ֻ��һ������group����
extern int file_FILELAYER_GLOSYSTEMID_READER(GLOSYSTEMID *glosysid);//���û���Ϣ��ȡ����Ӧ����

//����ȡ

extern int file_FILELAYER_CHUNKGROUP_READER_META(CHUNKGROUP *chkgroup);//��CHUNKGROUP�������а�����·����ȡ����Ӧ������,Ԫ���ݲ���
extern int file_FILELAYER_CHUNKGROUP_READER_DATA(CHUNKGROUP *chkgroup);//��CHUNKGROUP�������а�����·����ȡ����Ӧ������,���ݲ���
extern int file_FILELAYER_STRIPSECTGROUP_READER(STRIPSECTGROUP *strsetgroup);//��STRIPSECTGROUP�������а�����·����ȡ����Ӧ������
extern int file_FILELAYER_STRIPGROUP_READER(STRIPGROUP *strgroup);//��STRIPGROUP�������а�����·����ȡ����Ӧ������;������Ҫͨ��region��disk�в���
extern int file_FILELAYER_REGIONGROUP_READER(REGIONGROUP *reggroup);//��REGIONGROUP��ȡ����Ӧλ��
extern int file_FILELAYER_DISKGROUP_READER(DISKGROUP *diskgroup);//��DISKGROUP��ȡ����Ӧλ��
extern int file_FILELAYER_DEVICEGROUP_READER(DEVICEGROUP *devicegroup);//��DEVICEGROUP��ȡ����Ӧλ��
extern int file_FILELAYER_FILEMETAGROUP_READER(FILEMETAGROUP *fmetagroup);//��FILEMETAGROUP��ȡ����Ӧλ��
extern int file_FILELAYER_USERPROFILEGROUP_READER(USERGROUP *ugroup);//��USERGROUP��ȡ��Ӧ����

//����д����,д�����
extern int file_FILELAYER_CHUNK_WRITER_META(CHUNK *chk);//��CHUNK�������а�����·��д�뵽��Ӧ������,Ԫ���ݲ���
extern int file_FILELAYER_CHUNK_WRITER_DATA(CHUNK *chk);//��CHUNK�������а�����·��д�뵽��Ӧ������,���ݲ���
extern int file_FILELAYER_STRIPSECT_CREATE(STRIPSECT *strset);//����һ��strset���
extern int file_FILELAYER_STRIPSECT_WRITER(STRIPSECT *strset);//��STRIPSECT�������а�����·��д�뵽��Ӧ������
extern int file_FILELAYER_STRIP_WRITER(STRIP *str);//��STRIPSECT�������а�����·��д�뵽��Ӧ������;������Ҫͨ��region��disk�в���
extern int file_FILELAYER_REGION_WRITER(REGION *reg);//��regionд����Ӧλ��;������Ҫͨ��region��disk�в���
extern int file_FILELAYER_DISK_WRITER(DISK *disk);//��DISK��Ԫ����д�����
extern int file_FILELAYER_DEVICE_WRITER(DEVICE *device);//��DEVICE��Ԫ����д�����
extern int file_FILELAYER_FILEMETA_WRITER(FILEMETA *fmeta);//���ļ���Ԫ����Ϣд�����
extern int file_FILELAYER_USERPROFILE_WRITER(USERPROFILE *pfile);//���û���Ϣ��Ԫ����д�����
extern int file_FILELAYER_SHARE_WRITER(AONTSHARE *share);
//����ȫ���ļ�ֻ��һ������group����
extern int file_FILELAYER_GLOSYSTEMID_WRITER(GLOSYSTEMID *glosysid);//���û���Ϣ��Ԫ����д�����

//���д��,д�����
extern int file_FILELAYER_CHUNKGROUP_WRITER_META(CHUNKGROUP *chkgroup);//��CHUNKGROUP�������а�����·��д�뵽��Ӧ������,Ԫ���ݲ���
extern int file_FILELAYER_CHUNKGROUP_WRITER_DATA(CHUNKGROUP *chkgroup);//��CHUNKGROUP�������а�����·��д�뵽��Ӧ������,���ݲ���
extern int file_FILELAYER_STRIPSECTGROUP_CREATE(STRIPSECTGROUP *strsetgroup);//��STRIPSECTGROUP�����ڲ���Ϣ�ڶ�Ӧλ�ô�����Ӧ��stripsect
extern int file_FILELAYER_STRIPSECTGROUP_WRITER(STRIPSECTGROUP *strsetgroup);//��STRIPSECTGROUP�������а�����·��д�뵽��Ӧ������
extern int file_FILELAYER_STRIPGROUP_WRITER(STRIPGROUP *strgroup);//��STRIPGROUP�������а�����·��д�뵽��Ӧ������;������Ҫͨ��region��disk�в���
extern int file_FILELAYER_REGIONGROUP_WRITER(REGIONGROUP *reggroup);//��REGIONGROUPд����Ӧ����
extern int file_FILELAYER_DISKGROUP_WRITER(DISKGROUP *diskgroup);//��DISKGROUPд����Ӧ����
extern int file_FILELAYER_DEVICEGROUP_WRITER(DEVICEGROUP *devicegroup);//��DEVICEGROUPд����Ӧ����
extern int file_FILELAYER_FILEMETAGROUP_WRITER(FILEMETAGROUP *fmetagroup);//��FILEMETAGROUPд����Ӧ����
extern int file_FILELAYER_USERPROFILEGROUP_WRITER(USERGROUP *ugroup);//��USERGROUPд�뵽��Ӧλ��

//�ж��ļ���״̬
extern int file_FILELAYER_dictionary_exists(char *dicpath);
extern int file_FILELAYER_dictionary_region_exists(UINT64 regionid);
extern int file_FILELAYER_dictionary_strip_exists(UINT64 regionid,UINT64 stripid);
extern int file_FILELAYER_dictionary_stripsect_exists(UINT64 regionid,UINT64 stripid,UINT64 strsetid);
extern int file_FILELAYER_dictionary_filemeta_exists(UINT64 regionid,UINT64 fileid);
extern int file_FILELAYER_dictionary_userprofile_exists(UINT64 userid);
extern int file_FILELAYER_dictionary_device_exists(UINT64 deviceid);
extern int file_FILELAYER_dictionary_disk_exists(UINT64 deviceid,UINT64 diskid);

//��������
extern long file_FILELAYER_get_filesize(FILE *fp);//��ȡ�ļ���ȡ�ļ���С��ָ�����ļ�����

//д������ݽӿ�APIͨ��pushlist�������Ƿ���ʱд
extern int file_chunk_write_API(CHUNK *chunkptr);//��Ҫͬ�����ݵ�ָ��

//����64λ��ת�ַ���
#define U64toSTR(str,a64) sprintf(str,"%I64d",a64)//������ת��Ϊ�ַ���
//#define REGIONSTR(regname,regid) strcat(strcat(strcat(regname,"region")regid),"/")//������Ӧ�������ַ���
//#define STRIPSTR(strname,strid) strcat(strcat(strcat(strname,"strip"),strid),"/")//������Ӧ�������ַ���
//ʹ������飬����Ԫ���������ļ����������룬���ʹ��.txt��Ϊ��չ��
//#define STRIPSECTSTR(strsetname,strsetid) strcat(strcat(strcat(strsetname,"stripsect"),strsetid),".txt")//������Ӧ�����������ַ���
//#define CHUNKSTR(chkname,chkid) strcat(strcat(strcat(chkname,"chunk"),chkid),".txt")//������Ӧ�����������ַ���
//��ǰ�ļ�Ԫ����
//#define FILEMETASTR(filename,filemetaid) strcat(strcat(strcat(fname,)))
#endif