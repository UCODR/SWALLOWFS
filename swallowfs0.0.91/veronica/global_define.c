/*
This program is created by Jiajie Shen 
2014.11.26
��ѽܴ���2014.11.26
*/
/*
global_define.h���ڳ�ʼ��ϵͳ����ʵ�����ȵ�
*/

#include "global_define.h"

//��ͨ���ݽṹ
MAPITEM GLOBAL_create_MAPITEM_NULL()//�Զ�����һ����MAPITEM���ݽṹ
{
	MAPITEM mitem;
	mitem.fileid=NOVALUE;//�ļ�id
	mitem.filemetaptr=NULL;//�ļ�ָ��
	mitem.deviceid;//�豸id
	mitem.deviceptr=NULL;//�豸ָ��
	mitem.diskid=NOVALUE;//�洢��id
	mitem.diskptr;//�洢��ָ��
	mitem.stripid; //����id
	mitem.stripptr;//����ָ��
	mitem.stripsectid;//������id
	mitem.stripsectptr;///������ָ��
	mitem.chunkid;//��id
	mitem.chunkptr;//��ָ��
	mitem.regoinid;//����id
	mitem.regionptr;//����ָ��
	return mitem;
}
MAPPAIR GLOBAL_create_MAPPAIR_NULL()//�Զ�����һ����MAPPAIR���ݽṹ
{
	MAPPAIR mpair;
	mpair.login_item=NULL;
	mpair.physic_item=NULL;
	return mpair;
}
CODEPARA GLOBAL_create_CODEPARA_NULL()//�Զ�����һ����CHUNK���ݽṹ
{
	CODEPARA cparam;
	cparam.codenum=NOVALUE;
	cparam.datanum=NOVALUE;
	cparam.pronum=NOVALUE;
	cparam.sectornum=NOVALUE;
	cparam.totnum=NOVALUE;
	return cparam;
}
STRIPDES GLOBAL_create_STRIPDES_NULL()//�Զ�����һ����STRIPDES���ݽṹ
{
	STRIPDES strdes;

	strdes.chunknum=NOVALUE;//stripsectchunk��

	strdes.disklist=NULL;
	strdes.diskid=NULL;
	strdes.disknum=NOVALUE;//strip��ʹ�õĴ��̸���

	strdes.chunksize=NOSIZE;//chunk��С

	return strdes;
}
CHUNKGROUP GLOBAL_create_CHUNKGROUP_NULL()//�Զ�����һ����CHUNKGROUP���ݽṹ
{
	CHUNKGROUP chkgroup;
	chkgroup.ckgroup=NULL;
	chkgroup.groupsize=NOSIZE;
	return chkgroup;
}
STRIPSECTGROUP GLOBAL_create_STRIPSECTGROUP_NULL()//�Զ�����һ����STRIPSECTGROUP���ݽṹ
{
	STRIPSECTGROUP strsetgroup;
	strsetgroup.stripsectgroup=NULL;
	strsetgroup.groupsize=NOSIZE;
	return strsetgroup;
}
STRIPGROUP GLOBAL_create_STRIPGROUP_NULL()//�Զ�����һ����STRIPGROUP���ݽṹ
{
	STRIPGROUP stripgroup;
	stripgroup.stripgroup=NULL;
	stripgroup.groupsize=NOVALUE;
	return stripgroup;
}
DISKGROUP GLOBAL_create_DISKGROUP_NULL()//�Զ�����һ����DISKGROUP���ݽṹ
{
	DISKGROUP dgroup;
	dgroup.diskgroup=NULL;
	dgroup.groupsize=NOSIZE;
	return dgroup;
}
DEVICEGROUP GLOBAL_create_DEVICEGROUP_NULL()//�Զ�����һ����DEVICEGROUP���ݽṹ
{
	DEVICEGROUP devgroup;
	devgroup.devicegroup=NULL;
	devgroup.groupsize=NOSIZE;
	return devgroup;
}
REGIONGROUP GLOBAL_create_REGIONGROUP_NULL()//�Զ�����һ����REGIONGROUP���ݽṹ
{
	REGIONGROUP reggroup;
	reggroup.regiongroup=NULL;
	reggroup.groupsize=NOSIZE;
	return reggroup;
}
RUNPATARMETER GLOBAL_create_RUNPATARMETER_NULL()//�Զ�����һ����RUNPATARMETER���ݽṹ
{
	RUNPATARMETER rpmeter;
	rpmeter.appnumber=NOVALUE;
	rpmeter.initalstate=NOVALUE;
	rpmeter.machinedvice=NULL;
	return rpmeter;
}
CHUNKPATH GLOBAL_create_CHUNKPATH_NULL()//�Զ�����һ����CHUNKPATH���ݽṹ
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
FILEINF GLOBAL_create_FILEINF_NULL()//�Զ�����һ����FILEINF���ݽṹ
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
FILEMETA GLOBAL_create_FILEMETA_NULL()//�Զ�����һ����FILEMETA���ݽṹ,ͬʱfileidָ����һ������id
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

	//����趨���
	fmeta.FileID=get_state_glostripid();
	set_state_glofileid_add(1);
	return fmeta;
}
//�Զ�����һ����USERLOCATION���ݽṹ
USERLOCATION GLOBAL_create_USERLOCATION_NULL()
{
	USERLOCATION ulac;
	ulac.DICid=NOVALUE;
	ulac.DICmetaptr=NULL;
	ulac.DICpath=NULL;
	return ulac;
}
//�Զ�����һ����USERPROFILE���ݽṹ
USERPROFILE GLOBAL_create_USERPROFILE_NULL()
{
	USERPROFILE upro;
	upro.username=NULL;
	upro.password=NULL;
	upro.userlocinf=NULL;
	upro.userprivil=NOVALUE;
	//����趨���
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
SYSTEMUSERPTR GLOBAL_create_SYSTEMUSERPTR_NULL()//�Զ�����һ����SYSTEMUSERPTR���ݽṹ
{
	SYSTEMUSERPTR sysuserptr;
	sysuserptr.userid=NOVALUE;
	sysuserptr.userprofileptr=NULL;
	return sysuserptr;
}
//�趨�������ݽṹֵ
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
//�趨MAPITEM����ֵ
int GLOBAL_set_MAPITEM_data(MAPITEM *mitem,UINT64 fileid,FILEMETA *filemetaptr,//�ļ�ָ��
								   UINT64 deviceid,DEVICE *deviceptr,//�豸ָ��
								   UINT64 diskid,DISK *diskptr,//�洢��ָ��
								   UINT64 stripid,STRIP *stripptr,//����ָ��
								   UINT64 stripsectid,STRIPSECT *stripsectptr,//������ָ��
								   UINT64 chunkid,CHUNK *chunkptr,//��ָ��
								   UINT64 regoinid,REGION *regionptr//����ָ��
								   )
{
	mitem->fileid=fileid;
	mitem->filemetaptr=filemetaptr;//�ļ�ָ��

	mitem->deviceid=deviceid;
	mitem->deviceptr=deviceptr;//�豸ָ��
	
	mitem->diskid=diskid;
	mitem->diskptr=diskptr;//�洢��ָ��
							
	mitem->stripid=stripid;
	mitem->stripptr=stripptr;//����ָ��
								   
	mitem->stripsectid=stripsectid;
	mitem->stripsectptr=stripsectptr;//������ָ��
								   
	mitem->chunkid=chunkid;
	mitem->chunkptr=chunkptr;//��ָ��
	
	mitem->regoinid=regoinid;
	mitem->regionptr=regionptr;//����ָ��
	return TRUE;
}
//�趨MAPPAIR����ֵ
int GLOBAL_set_MAPPAIR_data(MAPPAIR *mpair,MAPITEM *login_item,MAPITEM *physic_item)//�����					
{
	mpair->login_item=login_item;
	mpair->physic_item=physic_item;
	return TRUE;
}
//�趨CODEPARA����ֵ
int GLOBAL_set_CODEPARA_data(CODEPARA *cpara,
									int w,//٤�޻����С
									int datanum,//k
									int codenum,//m
									int totnum,//n
									int pronum,//d
									int sectornum//�����������Ŀ���
									)
{
	cpara->w=w;
	cpara->datanum=datanum;
	cpara->codenum=codenum;//m
	cpara->totnum=totnum;//n
	cpara->pronum=pronum;//d
	cpara->sectornum=sectornum;//�����������Ŀ���
	return TRUE;
}
//�趨STRIPDES����ֵ
int GLOBAL_set_STRIPDES_data(STRIPDES *strdes,
									int chunknum,//ÿһ����������������,��chunk��
									DISKBLOCK *disklist,//�����disk�б�
									UINT64 *diskid,//��ǰ����id
									int disknum,//���ڵļ�һ����������������������ͨ�����������region��disk��һ��
									int chunksize//ÿһ��CHUNK�Ĵ�С���ֽ�Ϊ��λ
									)
{
	strdes->chunknum=chunknum;

	strdes->disklist=disklist;
	strdes->diskid=diskid;
	strdes->disknum=disknum;

	strdes->chunksize=chunksize;
	return TRUE;
}
//�趨CHUNKGROUP����ֵ
int GLOBAL_set_CHUNKGROUP_data(CHUNKGROUP *chkgroup,
									  CHUNK *ckgroup,//�б�
									  int groupsize//��С
									  )
{
	chkgroup->ckgroup=ckgroup;
	chkgroup->groupsize=groupsize;
	return TRUE;
}
//�趨STRIPSECTGROUP����ֵ
int GLOBAL_set_STRIPSECTGROUP_data(STRIPSECTGROUP *strsetgroup,
										  STRIPSECT *stripsectgroup,//�б�
										  int groupsize//��С
										  )
{
	strsetgroup->stripsectgroup=stripsectgroup;
	strsetgroup->groupsize=groupsize;
	return TRUE;
}
//�趨STRIPGROUP����ֵ
int GLOBAL_set_STRIPGROUP_data(STRIPGROUP *strgroup,
									  STRIP *stripgroup,//�б�
									  int groupsize//��С
									  )
{
	strgroup->stripgroup=stripgroup;
	strgroup->groupsize=groupsize;
	return TRUE;
}
//�趨DISKGROUP����ֵ
int GLOBAL_set_DISKGROUP_data(DISKGROUP *disgroup,
									 DISK *diskgroup,//�б�
									 int groupsize//��С
									 )
{
	disgroup->diskgroup=diskgroup;
	disgroup->groupsize=groupsize;
	return TRUE;
}
//�趨DEVICEGROUP����ֵ
int GLOBAL_set_DEVICEGROUP_data(DEVICEGROUP *devgroup,
									   DEVICE *devicegroup,//�б�
									   int groupsize//��С
									   )
{
	devgroup->devicegroup=devicegroup;
	devgroup->groupsize=groupsize;
	return TRUE;
}
//�趨REGIONGROUP����ֵ
int GLOBAL_set_REGIONGROUP_data(REGIONGROUP *reggroup,
									   REGION *regiongroup,//�б�
									   int groupsize//��С
									   )
{
	reggroup->regiongroup=regiongroup;
	reggroup->groupsize=groupsize;
	return TRUE;
}
//�趨CHUNKPATH����ֵ
int GLOBAL_set_CHUNKPATH_data(CHUNKPATH *chkpath,
									 UINT64 regionid,int regionarrayid,REGION *regionptr,//regionָ��
									 UINT64 stripid,int striparrayid,STRIP *stripptr,//stripָ��
									 UINT64 stripsectid,int stripsectarrayid,STRIPSECT *stripsectptr,//stripsectָ��
									 UINT64 chunkid,int chunkarrayid,CHUNK *chunkptr//ָ��ǰchunk
									 )
{
	chkpath->regionid=regionid;
	chkpath->regionarrayid=regionarrayid;
	chkpath->regionptr=regionptr;//regionָ��
									 
	chkpath->stripid=stripid;
	chkpath->striparrayid=striparrayid;
	chkpath->stripptr=stripptr;//stripָ��
									 
	chkpath->stripsectid=stripsectid;
	chkpath->stripsectarrayid=stripsectarrayid;
	chkpath->stripsectptr=stripsectptr;//stripsectָ��

	chkpath->chunkid=chunkid;
	chkpath->chunkarrayid=chunkarrayid;
	chkpath->chunkptr=chunkptr;//ָ��ǰchunk
	return TRUE;
}
//�趨FILEINF����ֵ
int GLOBAL_set_FILEINF_data(FILEINF *finf,UINT64 fileid,UINT64 *chunkid,FILEMETA *filemeta,
								   CHUNKPATH *chkpath,CHUNKBLOCK *chunklist,int chunknum,//chun�б�
								   REGION *regionptr,UINT64 regionid,//regionָ��
								   DEVICEBLOCK *devicelist,UINT64 *deviceid,int devicenum,//�豸�б�
								   DISKBLOCK *disklist,UINT64 *diskid,int disknum,//�洢���б�
								   STRIPBLOCK *striplist,UINT64 *stripid,int stripnum,//�����б�
								   STRIPSECTBLOCK *stripsectlist,UINT64 *stripsectid,int stripsectnum//���������б�
								   )
{
	finf->fileid=fileid;
	finf->chunkid=chunkid;
	finf->filemeta=filemeta;
								   
	finf->chkpath=chkpath;
	finf->chunklist=chunklist;
	finf->chunknum=chunknum;//chun�б�
								   
	finf->regoinptr=regionptr;
	finf->regionid=regionid;//regionָ��
								   
	finf->devicelist=devicelist;
	finf->deviceid=deviceid;
	finf->devicenum=devicenum;//�豸�б�
								   
	finf->disklist=disklist;
	finf->diskid=diskid;
	finf->disknum=disknum;//�洢���б�
								   
	finf->striplist=striplist;
	finf->stripid=stripid;
	finf->stripnum=stripnum;//�����б�
								   
	finf->stripsectlist=stripsectlist;
	finf->stripsectid=stripsectid;
	finf->stripsectnum=stripsectnum;//���������б�
	return TRUE;
}
//�趨FILEMETA����ֵ
int GLOBAL_set_FILEMETA_data(FILEMETA *fmeta,char *filename,UINT64 filesize,int ACList,int filetype,
									REGION *regionptr,UINT64 regionid,//�ϲ�regionָ��
									struct USERPROFILE *userinf,UINT64 userid,//�ļ�������
									UINT64 parentid,FILEMETA *parentptr,//��һ���ļ���
									UINT64 *subfileidlist,FILEMETABLOCK *subfilelist,int subfilenum,//�ļ���ָ����Ҫָ��ǰĿ¼��һ��Ԫ���ݿ�
									struct tm *createtime,
									struct tm *updatetime,
									FILEINF *filechunkinf//���ڴ�����ݿ���Ϣ
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
	fmeta->parentptr=parentptr;//��һ���ļ���
									
	
	fmeta->subfileidlist=subfileidlist;
	fmeta->subfilelist=subfilelist;//�ļ���ָ����Ҫָ��ǰĿ¼��һ��Ԫ���ݿ�;
	fmeta->subfilenum=subfilenum;
	
	fmeta->createtime=createtime;
	fmeta->updatetime=updatetime;

	fmeta->filechunkinf=filechunkinf;
	return TRUE;
}
//�û��ĵ�ǰ
int GLOBAL_set_USERLOCATION_data(USERLOCATION *ulac,UINT64 DICid,FILEMETA *DICmetaptr,char *DICpath)
{
	ulac->DICid=DICid;
	ulac->DICmetaptr=DICmetaptr;
	ulac->DICpath=DICpath;
	return TRUE;
}
//�趨�û�����ϢidΪ��һ������id
int GLOBAL_set_USERPROFILE_data(USERPROFILE *upro,
									char *username,char *password,
									USERLOCATION *userlocinf,int userprivil,//�û���Ϣ
									struct tm *createtime//����ʱ��
									)
{
	upro->username=username;
	upro->password=password;
	upro->userlocinf=userlocinf;
	upro->userprivil=userprivil;
	upro->createtime=createtime;
	return TRUE;
}
int GLOBAL_set_USERGROUP_data(USERGROUP *ugroup,USERPROFILE *userlist,int groupsize)//�û����趨
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
								UINT64 glofileid,UINT64 glouserid)//�趨һ�¸����Է����ϵͳ���
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
//6��ʵ����Ӧ������������
//�Զ�����һ����CHUNK���ݽṹ���ұ��Ϊ��һ��Ŀ��
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

	//����趨���
	chk.ChunkID=get_state_glochunkid();
	set_state_glochunkid_add(1);
	return chk;

}
//�Զ�����һ����STRIPSECT���ݽṹ���ұ��Ϊ��һ��Ŀ��
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

	//����趨���
	strset.StripsectID=get_state_glostripsectid();
	set_state_glostripsectid_add(1);
	return strset;
}
//�Զ�����һ����STRIP���ݽṹ���ұ��Ϊ��һ��Ŀ��
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
	//����趨���
	str.StripID=get_state_glostripid();
	set_state_glostripid_add(1);
	return str;
}
//�Զ�����һ����DISK���ݽṹ���ұ��Ϊ��һ��Ŀ��
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

	//����趨���
	dis.DiskID=get_state_glodiskid();
	set_state_glodiskid_add(1);
	return dis;
}
//�Զ�����һ����DEVICE���ݽṹ���ұ��Ϊ��һ��Ŀ��
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

	//����趨���
	dev.DeviceID=get_state_glodeviceid();
	set_state_glodeviceid_add(1);
	return dev;
}
//�Զ�����һ����REGION���ݽṹ���ұ��Ϊ��һ��Ŀ��
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
	//����趨���
	reg.RegionID=get_state_gloregionid();
	set_state_gloregionid_add(1);
	return reg;
}
//�趨����
int GLOBAL_set_CHUNK_data(CHUNK *chk,int isparity,CHUNKPATH *chkpath,int sizenum,//������Ϣ
								 BYTE* chunkcontent,//����
								 UINT64 regionid,REGION *regionptr,//��һ��region��ָ��
								 UINT64 stripid,STRIP *stripptr,//��һ��strip��ָ��
								 UINT64 stripsectid,STRIPSECT *stripsectptr,//��һ��stripsect��ָ��
								 UINT64 diskid,DISK *diskptr,//��һ��disk��ָ��
								 UINT64 deviceid,DEVICE *deviceptr,//��һ��device��ָ��
								 UINT64 fileid,FILEMETA *fmeta,//�����ļ�Ԫ����
								 int storestate//��ǰ��洢״̬
								 )//�趨��ǰCHUNK�е�����
{
	chk->isparity=isparity;
	chk->chkpath=chkpath;
	chk->sizenum=sizenum;//������Ϣ							
	chk->chunkcontent=chunkcontent;//����
	
	chk->regionid=regionid,
	chk->regionptr=regionptr;//��һ��region��ָ��
								
	chk->stripid=stripid,
	chk->stripptr=stripptr,//��һ��strip��ָ��
								 
	chk->stripsectid=stripsectid;
	chk->stripsectptr=stripsectptr,//��һ��stripsect��ָ��
								 
	chk->diskid=diskid;
	chk->diskptr=diskptr;//��һ��disk��ָ��
								 
	chk->deviceid=deviceid;
	chk->deviceptr=deviceptr;//��һ��device��ָ��
								 
								 
	chk->fileid=fileid;
	chk->fmeta=fmeta,//�����ļ�Ԫ����
								 
	chk->storestate=storestate;//��ǰ��洢״̬
	return TRUE;				
}
int GLOBAL_set_STRIPSECT_data(STRIPSECT *strset,int isparity,UINT64 *chunkid,CHUNKGROUP *chunklist,int chunksize,int chunknum,//chunk�б�
									 UINT64 regionid,REGION *regionptr,//��һ��regionָ��
									 UINT64 stripid,STRIP *stripptr,//��һ��stripָ��
									 UINT64 diskid,DISK *diskptr,//��һ��diskָ��
									 UINT64 deviceid,DEVICE *deviceptr,//��һ��deviceָ��
									 char *filename,char *filepath,//·��
									 int storestate//��ǰ�洢״̬
									 )//�趨��ǰSTRIPSECT�е�����
{
	strset->chunkid=chunkid;

	strset->isparity=isparity;
	strset->chunklist=chunklist;
	strset->chunksize=chunksize;
	strset->chunknum=chunknum;//chunk�б�

	strset->regionid=regionid;
	strset->regionptr=regionptr;//��һ��regionָ��
									 
	strset->stripid=stripid;
	strset->stripptr=stripptr;//��һ��stripָ��
	
	strset->diskid=diskid;
	strset->diskptr=diskptr;//��һ��diskָ��
									 
	strset->deviceid=deviceid;
	strset->deviceptr=deviceptr,//��һ��deviceָ��
									 
	strset->filename=filename;
	strset->filepath=filepath;//·��
									 
	strset->storestate=storestate;//��ǰ�洢״̬
	return TRUE;
}
int GLOBAL_set_STRIP_data(STRIP *str,STRIPDES *strdes,//��������
								 DISKBLOCK *disklist,UINT64 *diskid,int disknum,//�����洢������
								 DEVICEBLOCK *devicelist,UINT64 *deviceid,int devicenum,//�豸�б�
								 STRIPSECTGROUP *stripsectlist,UINT64 *stripsectid,int strsetnum,//Strset�б�
								 CHUNKGROUP *chunklist,UINT64 *chunkid,int chunknum,//chunk�б�
								 UINT64 regionid,REGION *regionptr,//��һ��regionָ��
								 int storestate//��ǰ�洢״̬
								 )//�趨��ǰSTRIP�е�����
{
	str->strdes=strdes;//��������
								 
	str->disklist=disklist;
	str->diskid=diskid;
	str->disknum=disknum;//�����洢������

	str->devicelist=devicelist;//�豸�б�
	str->deviceid=deviceid;
	str->devicenum=devicenum;
								 
	str->stripsectlist=stripsectlist;
	str->stripsectid=stripsectid;
	str->strsetnum=strsetnum;//Strset�б�
								 
	str->chunklist=chunklist;
	str->chunkid=chunkid;
	str->chunknum=chunknum,//chunk�б�

	str->regionid=regionid;
	str->regionptr=regionptr;//��һ��regionָ��
								 
	str->storestate=storestate;//��ǰ�洢״̬
	return TRUE;
}
int GLOBAL_set_DISK_data(DISK *dis,int DiskTYPE,int capability,UINT64 volumn,
								REGIONBLOCK *regionlist,UINT64 *regionid,int regionnum,//�洢���ϰ�����region����
								DEVICE *deviceptr,UINT64 deviceid,//��һ���device���
								char *diskpath,//�ؼ���Ϣ��ǰ���̵�����·��
								int storestate//��ǰ�洢״̬	
								)//�趨��ǰDISK�е�����
{
	dis->DiskTYPE=DiskTYPE;
	dis->capability=capability;
	dis->volumn=volumn;


	dis->regionlist=regionlist;
	dis->regionid=regionid;
	dis->regionnum=regionnum;//�洢���ϰ�����region����
								
	dis->deviceptr=deviceptr;
	dis->deviceid=deviceid;//��һ���device���
								
	dis->diskpath=diskpath;//�ؼ���Ϣ��ǰ���̵�����·��
								
	dis->storestate=storestate;//��ǰ�洢״̬	
	return TRUE;
								
}
int GLOBAL_set_DEVICE_data(DEVICE *div,int Devicetype,int processnum,int *speed,
								  DISKBLOCK *disklist,UINT64 *diskid,int disknum,//�洢���б�
								  REGIONBLOCK *regionlist,UINT64 *regionid,int regionnum,//region�б�
								  int storestate//��ǰ�洢״̬
								  )//�趨��ǰDEVICE�е�����
{
	div->Devicetype=Devicetype;
	div->processnum=processnum;
	div->speed=speed;
								  
	div->diskid=diskid;
	div->disklist=disklist;
	div->disknum=disknum;//�洢���б�
								  
	div->regionlist=regionlist;
	div->regionid=regionid;
	div->regionnum=regionnum;//region�б�
								  
	div->storestate=storestate;//��ǰ�洢״̬
	return TRUE;
}
int GLOBAL_set_REGION_data(REGION *reg,int codetype,CODEPARA *codepara,UINT64 totalsize,
								  FILEMETABLOCKGROUP *filemetalist,UINT64 *fileid,int filenum,//������file���б�
								  DISKBLOCK *disklist,UINT64 *diskid,int disknum,//Disk���б�
								  DEVICEBLOCK *devicelist,UINT64 *deviceid,int devicenum,//device�б�
								  STRIPDES *strdes,STRIPGROUP *striplist,UINT64 *stripid,int stripnum,//��������
								  UINT64 chunknum,UINT64 stripsectnum,//chunk��stripsect����
								  FILEMETA *fileroot,UINT64 rootfileid,//���ļ�ָ��
								  int storestate//��ǰ�洢״̬
								  )//�趨��ǰREGION�е�����

