#ifndef _EVENODD
#define _EVENODD
#include "global_define.h"
#include "galois.h"
#include "cauchy.h"
#include "matrix.h"
#include "profile.h"
#include "update_API.h"
//生成编码举证
extern int EVENODD_add_grandmother(BITMATRIX *matrix);
extern int EVENODD_create_encode_matrix(BITMATRIX *matrix);

//下面是系统调用的API
extern int EVENODD_API(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr);
extern int EVENODD_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix);

extern int EVENODD_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);
#endif