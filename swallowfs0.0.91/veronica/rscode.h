#ifndef _RSCODE
#define _RSCODE
#include "global_define.h"
#include "galois.h"
#include "reed_sol_classic.h"
#include "cauchy.h"
#include "cauchy_org.h"
extern int RSCODE_calculate_parity_strip(STRIP *stripptr,int subtype);//����һ�������е�У�飬���ｻ���������д���
extern int RSCODE_calculate_parity(STRIPBLOCKGROUP *stripblockgroupptr,int subtype);//����subtype������ַ�

extern int RSCODE_decoder_parity_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,int subtype);//��������Դ���
extern int RSCODE_decoder_parity(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr,int subtype);//�������������

extern int RSCODE_decoder_parity_degrade_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype);//��������Դ���
extern int RSCODE_decoder_parity_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype);//������������

extern int RSCODE_degrade_map_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype);//degrade��Ҫ��map������
extern int RSCODE_degrade_map_chunkblock(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype);//degrade��Ҫ��map������

extern int RSCODE_recover_map_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover��Ҫ��map����
extern int RSCODE_recover_map_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover��Ҫ��map����

extern int RSCODE_update_encode_chunkblock_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr,int subtype);//����һ�������ڵ�����
extern int RSCODE_update_encode_chunkblock(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,int subtype);//�������е�update����
#endif