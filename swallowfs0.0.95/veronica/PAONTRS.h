#ifndef _PAONTRS
#define _PAONTRS
#include "file.h"
#include "galois.h"
#include "cauchy.h"
#include "AONTRS.h"
#include "matrix.h"
//由于需要全局同步因此需要信号量
sem_t PAONT_empty,PAONT_full;//两个信号量
AONTSHARE memshareptr;
//一开始没想明白，pipline本质是生产者消费者问题
extern int PAONTRS_RANDKEY(BYTE *content,
							int strlen);//将给定空间设定为随机
extern int PAONTRS_HASHKEY(BYTE *key,//输出hash结果
							BYTE *context,//原文
							int strlen
							);//计算hash值
extern int PAONTRS_CHRYPTEXT(BYTE *out,
							BYTE *in,
							int startindex,
							int strlen,
							BYTE *key,
							int keylen);//重新定义加密接口
extern int PAONTRS_XORKEY(BYTE *out,
						BYTE *in,
						int strlen);//将in异或out存到out
extern int PAONTRS_CHRYPTER(AONTSHAREGROUP *sharegroupptr,//密文组填写前datanum个
							BYTE *context,//原文
							CODEPARA *codeptr,
							int strlen);
extern int PAONTRS_RS(AONTSHAREGROUP *sharegroupptr);//根据前面
//这里是和AONT最大不同点，需要多线程来一个存一个
extern void* PAONTRS_STORE_thread(void* arg);

extern int PAONTRS_STORE(AONTSHARE *shareptr);//根据当前参数将数据存入

extern int PAONTRS_API(BYTE *content,int strlen,ADDRESSLIST *addresslistptr);//给定一个内容给定一个地址集合尝试

#endif