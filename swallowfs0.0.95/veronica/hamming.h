#ifndef _HAMMING
#define _HAMMING
#include "galois.h"
#include "matrix.h"
extern int HAMMING_calculate_parity_strip(STRIP *stripptr);//处理一个strip中的编码
extern int HAMMING_calculate_parity(STRIPBLOCKGROUP *stripblockgroupptr);//Hamming计算条带的校验

extern int HAMMING_decoder_parity_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,REGION *regionptr);//处理一个条带中的chunkblock
extern int HAMMING_decoder_parity(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//计算stripblockgroup中的strip的源码块

extern int HAMMING_decoder_parity_degrade_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix);//解码数据
extern int HAMMING_decoder_parity_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix);//计算chunkblockgroup的数据

extern int HAMMING_degrade_map_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix);//degrade需要的map的数据
extern int HAMMING_degrade_map_chunkblock(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix);//degrade需要的map的数据

extern int HAMMING_recover_map_strip(STRIP *stripptr,ERRORPATTERN *errormatrix);//recover需要的map数据
extern int HAMMING_recover_map_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover需要的map数据

extern int HAMMING_update_encode_chunkblock_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);//计算一个条带内的数据
extern int HAMMING_update_encode_chunkblock(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr);//计算所有的update数据
#endif
