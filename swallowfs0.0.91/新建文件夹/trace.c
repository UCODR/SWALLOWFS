#include "trace.h"
//��Ҫ��Ŀ���Ǵ��ļ��ж�ȡ�켣�ṹ������
//ʵ����û���õ�
int trace_read_IO(FILE *fileptr,TRACEITEM *itemptr)
{
	itemptr->opertype=FILEREAD;

	return TRUE;
}
//��Ҫ��write�켣
int trace_write_IO(FILE *fileptr,TRACEITEM *itemptr)
{
	int offset,length;
	char *opertype;
	itemptr->opertype=FILEWRITE;
	opertype=talloc(char,4);//����ռ�
	if(opertype==NULL)
	{
		show_error("","","");
		return TRUE;
	}
	
	while(strcmp(opertype,"w")!=0)//�˵����в���w����Ŀ
	{
		fscanf(fileptr,"%s %d %d",opertype,&offset,&length);
	}
	 //��д����
	itemptr->offset=offset;
	itemptr->length=length;
	return TRUE;
}
