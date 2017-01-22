/*
This program is created by Jiajie Shen 
2014.11.26
沈佳杰创建2014.11.26
*/
/*
global_define.h用于初始化系统参数实现类别等等
*/

#include "global_define.h"

//普通数据结构
MAPITEM GLOBAL_create_MAPITEM_NULL()//自动返回一个空MAPITEM数据结构
{
	MAPITEM mitem;
	mitem.fileid=NOVALUE;//文件id
	mitem.filemetaptr=NULL;//文件指针
	mitem.deviceid;//设备id
	mitem.deviceptr=NULL;//设备指针
	mitem.diskid=NOVALUE;//存储器id
	mitem.diskptr;//存储器指针
	mitem.stripid; //条带id
	mitem.stripptr;//条带指针
	mitem.stripsectid;//条带块id
	mitem.stripsectptr;///条带块指针
	mitem.chunkid;//块id
	mitem.chunkptr;//块指针
	mitem.regoinid;//区域id
	mitem.regionptr;//区域指针
	return mitem;
}
MAPPAIR GLOBAL_create_MAPPAIR_NULL()//自动返回一个空MAPPAIR数据结构
{
	MAPPAIR mpair;
	mpair.login_item=NULL;
	mpair.physic_item=NULL;
	return mpair;
}
CODEPARA GLOBAL_create_CODEPARA_NULL()//自动返回一个空CHUNK数据结构
{
	CODEPARA cparam;
	cparam.codenum=NOVALUE;
	cparam.datanum=NOVALUE;
	cparam.pronum=NOVALUE;
	cparam.sectornum=NOVALUE;
	cparam.totnum=NOVALUE;
	return cparam;
}
STRIPDES GLOBAL_create_STRIPDES_NULL()//自动返回一个空STRIPDES数据结构
{
	STRIPDES strdes;

	strdes.chunknum=NOVALUE;//stripsectchunk数

	strdes.disklist=NULL;
	strdes.diskid=NULL;
	strdes.disknum=NOVALUE;//strip中使用的磁盘个数

	strdes.chunksize=NOSIZE;//chunk大小

	return strdes;
}
CHUNKGROUP GLOBAL_create_CHUNKGROUP_NULL()//自动返回一个空CHUNKGROUP数据结构
{
	CHUNKGROUP chkgroup;
	chkgroup.ckgroup=NULL;
	chkgroup.groupsize=NOSIZE;
	return chkgroup;
}
STRIPSECTGROUP GLOBAL_create_STRIPSECTGROUP_NULL()//自动返回一个空STRIPSECTGROUP数据结构
{
	STRIPSECTGROUP strsetgroup;
	strsetgroup.stripsectgroup=NULL;
	strsetgroup.groupsize=NOSIZE;
	return strsetgroup;
}
STRIPGROUP GLOBAL_create_STRIPGROUP_NULL()//自动返回一个空STRIPGROUP数据结构
{
	STRIPGROUP stripgroup;
	stripgroup.stripgroup=NULL;
	stripgroup.groupsize=NOVALUE;
	return stripgroup;
}
DISKGROUP GLOBAL_create_DISKGROUP_NULL()//自动返回一个空DISKGROUP数据结构
{
	DISKGROUP dgroup;
	dgroup.diskgroup=NULL;
	dgroup.groupsize=NOSIZE;
	return dgroup;
}
DEVICEGROUP GLOBAL_create_DEVICEGROUP_NULL()//自动返回一个空DEVICEGROUP数据结构
{
	DEVICEGROUP devgroup;
	devgroup.devicegroup=NULL;
	devgroup.groupsize=NOSIZE;
	return devgroup;
}
REGIONGROUP GLOBAL_create_REGIONGROUP_NULL()//自动返回一个空REGIONGROUP数据结构
{
	REGIONGROUP reggroup;
	reggroup.regiongroup=NULL;
	reggroup.groupsize=NOSIZE;
	return reggroup;
}
RUNPATARMETER GLOBAL_create_RUNPATARMETER_NULL()//自动返回一个空RUNPATARMETER数据结构
{
	RUNPATARMETER rpmeter;
	rpmeter.appnumber=NOVALUE;
	rpmeter.initalstate=NOVALUE;
	rpmeter.machinedvice=NULL;
	return rpmeter;
}
CHUNKPATH GLOBAL_create_CHUNKPATH_NULL()//自动返回一个空CHUNKPATH数据结构
{
	CHUNKPATH chkpath;
	
	chkpath.regionarrayid=NOVALUE;
	chkpath.regionid=NOVALUE;
	chkpath.regionptr=NULL;

	chkpath.striparrayid=NOVALUE;
	chkpath.stripid=NOVALUE;
	chkpath.stripptr=NULL;

	chkpath.stripsectarrayid=NOVALUE;
	chkpath.stripsectid=NOVALUE;
	chkpath.stripsectptr=NULL;

	chkpath.chunkarrayid=NOVALUE;
	chkpath.chunkid=NOVALUE;
	chkpath.chunkptr=NULL;
	return chkpath;

}
FILEINF GLOBAL_create_FILEINF_NULL()//自动返回一个空FILEINF数据结构
{
	FILEINF finf;

	finf.fileid=NOVALUE;
	finf.filemeta=NULL;

	finf.chunklist=NULL;
	finf.chkpath=NULL;
	finf.chunkid=NULL;
	finf.chunknum=NOSIZE;

	finf.devicelist=NULL;
	finf.deviceid=NULL;
	finf.devicenum=NOSIZE;
	
	
	finf.disklist=NULL;
	finf.diskid=NULL;
	finf.disknum=NOSIZE;

	finf.regionid=NOVALUE;
	finf.regoinptr=NULL;

	finf.striplist=NULL;
	finf.stripid=NULL;
	finf.stripnum=NOSIZE;

	finf.stripsectlist=NULL;
	finf.stripsectid=NULL;
	finf.stripsectnum=NOSIZE;
	return finf;
}
FILEMETA GLOBAL_create_FILEMETA_NULL()//自动返回一个空FILEMETA数据结构,同时fileid指向下一个可用id
{
	FILEMETA fmeta;

	fmeta.ACList=NOVALUE;
	fmeta.filechunkinf=NULL;
	fmeta.filename=NULL;
	fmeta.filesize=NOSIZE;

	fmeta.regionptr=NULL;
	fmeta.regionid=NOVALUE;

	fmeta.userinf=NULL;
	fmeta.userid=NOVALUE;

	fmeta.parentptr=NULL;
	fmeta.parentid=NOVALUE;

	fmeta.subfileidlist=NULL;
	fmeta.subfilelist=NULL;
	fmeta.subfilenum=NOSIZE;

	fmeta.createtime=NULL;
	fmeta.updatetime=NULL;

	//最后设定编号
	fmeta.FileID=get_state_glostripid();
	set_state_glofileid_add(1);
	return fmeta;
}
//自动返回一个空USERLOCATION数据结构
USERLOCATION GLOBAL_create_USERLOCATION_NULL()
{
	USERLOCATION ulac;
	ulac.DICid=NOVALUE;
	ulac.DICmetaptr=NULL;
	ulac.DICpath=NULL;
	return ulac;
}
//自动返回一个空USERPROFILE数据结构
USERPROFILE GLOBAL_create_USERPROFILE_NULL()
{
	USERPROFILE upro;
	upro.username=NULL;
	upro.password=NULL;
	upro.userlocinf=NULL;
	upro.userprivil=NOVALUE;
	//最后设定编号
	upro.UserID=get_state_glouserid();
	set_state_glouserid_add(1);
	return upro;
}
USERGROUP GLOBAL_create_USERGROUP_NULL()
{
	USERGROUP ugroup;
	ugroup.userlist=NULL;
	ugroup.groupsize=NOSIZE;
	return ugroup;
}
SYSTEMUSERPTR GLOBAL_create_SYSTEMUSERPTR_NULL()//自动返回一个空SYSTEMUSERPTR数据结构
{
	SYSTEMUSERPTR sysuserptr;
	sysuserptr.userid=NOVALUE;
	sysuserptr.userprofileptr=NULL;
	return sysuserptr;
}
//设定辅助数据结构值
int GLOBAL_set_time(struct tm *timeptr,
							int createtime1,int createtime2,int createtime3,int createtime4,int createtime5,
							int createtime6,int createtime7,int createtime8,
							int createtime9)
{
	timeptr->tm_year=createtime1;
	timeptr->tm_mon=createtime2;
	timeptr->tm_yday=createtime3;
	timeptr->tm_mday=createtime4;
	timeptr->tm_wday=createtime5;

	timeptr->tm_hour=createtime6;
	timeptr->tm_min=createtime7;
	timeptr->tm_sec=createtime8;

	timeptr->tm_isdst=createtime9;
	return TRUE;
}
//设定MAPITEM数据值
int GLOBAL_set_MAPITEM_data(MAPITEM *mitem,UINT64 fileid,FILEMETA *filemetaptr,//文件指针
								   UINT64 deviceid,DEVICE *deviceptr,//设备指针
								   UINT64 diskid,DISK *diskptr,//存储器指针
								   UINT64 stripid,STRIP *stripptr,//条带指针
								   UINT64 stripsectid,STRIPSECT *stripsectptr,//条带块指针
								   UINT64 chunkid,CHUNK *chunkptr,//块指针
								   UINT64 regoinid,REGION *regionptr//区域指针
								   )
{
	mitem->fileid=fileid;
	mitem->filemetaptr=filemetaptr;//文件指针

	mitem->deviceid=deviceid;
	mitem->deviceptr=deviceptr;//设备指针
	
	mitem->diskid=diskid;
	mitem->diskptr=diskptr;//存储器指针
							
	mitem->stripid=stripid;
	mitem->stripptr=stripptr;//条带指针
								   
	mitem->stripsectid=stripsectid;
	mitem->stripsectptr=stripsectptr;//条带块指针
								   
	mitem->chunkid=chunkid;
	mitem->chunkptr=chunkptr;//块指针
	
	mitem->regoinid=regoinid;
	mitem->regionptr=regionptr;//区域指针
	return TRUE;
}
//设定MAPPAIR数据值
int GLOBAL_set_MAPPAIR_data(MAPPAIR *mpair,MAPITEM *login_item,MAPITEM *physic_item)//物理块					
{
	mpair->login_item=login_item;
	mpair->physic_item=physic_item;
	return TRUE;
}
//设定CODEPARA数据值
int GLOBAL_set_CODEPARA_data(CODEPARA *cpara,
									int w,//伽罗华域大小
									int datanum,//k
									int codenum,//m
									int totnum,//n
									int pronum,//d
									int sectornum//针对扇区编码的块数
									)
{
	cpara->w=w;
	cpara->datanum=datanum;
	cpara->codenum=codenum;//m
	cpara->totnum=totnum;//n
	cpara->pronum=pronum;//d
	cpara->sectornum=sectornum;//针对扇区编码的块数
	return TRUE;
}
//设定STRIPDES数据值
int GLOBAL_set_STRIPDES_data(STRIPDES *strdes,
									int chunknum,//每一个条带包括的行数,即chunk数
									DISKBLOCK *disklist,//所需的disk列表
									UINT64 *diskid,//当前磁盘id
									int disknum,//存在的即一个条带的列数，磁盘数，通常这个数量和region的disk数一致
									int chunksize//每一个CHUNK的大小以字节为单位
									)
{
	strdes->chunknum=chunknum;

	strdes->disklist=disklist;
	strdes->diskid=diskid;
	strdes->disknum=disknum;

	strdes->chunksize=chunksize;
	return TRUE;
}
//设定CHUNKGROUP数据值
int GLOBAL_set_CHUNKGROUP_data(CHUNKGROUP *chkgroup,
									  CHUNK *ckgroup,//列表
									  int groupsize//大小
									  )
{
	chkgroup->ckgroup=ckgroup;
	chkgroup->groupsize=groupsize;
	return TRUE;
}
//设定STRIPSECTGROUP数据值
int GLOBAL_set_STRIPSECTGROUP_data(STRIPSECTGROUP *strsetgroup,
										  STRIPSECT *stripsectgroup,//列表
										  int groupsize//大小
										  )
{
	strsetgroup->stripsectgroup=stripsectgroup;
	strsetgroup->groupsize=groupsize;
	return TRUE;
}
//设定STRIPGROUP数据值
int GLOBAL_set_STRIPGROUP_data(STRIPGROUP *strgroup,
									  STRIP *stripgroup,//列表
									  int groupsize//大小
									  )
{
	strgroup->stripgroup=stripgroup;
	strgroup->groupsize=groupsize;
	return TRUE;
}
//设定DISKGROUP数据值
int GLOBAL_set_DISKGROUP_data(DISKGROUP *disgroup,
									 DISK *diskgroup,//列表
									 int groupsize//大小
									 )
{
	disgroup->diskgroup=diskgroup;
	disgroup->groupsize=groupsize;
	return TRUE;
}
//设定DEVICEGROUP数据值
int GLOBAL_set_DEVICEGROUP_data(DEVICEGROUP *devgroup,
									   DEVICE *devicegroup,//列表
									   int groupsize//大小
									   )
{
	devgroup->devicegroup=devicegroup;
	devgroup->groupsize=groupsize;
	return TRUE;
}
//设定REGIONGROUP数据值
int GLOBAL_set_REGIONGROUP_data(REGIONGROUP *reggroup,
									   REGION *regiongroup,//列表
									   int groupsize//大小
									   )
{
	reggroup->regiongroup=regiongroup;
	reggroup->groupsize=groupsize;
	return TRUE;
}
//设定CHUNKPATH数据值
int GLOBAL_set_CHUNKPATH_data(CHUNKPATH *chkpath,
									 UINT64 regionid,int regionarrayid,REGION *regionptr,//region指针
									 UINT64 stripid,int striparrayid,STRIP *stripptr,//strip指针
									 UINT64 stripsectid,int stripsectarrayid,STRIPSECT *stripsectptr,//stripsect指针
									 UINT64 chunkid,int chunkarrayid,CHUNK *chunkptr//指向当前chunk
									 )
{
	chkpath->regionid=regionid;
	chkpath->regionarrayid=regionarrayid;
	chkpath->regionptr=regionptr;//region指针
									 
	chkpath->stripid=stripid;
	chkpath->striparrayid=striparrayid;
	chkpath->stripptr=stripptr;//strip指针
									 
	chkpath->stripsectid=stripsectid;
	chkpath->stripsectarrayid=stripsectarrayid;
	chkpath->stripsectptr=stripsectptr;//stripsect指针

	chkpath->chunkid=chunkid;
	chkpath->chunkarrayid=chunkarrayid;
	chkpath->chunkptr=chunkptr;//指向当前chunk
	return TRUE;
}
//设定FILEINF数据值
int GLOBAL_set_FILEINF_data(FILEINF *finf,UINT64 fileid,UINT64 *chunkid,FILEMETA *filemeta,
								   CHUNKPATH *chkpath,CHUNKBLOCK *chunklist,int chunknum,//chun列表
								   REGION *regionptr,UINT64 regionid,//region指针
								   DEVICEBLOCK *devicelist,UINT64 *deviceid,int devicenum,//设备列表
								   DISKBLOCK *disklist,UINT64 *diskid,int disknum,//存储器列表
								   STRIPBLOCK *striplist,UINT64 *stripid,int stripnum,//条带列表
								   STRIPSECTBLOCK *stripsectlist,UINT64 *stripsectid,int stripsectnum//条带区域列表
								   )
{
	finf->fileid=fileid;
	finf->chunkid=chunkid;
	finf->filemeta=filemeta;
								   
	finf->chkpath=chkpath;
	finf->chunklist=chunklist;
	finf->chunknum=chunknum;//chun列表
								   
	finf->regoinptr=regionptr;
	finf->regionid=regionid;//region指针
								   
	finf->devicelist=devicelist;
	finf->deviceid=deviceid;
	finf->devicenum=devicenum;//设备列表
								   
	finf->disklist=disklist;
	finf->diskid=diskid;
	finf->disknum=disknum;//存储器列表
								   
	finf->striplist=striplist;
	finf->stripid=stripid;
	finf->stripnum=stripnum;//条带列表
								   
	finf->stripsectlist=stripsectlist;
	finf->stripsectid=stripsectid;
	finf->stripsectnum=stripsectnum;//条带区域列表
	return TRUE;
}
//设定FILEMETA数据值
int GLOBAL_set_FILEMETA_data(FILEMETA *fmeta,char *filename,UINT64 filesize,int ACList,int filetype,
									REGION *regionptr,UINT64 regionid,//上层region指针
									struct USERPROFILE *userinf,UINT64 userid,//文件所有者
									UINT64 parentid,FILEMETA *parentptr,//上一次文件夹
									UINT64 *subfileidlist,FILEMETABLOCK *subfilelist,int subfilenum,//文件块指针主要指向当前目录下一级元数据块
									struct tm *createtime,
									struct tm *updatetime,
									FILEINF *filechunkinf//用于存放数据块信息
									)
{
	fmeta->filename=filename;
	fmeta->filesize=filesize;
	fmeta->ACList=ACList;
	fmeta->filetype=filetype;
		
	fmeta->regionptr=regionptr;
	fmeta->regionid=regionid;

	fmeta->userinf=userinf;
	fmeta->userid=userid;

	fmeta->parentid=parentid;
	fmeta->parentptr=parentptr;//上一次文件夹
									
	
	fmeta->subfileidlist=subfileidlist;
	fmeta->subfilelist=subfilelist;//文件块指针主要指向当前目录下一级元数据块;
	fmeta->subfilenum=subfilenum;
	
	fmeta->createtime=createtime;
	fmeta->updatetime=updatetime;

	fmeta->filechunkinf=filechunkinf;
	return TRUE;
}
//用户的当前
int GLOBAL_set_USERLOCATION_data(USERLOCATION *ulac,UINT64 DICid,FILEMETA *DICmetaptr,char *DICpath)
{
	ulac->DICid=DICid;
	ulac->DICmetaptr=DICmetaptr;
	ulac->DICpath=DICpath;
	return TRUE;
}
//设定用户的信息id为下一个可用id
int GLOBAL_set_USERPROFILE_data(USERPROFILE *upro,
									char *username,char *password,
									USERLOCATION *userlocinf,int userprivil,//用户信息
									struct tm *createtime//创建时间
									)
{
	upro->username=username;
	upro->password=password;
	upro->userlocinf=userlocinf;
	upro->userprivil=userprivil;
	upro->createtime=createtime;
	return TRUE;
}
int GLOBAL_set_USERGROUP_data(USERGROUP *ugroup,USERPROFILE *userlist,int groupsize)//用户组设定
{
	ugroup->userlist=userlist;
	ugroup->groupsize=groupsize;
	return TRUE;
}
int GLOBAL_set_SYSTEMUSERPTR_data(SYSTEMUSERPTR *sysuserptr,UINT64 userid,USERPROFILE *userprofileptr)
{
	sysuserptr->userprofileptr=userprofileptr;
	sysuserptr->userid=userid;
	return TRUE;
}
int GLOABL_set_SYSTEMNEXTID_data(IDITEM *systemnextid,
								UINT64 gloregionid,UINT64 glostripid,UINT64 glostripsectid,UINT64 glochunkid,
								UINT64 glodeviceid,UINT64 glodiskid,
								UINT64 glofileid,UINT64 glouserid)//设定一下个可以分配的系统编号
{
	systemnextid->gloregionid=gloregionid;
	systemnextid->glostripid=glostripid;
	systemnextid->glostripsectid=glostripsectid;
	systemnextid->glochunkid=glochunkid;

	systemnextid->glodeviceid=glodeviceid;
	systemnextid->glodiskid=glodiskid;
	
	systemnextid->glofileid=glofileid;
	systemnextid->glouserid=glouserid;
	return TRUE;
}
int GLOBAL_set_GLOSYSTEMID_data(GLOSYSTEMID *systemid,
									UINT64 *regionid,REGIONGROUP *gloregiongroup,int regionnum,
									UINT64 *userid,USERGROUP *glousergroup,int usernum,
									UINT64 *deviceid,DEVICEGROUP *glodevicegroup,int devicenum,
									UINT64 *diskid,DISKGROUP *glodiskgroup,int disknum,
									IDITEM *systemnextid,
									int glopushtime,UINT64 glomaxbuffersize,
									int *availkind,int availnum)
{
	systemid->regionid=regionid;
	systemid->gloregiongroup=gloregiongroup;
	systemid->regionnum=regionnum;

	systemid->userid=userid;
	systemid->glousergroup=glousergroup;
	systemid->usernum=usernum;

	systemid->deviceid=deviceid;
	systemid->glodevicegroup=glodevicegroup;
	systemid->devicenum=devicenum;

	systemid->diskid=diskid;
	systemid->glodiskgroup=glodiskgroup;
	systemid->disknum=disknum;

	systemid->systemnextid=systemnextid;
	systemid->glopushtime=glopushtime;
	systemid->glomaxbuffersize=glomaxbuffersize;

	systemid->availkind=availkind;
	systemid->availnum=availnum;
	return TRUE;
}
int GLOBAL_set_GLODIRTYDATA_data(GLODIRTYDATA *dirtydata,
										CHUNKBLOCK *chunkblockptr,int chunknum,
										STRIPSECTBLOCK *strsetblockptr,int strsectnum,
										STRIPBLOCK *stripblockptr,int stripnum,
										REGIONBLOCK *regionblockptr,int regionnum,
										DEVICEBLOCK *deviceblockptr,int devicenum,
										DISKBLOCK *diskblockptr,int disknum,
										FILEMETABLOCK *filemetablockptr,int filemetanum,
										USERBLOCK *userblockptr,int usernum
										)
{
	dirtydata->chunkblockptr=chunkblockptr;
	dirtydata->chunknum=chunknum;

	dirtydata->stripsectblockptr=strsetblockptr;
	dirtydata->stripsectnum=strsectnum;

	dirtydata->stripblockptr=stripblockptr;
	dirtydata->stripnum=stripnum;

	dirtydata->regionblockptr=regionblockptr;
	dirtydata->regionnum=regionnum;

	dirtydata->deviceblockptr=deviceblockptr;
	dirtydata->devicenum=devicenum;

	dirtydata->diskblockptr=diskblockptr;
	dirtydata->disknum=disknum;

	dirtydata->filemetablockptr=filemetablockptr;
	dirtydata->filemtetanum=filemetanum;

	dirtydata->userblockptr=userblockptr;
	dirtydata->usernum=usernum;
	return TRUE;
}
int GLOBAL_set_UPDATEELEMENT_data(UPDATEELEMENT *updateelementptr,BITELEMENT *bitelementptr,
										SCHEDULE *updateIscheduleptr,BITMATRIX *updateIelementptr,
										SCHEDULE *updateIIscheduleptr,BITMATRIX *updateIIelementptr,
										int stripsecindex,int chunkindex,
										int isupdateI,CHUNK *tempchunkptr,
										int shouldreadnum,int lastindex,
										BITELEMENT *lastdiskelement,int diskshouldread,int isdiskupdateI,
										BITELEMENT *lastmemoryelement,int memoryshouldread,int ismemoryupdateI,
										UPDATEELEMENT *lastupdateelement,int updateshouldread,int isupdateupdateI)
{
	updateelementptr->bitelementptr=bitelementptr;

	updateelementptr->updateIscheduleptr=updateIscheduleptr;
	updateelementptr->updateIelementptr=updateIelementptr;

	updateelementptr->updateIIscheduleptr=updateIIscheduleptr;
	updateelementptr->updateIIelementptr=updateIIelementptr;

	updateelementptr->stripsecindex=stripsecindex;
	updateelementptr->chunkindex=chunkindex;

	updateelementptr->isupdateI=isupdateI;
	updateelementptr->tempchunkptr=tempchunkptr;
	//updateelementptr->sizenum=sizenum;

	updateelementptr->shouldreadnum=shouldreadnum;
	updateelementptr->lastindex=lastindex;

	updateelementptr->lastdiskelement=lastdiskelement;
	updateelementptr->diskshouldread=diskshouldread;
	updateelementptr->isdiskupdateI=isdiskupdateI;

	updateelementptr->lastmemoryelement=lastmemoryelement;
	updateelementptr->memoryshouldread=memoryshouldread;
	updateelementptr->ismemoryupdateI=ismemoryupdateI;
										
	updateelementptr->lastupdateelement=lastupdateelement;
	updateelementptr->updateshouldread=updateshouldread;
	updateelementptr->isupdateupdateI=isupdateupdateI;
	return TRUE;
}
int GLOBAL_set_BITELEMENT_data(BITELEMENT *bitelementptr,
									BITMATRIX *elementptr,int stripsectindex,int chunkindex,
									int istarget,SCHEDULE *scheduleptr,
									CHUNK *chunkptr,UINT64 chunkid)
{
	bitelementptr->elementptr=elementptr;

	bitelementptr->stripsectindex=stripsectindex;
	bitelementptr->chunkindex=chunkindex;

	bitelementptr->istarget=istarget;
	bitelementptr->scheduleptr=scheduleptr;

	bitelementptr->chunkptr=chunkptr;
	bitelementptr->chunkid=chunkid;
	return TRUE;
}
int GLOBAL_set_SCHEDULE_data(SCHEDULE *scheduleptr,SCHEDOP *schedlist,int size,int w)
{
	scheduleptr->schedlist=schedlist;
	scheduleptr->size=size;
	scheduleptr->w=w;
	return TRUE;
}
//6个实体相应的数据描述符
//自动返回一个空CHUNK数据结构并且标号为下一个目标
CHUNK GLOBAL_create_CHUNK_NULL()
{
	CHUNK chk;
	chk.sizenum=NOSIZE;
	chk.chunkcontent=NULL;
	chk.chkpath=NULL;
	chk.isparity=NOVALUE;

	chk.deviceid=NODEVICE;
	chk.deviceptr=NULL;

	chk.diskid=NODEVICE;
	chk.diskptr=NULL;

	chk.fileid=0;
	chk.fmeta=NULL;

	chk.regionid=NODEVICE;
	chk.regionptr=NULL;
	
	chk.stripid=NOVALUE;
	chk.stripptr=NULL;

	chk.stripsectid=NOVALUE;
	chk.stripsectptr=NULL;
	
	chk.storestate=NOVALUE;

	//最后设定编号
	chk.ChunkID=get_state_glochunkid();
	set_state_glochunkid_add(1);
	return chk;

}
//自动返回一个空STRIPSECT数据结构并且标号为下一个目标
STRIPSECT GLOBAL_create_STRIPSECT_NULL()
{
	STRIPSECT strset;
	
	strset.storestate=NOVALUE;

	strset.chunkid=NULL;
	strset.chunklist=NULL;
	strset.chunksize=NOVALUE;
	strset.chunknum=NOVALUE;

	strset.deviceid=NOVALUE;
	strset.deviceptr=NULL;

	strset.diskid=NOVALUE;
	strset.diskptr=NULL;

	strset.filename=NULL;
	strset.filepath=NULL;

	strset.regionid=NOVALUE;
	strset.regionptr=NULL;

	strset.stripid=NOVALUE;
	strset.stripptr=NULL;

	//最后设定编号
	strset.StripsectID=get_state_glostripsectid();
	set_state_glostripsectid_add(1);
	return strset;
}
//自动返回一个空STRIP数据结构并且标号为下一个目标
STRIP GLOBAL_create_STRIP_NULL()
{
	STRIP str;
	
	str.storestate=NOVALUE;
	str.strdes=NULL;

	str.chunkid=NULL;
	str.chunklist=NULL;
	str.chunknum=NOVALUE;

	str.diskid=NULL;
	str.disklist=NULL;
	str.disknum=NOVALUE;

	str.devicelist=NULL;
	str.deviceid=NULL;
	str.devicenum=NOVALUE;

	str.regionid=NOVALUE;
	str.regionptr=NULL;

	str.stripsectid=NULL;
	str.stripsectlist=NULL;
	str.strsetnum=NOVALUE;
	//最后设定编号
	str.StripID=get_state_glostripid();
	set_state_glostripid_add(1);
	return str;
}
//自动返回一个空DISK数据结构并且标号为下一个目标
DISK GLOBAL_create_DISK_NULL()
{
	DISK dis;

	dis.capability=NOVALUE;
	dis.DiskTYPE=NODEVICE;
	dis.diskpath=NULL;
	dis.storestate=NOVALUE;
	dis.volumn=NOSIZE;

	dis.deviceid=NOVALUE;
	dis.deviceptr=NULL;

	dis.regionid=NULL;
	dis.regionlist=NULL;
	dis.regionnum=NOVALUE;

	//最后设定编号
	dis.DiskID=get_state_glodiskid();
	set_state_glodiskid_add(1);
	return dis;
}
//自动返回一个空DEVICE数据结构并且标号为下一个目标
DEVICE GLOBAL_create_DEVICE_NULL()
{
	DEVICE dev;
	dev.Devicetype=NOVALUE;
	dev.processnum=NOVALUE;
	dev.speed=NULL;
	dev.storestate=NOVALUE;

	dev.disklist=NULL;
	dev.diskid=NULL;
	dev.disknum=NOVALUE;

	dev.regionlist=NULL;
	dev.regionid=NULL;
	dev.regionnum=NOVALUE;

	//最后设定编号
	dev.DeviceID=get_state_glodeviceid();
	set_state_glodeviceid_add(1);
	return dev;
}
//自动返回一个空REGION数据结构并且标号为下一个目标
REGION GLOBAL_REGION_REGION_NULL()
{
	REGION reg;
	
	reg.codepara=NULL;
	reg.codetype=NOVALUE;
	reg.totalsize=NOVALUE;

	reg.devicelist=NULL;
	reg.deviceid=NULL;
	reg.devicenum=NOVALUE;

	reg.diskid=NULL;
	reg.disklist=NULL;
	reg.disknum=NOVALUE;

	reg.fileid=NULL;
	reg.filemetalist=NULL;
	reg.filenum=NOVALUE;

	reg.stripid=NULL;
	reg.striplist=NULL;
	reg.stripnum=NOVALUE;

	reg.chunknum=NOVALUE;
	reg.stripsectnum=NOVALUE;
	
	reg.fileroot=NULL;
	reg.rootfileid=NOVALUE;
	//最后设定编号
	reg.RegionID=get_state_gloregionid();
	set_state_gloregionid_add(1);
	return reg;
}
//设定参数
int GLOBAL_set_CHUNK_data(CHUNK *chk,int isparity,CHUNKPATH *chkpath,int sizenum,//基本信息
								 BYTE* chunkcontent,//内容
								 UINT64 regionid,REGION *regionptr,//上一级region的指针
								 UINT64 stripid,STRIP *stripptr,//上一级strip的指针
								 UINT64 stripsectid,STRIPSECT *stripsectptr,//上一级stripsect的指针
								 UINT64 diskid,DISK *diskptr,//上一级disk的指针
								 UINT64 deviceid,DEVICE *deviceptr,//上一级device的指针
								 UINT64 fileid,FILEMETA *fmeta,//属于文件元数据
								 int storestate//当前块存储状态
								 )//设定当前CHUNK中的数据
{
	chk->isparity=isparity;
	chk->chkpath=chkpath;
	chk->sizenum=sizenum;//基本信息							
	chk->chunkcontent=chunkcontent;//内容
	
	chk->regionid=regionid,
	chk->regionptr=regionptr;//上一级region的指针
								
	chk->stripid=stripid,
	chk->stripptr=stripptr,//上一级strip的指针
								 
	chk->stripsectid=stripsectid;
	chk->stripsectptr=stripsectptr,//上一级stripsect的指针
								 
	chk->diskid=diskid;
	chk->diskptr=diskptr;//上一级disk的指针
								 
	chk->deviceid=deviceid;
	chk->deviceptr=deviceptr;//上一级device的指针
								 
								 
	chk->fileid=fileid;
	chk->fmeta=fmeta,//属于文件元数据
								 
	chk->storestate=storestate;//当前块存储状态
	return TRUE;				
}
int GLOBAL_set_STRIPSECT_data(STRIPSECT *strset,int isparity,UINT64 *chunkid,CHUNKGROUP *chunklist,int chunksize,int chunknum,//chunk列表
									 UINT64 regionid,REGION *regionptr,//上一级region指针
									 UINT64 stripid,STRIP *stripptr,//上一级strip指针
									 UINT64 diskid,DISK *diskptr,//上一级disk指针
									 UINT64 deviceid,DEVICE *deviceptr,//上一级device指针
									 char *filename,char *filepath,//路径
									 int storestate//当前存储状态
									 )//设定当前STRIPSECT中的数据
{
	strset->chunkid=chunkid;

	strset->isparity=isparity;
	strset->chunklist=chunklist;
	strset->chunksize=chunksize;
	strset->chunknum=chunknum;//chunk列表

	strset->regionid=regionid;
	strset->regionptr=regionptr;//上一级region指针
									 
	strset->stripid=stripid;
	strset->stripptr=stripptr;//上一级strip指针
	
	strset->diskid=diskid;
	strset->diskptr=diskptr;//上一级disk指针
									 
	strset->deviceid=deviceid;
	strset->deviceptr=deviceptr,//上一级device指针
									 
	strset->filename=filename;
	strset->filepath=filepath;//路径
									 
	strset->storestate=storestate;//当前存储状态
	return TRUE;
}
int GLOBAL_set_STRIP_data(STRIP *str,STRIPDES *strdes,//条带描述
								 DISKBLOCK *disklist,UINT64 *diskid,int disknum,//包含存储器个数
								 DEVICEBLOCK *devicelist,UINT64 *deviceid,int devicenum,//设备列表
								 STRIPSECTGROUP *stripsectlist,UINT64 *stripsectid,int strsetnum,//Strset列表
								 CHUNKGROUP *chunklist,UINT64 *chunkid,int chunknum,//chunk列表
								 UINT64 regionid,REGION *regionptr,//上一级region指针
								 int storestate//当前存储状态
								 )//设定当前STRIP中的数据
{
	str->strdes=strdes;//条带描述
								 
	str->disklist=disklist;
	str->diskid=diskid;
	str->disknum=disknum;//包含存储器个数

	str->devicelist=devicelist;//设备列表
	str->deviceid=deviceid;
	str->devicenum=devicenum;
								 
	str->stripsectlist=stripsectlist;
	str->stripsectid=stripsectid;
	str->strsetnum=strsetnum;//Strset列表
								 
	str->chunklist=chunklist;
	str->chunkid=chunkid;
	str->chunknum=chunknum,//chunk列表

	str->regionid=regionid;
	str->regionptr=regionptr;//上一级region指针
								 
	str->storestate=storestate;//当前存储状态
	return TRUE;
}
int GLOBAL_set_DISK_data(DISK *dis,int DiskTYPE,int capability,UINT64 volumn,
								REGIONBLOCK *regionlist,UINT64 *regionid,int regionnum,//存储器上包括的region数量
								DEVICE *deviceptr,UINT64 deviceid,//上一层的device编号
								char *diskpath,//关键信息当前磁盘的物理路径
								int storestate//当前存储状态	
								)//设定当前DISK中的数据
{
	dis->DiskTYPE=DiskTYPE;
	dis->capability=capability;
	dis->volumn=volumn;


	dis->regionlist=regionlist;
	dis->regionid=regionid;
	dis->regionnum=regionnum;//存储器上包括的region数量
								
	dis->deviceptr=deviceptr;
	dis->deviceid=deviceid;//上一层的device编号
								
	dis->diskpath=diskpath;//关键信息当前磁盘的物理路径
								
	dis->storestate=storestate;//当前存储状态	
	return TRUE;
								
}
int GLOBAL_set_DEVICE_data(DEVICE *div,int Devicetype,int processnum,int *speed,
								  DISKBLOCK *disklist,UINT64 *diskid,int disknum,//存储器列表
								  REGIONBLOCK *regionlist,UINT64 *regionid,int regionnum,//region列表
								  int storestate//当前存储状态
								  )//设定当前DEVICE中的数据
{
	div->Devicetype=Devicetype;
	div->processnum=processnum;
	div->speed=speed;
								  
	div->diskid=diskid;
	div->disklist=disklist;
	div->disknum=disknum;//存储器列表
								  
	div->regionlist=regionlist;
	div->regionid=regionid;
	div->regionnum=regionnum;//region列表
								  
	div->storestate=storestate;//当前存储状态
	return TRUE;
}
int GLOBAL_set_REGION_data(REGION *reg,int codetype,CODEPARA *codepara,UINT64 totalsize,
								  FILEMETABLOCKGROUP *filemetalist,UINT64 *fileid,int filenum,//包括的file的列表
								  DISKBLOCK *disklist,UINT64 *diskid,int disknum,//Disk的列表
								  DEVICEBLOCK *devicelist,UINT64 *deviceid,int devicenum,//device列表
								  STRIPDES *strdes,STRIPGROUP *striplist,UINT64 *stripid,int stripnum,//条带个数
								  UINT64 chunknum,UINT64 stripsectnum,//chunk和stripsect总数
								  FILEMETA *fileroot,UINT64 rootfileid,//根文件指针
								  int storestate//当前存储状态
								  )//设定当前REGION中的数据

