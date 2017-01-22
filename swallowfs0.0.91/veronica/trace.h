#ifndef _trace_h
#define _trace_h
//输入轨迹格式
//IO级轨迹接口
//第一位使用w和r来定义
#include "global_define.h"
extern int trace_read_IO(FILE *fileptr,TRACEITEM *itemptr);//提取轨迹中是read的部分读取一项并将指针指向下一个
extern int trace_write_IO(FILE *fileptr,TRACEITEM *itemptr);//提取轨迹中的一项
extern int trace_readwrite_IO(FILE *fileptr,TRACEITEM *itemptr);
#endif