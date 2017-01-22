/*
This program is created by Jiajie Shen 
2014.11.23
��ѽܴ���2014.11.23
*/


#ifndef _GLOBAL_DEFINE_H
#define _GLOBAL_DEFINE_H

#include <stdio.h>
#include <stdlib.h>
//#include <cstdlib>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <io.h>
#include <direct.h>
#include <math.h>
#include <Windows.h>
//#include <WinSock2.h>
#include <mysql.h>
#include <pthread.h>
#include <semaphore.h>

#include <openssl/sha.h>
#include <openssl/aes.h>

#pragma comment(lib,"pThreadVC2.lib")
#pragma comment(lib,"libmysql.lib")
#pragma comment(lib,"libeay32.lib")
#pragma comment(lib,"ssleay32.lib")

#define DISKINDEX 0
#define MEMORYINDEX 1
#define UPDATEINDEX 2 

//�ļ��ӿ�ѡ��
#define MAXVALUE 100000000

#define UPDATESELECT UPDATEOPTINTERFACE

#define MATRIXINTERFACE 0
#define UPDATEOPTINTERFACE 1
#define UPDATE1INTERFACE 2
#define UPDATE2INTERFACE 3
#define PARITYDELAY 4

#define FILESELECT MYSQLINTERFACE

#define MYSQLINTERFACE 0
#define FILEINTERFACE 1

//����
#define Hamming 1
#define reed_sol 2
#define MSR 3
#define MBR 4
#define RAID6 5
#define RAID5 6
#define OTHER 7



//С��
#define FMSR 1
#define FMBR 2
#define EMSR 3
#define EMBR 4
#define MDRI 5
#define MDRII 6
#define RDP 7
#define EVENODD 8
#define LIBERATION 9
#define XCODE 10
#define PCODE 11
#define WEAVER 12
#define HOVER 13
#define CLASSICRS 15
#define CAUCHYORGRS 16
#define CAUCHYRS 17
#define BLAUMROTH 18
#define STAR 19
#define GENRDP 20


#define NULLTYPE 0
#define OTHERTYPE 50

//����������
#define mlowlevel 0
#define lowlevel 1
#define midlevel 2
#define highlevel 3
#define mhighlevel 4

//�������Ŷ���
#define QTRUE 0
#define TRUE 1
#define FALSE 0
#define PARTFALSE 2//���ڼ���stair����ģʽ
#define PFALSE -1
//#define NULL -1//�б���δ���ɣ������ڴ�Ϊ��

//galois�㷨����
#define GERROR -1
#define NONE 0
#define LOGS 1001
#define TABLE 1002
#define SHIFT 1003
#define SPLITW8 1004
#define INT64 long
#define UINT64 unsigned __int64
#define UINT32 unsigned long int
#define UINT16 unsigned short int
#define UINT8 unsigned char
#define INT32 long int
#define TINT64 int

//matrix�ж���
#define UFLOAT float
#define UDOUBLE double
#define BITMATRIX INTMATRIX
#define BITMATRIXGROUP INTMATRIXGROUP
//#define ERRORPATTERN INTMATRIX
#define ENCHUNK CHUNK
#define BYTE unsigned char
#define NODEVICE -1
#define NOSIZE -1
#define NOVALUE -1
#define COPY 0
#define XOR 1

//�洢����
#define NORHDD 0
#define SSHD 1
#define SSD 2

//�洢����״̬
#define EMPTY 0
//������״̬����ʵ�ʼ�����chunk�м�¼��ǰ���ڵ�BYTE������chunk�м�¼��һ���Ѿ�
#define PART 1
#define FULL 2

//�洢����������������
#define NONCAP 0//崻���
#define LOWCAP 1
#define MIDCAP 2
#define HIGHCAP 3

//�豸���Ͷ���
#define RACKMAC 0
#define PCMAC 1
#define NASMAC 2 

//�ļ�����
#define DICTKIND 0
#define FILEKIND 1//�鵵����ִ��һ�в���
#define READONLY 2
#define SYSTEMFILE 3
#define HIDEFILE 4

//����Ȩ�ޣ�����Ӽ�
#define SYSADMIN 0
#define SYSUSER 1
#define SYSVISITOR 2

//ϵͳ���ö���
#define TOTREGIONNUM 35
#define TOTDISKNUMBER 7
#define TOTDEVICENUMBER 7

//У������
#define PARITY 1
#define PPARITY 1
#define QPARITY 2

//����
#define AVAILTRUE 1
#define AVAILFALSE 0
#define AVAILPART 2


//��������
#define SYSTEMREPORT 0
#define FILEOPERATION 1

#define FILEUPDATE 0
#define FILEWRITE 1
#define FILEREAD 2
#define	FILEAPPEND 3
#define FILEDELETE 4




//��ǰ����
#define OPERATIONSUCCESS 0//�����ɹ�
#define FILENOTEXIST 1//ɾ��ʱ�ļ��Ѿ�����
#define FILEUPDATEOVERFINITE 2//���²�����
#define REGIONISFULL 3//��ǰ�ļ�


//��������stripsectblock��chunk����
typedef struct VSTRIPSECTBLOCK
{
	struct CHUNKBLOCK *chunkblockptr;
	int chunknum;
}VSTRIPSECTBLOCK;

typedef struct VSTRIPSECTBLOCKGROUP
{
	VSTRIPSECTBLOCK *vstripsectblockptr;
	int vstripsectnum;
}VSTRIPSECTBLOCKGROUP;

//���������ʽ
typedef struct REQUESTMESSAGE
{
	
	int operationtype;//��������
	char sysfilepath[1000];//��ǰ��ϵͳ·��
	int size;//��д�͸����д����ڶ�����ʱû������
	int offset;//updateϵͳƫ����

}REQUESTMESSAGE;


typedef struct RESPONSEMESSAGE
{
	int stateanswer;//��ǰ�ظ���ǰ�ļ�״̬
	int responsesize;//��ǰ�ظ����ݴ�С��Ҫ�������ݶ�ȡ
}RESPONSEMESSAGE;

//REED-sol.c����

//cauchy.c����
typedef struct INTARRAY
{
	UINT32 *items;
	int size;
}INTARRAY;



//�豸��ſ��Դ�0��ʼ�����и��������ң���ѧ�ң����ǳ���Գ��
typedef struct BYTESTREAM
{
	BYTE *BYTEcontent;
	UINT64 bytessize;
}BYTESTREAM;

typedef struct FILECONTENT
{
	BYTE *filecontent;
	char *filename;
	int size;
}FILECONTENT;

typedef struct REGCODEPATARMETER
{
	int n;//
	int k;//
	int d;//
}CODEPATAMETER; 


//�����ר��
typedef struct INTMATRIX //����xm,ymΪ��ǰwλ����xm��ym
{
	int w;//ȡֵΪ8,16,32
	int xm;
	int ym;
	UINT32* matrix;//ͳһΪ32λ//�����˺ܾ��ǲ���Ҫ�ֳ�8,16,32λ�ֱ�������û�б�Ҫ
	//�����bit����ôxm��ym�洢bitλ��
}INTMATRIX;//����һ�����;���

typedef struct INTMATRIXGROUP
{
	INTMATRIX *matrix;
	int groupsize;
}INTMATRIXGROUP;

typedef struct DOUMATRIX //����xm,ymΪ��ǰwλ����xm��ym
{
	int w;//ȡֵΪ8,16,32
	int xm;
	int ym;
	UDOUBLE* matrix32;
	
}DOUMATRIX;//����һ������������

