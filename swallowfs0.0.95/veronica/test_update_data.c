#include "test_update_data.h"

void update_data_update_test()
{
	int resTF;
	int i,j,k;
	double randnum;
	int updatesize,updateKB;
	FILE *fileptr;
	char *resultpath,*systempath;//resultpath�������
	BYTESTREAM *updatestream;
	BYTE *contentptr;
	long starttick,endtick;//����ʹ�õ�����ʱ϶
	double sectime;
	int offset;
	systemcom_system_reset_format();
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
	//profile_global_system_intial();
	profile_global_system_intial_without_datafile();
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
	updateKB=32;
	for(i=0;i<5;i++)//������ǰ�ı�������
	{
		sprintf(resultpath,"dataupdate\\%d.txt",updateKB);
		fileptr=fopen(resultpath,"wb");
		//���ɸ��´�С
		
		updatesize=chksize_KB(updateKB);
		updateKB=updateKB*2;
		updatestream->bytessize=updatesize;
		updatesize=updatesize*2;
		//���Ǵ�improve cauchy RS����������
		for(j=10;j<35;j++)
		{
			sprintf(systempath,"region%d\\update.txt",j);//���ɴ洢·��
			//�洢һ���ļ�ʷ��
			resTF=encoder_filestore_API_path(systempath,"D:\\update.txt");
			if(resTF==FALSE)
			{
				show_error("weqwe","","");
			}
			fprintf(fileptr,"region%d\n",j);//
			for(k=0;k<1000;k++)
			{
				//��������һǧ������
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
				fprintf(fileptr,"%lf\n",sectime);
				printf("file updated %d\n",k);
			}
			printf("region %d\n",j);
		}
		fclose(fileptr);
	}
	free(updatestream);
	free(contentptr);
	free(systempath);
	free(resultpath);
}