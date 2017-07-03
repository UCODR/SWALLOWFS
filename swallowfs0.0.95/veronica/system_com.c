#include "system_com.h"
//����һ������
int systemcom_REGION_create(REGION *regionptr)
{
	int resTF;
	
	resTF=profile_region_format_PTR(regionptr);//������Ӧ�ṹ
	if(resTF==FALSE)
	{
		show_error("systemcom","REGION_create","region can't format");
		return FALSE;
	}
	//��������ɵ����ݽ��п���
	resTF=set_state_gloregiongroup_add(regionptr);
	if(resTF==FALSE)
	{
		show_error("systemcom","REGION_create","region can't add into system");
		return FALSE;
	}
	//������ͬ������ǰ��Ԫ��������
	resTF=profile_region_sync(regionptr);
	if(resTF==FALSE)
	{
		show_error("systemcom","REGION_create","region can't sync");
		return FALSE;
	}
	return TRUE;
}
//ͨ��ptrɾ��region
int systemcom_REGION_delete_ptr(REGION *regionptr)
{
	return TRUE;
}
//ͨ��idɾ��region	
int systemcom_REGION_delete_id(UINT64 regionid)
{
	return TRUE;
}

//
//����һ��device
int systemcom_DEVICE_create(DEVICE *deviceptr)
{
	
	return TRUE;
}
//ɾ��һ��device
int systemcom_DEVICE_delete_ptr(DEVICE *deviceptr)
{ 
	return TRUE;
}
//ɾ��һ��device
int systemcom_DEVICE_delete_ID(UINT64 deviceid)
{
	return TRUE;
}
//ͬ��disk
//����һ��disk
int systemcom_DISK_create(DISK *diskptr)
{
	return TRUE;
}
//ɾ��һ��disk
int systemcom_DISK_delete_PTR(DISK *diskptr)
{
	return TRUE;
}
//ɾ��һ��disk 
int systemcom_DISK_delete_ID(UINT64 diskid)
{
	return TRUE;
}

//�û�ָ��
//������Ӧ�û�
int systemcom_USER_create(USERPROFILE *userptr)
{
	return TRUE; 
}
//ɾ��ϵͳ�û�
int systemcom_USER_delete_PTR(USERPROFILE *userptr)
{
	return TRUE;
}
//ɾ��ϵͳ�û�
int systemcom_USER_delete_ID(UINT64 userid)
{
	return TRUE;
}



