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
extern int PCAONTRS_HASHKEY(BYTE *key,//输出hash结果
							BYTE *context,//原文
							int strlen
							);//计算hash值
extern int PCAONTRS_CHRYPTEXT(BYTE *out,
							BYTE *in,
							int startindex,
							int strlen,
							BYTE *key,
							int keylen);//重新定义加密接口
extern int PCAONTRS_XORKEY(BYTE *out,
						BYTE *in,
						int strlen);//将in异或out存到out
extern int PCAONTRS_CHRYPTER(AONTSHAREGROUP *sharegroupptr,//密文组填写前datanum个
							BYTE *context,//原文
							CODEPARA *codeptr,
							int strlen);
extern int PCAONTRS_RS(AONTSHAREGROUP *sharegroupptr);//计算相应的RS值

extern int PCAONTRS_STORE(AONTSHARE *shareptr);//根据当前参数将数据存入

extern int PCAONTRS_API(BYTE *content,int strlen,ADDRESSLIST *addresslistptr);//给定一个内容给定一个地址集合尝试


#endif