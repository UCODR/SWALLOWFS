#ifndef _REED_SOL_CLASSIC
#define _REED_SOL_CLASSIC
#include "galois.h"
#include "global_define.h"
#include "matrix.h"
//Vandermonder����
extern int reed_sol_r6_matrix(INTMATRIX *matrix);//��Ҫ����������RAID-6��vandermonder��
extern int reed_sol_vandermonde_coding_matrix(INTMATRIX *matrix);//��Ҫ��������������vandermonder����
extern int reed_sol_big_vandermonde_distribution_matrix(INTMATRIX *matrix);//����vandermonder�ֲ�����
extern int reed_sol_extended_vandermonde_matrix(INTMATRIX *matrix);//���ݾ����������ɷ���������ʽ

//��raid6�����RS�������ɱ������
extern int reed_sol_r6_encode_w(CHUNKBLOCKGROUP *datachk,CHUNK *pchunkptr,CHUNK *qchunkptr,int w);//��Ӧ��Ӧ��r6ϵͳ���б���
extern int reed_sol_r6_encode(CHUNKBLOCKGROUP *datachk,CHUNK *pchunkptr,CHUNK *qchunkptr,ENDECODEPARA *para);//��Ӧ��Ӧ��r6ϵͳ���б��벢�ҽ�r6���󱣴���para��

extern int reed_sol_r6_decode_w(CHUNKBLOCKGROUP *datachk,CHUNK *pchunkptr,CHUNK *qchunkptr,int w,ERASES *erarray);//��Ӧ��Ӧ��r6ϵͳ���б���
extern int reed_sol_r6_decode(CHUNKBLOCKGROUP *datachk,CHUNK *pchunkptr,CHUNK *qchunkptr,ENDECODEPARA *para,ERASES *erarray);//������Ӧ��r6���н��벢�ҽ�������󱣴���para��

extern int reed_sol_van_encode_w(CHUNKBLOCKGROUP *datachk,CHUNKBLOCKGROUP *parachk,ENDECODEPARA *para);//����datachk��parachk�Ĵ�С���б���
extern int reed_sol_van_encode(CHUNKBLOCKGROUP *datachk,CHUNKBLOCKGROUP *parachk,ENDECODEPARA *para);//����datachk��parachk�Ĵ�С���б��벢�ҽ�������󱣴���para��

extern int reed_sol_van_decode_w(CHUNKBLOCKGROUP *datachk,CHUNKBLOCKGROUP *parachk,int w,ERASES *erarray);//������Ӧ��van���н���
extern int reed_sol_van_decode(CHUNKBLOCKGROUP *datachk,CHUNKBLOCKGROUP *parachk,ENDECODEPARA *para,ERASES *erarray);//������Ӧ��van���н��벢�ҽ�������󱣴���para��

extern int reed_sol_API_RAID6(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr);//classic RS����raid6�ӿ�
extern int reed_sol_API(STRIP *stripptr);//����RS����ӿ�


extern int reed_sol_degrade_API_RAID6(CHUNK *chunkptr,ERRORPATTERN *errormatrix);
extern int reed_sol_degrade_API(CHUNK *chunkptr,ERRORPATTERN *errormatrix);

extern int reed_sol_update_API_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);//RAID6��update����
extern int reed_sol_update_API(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,STRIP *stripptr);//update����

extern int reed_sol_decoder_API_strip(STRIP *stripptr,ERRORPATTERN *errormatrix);//����RS����ӿ�
extern int reed_sol_decoder_API_chunk(CHUNK *chunkptr,ERRORPATTERN *errormatrix);//����RS����ӿ�
#endif