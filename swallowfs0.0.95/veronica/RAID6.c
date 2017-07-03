#include "RAID6.h"
//RAID6计算校验块
//处理一个strip中的编码
int RAID6_do_parity(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr,int subtype)
{
	//根据自类别调用相应的函数
	int resTF;
	switch(subtype)
	{
	case EVENODD:
		resTF=EVENODD_API(strsetblockgroupptr,pparityptr,qparityptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","do_parity","EVENODD can't run");
			return FALSE;
		}
		break;
	case RDP:
		resTF=RDP_API(strsetblockgroupptr,pparityptr,qparityptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","do_parity","RDP can't run");
			return FALSE;
		}
		break;
	case LIBERATION:
		resTF=LIBERATION_API(strsetblockgroupptr,pparityptr,qparityptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","do_parity","LIBERATION can't run");
			return FALSE;
		}
		break;
	case MDRI:
		resTF=MDRI_API(strsetblockgroupptr,pparityptr,qparityptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","do_parity","MDRI can't run");
			return FALSE;
		}
		break;
	case MDRII:
		resTF=MDRII_API(strsetblockgroupptr,pparityptr,qparityptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","do_parity","MDRII can't run");
			return FALSE;
		}
		break;
	case XCODE://这样写之后再改
		resTF=XCODE_API(strsetblockgroupptr,pparityptr,qparityptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","do_parity","XCODE can't run");
			return FALSE;
		}
		break;
	case PCODE:
		resTF=PCODE_API(strsetblockgroupptr,pparityptr,qparityptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","do_parity","PCODE can't run");
			return FALSE;
		}
		break;
	//以下两种是非MDS编码,可以说是准RAID-6算法
	case WEAVER:
		resTF=WEAVER_API_RAID6(strsetblockgroupptr,pparityptr,qparityptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","do_parity","WEAVER can't run");
			return FALSE;
		}
		break;
	case HOVER:
		resTF=HOVER_API_RAID6(strsetblockgroupptr,pparityptr,qparityptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","do_parity","HoVer can't run");
			return FALSE;
		}
		break;
	case CLASSICRS:
		resTF=reed_sol_API_RAID6(strsetblockgroupptr,pparityptr,qparityptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","do_parity","CLASSIC RS can't run");
			return FALSE;
		}
		break;
	case CAUCHYORGRS:
		resTF=cauchy_org_API_RAID6(strsetblockgroupptr,pparityptr,qparityptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","do_parity","ORG CAUCHYRS can't run");
			return FALSE;
		}
		break;
	case CAUCHYRS:
		resTF=cauchy_API_RAID6(strsetblockgroupptr,pparityptr,qparityptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","do_parity","CAUCHYRS can't run");
			return FALSE;
		}
		break;
	case BLAUMROTH:
		resTF=LIBERATION_blaum_roth_API(strsetblockgroupptr,pparityptr,qparityptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","do_parity","blaum_roth can't run");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
//使用数据块生成相应的PQ数据stripsect
int RAID6_calculate_parity_strip(STRIP *stripptr,int subtype)
{
	//找出相应的P盘、Q盘和数据盘
	 
	STRIPSECT *pparityptr,*qparityptr;
	int i,resTF,strsetgroupsize,isparity;
	STRIPSECTGROUP *strsetgroupptr;
	STRIPSECT *strsetptr,*curstrsectptr;

	STRIPSECTBLOCKGROUP *strsetblockgroupptr;
	STRIPSECTBLOCK *strsetblockptr,*curstrsetblockptr;
	int strsetnum;
	
	strsetgroupptr=stripptr->stripsectlist;

	strsetptr=strsetgroupptr->stripsectgroup;
	strsetgroupsize=strsetgroupptr->groupsize;
	
	//开内存
	strsetblockgroupptr=talloc(STRIPSECTBLOCKGROUP,1);
	if(strsetblockgroupptr==NULL)
	{
		show_error("RAID6","calculate_parity_strip","No memory");
		return FALSE;
	}

	strsetblockptr=talloc(STRIPSECTBLOCK,strsetgroupsize-2);//将用于记录当前的数据
	if(strsetblockptr==NULL)
	{
		show_error("RAID6","calculate_parity_strip","No memory");
		return FALSE;
	}
	strsetblockgroupptr->stripsectblockptr=strsetblockptr;
	strsetblockgroupptr->groupsize=strsetgroupsize-2;

	curstrsectptr=strsetptr;
	curstrsetblockptr=strsetblockptr;
	strsetnum=0;
	for(i=0;i<strsetgroupsize;i++)
	{
		isparity=curstrsectptr->isparity;
		if(isparity==FALSE)
		{
			curstrsetblockptr->stripsectptr=curstrsectptr;
			curstrsetblockptr->stripsectid=curstrsectptr->StripsectID;

			curstrsetblockptr++;
			strsetnum++;
		}
		if(isparity==PPARITY)
		{
			pparityptr=curstrsectptr;
		}
		if(isparity==QPARITY)
		{
			qparityptr=curstrsectptr;
		}

		curstrsectptr++;
	}
	resTF=RAID6_do_parity(strsetblockgroupptr,pparityptr,qparityptr,subtype);
	if(resTF==FALSE)
	{
		show_error("RAID6","calculate_parity_strip","RAID6 do parity");
		return FALSE;
	}
	return TRUE;
}

//RAID6计算校验块
int RAID6_calculate_parity(STRIPBLOCKGROUP *stripblockgroupptr,int subtype)
{
	//将数据
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	STRIP *stripptr;
	int i,resTF,stripgroupsize;

	stripblockptr=stripblockgroupptr->stripblockptr;
	stripgroupsize=stripblockgroupptr->groupsize;

	curstripblockptr=stripblockptr;
	for(i=0;i<stripgroupsize;i++)
	{
		stripptr=curstripblockptr->stripptr;
		resTF=RAID6_calculate_parity_strip(stripptr,subtype);
		if(resTF==FALSE)
		{
			show_error("RAID6","calculate_parity","the strip can't calculate parity");
			return FALSE;
		}
		curstripblockptr++;
	}
	return TRUE;
}
//处理一个条带中的chunkblock
int RAID6_decoder_parity_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,int subtype)
{

	return TRUE;
}
//计算stripblockgroup中的strip的源码块
int RAID6_decoder_parity(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr,int subtype)
{
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	STRIPGROUP *stripgroupptr;
	STRIP *stripptr,*curstripptr;
	int i,resTF,stripgroupsize;
	if(stripblockgroupptr==NULL)
	{
		stripgroupptr=regionptr->striplist;

		stripptr=stripgroupptr->stripgroup;
		stripgroupsize=stripgroupptr->groupsize;

		curstripptr=stripptr;
		for(i=0;i<stripgroupsize;i++)
		{
			resTF=RAID6_decoder_parity_strip(stripptr,errormatrix,subtype);
			if(resTF==FALSE)
			{
				show_error("RAID6","decoder_parity","the strip can't calculate data");
				return FALSE;
			}
			curstripptr++;
		}
	}
	else
	{
		stripblockptr=stripblockgroupptr->stripblockptr;
		stripgroupsize=stripblockgroupptr->groupsize;

		curstripblockptr=stripblockptr;
		for(i=0;i<stripgroupsize;i++)
		{
			stripptr=curstripblockptr->stripptr;
			resTF=RAID6_decoder_parity_strip(stripptr,errormatrix,subtype);
			if(resTF==FALSE)
			{
				show_error("RAID6","decoder_parity","the strip can't calculate data");
				return FALSE;
			}
			curstripblockptr++;
		}
	}
	return TRUE;
}
//计算解码的源码块
int RAID6_decoder_parity_degrade_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype)
{
	int resTF;
	//开始分配请求
	switch(subtype)
	{
	case EVENODD:
		resTF=EVENODD_degrade_API(chunkptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("RAID6","decoder_parity_degrade_chunk","EVENODD degrade can't run");
			return FALSE;
		}
		break;
	case RDP:
		resTF=RDP_degrade_API(chunkptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("RAID6","decoder_parity_degrade_chunk","RDP degrade can't run");
			return FALSE;
		}
		break;
	case LIBERATION:
		resTF=LIBERATION_degrade_API(chunkptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("RAID6","decoder_parity_degrade_chunk","LIBERATION degrade can't run");
			return FALSE;
		}
		break;
	case MDRI:
		resTF=MDRI_degrade_API(chunkptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("RAID6","decoder_parity_degrade_chunk","MDRI degrade can't run");
			return FALSE;
		}
		break;
	case MDRII:
		resTF=MDRII_degrade_API(chunkptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("RAID6","decoder_parity_degrade_chunk","MDRI degrade can't run");
			return FALSE;
		}
		break;
	case XCODE:
		break;
	case PCODE:
		break;
	case WEAVER:
		break;
	case CLASSICRS:
		resTF=reed_sol_degrade_API_RAID6(chunkptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("RAID6","decoder_parity_degrade_chunk","CLASSICRS degrade can't run");
			return FALSE;
		}
		break;
	case CAUCHYORGRS:
		resTF=reed_sol_degrade_API_RAID6(chunkptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("RAID6","decoder_parity_degrade_chunk","CAUCHYORGRS degrade can't run");
			return FALSE;
		}
		break;
	case CAUCHYRS:
		resTF=cauchy_degrade_API_RAID6(chunkptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("RAID6","decoder_parity_degrade_chunk","CAUCHYRS degrade can't run");
			return FALSE;
		}
		break;
	case BLAUMROTH:
		resTF=LIBERATION_blaum_roth_degrade_API(chunkptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("RAID6","decoder_parity_degrade_chunk","BLAUMROTH degrade can't run");
			return FALSE;
		}
		break;
	}


	return TRUE;
}
//计算块组的数据
int RAID6_decoder_parity_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype)
{
	int i,resTF;
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *chunkptr;
	int chunknum;

	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunknum=chunkblockgroupptr->groupsize;

	curchunkblockptr=chunkblockptr;
	for(i=0;i<chunknum;i++)
	{
		chunkptr=curchunkblockptr->chunkptr;
		resTF=RAID6_decoder_parity_degrade_chunk(chunkptr,errormatrix,subtype);
		if(resTF==FALSE)
		{
			show_error("RAID6","decoder_parity","chunk data can't decode");
			return FALSE;
		}
		curchunkblockptr++;
	}
	return TRUE;
}


