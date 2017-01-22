#ifndef _HoVer
#define _HoVer
#include "global_define.h"
#include "galois.h"
#include "matrix.h"
#include "cauchy.h"

extern int HOVER_create_encode_matrix(BITMATRIX *matrix);

extern int HOVER_API_RAID6(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr);
extern int HOVER_update_API_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);//RAID6µÄupdate²Ù×÷
#endif