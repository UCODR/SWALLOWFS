#include "MSR.h"
int MSR_calculate_parity_strip(STRIP *stripptr,int subtype)
{
	int resTF;
	switch(subtype)
	{
	case FMSR:
		resTF=FMSR_API(stripptr);
		if(resTF==FALSE)
		{
			show_error("MSR","calculate_parity","FMSR can't run");
			return FALSE;
		}
		break;
	case EMSR:
		resTF=EMSR_API(stripptr);
		if(resTF==FALSE)
		{
			show_error("MSR","calculate_parity","EMSR can't run");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int MSR_calculate_parity(STRIPBLOCKGROUP *stripblockgroupptr,int subtype)
{
	int i,resTF,stripblocksize;
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	STRIP *stripptr;

	stripblockptr=stripblockgroupptr->stripblockptr;
	stripblocksize=stripblockgroupptr->groupsize;

	curstripblockptr=stripblockptr;
	for(i=0;i<stripblocksize;i++)
	{
		stripptr=curstripblockptr->stripptr;

		resTF=MSR_calculate_parity_strip(stripptr,subtype);
		if(resTF==FALSE)
		{
			show_error("MBR","calculate_parity","strip parity can't calculate");
			return FALSE;
		}
		curstripblockptr++;
	}
	return TRUE;
}
//计算解码的源码块
int MSR_decoder_parity_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,int subtype)
{
	return TRUE;
}

//计算解码条带组
int MSR_decoder_parity(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr,int subtype)
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
			resTF=MSR_decoder_parity_strip(stripptr,errormatrix,subtype);
			if(resTF==FALSE)
			{
				show_error("MSR","decoder_parity","the strip can't calculate data");
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
			resTF=MSR_decoder_parity_strip(stripptr,errormatrix,subtype);
			if(resTF==FALSE)
			{
				show_error("MSR","decoder_parity","the strip can't calculate data");
				return FALSE;
			}
			curstripblockptr++;
		}
	}
	return TRUE;
}
//计算解码的源码块
int MSR_decoder_parity_degrade_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype)
{
	return TRUE;
}
//计算块组的数据
int MSR_decoder_parity_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype)
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
		resTF=MSR_decoder_parity_degrade_chunk(chunkptr,errormatrix,subtype);
		if(resTF==FALSE)
		{
			show_error("MSR","decoder_parity","chunk data can't decode");
			return FALSE;
		}
		curchunkblockptr++;
	}
	return TRUE;
}

//degrade需要的map的数据
int MSR_degrade_map_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype)
{
	return TRUE;
}
int MSR_degrade_map_chunkblock(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype)
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
		resTF=MSR_degrade_map_chunk(chunkptr,errormatrix,subtype);
		if(resTF==FALSE)
		{
			show_error("MSR","degrade_map_chunkblock","chunk data can't map");
			return FALSE;
		}
	}
	return TRUE;
}

//recover需要的map数据
int MSR_recover_map_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,REGION *regionptr)
{
	return TRUE;
}
int MSR_recover_map_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr)
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
		resTF=MSR_recover_map_strip(stripptr,errormatrix,regionptr);
		if(resTF==FALSE)
		{
			show_error("MSR","recover_map_strip","chunk data can't map");
			return FALSE;
		}
		curstripblockptr++;
	}
	return TRUE;
}
//计算一个条带中的
int MSR_update_encode_chunkblock_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr,int subtype)
{
	return TRUE;
}
//计算所有的update数据
int MSR_update_encode_chunkblock(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,int subtype)
{
	return TRUE;
}