{
	reg->codetype=codetype;
	reg->codepara=codepara;
	reg->totalsize=totalsize;

	reg->filemetalist=filemetalist;
	reg->fileid=fileid;
	reg->filenum=filenum;//包括的file的列表

	reg->disklist=disklist;
	reg->diskid=diskid;
	reg->disknum=disknum;//Disk的列表

	reg->devicelist=devicelist;
	reg->deviceid=deviceid;
	reg->devicenum=devicenum;//device列表

	reg->strdes=strdes;
	reg->striplist=striplist;
	reg->stripid=stripid;
	reg->stripnum=stripnum;//条带个数

	reg->chunknum=chunknum;
	reg->stripsectnum=stripsectnum;//chunk和stripsect总数
		
	reg->fileroot=fileroot;
	reg->rootfileid=rootfileid;//根文件指针

	reg->storestate=storestate;//当前存储状态
	return TRUE;
}

//生成相应的类别函数
//当前实现的RAID6下RDP，EVENODD，MDR，MSR下FMSR，EMSR，MBR下EMBR
void intial_kind()
{
	int kindid;
	availkind=(int *)malloc(7);
	kindid=codetype(RAID6,RDP);
	availkind[availnum]=kindid;
	availnum++;
	kindid=codetype(RAID6,EVENODD);
	availkind[availnum]=kindid;
	availnum++;
	kindid=codetype(RAID6,MDRI);
	availkind[availnum]=kindid;
	availnum++;
	kindid=codetype(MSR,FMSR);
	availkind[availnum]=kindid;
	availnum++;
	kindid=codetype(MSR,EMSR);
	availkind[availnum]=kindid;
	availnum++;
	kindid=codetype(MBR,EMSR);
	availkind[availnum]=kindid;
	availnum++;
	kindid=codetype(RAID5,NULLTYPE);
	availkind[availnum]=kindid;
	availnum++;
}
int isavailkind(int kindid)
{
	int i=0;
	if(availnum==0) 
	{
		//说明没有初始化
		show_error("gloabl_define","availkind","no-initial");
		return FALSE;
	}
	for(i=0;i<availnum;i++)
	{
		if(availkind[i]==kindid)
		{
			return TRUE;
		}
	}
	return FALSE;
}
//设置系统参数
int reset_state()//统统的清零
{
	systemstatic.memcpynum=0;
	systemstatic.readnum=0;
	systemstatic.writenum=0;
	systemstatic.sendnum=0;
	systemstatic.recnum=0;
	systemstatic.w08multnum=0;
	systemstatic.w16multnum=0;
	systemstatic.w32multnum=0;

	return TRUE;
}
//复杂度相关统计参数
int set_state_memcpynum_add(UINT64 memcpynum)
{
	systemstatic.memcpynum+=memcpynum;
	return TRUE;
}