typedef struct CHUNK 
{
	UINT64 ChunkID;//����

	int isparity;//�Ƿ���У���
	struct CHUNKPATH *chkpath;//chunk·��

	int sizenum;//�ֽ���
	BYTE* chunkcontent;//��Ҫԭ����chunk�Ĵ�С����byteΪ��λ

	UINT64 regionid;//���ڵ�region���
	struct REGION *regionptr;//��һ��region��ָ��

	UINT64 stripid;//����id��
	struct STRIP *stripptr;//��һ��strip��ָ��

	UINT64 stripsectid;//��������id��
	struct STRIPSECT *stripsectptr;//��һ��stripsect��ָ��

	UINT64 diskid;//���ڴ��̵�ID
	struct DISK *diskptr;//��һ��disk��ָ��

	UINT64 deviceid;//�����豸��ID
	struct DEVICE *deviceptr;//��һ��device��ָ��

	UINT64 fileid;//�ļ����
	struct FILEMETA *fmeta;//�ļ�Ԫ����

	int storestate;//��ǰ��洢״̬
}CHUNK;//����chunk�ṹ��

typedef struct CHUNKGROUP//����
{
	CHUNK *ckgroup;//�б�
	int groupsize;//��С
}CHUNKGROUP;

typedef struct CHUNKBLOCK//chunk��
{
	CHUNK *chunkptr;//chunkָ��
	UINT64 chunkid;//chunk���
}CHUNKBLOCK;

typedef struct CHUNKBLOCKGROUP//chunkblock��
{
	CHUNKBLOCK *chunkblockptr;
	int groupsize;
}CHUNKBLOCKGROUP;

typedef struct CHUNKPOSITIONBLOCK
{
	CHUNK *chunkptr;
	int chunkid;
	int stripsectindex;//datastripsect��λ��
	int chunkindex;//�ڵ�ǰstrip������һ��chunk
}CHUNKPOSITIONBLOCK;

typedef struct CHUNKPOSITIONBLOCKGROUP
{
	CHUNKPOSITIONBLOCK *chunkblockptr;
	int groupsize;
}CHUNKPOSITIONBLOCKGROUP;

typedef struct ERASES//�����Ҫ����ERASE���豸
{
	int *erases;
	int codenum;//�������
	int datanum;//�������
	int totnum;//Ϊ�����������
}ERASES;
typedef struct ENDECODEPARA//�����������
{
	int w;//��Ҫ���б�������
	INTMATRIX *matrix;//��Ҫ�ı�������
}ENDECODEPARA;
typedef struct DOTINF
{
	//��¼��Ҫʹ�õ��������ݿ��Ŀ��洢��
	int *src_ids;//��Ҫ�����chunk��
	int linenum;//��Ӧ��˵��к�
	int colsnum;//src_id����������group��������ȡ����src_ids�Ƿ�Ϊ��
	int packetsize;//bitmatrix�е�����С
	int parityTF;//Ŀ����Ƿ���У���
	
}DOTINF;
typedef struct DM_IDS
{
	int *dm_ids;//�ִ��豸��
	int size;//��С
}DM_IDS;

typedef struct COST_TIME
{
	clock_t start_time;//��ʼʱ��
	clock_t end_time;//����ʱ��
}COST_TIME;
//ͳ������
typedef struct STATSITEM
{
	//���㿪��
	UINT64 xornum;//�������
	UINT64 w08multnum;//w8�˷�
	UINT64 w16multnum;//w16�˷�
	UINT64 w32multnum;//w32�˷�
	//�ڴ濪��
	UINT64 memcpynum;//memcpy����
	//���Ϳ���
	UINT64 sendnum;//����������
	UINT64 recnum;//����������
	//��д����
	UINT64 readnum;//�Ӵ��̵Ķ���������
	UINT64 writenum;//�����д��������
	//ʵ��ʱ�俪��
	//����ʱ��
	COST_TIME EN_time;

	//����ʱ��
	COST_TIME DE_time;

	//�Ǳ��뿪��ʱ��,overhead
	COST_TIME OVER_time;

	//Ӳ�̶�дʱ��
	COST_TIME IO_time;

	//���紫��ʱ��
	COST_TIME TRANS_time;
}STATSITEM;
//id����
typedef struct IDITEM
{
//6��ȫ��id���
	UINT64 gloregionid;//ȫ��region���
	UINT64 glostripid;//ȫ��strip���
	UINT64 glostripsectid;//ȫ��stripsection���
	UINT64 glodeviceid;//ȫ��device���
	UINT64 glodiskid;//ȫ��disk���
	UINT64 glochunkid;//ȫ��chunk���
	UINT64 glofileid;//ȫ��file���
	UINT64 glouserid;//ȫ��user���
}IDITEM;

typedef struct SCHEDOP
{
	int op;//��Ҫ���еĲ���
	int sd;//Դ�洢��,�߼�stripsectindex
	int sb;//Դλ��,�߼�chunkindex
	int dd;//Ŀ��洢��,�߼�stripsectindex
	int db;//Ŀ��λ��,�߼�chunkindex
	int istareget;//�ǲ��ǵ�ǰ��Ҫ��Ŀ��ڵ�
	CHUNK *tarchunkptr;//Ŀ��chunk��
	UINT64 tarchunkid;
}SCHEDOP;

typedef struct SCHEDULE
{
	SCHEDOP *schedlist;//�����������
	int size;//��ǰ�������д�С
	int w;//��ǰ��
}SCHEDULE;

typedef struct SCHEDULEGROUP
{
	SCHEDULE *schedulegroup;//
	int groupsize;//
}SCHEDULEGROUP;

typedef struct BITELEMENT
{
	BITMATRIX *elementptr;//ģʽxmΪ����
	//�߼�
	int stripsectindex;//�ڼ���stripsect
	int chunkindex;//�ڼ���chunk

	int istarget;//��ǰ��Ԫ���ǲ���Ŀ��Ԫ��

	SCHEDULE *scheduleptr;//��������

	CHUNK *chunkptr;//��ǰchunkָ��
	UINT64 chunkid;//��ǰchunk��id
}BITELEMENT;

typedef struct BITELEMENTGROUP
{
	BITELEMENT *bitelemetgroup;//��ǰbitelementָ��
	int groupsize;//��ǰbitelement�Ĵ�С
}BITELEMENTGROUP;

typedef struct UPDATEELEMENT
{
	BITELEMENT *bitelementptr;//��ǰbitelement

	SCHEDULE *updateIscheduleptr;//updateI��������
	BITMATRIX *updateIelementptr;//updateI��Ŀ��element

	SCHEDULE *updateIIscheduleptr;//updateII��������
	BITMATRIX *updateIIelementptr;//updateII��Ŀ��element

	int stripsecindex;//�߼�stripsectindex
	int chunkindex;//�߼�chunkindex

	int isupdateI;//TRUE����updateI������FALSE������updateII,PFALSE����û��

	CHUNK *tempchunkptr;//��ǰ�����ָ�����ڼ�¼����update�м�ֵ�е�һ��
	//BYTE *updatecontentptr;//��ǰ����Ľ������
	//int sizenum;//��ǰ�Ŀ��С

	int shouldreadnum;
	int lastindex;//��һ������λ��,diskindexΪ0,momeryindexΪ1��updateindex2

	BITELEMENT *lastdiskelement;//�����diskԪ��
	int diskshouldread;//������Ҫ��ȡ�Ŀ������Ҫ��У���
	int isdiskupdateI;//���ʹ��diskԪ����Ҫ�ĸ��·�ʽ

	BITELEMENT *lastmemoryelement;//�����memoryԪ��
	int memoryshouldread;//memnory������Ҫ��ȡ�Ŀ���
	int ismemoryupdateI;//memoryʹ�õĸ��·�ʽ

	struct UPDATEELEMENT *lastupdateelement;//��һ��updateԪ��
	int updateshouldread;//update������Ҫ��ȡ�Ŀ���
	int isupdateupdateI;//updateʹ�õĸ��·�ʽ
	
	
}UPDATEELEMENT;

typedef struct UPDATEELEMENTGROUP
{
	UPDATEELEMENT *updategroup;//��ǰָ��
	int groupsize;//��С
}UPDATEELEMENTGROUP;

typedef struct UPDATEELEMENTBLOCK//ָ��
{
	UPDATEELEMENT *updateelementptr;
}UPDATEELEMENTBLOCK;

typedef struct UPDATEELEMENTBLOCKGROUP
{
	UPDATEELEMENTBLOCK *updateelementblockptr;
	int groupsize;
}UPDATEELEMENTBLOCKGROUP;

