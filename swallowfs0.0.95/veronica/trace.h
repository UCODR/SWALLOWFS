#ifndef _trace_h
#define _trace_h
//����켣��ʽ
//IO���켣�ӿ�
//��һλʹ��w��r������
#include "global_define.h"
extern int trace_read_IO(FILE *fileptr,TRACEITEM *itemptr);//��ȡ�켣����read�Ĳ��ֶ�ȡһ���ָ��ָ����һ��
extern int trace_write_IO(FILE *fileptr,TRACEITEM *itemptr);//��ȡ�켣�е�һ��
extern int trace_readwrite_IO(FILE *fileptr,TRACEITEM *itemptr);
#endif