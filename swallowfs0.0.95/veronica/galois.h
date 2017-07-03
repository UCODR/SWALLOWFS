/*
This program is created by Jiajie Shen 
2014.11.23
沈佳杰创建2014.11.24
*/
#ifndef _GALOIS_H
#define _GALOIS_H
#include "global_define.h"
void galois_region_xor(           char *r1,         /* Region 1 */
                                  char *r2,         /* Region 2 */
                                  char *target,         /* Sum region (r3 = r1 ^ r2) -- can be r1 or r2 两者*/
                                  UINT32 nbytes);       /* Number of bytes in region 多少个字节进行异或*/
extern UINT32 galois_region_subtract(BYTE *des,BYTE *sou,UINT32 nbytes);//计算两者相减
extern UINT32 galois_region_add(BYTE *des,BYTE *sou,UINT32 nbytes);//两者相加

extern void galois_log_intial();//logtable初始化
extern UINT32 galois_logtable_create(UINT32 w);//生成在w下的log和ilog表
extern UINT32* galois_ilog_table(UINT32 w);//获取w的ilogtable
extern UINT32* galois_log_table(UINT32 w);//获取w的logtable
extern UINT32 galois_log_multiply(UINT32 x,UINT32 y,UINT32 w);//实现logtable乘法
extern UINT32 galois_log_divide(UINT32 x,UINT32 y,UINT32 w);//实现logtable除法

extern void galois_multtable_intial();//初始化，创建乘法表
extern UINT32 galois_multtable_create(UINT32 w);//创建w乘法表
extern UINT32 galois_multtable_multiply(UINT32 x,UINT32 y,UINT32 w);//使用multibale进行乘法
extern UINT32 galois_multtable_divide(UINT32 x,UINT32 y,UINT32 w);//使用multibale进行除法
extern UINT32** galois_mult_table(UINT32 w);//获取乘法表
extern UINT32** galois_div_table(UINT32 w);//获取除法表

extern void galois_shift_intial();//正常移动计算无需初始化
extern void galois_inv_binary_matrix(UINT32 *mat,UINT32 *inv,UINT32 rows);//这里还是用Mr. plank的算法求矩阵的逆
extern UINT32 galois_shift_inverse(UINT32 y,UINT32 w);//求在w下y的逆元
extern UINT32 galois_shift_divide(UINT32 x,UINT32 y,UINT32 w);//shift除法

extern void galois_split_intial();//初始化split算法
extern UINT32 galois_create_split_w8_table();//创建7张split表
extern UINT32 galois_split_w8_multiply(UINT32 x,UINT32 y);//split乘法
extern UINT32 galois_split_w8_divide(UINT32 x,UINT32 y);//split除法直接调用shift除法
extern UINT32 galois_inverse(UINT32 y,UINT32 w);//逆元生成


extern UINT32 galois_single_multiply(UINT32 x,UINT32 y,UINT32 w);//整体乘法接口
extern UINT32 galois_single_divide(UINT32 x,UINT32 y,UINT32 w);//整体除法接口

extern void galois_w08_region_multiply(char *region,//需要进行乘法的区域
								int multby,//乘数
								int nbytes,//需要进行乘法的比特数
								char *target,//目标区域.
								int XORTF//目标区域是不是要异或，如果target有内容并且为TRUE则与原内容XOR，否则overwrite
								//条件为(target!=NULL)&&(XORTF=TRUE)异或
								);//完成一个区域w8的galois乘法
extern void galois_w16_region_multiply(char *region,//需要进行乘法的区域
								int multby,//乘数
								int nbytes,//需要进行乘法的比特数
								char *target,//目标区域
								int XORTF//目标区域是不是要异或，如果target有内容并且为TRUE则与原内容XOR，否则overwrite
								//条件为(target!=NULL)&&(XORTF=TRUE)异或
								);//完成一个区域w8的galois乘法
extern void galois_w32_region_multiply(char *region,//需要进行乘法的区域
								int multby,//乘数
								int nbytes,//需要进行乘法的比特数
								char *target,//目标区域
								int XORTF//目标区域是不是要异或，如果target有内容并且为TRUE则与原内容XOR，否则overwrite
								//条件为(target!=NULL)&&(XORTF=TRUE)异或
								);//完成一个区域w8的galois乘法
#endif


