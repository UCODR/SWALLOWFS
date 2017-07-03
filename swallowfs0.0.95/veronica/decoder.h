#ifndef _DECODER_H
#define _DECODER_H
#include "global_define.h"
#include "galois.h"
#include "matrix.h"
#include "file.h"
#include "profile.h"
#include "encoder.h"
#include "system_com.h"
#include "hamming.h"
#include "RAID5.h"
#include "RAID6.h"
#include "MBR.h"
#include "MSR.h"
//Ԫ���ݲ�
extern int decoder_METALAYER_storage(char *filepath,BYTESTREAM *filecontent);//�����ݴ洢����Ӧ���ļ�ָ����
extern int decoder_METALAYER_merger(BYTESTREAM *filecontent,CHUNKBLOCKGROUP *chunkblockgroupptr);//������������֯��Ϊ������

//encoderlayer

//recover�����ĸ���������recover
extern int decoder_DECODERLAYER_decoder_data_ptr(STRIPBLOCKGROUP *stripblockgrouppt,ERRORPATTERN *errormatrix,REGION *regionptr);//����stripblock����
extern int decoder_DECODERLAYER_decoder_data_ID(STRIPBLOCKGROUP *stripblockgrouppt,ERRORPATTERN *errormatrix,REGION *regionptr);//����stripblock����

//extern int decoder_DECODERLAYER_decoder_data_ptr_chunkblockstripptr(CHUNKBLOCKSTRIPGROUP *chunkblockstripptr,ERRORPATTERN *errormatrix,REGION *regionptr);//��У�����ݺ���������ʧЧ���ݿ��е�ԭʼ���ݿ鲢��ʹ��ָ��ָ����Щ��
//extern int decoder_DECODERLAYER_decoder_data_ID_chunkblockstripptr(CHUNKBLOCKSTRIPGROUP *chunkblockstripptr,ERRORPATTERN *errormatrix,UINT64 regionid);//��У�����ݺ���������ʧЧ���ݿ��ԭʼԪ���ݿ鲢��ʹ��ָ��ָ����Щ��
extern int decoder_DECODERLAYER_decoder_data_ptr_chunk(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//
extern int decoder_DECODERLAYER_decoder_data_ID_chunk(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,UINT64 regionid);

//degrader����·���ϵĿ�
extern int decoder_DECODERLAYER_decoder_data_ID_chunk_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,UINT64 regionid);
extern int decoder_DECODERLAYER_decoder_data_ptr_chunk_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);

//maplayer
//�������д������
//chunk��ͬ��
//extern int decoder_MAPLAYER_map_data_PTR_writer_chunk_chunkblockstrip(CHUNKBLOCKSTRIPGROUP *chunkblockstripgroupptr,REGION *regionptr);//��Ҫ����decode�ں���
//extern int decoder_MAPLAYER_map_data_ID_writer_chunk_chunkblockstrip(CHUNKBLOCKSTRIPGROUP *chunkblockstripgroupptr,UINT64 regionid);//��Ҫ����decode����

extern int decoder_MAPLAYER_map_data_PTR_writer_chunk(STRIPBLOCKGROUP *stripblockgroup,CHUNKBLOCKGROUP *chunkblockgroup,REGION *regionptr);//��Ҫ����encode�ں���
extern int decoder_MAPLAYER_map_data_ID_writer_chunk(STRIPBLOCKGROUP *stripblockgroup,CHUNKBLOCKGROUP *chunkblockgroup,UINT64 regionid);//��Ҫ����encode����

//strip��ͬ��
extern int decoder_MAPLAYER_map_data_PTR_writer(STRIPBLOCKGROUP *stripblockgroupptr,REGION *regionptr);//����������ͬ����
extern int decoder_MAPLAYER_map_data_ID_writer(STRIPBLOCKGROUP *stripblockgroupptr,UINT64 regionid);

//�Ӵ����ж�ȡ����
extern int decoder_MAPLAYER_map_data_PTR(CHUNKBLOCKGROUP *chunkblockgroupptr,REGION *regionptr);//���������ݸ��ݲ��Զ�ȡ����//������pushtime��������
extern int decoder_MAPLAYER_map_data_ID(CHUNKBLOCKGROUP *chunkblockgroupptr,UINT64 regionid);//���������ݸ��ݲ��Զ�ȡ����ʹ��id����Ⱥ

//������������degrade download����
extern int decoder_MAPLAYER_map_data_PTR_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//��Ҫ���ݲ�ͬ���㷨ѡ����Ӧ��degrade��map��ȡ
extern int decoder_MAPLAYER_map_data_ID_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,UINT64 regionid);//��Ҫ���ݲ�ͬ���㷨ѡ����Ӧ��degrade��map��ȡ

//����recover����map
extern int decoder_MAPLAYER_map_data_PTR_recover(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//��Ҫ���ݲ�ͬ���㷨ѡ����Ӧ��recover��map��ȡ
extern int decoder_MAPLAYER_map_data_ID_recover(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,UINT64 regionid);//��ǰ��Ҫ�Ļָ�������

//���ݶ�����Ҫ�ͷ����ݿռ�
extern int decoder_MAPLAYER_map_data_free_chunk(CHUNKBLOCKGROUP *chunkblockgroupptr);//�ͷ�chunk�ռ�
extern int decoder_MAPLAYER_map_data_free_strip(STRIPBLOCKGROUP *stripblockgroupptr);//�ͷ�strip�ռ�

//������ú���
extern int decoder_filestore_API_path(char *tarpath,char *soupath);//����soupath�Ǳ��طֲ�ʽ�ļ�·����tarpath�Ǽ����ļ�ϵͳ·��
extern int decoder_filestore_API_CONTENT(BYTESTREAM *filecontent,char *soupath);//����BYTESTREAM filecontent�����ļ����ݣ�tarpath�Ƿֲ�ʽ�ļ�ϵͳ·��
//degrade����
extern int decoder_filestore_API_path_degrade(char *tarpath,char *soupath,ERRORPATTERN *errormatrix);//ʹ�ó���ģʽ������degrade���ݶ�ȡ������soupath�Ǳ��طֲ�ʽ�ļ�·����tarpath�Ǽ����ļ�ϵͳ·��
extern int decoder_filestore_API_CONTENT_degrade(BYTESTREAM *filecontent,char *soupath,ERRORPATTERN *errormatrix);//ʹ�ó���ģʽ������degrade���ݶ�ȡ������BYTESTREAM filecontent�����ļ����ݣ�tarpath�Ƿֲ�ʽ�ļ�ϵͳ·��

//recover����
extern int decoder_filestore_API_recover_ID(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,UINT64 regionid);//ʹ�ó���ģʽ���ָ�����,��stripblockgroupΪ��ʱ,��region�ָ�ȫ������
extern int decoder_filestore_API_recover_PTR(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//ʹ�ó���ģʽ���ָ�����,��stripblockgroupΪ��ʱ,��region�ָ�ȫ������
#endif