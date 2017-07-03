#include "rscode.h"
//这里交给函数自行处理
int RSCODE_calculate_parity_strip(STRIP *stripptr,int subtype)
{
	int resTF;
	//根据subtype进行分配
	switch(subtype)
	{
	case CLASSICRS:
		resTF=reed_sol_API(stripptr);
		if(resTF==FALSE)
		{
			show_error("RSCODE","calculate_parity_strip","CLASSIC RS can't run");
			return FALSE;
		}
		break;
	case CAUCHYORGRS:
		resTF=cauchy_org_API(stripptr);
		if(resTF==FALSE)
		{
			show_error("RSCODE","calculate_parity_strip","CAUCHY_ORG RS can't run");
			return FALSE;
		}
		break;
	case CAUCHYRS:
		resTF=cauchy_API(stripptr);
		if(resTF==FALSE)
		{
			show_error("RSCODE","calculate_parity_strip","CAUCHY RS can't run");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
//根据subtype将请求分发
int RSCODE_calculate_parity(STRIPBLOCKGROUP *stripblockgroupptr,int subtype)
{
	STRIP *stripptr;
	STRIPBLOCK	*stripblockptr,*curstripblockptr;
	
	int i,stripgroupsize,resTF;

	stripblockptr=stripblockgroupptr->stripblockptr;
	stripgroupsize=stripblockgroupptr->groupsize;

	curstripblockptr=stripblockptr;
	for(i=0;i<stripgroupsize;i++)
	{
		stripptr=curstripblockptr->stripptr;
		resTF=RSCODE_calculate_parity_strip(stripptr,subtype);
		if(resTF==FALSE)
		{
			show_error("RSCODE","calculate_parity","the strip can't calculate parity");
			return FALSE;
		}
		curstripblockptr++;
	}
	return TRUE;
}
//计算解码的源码块
int RSCODE_decoder_parity_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,int subtype)
{
	int resTF;
	switch(subtype)
	{
	case CLASSICRS:
		resTF=reed_sol_decoder_API_strip(stripptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("RSCODE","decoder_parity_strip","strip can't decoder");
			return FALSE;
		}
		break;
	case CAUCHYORGRS:
		resTF=cauchy_org_decoder_API_strip(stripptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("RSCODE","decoder_parity_strip","strip can't decoder");
			return FALSE;
		}
		break;
	case CAUCHYRS:
		resTF=cauchy_decoder_API_strip(stripptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("RSCODE","decoder_parity_strip","strip can't decoder");
			return FALSE;
		}
		break;
	}
	return TRUE;
}

int RSCODE_decoder_parity(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr,int subtype)
{
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	STRIP *stripptr,*curstripptr;
	STRIPGROUP *stripgroupptr;
	int i,resTF,stripgroupsize;
	if(stripblockgroupptr==NULL)
	{
		stripgroupptr=regionptr->striplist;

		stripptr=stripgroupptr->stripgroup;
		stripgroupsize=stripgroupptr->groupsize;

		curstripptr=stripptr;
		for(i=0;i<stripgroupsize;i++)
		{
			resTF=RSCODE_decoder_parity_strip(curstripptr,errormatrix,subtype);
			if(resTF==FALSE)
			{
				show_error("RSCODE","decoder_parity","the strip can't calculate data");
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
			resTF=RSCODE_decoder_parity_strip(stripptr,errormatrix,subtype);
			if(resTF==FALSE)
			{
				show_error("RSCODE","decoder_parity","the strip can't calculate data");
				return FALSE;
			}
			curstripblockptr++;
		}
	}
	return TRUE;
}

//计算解码的源码块
int RSCODE_decoder_parity_degrade_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype)
{
	int resTF;
	switch(subtype)
	{
	case CLASSICRS:
		resTF=reed_sol_decoder_API_chunk(chunkptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("RSCODE","decoder_parity_strip","strip can't decoder");
			return FALSE;
		}
		break;
	case CAUCHYORGRS:
		resTF=cauchy_org_decoder_API_chunk(chunkptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("RSCODE","decoder_parity_strip","strip can't decoder");
			return FALSE;
		}
		break;
	case CAUCHYRS:
		resTF=cauchy_decoder_API_chunk(chunkptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("RSCODE","decoder_parity_strip","strip can't decoder");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
//计算块组的数据
int RSCODE_decoder_parity_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype)
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
		resTF=RSCODE_decoder_parity_degrade_chunk(chunkptr,errormatrix,subtype);
		if(resTF==FALSE)
		{
			show_error("RSCODE","decoder_parity","chunk data can't decode");
			return FALSE;
		}
		curchunkblockptr++;
	}
	return TRUE;
}
//degrade需要的map的数据
int RSCODE_degrade_map_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype)
{
	return TRUE;
}
int RSCODE_degrade_map_chunkblock(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype)
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
		resTF=RSCODE_degrade_map_chunk(chunkptr,errormatrix,subtype);
		if(resTF==FALSE)
		{
			show_error("RSCODE","degrade_map_chunkblock","chunk data can't map");
			return FALSE;
		}
	}
	return TRUE;
}
//recover需要的map数据
int RSCODE_recover_map_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,REGION *regionptr)
{
	return TRUE;
}
int RSCODE_recover_map_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr)
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
		resTF=RSCODE_recover_map_strip(stripptr,errormatrix,regionptr);
		if(resTF==FALSE)
		{
			show_error("RSCODE","recover_map_strip","chunk data can't map");
			return FALSE;
		}
		curstripblockptr++;
	}
	return TRUE;
}
//计算一个条带内的数据
int RSCODE_update_encode_chunkblock_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr,int subtype)
{
	int resTF;
	switch(subtype)
	{
	case CLASSICRS:
		resTF=reed_sol_update_API(chunkpositionblockgroupptr,parityblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RSCODE","pdate_encode_chunkblock_strip","Classic RS can't run");
			return FALSE;
		}
		break;
	case CAUCHYORGRS:
		resTF=cauchy_org_update_API(chunkpositionblockgroupptr,parityblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RSCODE","pdate_encode_chunkblock_strip","Cauchy orginal RS can't run");
			return FALSE;
		}
		break;
	case CAUCHYRS:
		resTF=cauchy_update_API(chunkpositionblockgroupptr,parityblockgroupptr,stripptr);
		if(resTF==FALSE)
		{
			show_error("RSCODE","pdate_encode_chunkblock_strip","Cauchy RS can't run");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
//计算所有的update数据
int RSCODE_update_encode_chunkblock(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,int subtype)
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
		show_error("RSCODE","update_encode_chunkblock","No memory");
		return FALSE;
	}
	
	stripblockgroupptr=talloc(STRIPBLOCKGROUP,1);
	if(stripblockgroupptr==NULL)
	{
		show_error("RSCODE","update_encode_chunkblock","No memory");
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
			show_error("RSCODE","update_encode_chunkblock","stripblock can't add");
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
		show_error("RSCODE","update_encode_chunkblock","No memory");
		return FALSE;
	}

	souchunkpositionblockptr=talloc(CHUNKPOSITIONBLOCK,chunknum*disknum);
	if(souchunkpositionblockptr==NULL)
	{
		show_error("RSCODE","update_encode_chunkblock","No memory");
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
			show_error("RSCODE","update_encode_chunkblock","chunkposition can't findt");
			return FALSE;
		}
		resTF=RSCODE_update_encode_chunkblock_strip(souchunkpositionblockgroupptr,parityblockgroupptr,stripptr,subtype);
		if(resTF==FALSE)
		{
			show_error("RSCODE","update_encode_chunkblock","chunkblock can't calculate");
			return FALSE;
		}
		curstripblockptr++;
	}
	return TRUE;
}