typedef struct CAHCE
{
	int ***cache;
}CACHE;

//�ļ�ϵͳ�ṹ
//���ݽṹ��Ϣ
typedef struct MAPITEM
{
	UINT64 fileid;//�ļ�id
	struct FILEMETA *filemetaptr;//�ļ�ָ��
	UINT64 deviceid;//�豸id
	struct DEVICE *deviceptr;//�豸ָ��
	UINT64 diskid;//�洢��id
	struct DISK *diskptr;//�洢��ָ��
	UINT64 stripid; //����id
	struct STRIP *stripptr;//����ָ��
	UINT64 stripsectid;//������id
	struct STRIPSECT *stripsectptr;//������ָ��
	UINT64 chunkid;//��id
	struct CHUNK *chunkptr;//��ָ��
	UINT64 regoinid;//����id
	struct REGION *regionptr;//����ָ��
}MAPITEM;

typedef struct MAPPAIR
{
	MAPITEM *login_item;//�߼���
	MAPITEM *physic_item;//�����
}MAPPAIR;

typedef struct CODEPARA//��Ҫ�Ĳ���
{
	int w;//٤�޻����С
	int datanum;//k
	int codenum;//m
	int totnum;//n
	int pronum;//d
	int sectornum; //�����������Ŀ���
}CODEPARA;

//����������Ϊ������Ҫ��������
typedef struct STRIPDES 
{
	int chunknum;//ÿһ����������������,��ÿһ��STRIPSECT��chunk��

	struct DISKBLOCK *disklist;//�����disk�б�
	UINT64 *diskid;//��ǰ����id
	int disknum;//���ڵļ�һ����������������������ͨ�����������region��disk��һ��

	int chunksize;//ÿһ��CHUNK�Ĵ�С���ֽ�Ϊ��λ
}STRIPDES;

typedef struct STRIPSECT
{
	UINT64 StripsectID;//STRIPSECT��id

	int isparity;//��ǰ��stripsect�ǲ�������У��
	UINT64 *chunkid;//	���а�����chunkid
	CHUNKGROUP *chunklist;//����һ��chunkgroup�þ߼�¼chunk��,��Ϊһ��chunkָ��
	int chunksize;//����ÿһ��chunk�Ĵ�С
	int chunknum;//������chunk��������

	UINT64 regionid;///���ڵ�region���
	struct REGION *regionptr;//��һ��regionָ��

	UINT64 stripid;//���ڵ�strip���
	struct STRIP *stripptr;//��һ��stripָ��

	UINT64 diskid;//���ڵ�disk���
	struct DISK *diskptr;//��һ��diskָ��

	UINT64 deviceid;//���ڵ�device���
	struct DEVICE *deviceptr;//��һ��deviceָ��

	char *filename;//�ļ���
	//veronica��
	char *filepath;//�ļ�������·�����������disk�е�·����filename���

	int storestate;//��ǰ�洢״̬
}STRIPSECT;

typedef struct STRIPSECTGROUP
{
	STRIPSECT *stripsectgroup;//�б�
	int groupsize;//��С
}STRIPSECTGROUP;

typedef struct STRIPSECTBLOCK
{
	STRIPSECT *stripsectptr;//stripsectָ��
	UINT64 stripsectid;//stripsect����
}STRIPSECTBLOCK;

typedef struct STRIPSECTBLOCKGROUP
{
	STRIPSECTBLOCK *stripsectblockptr;//�б�
	int groupsize;//��С
}STRIPSECTBLOCKGROUP;

typedef struct STRIP//����������Ϣ
{
	UINT64 StripID;//��Ϣ

	STRIPDES *strdes;//����������stripdes��chunk��*stripdes�д�����=���������chunk��
	
	struct DISKBLOCK *disklist;//�洢���б�
	UINT64 *diskid;//�����Ĵ洢��id
	int disknum;//�����洢������
	//����device��disk��region�б���,һֱ���ٵ�ǰveronica�汾һ��
	//��ע�����в�һ�°汾
	struct DEVICEBLOCK *devicelist;//�豸�б�
	UINT64 *deviceid;//�豸id
	int devicenum;//�豸��
	
	STRIPSECTGROUP *stripsectlist;//stripsectָ��
	UINT64 *stripsectid;//stripsect��id
	int strsetnum;//Strset������

	CHUNKGROUP *chunklist;//����һ��chunkgroup�þ߼�¼chunk��,��Ϊһ��chunkָ��
	UINT64 *chunkid;//	���а�����chunkid
	int chunknum;//������chunk����

	UINT64 regionid;//���ڵ�region���
	struct REGION *regionptr;//��һ��regionָ��

	int storestate;//��ǰ�洢״̬
}STRIP;

typedef struct STRIPGROUP//������
{
	STRIP *stripgroup;//�б�
	int groupsize;//��С
}STRIPGROUP;

typedef struct STRIPBLOCK
{
	STRIP *stripptr;//stripָ��
	UINT64 stripid;//strip����
}STRIPBLOCK;

typedef struct STRIPBLOCKGROUP
{
	STRIPBLOCK *stripblockptr;//�б�
	int groupsize;//��С
}STRIPBLOCKGROUP;

typedef struct DISK//���ڵ����߼��洢����������
{
	UINT64 DiskID;//�洢�����
	int DiskTYPE;//�洢������
	int capability;//��������
	UINT64 volumn;//�洢������

	struct REGIONBLOCK *regionlist;//ָ�����а�����region��ָ��
	UINT64 *regionid;//�洢�����漰����region��
	int regionnum;//�洢���ϰ�����region����

	struct DEVICE *deviceptr;//ָ���ϼ�device�б�
	UINT64 deviceid;//��һ���device���
	
	char *diskpath;//�ؼ���Ϣ��ǰ���̵�����·��

	int availstate;//��ǰ�ɵ�״̬���������Ԫ���ݴ洢�У�����readǰ����״̬
	int storestate;//��ǰ�洢״̬	
}DISK;

typedef struct DISKGROUP//������
{
	DISK *diskgroup;//�б�
	int groupsize;//��С
}DISKGROUP;

typedef struct DISKBLOCK
{
	DISK *diskptr;//diskָ��
	UINT64 diskid;//disk���
}DISKBLOCK;

typedef struct DEVICE
{
	UINT64 DeviceID;//�豸���
	int Devicetype;//�豸���
	int processnum;//����������
	int *speed;//GHZ

	
	UINT64 *diskid;//�豸�д��ڵĴ洢��
	DISKBLOCK *disklist;//�洢�豸�б�
	int disknum;//�洢�����洢��

	struct REGIONBLOCK *regionlist;//region�б�
	UINT64 *regionid;//region���
	int regionnum;//region����

	int storestate;//��ǰ�洢״̬
}DEVICE;

typedef struct DEVICEGROUP//�豸��
{
	DEVICE *devicegroup;//�б�
	int groupsize;//��С
}DEVICEGROUP;

typedef struct DEVICEBLOCK
{
	DEVICE *deviceptr;//�б�
	UINT64 deviceid;//��С
}DEVICEBLOCK;

typedef struct REGION//�����߼�region��������
{
	UINT64 RegionID;//region��id
	int codetype;//��������
	CODEPARA *codepara;//�������
	UINT64 totalsize;//�ܴ洢�ռ��С�ֽ�Ϊ��С��NODEF�������޴�ֱ��ռ��

	struct FILEMETABLOCKGROUP *filemetalist;//�ļ�Ԫ�����б�,��Ϣ��Ϊ���ö���group�������
	UINT64 *fileid;//������file�ı���б�
	int filenum;//file����

	DISKBLOCK *disklist;//Disk�б�
	UINT64 *diskid;//Disk�ı���б�
	int disknum;//���̵ĸ���

	DEVICEBLOCK *devicelist;//device�б�
	UINT64 *deviceid;//�豸id�б�
	int devicenum;//�豸����

	STRIPDES *strdes;//��������������
	STRIPGROUP *striplist;//Strip�б�
	UINT64 *stripid;//����id�б�
	int stripnum;//��������
	
	//���ڿ��ܺܶ���Ҫ64λ������������У�飬��������format
	UINT64 chunknum;//����chunk����
	UINT64 stripsectnum;//����stripsect����

	struct FILEMETA *fileroot;//��ǰ������ļ��ĸ�ָ��
	UINT64 rootfileid;//���ļ����

	int storestate;//��ǰ�洢״̬
}REGION;