{
	reg->codetype=codetype;
	reg->codepara=codepara;
	reg->totalsize=totalsize;

	reg->filemetalist=filemetalist;
	reg->fileid=fileid;
	reg->filenum=filenum;//������file���б�

	reg->disklist=disklist;
	reg->diskid=diskid;
	reg->disknum=disknum;//Disk���б�

	reg->devicelist=devicelist;
	reg->deviceid=deviceid;
	reg->devicenum=devicenum;//device�б�

	reg->strdes=strdes;
	reg->striplist=striplist;
	reg->stripid=stripid;
	reg->stripnum=stripnum;//��������

	reg->chunknum=chunknum;
	reg->stripsectnum=stripsectnum;//chunk��stripsect����
		
	reg->fileroot=fileroot;
	reg->rootfileid=rootfileid;//���ļ�ָ��

	reg->storestate=storestate;//��ǰ�洢״̬
	return TRUE;
}

//������Ӧ�������
//��ǰʵ�ֵ�RAID6��RDP��EVENODD��MDR��MSR��FMSR��EMSR��MBR��EMBR
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
		//˵��û�г�ʼ��
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
//����ϵͳ����
int reset_state()//ͳͳ������
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
//���Ӷ����ͳ�Ʋ���
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

//���������ͳ�Ʋ���
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

