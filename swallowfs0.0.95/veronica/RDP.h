#ifndef _RDP_H
#define _RDP_H
#include "global_define.h"
#include "cauchy.h"
#include "matrix.h"
#include "RAID5.h"
#include "update_API.h"
extern int RDP_add_rowparity(BITMATRIX *matrix);//将编码矩阵加入行校验
extern int RDP_create_encode_matrix(BITMATRIX *matrix);//生成相应的RDP编码矩阵

extern int RDP_API(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr);
extern int RDP_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix);

extern int RDP_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);
#endif