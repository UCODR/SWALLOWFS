#ifndef _MSR
#define _MSR
#include "global_define.h"
#include "galois.h"
#include "matrix.h"
#include "reed_sol_classic.h"
#include "cauchy.h"
#include "FMSR.h"
#include "EMSR.h"
extern int MSR_calculate_parity_strip(STRIP *stripptr,int subtype);//对于条带进行编码
extern int MSR_calculate_parity(STRIPBLOCKGROUP *stripblockgroupptr,int subtype);//根据subtype将请求分发

extern int MSR_decoder_parity_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,int subtype);//计算解码的源码块
extern int MSR_decoder_parity(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr,int subtype);//计算解码条带组

extern int MSR_decoder_parity_degrade_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype);//计算解码的源码块
extern int MSR_decoder_parity_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype);//计算块组的数据

extern int MSR_degrade_map_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype);//degrade需要的map的数据
extern int MSR_degrade_map_chunkblock(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype);//degrade需要的map的数据

extern int MSR_recover_map_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover需要的map数据
extern int MSR_recover_map_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover需要的map数据

extern int MSR_update_encode_chunkblock_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr,int subtype);//计算一个条带中的
extern int MSR_update_encode_chunkblock(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,int subtype);//计算所有的update数据
#endif _MSR