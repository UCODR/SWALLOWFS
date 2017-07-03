  /*
This program is created by Jiajie Shen 
2015.1.18
沈佳杰创建2014.1.18
*/
//仿制PLank代码
#ifndef _CAUCHY_H
#define _CAUCHY_H
//实现基础基础Cauchy编码
#include "galois.h"
#include "global_define.h"
#include "matrix.h"
#include "update_API.h"
//函数常量定义
static int PPs[33] = { -1, -1, -1, -1, -1, -1, -1, -1,
                       -1, -1, -1, -1, -1, -1, -1, -1,
                       -1, -1, -1, -1, -1, -1, -1, -1,
                       -1, -1, -1, -1, -1, -1, -1, -1, -1 };
static int NOs[33];
static int ONEs[33][33];

static int *cbest_0;
static int *cbest_1;
static int cbest_2[3];
static int cbest_3[7];
static int cbest_4[15];
static int cbest_5[31];
static int cbest_6[63];
static int cbest_7[127];
static int cbest_8[255];
static int cbest_9[511];
static int cbest_10[1023];
static int cbest_11[1023];
static int *cbest_12, *cbest_13, *cbest_14, *cbest_15, *cbest_16, *cbest_17, *cbest_18, *cbest_19, *cbest_20,
           *cbest_21, *cbest_22, *cbest_23, *cbest_24, *cbest_25, *cbest_26, *cbest_27, *cbest_28, *cbest_29, *cbest_30,
           *cbest_31, *cbest_32;
static int cbest_max_k[33] = { -1, -1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 1023, -1,
     -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
     -1, -1, -1, -1 };

static int cbest_init = FALSE;//尚未初始化

static int *cbest_all[33];
//生成矩阵部分
extern int cauchy_inital();//用于初始化系统
extern int cauchy_orgininal_coding_matrix(INTMATRIX *matrix);//生成初始的柯西矩阵
extern int cauchy_orgininal_coding_bitmatrix(BITMATRIX *matrix);//生成相应的bitmatrix

extern int cauchy_xy_coding_matrix(INTMATRIX *matrix, INTARRAY *arrx,INTARRAY *arry);//根据给定x,y生成
extern int cauchy_improve_coding_matrix(INTMATRIX *matrix);//改进cauchy矩阵
extern int cauchy_good_general_coding_matrix(INTMATRIX *matrix);//生成Plank的Cauchy矩阵
extern int cauchy_good_general_coding_bitmatrix(BITMATRIX *matrix);//生成相应的bitmatrix
//统一接口
extern int cauchy_API_RAID6(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr);//RAID6接口
extern int cauchy_API(STRIP *stripptr);//cauchy RS接口

extern int cauchy_degrade_API_RAID6(CHUNK *chunkptr,ERRORPATTERN *errormatrix);
extern int cauchy_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix);

extern int cauchy_update_API_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);
extern int cauchy_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);

extern int cauchy_decoder_API_strip(STRIP *stripptr,ERRORPATTERN *errormatrix);//经典RS解码接口
extern int cauchy_decoder_API_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix);//经典RS解码接口

//随机请求大小接口
extern int cauchy_API_Context(AONTSHAREGROUP *sharegroup,CODEPARA *codeptr,BYTE *context,int strlen);//根据内容和编码参数将文件分成相应的shares
extern int cauchy_API_Sharegroup(AONTSHAREGROUP *sharegroupptr,CODEPARA *codeptr,BITMATRIX *matrixptr);//根据矩阵计算最后几个share

#endif