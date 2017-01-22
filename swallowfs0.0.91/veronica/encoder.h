#ifndef _ENCODER_H
#define _ENCODER_H
//�ļ����б����
//�ֿ麯��
//������veronica����˽���ʹ��encoder����map��mate��encode�������
//veronica�Ǽ򻯰����ʵ�����ר�ò�֧��Ŀ¼�ṹ
#include "global_define.h"
#include "galois.h"
#include "matrix.h"
#include "file.h"
#include "profile.h"
#include "rscode.h"
#include "RAID5.h"
#include "RAID6.h"
#include "MBR.h"
#include "MSR.h"
#include "other.h"
#include "system_com.h"
//meta-layer
extern int encoder_METALAYER_matedata(BYTESTREAM *filecontent,char *filepath);//��ȡ�ļ�Ԫ���ݺ���Ӧ�ļ�����
extern int encoder_METALAYER_split(CHUNKBLOCKGROUP *ckbgroup,BYTESTREAM *filecontent);//���ļ����ݷֽ���Ӧ�Ŀ�,����chunksize������֪����groupsize��С

//encoder-layer
//���ñ��뺯��
extern int encoder_ENCODERLAYER_encoder_data_ptr(STRIPBLOCKGROUP *stripblockgroupptr,REGION *regionptr);//ʹ��ѡ��region���뷽ʽ������Ӧȫ�����ݿ���������У��
extern int encoder_ENCODERLAYER_encoder_data_id(STRIPBLOCKGROUP *stripblockgroupptr,UINT64 regionid);//ͨ��regionid�����ݿ���б���

//map-layer
//�洢����
//extern int encoder_MAPLAYER_map_data_ptr(CHUNKBLOCKGROUP *chunkblockgroupptr,STRIPBLOCKGROUP *stripblockgroupptr,REGION *regionptr);//�����ݿ����ָ��λ��
//����������������������ͬ��
extern int encoder_MAPLAYER_map_data_ptr(STRIPBLOCKGROUP *stripblockgroupptr,REGION *regionptr);//�����ݿ����ָ��λ��,������Ϊ��λ
extern int encoder_MAPLAYER_map_data_and_file_ptr(STRIPBLOCKGROUP *stripblockgroupptr,FILEMETABLOCKGROUP *filemetablockgroupptr,REGION *regionptr);//�����ݿ����ָ��λ��+�ļ�����

extern int encoder_MAPLAYER_map_data_ptr_stripmeta(STRIPBLOCKGROUP *stripblockgroupptr,FILEMETABLOCKGROUP *filemetablockgroupptr,REGION *regionptr);//ͬ��������Ԫ����
extern int encoder_MAPLAYER_map_data_and_parity_ptr(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *datablockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,REGION *regionptr);//��У�������ݿ�д���ڴ�
extern int encoder_MAPLAYER_map_data_ptr_chunk(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *datablockgroupptr,REGION *regionptr);//ͬ������Ԫ���ݺ����ݿ������Լ���ӦУ��
extern int encoder_MAPLAYER_map_data_and_file_ptr_CHUNK(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *datablockgroupptr,FILEMETABLOCKGROUP *filemetablockgroupptr,REGION *regionptr);//ͬ������Ԫ���ݺ����ݿ������Լ��ļ�


//extern int encoder_MAPLAYER_map_data_id(CHUNKBLOCKGROUP *chunkblockgroupptr,STRIPBLOCKGROUP *stripblockgroupptr,UINT64 regionid);//ͨ��id�����ݷ���ָ��λ��
extern int encoder_MAPLAYER_map_data_id(STRIPBLOCKGROUP *stripblockgroupptr,UINT64 regionid);//ͨ��id�����ݷ���ָ��λ��



//������ú���
extern int encoder_filestore_API_path(char *tarpath,char *soupath);//����soupath�Ǳ����ļ�·����tarpath���ļ�ϵͳ·��
extern int encoder_filestore_API_CONTENT(char *tarpath,BYTESTREAM *filecontent);//����BYTESTREAM filecontent�����ļ����ݣ�tarpath���ļ�ϵͳ·��


extern int encoder_METALAYER_update_map(CHUNKPOSITIONBLOCKGROUP *chunkposistionblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr,
										BYTESTREAM *updatestream,int offset,REGION *regionptr);//�����µĿռ佫���ݷ��䵽�м�
extern int encoder_METALAYER_location_chunkposition_update_chunk(CHUNKPOSITIONBLOCK *chunkpositionblockptr);//����chunkλ������
extern int encoder_METALAYER_location_chunkposition_update(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr);//��λchunk�������е�λ��


extern int encoder_MATELAYER_update_data_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										CHUNK *chunkptr,int startoffset,int lastoffset,//���ݿ�
										BYTESTREAM *bytecontentptr//���ݵ�ָ��
										);
extern int encoder_METALAYER_update_data_split(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//��ǰ����chunk�б�
												CHUNK *firstchunkptr,int startoffset,//��һ������chunk�Լ��뿪ͷ����ƫ����
												CHUNK *lastchunkptr,int lastoffset,//���һ������chunk�Լ�����chunk���ײ���ƫ����
												BYTESTREAM *bytecontentptr//���ݵ�ָ��
												);

extern int encoder_ENCODERLAYER_update_encode_id(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,UINT64 regionid);//���ݱ�����Ϣ���з���
extern int encoder_ENCODERLAYER_updata_encode_ptr(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,REGION *regionptr);//���ݱ�����Ϣ���з���

extern int encoder_MAPLAYER_update_map_data_and_pairty(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr);//������д����Ӧ���̺��ڴ�λ��

extern int encoder_filestore_API_update(char *tarpath,BYTESTREAM *updatestream,int offset);//����update��ƫ����
#endif