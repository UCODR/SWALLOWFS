#ifndef _STAR
#define _STAR

#include "global_define.h"
#include "galois.h"
#include "matrix.h"
#include "profile.h"
#include "EVENODD.h"
#include "update_API.h"
extern int STAR_add_second_grandmother(BITMATRIX *matrix);//���ڶ�����ĸ��ӵ�������������
extern int STAR_calculate_third_parity_matrix(BITMATRIX *matrix);//����matrix��Ӧ�ĵ�����У���
extern int STAR_create_encode_matrix(BITMATRIX *matrix);//������Ӧ��STAR�������

extern int STAR_API(STRIP *stripptr);//����һ�������е�У���
extern int STAR_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix);//������

extern int STAR_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);//ʵ�ָ���
#endif
