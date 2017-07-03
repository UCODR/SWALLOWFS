/*
This program is created by Jiajie Shen 
2014.11.23
��ѽܴ���2014.11.24
*/
#ifndef _GALOIS_H
#define _GALOIS_H
#include "global_define.h"
void galois_region_xor(           char *r1,         /* Region 1 */
                                  char *r2,         /* Region 2 */
                                  char *target,         /* Sum region (r3 = r1 ^ r2) -- can be r1 or r2 ����*/
                                  UINT32 nbytes);       /* Number of bytes in region ���ٸ��ֽڽ������*/
extern UINT32 galois_region_subtract(BYTE *des,BYTE *sou,UINT32 nbytes);//�����������
extern UINT32 galois_region_add(BYTE *des,BYTE *sou,UINT32 nbytes);//�������

extern void galois_log_intial();//logtable��ʼ��
extern UINT32 galois_logtable_create(UINT32 w);//������w�µ�log��ilog��
extern UINT32* galois_ilog_table(UINT32 w);//��ȡw��ilogtable
extern UINT32* galois_log_table(UINT32 w);//��ȡw��logtable
extern UINT32 galois_log_multiply(UINT32 x,UINT32 y,UINT32 w);//ʵ��logtable�˷�
extern UINT32 galois_log_divide(UINT32 x,UINT32 y,UINT32 w);//ʵ��logtable����

extern void galois_multtable_intial();//��ʼ���������˷���
extern UINT32 galois_multtable_create(UINT32 w);//����w�˷���
extern UINT32 galois_multtable_multiply(UINT32 x,UINT32 y,UINT32 w);//ʹ��multibale���г˷�
extern UINT32 galois_multtable_divide(UINT32 x,UINT32 y,UINT32 w);//ʹ��multibale���г���
extern UINT32** galois_mult_table(UINT32 w);//��ȡ�˷���
extern UINT32** galois_div_table(UINT32 w);//��ȡ������

extern void galois_shift_intial();//�����ƶ����������ʼ��
extern void galois_inv_binary_matrix(UINT32 *mat,UINT32 *inv,UINT32 rows);//���ﻹ����Mr. plank���㷨��������
extern UINT32 galois_shift_inverse(UINT32 y,UINT32 w);//����w��y����Ԫ
extern UINT32 galois_shift_divide(UINT32 x,UINT32 y,UINT32 w);//shift����

extern void galois_split_intial();//��ʼ��split�㷨
extern UINT32 galois_create_split_w8_table();//����7��split��
extern UINT32 galois_split_w8_multiply(UINT32 x,UINT32 y);//split�˷�
extern UINT32 galois_split_w8_divide(UINT32 x,UINT32 y);//split����ֱ�ӵ���shift����
extern UINT32 galois_inverse(UINT32 y,UINT32 w);//��Ԫ����


extern UINT32 galois_single_multiply(UINT32 x,UINT32 y,UINT32 w);//����˷��ӿ�
extern UINT32 galois_single_divide(UINT32 x,UINT32 y,UINT32 w);//��������ӿ�

extern void galois_w08_region_multiply(char *region,//��Ҫ���г˷�������
								int multby,//����
								int nbytes,//��Ҫ���г˷��ı�����
								char *target,//Ŀ������.
								int XORTF//Ŀ�������ǲ���Ҫ������target�����ݲ���ΪTRUE����ԭ����XOR������overwrite
								//����Ϊ(target!=NULL)&&(XORTF=TRUE)���
								);//���һ������w8��galois�˷�
extern void galois_w16_region_multiply(char *region,//��Ҫ���г˷�������
								int multby,//����
								int nbytes,//��Ҫ���г˷��ı�����
								char *target,//Ŀ������
								int XORTF//Ŀ�������ǲ���Ҫ������target�����ݲ���ΪTRUE����ԭ����XOR������overwrite
								//����Ϊ(target!=NULL)&&(XORTF=TRUE)���
								);//���һ������w8��galois�˷�
extern void galois_w32_region_multiply(char *region,//��Ҫ���г˷�������
								int multby,//����
								int nbytes,//��Ҫ���г˷��ı�����
								char *target,//Ŀ������
								int XORTF//Ŀ�������ǲ���Ҫ������target�����ݲ���ΪTRUE����ԭ����XOR������overwrite
								//����Ϊ(target!=NULL)&&(XORTF=TRUE)���
								);//���һ������w8��galois�˷�
#endif


