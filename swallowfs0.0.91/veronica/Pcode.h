#ifndef _PCODE
#define _PCODE
#include "global_define.h"
#include "galois.h"
#include "matrix.h"
#include "cauchy.h"

extern int PCODE_API(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr);
extern int PCODE_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);//RAID6µÄupdate²Ù×÷
#endif