//degrade需要的map的数据
int RAID6_degrade_map_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype)
{
	return TRUE;
}
int RAID6_degrade_map_chunkblock(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype)
{
	int i,resTF,chunknum;
	CHUNKBLOCK *chunkblockptr,*curchunkblockptr;
	CHUNK *chunkptr;

	chunkblockptr=chunkblockgroupptr->chunkblockptr;
	chunknum=chunkblockgroupptr->groupsize;

	curchunkblockptr=chunkblockptr;
	for(i=0;i<chunknum;i++)
	{
		chunkptr=curchunkblockptr->chunkptr;
		resTF=RAID6_degrade_map_chunk(chunkptr,errormatrix,subtype);
		if(resTF==FALSE)
		{
			show_error("RAID6","degrade_map_chunkblock","chunk data can't map");
			return FALSE;
		}
	}
	return TRUE;
}
//recover需要的map数据
int RAID6_recover_map_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,REGION *regionptr)
{
	return TRUE;
}
int RAID6_recover_map_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr)
{
	int i,resTF,stripnum;
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	STRIP *stripptr;

	stripblockptr=stripblockgroupptr->stripblockptr;
	stripnum=stripblockgroupptr->groupsize;

	curstripblockptr=stripblockptr;
	for(i=0;i<stripnum;i++)
	{
		stripptr=curstripblockptr->stripptr;
		resTF=RAID6_recover_map_strip(stripptr,errormatrix,regionptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","recover_map_strip","chunk data can't map");
			return FALSE;
		}
		curstripblockptr++;
	}
	return TRUE;
}
//计算一个条带中的
int RAID6_update_encode_chunkblock_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr,int subtype)
{
	int resTF;
	switch(subtype)
	{
	case EVENODD:
		resTF=EVENODD_update_API(chunkpositionblockgroupptr,parityblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock_strip","EVENODD can't run");
			return FALSE;
		}
		break;
	case RDP:
		resTF=RDP_update_API(chunkpositionblockgroupptr,parityblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock_strip","RDP can't run");
			return FALSE;
		}
		break;
	case LIBERATION:
		resTF=LIBERATION_update_API(chunkpositionblockgroupptr,parityblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock_strip","LIBERATION can't run");
			return FALSE;
		}		
		break;
	case BLAUMROTH:
		resTF=LIBERATION_blaum_roth_update_API(chunkpositionblockgroupptr,parityblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock_strip","Blaum Roth can't run");
			return FALSE;
		}
		break;
	case MDRI:
		resTF=MDRI_update_API(chunkpositionblockgroupptr,parityblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock_strip","MDR can't run");
			return FALSE;
		}	
		break;
	case XCODE:
		resTF=XCODE_update_API(chunkpositionblockgroupptr,parityblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock_strip","XCODE can't run");
			return FALSE;
		}
		break;
	case PCODE:
		resTF=PCODE_update_API(chunkpositionblockgroupptr,parityblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock_strip","PCODE can't run");
			return FALSE;
		}
		break;
	case WEAVER:
		resTF=WEAVER_update_API_RAID6(chunkpositionblockgroupptr,parityblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock_strip","WEAVER can't calculate");
			return FALSE;
		}
		break;
	case HOVER:
		resTF=HOVER_update_API_RAID6(chunkpositionblockgroupptr,parityblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock_strip","HOVER can't calculate");
			return FALSE;
		}
		break;
	case CLASSICRS:
		resTF=reed_sol_update_API_RAID6(chunkpositionblockgroupptr,parityblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock_strip","CLASSICRS can't calculate");
			return FALSE;
		}
		break;
	case CAUCHYORGRS:
		resTF=cauchy_org_update_API_RAID6(chunkpositionblockgroupptr,parityblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock_strip","CAUCHYORGRS can't calculate");
			return FALSE;
		}
		break;
	case CAUCHYRS:
		resTF=cauchy_update_API_RAID6(chunkpositionblockgroupptr,parityblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock_strip","CAUCHYRS can't calculate");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
//计算所有的update数据
int RAID6_update_encode_chunkblock(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,int subtype)
{
	//计算条带
	int i,resTF;
	CHUNKPOSITIONBLOCK *chunkpositionblockptr,*curchunkpositionblockptr;
	CHUNK *chunkptr;
	//int chunknum;

	STRIPBLOCKGROUP *stripblockgroupptr;
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	STRIP *stripptr;
	STRIPDES *stripdesptr;
	int stripnum;

	//CHUNKBLOCKSTRIPGROUP *chunkblockstripgroupptr;
	//CHUNKBLOCKSTRIP *chunk;
	CHUNKPOSITIONBLOCKGROUP *souchunkpositionblockgroupptr;
	CHUNKPOSITIONBLOCK *souchunkpositionblockptr;
	int chunknum,disknum;

	chunkpositionblockptr=chunkpositionblockgroupptr->chunkblockptr;
	chunknum=chunkpositionblockgroupptr->groupsize;

	stripblockptr=talloc(STRIPBLOCK,chunknum);
	if(stripblockptr==NULL)
	{
		show_error("RAID6","update_encode_chunkblock","No memory");
		return FALSE;
	}
	
	stripblockgroupptr=talloc(STRIPBLOCKGROUP,1);
	if(stripblockgroupptr==NULL)
	{
		show_error("RAID6","update_encode_chunkblock","No memory");
		return FALSE;
	}
	stripblockgroupptr->stripblockptr=stripblockptr;
	stripblockgroupptr->groupsize=0;

	curchunkpositionblockptr=chunkpositionblockptr;
	for(i=0;i<chunknum;i++)
	{
		chunkptr=curchunkpositionblockptr->chunkptr;
		stripptr=chunkptr->stripptr;
		resTF=profile_stripblockgroup_strip_add(stripblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock","stripblock can't add");
			return FALSE;
		}
	}
	stripdesptr=stripptr->strdes;
	chunknum=stripdesptr->chunknum;
	disknum=stripdesptr->disknum;

	//开chunk空间用于记下一个条带的信息
	souchunkpositionblockgroupptr=talloc(CHUNKPOSITIONBLOCKGROUP,1);
	if(souchunkpositionblockgroupptr==NULL)
	{
		show_error("RAID6","update_encode_chunkblock","No memory");
		return FALSE;
	}

	souchunkpositionblockptr=talloc(CHUNKPOSITIONBLOCK,chunknum*disknum);
	if(souchunkpositionblockptr==NULL)
	{
		show_error("RAID6","update_encode_chunkblock","No memory");
		return FALSE;
	}
	souchunkpositionblockgroupptr->chunkblockptr=souchunkpositionblockptr;
	souchunkpositionblockgroupptr->groupsize=0;

	stripblockptr=stripblockgroupptr->stripblockptr;
	stripnum=stripblockgroupptr->groupsize;

	curstripblockptr=stripblockptr;
	for(i=0;i<stripnum;i++)
	{
		stripptr=curstripblockptr->stripptr;
		resTF=profile_chunkblockpositiongroup_from_chunkblockpositiongroup_search_ptr(souchunkpositionblockgroupptr,chunkpositionblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock","chunkposition can't findt");
			return FALSE;
		}
		resTF=RAID6_update_encode_chunkblock_strip(souchunkpositionblockgroupptr,parityblockgroupptr,stripptr,subtype);
		if(resTF==FALSE)
		{
			show_error("RAID6","update_encode_chunkblock","chunkblock can't calculate");
			return FALSE;
		}
		curstripblockptr++;
	}
	return TRUE;
}