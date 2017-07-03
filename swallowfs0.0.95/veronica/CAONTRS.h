#ifndef _CAONTRS
#define _CAONTRS

#include "global_define.h"
#include "file.h"
#include "galois.h"
#include "cauchy.h"
#include "AONTRS.h"
extern int CAONTRS_HASHKEY(BYTE *key,//���hash���
							BYTE *context,//ԭ��
							int strlen
							);//����ֵ
extern int CAONTRS_CHRYPTEXT(BYTE *out,
							BYTE *in,
							int strlen,
							BYTE *key,
							int keylen);//���¶�����ܽӿ�
extern int CAONTRS_XORKEY(BYTE *out,
						BYTE *in,
						int strlen);//��in���out�浽out
extern int CAONTRS_CHRYPTER(BYTE *cipertext,//����
							BYTE *context,//ԭ��
							int strlen);
extern int CAONTRS_RS(AONTSHAREGROUP *sharegroupptr,
					BYTE *cipertext,
					CODEPARA *codeptr,
					int strlen);//����һ��share
extern int CAONTRS_STORE(AONTSHAREGROUP *sharegroupptr);//���ݵ�ǰ���������ݴ���

extern int CAONTRS_API(BYTE *content,int strlen,ADDRESSLIST *addresslistptr);//����һ�����ݸ���һ����ַ���ϳ���



#endif