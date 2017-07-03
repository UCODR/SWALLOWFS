#include "test_update_sch_trace.h"

void update_sch_trace_test()
{
	int resTF;
	int i,j,k,r,itemindex,strlen;
	int updatesize,updateKB;
	char *resultpath,*systempath;//resultpath结果数据
	FILE *fin,*fout;
	BYTESTREAM *updatestream;
	BYTE *contentptr;
	long starttick,endtick;//程序使用的数据时隙
	double sectime;
	int offset;
	char *tracepath;//记录trace的轨迹
	int randnum;//生成一个随机数
	TRACEITEM *itemptr;
	FILE *fileptr;
	itemptr=talloc(TRACEITEM,1);
	if(itemptr==NULL)
	{
		show_error("","","");
	}
	resTF=systemcom_system_reset_format();//第一步重新格式化系统
	if(resTF==FALSE)
	{
		show_error("update","update_data_trace_test","system cannot be format");
		//return FALSE;
	}
	updatestream=talloc(BYTESTREAM,1);
	if(updatestream==NULL)
	{
		show_error("","","");
	}
	contentptr=talloc(BYTE,chksize_KB(512));
	if(contentptr==NULL)
	{
		show_error("","","");
	}
	mset(contentptr,BYTE,34,chksize_KB(512));
	updatestream->BYTEcontent=contentptr;
	//profile_global_system_intial_without_datafile();
	profile_global_system_intial();
	systempath=talloc(char,200);
	if(systempath==NULL)
	{
		show_error("","","");
	}
	resultpath=talloc(char,200);
	if(resultpath==NULL)
	{
		show_error("","","");
	}
	updateKB=512;
	fout=fopen(".\\update_sch_test_trace.txt","w");
	if(fout==NULL)
	{
		show_error("AONTRS","AONTRS_test","output file cannot open");
		//return FALSE;
	}
	for(r=0;r<10;r++)//执行10次
	{
		for(i=10;i<35;i++)
		{
			if(r==0)
			{
				sprintf(systempath,"region%d\\update.txt",i);//生成存储路径
				//存储一个文件史记
				resTF=encoder_filestore_API_path(systempath,"D:\\update.txt");
				if(resTF==FALSE)
				{
					show_error("weqwe","","");
				}
			}
			for(j=0;j<7;j++)//还是test cauchy rs之后
			{
				switch(j)
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
				//获取当前trace需要的更行大小
			
				fin=fopen(tracepath,"r");
				if(fin==NULL)
				{
					show_error("update","update_data_trace_test","the trace file cannot be opened");
				}
				//对每一找到轨迹开始位置
				randnum=rand()%1000;
				for(itemindex=0;itemindex<randnum;itemindex++)
				{
					resTF=trace_write_IO(fin,itemptr);
					if(resTF==FALSE)
					{
						show_error("AONTRS","AONTRS_test","the traceitem cannot be read");
						//return FALSE;
					}
				}
				
				
				for(k=1;k<100;k++)
				{

					//fprintf(fout,"region%d\n",j);//
					resTF=trace_write_IO(fin,itemptr);
					if(resTF==FALSE)
					{
						show_error("AONTRS","AONTRS_test","the traceitem cannot be read");
						//return FALSE;
					}
					strlen=itemptr->length;
					while(strlen<chksize_KB(16))
					{
						resTF=trace_write_IO(fin,itemptr);
						if(resTF==FALSE)
						{
							show_error("AONTRS","AONTRS_test","the traceitem cannot be read");
							//return FALSE;
						}
						strlen=itemptr->length;
					}
					while(strlen>chksize_KB(512))
					{
						resTF=trace_write_IO(fin,itemptr);
						if(resTF==FALSE)
						{
							show_error("AONTRS","AONTRS_test","the traceitem cannot be read");
							//return FALSE;
						}
						strlen=itemptr->length;
					}
					updatestream->bytessize=strlen;//根据现实大小进行更行
					randnum=(double)rand();
					randnum=randnum/RAND_MAX;
					if(randnum<=0)
					{
						randnum=(double)rand();
						randnum=randnum/RAND_MAX;
					}
					offset=chksize_MB(1)*randnum;
					starttick=clock();
 					resTF=encoder_filestore_API_update(systempath,updatestream,offset);
					if(resTF==FALSE)
					{
						show_error("","","");
					}
					endtick=clock();
					sectime=profile_calculate_time_diff(starttick,endtick);
					fprintf(fout,"%lf\n",sectime);
					//printf("file updated %d\n",j);
				}
				fprintf(fout,"trace %d\n",j);
				fclose(fin);
			}
			fprintf(fout,"region %d\n",i);
			printf("region %d\n",i);
		}
		
	}
}