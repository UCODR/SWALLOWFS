#ifndef _STAR
#define _STAR

#include "global_define.h"
#include "galois.h"
#include "matrix.h"
#include "profile.h"
#include "EVENODD.h"
#include "update_API.h"
extern int STAR_add_second_grandmother(BITMATRIX *matrix);//将第二个祖母块加到第三个矩阵上
extern int STAR_calculate_third_parity_matrix(BITMATRIX *matrix);//计算matrix相应的第三个校验块
extern int STAR_create_encode_matrix(BITMATRIX *matrix);//生成相应的STAR编码矩阵

extern int STAR_API(STRIP *stripptr);//计算一个条带中的校验块
extern int STAR_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix);//降级读

extern int STAR_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);//实现更新
#endif
