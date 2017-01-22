#ifndef _RAID5
#define _RAID5
#include "galois.h"
#include "matrix.h"
#include "file.h"
extern int RAID5_do_parity(CHUNKBLOCKGROUP *chunkblockgroupptr,CHUNK *parity);//��Ҫ�����ݽ���У�����,����1���ݿ飬����2У���
extern int RAID5_calculate_parity_strip(STRIP *stripptr);//����һ��strip�еı���
extern int RAID5_calculate_parity(STRIPBLOCKGROUP *stripblockgroupptr);//RAID5����������У��

extern int RAID5_decoder_parity_strip(STRIP *stripptr,ERRORPATTERN *errormatrix);//����һ�������е�chunkblock
extern int RAID5_decoder_pairty(STRIPBLOCKGROUP *stripblockgrouoptr,ERRORPATTERN *errormatrix,REGION *regionptr);//����stripblockgroup�е�strip��Դ���

extern int RAID5_decoder_parity_degrade_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix);//��������Դ���
extern int RAID5_decoder_parity_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix);//������������

extern int RAID5_degrade_map_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix);//degrade��Ҫ��map������
extern int RAID5_degrade_map_chunkblock(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix);//degrade��Ҫ��map������

extern int RAID5_recover_map_strip(STRIP *stripptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover��Ҫ��map����
extern int RAID5_recover_map_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//recover��Ҫ��map����

extern int RAID5_update_encode_chunkblock_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);//����һ�������е�
extern int RAID5_update_encode_chunkblock(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr);//�������е�update����
#endif