typedef struct REGIONGROUP//������
{
	REGION *regiongroup;//�б�
	int groupsize;//��С
}REGIONGROUP; 

typedef struct REGIONBLOCK
{
	REGION *regionptr;//regionָ��
	UINT64 regionid;//region���
}REGIONBLOCK;

typedef struct RUNPATARMETER//ϵͳ����ʱ��Ҫ�Ĳ�����veronica�����豸���и�֪���DEVIE�����ò���
{
	int appnumber;//�����豸��
	struct DEIVCEGROUP *machinedvice;//�豸����
	int initalstate;//ϵͳ�Ƿ��ѳ�ʼ��
}RUNPATARMETER;

//�ļ���·��
typedef struct CHUNKPATH//��·��
{
	UINT64 regionid;//regionidȫ�ֱ��
	int regionarrayid;//֮ǰһ�η���ֵ��region���λ��
	REGION *regionptr;//regionָ��

	UINT64 stripid;//stripidȫ�ֱ��
	int striparrayid;//֮ǰһ�η���ֵ��strip���λ��
	STRIP *stripptr;//stripָ��

	UINT64 stripsectid;//stripsectȫ�ֱ��
	int stripsectarrayid;//֮ǰһ�η���ֵ��stripsect���λ��
	STRIPSECT *stripsectptr;//stripsectָ��

	UINT64 chunkid;//chenk��ȫ�ֱ��
	int chunkarrayid;//֮ǰһ�η���ֵ��chunk�����λ��
	CHUNK *chunkptr;//ָ��ǰchunk
}CHUNKPATH;

//�ļ���BLOCK
typedef struct CHUNKPATHBLOCK
{
	UINT64 chunkid;
	CHUNKPATH *chunkpath;
}CHUNKPATHBLOCK;

typedef struct CHUNKBLOCKSTRIP
{
	UINT64 stripid;//�������
	STRIP *stripptr;

	CHUNKBLOCK *datachunkblockptr;//��Ž��
	int chunknum;

//	CHUNKBLOCK *paritychunkblockptr;������������
//	int chunknum;
}CHUNKBLOCKSTRIP;

typedef struct CHUNKBLOCKSTRIPGROUP
{
	CHUNKBLOCKSTRIP *chunkblockstripptr;
	int groupsize;
}CHUNKBLOCKSTRIPGROUP;

//�ļ��洢��Ϣ
typedef struct FILEINF
{
	UINT64 fileid;//�ļ�ID
	struct FILEMETA *filemeta;//�ļ�Ԫ���ݷ���ָ��
	UINT64 *chunkid;//Դ����б�
	CHUNKPATH *chkpath;//����chunk��path
	CHUNKBLOCK *chunklist;//���б�
	int chunknum;//chunk����

	REGION *regoinptr;//regionָ��
	UINT64 regionid;//���ڵ�region�ı��
	
	DEVICEBLOCK *devicelist;//�豸�б�
	UINT64 *deviceid;//�豸id
	int devicenum;//�豸��
	
	DISKBLOCK *disklist;//�洢���б�
	UINT64 *diskid;//�洢��id�б�
	int disknum;//�洢������

	STRIPBLOCK *striplist;//�����б�
	UINT64 *stripid;//����id�б�
	int stripnum;//��������

	STRIPSECTBLOCK *stripsectlist;//���������б�
	UINT64 *stripsectid;///��������id�б�
	int stripsectnum;//������������
}FILEINF;
//FILEMETAָ��BLOCK
typedef struct FILEMETABLOCK
{
	UINT64 FileID;
	struct FILEMETA *filemetaptr;
}FILEMETABLOCK;

//FILEMETAָ��BLOCK��
typedef struct FILEMETABLOCKGROUP
{
	FILEMETABLOCK *filemetablockptr;
	int groupsize;
}FILEMETABLOCKGROUP;

//�ļ�Ԫ����
typedef struct FILEMETA
{
	UINT64 FileID;//�ļ�ID
	char *filename;//�ļ�������Ŀ¼��
	UINT64 filesize;//�ļ���С
	int ACList;//�ļ����ʱ�ʶ
	int filetype;//�ļ�����,�ļ�����Ŀ¼,�ļ�����,ֻ���鵵����ϵͳ

	REGION *regionptr;//�ϲ�regionָ��
	UINT64 regionid;//�ϲ�region���

	struct USERPROFILE *userinf;//�ļ�������
	UINT64 userid;//�ļ�������id

	UINT64 parentid;//��һ���ļ���id
	struct FILEMETA *parentptr;//��һ���ļ���
	
	UINT64 *subfileidlist;//��Ŀ¼�б�������Ҫ����linux˼��
	struct FILEMETABLOCK *subfilelist;//�ļ���ָ����Ҫָ��ǰĿ¼��һ��Ԫ���ݿ飬Ϊ�˼���
	int subfilenum;//��Ŀ¼���ļ�����

	int curoffset;//��ǰָ���ƫ�������豣�ֳ�ʼ��������ʱ��

	struct tm *createtime;//����ʱ��
	struct tm *updatetime;//����ʱ��

	FILEINF *filechunkinf;//���ڴ�����ݿ���Ϣ
}FILEMETA;
//�ļ�Ԫ������
typedef struct FILEMETAGROUP
{
	FILEMETA *filemetagroup;
	int grouposize;
}FILEMETAGROUP;

//�û���ǰ��λ��
typedef struct USERLOCATION
{
	UINT64 DICid;//Ŀ¼id
	FILEMETA *DICmetaptr;//Ŀ¼Ԫ����
	char *DICpath;//��ǰĿ¼·��
}USERLOCATION;

//�û���Ϣ
typedef struct USERPROFILE
{
	UINT64 UserID;//�û�id
	char *username;//�û���
	char *password;//����
	USERLOCATION *userlocinf;//�û�Ŀ¼λ��
	int userprivil;//�û�Ȩ��
	struct tm *createtime;//�˻�����ʱ��
	
}USERPROFILE;

//�û���
typedef struct USERGROUP//�û���
{
	USERPROFILE *userlist;//�û��б�
	int groupsize;//��С
}USERGROUP;
//�û�ָ����
typedef struct USERBLOCK
{
	UINT64 userid;
	USERPROFILE *userprofileptr;
}USERBLOCK;
//��ǰ�û���Ϣ
typedef struct SYSTEMUSERPTR
{
	UINT64 userid;//��ǰϵͳ�û�id
	USERPROFILE *userprofileptr;//ϵͳ��ǰ�û�ָ��
}SYSTEMUSERPTR;

//ȫ��id��Ϣ,regionid,userid,deviceid,diskid
typedef struct GLOSYSTEMID
{
	UINT64 *regionid;//��ǰregion����б�
	int regionnum;//��ǰregion����
	REGIONGROUP *gloregiongroup;//��ǰregion�б�

	UINT64 *userid;//��ǰuser����б�
	int usernum;//��ǰuser����
	USERGROUP *glousergroup;//��ǰuser�б�

	UINT64 *deviceid;//��ǰdevice����б�
	int devicenum;//��ǰdevice����
	DEVICEGROUP *glodevicegroup;//��ǰdevice�б�

	UINT64 *diskid;//��ǰdisk����б�
	int disknum;//��ǰdisk����
	DISKGROUP *glodiskgroup;//��ǰdisk�б�

	IDITEM *systemnextid;//��һ��ϵͳ��Ҫ�����id
	
	int glopushtime;//push��ʱ����
	UINT64 glomaxbuffersize;//��󻺳���
	//CHUNKGROUP *glopushchunklist;//��Ҫpush�����ݿ���
	int *availkind;//�ִ��������
	int availnum;//������������
}GLOSYSTEMID;

