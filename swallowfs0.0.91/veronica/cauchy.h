  /*
This program is created by Jiajie Shen 
2015.1.18
��ѽܴ���2014.1.18
*/
//����PLank����
#ifndef _CAUCHY_H
#define _CAUCHY_H
//ʵ�ֻ�������Cauchy����
#include "galois.h"
#include "global_define.h"
#include "matrix.h"
#include "update_API.h"
//������������
static int PPs[33] = { -1, -1, -1, -1, -1, -1, -1, -1,
                       -1, -1, -1, -1, -1, -1, -1, -1,
                       -1, -1, -1, -1, -1, -1, -1, -1,
                       -1, -1, -1, -1, -1, -1, -1, -1, -1 };
static int NOs[33];
static int ONEs[33][33];

static int *cbest_0;
static int *cbest_1;
static int cbest_2[3];
static int cbest_3[7];
static int cbest_4[15];
static int cbest_5[31];
static int cbest_6[63];
static int cbest_7[127];
static int cbest_8[255];
static int cbest_9[511];
static int cbest_10[1023];
static int cbest_11[1023];
static int *cbest_12, *cbest_13, *cbest_14, *cbest_15, *cbest_16, *cbest_17, *cbest_18, *cbest_19, *cbest_20,
           *cbest_21, *cbest_22, *cbest_23, *cbest_24, *cbest_25, *cbest_26, *cbest_27, *cbest_28, *cbest_29, *cbest_30,
           *cbest_31, *cbest_32;
static int cbest_max_k[33] = { -1, -1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 1023, -1,
     -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
     -1, -1, -1, -1 };

static int cbest_init = FALSE;//��δ��ʼ��

static int *cbest_all[33];
//���ɾ��󲿷�
extern int cauchy_inital();//���ڳ�ʼ��ϵͳ
extern int cauchy_orgininal_coding_matrix(INTMATRIX *matrix);//���ɳ�ʼ�Ŀ�������
extern int cauchy_orgininal_coding_bitmatrix(BITMATRIX *matrix);//������Ӧ��bitmatrix

extern int cauchy_xy_coding_matrix(INTMATRIX *matrix, INTARRAY *arrx,INTARRAY *arry);//���ݸ���x,y����
extern int cauchy_improve_coding_matrix(INTMATRIX *matrix);//�Ľ�cauchy����
extern int cauchy_good_general_coding_matrix(INTMATRIX *matrix);//����Plank��Cauchy����
extern int cauchy_good_general_coding_bitmatrix(BITMATRIX *matrix);//������Ӧ��bitmatrix
//ͳһ�ӿ�
extern int cauchy_API_RAID6(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr);//RAID6�ӿ�
extern int cauchy_API(STRIP *stripptr);//cauchy RS�ӿ�

extern int cauchy_degrade_API_RAID6(CHUNK *chunkptr,ERRORPATTERN *errormatrix);
extern int cauchy_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix);

extern int cauchy_update_API_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);
extern int cauchy_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);

extern int cauchy_decoder_API_strip(STRIP *stripptr,ERRORPATTERN *errormatrix);//����RS����ӿ�
extern int cauchy_decoder_API_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix);//����RS����ӿ�

//��������С�ӿ�
extern int cauchy_API_Context(AONTSHAREGROUP *sharegroup,CODEPARA *codeptr,BYTE *context,int strlen);//�������ݺͱ���������ļ��ֳ���Ӧ��shares
extern int cauchy_API_Sharegroup(AONTSHAREGROUP *sharegroupptr,CODEPARA *codeptr,BITMATRIX *matrixptr);//���ݾ��������󼸸�share

#endif