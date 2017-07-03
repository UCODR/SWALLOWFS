#ifndef _GENRDP
#define _GENRDP
#include "global_define.h"
#include "galois.h"
#include "matrix.h"
#include "profile.h"
extern int GENRDP_P_disk_add(BITMATRIX *matrix,int tarindex,int souindex);//��p���е�һ�мӵ�Ŀ����

extern int GENRDP_create_encode_matrix(BITMATRIX *matrix);//������Ӧ��GENRDP�������

extern int GENRDP_API(STRIP *stripptr);//����һ�������е�У���
extern int GENRDP_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix);//������

extern int EVENODD_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);//ʵ�ָ���
#endif