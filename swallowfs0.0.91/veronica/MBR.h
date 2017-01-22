#ifndef _MBR
#define _MBR
#include "galois.h"
#include "matrix.h"
#include "reed_sol_classic.h"
#include "cauchy.h"
#include "EMBR.h"
#include "FMBR.h"
extern int MBR_calculate_parity_strip(STRIP *stripptr,int subtype);//����һ�������е�У��
extern int MBR_calculate_parity(STRIPBLOCKGROUP *stripblockgroupptr,int subtype);//����У��������

extern int MBR_decoder_parity_strip(STRIP *strippptr,ERRORPATTERN *errormatrix,int subtype);//����һ�������е�chunkblock
extern int MBR_decoder_parity(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr,int subtype);//����stripblockgroup�е�strip��Դ���

extern int MBR_decoder_parity_degrade_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype);//��������Դ���
extern int MBR_decoder_parity_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype);//������������

extern int MBR_degrade_map_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype);//degrade��Ҫ��map������
extern int MBR_degrade_map_chunkblock(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype);//degrade��Ҫ��map������

extern int MBR_recover_map_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover��Ҫ��map����
extern int MBR_recover_map_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover��Ҫ��map����

extern int MBR_update_encode_chunkblock_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr,int subtype);//����һ�������е�
extern int MBR_update_encode_chunkblock(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,int subtype);//�������е�update����

#endif _MBR