//�ļ���������
//�ļ�����
FILEMETA *systemcom_FILE_create_handle(char *filepath)
{
	FILEMETA *resfilemetaptr=NULL;
	//FILEMETA *regionroot;
	//��һ���Ƚ�����ǰ��·��
	REGIONGROUP *regiongroupptr;
	REGION *regionptr;

	FILEMETA *filemetaptr,*parentfilemetaptr;
	FILEMETABLOCK *fileblockptr;

	USERPROFILE *userprofileptr;//��ȡ��ǰ�û�ָ��

	//time_t rawtime;
	struct tm *createtime;
	struct tm *updatetime;

	char *filemetaname;
	int filenum;

	char *curfilenamepart,*nextfileptr;//����ÿһ��

	int j,strindex,resTF;//i���ڼ�¼�ļ��ֿ������
	//int regiongroupsize;
	UINT64 regionindex,currentid;
	UINT64 perantid,userid,regionid;
	/*//��һ���ҵ���ǰ
	strindex=7;
	i=0;
	curchar=filepath[strindex];
	strindex++;
	while(curchar!='\\')
	{
		curchar=filepath[strindex];
		curfilenamepart[i]=curchar;
		i++;
		strindex++;
	}
	curfilenamepart[i]='\0';//����β�����
	STRTOINT64(curfilenamepart,regionindex);//���ַ���ת��Ϊ��ֵ
	//�ҳ�Ŀ��������ȡ�ļ�ָ��
	regiongroupptr=get_state_gloregiongroup_PTR();
	regionptr=regiongroupptr->regiongroup;
	regiongroupsize=regiongroupptr->groupsize;
	for(i=0;i<regiongroupsize;i++)
	{
		currentid=regionptr->RegionID;
		if(currentid==regionindex)
		{
			//��ȡ����
			filemetaptr=regionptr->fileroot;
			break;
		}
		regionptr++;
	}
	if(i==regiongroupsize)
	{
		show_error("systemcom","FILE_create_handle","region can't find");
		return FALSE;
	}*/
	regionindex=profile_get_region_id(filepath);
	regionptr=profile_region_search_ptr(regionindex);
	if(regionptr==NULL)
	{
		show_error("systemcom","FILE_create_handle","regionptr can't find");
		return FALSE;
	}
	

	//��Ȼ�ѽ��ҵ��˸�ָ��Ϳɼ��������˼���������
	//i=0;
	filemetaptr=regionptr->fileroot;//��ȡ��Ŀ¼
	curfilenamepart=strstr(filepath,"\\");//Ѱ�ҵ�һ��λ��ʡȥregion
	curfilenamepart=curfilenamepart+1;//���\�������������Ҫȥ��
	parentfilemetaptr=filemetaptr;
	while(curfilenamepart!=NULL)
	{
		nextfileptr=strstr(curfilenamepart,"\\");//�ҵ���һ��λ��
		
		if(nextfileptr==NULL)//�Ѿ�����
		{
			fileblockptr=filemetaptr->subfilelist;
			filenum=filemetaptr->subfilenum;//��һ���ж��ٸ����ļ���
			parentfilemetaptr=filemetaptr;//��ס�Ա�����
			if(fileblockptr!=NULL)
			{
				for(j=0;j<filenum;j++)
				{
				
					filemetaptr=fileblockptr->filemetaptr;
					currentid=filemetaptr->FileID;
					filemetaname=filemetaptr->filename;//��ȡ��ǰ�ļ�����
					resTF=strcmp(curfilenamepart,filemetaname);
					if(currentid!=NOVALUE)//�����ǰĿ¼û��ûɾ��
					{
						if(resTF==0)
						{
							//�������һ�£�������һ��Ŀ¼����
							curfilenamepart=nextfileptr;//��ֵΪNULL
							break;
						}
					}
					fileblockptr++;
				}
			}
			else
			{
				j=filenum;
			}
			resfilemetaptr=filemetaptr;//���Ǽ����Ѿ��ҵ�
			if(j==filenum)//û�ҵ�����һ���յĲ��ҽ�ָ����и�ֵ
			{
				resfilemetaptr=talloc(FILEMETA,1);//û���ҵ��Ļ��������µ�
				if(filemetaptr==NULL)
				{
					show_error("systemcom","FILE_create_handle","No memory");
					return NULL;
				}
				perantid=parentfilemetaptr->FileID;//���ϼ���id���и�ֵ
				//��ȡ��ǰ�û�
				userprofileptr=get_state_glosysuserptr_userprofile();
				userid=userprofileptr->UserID;
				//��ȡ��ǰregion���
				regionid=regionptr->RegionID;
				//��ȡ��ǰʱ��
				//time(&rawtime);
				createtime=get_system_time();//ת����ǰʱ��
				updatetime=get_system_time();
				//��ʼ��ֵ
				//��ǰ��û�����ָ��
				resfilemetaptr->FileID=get_state_glofileid();//��ȡϵͳfileid
				set_state_glofileid_add(1);//����ϵͳfileid����
				GLOBAL_set_FILEMETA_data(resfilemetaptr,curfilenamepart,NOVALUE,NOVALUE,FILEKIND,
									regionptr,regionid,//�ϲ�regionָ��
									userprofileptr,userid,//�ļ�������
									perantid,parentfilemetaptr,//��һ���ļ���
									NULL,NULL,NONE,//�ļ���ָ����Ҫָ��ǰĿ¼��һ��Ԫ���ݿ�
									createtime,
									updatetime,
									NULL//���ڴ�����ݿ���Ϣ
									);//�趨FILEMETA����ֵ 
				curfilenamepart=nextfileptr;
			}
		}
		else
		{
			//��ǰΪ�ļ���
			fileblockptr=filemetaptr->subfilelist;
			filenum=filemetaptr->subfilenum;
			if((fileblockptr==NULL)||(filenum=0))
			{
				show_error("systemcom","FILE_create_handle","dictionary have no subfile");
				return NULL;

			}
			for(j=0;j<filenum;j++)
			{
				
				filemetaptr=fileblockptr->filemetaptr;
				parentfilemetaptr=filemetaptr;//��ָ������
				currentid=filemetaptr->FileID;
				filemetaname=filemetaptr->filename;//��ȡ��ǰ�ļ�����
				resTF=strcmp(curfilenamepart,filemetaname);
				if(currentid!=NOVALUE)//�����ǰĿ¼û��ûɾ��
				{
					if(resTF==0)
					{
						//�������һ�£�������һ��Ŀ¼����
						break;
					}
				}
				fileblockptr++;
			}
			if(j==filenum)
			{
				show_error("systemcom","FILE_create_handle","the dictionary can't find");
				return NULL;
			}
			//i=0;//Ѱ����ɽ�partָ����0
			break;
			nextfileptr=nextfileptr+1;
			curfilenamepart=nextfileptr;//��ָ�������ƶ�һ��λ��
		}
	}
	/*while(curchar!='/0')//ɨ�赽�ļ�β
	{
		curchar=filepath[strindex];//������
		switch(curchar)
		{
		case '\\':
			//˵��֮ǰ�������Ѿ����
			fileblockptr=filemetaptr->subfilelist;
			filenum=filemetaptr->subfilenum;
			for(j=0;j<filenum;j++)
			{
				
				filemetaptr=fileblockptr->filemetaptr;
				currentid=filemetaptr->FileID;
				filemetaname=filemetaptr->filename;//��ȡ��ǰ�ļ�����
				resTF=strcmp(curfilenamepart,filemetaname);
				if(currentid!=NOVALUE)//�����ǰĿ¼û��ûɾ��
				{
					if(resTF==0)
					{
						//�������һ�£�������һ��Ŀ¼����
						break;
					}
				}
				fileblockptr++;
			}
			if(j==filenum)
			{
				show_error("systemcom","FILE_create_handle","the dictionary can't find");
				return FALSE;
			}
			i=0;//Ѱ����ɽ�partָ����0
			break;
		case '\0':
			//��ǰ�����Ѿ�������,�ж��ǲ��ǵ�ǰ��������ļ��еĻ������ص�ǰ�ļ�Ԫ���ݾ����û�оʹ���һ��
			fileblockptr=filemetaptr->subfilelist;
			parentfilemetaptr=filemetaptr;//��ס�Ա�����
			for(j=0;j<filenum;j++)
			{
				
				filemetaptr=fileblockptr->filemetaptr;
				currentid=filemetaptr->FileID;
				filemetaname=filemetaptr->filename;//��ȡ��ǰ�ļ�����
				resTF=strcmp(curfilenamepart,filemetaname);
				if(currentid!=NOVALUE)//�����ǰĿ¼û��ûɾ��
				{
					if(resTF==0)
					{
						//�������һ�£�������һ��Ŀ¼����
						break;
					}
				}
				fileblockptr++;
			}
			resfilemetaptr=filemetaptr;//���Ǽ����Ѿ��ҵ�
			if(j==filenum)//û�ҵ�����һ���յĲ��ҽ�ָ����и�ֵ
			{
				resfilemetaptr=talloc(FILEMETA,1);//û���ҵ��Ļ��������µ�
				if(filemetaptr==NULL)
				{
					show_error("systemcom","FILE_create_handle","No memory");
					return FALSE;
				}
				perantid=parentfilemetaptr->FileID;//���ϼ���id���и�ֵ
				//��ȡ��ǰ�û�
				userprofileptr=get_state_glosysuserptr_userprofile();
				userid=userprofileptr->UserID;
				//��ȡ��ǰregion���
				regionid=regionptr->RegionID;
				//��ȡ��ǰʱ��
				//time(&rawtime);
				createtime=get_system_time();//ת����ǰʱ��
				updatetime=get_system_time();
				//��ʼ��ֵ
				resfilemetaptr->FileID=NOVALUE;//��ǰ��û�����ָ��
				GLOBAL_set_FILEMETA_data(resfilemetaptr,curfilenamepart,NOVALUE,NOVALUE,FILEKIND,
									regionptr,regionid,//�ϲ�regionָ��
									userprofileptr,userid,//�ļ�������
									perantid,parentfilemetaptr,//��һ���ļ���
									NULL,NULL,NOVALUE,//�ļ���ָ����Ҫָ��ǰĿ¼��һ��Ԫ���ݿ�
									createtime,
									updatetime,
									NULL//���ڴ�����ݿ���Ϣ
									);//�趨FILEMETA����ֵ
			}
			break;
		default:
			//���߶�����
			curfilenamepart[i]=curchar;
			//i++;
			break;
		}
		strindex++;
	}*/
	return resfilemetaptr;
}
//�ļ�ɾ��
int systemcom_FILE_delete(FILEMETA *fmeta)
{
	return TRUE;
}
//�ļ���ȡ
int systemcom_FILE_read(FILEMETA *fmeta,BYTESTREAM *bstream)
{
	return TRUE;
}
//�ļ�����д�൱��"w"
int systemcom_FILE_write_overwrite(FILEMETA *fmeta,BYTESTREAM *bstream)
{
	return TRUE;
}
//�Ǹ���д
int systemcom_FILE_write_change(FILEMETA *fmeta,BYTESTREAM *bstream,int offset)
{
	return TRUE;
}
//�ļ����
int systemcom_FILE_append(FILEMETA *fmeta,BYTESTREAM *bstream)
{
	return TRUE;
}
//�ļ���һ�����򿽱�����һ·��
int systemcom_FILE_duplicate(FILEMETA *soufmeta,FILEMETA *desfmeta)
{
	return TRUE;
}
//�����޸�
//���µ�ǰ�ļ���
extern int systemcom_FILE_ACLMOD(int ACList)
{
	return TRUE;
}

