#include "update_API.h"

int UPDATE_API_bitmatrix_update_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,//
											CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix)
{
	int resTF;
	int selectindex;
	selectindex=UPDATESELECT;
	switch(selectindex)
	{
	case MATRIXINTERFACE:
		resTF=matrix_bitmatrix_update_stripsect_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,pparity,qparity,
												parityblockgroupptr,matrix);
		if(resTF==FALSE)
		{
			show_error("UPDATE_API","bitmatrix_update_RAID6","");
			return FALSE;
		}
		break;
	case UPDATEOPTINTERFACE:
		resTF=UPDATE_OPT_update_scheduling_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,pparity,qparity,
												parityblockgroupptr,matrix);
		if(resTF==FALSE)
		{
			show_error("UPDATE_API","bitmatrix_update_RAID6","");
			return FALSE;
		}
	}
	return TRUE;
}
int UPDATE_API_matrix_update_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,
											CHUNKBLOCKGROUP *parityblockgroupptr,INTMATRIX *matrix)
{
	int resTF;
	int selectindex;
	selectindex=UPDATESELECT;
	switch(selectindex)
	{
	case MATRIXINTERFACE:
	case UPDATEOPTINTERFACE:
		resTF=matrix_matrix_update_stripsect_RAID6(chunkpositionblockgroupptr,strsetblockgroupptr,pparity,qparity,
											parityblockgroupptr,matrix);
		if(resTF==FALSE)
		{
			show_error("UPDATE_API","matrix_update_RAID6","matrix stripsect can't update");
			return FALSE;
		}
		break;
	}
	return TRUE;
}

int UPDATE_API_bitmatrix_update(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										STRIP *stripptr,CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix)
{
	int resTF;
	int selectindex;
	selectindex=UPDATESELECT;
	switch(selectindex)
	{
	case MATRIXINTERFACE:
		resTF=matrix_bitmatrix_update_strip(chunkpositionblockgroupptr,stripptr,parityblockgroupptr,matrix);
		if(resTF==FALSE)
		{
			show_error("UPDATE_API","bitmatrix_update","strip can't update");
			return FALSE;
		}
		break;
	case UPDATEOPTINTERFACE:
		resTF=UPDATE_OPT_update_scheduling(chunkpositionblockgroupptr,stripptr,parityblockgroupptr,matrix);
		if(resTF==FALSE)
		{
			show_error("UPDATE_API","bitmatrix_update","strip can't update");
			return FALSE;
		}
		break;
	}
	return TRUE;
}
int UPDATE_API_matrix_update(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
									STRIP *stripptr,CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix)
{
	int resTF;
	int selectindex;
	selectindex=UPDATESELECT;
	switch(selectindex)
	{
	case MATRIXINTERFACE:
	case UPDATEOPTINTERFACE:
		resTF=matrix_matrix_update_strip(chunkpositionblockgroupptr,stripptr,parityblockgroupptr,matrix);
		if(resTF==FALSE)
		{
			show_error("UPDATE_API","matrix_update","strip can't calculate");
			return FALSE;
		}
		break;
	}
	return TRUE;
}