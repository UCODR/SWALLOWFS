#ifndef _RAID5
#define _RAID5
#include "galois.h"
#include "matrix.h"
#include "file.h"
extern int RAID5_do_parity(CHUNKBLOCKGROUP *chunkblockgroupptr,CHUNK *parity);//需要将数据进行校验计算,参数1数据块，参数2校验块
extern int RAID5_calculate_parity_strip(STRIP *stripptr);//处理一个strip中的编码
extern int RAID5_calculate_parity(STRIPBLOCKGROUP *stripblockgroupptr);//RAID5计算条带的校验

extern int RAID5_decoder_parity_strip(STRIP *stripptr,ERRORPATTERN *errormatrix);//处理一个条带中的chunkblock
extern int RAID5_decoder_pairty(STRIPBLOCKGROUP *stripblockgrouoptr,ERRORPATTERN *errormatrix,REGION *regionptr);//计算stripblockgroup中的strip的源码块

extern int RAID5_decoder_parity_degrade_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix);//计算解码的源码块
extern int RAID5_decoder_parity_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix);//计算块组的数据

extern int RAID5_degrade_map_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix);//degrade需要的map的数据
extern int RAID5_degrade_map_chunkblock(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix);//degrade需要的map的数据

extern int RAID5_recover_map_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover需要的map数据
extern int RAID5_recover_map_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover需要的map数据

extern int RAID5_update_encode_chunkblock_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);//计算一个条带中的
extern int RAID5_update_encode_chunkblock(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr);//计算所有的update数据
#endif
