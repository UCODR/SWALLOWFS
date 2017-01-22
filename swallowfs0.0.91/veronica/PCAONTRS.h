#ifndef _PCAONTRS
#define _PCAONTRS
#include "file.h"
#include "galois.h"
#include "cauchy.h"
#include "AONTRS.h"
#include "PAONTRS.h"

//AONTSHARE Pmemshareptr;
//sem_t PCAONT_empty,PCAONT_full;
extern int PCAONTRS_RANDKEY(BYTE *content,
							int strlen);
extern int PCAONTRS_HASHKEY(BYTE *key,//���hash���
							BYTE *context,//ԭ��
							int strlen
							);//����hashֵ
extern int PCAONTRS_CHRYPTEXT(BYTE *out,
							BYTE *in,
							int startindex,
							int strlen,
							BYTE *key,
							int keylen);//���¶�����ܽӿ�
extern int PCAONTRS_XORKEY(BYTE *out,
						BYTE *in,
						int strlen);//��in���out�浽out
extern int PCAONTRS_CHRYPTER(AONTSHAREGROUP *sharegroupptr,//��������дǰdatanum��
							BYTE *context,//ԭ��
							CODEPARA *codeptr,
							int strlen);
extern int PCAONTRS_RS(AONTSHAREGROUP *sharegroupptr);//������Ӧ��RSֵ

extern int PCAONTRS_STORE(AONTSHARE *shareptr);//���ݵ�ǰ���������ݴ���

extern int PCAONTRS_API(BYTE *content,int strlen,ADDRESSLIST *addresslistptr);//����һ�����ݸ���һ����ַ���ϳ���


#endif