#ifndef _MDR_H
#define _MDR_H
#include "global_define.h"
#include "matrix.h"
//构建编码矩阵,其中size是基本盘数量，其中生成包括P盘
extern int MDRI_create_encode_matrix_B(BITMATRIX *matrix);//其中w为条带宽度，k代表数据盘+p盘
extern int MDRII_create_encode_matrix_B(BITMATRIX *matrix);//其中w为条带宽度，k代表数据盘+p盘、


extern int MDRI_create_encode_matrix(BITMATRIX *matrix);//其中w代表w条带宽度，k为数据盘
extern int MDRII_create_encode_matrix(BITMATRIX *matrix);//其中w代表w条带宽度，k为数据盘
//接口
extern int MDRI_API(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr);
extern int MDRII_API(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr);

extern int MDRI_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix);
extern int MDRII_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix);

extern int MDRI_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);
extern int MDRII_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);

static UINT32 MDRIB1matrix[4]={0,1,
								0,0};	
static UINT32 MDRIB2matrix[4]={0,0,
								1,0};
static UINT32 MDRIIB1matrix[16]={1,0,0,1,  
								0,1,1,0,  
								0,0,1,0,   
								0,0,0,1};   
static UINT32 MDRIIB2matrix[16]={1,0,0,0,
								 0,1,0,0,
								 0,1,1,0,
								 1,0,0,1};
static UINT32 MDRIIB3matrix[16]={0,1,0,0,
								 0,0,0,0,
								 0,0,0,0,
								 0,0,1,0};
static UINT32 MDRIIB4matrix[64]={0,0,0,0,
								 1,0,0,0,
								 0,0,0,1,
								 0,0,0,0};
#endif