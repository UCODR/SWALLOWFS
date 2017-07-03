#include "global_define.h"
#include "matrix.h"
#include "update_opt.h"

extern int UPDATE_API_bitmatrix_update_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,//
											CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix);
extern int UPDATE_API_matrix_update_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,
											CHUNKBLOCKGROUP *parityblockgroupptr,INTMATRIX *matrix);

extern int UPDATE_API_bitmatrix_update(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										STRIP *stripptr,CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix);
extern int UPDATE_API_matrix_update(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
									STRIP *stripptr,CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix);