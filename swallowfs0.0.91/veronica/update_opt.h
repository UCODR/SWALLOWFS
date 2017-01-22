#include "global_define.h"
#include "matrix.h"
#include "profile.h"
#include "galois.h"
//�ͷ�����
extern int UPDATE_OPT_free_matrix(BITMATRIX *matrixptr);

extern int UPDATE_OPT_free_schedule(SCHEDULE *schedule);

extern int UPDATE_OPT_free_bitelementgroup(BITELEMENTGROUP *bitelementgroupptr);
extern int UPDATE_OPT_free_bitelement(BITELEMENT *bitelementptr);

extern int UPDATE_OPT_free_updateelementgroup(UPDATEELEMENTGROUP *updateelementgroupptr);
extern int UPDATE_OPT_free_updateelement(UPDATEELEMENT *updateelementptr);

//readmapmatrix��xΪchunknum��yΪsripsectnum,������Ϊ��������
//����ǰbitelement���и�ֵ
extern int UPDATE_OPT_bitelement_ptr(BITELEMENT *bitelementptr,
									STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
									STRIPSECTBLOCKGROUP *codestrsetblockgroupptr);
//����stripsectindex��chunkindex������Ӧ��bitelement
extern int UPDATE_OPT_bitelement(BITELEMENT *bitelementptr,
									STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
									STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
									BITMATRIX *matrix,REGION *regionptr);
//������updateIelement��updateIIelement������д
extern int UPDATE_OPT_updateI_II_element(UPDATEELEMENT *updateelementptr,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
											BITMATRIX *matrix,REGION *regionptr);

//������Ӧ��updateelement������bitelement����stripindex��chunkindex
extern int UPDATE_OPT_update_element(UPDATEELEMENT *updateelementptr,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
										STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
										int *updatelist,BITMATRIX *matrix,
										int stripsectindex,int chunkindex,
										REGION *regionptr);
//����ÿһ��updateelement�����Ϣ
extern int UPDATE_OPT_update_element_group(UPDATEELEMENTGROUP *updategroupptr,
										CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
										STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
										int *updatelist,
										BITMATRIX *matrix,REGION *regionptr);
//ͨ��RAID6��������updateelement������֮�����Ϣ
extern int UPDATE_OPT_update_element_group_RAID6(UPDATEELEMENTGROUP *updategroupptr,
												CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
												STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
												STRIPSECT *pparity,STRIPSECT *qparity,
												int *pupdatelist,int *qupdatelist,
												BITMATRIX *matrix,REGION *regionptr);
//���ݱ���λ�����ݷֳ���������,�ڴ��̺��ڴ漯�Ͻ��з���
extern int UPDATE_OPT_create_memory_disk_readmapmatrix(BITELEMENTGROUP *memorygroupptr,BITELEMENTGROUP *diskgroupptr,
														STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
														BITMATRIX *readmapmatrix,BITMATRIX *matrix,
														int *countnum,REGION *regionptr);
extern int UPDATE_OPT_create_memory_disk(BITELEMENTGROUP *memorygroupptr,BITELEMENTGROUP *diskgroupptr,
										STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
										BITMATRIX *readmapmatrix,BITMATRIX *matrix,
										int *countnum,REGION *regionptr);
extern int UPDATE_OPT_create_memory_disk_index(BITELEMENTGROUP *memorygroupptr,BITELEMENTGROUP *diskgroupptr,
												BITMATRIX *readmapmatrix);
extern int UPDATE_OPT_create_memory_disk_ptr(BITELEMENTGROUP *memorygroupptr,BITELEMENTGROUP *diskgroupptr,
										STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,STRIPSECTBLOCKGROUP *codestrsetblockgroupptr);
extern int UPDATE_OPT_create_menory_disk_bitnumber_set(BITELEMENTGROUP *memorygroupptr,BITELEMENTGROUP *diskgroupptr,
												BITMATRIX *readmapmatrix,BITMATRIX *matrix,REGION *regionptr);



//������Ϣ������������Ϣ��������ȫ�ֵ�������
extern int UPDATE_OPT_create_scheduling(UPDATEELEMENTBLOCKGROUP *schresult,
										UPDATEELEMENTGROUP *updateelementgroupptr,
										SCHEDULE *schefuling,
										STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
										STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
										BITMATRIX *matrix,BITMATRIX *readmatrix,
										REGION *regionptr);//��ʾʹ��
//������Ϣ������������Ϣ��������ȫ�ֵ�������
extern int UPDATE_OPT_create_scheduling_RAID6(UPDATEELEMENTBLOCKGROUP *schresult,
												UPDATEELEMENTGROUP *updateelementgroupptr,
												SCHEDULE *schefuling,//
												STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
												STRIPSECT *pparity,STRIPSECT *qparity,//
												CHUNKBLOCKGROUP *parityblockgroupptr,
												BITMATRIX *matrix,BITMATRIX *readmapmatrix,
												REGION *regionptr);



extern int UPDATE_OPT_find_scheduling_memory_closest(UPDATEELEMENT *resultelementptr,
													BITELEMENTGROUP *memorygroupptr,
													BITMATRIX *readmapmatrix);
extern int UPDATE_OPT_find_scheduling_disk_closest(UPDATEELEMENT *resultelementptr,
													BITELEMENTGROUP *diskgroupptr,
													BITMATRIX *readmapmatrix);
extern int UPDATE_OPT_find_scheduling_updateelement_closest(UPDATEELEMENT *resultelementptr,
													UPDATEELEMENTGROUP  *updateelementgroupptr,
													BITMATRIX *readmapmatrix);
extern int UPDATE_OPT_find_scheduling_closest(UPDATEELEMENT *resultelementptr,//��Ҫ�����updateelement
											UPDATEELEMENTGROUP  *updateelementgroupptr,//
											BITELEMENTGROUP *memorygroupptr,
											BITELEMENTGROUP *diskgroupptr,
											BITMATRIX *readmapmatrix);
extern UPDATEELEMENT *UPDATE_OPT_find_next_updateelement(UPDATEELEMENTGROUP *updateelementgroupptr,
											BITELEMENTGROUP *memorygroupptr,
											BITELEMENTGROUP *diskgroupptr,
											BITMATRIX *readmapmatrix);

extern int UPDATE_OPT_matrix_matrix_create_schedule(BITMATRIX *tarmatrix,BITMATRIX *soumatrix,
											SCHEDULE *sch,
											STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
											STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
											UPDATEELEMENT *updateelement,
											BITMATRIX *readmapmatrix);
extern int UPDATE_OPT_updateelement_bitelement_create_schedule(UPDATEELEMENT *tarupdateelement,BITELEMENT *soubitelement,
																STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
																STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
																BITMATRIX *readmapmatrix);
extern int UPDATE_OPT_updateelement_updateelement_create_schedule(UPDATEELEMENT *tarupdateelement,UPDATEELEMENT *souupdateelement,
																	STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
																	STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
																	BITMATRIX *readmapmatrix);

//������Ϣ������������Ϣ��������ȫ�ֵ�������
extern int UPDATE_OPT_create_scheduling_group(UPDATEELEMENTBLOCKGROUP *schresult,
											UPDATEELEMENTGROUP *updateelementgroupptr,
											STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
											STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
											BITMATRIX *matrix,//������
											BITMATRIX *readmapmatrix,int *countnum,//
											REGION *regionptr);//����ʹ��
//������Ϣ������������Ϣ
extern int UPDATE_OPT_create_scheduling_group_RAID6(UPDATEELEMENTBLOCKGROUP *schresult,
													UPDATEELEMENTGROUP *updateelementgroupptr,
													STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
													STRIPSECT *pparity,STRIPSECT *qparity,
													BITMATRIX *matrix,//������
													BITMATRIX *readmapmatrix,int *countnum,
													REGION *regionptr);//����countnum

//ʹ�������㷨����ʵ�ʼ���
extern int UPDATE_OPT_calculate_UPDATEI(SCHEDULE *schedorder,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNK *tarchunkptr,UPDATEELEMENT *updateelementptr);
extern int UPDATE_OPT_calculate_UPDATEII(SCHEDULE *schedorder,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNK *tarchunkptr,UPDATEELEMENT *updateelementptr);

//���ݵ�ǰ�����ݽ��м���
extern int UPDATE_OPT_calculate_target_chunk(UPDATEELEMENTBLOCKGROUP *updateelementblockgroupptr,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,UPDATEELEMENT *updateelementptr);
//���ݵ�ǰ�����ݽ��м���
extern int UPDATE_OPT_calculate_target_chunk_RAID6(UPDATEELEMENTBLOCKGROUP *updateelementblockgroupptr,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,UPDATEELEMENT *updateelementptr);


//ͨ�ýӿ�
extern int UPDATE_OPT_update_scheduling(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										STRIP *stripptr,CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix);
//RAID-6�ӿ�
extern int UPDATE_OPT_update_scheduling_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//
											STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,//
											CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix);