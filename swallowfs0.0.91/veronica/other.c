#include "other.h"
int OTHER_calculate_parity_strip(STRIP *stripptr,int subtype)
{
	int resTF;
	switch(subtype)
	{
	case STAR:
		resTF=STAR_API(stripptr);
		if(resTF==FALSE)
		{
			show_error("OTHER","calculate_parity_strip","STAR can't run");
			return FALSE;
		}
		break;
	case GENRDP:
		resTF=GENRDP_API(stripptr);
		if(resTF==FALSE)
		{
			show_error("OTHER","calculate_parity_strip","Generalization GDP can't run");
			return FALSE;
		}
		break;
	}
}
int OTHER_calculate_parity(STRIPBLOCKGROUP *stripblockgroupptr,int subtype)
{
	int i,stripnum,resTF;
	STRIPBLOCK *stripblockptr,*curstripblockptr;
	STRIP *stripptr;

	stripblockptr=stripblockgroupptr->stripblockptr;
	stripnum=stripblockgroupptr->groupsize;

	curstripblockptr=stripblockptr;
	for(i=0;i<stripnum;i++)
	{
		stripptr=curstripblockptr->stripptr;
		resTF=OTHER_calculate_parity_strip(stripptr,subtype);
		if(resTF==FALSE)
		{
			show_error("","","");
			return FALSE;
		}
		curstripblockptr++;
	}
	return TRUE;
}