//��ǰpush�б�
typedef struct GLOPUSHLIST
{
	int glopushtime;//push��ʱ����
	CHUNKBLOCK *glopushchunklist;//��Ҫpush�����ݿ���
	int chunknum;//��ǰ�����chunk��
	UINT64 currentbuffersize;//��ǰ�Ѿ������buffer��С
	UINT64 maxbuffersize;//����������buffer��С
	struct tm *glolastpushtime;//��һ��pushʱ��
}GLOPUSHLIST;

//�����޸�����ͬ��,��¼������
typedef struct GLODIRTYDATA
{
	//����Ԫ����ʵ��
	CHUNKBLOCK *chunkblockptr;
	int chunknum;

	STRIPSECTBLOCK *stripsectblockptr;
	int stripsectnum;

	STRIPBLOCK *stripblockptr;
	int stripnum;

	REGIONBLOCK *regionblockptr;
	int regionnum;

	FILEMETABLOCK *filemetablockptr;
	int filemtetanum;

	DEVICEBLOCK *deviceblockptr;
	int devicenum;

	DISKBLOCK *diskblockptr;
	int disknum;

	USERBLOCK *userblockptr;
	int usernum;
}GLODIRTYDATA;

typedef struct ERRORPATTERN
{
	BITMATRIX *bitmatrix;//���ڼ�¼����ģʽ������У��Ϊһ�У���У����Ҫ���ݶ��崦��ʧЧΪTRUE��û��ΪFALSE
	int errordisknum;//������̸���
	int errorchunknum;//����chunknum����������У��������
}ERRORPATTERN;

typedef struct GLOTEMPFREELIST//��Ҫ���ڼ�¼��ǰ�����ж����ڴ�
{
	CHUNKBLOCK *chunkblockptr;//��ǰ��Ҫ�ͷŵ��б�
	int tempnum;//������ǰ����Ķ�ȡ��
}GLOTEMPFREELIST;

typedef struct AONTSHARE//���嵱ǰ��ȫ�洢�е�SHARE
{
	char *storepath;
	CODEPARA *codeptr;//��ǰ�������
	BYTE *content;//��Ҫд������� 
	int sizenum;
}AONTSHARE;

typedef struct AONTSHAREGROUP
{
	int groupsize;
	struct AONTSHARE *sharegroupptr;
}AONTSHAREGROUP;

typedef struct SHAREADDRESS
{
	char *storepath;
}SHAREADDRESS;

typedef struct ADDRESSLIST
{
	CODEPARA *codeptr;//�������ָ��
	SHAREADDRESS *addressptr;//�洢��ַ��
}ADDRESSLIST;

typedef struct TRACEITEM 
{
	int opertype;
	UINT64 offset;//ƫ����һ��ϴ�
	int length;
	char *filename;//�ļ���
}TRACEITEM;



extern void intial();


#define talloc(type,num) (type *)malloc(sizeof(type)*num)//����洢�ռ�
#define ralloc(type,num,point) (type *)realloc(point,sizeof(type)*num)//���·����ڴ�ռ�
#define mcpy(point1,point2,type,num) memcpy(point1,point2,sizeof(type)*num)

#define show_error(part,func,desc) fprintf(stderr,"filename:%s,function:%s,description:%s\n",part,func,desc)//��¼������Ϣ

#define show_message(mcontent) printf("%s\n",mcontent)

#define codetype(type1,type2) (type1*1000+type2)//����������
#define maintype(codetype) (int)(codetype/1000)//������Ҫ�����Ҫ��mapper��Ҫ��
#define subtype(codetype) (int)(codetype%1000)//��������Ҫʹ��no-use

#define calchunknum(filesize,chunksize) (int)(filesize/(UINT64)chunksize)+1
#define calremainsize(chunksize,chunknum,filesize) (int)(filesize-(UINT64)chunksize*(UINT64)(chunknum-1))

#define calstripsize(strsetsize,disknum) strsetsize*disknum
#define calstripsectsize(chunksize,chunknum) chunksize*chunknum;
#define calstripnum(totalsize,stripsize) (int)(totalsize/stripsize)+1
#define calstripchunkmaxnum(chunknum,disknum) chunknum*disknum
#define calmaxchunknum(stripnum,stripchunkmaxnum) stripnum*stripchunkmaxnum
#define calcodecountnum(chunknum,codenum) chunknum*codenum

#define calchunkstriparrayid(chunknum,strsetarrayid,chunkarrayid) chunknum*strsetarrayid+chunkarrayid
#define calchunkregionarrayid(chunknum,striparrayid,chunkarrayid) chunknum*striparrayid+chunkarrayid

#define calstripsectregionarrayid(strsetnum,striparrayid,strsetarrayid) strsetnum*striparrayid+strsetarrayid

#define caldevice(cols,w) cols/w//ͨ�����ݽ��м��������豸��k

#define bzero(matrix,type,sizenum) memset(matrix,0,sizeof(type)*sizenum) 
#define mset(matrix,type,number,sizenum) memset(matrix,number,sizeof(type)*sizenum)

#define randomnumber01 rand()/RAND_MAX

//����Ҫע�ⲻҪ������c++���������˲�֧��
#define chksize_KB(kbyte) (kbyte*1024)//��KBΪ��λ����chunksize
#define chksize_MB(mbyte) (mbyte*1048576)//��MBΪ��λ����chunksize

//���������ǿ��ת64λ�����������һ�����ʻᱨ��
#define chksize_GB(gbyte) ((UINT64)gbyte*(UINT64)1073741824)//��GBΪ��λ����chunksize
#define chksize_TB(tbyte) ((UINT64)tbyte*(UINT64)1099511627776)//��TBΪ��λ�����С

#define STRTOINT64(charstring,int64str) sscanf(charstring,"%I64d",&int64str);
#define STRTOINT32(charstring,int32str) sscanf(charstring,"%d",&int32str);

static STATSITEM systemstatic;//ϵͳͳ����Ϣ
static IDITEM systemid;//ϵͳid��Ϣ

static DEVICEGROUP grodevicelist;

static DISKGROUP grodisklist;//��ǰϵͳ���ڵ�disk�б�

static REGIONGROUP groregionlist;//��ǰϵͳREGION�б�

static USERGROUP grouserlist;//��ǰϵͳ�û��б�

static char *grometadatapath;//ȫ��Ԫ����
static SYSTEMUSERPTR sysuserptr;//ȫ��ϵͳ�û�ָ��

static GLOSYSTEMID grosysid;//�����ڳ�ʼ��ʱ��ʹ������ʱ��ϵͳGROUPΪ׼��ͬ��ʱҲ��ϵͳgroupΪ׼

static GLOPUSHLIST gropushlist;//pushlist����push�õ���Ϣ

static GLODIRTYDATA grodirtydatalist;//�������б�

static GLOTEMPFREELIST grotempfreelistptr;//��ǰ��Ҫ�ͷŵ����ݿ�ָ��

static int *availkind;//�ִ��������
static int availnum=0;//������������

