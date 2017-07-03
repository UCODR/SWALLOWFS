#include "checkpoint.h"

int checkpoint_record_recent_request(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr)
{
	
	int resTF;
	UINT64 maxlognum,deletelognum;

	maxlognum=Requestlognumber;

	if(systemlogreqindex==0)
	{
		resTF=mysql_FILELAYER_checkpoint_delete_all();
		if(resTF==FALSE)
		{
			show_error("checkpoint_record","recent_request","data cannot delete");
			return FALSE;
		}
	}

	//�����ǰû�б�д������д
	if(systemlogreqindex<maxlognum)
	{
		//��һ�����û�д���
		resTF=checkpoint_record_chunks(chunkpositionblockgroupptr,parityblockgroupptr);
		if(resTF==FALSE)
		{
			show_error("checkpoint_record","recent_request","chunks cannot record");
			return FALSE;
		}
		
	}
	else
	{
		//��һ��������Ҫɾ��������
		deletelognum=systemlogreqindex-maxlognum;
		resTF=checkpoint_delete_request(deletelognum);
		if(resTF==FALSE)
		{
			show_error("checkpoint_record","recent_request","record cannot delete");
			return FALSE;
		}
		//�����������ݿ�
		resTF=checkpoint_record_chunks(chunkpositionblockgroupptr,parityblockgroupptr);
		if(resTF==FALSE)
		{
			show_error("checkpoint_record","recent_request","chunks cannot record");
			return FALSE;
		}
	}
	systemlogreqindex++;
	return TRUE;
}
int checkpoint_record_chunks(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr)
{
	CHUNKPOSITIONBLOCK *chunkpblockptr,*curchunkpblockptr;
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;//������ָ��
	CHUNK *chunkptr;

	int i,resTF,groupsize,chunkindex;

	chunkpblockptr=chunkpositionblockgroupptr->chunkblockptr;
	groupsize=chunkpositionblockgroupptr->groupsize;

	curchunkpblockptr=chunkpblockptr;
	chunkindex=0;
	for(i=0;i<groupsize;i++)
	{
		chunkptr=curchunkpblockptr->chunkptr;
		resTF=checkpoint_record_one_chunk(chunkptr,systemlogreqindex,chunkindex);
		if(resTF==FALSE)
		{
			show_error("checkpoint_record","recent_request","chunk cannnot record");
			return FALSE;
		}
		chunkindex++;
		curchunkpblockptr++;
	}
	//��Ҫ��������У���
	chunkblockptr=parityblockgroupptr->chunkblockptr;
	groupsize=parityblockgroupptr->groupsize;

	curchunkblockptr=chunkblockptr;
	for(i=0;i<groupsize;i++)
	{
		chunkptr=curchunkblockptr->chunkptr;
		resTF=checkpoint_record_one_chunk(chunkptr,systemlogreqindex,chunkindex);
		if(resTF==FALSE)
		{
			show_error("checkpoint_record","recent_request","chunk cannnot record");
			return FALSE;
		}
		chunkindex++;
		curchunkblockptr++;
	}

	return TRUE;
}

