#ifndef _HAMMING
#define _HAMMING
#include "galois.h"
#include "matrix.h"
extern int HAMMING_calculate_parity_strip(STRIP *stripptr);//����һ��strip�еı���
extern int HAMMING_calculate_parity(STRIPBLOCKGROUP *stripblockgroupptr);//Hamming����������У��

extern int HAMMING_decoder_parity_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,REGION *regionptr);//����һ�������е�chunkblock
extern int HAMMING_decoder_parity(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//����stripblockgroup�е�strip��Դ���

extern int HAMMING_decoder_parity_degrade_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix);//��������
extern int HAMMING_decoder_parity_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix);//����chunkblockgroup������

extern int HAMMING_degrade_map_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix);//degrade��Ҫ��map������
extern int HAMMING_degrade_map_chunkblock(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix);//degrade��Ҫ��map������

extern int HAMMING_recover_map_strip(STRIP *stripptr,ERRORPATTERN *errormatrix);//recover��Ҫ��map����
extern int HAMMING_recover_map_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover��Ҫ��map����

extern int HAMMING_update_encode_chunkblock_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);//����һ�������ڵ�����
extern int HAMMING_update_encode_chunkblock(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr);//�������е�update����
#endif