//Ŀ¼ָ��
int systemcom_DICT_DIR(char *dictpath)//��ʾһ��Ŀ¼
{
	return TRUE;
}
int systemcom_DICT_DIR_rootuser()//��ʾ�û���ǰĿ¼����
{
	return TRUE;
}
int systemcom_DICT_create(char *dictpath)//ϵͳĿ¼����
{
	return TRUE;
}
int systemcom_DICT_delete(char *dictpath)//ϵͳĿ¼ɾ��
{
	return TRUE;
}
int systemcom_DICT_access(char *dictpath)//�ж�һ��Ŀ¼�Ƿ����
{
	return TRUE;
}

//ϵͳ״̬���£�����
//ϵͳ״̬����
//�㱨����״̬
int systemcom_userstate_report()
{
	int i;
	int usernum;
	USERPROFILE *userlist;
	USERGROUP *usergrouplist;
	usergrouplist=get_state_glousergroup_PTR();
	userlist=usergrouplist->userlist;
	usernum=usergrouplist->groupsize;
	for(i=0;i<usernum;i++)
	{
		profile_userprofile_info(userlist);
		userlist++;
	}
	return TRUE;
}
int systemcom_diskstate_report()
{
	int i;
	int disknum;
	DISK *diskptr;
	DISKGROUP *diskgroupptr;
	diskgroupptr=get_state_glodiskgroup_PTR();
	diskptr=diskgroupptr->diskgroup;
	disknum=diskgroupptr->groupsize;
	for(i=0;i<disknum;i++)
	{
		profile_disk_info(diskptr);
		diskptr++;
	}
	return TRUE;
}
//�㱨�豸״̬
int systemcom_devicestate_report()
{
	int i;
	DEVICEGROUP *devicegroupptr;
	DEVICE *deviceptr;
	int devicegroupsize;
	devicegroupptr=get_state_glodevicegroup_PTR();
	deviceptr=devicegroupptr->devicegroup;
	devicegroupsize=devicegroupptr->groupsize;
	for(i=0;i<devicegroupsize;i++)
	{
		profile_device_info(deviceptr);
		deviceptr++;
	}
	return TRUE;
}
//�㱨����״̬
int systemcom_regionstate_report()
{
	int i;
	REGIONGROUP *regiongroupptr;
	REGION *regionptr;
	int regiongroupsize;
	regiongroupptr=get_state_gloregiongroup_PTR();
	regionptr=regiongroupptr->regiongroup;
	regiongroupsize=regiongroupptr->groupsize;
	for(i=0;i<regiongroupsize;i++)
	{
		profile_region_info(regionptr);
		regionptr++;
	}
	return TRUE;
}


//ϵͳ��ʼ��
//ϵͳ��ʼ��,����Ԫ���ݵ�ַ��ʼ��
int systemcom_system_inital()
{
	//ֱ�ӵ���ϵͳ��ʼ��api
	profile_global_system_intial();
	return TRUE;
}
//ϵͳ��ʽ��,����region��Ϣ����format����
int systemcom_system_format()
{
	//��ȡregionָ��
	int i,regiongroupsize,resTF;
	REGIONGROUP *regiongroupptr;
	REGION *regionptr;
	//��ʼȫԱ��ʽ������
	regiongroupptr=get_state_gloregiongroup_PTR();
	regionptr=regiongroupptr->regiongroup;
	regiongroupsize=regiongroupptr->groupsize;
	for(i=0;i<regiongroupsize;i++)
	{
		resTF=profile_region_format_PTR(regionptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_format","region can't format");
			return FALSE;
		}
		regionptr++;
	}
	return TRUE;
}

