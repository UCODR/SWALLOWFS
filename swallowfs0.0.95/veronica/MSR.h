#ifndef _MSR
#define _MSR
#include "global_define.h"
#include "galois.h"
#include "matrix.h"
#include "reed_sol_classic.h"
#include "cauchy.h"
#include "FMSR.h"
#include "EMSR.h"
extern int MSR_calculate_parity_strip(STRIP *stripptr,int subtype);//�����������б���
extern int MSR_calculate_parity(STRIPBLOCKGROUP *stripblockgroupptr,int subtype);//����subtype������ַ�

extern int MSR_decoder_parity_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,int subtype);//��������Դ���
extern int MSR_decoder_parity(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr,int subtype);//�������������

extern int MSR_decoder_parity_degrade_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype);//��������Դ���
extern int MSR_decoder_parity_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype);//������������

extern int MSR_degrade_map_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix,int subtype);//degrade��Ҫ��map������
extern int MSR_degrade_map_chunkblock(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,int subtype);//degrade��Ҫ��map������

extern int MSR_recover_map_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover��Ҫ��map����
extern int MSR_recover_map_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover��Ҫ��map����

extern int MSR_update_encode_chunkblock_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr,int subtype);//����һ�������е�
extern int MSR_update_encode_chunkblock(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,int subtype);//�������е�update����
#endif _MSR