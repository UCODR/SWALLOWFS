#ifndef _PAONTRS
#define _PAONTRS
#include "file.h"
#include "galois.h"
#include "cauchy.h"
#include "AONTRS.h"
#include "matrix.h"
//������Ҫȫ��ͬ�������Ҫ�ź���
sem_t PAONT_empty,PAONT_full;//�����ź���
AONTSHARE memshareptr;
//һ��ʼû�����ף�pipline����������������������
extern int PAONTRS_RANDKEY(BYTE *content,
							int strlen);//�������ռ��趨Ϊ���
extern int PAONTRS_HASHKEY(BYTE *key,//���hash���
							BYTE *context,//ԭ��
							int strlen
							);//����hashֵ
extern int PAONTRS_CHRYPTEXT(BYTE *out,
							BYTE *in,
							int startindex,
							int strlen,
							BYTE *key,
							int keylen);//���¶�����ܽӿ�
extern int PAONTRS_XORKEY(BYTE *out,
						BYTE *in,
						int strlen);//��in���out�浽out
extern int PAONTRS_CHRYPTER(AONTSHAREGROUP *sharegroupptr,//��������дǰdatanum��
							BYTE *context,//ԭ��
							CODEPARA *codeptr,
							int strlen);
extern int PAONTRS_RS(AONTSHAREGROUP *sharegroupptr);//����ǰ��
//�����Ǻ�AONT���ͬ�㣬��Ҫ���߳���һ����һ��
extern void* PAONTRS_STORE_thread(void* arg);

extern int PAONTRS_STORE(AONTSHARE *shareptr);//���ݵ�ǰ���������ݴ���

extern int PAONTRS_API(BYTE *content,int strlen,ADDRESSLIST *addresslistptr);//����һ�����ݸ���һ����ַ���ϳ���

#endif