int set_state_xor_add(UINT64 xornum)
{
	systemstatic.xornum+=xornum;
	return TRUE;
}
int set_state_w08_add(UINT64 w08num)
{
	systemstatic.w08multnum+=w08num;
	return TRUE;
}
int set_state_w16_add(UINT64 w16num)
{
	systemstatic.w16multnum+=w16num;
	return TRUE;
}
int set_state_w32_add(UINT64 w32num)
{
	systemstatic.w32multnum+=w32num;
	return TRUE;
}

//与网络相关统计参数
int set_state_NETWORK_send_add(UINT64 sendnum)
{
	systemstatic.sendnum+=sendnum;
	return TRUE;
}
int set_state_NETWORK_rec_add(UINT64 recnum)
{
	systemstatic.recnum+=recnum;
	return TRUE;
}

//与磁盘有关统计参数
int set_state_IO_read_add(UINT64 readnum)
{
	systemstatic.readnum+=readnum;
	return TRUE;
}
int set_state_IO_write_add(UINT64 writenum)
{
	systemstatic.writenum+=writenum;
	return TRUE;
}


//初始化全局id
int intial_globalid(UINT64 gloregionid,UINT64 glostripid,UINT64 glostripsectid,UINT64 glodeviceid,UINT64 glodiskid,UINT64 glochunkid,UINT64 glofileid,UINT64 glouserid)
{
	//对于系统id进行赋值
	systemid.gloregionid=gloregionid;
	systemid.glostripid=glostripid;
	systemid.glostripsectid=glostripsectid;
	systemid.glodeviceid=glodeviceid;
	systemid.glodiskid=glodiskid;
	systemid.glochunkid=glochunkid;
	systemid.glofileid=glofileid;
	systemid.glouserid=glouserid;
	return TRUE;
}

