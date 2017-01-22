#ifndef _WEAVER
#define _WEAVER
#include "global_define.h"
#include "galois.h"
#include "matrix.h"
#include "cauchy.h"
extern int WEAVER_API_RAID6(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr);

extern int WEAVER_update_API_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);
#endif