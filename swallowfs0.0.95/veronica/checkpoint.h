//����������д��mysql���ݿ�
#include "mysql.h"
#include "matrix.h"
#include "FILELAYER.h"
#include "file.h"

extern int checkpoint_record_recent_request(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr);//�����յ�Ӱ��
extern int checkpoint_record_chunks(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr);//��¼���еĿ�����
//������������
extern int checkpoint_delete_request(int reqindex);//ɾ�������ļ�����������ݿ�
extern int checkpoint_delete_backup_data(CHECKPOINTGROUP *checkpointgrpptr);//ɾ����������Ŀ�

extern int checkpoint_record_one_chunk(CHUNK *chunkptr,UINT64 reqindex,int chunkindex);//��Ҫ��chunkindex����

extern int checkpoint_recover_recent_request(int requestnum);//�ָ������requestnum���������
extern int checkpoint_recover_one_request(CHECKPOINTINF *checkpointinfptr);//�ָ�һ������
extern int checkpoint_recover_one_chunk(CHECKPOINT *checkpointptr);//����һ����¼�ָ�һ����