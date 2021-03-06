#ifndef _AONTRS
#define _AONTRS

#include "global_define.h"
#include "file.h"
#include "galois.h"
#include "cauchy.h"
extern int AONTRS_RANDKEY(BYTE *content,
							int strlen);//将给定空间设定为随机
extern int AONTRS_HASHKEY(BYTE *key,//输出hash结果
							BYTE *context,//原文
							int strlen
							);//计算值
extern int AONTRS_CHRYPTEXT(BYTE *out,
							BYTE *in,
							int strlen,
							BYTE *key,
							int keylen);//重新定义加密接口
extern int AONTRS_XORKEY(BYTE *out,
						BYTE *in,
						int strlen);//将in异或out存到out
extern int AONTRS_CHRYPTER(BYTE *cipertext,//密文
							BYTE *context,//原文
							int strlen);
extern int AONTRS_RS(AONTSHAREGROUP *sharegroupptr,
					BYTE *cipertext,
					CODEPARA *codeptr,
					int strlen);//生成一组share
extern int AONTRS_STORE(AONTSHAREGROUP *sharegroupptr);//根据当前参数将数据存入

extern int AONTRS_API(BYTE *content,int strlen,ADDRESSLIST *addresslistptr);//给定一个内容给定一个地址集合尝试
#endif