int inital_globalid_by_iditem(IDITEM *initaliditem)
{
	//对于系统id进行赋值
	if(initaliditem==NULL)
	{
		show_error("golbal_define","globalid","initaliditems==NULL");
		return FALSE;
	}
	systemid.gloregionid=initaliditem->gloregionid;
	systemid.glostripid=initaliditem->glostripid;
	systemid.glostripsectid=initaliditem->glostripsectid;
	systemid.glodeviceid=initaliditem->glodeviceid;
	systemid.glodiskid=initaliditem->glodiskid;
	systemid.glochunkid=initaliditem->glochunkid;
	systemid.glofileid=initaliditem->glofileid;
	systemid.glouserid=initaliditem->glouserid;
	return TRUE;
}
//对于系统regionid增加
int set_state_gloregionid_add(UINT64 regnum)
{
	systemid.gloregionid+=regnum;
	return TRUE;
}
//对于系统stripid增加
int set_state_glostripid_add(UINT64 stripnum)
{
	systemid.glostripid+=stripnum;
	return TRUE;
}
//对于系统stripsectid增加
int set_state_glostripsectid_add(UINT64 stripsectnum)
{
	systemid.glostripsectid+=stripsectnum;
	return TRUE;
}
//对于系统deviceid增加
int set_state_glodeviceid_add(UINT64 devicenum)
{
	systemid.glodeviceid+=devicenum;
	return TRUE;
}
//对于系统diskid增加
int set_state_glodiskid_add(UINT64 disknum)
{
	systemid.glodiskid+=disknum;
	return TRUE;
}
//对于系统chunkid增加
int set_state_glochunkid_add(UINT64 chunknum)
{
	systemid.glochunkid+=chunknum;
	return TRUE;
}
//对于系统fileid增加
extern int set_state_glofileid_add(UINT64 filenum)
{
	systemid.glofileid+=filenum;
	return TRUE;
}
//对于系统userid增加
int set_state_glouserid_add(UINT64 usernum)
{
	systemid.glouserid+=usernum;
	return TRUE;
}

