#ifndef _REED_SOL_CLASSIC
#define _REED_SOL_CLASSIC
#include "galois.h"
#include "global_define.h"
#include "matrix.h"
//Vandermonder矩阵
extern int reed_sol_r6_matrix(INTMATRIX *matrix);//主要是用于生成RAID-6的vandermonder阵
extern int reed_sol_vandermonde_coding_matrix(INTMATRIX *matrix);//主要是用于任意生成vandermonder矩阵
extern int reed_sol_big_vandermonde_distribution_matrix(INTMATRIX *matrix);//生成vandermonder分布矩阵
extern int reed_sol_extended_vandermonde_matrix(INTMATRIX *matrix);//根据矩阵数据生成范的蒙行列式

//在raid6情况下RS无需生成编码矩阵
extern int reed_sol_r6_encode_w(CHUNKBLOCKGROUP *datachk,CHUNK *pchunkptr,CHUNK *qchunkptr,int w);//对应相应的r6系统进行编码
extern int reed_sol_r6_encode(CHUNKBLOCKGROUP *datachk,CHUNK *pchunkptr,CHUNK *qchunkptr,ENDECODEPARA *para);//对应相应的r6系统进行编码并且将r6矩阵保存在para中

extern int reed_sol_r6_decode_w(CHUNKBLOCKGROUP *datachk,CHUNK *pchunkptr,CHUNK *qchunkptr,int w,ERASES *erarray);//对应相应的r6系统进行编码
extern int reed_sol_r6_decode(CHUNKBLOCKGROUP *datachk,CHUNK *pchunkptr,CHUNK *qchunkptr,ENDECODEPARA *para,ERASES *erarray);//对于相应的r6进行解码并且将解码矩阵保存在para中

extern int reed_sol_van_encode_w(CHUNKBLOCKGROUP *datachk,CHUNKBLOCKGROUP *parachk,ENDECODEPARA *para);//根据datachk和parachk的大小进行编码
extern int reed_sol_van_encode(CHUNKBLOCKGROUP *datachk,CHUNKBLOCKGROUP *parachk,ENDECODEPARA *para);//根据datachk和parachk的大小进行编码并且将编码矩阵保存在para中

extern int reed_sol_van_decode_w(CHUNKBLOCKGROUP *datachk,CHUNKBLOCKGROUP *parachk,int w,ERASES *erarray);//对于相应的van进行解码
extern int reed_sol_van_decode(CHUNKBLOCKGROUP *datachk,CHUNKBLOCKGROUP *parachk,ENDECODEPARA *para,ERASES *erarray);//对于相应的van进行解码并且将解码矩阵保存在para中

extern int reed_sol_API_RAID6(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr);//classic RS编码raid6接口
extern int reed_sol_API(STRIP *stripptr);//经典RS编码接口


extern int reed_sol_degrade_API_RAID6(CHUNK *chunkptr,ERRORPATTERN *errormatrix);
extern int reed_sol_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix);

extern int reed_sol_update_API_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);//RAID6的update操作
extern int reed_sol_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);//update操作

extern int reed_sol_decoder_API_strip(STRIP *stripptr,ERRORPATTERN *errormatrix);//经典RS解码接口
extern int reed_sol_decoder_API_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix);//经典RS解码接口
#endif