int checkpoint_delete_request(int reqindex)
{
	int i,resTF;
	//������Ҫ��ȡ�����еĵ�ַ��Ϣ�������ݽ���ɾ��
	CHECKPOINTGROUP *checkpointgrpptr;
	CHECKPOINT *checkpointptr,*curcheckpointptr;
	CHECKPOINTINF *checkpointinfptr;

	int chunknum;
	char *uppath,*orgpath;

	checkpointgrpptr=talloc(CHECKPOINTGROUP,1);
	if(checkpointgrpptr==NULL)
	{
		show_error("checkpoint","delete_request","No memoey");
		return FALSE;
	}
	checkpointinfptr=talloc(CHECKPOINTINF,1);
	if(checkpointinfptr==NULL)
	{
		show_error("checkpoint","delete_request","No memory");
		return FALSE;
	}
	checkpointinfptr->reqindex=reqindex;
	resTF=mysql_FILELAYER_checkpoint_select_request_countnum(checkpointinfptr);
	if(resTF==FALSE)
	{
		show_error("checkpoint","delete_request","information cannot read");
		return FALSE;
	}

	chunknum=checkpointinfptr->reqcount;

	checkpointptr=talloc(CHECKPOINT,chunknum);
	if(checkpointptr==NULL)
	{
		show_error("checkpoint","delete_request","No memory");
		return FALSE;
	}

	checkpointgrpptr->checkpointptr=checkpointptr;
	checkpointgrpptr->groupsize=chunknum;

	curcheckpointptr=checkpointptr;

	for(i=0;i<chunknum;i++)
	{
		orgpath=talloc(char,1024);
		if(orgpath==NULL)
		{
			show_error("checkpoint","delete_request","No memory");
			return FALSE;
		}
		uppath=talloc(char,1024);
		if(uppath==NULL)
		{
			show_error("checkpoint","delete_request","No memory");
			return FALSE;
		}
		curcheckpointptr->orgcontent=orgpath;
		curcheckpointptr->upcontent=uppath;
		curcheckpointptr++;
	}

	//����Ϣ�����ڴ�
	resTF=mysql_FILELAYER_checkpoint_select_group(checkpointgrpptr,reqindex);
	if(resTF==FALSE)
	{
		show_error("checkpoint","delete_request","metadata cannot read");
		return FALSE;
	}

	resTF=checkpoint_delete_backup_data(checkpointgrpptr);
	if(resTF==FALSE)
	{
		show_error("checkpoint","delete_request","delete backup data");
		return FALSE;
	}

	resTF=mysql_FILELAYER_checkpoint_delete(reqindex);
	if(resTF==FALSE)
	{
		show_error("checkpoint","delete_request","The records cannot be deleted");
		return FALSE;
	}

	//���տռ�
	curcheckpointptr=checkpointptr;
	for(i=0;i<chunknum;i++)
	{
		orgpath=curcheckpointptr->orgcontent;
		uppath=curcheckpointptr->upcontent;
		free(orgpath);
		free(uppath);
		curcheckpointptr++;
	}
	free(checkpointptr);
	free(checkpointgrpptr);
	return TRUE;
}

int checkpoint_delete_backup_data(CHECKPOINTGROUP *checkpointgrpptr)
{
	CHECKPOINT *checkpointptr,*curcheckpointptr;
	char *orgpath,*orgfilename;
	char *uppath,*upfilename;
	int i,chunknum,resTF;

	orgpath=talloc(char,1024);
	if(orgpath==NULL)
	{
		show_error("checkpoint_delete","backup_data","No memory");
		return FALSE;
	}
	//mcpy(orgpath,"",char,2);//�趨Ϊ���ַ���

	uppath=talloc(char,1024);
	if(uppath==NULL)
	{
		show_error("checkpoint_delete","backup_data","No memory");
		return FALSE;
	}
	//mcpy(uppath,"",char,2);


	checkpointptr=checkpointgrpptr->checkpointptr;
	chunknum=checkpointgrpptr->groupsize;

	curcheckpointptr=checkpointptr;
	for(i=0;i<chunknum;i++)
	{
		orgfilename=curcheckpointptr->orgcontent;
		//����sprintf��
		sprintf(orgpath,"%s\\%s",SYSBACKUPPATH,orgfilename);
		//uppath=curcheckpointptr->upcontent;
		//strcat(orgpath,SYSBACKUPPATH);
		//strcat(orgpath,orgfilename);

		upfilename=curcheckpointptr->upcontent;
		sprintf(uppath,"%s\\%s",SYSBACKUPPATH,upfilename);
		//strcat(uppath,SYSBACKUPPATH);
		//strcat(uppath,upfilename);

		resTF=file_FILELAYER_BYTE_DELETE_ORG(orgpath);
		if(resTF==FALSE)
		{
			show_error("checkpoint_delete","backup_data","data cannot delete");
			return FALSE;
		}
		resTF=file_FILELAYER_BYTE_DELETE_ORG(uppath);
		if(resTF==FALSE)
		{
			show_error("checkpoint_delete","backup_data","data cannot delete");
			return FALSE;
		}
		curcheckpointptr++;
	}
	free(uppath);
	free(orgpath);
	return TRUE;
}