//获取系统regionid
UINT64 get_state_gloregionid()
{
	return systemid.gloregionid;
}
//获取系统stripid
UINT64 get_state_glostripid()
{
	return systemid.glostripid;
}
//获取系统stripsectid
UINT64 get_state_glostripsectid()
{
	return systemid.glostripsectid;
}
//获取系统deviceid
UINT64 get_state_glodeviceid()
{
	return systemid.glodeviceid;
}
//获取系统diskid
UINT64 get_state_glodiskid()
{
	return systemid.glodiskid;
}
//获取系统chunkid
UINT64 get_state_glochunkid()
{
	return systemid.glochunkid;
}
//获取系统fileid
UINT64 get_state_glofileid()
{
	return systemid.glofileid;
}
//获取系统userid
UINT64 get_state_glouserid()
{
	return systemid.glouserid;
}

//next_id
//设定系统id号
int set_SYSID_PTR(IDITEM *systemnextid)
{
	systemid.gloregionid=systemnextid->gloregionid;
	systemid.glostripid=systemnextid->glostripid;
	systemid.glostripsectid=systemnextid->glostripsectid;
	systemid.glochunkid=systemnextid->glochunkid;

	systemid.glodeviceid=systemnextid->glodeviceid;
	systemid.glodiskid=systemnextid->glodiskid;

	systemid.glofileid=systemnextid->glofileid;
	systemid.glouserid=systemnextid->glouserid;
	return TRUE;
}
//返回指针
IDITEM *get_SYSID_PTR()
{
	return &systemid;
}

