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
	UINT64 offset;
	int length;
	char opertype='r';//��Ĭ��ֵ��Ϊ��
	itemptr->opertype=FILEWRITE;
	/*opertype=talloc(char,4);//����ռ�
	if(opertype==NULL)
	{
		show_error("trace","trace_write_IO","No memory");
		return TRUE;
	}*/
	
	//while(strcmp(opertype,"w")!=0)//�˵����в���w����Ŀ
	while(opertype!='w')
	{
		fscanf(fileptr,"%c,%l64d,%d",&opertype,&offset,&length);
	}
	 //��д����
	itemptr->offset=offset;
	itemptr->length=length;
	return TRUE;
}
