#ifndef _CAUCHY_ORG
#define _CAUCHY_ORG
#include "global_define.h"
#include "galois.h"
#include "cauchy.h"
#include "matrix.h"
#include "update_API.h"
extern int cauchy_org_API_RAID6(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr);//ԭʼcauchy RS����RAID6�ӿ�
extern int cauchy_org_API(STRIP *stripptr);//ԭʼcauchy����

extern int cauchy_org_update_API_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);
extern int cauchy_org_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);

extern int cauchy_org_decoder_API_strip(STRIP *stripptr,ERRORPATTERN *errormatrix);//����RS����ӿ�
extern int cauchy_org_decoder_API_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix);//����RS����ӿ�
#endif