STATSITEM* get_stats_PTR()
{
	return &systemstatic;
}

//之后版本从此处开始
//设定路径数据和region数据和用户数据
int set_state_glopath(char *glopath)//设定全局路径
{
	grometadatapath=glopath;
	return TRUE;
}
char *get_state_glopath_PTR()//获取全局路径
{
	return grometadatapath;
}

//设定全局device组
//设定当前的devicegroup
int set_state_glodevicegroup(DEVICEGROUP *devgroup)
{
	grodevicelist.devicegroup=devgroup->devicegroup;
	grodevicelist.groupsize=devgroup->groupsize;
	return TRUE;
}
//得到当前的devicegroup指针
DEVICEGROUP *get_state_glodevicegroup_PTR()
{
	return &grodevicelist;
}

//设定全局disk组
//设定当前的diskgroup
int set_state_glodiskgroup(DISKGROUP *diskgroup)
{
	grodisklist.diskgroup=diskgroup->diskgroup;
	grodisklist.groupsize=diskgroup->groupsize;
	return TRUE;
}
//得到当前的diskgroup指针
DISKGROUP *get_state_glodiskgroup_PTR()
{
	return &grodisklist;
}

//设定全局id
//设置全局id路径
int set_state_glosystemidgroup(GLOSYSTEMID *glosysid)
{
	grosysid.regionid=glosysid->regionid;
	grosysid.regionnum=glosysid->regionnum;
	grosysid.gloregiongroup=glosysid->gloregiongroup;

	grosysid.userid=glosysid->userid;
	grosysid.usernum=glosysid->usernum;
	grosysid.glousergroup=glosysid->glousergroup;

	grosysid.deviceid=glosysid->deviceid;
	grosysid.devicenum=glosysid->devicenum;
	grosysid.glodevicegroup=glosysid->glodevicegroup;

	grosysid.diskid=glosysid->diskid;
	grosysid.disknum=glosysid->disknum;
	grosysid.glodiskgroup=glosysid->glodiskgroup;
	return TRUE;
}
//获取全局id路径
GLOSYSTEMID *get_state_glosystemidgroup_PTR()
{
	return &grosysid;
}
//设定全局区域组
int set_state_gloregiongroup(REGIONGROUP *reggroup)//设定当前的regiongroup
{
	groregionlist.regiongroup=reggroup->regiongroup;
	groregionlist.groupsize=reggroup->groupsize;
	return TRUE;
}
int set_state_gloregiongroup_add(REGION *regionptr)//在当前的regiongroup中加入一个region
{
	REGION *regionlistptr,*newregionptr;//区域指针
	int groupsize,i;//大小以及i
	REGION *freeloc;//第一个可以插入的位置
	freeloc=NULL;//将将其制空
	//读取数据
	regionlistptr=groregionlist.regiongroup;
	groupsize=groregionlist.groupsize;
	for(i=0;i<groupsize;i++)//先检查是不是当前区域组中的元素
	{
		//看看当前指针是不是存在
		if(regionptr==regionlistptr)
		{
			show_error("global_define","gloregiongroup_add","region is exist");
			return FALSE;
		}
		
		//搜索第一个可以使用的位置
		if(regionlistptr->RegionID==NOVALUE)//如果当前为无效
		{
			i--;
			freeloc=regionlistptr;//将freeloc指向当前数据块
		}
		regionlistptr++;//计算下一个
	}
	groupsize+=1;//将组大小扩张1个
	regionlistptr=groregionlist.regiongroup;//置顶
	//将数据转存至第一个空白处
	if(freeloc==NULL)
	{
		//说明都厚数据需要重新分配
		newregionptr=ralloc(REGION,groupsize,regionlistptr);//重新扩张空间
		groregionlist.regiongroup=newregionptr;//将数据的指针重新定位
		//将数据存储在最后一个部分
		newregionptr=newregionptr+groupsize;
	}
	else
	{
		//将数据重新定位到新的位置
		newregionptr=freeloc;//可以无效数据填充
	}
	memcpy(newregionptr,regionptr,sizeof(REGION));//将其复制过去
	return TRUE;
}
int set_state_gloregiongroup_del_ID(UINT64 regionid)//将指定的region删除region
{
	//找数据设定为空即可
	int i,groupsize;
	UINT64 currentid;
	REGION *regionlistptr;
	//进行赋值
	regionlistptr=groregionlist.regiongroup;
	groupsize=groregionlist.groupsize;
	for(i=0;i<groupsize;i++)
	{
		currentid=regionlistptr->RegionID;//获取当前id
		if(currentid==regionid)
		{
			//如果找到标记为无效返回正确
			regionlistptr->RegionID=NOVALUE;
			groregionlist.groupsize=groupsize-1;
			return TRUE;
		}
		regionlistptr=regionlistptr++;
	}
	show_error("global_define","gloregiongroup_del","region isn't exist");
	return FALSE;
}
int set_state_gloregiongroup_del_PTR(REGION *regionptr)//指定的region删除region
{
	//找数据设定为空即可
	int i,groupsize;
	//UINT64 currentid;
	REGION *regionlistptr;
	//进行赋值
	regionlistptr=groregionlist.regiongroup;
	groupsize=groregionlist.groupsize;
	for(i=0;i<groupsize;i++)
	{
		//currentid=regionlistptr->RegionID;//获取当前id
		if(regionlistptr==regionptr)
		{
			//如果找到标记为无效返回正确
			regionlistptr->RegionID=NOVALUE;
			groregionlist.groupsize=groupsize-1;
			return TRUE;
		}
		regionlistptr=regionlistptr++;
	}
	show_error("global_define","gloregiongroup_del","region isn't exist");
	return FALSE;
}
REGIONGROUP *get_state_gloregiongroup_PTR()//得到当前的region指针
{
	
	return &groregionlist;
}

