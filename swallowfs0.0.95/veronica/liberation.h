#ifndef _LIBERATION
#define _LIBERATION
#include "global_define.h"
#include "galois.h"
#include "matrix.h"
#include "cauchy.h"
#include "reed_sol_classic.h"
//生成编码矩阵
extern int liberation_create_encode_matrix(BITMATRIX *matrix);//其中y代表k*w设备数量，w代表块长度
extern int liberation_liber8tion_create_encode_matrix(BITMATRIX *matrix);//其中y代表k*w设备数量
extern int liberation_blaum_roth_create_encode_matrix(BITMATRIX *matrix);//其中y代表k*w设备数量，w代表块长度

//接口
extern int LIBERATION_API(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr);
extern int LIBERATION_blaum_roth_API(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr);

extern int LIBERATION_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix);
extern int LIBERATION_blaum_roth_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix);

extern int LIBERATION_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);
extern int LIBERATION_blaum_roth_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);
#endif