int checkpoint_record_one_chunk(CHUNK *chunkptr,UINT64 reqindex,int chunkindex)
{
	int resTF;
	CHECKPOINT *checkpointptr;

	int regionoffset,stripoffset,strsetoffset,chunkoffset,chunksize;

	REGION *regionptr,*curregionptr;
	REGIONGROUP *regiongrpptr;

	STRIP *stripptr,*curstripptr;
	STRIPGROUP *stripgrpptr;

	STRIPSECT *strsetptr,*curstrsetptr;
	STRIPSECTGROUP *strsetgrpptr;

	CHUNK *startchunkptr;
	CHUNKGROUP *chunkgrpptr;

	CHUNK *orgchunkptr;//��Ҫ��ԭʼ������ڴ�
	BYTE *orgcontent,*upcontent;

	char *orgpath,*uppath,*orgfilename,*upfilename;

	//int chunksize;
	//��һ���ڴ�ռ�
	checkpointptr=talloc(CHECKPOINT,1);
	if(checkpointptr==NULL)
	{
		show_error("checkpoint_record","one_chunk","No memory");
		return FALSE;
	}

	orgchunkptr=talloc(CHUNK,1);
	if(orgchunkptr==NULL)
	{
		show_error("checkpoint_record","one_chunk","No memory");
		return FALSE;
	}
	chunksize=chunkptr->sizenum;

	orgcontent=talloc(BYTE,chunksize);
	if(orgcontent==NULL)
	{
		show_error("checkpoint_record","one_chunk","No memory");
		return FALSE;
	}

	orgfilename=talloc(char,1024);
	if(orgfilename==NULL)
	{
		show_error("checkpoint_record","one_chunk","No memory");
		return FALSE;
	}

	upfilename=talloc(char,1024);
	if(upfilename==NULL)
	{
		show_error("checkpoint_record","one_chunk","No memory");
		return FALSE;
	}

	orgpath=talloc(char,1024);
	if(orgpath==NULL)
	{
		show_error("checkpoint_record","one_chunk","No memory");
		return FALSE;
	}

	uppath=talloc(char,1024);
	if(uppath==NULL)
	{
		show_error("checkpoint_record","one_chunk","No memory");
		return FALSE;
	}
	//��дһ������
	checkpointptr->RecordID=reqindex;//ǿ�Ƶ��������

	checkpointptr->chunkID=chunkptr->ChunkID;
	checkpointptr->requestID=reqindex;

	checkpointptr->regionID=chunkptr->regionid;
	checkpointptr->stripID=chunkptr->stripid;
	checkpointptr->strsetID=chunkptr->stripsectid;

	//checkpointptr->chunksize=chunkptr->sizenum;
	//sprintf(uppath,"D:\\backup\\u%I64d_%d.txt",reqindex,chunkindex);
	sprintf(upfilename,"u%I64d_%d.txt",reqindex,chunkindex);

	checkpointptr->upcontent=upfilename;
	upcontent=chunkptr->chunkcontent;
	chunksize=chunkptr->sizenum;

	sprintf(uppath,"%s\\%s",SYSBACKUPPATH,upfilename);

	resTF=file_FILELAYER_BYTE_WRITER_ORG(uppath,upcontent,chunksize);
	if(resTF==FALSE)
	{
		show_error("checkpoint_record","one_chunk","BYTE cannot write");
		return FALSE;
	}

	checkpointptr->chunksize=chunksize;

	curregionptr=chunkptr->regionptr;
	curstripptr=chunkptr->stripptr;
	curstrsetptr=chunkptr->stripsectptr;

	//���ͷָ��
	regiongrpptr=get_state_gloregiongroup_PTR();
	regionptr=regiongrpptr->regiongroup;

	stripgrpptr=curregionptr->striplist;
	stripptr=stripgrpptr->stripgroup;

	strsetgrpptr=curstripptr->stripsectlist;
	strsetptr=strsetgrpptr->stripsectgroup;
	
	chunkgrpptr=curstrsetptr->chunklist;
	startchunkptr=chunkgrpptr->ckgroup;
	//����ƫ����
	regionoffset=curregionptr-regionptr;
	stripoffset=curstripptr-stripptr;
	strsetoffset=curstrsetptr-strsetptr;
	chunkoffset=chunkptr->ChunkID-startchunkptr->ChunkID;//�п��ܾ�����copyΪ�˱�֤һ����ȷ

	checkpointptr->regionoffset=regionoffset;
	checkpointptr->stripoffset=stripoffset;
	checkpointptr->strsetoffset=strsetoffset;
	checkpointptr->chunkoffset=chunkoffset;

	//��Ҫ��ԭʼ�Ŀ�Ӵ����ж�����
	//��һ������
	resTF=matrix_CHUNK_copy_meta(orgchunkptr,chunkptr);
	if(resTF==FALSE)
	{
		show_error("checkpoint_record","one_chunk","metadata cannot copy");
		return FALSE;
	}
	orgchunkptr->chunkcontent=orgcontent;
	//�������ǻ���Ҫ�Ӵ��̶�ȡԭʼ����
	resTF=FILELAYER_CHUNK_READER_DATA(orgchunkptr);
	if(resTF==FALSE)
	{
		show_error("checkpoint_record","one_chunk","metadata and data cannot copy");
		return FALSE;
	}
	//sprintf(orgpath,"D:\\backup\\o%I64d_%d.txt",reqindex,chunkindex);
	sprintf(orgfilename,"o%I64d_%d.txt",reqindex,chunkindex);
	checkpointptr->orgcontent=orgfilename;

	sprintf(orgpath,"%s\\%s",SYSBACKUPPATH,orgfilename);
	//���ڻ�����orgcontent��˿���ֱ�Ӷ�
	resTF=file_FILELAYER_BYTE_WRITER_ORG(orgpath,orgcontent,chunksize);
	if(resTF==FALSE)
	{
		show_error("checkpoint_record","one_chunk","BYTE cannot read");
		return FALSE;
	}
	//�����ݲ������ݿ�
	resTF=mysql_FILELAYER_checkpoint_insert(checkpointptr);
	if(resTF==FALSE)
	{
		show_error("checkpoint_record","one_chunk","No memory");
		return FALSE; 
	}

	free(orgfilename);
	free(upfilename);
	free(orgpath);
	free(uppath);
	free(orgchunkptr);
	free(orgcontent);
	free(checkpointptr);
	return TRUE;
}
int checkpoint_recover_recent_request(int requestnum)
{
	//��ʼ�����޸��߼�
	int i,resTF;
	UINT64 requestID;
	CHECKPOINTINF *checkpointinfptr;
	int groupsize;

	//��һ����ȡ���ֵ
	if(requestnum>Requestlognumber)//������������¼����Ҫ����
	{
		show_error("checkpoint_recover","recent_request","too many recover request");
		return FALSE;
	}
	checkpointinfptr=talloc(CHECKPOINTINF,1);
	if(checkpointinfptr==NULL)
	{
		show_error("checkpoint_recover","recent_request","No memory");
		return FALSE;
	}
	//��ȡ��ǰ�����requstID����
	resTF=mysql_FILELAYER_checkpoint_select_request_max_indexandcount(checkpointinfptr);
	if(resTF==FALSE)
	{
		show_error("checkpoint_recover","recent_request","select cannot execute");
		return FALSE;
	}
	requestID=checkpointinfptr->reqindex;
	if(requestID<requestnum)
	{
		requestnum=requestID;//��������ָܻ������Ƕ���
	}
	for(i=0;i<requestnum;i++)
	{
		resTF=checkpoint_recover_one_request(checkpointinfptr);
		if(resTF==FALSE)
		{
			show_error("checkpoint_recover","recent_request","select cannot execute");
			return FALSE;
		}
	}

	return TRUE;
}
int checkpoint_recover_one_request(CHECKPOINTINF *checkpointinfptr)
{
	UINT64 requestID;
	int i,reqcount,resTF,chunksize;

	CHECKPOINT *checkpointptr,*curcheckpointptr;
	CHECKPOINTGROUP *checkpointgrpptr;

	char *orgpath,*uppath;

	//�Ȼ�ȡ��Ҫ����
	requestID=checkpointinfptr->reqindex;
	reqcount=checkpointinfptr->reqcount;
	chunksize=checkpointinfptr->chunksize;

	checkpointgrpptr=talloc(CHECKPOINTGROUP,1);
	if(checkpointgrpptr==NULL)
	{
		show_error("checkpoint_recover","one_request","No memory");
		return FALSE; 
	}

	

	checkpointptr=talloc(CHECKPOINT,reqcount);
	if(checkpointptr==NULL)
	{
		show_error("checkpoint_recover","one_request","No memory");
		return FALSE; 
	}

	curcheckpointptr=checkpointptr;
	for(i=0;i<reqcount;i++)
	{
		orgpath=talloc(char,1024);
		if(orgpath==NULL)
		{
			show_error("checkpoint_recover","one_request","No memory");
			return FALSE;
		}
		uppath=talloc(char,1024);
		if(uppath==NULL)
		{
			show_error("checkpoint_recover","one_request","No memory");
			return FALSE;
		}
		curcheckpointptr->orgcontent=orgpath;
		curcheckpointptr->upcontent=uppath;

		curcheckpointptr++;
	}
	

	checkpointgrpptr->checkpointptr=checkpointptr;
	checkpointgrpptr->groupsize=reqcount;
	//��λ��Щ����Ҫ�ָ�
	resTF=mysql_FILELAYER_checkpoint_select_group(checkpointgrpptr,requestID);
	if(resTF==FALSE)
	{
		show_error("checkpoint_recover","one_request","chunk cannot obtain");
		return FALSE;
	}

	//ָ�븴λ��ʼ�ָ�����
	curcheckpointptr=checkpointptr;
	for(i=0;i<reqcount;i++)
	{
		//����ָ�ԭʼ��
		resTF=checkpoint_recover_one_chunk(curcheckpointptr);
		if(resTF==FALSE)
		{
			show_error("checkpoint_recover","one_request","chunk cannot recover");
			return FALSE;
		}
		curcheckpointptr++;
	}
	//�����ڴ�
	curcheckpointptr=checkpointptr;//ָ���λ
	for(i=0;i<reqcount;i++)
	{
		orgpath=curcheckpointptr->orgcontent;
		uppath=curcheckpointptr->upcontent;
		free(orgpath);
		free(orgpath);
	}
	free(checkpointgrpptr);
	free(checkpointptr);

	return TRUE;
}
int checkpoint_recover_one_chunk(CHECKPOINT *checkpointptr)
{
	int resTF,chunksize;
	char *orgpath,*orgname;

	UINT64 regionID,stripID,strsetID,chunkID;
	int regionoffset,stripoffset,strsetoffset,chunkoffset;
	//BYTE *orgcontent;
	BYTE *oldcontentptr;
	BYTE *orgcontent,*upcontent;//��Ҫ�����ռ��¼����

	REGIONGROUP *sysregptr;//��ȡȫ������ָ��
	REGION *regionptr,*curregionptr;

	STRIPGROUP *stripgrpptr;
	STRIP *stripptr,*curstripptr;

	STRIPSECTGROUP *strsetgrpptr;
	STRIPSECT *strsetptr,*curstrsetptr;

	CHUNKGROUP *chunkgrpptr;
	CHUNK *chunkptr,*curchunkptr;
	//��ȡ���е�
	chunksize=checkpointptr->chunksize;
	orgpath=talloc(char,1024);
	if(orgname==NULL)
	{
		show_error("checkpoint_recover","one_request","No memory");
		return FALSE;
	}
	orgcontent=talloc(BYTE,chunksize);
	if(orgcontent==NULL)
	{
		show_error("checkpoint_recover","one_request","No memory");
		return FALSE; 
	}
	/*upcontent=talloc(BYTE,chunksize);
	if(orgcontent==NULL)
	{
		show_error("checkpoint_recover","one_request","No memory");
		return FALSE;
	}*/

	regionID=checkpointptr->regionID;
	stripID=checkpointptr->stripID;
	strsetID=checkpointptr->strsetID;
	strsetID=checkpointptr->strsetID;

	regionoffset=checkpointptr->regionoffset;
	stripoffset=checkpointptr->stripoffset;
	strsetoffset=checkpointptr->strsetoffset;
	chunkoffset=checkpointptr->chunkoffset;

	sysregptr=get_state_gloregiongroup_PTR();

	regionptr=sysregptr->regiongroup;
	curregionptr=regionptr+regionoffset;

	stripgrpptr=curregionptr->striplist;
	stripptr=stripgrpptr->stripgroup;
	curstripptr=stripptr+stripoffset;

	strsetgrpptr=curstripptr->stripsectlist;
	strsetptr=strsetgrpptr->stripsectgroup;
	curstrsetptr=strsetptr+strsetoffset;

	chunkgrpptr=curstrsetptr->chunklist;
	chunkptr=chunkgrpptr->ckgroup;
	curchunkptr=chunkptr+chunkoffset;

	//������һ����Ҫ�ҵ�����
	oldcontentptr=curchunkptr->chunkcontent;//�����ֳ�

	orgpath=checkpointptr->orgcontent;
	//
	resTF=file_FILELAYER_BYTE_READER_ORG(orgpath,orgcontent,chunksize);
	if(resTF==FALSE)
	{
		show_error("checkpoint","recover_one_chunk","data cannot read");
		return FALSE;
	}
	curchunkptr->chunkcontent=orgcontent;
	//������д������
	resTF=file_FILELAYER_CHUNK_WRITER_DATA(curchunkptr);
	if(resTF==FALSE)
	{
		show_error("checkpoint","recover_one_chunk","data cannot write");
		return FALSE;
	}
	curchunkptr->chunkcontent=oldcontentptr;
	return TRUE;
}