//设定用户组
int set_state_glousergroup(USERGROUP *ugroup)//设定当前用户组
{
	grouserlist.userlist=ugroup->userlist;
	grouserlist.groupsize=ugroup->groupsize;
	return TRUE;
}
int set_state_glousergroup_add(USERPROFILE *userprofileptr)//在当前的usergroup中加入一个userprofile
{
	//进行插入
	USERPROFILE *userlistptr,*newruserlistptr;//区域指针
	int groupsize,i;//大小以及i
	USERPROFILE *freeloc;//第一个可以插入的位置
	freeloc=NULL;//将将其制空
	//读取数据
	userlistptr=grouserlist.userlist;
	groupsize=grouserlist.groupsize;
	for(i=0;i<groupsize;i++)//先检查是不是当前区域组中的元素
	{
		//看看当前指针是不是存在
		if(userprofileptr==userlistptr)
		{
			show_error("global_define","glousergroup_add","userlist is exist");
			return FALSE;
		}
		
		//搜索第一个可以使用的位置
		if(userlistptr->UserID==NOVALUE)//如果当前为无效
		{
			i--;
			freeloc=userlistptr;//将freeloc指向当前数据块
		}
		userlistptr++;//计算下一个
	}
	groupsize+=1;//将组大小扩张1个
	userlistptr=grouserlist.userlist;//重新置顶
	//将数据转存至第一个空白处
	if(freeloc==NULL)
	{
		//说明都厚数据需要重新分配
		newruserlistptr=ralloc(USERPROFILE,groupsize,userlistptr);//重新扩张空间
		grouserlist.userlist=newruserlistptr;//将数据的指针重新定位
		//将数据存储在最后一个部分
		newruserlistptr=newruserlistptr+groupsize;
	}
	else
	{
		//将数据重新定位到新的位置
		newruserlistptr=freeloc;//可以无效数据填充
	}
	mcpy(newruserlistptr,userprofileptr,REGION,1);//将其复制过去
	return TRUE;
	return TRUE;
}
int set_state_glousergroup_del_ID(UINT64 userprofileid)//根据id删除userprofile
{
	USERPROFILE *userlistptr;
	//和上面的逻辑一样
	int i,groupsize;
	UINT64 currentid;
	//读取数据
	userlistptr=grouserlist.userlist;
	groupsize=grouserlist.groupsize;
	for(i=0;i<groupsize;i++)
	{
		currentid=userlistptr->UserID;
		if(currentid==userprofileid)
		{
			//找到标记为无效
			userlistptr->UserID=NOVALUE;
			grouserlist.groupsize=groupsize-1;
			return TRUE;
		}
		userlistptr++;
	}
	show_error("global_define","glousergroup_del","user isn't exist");
	return FALSE;
}
int set_state_glousergroup_del_PTR(USERPROFILE *userprofileptr)//根据指针删除userprofile
{
	USERPROFILE *userlistptr;
	//和上面的逻辑一样
	int i,groupsize;
	//UINT64 currentid;
	//读取数据
	userlistptr=grouserlist.userlist;
	groupsize=grouserlist.groupsize;
	for(i=0;i<groupsize;i++)
	{
		//currentid=userlistptr->UserID;
		if(userlistptr==userprofileptr)
		{
			//找到标记为无效
			userlistptr->UserID=NOVALUE;
			grouserlist.groupsize=groupsize-1;
			return TRUE;
		}
		userlistptr++;
	}
	show_error("global_define","glousergroup_del","user isn't exist");
	return FALSE;
}
USERGROUP *get_state_glousergroup_PTR()//返回系统用户组指针
{
	return &grouserlist;
}

