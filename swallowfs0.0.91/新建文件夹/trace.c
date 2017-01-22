#include "trace.h"
//主要的目的是从文件中读取轨迹结构体数据
//实验中没有用到
int trace_read_IO(FILE *fileptr,TRACEITEM *itemptr)
{
	itemptr->opertype=FILEREAD;

	return TRUE;
}
//主要是write轨迹
int trace_write_IO(FILE *fileptr,TRACEITEM *itemptr)
{
	int offset,length;
	char *opertype;
	itemptr->opertype=FILEWRITE;
	opertype=talloc(char,4);//给点空间
	if(opertype==NULL)
	{
		show_error("","","");
		return TRUE;
	}
	
	while(strcmp(opertype,"w")!=0)//滤掉所有不是w的条目
	{
		fscanf(fileptr,"%s %d %d",opertype,&offset,&length);
	}
	 //填写数据
	itemptr->offset=offset;
	itemptr->length=length;
	return TRUE;
}
