#ifndef _AONTRS
#define _AONTRS

#include "global_define.h"
#include "file.h"
#include "galois.h"
#include "cauchy.h"
extern int AONTRS_RANDKEY(BYTE *content,
							int strlen);//�������ռ��趨Ϊ���
extern int AONTRS_HASHKEY(BYTE *key,//���hash���
							BYTE *context,//ԭ��
							int strlen
							);//����ֵ
extern int AONTRS_CHRYPTEXT(BYTE *out,
							BYTE *in,
							int strlen,
							BYTE *key,
							int keylen);//���¶�����ܽӿ�
extern int AONTRS_XORKEY(BYTE *out,
						BYTE *in,
						int strlen);//��in���out�浽out
extern int AONTRS_CHRYPTER(BYTE *cipertext,//����
							BYTE *context,//ԭ��
							int strlen);
extern int AONTRS_RS(AONTSHAREGROUP *sharegroupptr,
					BYTE *cipertext,
					CODEPARA *codeptr,
					int strlen);//����һ��share
extern int AONTRS_STORE(AONTSHAREGROUP *sharegroupptr);//���ݵ�ǰ���������ݴ���

extern int AONTRS_API(BYTE *content,int strlen,ADDRESSLIST *addresslistptr);//����һ�����ݸ���һ����ַ���ϳ���
#endif