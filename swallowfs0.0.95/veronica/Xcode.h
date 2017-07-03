#ifndef _XCODE
#define _XCODE
#include "global_define.h"
#include "galois.h"
#include "matrix.h"
#include "cauchy.h"
#include "profile.h"
extern int XCODE_create_encode_matrix(BITMATRIX *matrix);//这里将XCODE横过来建立编码阵,通过映射在将其竖向防止

extern int XCODE_API(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr);
extern int XCODE_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);
#endif