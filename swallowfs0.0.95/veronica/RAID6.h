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

extern int RAID6_do_parity(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr,int subtype);//ʹ�����ݿ�������Ӧ��PQ����stripsect
extern int RAID6_calculate_parity_strip(STRIP *stripptr,int subtype);//����һ��strip�еı���
extern int RAID6_calculate_parity(STRIPBLOCKGROUP *stripblockgroupptr,int subtype);//RAID6����У���

extern int RAID6_decoder_parity_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,int subtype);//����һ�������е�chunkblock
extern int RAID6_decoder_parity(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr,int subtype);//����stripblockgroup�е�strip��Դ���

extern int RAID6_decoder_parity_degrade_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype);//��������Դ���
extern int RAID6_decoder_parity_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype);//������������

extern int RAID6_degrade_map_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype);//degrade��Ҫ��map������
extern int RAID6_degrade_map_chunkblock(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype);//degrade��Ҫ��map������

extern int RAID6_recover_map_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover��Ҫ��map����
extern int RAID6_recover_map_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover��Ҫ��map����

extern int RAID6_update_encode_chunkblock_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr,int subtype);//����һ�������е�
extern int RAID6_update_encode_chunkblock(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,int subtype);//�������е�update����
#endif