//������й�ͳ�Ʋ���
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


//��ʼ��ȫ��id
int intial_globalid(UINT64 gloregionid,UINT64 glostripid,UINT64 glostripsectid,UINT64 glodeviceid,UINT64 glodiskid,UINT64 glochunkid,UINT64 glofileid,UINT64 glouserid)
{
	//����ϵͳid���и�ֵ
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
	//����ϵͳid���и�ֵ
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
//����ϵͳregionid����
int set_state_gloregionid_add(UINT64 regnum)
{
	systemid.gloregionid+=regnum;
	return TRUE;
}
//����ϵͳstripid����
int set_state_glostripid_add(UINT64 stripnum)
{
	systemid.glostripid+=stripnum;
	return TRUE;
}
//����ϵͳstripsectid����
int set_state_glostripsectid_add(UINT64 stripsectnum)
{
	systemid.glostripsectid+=stripsectnum;
	return TRUE;
}
//����ϵͳdeviceid����
int set_state_glodeviceid_add(UINT64 devicenum)
{
	systemid.glodeviceid+=devicenum;
	return TRUE;
}
//����ϵͳdiskid����
int set_state_glodiskid_add(UINT64 disknum)
{
	systemid.glodiskid+=disknum;
	return TRUE;
}
//����ϵͳchunkid����
int set_state_glochunkid_add(UINT64 chunknum)
{
	systemid.glochunkid+=chunknum;
	return TRUE;
}
//����ϵͳfileid����
extern int set_state_glofileid_add(UINT64 filenum)
{
	systemid.glofileid+=filenum;
	return TRUE;
}
//����ϵͳuserid����
int set_state_glouserid_add(UINT64 usernum)
{
	systemid.glouserid+=usernum;
	return TRUE;
}

//��ȡϵͳregionid
UINT64 get_state_gloregionid()
{
	return systemid.gloregionid;
}
//��ȡϵͳstripid
UINT64 get_state_glostripid()
{
	return systemid.glostripid;
}
//��ȡϵͳstripsectid
UINT64 get_state_glostripsectid()
{
	return systemid.glostripsectid;
}
//��ȡϵͳdeviceid
UINT64 get_state_glodeviceid()
{
	return systemid.glodeviceid;
}
//��ȡϵͳdiskid
UINT64 get_state_glodiskid()
{
	return systemid.glodiskid;
}
//��ȡϵͳchunkid
UINT64 get_state_glochunkid()
{
	return systemid.glochunkid;
}
//��ȡϵͳfileid
UINT64 get_state_glofileid()
{
	return systemid.glofileid;
}
//��ȡϵͳuserid
UINT64 get_state_glouserid()
{
	return systemid.glouserid;
}

//next_id
//�趨ϵͳid��
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
//����ָ��
IDITEM *get_SYSID_PTR()
{
	return &systemid;
}

STATSITEM* get_stats_PTR()
{
	return &systemstatic;
}

//֮��汾�Ӵ˴���ʼ
//�趨·�����ݺ�region���ݺ��û�����
int set_state_glopath(char *glopath)//�趨ȫ��·��
{
	grometadatapath=glopath;
	return TRUE;
}
char *get_state_glopath_PTR()//��ȡȫ��·��
{
	return grometadatapath;
}

//�趨ȫ��device��
//�趨��ǰ��devicegroup
int set_state_glodevicegroup(DEVICEGROUP *devgroup)
{
	grodevicelist.devicegroup=devgroup->devicegroup;
	grodevicelist.groupsize=devgroup->groupsize;
	return TRUE;
}
//�õ���ǰ��devicegroupָ��
DEVICEGROUP *get_state_glodevicegroup_PTR()
{
	return &grodevicelist;
}

//�趨ȫ��disk��
//�趨��ǰ��diskgroup
int set_state_glodiskgroup(DISKGROUP *diskgroup)
{
	grodisklist.diskgroup=diskgroup->diskgroup;
	grodisklist.groupsize=diskgroup->groupsize;
	return TRUE;
}
//�õ���ǰ��diskgroupָ��
DISKGROUP *get_state_glodiskgroup_PTR()
{
	return &grodisklist;
}

//�趨ȫ��id
//����ȫ��id·��
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
//��ȡȫ��id·��
GLOSYSTEMID *get_state_glosystemidgroup_PTR()
{
	return &grosysid;
}
//�趨ȫ��������
int set_state_gloregiongroup(REGIONGROUP *reggroup)//�趨��ǰ��regiongroup
{
	groregionlist.regiongroup=reggroup->regiongroup;
	groregionlist.groupsize=reggroup->groupsize;
	return TRUE;
}
int set_state_gloregiongroup_add(REGION *regionptr)//�ڵ�ǰ��regiongroup�м���һ��region
{
	REGION *regionlistptr,*newregionptr;//����ָ��
	int groupsize,i;//��С�Լ�i
	REGION *freeloc;//��һ�����Բ����λ��
	freeloc=NULL;//�������ƿ�
	//��ȡ����
	regionlistptr=groregionlist.regiongroup;
	groupsize=groregionlist.groupsize;
	for(i=0;i<groupsize;i++)//�ȼ���ǲ��ǵ�ǰ�������е�Ԫ��
	{
		//������ǰָ���ǲ��Ǵ���
		if(regionptr==regionlistptr)
		{
			show_error("global_define","gloregiongroup_add","region is exist");
			return FALSE;
		}
		
		//������һ������ʹ�õ�λ��
		if(regionlistptr->RegionID==NOVALUE)//�����ǰΪ��Ч
		{
			i--;
			freeloc=regionlistptr;//��freelocָ��ǰ���ݿ�
		}
		regionlistptr++;//������һ��
	}
	groupsize+=1;//�����С����1��
	regionlistptr=groregionlist.regiongroup;//�ö�
	//������ת������һ���հ״�
	if(freeloc==NULL)
	{
		//˵������������Ҫ���·���
		newregionptr=ralloc(REGION,groupsize,regionlistptr);//�������ſռ�
		groregionlist.regiongroup=newregionptr;//�����ݵ�ָ�����¶�λ
		//�����ݴ洢�����һ������
		newregionptr=newregionptr+groupsize;
	}
	else
	{
		//���������¶�λ���µ�λ��
		newregionptr=freeloc;//������Ч�������
	}
	memcpy(newregionptr,regionptr,sizeof(REGION));//���临�ƹ�ȥ
	return TRUE;
}
int set_state_gloregiongroup_del_ID(UINT64 regionid)//��ָ����regionɾ��region
{
	//�������趨Ϊ�ռ���
	int i,groupsize;
	UINT64 currentid;
	REGION *regionlistptr;
	//���и�ֵ
	regionlistptr=groregionlist.regiongroup;
	groupsize=groregionlist.groupsize;
	for(i=0;i<groupsize;i++)
	{
		currentid=regionlistptr->RegionID;//��ȡ��ǰid
		if(currentid==regionid)
		{
			//����ҵ����Ϊ��Ч������ȷ
			regionlistptr->RegionID=NOVALUE;
			groregionlist.groupsize=groupsize-1;
			return TRUE;
		}
		regionlistptr=regionlistptr++;
	}
	show_error("global_define","gloregiongroup_del","region isn't exist");
	return FALSE;
}
int set_state_gloregiongroup_del_PTR(REGION *regionptr)//ָ����regionɾ��region
{
	//�������趨Ϊ�ռ���
	int i,groupsize;
	//UINT64 currentid;
	REGION *regionlistptr;
	//���и�ֵ
	regionlistptr=groregionlist.regiongroup;
	groupsize=groregionlist.groupsize;
	for(i=0;i<groupsize;i++)
	{
		//currentid=regionlistptr->RegionID;//��ȡ��ǰid
		if(regionlistptr==regionptr)
		{
			//����ҵ����Ϊ��Ч������ȷ
			regionlistptr->RegionID=NOVALUE;
			groregionlist.groupsize=groupsize-1;
			return TRUE;
		}
		regionlistptr=regionlistptr++;
	}
	show_error("global_define","gloregiongroup_del","region isn't exist");
	return FALSE;
}
REGIONGROUP *get_state_gloregiongroup_PTR()//�õ���ǰ��regionָ��
{
	
	return &groregionlist;
}

//�趨�û���
int set_state_glousergroup(USERGROUP *ugroup)//�趨��ǰ�û���
{
	grouserlist.userlist=ugroup->userlist;
	grouserlist.groupsize=ugroup->groupsize;
	return TRUE;
}
int set_state_glousergroup_add(USERPROFILE *userprofileptr)//�ڵ�ǰ��usergroup�м���һ��userprofile
{
	//���в���
	USERPROFILE *userlistptr,*newruserlistptr;//����ָ��
	int groupsize,i;//��С�Լ�i
	USERPROFILE *freeloc;//��һ�����Բ����λ��
	freeloc=NULL;//�������ƿ�
	//��ȡ����
	userlistptr=grouserlist.userlist;
	groupsize=grouserlist.groupsize;
	for(i=0;i<groupsize;i++)//�ȼ���ǲ��ǵ�ǰ�������е�Ԫ��
	{
		//������ǰָ���ǲ��Ǵ���
		if(userprofileptr==userlistptr)
		{
			show_error("global_define","glousergroup_add","userlist is exist");
			return FALSE;
		}
		
		//������һ������ʹ�õ�λ��
		if(userlistptr->UserID==NOVALUE)//�����ǰΪ��Ч
		{
			i--;
			freeloc=userlistptr;//��freelocָ��ǰ���ݿ�
		}
		userlistptr++;//������һ��
	}
	groupsize+=1;//�����С����1��
	userlistptr=grouserlist.userlist;//�����ö�
	//������ת������һ���հ״�
	if(freeloc==NULL)
	{
		//˵������������Ҫ���·���
		newruserlistptr=ralloc(USERPROFILE,groupsize,userlistptr);//�������ſռ�
		grouserlist.userlist=newruserlistptr;//�����ݵ�ָ�����¶�λ
		//�����ݴ洢�����һ������
		newruserlistptr=newruserlistptr+groupsize;
	}
	else
	{
		//���������¶�λ���µ�λ��
		newruserlistptr=freeloc;//������Ч�������
	}
	mcpy(newruserlistptr,userprofileptr,REGION,1);//���临�ƹ�ȥ
	return TRUE;
	return TRUE;
}
int set_state_glousergroup_del_ID(UINT64 userprofileid)//����idɾ��userprofile
{
	USERPROFILE *userlistptr;
	//��������߼�һ��
	int i,groupsize;
	UINT64 currentid;
	//��ȡ����
	userlistptr=grouserlist.userlist;
	groupsize=grouserlist.groupsize;
	for(i=0;i<groupsize;i++)
	{
		currentid=userlistptr->UserID;
		if(currentid==userprofileid)
		{
			//�ҵ����Ϊ��Ч
			userlistptr->UserID=NOVALUE;
			grouserlist.groupsize=groupsize-1;
			return TRUE;
		}
		userlistptr++;
	}
	show_error("global_define","glousergroup_del","user isn't exist");
	return FALSE;
}
int set_state_glousergroup_del_PTR(USERPROFILE *userprofileptr)//����ָ��ɾ��userprofile
{
	USERPROFILE *userlistptr;
	//��������߼�һ��
	int i,groupsize;
	//UINT64 currentid;
	//��ȡ����
	userlistptr=grouserlist.userlist;
	groupsize=grouserlist.groupsize;
	for(i=0;i<groupsize;i++)
	{
		//currentid=userlistptr->UserID;
		if(userlistptr==userprofileptr)
		{
			//�ҵ����Ϊ��Ч
			userlistptr->UserID=NOVALUE;
			grouserlist.groupsize=groupsize-1;
			return TRUE;
		}
		userlistptr++;
	}
	show_error("global_define","glousergroup_del","user isn't exist");
	return FALSE;
}
USERGROUP *get_state_glousergroup_PTR()//����ϵͳ�û���ָ��
{
	return &grouserlist;
}

//�л���ǰ�û�
int set_state_glosysuserptr(UINT64 userid,USERPROFILE *useprofileptr)//�趨��ǰϵͳ�û�ָ��
{
	sysuserptr.userid=userid;
	sysuserptr.userprofileptr=useprofileptr;
	return TRUE;
}
int set_state_glosysuserptr_SYSTEMUSERPTR(SYSTEMUSERPTR *sysuserlistptr)//ʹ��ָ�����趨��ǰָ��
{
	sysuserptr.userid=sysuserlistptr->userid;
	sysuserptr.userprofileptr=sysuserlistptr->userprofileptr;
	return TRUE;
}
SYSTEMUSERPTR *get_state_glosysuserptr_PTR()//���ص�ǰϵͳ�û���ָ��
{
	return &sysuserptr;
}
UINT64 get_state_glosysuserptr_ID()//���ص�ǰϵͳ�û��ı��
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

//ȫ��Ԫ����·��
extern int set_state_glometapath(char *grometapath)
{
	grometadatapath=grometapath;
	return TRUE;
}
extern char *get_state_glometapath()
{
	return grometadatapath;
}

//ȫ�ֱ����б��
//��ȡ��������
int get_state_avail_kind_number()
{
	return availnum;
}
//��ȡ�����б�
int *get_state_avail_kind()
{
	return availkind;
}
//�趨ȫ����������
int set_state_avail_kind_number(int kindnum)
{
	availnum=kindnum;
	return TRUE;
}
//�趨ȫ����������
int set_state_avail_kind(int *kindlist)
{
	availkind=kindlist;
	return TRUE;
}

//���û�ȡ�������
//��ȡ�������
GLOPUSHLIST *get_state_buffer_pushlist()
{
	return &gropushlist;
}
//����pushtime
int get_state_buffer_push_time()
{
	return gropushlist.glopushtime;
}
//����pushʱ��
struct tm *get_state_buffer_last_push_time()
{
	return gropushlist.glolastpushtime;
}
//�趨�������
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
//�趨pushtimeʱ��
int set_state_buffer_push_time(int ptime)
{
	gropushlist.glopushtime=ptime;
	return TRUE;
}
//�趨�ϴ�pushʱ��
int set_state_buffer_last_push_time(struct tm *ltime)
{
	gropushlist.glolastpushtime=ltime;
	return TRUE;
}
//maximum��������С
int set_state_buffer_maxbuffersize(UINT64 maxbuffersize)
{
	gropushlist.maxbuffersize=maxbuffersize;
	return TRUE;
}
//��ǰ��������С
int set_state_buffer_currentbuffersize(UINT64 currentbuffersize)
{
	gropushlist.currentbuffersize=currentbuffersize;
	return TRUE;
}
//�趨�ͻ�ȡȫ��dirty��talistָ��
//��ȡȫ��������ָ��
GLODIRTYDATA *get_state_dirtydatalist()
{
	return &grodirtydatalist;
}
//����ȫ��������ָ��
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
//tempfreelisty����
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

//��ȡʱ��
struct tm *get_system_time()
{
	time_t raw_time;
	struct tm *timeinfo; 
	time(&raw_time);
	timeinfo=localtime(&raw_time);
	return timeinfo;
}