//切换当前用户
int set_state_glosysuserptr(UINT64 userid,USERPROFILE *useprofileptr)//设定当前系统用户指针
{
	sysuserptr.userid=userid;
	sysuserptr.userprofileptr=useprofileptr;
	return TRUE;
}
int set_state_glosysuserptr_SYSTEMUSERPTR(SYSTEMUSERPTR *sysuserlistptr)//使用指针来设定当前指针
{
	sysuserptr.userid=sysuserlistptr->userid;
	sysuserptr.userprofileptr=sysuserlistptr->userprofileptr;
	return TRUE;
}
SYSTEMUSERPTR *get_state_glosysuserptr_PTR()//返回当前系统用户的指针
{
	return &sysuserptr;
}
UINT64 get_state_glosysuserptr_ID()//返回当前系统用户的编号
{
	UINT64 userid;
	userid=sysuserptr.userid;
	return userid;
}
USERPROFILE *get_state_glosysuserptr_userprofile()//
{
	USERPROFILE *uprofile;
	uprofile=sysuserptr.userprofileptr;
	return uprofile;
}

//全局元数据路径
extern int set_state_glometapath(char *grometapath)
{
	grometadatapath=grometapath;
	return TRUE;
}
extern char *get_state_glometapath()
{
	return grometadatapath;
}

//全局编码列表号
//获取种类数量
int get_state_avail_kind_number()
{
	return availnum;
}
//获取种类列表
int *get_state_avail_kind()
{
	return availkind;
}
//设定全局种类数量
int set_state_avail_kind_number(int kindnum)
{
	availnum=kindnum;
	return TRUE;
}
//设定全局种类类型
int set_state_avail_kind(int *kindlist)
{
	availkind=kindlist;
	return TRUE;
}

//设置获取缓冲队列
//获取缓冲队列
GLOPUSHLIST *get_state_buffer_pushlist()
{
	return &gropushlist;
}
//设置pushtime
int get_state_buffer_push_time()
{
	return gropushlist.glopushtime;
}
//设置push时间
struct tm *get_state_buffer_last_push_time()
{
	return gropushlist.glolastpushtime;
}
//设定缓冲队列
int set_state_buffer_pushlist(GLOPUSHLIST *gpushlist)
{
	gropushlist.glopushtime=gpushlist->glopushtime;
	gropushlist.glopushchunklist=gpushlist->glopushchunklist;
	gropushlist.chunknum=gpushlist->chunknum;

	gropushlist.glolastpushtime=gpushlist->glolastpushtime;

	gropushlist.maxbuffersize=gpushlist->maxbuffersize;
	gropushlist.currentbuffersize=gpushlist->currentbuffersize;
	return TRUE;
}
//设定pushtime时间
int set_state_buffer_push_time(int ptime)
{
	gropushlist.glopushtime=ptime;
	return TRUE;
}
//设定上次push时间
int set_state_buffer_last_push_time(struct tm *ltime)
{
	gropushlist.glolastpushtime=ltime;
	return TRUE;
}
//maximum缓冲区大小
int set_state_buffer_maxbuffersize(UINT64 maxbuffersize)
{
	gropushlist.maxbuffersize=maxbuffersize;
	return TRUE;
}
//当前缓冲区大小
int set_state_buffer_currentbuffersize(UINT64 currentbuffersize)
{
	gropushlist.currentbuffersize=currentbuffersize;
	return TRUE;
}
//设定和获取全局dirty大talist指针
//获取全局脏数据指针
GLODIRTYDATA *get_state_dirtydatalist()
{
	return &grodirtydatalist;
}
//设置全局脏数据指针
int set_state_dirtydatalist(GLODIRTYDATA *dirtydata)
{
	
	grodirtydatalist.chunkblockptr=dirtydata->chunkblockptr;
	grodirtydatalist.chunknum=dirtydata->chunknum;

	grodirtydatalist.stripsectblockptr=dirtydata->stripsectblockptr;
	grodirtydatalist.stripsectnum=dirtydata->stripsectnum;

	grodirtydatalist.stripblockptr=dirtydata->stripblockptr;
	grodirtydatalist.stripnum=dirtydata->stripnum;

	grodirtydatalist.regionblockptr=dirtydata->regionblockptr;
	grodirtydatalist.regionnum=dirtydata->regionnum;

	grodirtydatalist.filemetablockptr=dirtydata->filemetablockptr;
	grodirtydatalist.filemtetanum=dirtydata->filemtetanum;

	grodirtydatalist.userblockptr=dirtydata->userblockptr;
	grodirtydatalist.usernum=dirtydata->usernum;

	grodirtydatalist.deviceblockptr=dirtydata->deviceblockptr;
	grodirtydatalist.devicenum=dirtydata->devicenum;

	grodirtydatalist.diskblockptr=dirtydata->diskblockptr;
	grodirtydatalist.disknum=dirtydata->disknum;
	return TRUE;
}
//tempfreelisty操作
GLOTEMPFREELIST *get_state_tempfreelist()
{
	return &grotempfreelistptr;
}
int set_state_tempfreelist(GLOTEMPFREELIST *tempfree)
{
	grotempfreelistptr.chunkblockptr=tempfree->chunkblockptr;
	grotempfreelistptr.tempnum=tempfree->tempnum;
	return TRUE;
}

//获取时间
struct tm *get_system_time()
{
	time_t raw_time;
	struct tm *timeinfo; 
	time(&raw_time);
	timeinfo=localtime(&raw_time);
	return timeinfo;
}