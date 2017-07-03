#include "hamming.h"
int HAMMING_calculate_parity_strip(STRIP *stripptr)
{
	return TRUE;
}
//Hamming����������У��
int HAMMING_calculate_parity(STRIPBLOCKGROUP *stripblockgroupptr)
{
	STRIPBLOCK *stripblock,*curstripblock;
	STRIP *stripptr;
	int i,stripblocksize,resTF;

	stripblock=stripblockgroupptr->stripblockptr;
	stripblocksize=stripblockgroupptr->groupsize;

	curstripblock=stripblock;
	for(i=0;i<stripblocksize;i++)
	{
		stripptr=curstripblock->stripptr;
		resTF=HAMMING_calculate_parity_strip(stripptr);
		if(resTF==FALSE)
		{
			show_error("HAMMING","calculate_parity","strip can't calculate");
			return FALSE;
		}
		curstripblock++;
	}
	return TRUE;
}
//����һ�������е�chunkblock
int HAMMING_decoder_parity_strip(STRIP *stripptr,ERRORPATTERN *errormatrix)
{
	return TRUE;
}
//���㼴��
int HAMMING_decoder_parity(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr)
{
	STRIP *stripptr,*curstripptr;
	STRIPBLOCK	*stripblockptr,*curstripblockptr;
	STRIPGROUP *stripgroupptr;
	int i,stripgroupsize,resTF;
	if(stripblockgroupptr==NULL)
	{
		stripgroupptr=regionptr->striplist;

		stripptr=stripgroupptr->stripgroup;
		stripgroupsize=stripgroupptr->groupsize;

		curstripptr=stripptr;
		for(i=0;i<stripgroupsize;i++)
		{
			resTF=HAMMING_decoder_parity_strip(curstripptr,errormatrix);
			if(resTF==FALSE)
			{
				show_error("HAMMING","decoder_parity","the strip can't calculate data");
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
			resTF=HAMMING_decoder_parity_strip(stripptr,errormatrix);
			if(resTF==FALSE)
			{
				show_error("HAMMING","decoder_parity","the strip can't calculate data");
				return FALSE;
			}
			curstripblockptr++;
		}
	}
	return TRUE;
}

//��������
int HAMMING_decoder_parity_degrade_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix)
{
	return TRUE;
}
//����chunkblockgroup������
int HAMMING_decoder_parity_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix)
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
		resTF=HAMMING_decoder_parity_degrade_chunk(chunkptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("HAMMING","decoder_parity","chunk data can't decode");
			return FALSE;
		}
		curchunkblockptr++;
	}
	return TRUE;
}

//degrade��Ҫ��map������
int HAMMING_degrade_map_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix)
{
	return TRUE;
}
int HAMMING_degrade_map_chunkblock(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix)
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
		resTF=HAMMING_degrade_map_chunk(chunkptr,errormatrix);
		if(resTF==FALSE)
		{
			show_error("HAMMING","degrade_map_chunkblock","chunk data can't map");
			return FALSE;
		}
	}
	return TRUE;
}

//recover��Ҫ��map����
int HAMMING_recover_map_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,REGION *regionptr)
{
	return TRUE;
}

int HAMMING_recover_map_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr)
{
	int i,resTF,stripnum;
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	STRIPGROUP *stripgroupptr;
	STRIP *stripptr,*curstripptr;

	stripblockptr=stripblockgroupptr->stripblockptr;
	stripnum=stripblockgroupptr->groupsize;

	curstripblockptr=stripblockptr;
	for(i=0;i<stripnum;i++)
	{
		stripptr=curstripblockptr->stripptr;
		resTF=HAMMING_recover_map_strip(stripptr,errormatrix,regionptr);
		if(resTF==FALSE)
		{
			show_error("HAMMING","recover_map_strip","chunk data can't map");
			return FALSE;
		}
		curstripblockptr++;
	}
	return TRUE;
}
//����һ�������ڵ�����
int HAMMING_update_encode_chunkblock_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr)
{
	return TRUE;
}
//�������е�update����
int HAMMING_update_encode_chunkblock(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr)
{
	return TRUE;
}