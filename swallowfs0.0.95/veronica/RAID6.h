#ifndef _RAID6
#define _RAID6
#include "galois.h"
#include "matrix.h"
#include "cauchy.h"
#include "cauchy_org.h"
#include "RAID5.h"
#include "EVENODD.h"
#include "RDP.h"
#include "liberation.h"
#include "MDR.h"
#include "WEAVER.h"
#include "HoVer.h"
#include "Xcode.h"
#include "Pcode.h"

extern int RAID6_do_parity(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr,int subtype);//使用数据块生成相应的PQ数据stripsect
extern int RAID6_calculate_parity_strip(STRIP *stripptr,int subtype);//处理一个strip中的编码
extern int RAID6_calculate_parity(STRIPBLOCKGROUP *stripblockgroupptr,int subtype);//RAID6计算校验块

extern int RAID6_decoder_parity_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,int subtype);//处理一个条带中的chunkblock
extern int RAID6_decoder_parity(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr,int subtype);//计算stripblockgroup中的strip的源码块

extern int RAID6_decoder_parity_degrade_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype);//计算解码的源码块
extern int RAID6_decoder_parity_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype);//计算块组的数据

extern int RAID6_degrade_map_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype);//degrade需要的map的数据
extern int RAID6_degrade_map_chunkblock(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype);//degrade需要的map的数据

extern int RAID6_recover_map_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover需要的map数据
extern int RAID6_recover_map_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover需要的map数据

extern int RAID6_update_encode_chunkblock_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr,int subtype);//计算一个条带中的
extern int RAID6_update_encode_chunkblock(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,int subtype);//计算所有的update数据
#endif