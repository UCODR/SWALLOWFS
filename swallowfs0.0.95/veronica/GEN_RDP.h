#ifndef _GENRDP
#define _GENRDP
#include "global_define.h"
#include "galois.h"
#include "matrix.h"
#include "profile.h"
extern int GENRDP_P_disk_add(BITMATRIX *matrix,int tarindex,int souindex);//将p盘中的一行加到目标行

extern int GENRDP_create_encode_matrix(BITMATRIX *matrix);//生成相应的GENRDP编码矩阵

extern int GENRDP_API(STRIP *stripptr);//计算一个条带中的校验块
extern int GENRDP_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix);//降级读

extern int EVENODD_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);//实现更新
#endif