//���ý�ϵͳ�ָ�����ֽ״̬
//35��region���������
//0-4 RAID5��6+1��
//RAID6:��5+2��
//5-9:CAUCHY orginal RS
//10-14:CAUCHY RS
//15-19:EVENODD
//20-24:RDP
//25-30:LIBERATION CODE
//30-34:blaum-roth code
//����һ��7NAS��7disk��ϵͳ���͹�Ҫ�ǲ�����������Լ���
int systemcom_system_reset_format()
{
	//format�Ƚ���device��disk����Ϣ
	int i,disknum,devicenum,resTF;
	int pushtime,maxbuffersize;
	int multindex;
	//int chunksize;

	char *diskpath,*curdiskpath,*username,*curusername,*filename,*curfilename;

	UINT64 currentid;
	//ȫ�ֱ���������
	UINT64 *glodiskidlist,*glodeviceidlist,*glofileidlist;
	DEVICEBLOCK *glodeviceblockptr,*curglodeviceblockptr;
	DISKBLOCK *glodiskblockptr,*curglodiskblockptr;

	UINT64 *RDPdeviceid;
	DEVICEBLOCK *RDPdeviceblockptr,*curRDPdeviceblockptr;

	UINT64 *RDPdiskid;
	DISKBLOCK *RDPdiskblockptr,*curRDPdiskblockptr;

	CHUNKBLOCK *chunkblockbuffer;

	GLOPUSHLIST *pushlistptr;

	DEVICE *deviceptr,*curdeviceptr;
	DEVICEGROUP *devicegroupptr;
	

	DISK *diskptr,*curdiskptr;
	DISKGROUP *diskgroupptr;
	DISKBLOCK *diskblockptr;
	UINT64 *diskidlist;//���ڼ�¼ָ��
	UINT64 volumn;

	REGION *regionptr,*curregionptr;//ָ��͵�ǰָ��
	REGIONBLOCK *regionblockptr,*curregionblockptr;
	REGIONGROUP *regiongroupptr;
	UINT64 *regionidlist;
	int regionnum;
	UINT64 totalsize;

	USERPROFILE *userprofileptr,*curuserprofileptr;
	USERLOCATION *userlocationptr;
	USERGROUP *usergroupptr;

	IDITEM *systemnextid;

	CODEPARA *codepara;

	STRIPDES *strdes;//��������

	FILEMETA *filemetaptr;//����
	FILEINF *fileinfptr;
	FILEMETAGROUP *filemetagroupptr;
	//UINT64 fileidlist;//������Ҫ��¼һ������
	//ʱ��
	time_t rawtime;
	struct tm *Nowtime;

	int strindex,codetype;
	
	disknum=TOTDISKNUMBER;
	devicenum=TOTDEVICENUMBER;
	regionnum=TOTREGIONNUM;
	deviceptr=talloc(DEVICE,devicenum);
	if(deviceptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	diskptr=talloc(DISK,disknum);
	if(diskptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	//��Ϊ���ֹ���ʼ��globaldefine����ʡ��
	//��Ҫ�趨������Ҫ�趨����
	intial_kind();//��ʼ�����
	//�趨������
	pushtime=0;
	/*chunkblockbuffer=talloc(CHUNKBLOCK,chksize_MB(4));//4G�Ĵ洢�����壬���4G/1K=���4M��
	if(chunkblockbuffer==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}*/
	chunkblockbuffer=NULL;
	maxbuffersize=0;
	pushlistptr=talloc(GLOPUSHLIST,1);
	if(pushlistptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	pushlistptr->chunknum=0;
	pushlistptr->currentbuffersize=0;
	pushlistptr->glolastpushtime=NULL;
	pushlistptr->maxbuffersize=maxbuffersize;
	pushlistptr->glopushchunklist=chunkblockbuffer;
	pushlistptr->glopushtime=pushtime;
	//�����趨��ϸ�ֵ����
	set_state_buffer_pushlist(pushlistptr);
	//������Բ���
	free(pushlistptr);
	//�ֿռ�
	systemnextid=talloc(IDITEM,1);
	if(systemnextid==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	GLOABL_set_SYSTEMNEXTID_data(systemnextid,0,0,0,0,0,0,0,0);//C��0��ʼ
	//��ֵ
	set_SYSID_PTR(systemnextid);
	//������Բ���
	free(systemnextid);
	
	//�Ƚ���regionָ�����Ӧregionblock��regiongroup
	regionptr=talloc(REGION,regionnum);
	if(regionptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	regiongroupptr=talloc(REGIONGROUP,1);
	if(regiongroupptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	regiongroupptr->regiongroup=regionptr;
	regiongroupptr->groupsize=regionnum;
	//��ֵ
	set_state_gloregiongroup(regiongroupptr);
	//�ͷſռ�
	free(regiongroupptr);
	regionidlist=talloc(UINT64,regionnum);
	if(regionidlist==NULL)
	{	
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}

	regionblockptr=talloc(REGIONBLOCK,regionnum);
	if(regionblockptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	curregionblockptr=regionblockptr;
	curregionptr=regionptr;
	for(i=0;i<35;i++)
	{
		
		curregionptr->RegionID=get_state_gloregionid();
		set_state_gloregionid_add(1);
		
		curregionblockptr->regionid=regionptr->RegionID;
		curregionblockptr->regionptr=regionptr;
		
		regionidlist[i]=regionptr->RegionID;
		curregionptr++;
		curregionblockptr++;
	}
	
	

	/*deviceptr=talloc(DEVICE,devicenum);
	if(deviceptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}*/
	devicegroupptr=talloc(DEVICEGROUP,1);
	if(devicegroupptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	devicegroupptr->devicegroup=deviceptr;
	devicegroupptr->groupsize=devicenum;
	glodeviceblockptr=talloc(DEVICEBLOCK,devicenum);
	if(glodeviceblockptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	glodeviceidlist=talloc(UINT64,devicenum);
	if(glodeviceidlist==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	curglodeviceblockptr=glodeviceblockptr;
	curdeviceptr=deviceptr;
	//�趨����
	for(i=0;i<devicenum;i++)
	{
		curdeviceptr->DeviceID=get_state_glodeviceid();//����id���и�ֵ
		set_state_glodeviceid_add(1);
		GLOBAL_set_DEVICE_data(curdeviceptr,NASMAC,0,NULL,
								  NULL,NULL,NOVALUE,//�洢���б�
								  regionblockptr,regionidlist,1,//region�б�
								  EMPTY//��ǰ�洢״̬
								  );//�趨��ǰDEVICE�е�����
		//�趨ȫ���豸���
		glodeviceidlist[i]=curdeviceptr->DeviceID;
		//�趨ȫ��blockָ��
		curglodeviceblockptr->deviceptr=curdeviceptr;
		curglodeviceblockptr->deviceid=curdeviceptr->DeviceID;//����־־
		curglodeviceblockptr++;
		curdeviceptr++;
	}
	//�趨����
	set_state_glodevicegroup(devicegroupptr);
	//�ͷſռ�
	free(devicegroupptr);


	/*diskptr=talloc(DISK,disknum);
	if(diskptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}*/
	diskgroupptr=talloc(DISKGROUP,1);
	if(diskgroupptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	glodiskblockptr=talloc(DISKBLOCK,disknum);
	if(glodiskblockptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	glodiskidlist=talloc(UINT64,disknum);
	if(glodiskidlist==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}

	

	diskgroupptr->diskgroup=diskptr;
	diskgroupptr->groupsize=disknum;

	curglodiskblockptr=glodiskblockptr;
	curdiskptr=diskptr;
	curdeviceptr=deviceptr;

	diskpath="d:\\";
	for(i=0;i<disknum;i++)
	{
		curdiskptr->DiskID=get_state_glodiskid();//����id���и�ֵ
		set_state_glodiskid_add(1);
		curdiskpath=talloc(char,1000);
		if(curdiskpath==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		mcpy(curdiskpath,diskpath,char,strlen(diskpath)+1);
		curdiskpath[0]=curdiskpath[0]+i;//���̷�����ƶ�һ��
		currentid=curdeviceptr->DeviceID;
		volumn=chksize_TB(2);
		GLOBAL_set_DISK_data(curdiskptr,NORHDD,MIDCAP,volumn,
								regionblockptr,regionidlist,1,//�洢���ϰ�����region����
								curdeviceptr,currentid,//��һ���device���
								curdiskpath,//�ؼ���Ϣ��ǰ���̵�����·��
								EMPTY//��ǰ�洢״̬	
								);//�趨��ǰDISK�е�����
		//���㵱ǰcurdevice�е�block��Ϣ
		diskblockptr=talloc(DISKBLOCK,1);
		if(diskblockptr==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		diskblockptr->diskptr=curdiskptr;
		diskblockptr->diskid=curdiskptr->DiskID;
		diskidlist=talloc(UINT64,1);
		if(diskidlist==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		diskidlist[0]=curdiskptr->DiskID;//����������д��
		curdeviceptr->diskid=diskidlist;
		curdeviceptr->disklist=diskblockptr;
		curdeviceptr->disknum=1;

		//�趨ȫ��disk���
		glodiskidlist[i]=curdiskptr->DiskID;
		//�趨ȫ��blockָ��
		curglodiskblockptr->diskptr=curdiskptr;
		curglodiskblockptr->diskid=curdiskptr->DiskID;

		curglodiskblockptr++;
		curdeviceptr++;
		curdiskptr++;
	}
	//�趨����
	set_state_glodiskgroup(diskgroupptr);
	//�ͷſռ�
	free(diskgroupptr);

	//�趨user��Ϣ,������������û�
	userprofileptr=talloc(USERPROFILE,2);
	if(userprofileptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	//��group�Ŀռ�
	usergroupptr=talloc(USERGROUP,1);
	if(usergroupptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	curuserprofileptr=userprofileptr;
	username="user1";
	for(i=0;i<2;i++)
	{
		curuserprofileptr->UserID=get_state_glouserid();//����id���и�ֵ
		set_state_glouserid_add(1);
		userlocationptr=talloc(USERLOCATION,1);
		if(userlocationptr==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		
		GLOBAL_set_USERLOCATION_data(userlocationptr,NOVALUE,NULL,NULL);//�û��ĵ�ǰ�ļ�ϵͳλ��
		
		curusername=talloc(char,1000);
		if(curusername==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		//��ȡ��ǰʱ��
		time(&rawtime);
		Nowtime=localtime(&rawtime);
		//ת����ǰʱ��
		strindex=(int)strlen(username);
		mcpy(curusername,username,char,strlen(username)+1);
		
		curusername[strindex-1]=curusername[strindex-1]+i;//��Ҫԭ������Ϊ
		GLOBAL_set_USERPROFILE_data(curuserprofileptr,curusername,"111111",
									   userlocationptr,SYSADMIN,//�û���Ϣ
									   Nowtime//����ʱ��
									   );
		curuserprofileptr++;
	}
	//�����û���
	curuserprofileptr=userprofileptr;
	for(i=0;i<2;i++)
	{
		userlocationptr=curuserprofileptr->userlocinf;
		userlocationptr->DICid=0;//�����ݶ�λ��һ���ļ���region0
		userlocationptr->DICpath="region0\\";
	}
	usergroupptr->userlist=userprofileptr;
	usergroupptr->groupsize=2;
	set_state_glousergroup(usergroupptr);
	free(usergroupptr);


	//����ȫ��regionԪ����
	// һ��һ��������RAID-5
	totalsize=chksize_MB(10);

	curregionptr=regionptr;
	//index=0;
	filename="region0\\";
	multindex=1;
	for(i=0;i<5;i++)
	{
		curfilename=talloc(char,100);
		if(curfilename==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		strindex=(int)strlen(filename);
		mcpy(curfilename,filename,char,strindex+1);
		curfilename[strindex-2]=curfilename[strindex-2]+i;


		codetype=codetype(RAID5,NULLTYPE);//�����������
		codepara=talloc(CODEPARA,1);
		if(codepara==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}

		GLOBAL_set_CODEPARA_data(codepara,
										8,//٤�޻����С
										6,//k
										1,//m
										7,//n
										5,//d
										NOVALUE//�����������Ŀ���
										);//�趨CODEPARA����ֵ
		strdes=talloc(STRIPDES,1);
		if(strdes==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		//��ʼ��������
		GLOBAL_set_STRIPDES_data(strdes,
										1,//ÿһ����������������,��chunk��
										glodiskblockptr,//�����disk�б�
										glodiskidlist,//��ǰ����id
										disknum,//���ڵļ�һ����������������������ͨ�����������region��disk��һ��
										chksize_KB(16*multindex)//ÿһ��CHUNK�Ĵ�С���ֽ�Ϊ��λ
										);//�趨STRIPDES����ֵ
		multindex=multindex*2;
		resTF=profile_region_setup(curregionptr,codetype,codepara,strdes,totalsize,
									glodeviceidlist,glodeviceblockptr,devicenum,
									glodiskidlist,glodiskblockptr,disknum,
									curfilename,userprofileptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","region can't setup");
			return FALSE;
		}
		curregionptr++;
	}
	filename="region5\\";
	multindex=1;
	for(i=0;i<5;i++)
	{
		curfilename=talloc(char,100);
		if(curfilename==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		strindex=(int)strlen(filename);
		mcpy(curfilename,filename,char,strindex+1);
		curfilename[strindex-2]=curfilename[strindex-2]+i;

		codetype=codetype(RAID6,CAUCHYORGRS);//�����������
		codepara=talloc(CODEPARA,1);
		if(codepara==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		GLOBAL_set_CODEPARA_data(codepara,
										8,//٤�޻����С
										5,//k
										2,//m
										7,//n
										5,//d
										NOVALUE//�����������Ŀ���
										);//�趨CODEPARA����ֵ
		strdes=talloc(STRIPDES,1);
		if(strdes==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		//��ʼ��������
		GLOBAL_set_STRIPDES_data(strdes,
									8,//ÿһ����������������,��chunk��
									glodiskblockptr,//�����disk�б�
									glodiskidlist,//��ǰ����id
									disknum,//���ڵļ�һ����������������������ͨ�����������region��disk��һ��
									chksize_KB(16*multindex)//ÿһ��CHUNK�Ĵ�С���ֽ�Ϊ��λ
									);//�趨STRIPDES����ֵ
		multindex=multindex*2;
		resTF=profile_region_setup(curregionptr,codetype,codepara,strdes,totalsize,
									glodeviceidlist,glodeviceblockptr,devicenum,
									glodiskidlist,glodiskblockptr,disknum,
									curfilename,userprofileptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","region can't setup");
			return FALSE;
		}
		resTF=profile_map_define_intial(curregionptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","RAID5 can't define");
			return FALSE;
		}
		curregionptr++;
	}
	filename="region10\\";
	multindex=1;
	for(i=0;i<5;i++)
	{
		curfilename=talloc(char,100);
		if(curfilename==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		strindex=(int)strlen(filename);
		mcpy(curfilename,filename,char,strindex+1);
		curfilename[strindex-2]=curfilename[strindex-2]+i;

		codetype=codetype(RAID6,CAUCHYRS);//�����������
		codepara=talloc(CODEPARA,1);
		if(codepara==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		GLOBAL_set_CODEPARA_data(codepara,
										8,//٤�޻����С
										5,//k
										2,//m
										7,//n
										5,//d
										NOVALUE//�����������Ŀ���
										);//�趨CODEPARA����ֵ

		strdes=talloc(STRIPDES,1);
		if(strdes==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		//��ʼ��������
		GLOBAL_set_STRIPDES_data(strdes,
									8,//ÿһ����������������,��chunk��
									glodiskblockptr,//�����disk�б�
									glodiskidlist,//��ǰ����id
									disknum,//���ڵļ�һ����������������������ͨ�����������region��disk��һ��
									chksize_KB(multindex*16)//ÿһ��CHUNK�Ĵ�С���ֽ�Ϊ��λ
									);//�趨STRIPDES����ֵ
		multindex=multindex*2;
		resTF=profile_region_setup(curregionptr,codetype,codepara,strdes,totalsize,
									glodeviceidlist,glodeviceblockptr,devicenum,
									glodiskidlist,glodiskblockptr,disknum,
									curfilename,userprofileptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","region can't setup");
			return FALSE;
		}
		resTF=profile_map_define_intial(curregionptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","RAID5 can't define");
			return FALSE;
		}
		curregionptr++;
	}
	filename="region15\\";
	multindex=1;
	for(i=0;i<5;i++)
	{
		curfilename=talloc(char,100);
		if(curfilename==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		strindex=(int)strlen(filename);
		mcpy(curfilename,filename,char,strindex+1);
		curfilename[strindex-2]=curfilename[strindex-2]+i;

		codetype=codetype(RAID6,EVENODD);//�����������
		codepara=talloc(CODEPARA,1);
		if(codepara==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		GLOBAL_set_CODEPARA_data(codepara,
										4,//٤�޻����С
										5,//k
										2,//m
										7,//n
										5,//d
										NOVALUE//�����������Ŀ���
										);//�趨CODEPARA����ֵ

		strdes=talloc(STRIPDES,1);
		if(strdes==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		//��ʼ��������
		GLOBAL_set_STRIPDES_data(strdes,
									4,//ÿһ����������������,��chunk��
									glodiskblockptr,//�����disk�б�
									glodiskidlist,//��ǰ����id
									disknum,//���ڵļ�һ����������������������ͨ�����������region��disk��һ��
									chksize_KB(multindex*16)//ÿһ��CHUNK�Ĵ�С���ֽ�Ϊ��λ
									);//�趨STRIPDES����ֵ
		multindex=multindex*2;
		resTF=profile_region_setup(curregionptr,codetype,codepara,strdes,totalsize,
									glodeviceidlist,glodeviceblockptr,devicenum,
									glodiskidlist,glodiskblockptr,disknum,
									curfilename,userprofileptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","region can't setup");
			return FALSE;
		}
		/*resTF=profile_map_define_intial(curregionptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","RAID5 can't define");
			return FALSE;
		}*/
		curregionptr++;
	}
	/*RDPdeviceid=talloc(UINT64,6);
	if(RDPdeviceid==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	RDPdeviceblockptr=talloc(DEVICEBLOCK,6);
	if(RDPdeviceblockptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	curRDPdeviceblockptr=RDPdeviceblockptr;

	RDPdiskid=talloc(UINT64,6);
	if(RDPdiskid==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	RDPdiskblockptr=talloc(DISKBLOCK,6);
	if(RDPdiskblockptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	curRDPdiskblockptr=RDPdiskblockptr;
	curglodeviceblockptr=glodeviceblockptr;
	curglodiskblockptr=glodiskblockptr;
	for(i=0;i<6;i++)
	{
		RDPdiskid[i]=glodiskidlist[i];
		curRDPdeviceblockptr->deviceid=curglodeviceblockptr->deviceid;
		curRDPdeviceblockptr->deviceptr=curglodeviceblockptr->deviceptr;

		curRDPdiskblockptr->diskid=curglodiskblockptr->diskid;
		curRDPdiskblockptr->diskptr=curglodiskblockptr->diskptr;
	}*/
	disknum=6;
	devicenum=6;
	filename="region20\\";
	multindex=1;
	for(i=0;i<5;i++)
	{
		curfilename=talloc(char,100);
		if(curfilename==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		strindex=(int)strlen(filename);
		mcpy(curfilename,filename,char,strindex+1);
		curfilename[strindex-2]=curfilename[strindex-2]+i;

		codetype=codetype(RAID6,RDP);//�����������
		codepara=talloc(CODEPARA,1);
		if(codepara==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		GLOBAL_set_CODEPARA_data(codepara,
										4,//٤�޻����С
										4,//k
										2,//m
										6,//n
										4,//d
										NOVALUE//�����������Ŀ���
										);//�趨CODEPARA����ֵ
		strdes=talloc(STRIPDES,1);
		if(strdes==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		//��ʼ��������
		//��һ�����ⲻ����ȫ�ֵ�diskid��ָ��

		GLOBAL_set_STRIPDES_data(strdes,
									4,//ÿһ����������������,��chunk��
									glodiskblockptr,//�����disk�б�
									glodiskidlist,//��ǰ����id
									disknum,//���ڵļ�һ����������������������ͨ�����������region��disk��һ��
									chksize_KB(multindex*16)//ÿһ��CHUNK�Ĵ�С���ֽ�Ϊ��λ
									);//�趨STRIPDES����ֵ
		multindex=multindex*2;
		resTF=profile_region_setup(curregionptr,codetype,codepara,strdes,totalsize,
									glodeviceidlist,glodeviceblockptr,devicenum,
									glodiskidlist,glodiskblockptr,disknum,
									curfilename,userprofileptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","region can't setup");
			return FALSE;
		}
		/*resTF=profile_map_define_intial(curregionptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","RAID5 can't define");
			return FALSE;
		}*/
		curregionptr++;


	}
	//liberation��bloth������ʱ��������6��
	disknum=7;
	devicenum=7;
	filename="region25\\";
	multindex=1;
	for(i=0;i<5;i++)
	{
		curfilename=talloc(char,100);
		if(curfilename==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		strindex=(int)strlen(filename);
		mcpy(curfilename,filename,char,strindex+1);
		curfilename[strindex-2]=curfilename[strindex-2]+i;

		codetype=codetype(RAID6,LIBERATION);//�����������
		codepara=talloc(CODEPARA,1);
		if(codepara==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		GLOBAL_set_CODEPARA_data(codepara,
										6,//٤�޻����С
										5,//k
										2,//m
										7,//n
										5,//d
										NOVALUE//�����������Ŀ���
										);//�趨CODEPARA����ֵ
		strdes=talloc(STRIPDES,1);
		if(strdes==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		//��ʼ��������
		GLOBAL_set_STRIPDES_data(strdes,
									6,//ÿһ����������������,��chunk��
									glodiskblockptr,//�����disk�б�
									glodiskidlist,//��ǰ����id
									disknum,//���ڵļ�һ����������������������ͨ�����������region��disk��һ��
									chksize_KB(multindex*16)//ÿһ��CHUNK�Ĵ�С���ֽ�Ϊ��λ
									);//�趨STRIPDES����ֵ
		multindex=multindex*2;
		resTF=profile_region_setup(curregionptr,codetype,codepara,strdes,totalsize,
									glodeviceidlist,glodeviceblockptr,devicenum,
									glodiskidlist,glodiskblockptr,disknum,
									curfilename,userprofileptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","region can't setup");
			return FALSE;
		}
		curregionptr++;
	}
	filename="region30\\";
	multindex=1;
	disknum=6;
	devicenum=6;
	for(i=0;i<5;i++)
	{
		curfilename=talloc(char,100);
		if(curfilename==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		strindex=(int)strlen(filename);
		mcpy(curfilename,filename,char,strindex+1);
		curfilename[strindex-2]=curfilename[strindex-2]+i;

		codetype=codetype(RAID6,BLAUMROTH);//�����������
		codepara=talloc(CODEPARA,1);
		if(codepara==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		GLOBAL_set_CODEPARA_data(codepara,
										4,//٤�޻����С
										4,//k
										2,//m
										6,//n
										4,//d
										NOVALUE//�����������Ŀ���
										);//�趨CODEPARA����ֵ

		strdes=talloc(STRIPDES,1);
		if(strdes==NULL)
		{
			show_error("systemcom","system_reset_format","No memory");
			return FALSE;
		}
		//��ʼ��������
		GLOBAL_set_STRIPDES_data(strdes,
									6,//ÿһ����������������,��chunk��
									glodiskblockptr,//�����disk�б�
									glodiskidlist,//��ǰ����id
									disknum,//���ڵļ�һ����������������������ͨ�����������region��disk��һ��
									chksize_KB(multindex*16)//ÿһ��CHUNK�Ĵ�С���ֽ�Ϊ��λ
									);//�趨STRIPDES����ֵ
		multindex=multindex*2;
		resTF=profile_region_setup(curregionptr,codetype,codepara,strdes,totalsize,
									glodeviceidlist,glodeviceblockptr,devicenum,
									glodiskidlist,glodiskblockptr,disknum,
									curfilename,userprofileptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","region can't setup");
			return FALSE;
		}
		/*resTF=profile_map_define_intial(curregionptr);
		if(resTF==FALSE)
		{
			show_error("systemcom","system_reset_format","RAID5 can't define");
			return FALSE;
		}*/
		curregionptr++;
	}
	/*codetype=codetype(RAID5,Nulltype);//�����������
	codepara=talloc(CODEPARA,1);
	if(codepara==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	GLOBAL_set_CODEPARA_data(codepara,
									8,//٤�޻����С
									6,//k
									1,//m
									6,//n
									5,//d
									NOVALUE//�����������Ŀ���
									);//�趨CODEPARA����ֵ
	strdes=talloc(STRIPDES,1);
	if(strdes==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	//��ʼ��������
	GLOBAL_set_STRIPDES_data(strdes,
									1,//ÿһ����������������,��chunk��
									glodiskblockptr,//�����disk�б�
									glodiskidlist,//��ǰ����id
									disknum,//���ڵļ�һ����������������������ͨ�����������region��disk��һ��
									chksize_KB(64)//ÿһ��CHUNK�Ĵ�С���ֽ�Ϊ��λ
									);//�趨STRIPDES����ֵ
	totalsize=chksize_MB(64);
	GLOBAL_set_REGION_data(regionptr,codetype,codepara,totalsize,
								  NULL,NULL,NOVALUE,//������file���б�,�ļ��н��и���
								  glodiskblockptr,glodiskidlist,disknum,//Disk���б�
								  glodeviceblockptr,glodeviceidlist,devicenum,//device�б�
								  strdes,NULL,NULL,NOVALUE,//��������
								  NOVALUE,NOVALUE,//chunk��stripsect����
								  NULL,NOVALUE,//���ļ�ָ��,�ļ��н��и���
								  EMPTY//��ǰ�洢״̬
								  );//�趨��ǰREGION�е�����
	//��Ϣ������Ը�ʽ����
	resTF=profile_region_format_PTR(regionptr);
	if(resTF==FALSE)
	{
		show_error("systemcom","system_reset_format","region can't format");
		return FALSE;
	}
	//��ʼ��filemeta
	filemetaptr=talloc(FILEMETA,1);
	if(filemetaptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	filemetagroupptr=talloc(FILEMETAGROUP,1);
	if(filemetagroupptr==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	glofileidlist=talloc(UINT64,1);
	if(glofileidlist==NULL)
	{
		show_error("systemcom","system_reset_format","No memory");
		return FALSE;
	}
	//�趨����
	filemetaptr->FileID=get_state_glofileid();
	currentid=get_state_glofileid();//�����Ҽ�һ��
	set_state_glofileid_add(1);
	fileinfptr=NULL;//����ֻ�г�ʼĿ¼���û������
	GLOBAL_set_FILEMETA_data(filemetaptr,"region0",NOVALUE,NOVALUE,DICTKIND,
									regionptr,regionptr->RegionID,//�ϲ�regionָ��
									userprofileptr,userprofileptr->UserID,//�ļ������ߣ���ʱ�趨Ϊ
									NOVALUE,NULL,//��һ���ļ��У���Ŀ¼ΪNULL
									NULL,NULL,NONE,//��ʱû�����ݣ��ļ���ָ����Ҫָ��ǰĿ¼��һ��Ԫ���ݿ�
									Nowtime,//�������͸���ʱ�䶼�趨Ϊ��ǰʱ��
									Nowtime,
									NULL//���ڴ�����ݿ���Ϣ
									);//�趨FILEMETA����ֵ
	//�����û���
	curuserprofileptr=userprofileptr;
	for(i=0;i<2;i++)
	{
		userlocationptr=curuserprofileptr->userlocinf;
		userlocationptr->DICid=currentid;
		userlocationptr->DICpath="\\region0\\";
	}
	//�����ݸ�ֵ��region����
	regionptr->rootfileid=currentid;
	regionptr->fileroot=filemetaptr;
	filemetagroupptr->filemetagroup=filemetaptr;
	filemetagroupptr->grouposize=1;
	regionptr->filemetalist=filemetagroupptr;
	//����Ҫ���ռ�
	glofileidlist[0]=currentid;
	regionptr->fileid=glofileidlist;
	regionptr->filenum=1;*/
	//��ͬ��֮���Ƚ�Ԫ���ݵ�ַ�ռ�д��
	set_state_glometapath(".\\metadata\\");
	//�������ͬ��������
	resTF=profile_metadata_sync();
	if(resTF==FALSE)
	{
		show_error("systemcom","system_reset_format","metadata can't snyc");
		return FALSE;
	}
	//ȷ��У���λ��
	
	return TRUE;
}

//ͬ������
//ͬ��Ԫ����
int systemcom_metadata_sync()
{
	profile_metadata_sync();
	return TRUE;
}
//ͬ��chunk����
int systemcom_chunkdata_sync()
{
	profile_GLOBAL_chunk_data_sync();
	return TRUE;
}
//����ǰ��
int systemcom_system_buffer_clean()
{
	GLOPUSHLIST *pushlist;
	pushlist=get_state_buffer_pushlist();
	pushlist->currentbuffersize=0;
	pushlist->currentbuffersize=0;
	return TRUE;
}
//����push��Ϣָ��
int systemcom_push_time(int pushtime,int maxbuffersize)
{
	//����ֱѡ��ֵ����
	GLOPUSHLIST *pushlist;
	pushlist=get_state_buffer_pushlist();
	pushlist->glopushtime=pushtime;
	pushlist->maxbuffersize=maxbuffersize;
	return TRUE;
}