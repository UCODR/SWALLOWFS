#ifndef _MDR_H
#define _MDR_H
#include "global_define.h"
#include "matrix.h"
//�����������,����size�ǻ������������������ɰ���P��
extern int MDRI_create_encode_matrix_B(BITMATRIX *matrix);//����wΪ������ȣ�k����������+p��
extern int MDRII_create_encode_matrix_B(BITMATRIX *matrix);//����wΪ������ȣ�k����������+p�̡�


extern int MDRI_create_encode_matrix(BITMATRIX *matrix);//����w����w������ȣ�kΪ������
extern int MDRII_create_encode_matrix(BITMATRIX *matrix);//����w����w������ȣ�kΪ������
//�ӿ�
extern int MDRI_API(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr);
extern int MDRII_API(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr);

extern int MDRI_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix);
extern int MDRII_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix);

extern int MDRI_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);
extern int MDRII_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);

static UINT32 MDRIB1matrix[4]={0,1,
								0,0};	
static UINT32 MDRIB2matrix[4]={0,0,
								1,0};
static UINT32 MDRIIB1matrix[16]={1,0,0,1,  
								0,1,1,0,  
								0,0,1,0,   
								0,0,0,1};   
static UINT32 MDRIIB2matrix[16]={1,0,0,0,
								 0,1,0,0,
								 0,1,1,0,
								 1,0,0,1};
static UINT32 MDRIIB3matrix[16]={0,1,0,0,
								 0,0,0,0,
								 0,0,0,0,
								 0,0,1,0};
static UINT32 MDRIIB4matrix[64]={0,0,0,0,
								 1,0,0,0,
								 0,0,0,1,
								 0,0,0,0};
#endif