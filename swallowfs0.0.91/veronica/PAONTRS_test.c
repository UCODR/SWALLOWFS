#include "PAONTRS_test.h"
int PAONTRS_test_set_address(SHAREADDRESS *addptr,int n)
{
	SHAREADDRESS *curaddptr;
	curaddptr=addptr;
	switch(n)
	{
	case 4:
		mcpy(curaddptr->storepath,"S:\\s1.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"T:\\s2.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"U:\\s3.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"V:\\s4.txt",char,10);
		curaddptr++;
		break;
	case 5:
		mcpy(curaddptr->storepath,"S:\\s1.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"T:\\s2.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"U:\\s3.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"V:\\s4.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"W:\\s5.txt",char,10);
		curaddptr++;
		break;
	case 6:
		mcpy(curaddptr->storepath,"S:\\s1.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"T:\\s2.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"U:\\s3.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"V:\\s4.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"W:\\s5.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"X:\\s6.txt",char,10);
		curaddptr++;
		break;
	case 7:
		mcpy(curaddptr->storepath,"S:\\s1.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"T:\\s2.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"U:\\s3.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"V:\\s4.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"W:\\s5.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"X:\\s6.txt",char,10);
		curaddptr++;
		mcpy(curaddptr->storepath,"Y:\\s7.txt",char,10);
		curaddptr++;
		break;
	}
	return TRUE;
}

int PAONTRS_test()
{
	int i,k,n,r,itemindex,randnum,strlen,resTF;
	char *tracepath;//记录一下轨迹的路径
	FILE *fin,*fout;//用于输入trace，输出结果
	CODEPARA *codeptr;
	BYTE *content;//需要加密的内容
	ADDRESSLIST *addlistptr;
	SHAREADDRESS *addptr,*curaddptr;
	TRACEITEM *itemptr;
	int starttick,endtick;
	double sectime;

	content=talloc(BYTE,chksize_MB(100));//开100MB空间希望不会有比他大的
	if(content==NULL)
	{
		show_error("PAONTRS","PAONTRS_test","No memory");
		return FALSE;
	}
	codeptr=talloc(CODEPARA,1);
	if(codeptr==NULL)
	{
		show_error("PAONTRS","PAONTRS_test","No memory");
		return FALSE;
	}
	addptr=talloc(SHAREADDRESS,7);
	curaddptr=addptr;
	for(i=0;i<7;i++)
	{
		curaddptr->storepath=talloc(char,10);
		if(curaddptr->storepath==NULL)
		{
			show_error("PAONTRS","PAONTRS_test","No memory");
			return FALSE;
		}
		curaddptr++;
	}
	addlistptr=talloc(ADDRESSLIST,1);
	if(addlistptr==NULL)
	{
		show_error("PAONTRS","PAONTRS_test","No memory");
		return FALSE;
	}
	itemptr=talloc(TRACEITEM,1);
	if(itemptr==NULL)
	{
		show_error("PAONTRS","PAONTRS_test","No memory");
		return FALSE;
	}
	addlistptr->addressptr=addptr;
	addlistptr->codeptr=codeptr;
	memset(content,1,chksize_MB(100));
	k=4;
	fout=fopen(".\\PAONT-RS.txt","w");
	if(fout==NULL)
	{
		show_error("PAONTRS","PAONTRS_test","output file cannot open");
		return FALSE;
	}
	for(r=0;r<100;r++)
	{
		for(i=0;i<7;i++)
		{
			switch(i)
			{
			case 0://轨迹放在本地
				tracepath=".\\usr.txt";
				//linenum=
				//strlen=chksize_KB(64);
				break;
			case 1:
				tracepath=".\\web.txt";
				//strlen=chksize_KB(128);
				break;
			case 2:
				tracepath=".\\proj.txt";
				//strlen=chksize_KB(256);
				break;
			case 3:
				tracepath=".\\ts.txt";
				//strlen=chksize_KB(512);
				break;
			case 4:
				tracepath=".\\rsrch.txt";
				//strlen=chksize_MB(1);
				break;
			case 5:
				tracepath=".\\mds.txt";
				break;
			case 6:
				tracepath=".\\hm.txt";
				break;
			}
			fin=fopen(tracepath,"r");
			if(fin==NULL)
			{
				show_error("PAONTRS","PAONTRS_test","trace cannot open");
				return FALSE;
			}
			
			k=4;
			for(n=4;n<7;n++)
			{
				//填写所有参数
				codeptr->totnum=n;
				codeptr->datanum=k;
				codeptr->codenum=n-k;
				codeptr->w=8;
				PAONTRS_test_set_address(addptr,n);
				//while(!feof(fin))太多了
				randnum=rand()%1000;
				for(itemindex=0;itemindex<randnum;itemindex++)
				{
					resTF=trace_write_IO(fin,itemptr);
					if(resTF==FALSE)
					{
						show_error("PAONTRS","PAONTRS_test","the traceitem cannot be read");
						return FALSE;
					}
				}
				for(itemindex=0;itemindex<100;itemindex++)
				{
					
					starttick=clock();
					resTF=trace_write_IO(fin,itemptr);
					if(resTF==FALSE)
					{
						show_error("PAONTRS","PAONTRS_test","the traceitem cannot be read");
						return FALSE;
					}
					strlen=itemptr->length;
					PAONTRS_API(content,strlen,addlistptr);
					endtick=clock();
					sectime=profile_calculate_time_diff(starttick,endtick);
					fprintf(fout,"%f\n",sectime);
				}
				fprintf(fout,"(%d,%d),%d,%d\n",n,k,i,r);
				printf("(%d,%d),%d,%d\n",n,k,i,r);
			}
			n=7;
			for(k=4;k<=7;k++)
			{
				//填写所有参数
				codeptr->totnum=n;
				codeptr->datanum=k;
				codeptr->codenum=n-k;
				codeptr->w=8;
				AONTRS_test_set_address(addptr,n);
				randnum=rand()%1000;
				for(itemindex=0;itemindex<randnum;itemindex++)
				{
					resTF=trace_write_IO(fin,itemptr);
					if(resTF==FALSE)
					{
						show_error("PAONTRS","PAONTRS_test","the traceitem cannot be read");
						return FALSE;
					}
				}
				//while(!feof(fin))
				for(itemindex=0;itemindex<100;itemindex++)
				{
					starttick=clock();
					resTF=trace_write_IO(fin,itemptr);
					if(resTF==FALSE)
					{
						show_error("PAONTRS","PAONTRS_test","the traceitem cannot be read");
						return FALSE;
					}
					strlen=itemptr->length;
					PAONTRS_API(content,strlen,addlistptr);
					endtick=clock();
					sectime=profile_calculate_time_diff(starttick,endtick);
					fprintf(fout,"%f\n",sectime);
				}
				fprintf(fout,"(%d,%d),%d,%d\n",n,k,i,r);
				printf("(%d,%d),%d,%d\n",n,k,i,r);
			}
			fclose(fin);
		}
		printf("round %d",r);
	}
	fclose(fout);
	return TRUE;
}