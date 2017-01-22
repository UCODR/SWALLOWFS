/*
This program is created by Jiajie Shen 
2014.11.23
沈佳杰创建2014.11.23
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

//文件接口选着
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

//大类
#define Hamming 1
#define reed_sol 2
#define MSR 3
#define MBR 4
#define RAID6 5
#define RAID5 6
#define OTHER 7



//小类
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

//处理器质量
#define mlowlevel 0
#define lowlevel 1
#define midlevel 2
#define highlevel 3
#define mhighlevel 4

//常见符号定义
#define QTRUE 0
#define TRUE 1
#define FALSE 0
#define PARTFALSE 2//用于计算stair错误模式
#define PFALSE -1
//#define NULL -1//列表尚未生成，或是内存为空

//galois算法定义
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

//matrix中定义
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

//存储介质
#define NORHDD 0
#define SSHD 1
#define SSD 2

//存储区域状态
#define EMPTY 0
//这两个状态不用实际计数，chunk中记录当前存在的BYTE数，非chunk中记录下一集已经
#define PART 1
#define FULL 2

//存储器、计算能力定义
#define NONCAP 0//宕机了
#define LOWCAP 1
#define MIDCAP 2
#define HIGHCAP 3

//设备类型定义
#define RACKMAC 0
#define PCMAC 1
#define NASMAC 2 

//文件类型
#define DICTKIND 0
#define FILEKIND 1//归档可以执行一切操作
#define READONLY 2
#define SYSTEMFILE 3
#define HIDEFILE 4

//管理权限，这里从简
#define SYSADMIN 0
#define SYSUSER 1
#define SYSVISITOR 2

//系统配置定义
#define TOTREGIONNUM 35
#define TOTDISKNUMBER 7
#define TOTDEVICENUMBER 7

//校验数据
#define PARITY 1
#define PPARITY 1
#define QPARITY 2

//计算
#define AVAILTRUE 1
#define AVAILFALSE 0
#define AVAILPART 2


//操作类型
#define SYSTEMREPORT 0
#define FILEOPERATION 1

#define FILEUPDATE 0
#define FILEWRITE 1
#define FILEREAD 2
#define	FILEAPPEND 3
#define FILEDELETE 4




//当前错误
#define OPERATIONSUCCESS 0//操作成功
#define FILENOTEXIST 1//删除时文件已经存在
#define FILEUPDATEOVERFINITE 2//更新操作出
#define REGIONISFULL 3//当前文件


//纵向编码的stripsectblock，chunk定义
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

//传输请求格式
typedef struct REQUESTMESSAGE
{
	
	int operationtype;//操作类型
	char sysfilepath[1000];//当前的系统路径
	int size;//在写和更新中代表，在读请求时没有意义
	int offset;//update系统偏移量

}REQUESTMESSAGE;


typedef struct RESPONSEMESSAGE
{
	int stateanswer;//当前回复当前文件状态
	int responsesize;//当前回复数据大小主要用于数据读取
}RESPONSEMESSAGE;

//REED-sol.c定义

//cauchy.c定义
typedef struct INTARRAY
{
	UINT32 *items;
	int size;
}INTARRAY;



//设备编号可以从0开始，还有哥是艺术家，科学家，不是程序猿。
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


//编解码专用
typedef struct INTMATRIX //其中xm,ym为当前w位数下xm，ym
{
	int w;//取值为8,16,32
	int xm;
	int ym;
	UINT32* matrix;//统一为32位//考虑了很久是不是要分成8,16,32位分别存最后发现没有必要
	//如果是bit阵那么xm，ym存储bit位数
}INTMATRIX;//定义一个整型矩阵

typedef struct INTMATRIXGROUP
{
	INTMATRIX *matrix;
	int groupsize;
}INTMATRIXGROUP;

typedef struct DOUMATRIX //其中xm,ym为当前w位数下xm，ym
{
	int w;//取值为8,16,32
	int xm;
	int ym;
	UDOUBLE* matrix32;
	
}DOUMATRIX;//定义一个浮点数矩阵

typedef struct CHUNK 
{
	UINT64 ChunkID;//块编号

	int isparity;//是否是校验块
	struct CHUNKPATH *chkpath;//chunk路径

	int sizenum;//字节数
	BYTE* chunkcontent;//主要原因是chunk的大小是以byte为单位

	UINT64 regionid;//属于的region编号
	struct REGION *regionptr;//上一级region的指针

	UINT64 stripid;//条带id号
	struct STRIP *stripptr;//上一级strip的指针

	UINT64 stripsectid;//条带分区id号
	struct STRIPSECT *stripsectptr;//上一级stripsect的指针

	UINT64 diskid;//属于磁盘的ID
	struct DISK *diskptr;//上一级disk的指针

	UINT64 deviceid;//属于设备的ID
	struct DEVICE *deviceptr;//上一级device的指针

	UINT64 fileid;//文件序号
	struct FILEMETA *fmeta;//文件元数据

	int storestate;//当前块存储状态
}CHUNK;//定义chunk结构体

typedef struct CHUNKGROUP//块组
{
	CHUNK *ckgroup;//列表
	int groupsize;//大小
}CHUNKGROUP;

typedef struct CHUNKBLOCK//chunk块
{
	CHUNK *chunkptr;//chunk指针
	UINT64 chunkid;//chunk编号
}CHUNKBLOCK;

typedef struct CHUNKBLOCKGROUP//chunkblock组
{
	CHUNKBLOCK *chunkblockptr;
	int groupsize;
}CHUNKBLOCKGROUP;

typedef struct CHUNKPOSITIONBLOCK
{
	CHUNK *chunkptr;
	int chunkid;
	int stripsectindex;//datastripsect的位置
	int chunkindex;//在当前strip下是哪一个chunk
}CHUNKPOSITIONBLOCK;

typedef struct CHUNKPOSITIONBLOCKGROUP
{
	CHUNKPOSITIONBLOCK *chunkblockptr;
	int groupsize;
}CHUNKPOSITIONBLOCKGROUP;

typedef struct ERASES//标记需要进行ERASE的设备
{
	int *erases;
	int codenum;//编码块数
	int datanum;//明码块数
	int totnum;//为编码加上明码
}ERASES;
typedef struct ENDECODEPARA//定义编解码参数
{
	int w;//需要进行编解码的域
	INTMATRIX *matrix;//需要的编解码矩阵
}ENDECODEPARA;
typedef struct DOTINF
{
	//记录需要使用的明码数据块和目标存储器
	int *src_ids;//需要计算的chunk号
	int linenum;//对应点乘的行号
	int colsnum;//src_id的行数或是group的数量，取决于src_ids是否为空
	int packetsize;//bitmatrix中的组块大小
	int parityTF;//目标块是否是校验块
	
}DOTINF;
typedef struct DM_IDS
{
	int *dm_ids;//现存设备号
	int size;//大小
}DM_IDS;

typedef struct COST_TIME
{
	clock_t start_time;//开始时间
	clock_t end_time;//结束时间
}COST_TIME;
//统计数据
typedef struct STATSITEM
{
	//计算开销
	UINT64 xornum;//异或数量
	UINT64 w08multnum;//w8乘法
	UINT64 w16multnum;//w16乘法
	UINT64 w32multnum;//w32乘法
	//内存开销
	UINT64 memcpynum;//memcpy数量
	//发送开销
	UINT64 sendnum;//发送数据量
	UINT64 recnum;//接收数据量
	//读写开销
	UINT64 readnum;//从磁盘的读出数据量
	UINT64 writenum;//向磁盘写入数据量
	//实现时间开销
	//编码时间
	COST_TIME EN_time;

	//解码时间
	COST_TIME DE_time;

	//非编码开销时间,overhead
	COST_TIME OVER_time;

	//硬盘读写时间
	COST_TIME IO_time;

	//网络传输时间
	COST_TIME TRANS_time;
}STATSITEM;
//id变量
typedef struct IDITEM
{
//6大全局id编号
	UINT64 gloregionid;//全局region编号
	UINT64 glostripid;//全局strip编号
	UINT64 glostripsectid;//全局stripsection编号
	UINT64 glodeviceid;//全局device编号
	UINT64 glodiskid;//全局disk编号
	UINT64 glochunkid;//全局chunk编号
	UINT64 glofileid;//全局file编号
	UINT64 glouserid;//全局user编号
}IDITEM;

typedef struct SCHEDOP
{
	int op;//需要进行的操作
	int sd;//源存储器,逻辑stripsectindex
	int sb;//源位置,逻辑chunkindex
	int dd;//目标存储器,逻辑stripsectindex
	int db;//目标位置,逻辑chunkindex
	int istareget;//是不是当前需要的目标节点
	CHUNK *tarchunkptr;//目标chunk块
	UINT64 tarchunkid;
}SCHEDOP;

typedef struct SCHEDULE
{
	SCHEDOP *schedlist;//定义操作序列
	int size;//当前调度序列大小
	int w;//当前有
}SCHEDULE;

typedef struct SCHEDULEGROUP
{
	SCHEDULE *schedulegroup;//
	int groupsize;//
}SCHEDULEGROUP;

typedef struct BITELEMENT
{
	BITMATRIX *elementptr;//模式xm为数量
	//逻辑
	int stripsectindex;//第几个stripsect
	int chunkindex;//第几个chunk

	int istarget;//当前的元素是不是目标元素

	SCHEDULE *scheduleptr;//计算序列

	CHUNK *chunkptr;//当前chunk指针
	UINT64 chunkid;//当前chunk的id
}BITELEMENT;

typedef struct BITELEMENTGROUP
{
	BITELEMENT *bitelemetgroup;//当前bitelement指针
	int groupsize;//当前bitelement的大小
}BITELEMENTGROUP;

typedef struct UPDATEELEMENT
{
	BITELEMENT *bitelementptr;//当前bitelement

	SCHEDULE *updateIscheduleptr;//updateI调度序列
	BITMATRIX *updateIelementptr;//updateI的目标element

	SCHEDULE *updateIIscheduleptr;//updateII调度序列
	BITMATRIX *updateIIelementptr;//updateII的目标element

	int stripsecindex;//逻辑stripsectindex
	int chunkindex;//逻辑chunkindex

	int isupdateI;//TRUE代表updateI方案，FALSE代表是updateII,PFALSE代表没有

	CHUNK *tempchunkptr;//当前结果的指针用于记录两个update中间值中的一个
	//BYTE *updatecontentptr;//当前计算的结果内容
	//int sizenum;//当前的块大小

	int shouldreadnum;
	int lastindex;//上一个数据位置,diskindex为0,momeryindex为1和updateindex2

	BITELEMENT *lastdiskelement;//最近的disk元素
	int diskshouldread;//磁盘需要读取的块个数需要加校验块
	int isdiskupdateI;//如果使用disk元素需要的更新方式

	BITELEMENT *lastmemoryelement;//最近的memory元素
	int memoryshouldread;//memnory最少需要读取的块数
	int ismemoryupdateI;//memory使用的更新方式

	struct UPDATEELEMENT *lastupdateelement;//上一个update元素
	int updateshouldread;//update至少需要读取的块数
	int isupdateupdateI;//update使用的更新方式
	
	
}UPDATEELEMENT;

typedef struct UPDATEELEMENTGROUP
{
	UPDATEELEMENT *updategroup;//当前指针
	int groupsize;//大小
}UPDATEELEMENTGROUP;

typedef struct UPDATEELEMENTBLOCK//指针
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

//文件系统结构
//数据结构信息
typedef struct MAPITEM
{
	UINT64 fileid;//文件id
	struct FILEMETA *filemetaptr;//文件指针
	UINT64 deviceid;//设备id
	struct DEVICE *deviceptr;//设备指针
	UINT64 diskid;//存储器id
	struct DISK *diskptr;//存储器指针
	UINT64 stripid; //条带id
	struct STRIP *stripptr;//条带指针
	UINT64 stripsectid;//条带块id
	struct STRIPSECT *stripsectptr;//条带块指针
	UINT64 chunkid;//块id
	struct CHUNK *chunkptr;//块指针
	UINT64 regoinid;//区域id
	struct REGION *regionptr;//区域指针
}MAPITEM;

typedef struct MAPPAIR
{
	MAPITEM *login_item;//逻辑块
	MAPITEM *physic_item;//物理块
}MAPPAIR;

typedef struct CODEPARA//需要的参数
{
	int w;//伽罗华域大小
	int datanum;//k
	int codenum;//m
	int totnum;//n
	int pronum;//d
	int sectornum; //针对扇区编码的块数
}CODEPARA;

//由于条带较为复杂需要增加描述
typedef struct STRIPDES 
{
	int chunknum;//每一个条带包括的行数,即每一个STRIPSECT的chunk数

	struct DISKBLOCK *disklist;//所需的disk列表
	UINT64 *diskid;//当前磁盘id
	int disknum;//存在的即一个条带的列数，磁盘数，通常这个数量和region的disk数一致

	int chunksize;//每一个CHUNK的大小以字节为单位
}STRIPDES;

typedef struct STRIPSECT
{
	UINT64 StripsectID;//STRIPSECT的id

	int isparity;//当前的stripsect是不是用于校验
	UINT64 *chunkid;//	其中包含的chunkid
	CHUNKGROUP *chunklist;//定义一个chunkgroup用具记录chunk组,作为一级chunk指针
	int chunksize;//其中每一个chunk的大小
	int chunknum;//包含的chunk数量总数

	UINT64 regionid;///属于的region编号
	struct REGION *regionptr;//上一级region指针

	UINT64 stripid;//属于的strip编号
	struct STRIP *stripptr;//上一级strip指针

	UINT64 diskid;//属于的disk编号
	struct DISK *diskptr;//上一级disk指针

	UINT64 deviceid;//属于的device编号
	struct DEVICE *deviceptr;//上一级device指针

	char *filename;//文件名
	//veronica中
	char *filepath;//文件名完整路径，这里等于disk中的路径和filename相加

	int storestate;//当前存储状态
}STRIPSECT;

typedef struct STRIPSECTGROUP
{
	STRIPSECT *stripsectgroup;//列表
	int groupsize;//大小
}STRIPSECTGROUP;

typedef struct STRIPSECTBLOCK
{
	STRIPSECT *stripsectptr;//stripsect指针
	UINT64 stripsectid;//stripsect编码
}STRIPSECTBLOCK;

typedef struct STRIPSECTBLOCKGROUP
{
	STRIPSECTBLOCK *stripsectblockptr;//列表
	int groupsize;//大小
}STRIPSECTBLOCKGROUP;

typedef struct STRIP//单个条带信息
{
	UINT64 StripID;//信息

	STRIPDES *strdes;//条带描述，stripdes中chunk数*stripdes中磁盘数=整体包含的chunk数
	
	struct DISKBLOCK *disklist;//存储器列表
	UINT64 *diskid;//包含的存储器id
	int disknum;//包含存储器个数
	//这里device和disk和region中保持,一直至少当前veronica版本一致
	//在注释中有不一致版本
	struct DEVICEBLOCK *devicelist;//设备列表
	UINT64 *deviceid;//设备id
	int devicenum;//设备数
	
	STRIPSECTGROUP *stripsectlist;//stripsect指针
	UINT64 *stripsectid;//stripsect的id
	int strsetnum;//Strset的数量

	CHUNKGROUP *chunklist;//定义一个chunkgroup用具记录chunk组,作为一级chunk指针
	UINT64 *chunkid;//	其中包含的chunkid
	int chunknum;//包含的chunk数量

	UINT64 regionid;//属于的region编号
	struct REGION *regionptr;//上一级region指针

	int storestate;//当前存储状态
}STRIP;

typedef struct STRIPGROUP//条带组
{
	STRIP *stripgroup;//列表
	int groupsize;//大小
}STRIPGROUP;

typedef struct STRIPBLOCK
{
	STRIP *stripptr;//strip指针
	UINT64 stripid;//strip编码
}STRIPBLOCK;

typedef struct STRIPBLOCKGROUP
{
	STRIPBLOCK *stripblockptr;//列表
	int groupsize;//大小
}STRIPBLOCKGROUP;

typedef struct DISK//对于单个逻辑存储器进行描述
{
	UINT64 DiskID;//存储器编号
	int DiskTYPE;//存储器类型
	int capability;//性能能力
	UINT64 volumn;//存储器容量

	struct REGIONBLOCK *regionlist;//指向其中包括的region的指针
	UINT64 *regionid;//存储器上涉及到的region数
	int regionnum;//存储器上包括的region数量

	struct DEVICE *deviceptr;//指向上级device列表
	UINT64 deviceid;//上一层的device编号
	
	char *diskpath;//关键信息当前磁盘的物理路径

	int availstate;//当前可得状态不会出现在元数据存储中，用于read前设置状态
	int storestate;//当前存储状态	
}DISK;

typedef struct DISKGROUP//磁盘组
{
	DISK *diskgroup;//列表
	int groupsize;//大小
}DISKGROUP;

typedef struct DISKBLOCK
{
	DISK *diskptr;//disk指针
	UINT64 diskid;//disk编号
}DISKBLOCK;

typedef struct DEVICE
{
	UINT64 DeviceID;//设备编号
	int Devicetype;//设备类别
	int processnum;//处理器数量
	int *speed;//GHZ

	
	UINT64 *diskid;//设备中存在的存储器
	DISKBLOCK *disklist;//存储设备列表
	int disknum;//存储几个存储器

	struct REGIONBLOCK *regionlist;//region列表
	UINT64 *regionid;//region编号
	int regionnum;//region数量

	int storestate;//当前存储状态
}DEVICE;

typedef struct DEVICEGROUP//设备组
{
	DEVICE *devicegroup;//列表
	int groupsize;//大小
}DEVICEGROUP;

typedef struct DEVICEBLOCK
{
	DEVICE *deviceptr;//列表
	UINT64 deviceid;//大小
}DEVICEBLOCK;

typedef struct REGION//对于逻辑region进行描述
{
	UINT64 RegionID;//region的id
	int codetype;//编码类型
	CODEPARA *codepara;//编码参数
	UINT64 totalsize;//总存储空间大小字节为大小，NODEF代表无限大直至占满

	struct FILEMETABLOCKGROUP *filemetalist;//文件元数据列表,信息较为常用定义group方便查找
	UINT64 *fileid;//包括的file的编号列表
	int filenum;//file数量

	DISKBLOCK *disklist;//Disk列表
	UINT64 *diskid;//Disk的编号列表
	int disknum;//磁盘的个数

	DEVICEBLOCK *devicelist;//device列表
	UINT64 *deviceid;//设备id列表
	int devicenum;//设备数量

	STRIPDES *strdes;//对于条带的描述
	STRIPGROUP *striplist;//Strip列表
	UINT64 *stripid;//条带id列表
	int stripnum;//条带个数
	
	//由于可能很多需要64位数，仅仅用于校验，仅仅用于format
	UINT64 chunknum;//总体chunk数量
	UINT64 stripsectnum;//总体stripsect数量

	struct FILEMETA *fileroot;//当前区域的文件的根指针
	UINT64 rootfileid;//根文件编号

	int storestate;//当前存储状态
}REGION;

typedef struct REGIONGROUP//区域组
{
	REGION *regiongroup;//列表
	int groupsize;//大小
}REGIONGROUP; 

typedef struct REGIONBLOCK
{
	REGION *regionptr;//region指针
	UINT64 regionid;//region编号
}REGIONBLOCK;

typedef struct RUNPATARMETER//系统运行时需要的参数，veronica不对设备进行感知因此DEVIE描述用不到
{
	int appnumber;//申请设备数
	struct DEIVCEGROUP *machinedvice;//设备描述
	int initalstate;//系统是否已初始化
}RUNPATARMETER;

//文件块路径
typedef struct CHUNKPATH//块路径
{
	UINT64 regionid;//regionid全局标号
	int regionarrayid;//之前一次访问值在region表的位置
	REGION *regionptr;//region指针

	UINT64 stripid;//stripid全局标号
	int striparrayid;//之前一次访问值在strip表的位置
	STRIP *stripptr;//strip指针

	UINT64 stripsectid;//stripsect全局标号
	int stripsectarrayid;//之前一次访问值在stripsect表的位置
	STRIPSECT *stripsectptr;//stripsect指针

	UINT64 chunkid;//chenk的全局编号
	int chunkarrayid;//之前一次访问值在chunk表的我位置
	CHUNK *chunkptr;//指向当前chunk
}CHUNKPATH;

//文件块BLOCK
typedef struct CHUNKPATHBLOCK
{
	UINT64 chunkid;
	CHUNKPATH *chunkpath;
}CHUNKPATHBLOCK;

typedef struct CHUNKBLOCKSTRIP
{
	UINT64 stripid;//存放数据
	STRIP *stripptr;

	CHUNKBLOCK *datachunkblockptr;//存放结果
	int chunknum;

//	CHUNKBLOCK *paritychunkblockptr;还是搜索以下
//	int chunknum;
}CHUNKBLOCKSTRIP;

typedef struct CHUNKBLOCKSTRIPGROUP
{
	CHUNKBLOCKSTRIP *chunkblockstripptr;
	int groupsize;
}CHUNKBLOCKSTRIPGROUP;

//文件存储信息
typedef struct FILEINF
{
	UINT64 fileid;//文件ID
	struct FILEMETA *filemeta;//文件元数据返回指针
	UINT64 *chunkid;//源码块列表
	CHUNKPATH *chkpath;//所有chunk的path
	CHUNKBLOCK *chunklist;//块列表
	int chunknum;//chunk数量

	REGION *regoinptr;//region指针
	UINT64 regionid;//属于的region的编号
	
	DEVICEBLOCK *devicelist;//设备列表
	UINT64 *deviceid;//设备id
	int devicenum;//设备数
	
	DISKBLOCK *disklist;//存储器列表
	UINT64 *diskid;//存储器id列表
	int disknum;//存储器数量

	STRIPBLOCK *striplist;//条带列表
	UINT64 *stripid;//条带id列表
	int stripnum;//条带数量

	STRIPSECTBLOCK *stripsectlist;//条带区域列表
	UINT64 *stripsectid;///条带分区id列表
	int stripsectnum;//条带分区数量
}FILEINF;
//FILEMETA指针BLOCK
typedef struct FILEMETABLOCK
{
	UINT64 FileID;
	struct FILEMETA *filemetaptr;
}FILEMETABLOCK;

//FILEMETA指针BLOCK组
typedef struct FILEMETABLOCKGROUP
{
	FILEMETABLOCK *filemetablockptr;
	int groupsize;
}FILEMETABLOCKGROUP;

//文件元数据
typedef struct FILEMETA
{
	UINT64 FileID;//文件ID
	char *filename;//文件名或是目录名
	UINT64 filesize;//文件大小
	int ACList;//文件访问标识
	int filetype;//文件类型,文件还是目录,文件类型,只读归档还是系统

	REGION *regionptr;//上层region指针
	UINT64 regionid;//上层region编号

	struct USERPROFILE *userinf;//文件所有者
	UINT64 userid;//文件所有者id

	UINT64 parentid;//上一级文件夹id
	struct FILEMETA *parentptr;//上一次文件夹
	
	UINT64 *subfileidlist;//子目录列表这里主要仿照linux思想
	struct FILEMETABLOCK *subfilelist;//文件块指针主要指向当前目录下一级元数据块，为了加速
	int subfilenum;//子目录和文件数量

	int curoffset;//当前指针的偏移量无需保持初始化，运行时用

	struct tm *createtime;//创建时间
	struct tm *updatetime;//更新时间

	FILEINF *filechunkinf;//用于存放数据块信息
}FILEMETA;
//文件元数据组
typedef struct FILEMETAGROUP
{
	FILEMETA *filemetagroup;
	int grouposize;
}FILEMETAGROUP;

//用户当前的位置
typedef struct USERLOCATION
{
	UINT64 DICid;//目录id
	FILEMETA *DICmetaptr;//目录元数据
	char *DICpath;//当前目录路径
}USERLOCATION;

//用户信息
typedef struct USERPROFILE
{
	UINT64 UserID;//用户id
	char *username;//用户名
	char *password;//密码
	USERLOCATION *userlocinf;//用户目录位置
	int userprivil;//用户权限
	struct tm *createtime;//账户创建时间
	
}USERPROFILE;

//用户组
typedef struct USERGROUP//用户组
{
	USERPROFILE *userlist;//用户列表
	int groupsize;//大小
}USERGROUP;
//用户指针组
typedef struct USERBLOCK
{
	UINT64 userid;
	USERPROFILE *userprofileptr;
}USERBLOCK;
//当前用户信息
typedef struct SYSTEMUSERPTR
{
	UINT64 userid;//当前系统用户id
	USERPROFILE *userprofileptr;//系统当前用户指针
}SYSTEMUSERPTR;

//全局id信息,regionid,userid,deviceid,diskid
typedef struct GLOSYSTEMID
{
	UINT64 *regionid;//当前region编号列表
	int regionnum;//当前region数量
	REGIONGROUP *gloregiongroup;//当前region列表

	UINT64 *userid;//当前user编号列表
	int usernum;//当前user数量
	USERGROUP *glousergroup;//当前user列表

	UINT64 *deviceid;//当前device编号列表
	int devicenum;//当前device数量
	DEVICEGROUP *glodevicegroup;//当前device列表

	UINT64 *diskid;//当前disk编号列表
	int disknum;//当前disk数量
	DISKGROUP *glodiskgroup;//当前disk列表

	IDITEM *systemnextid;//下一次系统需要分配的id
	
	int glopushtime;//push的时间数
	UINT64 glomaxbuffersize;//最大缓冲区
	//CHUNKGROUP *glopushchunklist;//需要push的数据块组
	int *availkind;//现存编码类型
	int availnum;//编码类型总数
}GLOSYSTEMID;

//当前push列表
typedef struct GLOPUSHLIST
{
	int glopushtime;//push的时间数
	CHUNKBLOCK *glopushchunklist;//需要push的数据块组
	int chunknum;//当前缓冲的chunk数
	UINT64 currentbuffersize;//当前已经缓冲的buffer大小
	UINT64 maxbuffersize;//最大允许缓冲的buffer大小
	struct tm *glolastpushtime;//上一次push时间
}GLOPUSHLIST;

//用于修改数据同步,记录脏数据
typedef struct GLODIRTYDATA
{
	//几个元数据实体
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
	BITMATRIX *bitmatrix;//用于记录错误模式，磁盘校验为一行，块校验需要根据定义处理，失效为TRUE，没错为FALSE
	int errordisknum;//出错磁盘个数
	int errorchunknum;//出错chunknum个数，磁盘校验无意义
}ERRORPATTERN;

typedef struct GLOTEMPFREELIST//主要用于记录当前过程中读到内存
{
	CHUNKBLOCK *chunkblockptr;//当前需要释放的列表
	int tempnum;//数量当前缓冲的读取块
}GLOTEMPFREELIST;

typedef struct AONTSHARE//定义当前安全存储中的SHARE
{
	char *storepath;
	CODEPARA *codeptr;//当前编码参数
	BYTE *content;//需要写入的内容 
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
	CODEPARA *codeptr;//编码参数指针
	SHAREADDRESS *addressptr;//存储地址组
}ADDRESSLIST;

typedef struct TRACEITEM 
{
	int opertype;
	UINT64 offset;//偏移量一遍较大
	int length;
	char *filename;//文件名
}TRACEITEM;



extern void intial();


#define talloc(type,num) (type *)malloc(sizeof(type)*num)//分配存储空间
#define ralloc(type,num,point) (type *)realloc(point,sizeof(type)*num)//重新分配内存空间
#define mcpy(point1,point2,type,num) memcpy(point1,point2,sizeof(type)*num)

#define show_error(part,func,desc) fprintf(stderr,"filename:%s,function:%s,description:%s\n",part,func,desc)//记录错误信息

#define show_message(mcontent) printf("%s\n",mcontent)

#define codetype(type1,type2) (type1*1000+type2)//计算类别序号
#define maintype(codetype) (int)(codetype/1000)//计算主要编号主要是mapper中要用
#define subtype(codetype) (int)(codetype%1000)//计算编号主要使用no-use

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

#define caldevice(cols,w) cols/w//通过数据进行计算明码设备数k

#define bzero(matrix,type,sizenum) memset(matrix,0,sizeof(type)*sizenum) 
#define mset(matrix,type,number,sizenum) memset(matrix,number,sizeof(type)*sizenum)

#define randomnumber01 rand()/RAND_MAX

//这里要注意不要连续乘c++对于连续乘不支持
#define chksize_KB(kbyte) (kbyte*1024)//以KB为单位计算chunksize
#define chksize_MB(mbyte) (mbyte*1048576)//以MB为单位计算chunksize

//这里必须先强行转64位否则编译器有一定概率会报错
#define chksize_GB(gbyte) ((UINT64)gbyte*(UINT64)1073741824)//以GB为单位计算chunksize
#define chksize_TB(tbyte) ((UINT64)tbyte*(UINT64)1099511627776)//以TB为单位计算大小

#define STRTOINT64(charstring,int64str) sscanf(charstring,"%I64d",&int64str);
#define STRTOINT32(charstring,int32str) sscanf(charstring,"%d",&int32str);

static STATSITEM systemstatic;//系统统计信息
static IDITEM systemid;//系统id信息

static DEVICEGROUP grodevicelist;

static DISKGROUP grodisklist;//当前系统存在的disk列表

static REGIONGROUP groregionlist;//当前系统REGION列表

static USERGROUP grouserlist;//当前系统用户列表

static char *grometadatapath;//全局元数据
static SYSTEMUSERPTR sysuserptr;//全局系统用户指针

static GLOSYSTEMID grosysid;//仅仅在初始化时，使用运行时以系统GROUP为准，同步时也以系统group为准

static GLOPUSHLIST gropushlist;//pushlist包含push用的信息

static GLODIRTYDATA grodirtydatalist;//脏数据列表

static GLOTEMPFREELIST grotempfreelistptr;//当前需要释放的数据块指正

static int *availkind;//现存编码类型
static int availnum=0;//编码类型总数

//描述信息构造
extern MAPITEM GLOBAL_create_MAPITEM_NULL();//自动返回一个空MAPITEM数据结构
extern MAPPAIR GLOBAL_create_MAPPAIR_NULL();//自动返回一个空MAPPAIR数据结构
extern CODEPARA GLOBAL_create_CODEPARA_NULL();//自动返回一个空CODEPARA数据结构
extern STRIPDES GLOBAL_create_STRIPDES_NULL();//自动返回一个空STRIPDES数据结构
extern CHUNKGROUP GLOBAL_create_CHUNKGROUP_NULL();//自动返回一个空CHUNKGROUP数据结构
extern STRIPSECTGROUP GLOBAL_create_STRIPSECTGROUP_NULL();//自动返回一个空STRIPSECTGROUP数据结构
extern STRIPGROUP GLOBAL_create_STRIPGROUP_NULL();//自动返回一个空STRIPGROUP数据结构
extern DISKGROUP GLOBAL_create_DISKGROUP_NULL();//自动返回一个空DISKGROUP数据结构
extern DEVICEGROUP GLOBAL_create_DEVICEGROUP_NULL();//自动返回一个空DEVICEGROUP数据结构
extern REGIONGROUP GLOBAL_create_REGIONGROUP_NULL();//自动返回一个空REGIONGROUP数据结构
extern RUNPATARMETER GLOBAL_create_RUNPATARMETER_NULL();//自动返回一个空RUNPATARMETER数据结构
extern CHUNKPATH GLOBAL_create_CHUNKPATH_NULL();//自动返回一个空CHUNKPATH数据结构
extern FILEINF GLOBAL_create_FILEINF_NULL();//自动返回一个空FILEINF数据结构
extern FILEMETA GLOBAL_create_FILEMETA_NULL();//自动返回一个空FILEMETA数据结构,fileid指向下一个fileid
extern USERLOCATION GLOBAL_create_USERLOCATION_NULL();//自动返回一个空USERLOCATION数据结构
extern USERPROFILE GLOBAL_create_USERPROFILE_NULL();//自动返回一个空USERPROFILE数据结构
extern USERGROUP GLOBAL_create_USERGROUP_NULL();//自动返回一个空USERGROUP数据结构
extern SYSTEMUSERPTR GLOBAL_create_SYSTEMUSERPTR_NULL();//自动返回一个空SYSTEMUSERPTR数据结构

//描述信息构造函数
extern int GLOBAL_set_time(struct tm *timeptr,
							int createtime1,int createtime2,int createtime3,int createtime4,int createtime5,
							int createtime6,int createtime7,int createtime8,
							int createtime9);
extern int GLOBAL_set_MAPITEM_data(MAPITEM *mitem,UINT64 fileid,FILEMETA *filemetaptr,//文件指针
								   UINT64 deviceid,DEVICE *deviceptr,//设备指针
								   UINT64 diskid,DISK *diskptr,//存储器指针
								   UINT64 stripid,STRIP *stripptr,//条带指针
								   UINT64 stripsectid,STRIPSECT *stripsectptr,//条带块指针
								   UINT64 chunkid,CHUNK *chunkptr,//块指针
								   UINT64 regoinid,REGION *regionptr//区域指针
								   );//设定MAPITEM数据值
extern int GLOBAL_set_MAPPAIR_data(MAPPAIR *mpair,
								   MAPITEM *login_item,MAPITEM *physic_item//物理块
								   );//设定MAPPAIR数据值
extern int GLOBAL_set_CODEPARA_data(CODEPARA *cpara,
									int w,//伽罗华域大小
									int datanum,//k
									int codenum,//m
									int totnum,//n
									int pronum,//d
									int sectornum//针对扇区编码的块数
									);//设定CODEPARA数据值
extern int GLOBAL_set_STRIPDES_data(STRIPDES *strdes,
									int chunknum,//每一个条带包括的行数,即chunk数
									DISKBLOCK *disklist,//所需的disk列表
									UINT64 *diskid,//当前磁盘id
									int disknum,//存在的即一个条带的列数，磁盘数，通常这个数量和region的disk数一致
									int chunksize//每一个CHUNK的大小以字节为单位
									);//设定STRIPDES数据值
extern int GLOBAL_set_CHUNKGROUP_data(CHUNKGROUP *chkgroup,
									  CHUNK *ckgroup,//列表
									  int groupsize//大小
									  );//设定CHUNKGROUP数据值
extern int GLOBAL_set_STRIPSECTGROUP_data(STRIPSECTGROUP *strsetgroup,
										  STRIPSECT *stripsectgroup,//列表
										  int groupsize//大小
										  );//设定STRIPSECTGROUP数据值
extern int GLOBAL_set_STRIPGROUP_data(STRIPGROUP *strgroup,
									  STRIP *stripgroup,//列表
									  int groupsize//大小
									  );//设定STRIPGROUP数据值
extern int GLOBAL_set_DISKGROUP_data(DISKGROUP *disgroup,
									 DISK *diskgroup,//列表
									 int groupsize//大小
									 );//设定DISKGROUP数据值
extern int GLOBAL_set_DEVICEGROUP_data(DEVICEGROUP *devgroup,
									   DEVICE *devicegroup,//列表
									   int groupsize//大小
									   );//设定DEVICEGROUP数据值
extern int GLOBAL_set_REGIONGROUP_data(REGIONGROUP *reggroup,
									   REGION *regiongroup,//列表
									   int groupsize//大小
									   );//设定REGIONGROUP数据值
extern int GLOBAL_set_CHUNKPATH_data(CHUNKPATH *chkpath,
									 UINT64 regionid,int regionarrayid,REGION *regionptr,//region指针
									 UINT64 stripid,int striparrayid,STRIP *stripptr,//strip指针
									 UINT64 stripsectid,int stripsectarrayid,STRIPSECT *stripsectptr,//stripsect指针
									 UINT64 chunkid,int chunkarrayid,CHUNK *chunkptr//指向当前chunk
									 );//设定CHUNKPATH数据值
extern int GLOBAL_set_FILEINF_data(FILEINF *finf,UINT64 fileid,UINT64 *chunkid,FILEMETA *filemeta,
								   CHUNKPATH *chkpath,CHUNKBLOCK *chunklist,int chunknum,//chun列表
								   REGION *regionptr,UINT64 regionid,//region指针
								   DEVICEBLOCK *devicelist,UINT64 *deviceid,int devicenum,//设备列表
								   DISKBLOCK *disklist,UINT64 *diskid,int disknum,//存储器列表
								   STRIPBLOCK *striplist,UINT64 *stripid,int stripnum,//条带列表
								   STRIPSECTBLOCK *stripsectlist,UINT64 *stripsectid,int stripsectnum//条带区域列表
								   );//设定FILEINF数据值
extern int GLOBAL_set_FILEMETA_data(FILEMETA *fmeta,char *filename,UINT64 filesize,int ACList,int filetype,
									REGION *regionptr,UINT64 regionid,//上层region指针
									struct USERPROFILE *userinf,UINT64 userid,//文件所有者
									UINT64 parentid,FILEMETA *parentptr,//上一层文件夹
									UINT64 *subfileidlist,FILEMETABLOCK *subfilelist,int subfilenum,//文件块指针主要指向当前目录下一级元数据块
									struct tm *createtime,
									struct tm *updatetime,
									FILEINF *filechunkinf//用于存放数据块信息
									);//设定FILEMETA数据值
extern int GLOBAL_set_USERLOCATION_data(USERLOCATION *ulac,UINT64 DICid,FILEMETA *DICmetaptr,char *DICpath);//用户的当前文件系统位置
extern int GLOBAL_set_USERPROFILE_data(USERPROFILE *upro,
									   char *username,char *password,
									   USERLOCATION *userlocinf,int userprivil,//用户信息
									   struct tm *createtime//创建时间
									   );//设定用户的信息id为下一个可用id
extern int GLOBAL_set_USERGROUP_data(USERGROUP *ugroup,USERPROFILE *userlist,int groupsize);//用户组设定
extern int GLOBAL_set_SYSTEMUSERPTR_data(SYSTEMUSERPTR *sysuserptr,UINT64 userid,USERPROFILE *userprofileptr);//设定当前
extern int GLOABL_set_SYSTEMNEXTID_data(IDITEM *systemnextid,
										UINT64 gloregionid,UINT64 glostripid,UINT64 glostripsectid,UINT64 glochunkid,
										UINT64 glodeviceid,UINT64 glodiskid,
										UINT64 glofileid,UINT64 glouserid);//设定一下个可以分配的系统编号
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

//6实体参数规格化
extern CHUNK GLOBAL_create_CHUNK_NULL();//自动返回一个空CHUNK数据结构并且标号为下一个目标
extern STRIPSECT GLOBAL_create_STRIPSECT_NULL();//自动返回一个空STRIPSECT数据结构并且标号为下一个目标
extern STRIP GLOBAL_create_STRIP_NULL();//自动返回一个空STRIP数据结构并且标号为下一个目标
extern DISK GLOBAL_create_DISK_NULL();//自动返回一个空DISK数据结构并且标号为下一个目标
extern DEVICE GLOBAL_create_DEVICE_NULL();//自动返回一个空DEVICE数据结构并且标号为下一个目标
extern REGION GLOBAL_REGION_REGION_NULL();//自动返回一个空REGION数据结构并且标号为下一个目标

//设定参数
//在调用之间需要创建一个空的对象
extern int GLOBAL_set_CHUNK_data(CHUNK *chk,int isparity,CHUNKPATH *chkpath,int sizenum,//基本信息
								 BYTE* chunkcontent,//内容
								 UINT64 regionid,REGION *regionptr,//上一级region的指针
								 UINT64 stripid,STRIP *stripptr,//上一级strip的指针
								 UINT64 stripsectid,STRIPSECT *stripsectptr,//上一级stripsect的指针
								 UINT64 diskid,DISK *diskptr,//上一级disk的指针
								 UINT64 deviceid,DEVICE *deviceptr,//上一级device的指针
								 UINT64 fileid,FILEMETA *fmeta,//属于文件元数据
								 int storestate//当前块存储状态
								 );//设定当前CHUNK中的数据
extern int GLOBAL_set_STRIPSECT_data(STRIPSECT *strsec,
									 int isparity,UINT64 *chunkid,CHUNKGROUP *chunklist,int chunksize,int chunknum,//chunk列表
									 UINT64 regionid,REGION *regionptr,//上一级region指针
									 UINT64 stripid,STRIP *stripptr,//上一级strip指针
									 UINT64 diskid,DISK *diskptr,//上一级disk指针
									 UINT64 deviceid,DEVICE *deviceptr,//上一级device指针
									 char *filename,char *filepath,//路径
									 int storestate//当前存储状态
									 );//设定当前STRIPSECT中的数据
extern int GLOBAL_set_STRIP_data(STRIP *str,STRIPDES *strdes,//条带描述
								 DISKBLOCK *disklist,UINT64 *diskid,int disknum,//包含存储器个数
								 DEVICEBLOCK *devicelist,UINT64 *deviceid,int devicenum,//设备列表
								 STRIPSECTGROUP *stripsectlist,UINT64 *stripsectid,int strsetnum,//Strset列表
								 CHUNKGROUP *chunklist,UINT64 *chunkid,int chunknum,//chunk列表
								 UINT64 regionid,REGION *regionptr,//上一级region指针
								 int storestate//当前存储状态
								 );//设定当前STRIP中的数据
extern int GLOBAL_set_DISK_data(DISK *dis,int DiskTYPE,int capability,UINT64 volumn,
								REGIONBLOCK *regionlist,UINT64 *regionid,int regionnum,//存储器上包括的region数量
								DEVICE *deviceptr,UINT64 deviceid,//上一层的device编号
								char *diskpath,//关键信息当前磁盘的物理路径
								int storestate//当前存储状态	
								);//设定当前DISK中的数据
extern int GLOBAL_set_DEVICE_data(DEVICE *div,int Devicetype,int processnum,int *speed,
								  DISKBLOCK *disklist,UINT64 *diskid,int disknum,//存储器列表
								  REGIONBLOCK *regionlist,UINT64 *regionid,int regionnum,//region列表
								  int storestate//当前存储状态
								  );//设定当前DEVICE中的数据
extern int GLOBAL_set_REGION_data(REGION *reg,int codetype,CODEPARA *codepara,UINT64 totalsize,
								  FILEMETABLOCKGROUP *filemetalist,UINT64 *fileid,int filenum,//包括的file的列表
								  DISKBLOCK *disklist,UINT64 *diskid,int disknum,//Disk的列表
								  DEVICEBLOCK *devicelist,UINT64 *deviceid,int devicenum,//device列表
								  STRIPDES *strdes,STRIPGROUP *striplist,UINT64 *stripid,int stripnum,//条带个数
								  UINT64 chunknum,UINT64 stripsectnum,//chunk和stripsect总数
								  FILEMETA *fileroot,UINT64 rootfileid,//根文件指针
								  int storestate//当前存储状态
								  );//设定当前REGION中的数据
//设定BLOCK赋值
extern int GLOBAL_set_CHUNKBLOCK_data(UINT64 chunkid,CHUNK *chkptr);

extern void intial_kind();
extern int isavailkind(int kindid);
extern int reset_state();
//复杂度相关统计参数
extern int set_state_memcpynum_add(UINT64 memcpynum);//计算内存移动数量
extern int set_state_xor_add(UINT64 xornum);//增加异或数
extern int set_state_w08_add(UINT64 w08num);//增加w08计算数
extern int set_state_w16_add(UINT64 w16num);//增加w16计算数
extern int set_state_w32_add(UINT64 w32num);//增加w32计算数

//与网络相关统计参数
extern int set_state_NETWORK_send_add(UINT64 sendnum);//将网络传输中的发送数据进行累加
extern int set_state_NETWORK_rec_add(UINT64 recnum);///将网络传输中的发送数据进行累加

//与磁盘有关统计参数
extern int set_state_IO_read_add(UINT64 readnum);//将IO读取数据进行累加
extern int set_state_IO_write_add(UINT64 writenum);//将IO写入数据进行累加

//开始改动全局数据
extern int intial_globalid(UINT64 gloregionid,UINT64 glostripid,UINT64 glostripsectid,UINT64 glodeviceid,UINT64 glodiskid,UINT64 glochunkid,UINT64 glofileid,UINT64 glouserid);//初始化全局id
extern int inital_globalid_by_iditem(IDITEM *initaliditem);


extern int set_state_gloregionid_add(UINT64 regnum);//对于系统regionid增加
extern int set_state_glostripid_add(UINT64 stripnum);//对于系统stripid增加
extern int set_state_glostripsectid_add(UINT64 stripsectnum);//对于系统stripsectid增加
extern int set_state_glodeviceid_add(UINT64 devicenum);//对于系统deviceid增加
extern int set_state_glodiskid_add(UINT64 disknum);//对于系统diskid增加
extern int set_state_glochunkid_add(UINT64 chunknum);//对于系统chunkid增加
extern int set_state_glofileid_add(UINT64 filenum);//对于系统fileid增加
extern int set_state_glouserid_add(UINT64 usernum);//对于系统userid增加

extern UINT64 get_state_gloregionid();//获取系统regionid
extern UINT64 get_state_glostripid();//获取系统stripid
extern UINT64 get_state_glostripsectid();//获取系统stripsectid
extern UINT64 get_state_glodeviceid();//获取系统deviceid
extern UINT64 get_state_glodiskid();//获取系统diskid
extern UINT64 get_state_glochunkid();//获取系统chunkid
extern UINT64 get_state_glofileid();//获取系统fileid
extern UINT64 get_state_glouserid();//获取系统userid

extern STATSITEM *get_stats_PTR();//获取状态数据指针
//next_id
extern int set_SYSID_PTR(IDITEM *systemnextid);//设定系统id号
extern IDITEM *get_SYSID_PTR();//获取id数据指针
//char *Method[N]={""}//defined the order of method


//设定路径数据和region数据和用户数据
extern int set_state_glopath(char *glopath);//设定全局路径
extern char *get_state_glopath_PTR();//获取全局路径

//设定全局device组
//不允许动态改变disk和device列表,否则太复杂
extern int set_state_glodevicegroup(DEVICEGROUP *devgroup);//设定当前的devicegroup
//extern int set_state_glodevicegroup_add(DEVICE *deviceptr);//在当前的devicegroup中加入一个device
//extern int set_state_glodevicegroup_del_ID(UINT64 deviceid);//将指定的devicegroup删除device
//extern int set_state_glodevicegroup_del_PTR(DEVICE *deviceptr);//指定的devicegroup删除device
extern DEVICEGROUP *get_state_glodevicegroup_PTR();//得到当前的devicegroup指针

//设定全局disk组
extern int set_state_glodiskgroup(DISKGROUP *diskgroup);//设定当前的diskgroup
//extern int set_state_glodiskgroup_add(DISK *diskptr);//在当前的diskgroup中加入一个disk
//extern int set_state_glodiskgroup_del_ID(UINT64 diskid);//将指定的diskgroup删除disk
//extern int set_state_glodiskgroup_del_PTR(DISK *diskptr);//指定的diskgroup删除disk
extern DISKGROUP *get_state_glodiskgroup_PTR();//得到当前的diskgroup指针

//设定全局id
extern int set_state_glosystemidgroup(GLOSYSTEMID *glosysid);//设置全局id路径
extern GLOSYSTEMID *get_state_glosystemidgroup_PTR();//获取全局id路径

//设定全局区域组
extern int set_state_gloregiongroup(REGIONGROUP *reggroup);//设定当前的regiongroup
extern int set_state_gloregiongroup_add(REGION *regionptr);//在当前的regiongroup中加入一个region
extern int set_state_gloregiongroup_del_ID(UINT64 regionid);//将指定的regiongroup删除region
extern int set_state_gloregiongroup_del_PTR(REGION *regionptr);//指定的regiongroup删除region
extern REGIONGROUP *get_state_gloregiongroup_PTR();//得到当前的region指针

//设定用户组
extern int set_state_glousergroup(USERGROUP *ugroup);//设定当前用户组
extern int set_state_glousergroup_add(USERPROFILE *userprofileptr);//在当前的usergroup中加入一个userprofile
extern int set_state_glousergroup_del_ID(UINT64 userprofileid);//根据id删除userprofile
extern int set_state_glousergroup_del_PTR(USERPROFILE *userprofileptr);//根据指针删除userprofile
extern USERGROUP *get_state_glousergroup_PTR();//返回系统用户组指针

//切换当前用户
extern int set_state_glosysuserptr(UINT64 userid,USERPROFILE *useprofileptr);//设定当前系统用户指针
extern int set_state_glosysuserptr_SYSTEMUSERPTR(SYSTEMUSERPTR *sysuserlistptr);//使用指针来设定当前指针
extern SYSTEMUSERPTR *get_state_glosysuserptr_PTR();//返回当前系统用户的指针
extern UINT64 get_state_glosysuserptr_ID();//返回当前系统用户的编号
extern USERPROFILE *get_state_glosysuserptr_userprofile();//返回当前用户的userprofile

//全局元数据路径
extern int set_state_glometapath(char *grometapath);//设置全局元数据路径
extern char *get_state_glometapath();//得到全局元数据指针

//全局编码列表号
extern int get_state_avail_kind_number();//获取种类数量
extern int *get_state_avail_kind();//获取种类列表
extern int set_state_avail_kind_number(int kindnum);//设定全局种类数量
extern int set_state_avail_kind(int *kindlist);//设定全局种类类型

//设置获取缓冲队列               
extern GLOPUSHLIST *get_state_buffer_pushlist();//获取缓冲队列
extern int get_state_buffer_push_time();//设置pushtime
extern struct tm *get_state_buffer_last_push_time();//设置push时间
extern int set_state_buffer_pushlist(GLOPUSHLIST *gpushlist);//设定缓冲队列
extern int set_state_buffer_push_time(int ptime);//设定pushtime时间
extern int set_state_buffer_last_push_time(struct tm *ltime);//设定上次push时间
extern int set_state_buffer_maxbuffersize(UINT64 maxbuffersize);//maximum缓冲区大小
extern int set_state_buffer_currentbuffersize(UINT64 currentbuffersize);//当前缓冲区大小
//设定和获取全局dirty大talist指针
extern GLODIRTYDATA *get_state_dirtydatalist();//获取全局脏数据指针
extern int set_state_dirtydatalist(GLODIRTYDATA *dirtydata);//设置全局脏数据指针

//获取tempfreelist
extern GLOTEMPFREELIST *get_state_tempfreelist();
extern int set_state_tempfreelist(GLOTEMPFREELIST *tempfree);

//获取时间
extern struct tm *get_system_time();
#endif