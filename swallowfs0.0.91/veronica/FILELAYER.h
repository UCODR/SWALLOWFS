#include "global_define.h"
#include "mysql.h"
#include "file.h"
//���ݾ�ȫ�ֶ�����������Ǹ��ӿں�������
//���Խ���file�����н���access
extern int FILELAYER_intial();

extern int FILELAYER_CHUNK_READER_META(CHUNK *chk);//��CHUNK����ȫ��·����chunkpath��ȡԪ����
extern int FILELAYER_CHUNK_READER_DATA(CHUNK *chk);//��CHUNK�������а�����·����������Ӧ������,���ݲ��֣���������stripsect�ļ��������
extern int FILELAYER_STRIPSECT_READER(STRIPSECT *strset);//��STRIPSECT�������а�����·����������Ӧ������
extern int FILELAYER_STRIP_READER(STRIP *str);//��STRIP�������а�����·����������Ӧ������;������Ҫͨ��region��disk�в���
extern int FILELAYER_REGION_READER(REGION *reg);//��REGION��ȡ��Ӧ����
extern int FILELAYER_DISK_READER(DISK *disk);//��DISK��ȡ����Ӧ����
extern int FILELAYER_DEVICE_READER(DEVICE *device);//��DISK��ȡ����Ӧ����
extern int FILELAYER_FILEMETA_READER(FILEMETA *fmeta);//��DEVICE��ȡ����Ӧ����
extern int FILELAYER_USERPROFILE_READER(USERPROFILE *pfile);//��USERPROFILE��ȡ����Ӧ����


extern int FILELAYER_GLOSYSTEMID_READER(GLOSYSTEMID *glosysid);//���û���Ϣ��ȡ����Ӧ����

extern int FILELAYER_CHUNKGROUP_READER_META(CHUNKGROUP *chkgroup);//��CHUNKGROUP�������а�����·����ȡ����Ӧ������,Ԫ���ݲ���
extern int FILELAYER_CHUNKGROUP_READER_DATA(CHUNKGROUP *chkgroup);//��CHUNKGROUP�������а�����·����ȡ����Ӧ������,���ݲ���
extern int FILELAYER_STRIPSECTGROUP_READER(STRIPSECTGROUP *strsetgroup);//��STRIPSECTGROUP�������а�����·����ȡ����Ӧ������
extern int FILELAYER_STRIPGROUP_READER(STRIPGROUP *strgroup);//��STRIPGROUP�������а�����·����ȡ����Ӧ������;������Ҫͨ��region��disk�в���
extern int FILELAYER_REGIONGROUP_READER(REGIONGROUP *reggroup);//��REGIONGROUP��ȡ����Ӧλ��
extern int FILELAYER_DISKGROUP_READER(DISKGROUP *diskgroup);//��DISKGROUP��ȡ����Ӧλ��
extern int FILELAYER_DEVICEGROUP_READER(DEVICEGROUP *devicegroup);//��DEVICEGROUP��ȡ����Ӧλ��
extern int FILELAYER_FILEMETAGROUP_READER(FILEMETAGROUP *fmetagroup);//��FILEMETAGROUP��ȡ����Ӧλ��
extern int FILELAYER_USERPROFILEGROUP_READER(USERGROUP *ugroup);//��USERGROUP��ȡ��Ӧ����


//����д����,д�����
extern int FILELAYER_CHUNK_WRITER_META(CHUNK *chk);//��CHUNK�������а�����·��д�뵽��Ӧ������,Ԫ���ݲ���
extern int FILELAYER_CHUNK_WRITER_DATA(CHUNK *chk);//��CHUNK�������а�����·��д�뵽��Ӧ������,���ݲ���
extern int FILELAYER_STRIPSECT_CREATE(STRIPSECT *strset);//����һ��strset���
extern int FILELAYER_STRIPSECT_WRITER(STRIPSECT *strset);//��STRIPSECT�������а�����·��д�뵽��Ӧ������
extern int FILELAYER_STRIP_WRITER(STRIP *str);//��STRIPSECT�������а�����·��д�뵽��Ӧ������;������Ҫͨ��region��disk�в���
extern int FILELAYER_REGION_WRITER(REGION *reg);//��regionд����Ӧλ��;������Ҫͨ��region��disk�в���
extern int FILELAYER_DISK_WRITER(DISK *disk);//��DISK��Ԫ����д�����
extern int FILELAYER_DEVICE_WRITER(DEVICE *device);//��DEVICE��Ԫ����д�����
extern int FILELAYER_FILEMETA_WRITER(FILEMETA *fmeta);//���ļ���Ԫ����Ϣд�����
extern int FILELAYER_USERPROFILE_WRITER(USERPROFILE *pfile);//���û���Ϣ��Ԫ����д�����
//����ȫ���ļ�ֻ��һ������group����
extern int FILELAYER_GLOSYSTEMID_WRITER(GLOSYSTEMID *glosysid);//���û���Ϣ��Ԫ����д�����

extern int FILELAYER_CHUNKGROUP_WRITER_META(CHUNKGROUP *chkgroup);//��CHUNKGROUP�������а�����·��д�뵽��Ӧ������,Ԫ���ݲ���
extern int FILELAYER_CHUNKGROUP_WRITER_DATA(CHUNKGROUP *chkgroup);//��CHUNKGROUP�������а�����·��д�뵽��Ӧ������,���ݲ���
extern int FILELAYER_STRIPSECTGROUP_CREATE(STRIPSECTGROUP *strsetgroup);//��STRIPSECTGROUP�����ڲ���Ϣ�ڶ�Ӧλ�ô�����Ӧ��stripsect
extern int FILELAYER_STRIPSECTGROUP_WRITER(STRIPSECTGROUP *strsetgroup);//��STRIPSECTGROUP�������а�����·��д�뵽��Ӧ������
extern int FILELAYER_STRIPGROUP_WRITER(STRIPGROUP *strgroup);//��STRIPGROUP�������а�����·��д�뵽��Ӧ������;������Ҫͨ��region��disk�в���
extern int FILELAYER_REGIONGROUP_WRITER(REGIONGROUP *reggroup);//��REGIONGROUPд����Ӧ����
extern int FILELAYER_DISKGROUP_WRITER(DISKGROUP *diskgroup);//��DISKGROUPд����Ӧ����
extern int FILELAYER_DEVICEGROUP_WRITER(DEVICEGROUP *devicegroup);//��DEVICEGROUPд����Ӧ����
extern int FILELAYER_FILEMETAGROUP_WRITER(FILEMETAGROUP *fmetagroup);//��FILEMETAGROUPд����Ӧ����
extern int FILELAYER_USERPROFILEGROUP_WRITER(USERGROUP *ugroup);//��USERGROUPд�뵽��Ӧλ��