//������Ϣ����
extern MAPITEM GLOBAL_create_MAPITEM_NULL();//�Զ�����һ����MAPITEM���ݽṹ
extern MAPPAIR GLOBAL_create_MAPPAIR_NULL();//�Զ�����һ����MAPPAIR���ݽṹ
extern CODEPARA GLOBAL_create_CODEPARA_NULL();//�Զ�����һ����CODEPARA���ݽṹ
extern STRIPDES GLOBAL_create_STRIPDES_NULL();//�Զ�����һ����STRIPDES���ݽṹ
extern CHUNKGROUP GLOBAL_create_CHUNKGROUP_NULL();//�Զ�����һ����CHUNKGROUP���ݽṹ
extern STRIPSECTGROUP GLOBAL_create_STRIPSECTGROUP_NULL();//�Զ�����һ����STRIPSECTGROUP���ݽṹ
extern STRIPGROUP GLOBAL_create_STRIPGROUP_NULL();//�Զ�����һ����STRIPGROUP���ݽṹ
extern DISKGROUP GLOBAL_create_DISKGROUP_NULL();//�Զ�����һ����DISKGROUP���ݽṹ
extern DEVICEGROUP GLOBAL_create_DEVICEGROUP_NULL();//�Զ�����һ����DEVICEGROUP���ݽṹ
extern REGIONGROUP GLOBAL_create_REGIONGROUP_NULL();//�Զ�����һ����REGIONGROUP���ݽṹ
extern RUNPATARMETER GLOBAL_create_RUNPATARMETER_NULL();//�Զ�����һ����RUNPATARMETER���ݽṹ
extern CHUNKPATH GLOBAL_create_CHUNKPATH_NULL();//�Զ�����һ����CHUNKPATH���ݽṹ
extern FILEINF GLOBAL_create_FILEINF_NULL();//�Զ�����һ����FILEINF���ݽṹ
extern FILEMETA GLOBAL_create_FILEMETA_NULL();//�Զ�����һ����FILEMETA���ݽṹ,fileidָ����һ��fileid
extern USERLOCATION GLOBAL_create_USERLOCATION_NULL();//�Զ�����һ����USERLOCATION���ݽṹ
extern USERPROFILE GLOBAL_create_USERPROFILE_NULL();//�Զ�����һ����USERPROFILE���ݽṹ
extern USERGROUP GLOBAL_create_USERGROUP_NULL();//�Զ�����һ����USERGROUP���ݽṹ
extern SYSTEMUSERPTR GLOBAL_create_SYSTEMUSERPTR_NULL();//�Զ�����һ����SYSTEMUSERPTR���ݽṹ

//������Ϣ���캯��
extern int GLOBAL_set_time(struct tm *timeptr,
							int createtime1,int createtime2,int createtime3,int createtime4,int createtime5,
							int createtime6,int createtime7,int createtime8,
							int createtime9);
extern int GLOBAL_set_MAPITEM_data(MAPITEM *mitem,UINT64 fileid,FILEMETA *filemetaptr,//�ļ�ָ��
								   UINT64 deviceid,DEVICE *deviceptr,//�豸ָ��
								   UINT64 diskid,DISK *diskptr,//�洢��ָ��
								   UINT64 stripid,STRIP *stripptr,//����ָ��
								   UINT64 stripsectid,STRIPSECT *stripsectptr,//������ָ��
								   UINT64 chunkid,CHUNK *chunkptr,//��ָ��
								   UINT64 regoinid,REGION *regionptr//����ָ��
								   );//�趨MAPITEM����ֵ
extern int GLOBAL_set_MAPPAIR_data(MAPPAIR *mpair,
								   MAPITEM *login_item,MAPITEM *physic_item//�����
								   );//�趨MAPPAIR����ֵ
extern int GLOBAL_set_CODEPARA_data(CODEPARA *cpara,
									int w,//٤�޻����С
									int datanum,//k
									int codenum,//m
									int totnum,//n
									int pronum,//d
									int sectornum//�����������Ŀ���
									);//�趨CODEPARA����ֵ
extern int GLOBAL_set_STRIPDES_data(STRIPDES *strdes,
									int chunknum,//ÿһ����������������,��chunk��
									DISKBLOCK *disklist,//�����disk�б�
									UINT64 *diskid,//��ǰ����id
									int disknum,//���ڵļ�һ����������������������ͨ�����������region��disk��һ��
									int chunksize//ÿһ��CHUNK�Ĵ�С���ֽ�Ϊ��λ
									);//�趨STRIPDES����ֵ
extern int GLOBAL_set_CHUNKGROUP_data(CHUNKGROUP *chkgroup,
									  CHUNK *ckgroup,//�б�
									  int groupsize//��С
									  );//�趨CHUNKGROUP����ֵ
extern int GLOBAL_set_STRIPSECTGROUP_data(STRIPSECTGROUP *strsetgroup,
										  STRIPSECT *stripsectgroup,//�б�
										  int groupsize//��С
										  );//�趨STRIPSECTGROUP����ֵ
extern int GLOBAL_set_STRIPGROUP_data(STRIPGROUP *strgroup,
									  STRIP *stripgroup,//�б�
									  int groupsize//��С
									  );//�趨STRIPGROUP����ֵ
extern int GLOBAL_set_DISKGROUP_data(DISKGROUP *disgroup,
									 DISK *diskgroup,//�б�
									 int groupsize//��С
									 );//�趨DISKGROUP����ֵ
extern int GLOBAL_set_DEVICEGROUP_data(DEVICEGROUP *devgroup,
									   DEVICE *devicegroup,//�б�
									   int groupsize//��С
									   );//�趨DEVICEGROUP����ֵ
extern int GLOBAL_set_REGIONGROUP_data(REGIONGROUP *reggroup,
									   REGION *regiongroup,//�б�
									   int groupsize//��С
									   );//�趨REGIONGROUP����ֵ
extern int GLOBAL_set_CHUNKPATH_data(CHUNKPATH *chkpath,
									 UINT64 regionid,int regionarrayid,REGION *regionptr,//regionָ��
									 UINT64 stripid,int striparrayid,STRIP *stripptr,//stripָ��
									 UINT64 stripsectid,int stripsectarrayid,STRIPSECT *stripsectptr,//stripsectָ��
									 UINT64 chunkid,int chunkarrayid,CHUNK *chunkptr//ָ��ǰchunk
									 );//�趨CHUNKPATH����ֵ
extern int GLOBAL_set_FILEINF_data(FILEINF *finf,UINT64 fileid,UINT64 *chunkid,FILEMETA *filemeta,
								   CHUNKPATH *chkpath,CHUNKBLOCK *chunklist,int chunknum,//chun�б�
								   REGION *regionptr,UINT64 regionid,//regionָ��
								   DEVICEBLOCK *devicelist,UINT64 *deviceid,int devicenum,//�豸�б�
								   DISKBLOCK *disklist,UINT64 *diskid,int disknum,//�洢���б�
								   STRIPBLOCK *striplist,UINT64 *stripid,int stripnum,//�����б�
								   STRIPSECTBLOCK *stripsectlist,UINT64 *stripsectid,int stripsectnum//���������б�
								   );//�趨FILEINF����ֵ
extern int GLOBAL_set_FILEMETA_data(FILEMETA *fmeta,char *filename,UINT64 filesize,int ACList,int filetype,
									REGION *regionptr,UINT64 regionid,//�ϲ�regionָ��
									struct USERPROFILE *userinf,UINT64 userid,//�ļ�������
									UINT64 parentid,FILEMETA *parentptr,//��һ���ļ���
									UINT64 *subfileidlist,FILEMETABLOCK *subfilelist,int subfilenum,//�ļ���ָ����Ҫָ��ǰĿ¼��һ��Ԫ���ݿ�
									struct tm *createtime,
									struct tm *updatetime,
									FILEINF *filechunkinf//���ڴ�����ݿ���Ϣ
									);//�趨FILEMETA����ֵ
extern int GLOBAL_set_USERLOCATION_data(USERLOCATION *ulac,UINT64 DICid,FILEMETA *DICmetaptr,char *DICpath);//�û��ĵ�ǰ�ļ�ϵͳλ��
extern int GLOBAL_set_USERPROFILE_data(USERPROFILE *upro,
									   char *username,char *password,
									   USERLOCATION *userlocinf,int userprivil,//�û���Ϣ
									   struct tm *createtime//����ʱ��
									   );//�趨�û�����ϢidΪ��һ������id
extern int GLOBAL_set_USERGROUP_data(USERGROUP *ugroup,USERPROFILE *userlist,int groupsize);//�û����趨
extern int GLOBAL_set_SYSTEMUSERPTR_data(SYSTEMUSERPTR *sysuserptr,UINT64 userid,USERPROFILE *userprofileptr);//�趨��ǰ
extern int GLOABL_set_SYSTEMNEXTID_data(IDITEM *systemnextid,
										UINT64 gloregionid,UINT64 glostripid,UINT64 glostripsectid,UINT64 glochunkid,
										UINT64 glodeviceid,UINT64 glodiskid,
										UINT64 glofileid,UINT64 glouserid);//�趨һ�¸����Է����ϵͳ���
extern int GLOBAL_set_GLOSYSTEMID_data(GLOSYSTEMID *systemid,
									UINT64 *regionid,REGIONGROUP *gloregiongroup,int regionnum,
									UINT64 *userid,USERGROUP *glousergroup,int usernum,
									UINT64 *deviceid,DEVICEGROUP *glodevicegroup,int devicenum,
									UINT64 *diskid,DISKGROUP *glodiskgroup,int disknum,
									IDITEM *systemnextid,
									int glopushtime,UINT64 glomaxbuffersize,
									int *availkind,int availnum);
extern int GLOBAL_set_GLODIRTYDATA_data(GLODIRTYDATA *dirtydata,
										CHUNKBLOCK *chunkblockptr,int chunknum,
										STRIPSECTBLOCK *strsetblockptr,int strsectnum,
										STRIPBLOCK *stripblockptr,int stripnum,
										REGIONBLOCK *regionblockptr,int regionnum,
										DEVICEBLOCK *deviceblockptr,int devicenum,
										DISKBLOCK *diskblockptr,int disknum,
										FILEMETABLOCK *filemetablockptr,int filemetanum,
										USERBLOCK *userblockptr,int usernum
										);
extern int GLOBAL_set_UPDATEELEMENT_data(UPDATEELEMENT *updateelementptr,BITELEMENT *bitelementptr,
										SCHEDULE *updateIscheduleptr,BITMATRIX *updateIelementptr,
										SCHEDULE *updateIIscheduleptr,BITMATRIX *updateIIelementptr,
										int stripsecindex,int chunkindex,
										int isupdateI,CHUNK *tempchunkptr,
										int shouldreadnum,int lastindex,
										BITELEMENT *lastdiskelement,int diskshouldread,int isdiskupdateI,
										BITELEMENT *lastmemoryelement,int memoryshouldread,int ismemoryupdateI,
										UPDATEELEMENT *lastupdateelement,int updateshouldread,int isupdateupdateI);
extern int GLOBAL_set_BITELEMENT_data(BITELEMENT *bitelementptr,
										BITMATRIX *elementptr,int stripsectindex,int chunkindex,
										int istarget,SCHEDULE *scheduleptr,
										CHUNK *chunkptr,UINT64 chunkid);
extern int GLOBAL_set_SCHEDULE_data(SCHEDULE *scheduleptr,SCHEDOP *schedlist,int size,int w);

//6ʵ��������
extern CHUNK GLOBAL_create_CHUNK_NULL();//�Զ�����һ����CHUNK���ݽṹ���ұ��Ϊ��һ��Ŀ��
extern STRIPSECT GLOBAL_create_STRIPSECT_NULL();//�Զ�����һ����STRIPSECT���ݽṹ���ұ��Ϊ��һ��Ŀ��
extern STRIP GLOBAL_create_STRIP_NULL();//�Զ�����һ����STRIP���ݽṹ���ұ��Ϊ��һ��Ŀ��
extern DISK GLOBAL_create_DISK_NULL();//�Զ�����һ����DISK���ݽṹ���ұ��Ϊ��һ��Ŀ��
extern DEVICE GLOBAL_create_DEVICE_NULL();//�Զ�����һ����DEVICE���ݽṹ���ұ��Ϊ��һ��Ŀ��
extern REGION GLOBAL_REGION_REGION_NULL();//�Զ�����һ����REGION���ݽṹ���ұ��Ϊ��һ��Ŀ��

//�趨����
//�ڵ���֮����Ҫ����һ���յĶ���
extern int GLOBAL_set_CHUNK_data(CHUNK *chk,int isparity,CHUNKPATH *chkpath,int sizenum,//������Ϣ
								 BYTE* chunkcontent,//����
								 UINT64 regionid,REGION *regionptr,//��һ��region��ָ��
								 UINT64 stripid,STRIP *stripptr,//��һ��strip��ָ��
								 UINT64 stripsectid,STRIPSECT *stripsectptr,//��һ��stripsect��ָ��
								 UINT64 diskid,DISK *diskptr,//��һ��disk��ָ��
								 UINT64 deviceid,DEVICE *deviceptr,//��һ��device��ָ��
								 UINT64 fileid,FILEMETA *fmeta,//�����ļ�Ԫ����
								 int storestate//��ǰ��洢״̬
								 );//�趨��ǰCHUNK�е�����
extern int GLOBAL_set_STRIPSECT_data(STRIPSECT *strsec,
									 int isparity,UINT64 *chunkid,CHUNKGROUP *chunklist,int chunksize,int chunknum,//chunk�б�
									 UINT64 regionid,REGION *regionptr,//��һ��regionָ��
									 UINT64 stripid,STRIP *stripptr,//��һ��stripָ��
									 UINT64 diskid,DISK *diskptr,//��һ��diskָ��
									 UINT64 deviceid,DEVICE *deviceptr,//��һ��deviceָ��
									 char *filename,char *filepath,//·��
									 int storestate//��ǰ�洢״̬
									 );//�趨��ǰSTRIPSECT�е�����
extern int GLOBAL_set_STRIP_data(STRIP *str,STRIPDES *strdes,//��������
								 DISKBLOCK *disklist,UINT64 *diskid,int disknum,//�����洢������
								 DEVICEBLOCK *devicelist,UINT64 *deviceid,int devicenum,//�豸�б�
								 STRIPSECTGROUP *stripsectlist,UINT64 *stripsectid,int strsetnum,//Strset�б�
								 CHUNKGROUP *chunklist,UINT64 *chunkid,int chunknum,//chunk�б�
								 UINT64 regionid,REGION *regionptr,//��һ��regionָ��
								 int storestate//��ǰ�洢״̬
								 );//�趨��ǰSTRIP�е�����
extern int GLOBAL_set_DISK_data(DISK *dis,int DiskTYPE,int capability,UINT64 volumn,
								REGIONBLOCK *regionlist,UINT64 *regionid,int regionnum,//�洢���ϰ�����region����
								DEVICE *deviceptr,UINT64 deviceid,//��һ���device���
								char *diskpath,//�ؼ���Ϣ��ǰ���̵�����·��
								int storestate//��ǰ�洢״̬	
								);//�趨��ǰDISK�е�����
extern int GLOBAL_set_DEVICE_data(DEVICE *div,int Devicetype,int processnum,int *speed,
								  DISKBLOCK *disklist,UINT64 *diskid,int disknum,//�洢���б�
								  REGIONBLOCK *regionlist,UINT64 *regionid,int regionnum,//region�б�
								  int storestate//��ǰ�洢״̬
								  );//�趨��ǰDEVICE�е�����
extern int GLOBAL_set_REGION_data(REGION *reg,int codetype,CODEPARA *codepara,UINT64 totalsize,
								  FILEMETABLOCKGROUP *filemetalist,UINT64 *fileid,int filenum,//������file���б�
								  DISKBLOCK *disklist,UINT64 *diskid,int disknum,//Disk���б�
								  DEVICEBLOCK *devicelist,UINT64 *deviceid,int devicenum,//device�б�
								  STRIPDES *strdes,STRIPGROUP *striplist,UINT64 *stripid,int stripnum,//��������
								  UINT64 chunknum,UINT64 stripsectnum,//chunk��stripsect����
								  FILEMETA *fileroot,UINT64 rootfileid,//���ļ�ָ��
								  int storestate//��ǰ�洢״̬
								  );//�趨��ǰREGION�е�����
//�趨BLOCK��ֵ
extern int GLOBAL_set_CHUNKBLOCK_data(UINT64 chunkid,CHUNK *chkptr);

extern void intial_kind();
extern int isavailkind(int kindid);
extern int reset_state();
//���Ӷ����ͳ�Ʋ���
extern int set_state_memcpynum_add(UINT64 memcpynum);//�����ڴ��ƶ�����
extern int set_state_xor_add(UINT64 xornum);//���������
extern int set_state_w08_add(UINT64 w08num);//����w08������
extern int set_state_w16_add(UINT64 w16num);//����w16������
extern int set_state_w32_add(UINT64 w32num);//����w32������

//���������ͳ�Ʋ���
extern int set_state_NETWORK_send_add(UINT64 sendnum);//�����紫���еķ������ݽ����ۼ�
extern int set_state_NETWORK_rec_add(UINT64 recnum);///�����紫���еķ������ݽ����ۼ�

//������й�ͳ�Ʋ���
extern int set_state_IO_read_add(UINT64 readnum);//��IO��ȡ���ݽ����ۼ�
extern int set_state_IO_write_add(UINT64 writenum);//��IOд�����ݽ����ۼ�

//��ʼ�Ķ�ȫ������
extern int intial_globalid(UINT64 gloregionid,UINT64 glostripid,UINT64 glostripsectid,UINT64 glodeviceid,UINT64 glodiskid,UINT64 glochunkid,UINT64 glofileid,UINT64 glouserid);//��ʼ��ȫ��id
extern int inital_globalid_by_iditem(IDITEM *initaliditem);


extern int set_state_gloregionid_add(UINT64 regnum);//����ϵͳregionid����
extern int set_state_glostripid_add(UINT64 stripnum);//����ϵͳstripid����
extern int set_state_glostripsectid_add(UINT64 stripsectnum);//����ϵͳstripsectid����
extern int set_state_glodeviceid_add(UINT64 devicenum);//����ϵͳdeviceid����
extern int set_state_glodiskid_add(UINT64 disknum);//����ϵͳdiskid����
extern int set_state_glochunkid_add(UINT64 chunknum);//����ϵͳchunkid����
extern int set_state_glofileid_add(UINT64 filenum);//����ϵͳfileid����
extern int set_state_glouserid_add(UINT64 usernum);//����ϵͳuserid����

extern UINT64 get_state_gloregionid();//��ȡϵͳregionid
extern UINT64 get_state_glostripid();//��ȡϵͳstripid
extern UINT64 get_state_glostripsectid();//��ȡϵͳstripsectid
extern UINT64 get_state_glodeviceid();//��ȡϵͳdeviceid
extern UINT64 get_state_glodiskid();//��ȡϵͳdiskid
extern UINT64 get_state_glochunkid();//��ȡϵͳchunkid
extern UINT64 get_state_glofileid();//��ȡϵͳfileid
extern UINT64 get_state_glouserid();//��ȡϵͳuserid

extern STATSITEM *get_stats_PTR();//��ȡ״̬����ָ��
//next_id
extern int set_SYSID_PTR(IDITEM *systemnextid);//�趨ϵͳid��
extern IDITEM *get_SYSID_PTR();//��ȡid����ָ��
//char *Method[N]={""}//defined the order of method


//�趨·�����ݺ�region���ݺ��û�����
extern int set_state_glopath(char *glopath);//�趨ȫ��·��
extern char *get_state_glopath_PTR();//��ȡȫ��·��

//�趨ȫ��device��
//������̬�ı�disk��device�б�,����̫����
extern int set_state_glodevicegroup(DEVICEGROUP *devgroup);//�趨��ǰ��devicegroup
//extern int set_state_glodevicegroup_add(DEVICE *deviceptr);//�ڵ�ǰ��devicegroup�м���һ��device
//extern int set_state_glodevicegroup_del_ID(UINT64 deviceid);//��ָ����devicegroupɾ��device
//extern int set_state_glodevicegroup_del_PTR(DEVICE *deviceptr);//ָ����devicegroupɾ��device
extern DEVICEGROUP *get_state_glodevicegroup_PTR();//�õ���ǰ��devicegroupָ��

//�趨ȫ��disk��
extern int set_state_glodiskgroup(DISKGROUP *diskgroup);//�趨��ǰ��diskgroup
//extern int set_state_glodiskgroup_add(DISK *diskptr);//�ڵ�ǰ��diskgroup�м���һ��disk
//extern int set_state_glodiskgroup_del_ID(UINT64 diskid);//��ָ����diskgroupɾ��disk
//extern int set_state_glodiskgroup_del_PTR(DISK *diskptr);//ָ����diskgroupɾ��disk
extern DISKGROUP *get_state_glodiskgroup_PTR();//�õ���ǰ��diskgroupָ��

//�趨ȫ��id
extern int set_state_glosystemidgroup(GLOSYSTEMID *glosysid);//����ȫ��id·��
extern GLOSYSTEMID *get_state_glosystemidgroup_PTR();//��ȡȫ��id·��

//�趨ȫ��������
extern int set_state_gloregiongroup(REGIONGROUP *reggroup);//�趨��ǰ��regiongroup
extern int set_state_gloregiongroup_add(REGION *regionptr);//�ڵ�ǰ��regiongroup�м���һ��region
extern int set_state_gloregiongroup_del_ID(UINT64 regionid);//��ָ����regiongroupɾ��region
extern int set_state_gloregiongroup_del_PTR(REGION *regionptr);//ָ����regiongroupɾ��region
extern REGIONGROUP *get_state_gloregiongroup_PTR();//�õ���ǰ��regionָ��

//�趨�û���
extern int set_state_glousergroup(USERGROUP *ugroup);//�趨��ǰ�û���
extern int set_state_glousergroup_add(USERPROFILE *userprofileptr);//�ڵ�ǰ��usergroup�м���һ��userprofile
extern int set_state_glousergroup_del_ID(UINT64 userprofileid);//����idɾ��userprofile
extern int set_state_glousergroup_del_PTR(USERPROFILE *userprofileptr);//����ָ��ɾ��userprofile
extern USERGROUP *get_state_glousergroup_PTR();//����ϵͳ�û���ָ��

//�л���ǰ�û�
extern int set_state_glosysuserptr(UINT64 userid,USERPROFILE *useprofileptr);//�趨��ǰϵͳ�û�ָ��
extern int set_state_glosysuserptr_SYSTEMUSERPTR(SYSTEMUSERPTR *sysuserlistptr);//ʹ��ָ�����趨��ǰָ��
extern SYSTEMUSERPTR *get_state_glosysuserptr_PTR();//���ص�ǰϵͳ�û���ָ��
extern UINT64 get_state_glosysuserptr_ID();//���ص�ǰϵͳ�û��ı��
extern USERPROFILE *get_state_glosysuserptr_userprofile();//���ص�ǰ�û���userprofile

//ȫ��Ԫ����·��
extern int set_state_glometapath(char *grometapath);//����ȫ��Ԫ����·��
extern char *get_state_glometapath();//�õ�ȫ��Ԫ����ָ��

//ȫ�ֱ����б��
extern int get_state_avail_kind_number();//��ȡ��������
extern int *get_state_avail_kind();//��ȡ�����б�
extern int set_state_avail_kind_number(int kindnum);//�趨ȫ����������
extern int set_state_avail_kind(int *kindlist);//�趨ȫ����������

//���û�ȡ�������               
extern GLOPUSHLIST *get_state_buffer_pushlist();//��ȡ�������
extern int get_state_buffer_push_time();//����pushtime
extern struct tm *get_state_buffer_last_push_time();//����pushʱ��
extern int set_state_buffer_pushlist(GLOPUSHLIST *gpushlist);//�趨�������
extern int set_state_buffer_push_time(int ptime);//�趨pushtimeʱ��
extern int set_state_buffer_last_push_time(struct tm *ltime);//�趨�ϴ�pushʱ��
extern int set_state_buffer_maxbuffersize(UINT64 maxbuffersize);//maximum��������С
extern int set_state_buffer_currentbuffersize(UINT64 currentbuffersize);//��ǰ��������С
//�趨�ͻ�ȡȫ��dirty��talistָ��
extern GLODIRTYDATA *get_state_dirtydatalist();//��ȡȫ��������ָ��
extern int set_state_dirtydatalist(GLODIRTYDATA *dirtydata);//����ȫ��������ָ��

//��ȡtempfreelist
extern GLOTEMPFREELIST *get_state_tempfreelist();
extern int set_state_tempfreelist(GLOTEMPFREELIST *tempfree);

//��ȡʱ��
extern struct tm *get_system_time();
#endif