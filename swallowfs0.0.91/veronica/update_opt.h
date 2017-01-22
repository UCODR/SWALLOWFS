#include "global_define.h"
#include "matrix.h"
#include "profile.h"
#include "galois.h"
//释放数据
extern int UPDATE_OPT_free_matrix(BITMATRIX *matrixptr);

extern int UPDATE_OPT_free_schedule(SCHEDULE *schedule);

extern int UPDATE_OPT_free_bitelementgroup(BITELEMENTGROUP *bitelementgroupptr);
extern int UPDATE_OPT_free_bitelement(BITELEMENT *bitelementptr);

extern int UPDATE_OPT_free_updateelementgroup(UPDATEELEMENTGROUP *updateelementgroupptr);
extern int UPDATE_OPT_free_updateelement(UPDATEELEMENT *updateelementptr);

//readmapmatrix，x为chunknum，y为sripsectnum,以条带为横向排列
//将当前bitelement进行赋值
extern int UPDATE_OPT_bitelement_ptr(BITELEMENT *bitelementptr,
									STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
									STRIPSECTBLOCKGROUP *codestrsetblockgroupptr);
//根据stripsectindex和chunkindex生成相应的bitelement
extern int UPDATE_OPT_bitelement(BITELEMENT *bitelementptr,
									STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
									STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
									BITMATRIX *matrix,REGION *regionptr);
//将数据updateIelement和updateIIelement进行填写
extern int UPDATE_OPT_updateI_II_element(UPDATEELEMENT *updateelementptr,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
											BITMATRIX *matrix,REGION *regionptr);

//生成相应的updateelement和其中bitelement根据stripindex和chunkindex
extern int UPDATE_OPT_update_element(UPDATEELEMENT *updateelementptr,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
										STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
										int *updatelist,BITMATRIX *matrix,
										int stripsectindex,int chunkindex,
										REGION *regionptr);
//更新每一个updateelement组的信息
extern int UPDATE_OPT_update_element_group(UPDATEELEMENTGROUP *updategroupptr,
										CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
										STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
										int *updatelist,
										BITMATRIX *matrix,REGION *regionptr);
//通过RAID6创建给定updateelement除调度之外的信息
extern int UPDATE_OPT_update_element_group_RAID6(UPDATEELEMENTGROUP *updategroupptr,
												CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
												STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
												STRIPSECT *pparity,STRIPSECT *qparity,
												int *pupdatelist,int *qupdatelist,
												BITMATRIX *matrix,REGION *regionptr);
//根据比特位阵将数据分成两个集合,在磁盘和内存集合进行分离
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



//根据信息创建调度组信息并且生成全局调度序列
extern int UPDATE_OPT_create_scheduling(UPDATEELEMENTBLOCKGROUP *schresult,
										UPDATEELEMENTGROUP *updateelementgroupptr,
										SCHEDULE *schefuling,
										STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
										STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
										BITMATRIX *matrix,BITMATRIX *readmatrix,
										REGION *regionptr);//演示使用
//根据信息创建调度组信息并且生成全局调度序列
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
extern int UPDATE_OPT_find_scheduling_closest(UPDATEELEMENT *resultelementptr,//需要处理的updateelement
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

//根据信息创建调度组信息并且生成全局调度序列
extern int UPDATE_OPT_create_scheduling_group(UPDATEELEMENTBLOCKGROUP *schresult,
											UPDATEELEMENTGROUP *updateelementgroupptr,
											STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
											STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,
											BITMATRIX *matrix,//编码阵
											BITMATRIX *readmapmatrix,int *countnum,//
											REGION *regionptr);//操作使用
//根据信息创建调度组信息
extern int UPDATE_OPT_create_scheduling_group_RAID6(UPDATEELEMENTBLOCKGROUP *schresult,
													UPDATEELEMENTGROUP *updateelementgroupptr,
													STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
													STRIPSECT *pparity,STRIPSECT *qparity,
													BITMATRIX *matrix,//编码阵
													BITMATRIX *readmapmatrix,int *countnum,
													REGION *regionptr);//其中countnum

//使用两种算法进行实际计算
extern int UPDATE_OPT_calculate_UPDATEI(SCHEDULE *schedorder,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNK *tarchunkptr,UPDATEELEMENT *updateelementptr);
extern int UPDATE_OPT_calculate_UPDATEII(SCHEDULE *schedorder,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNK *tarchunkptr,UPDATEELEMENT *updateelementptr);

//根据当前的数据进行计算
extern int UPDATE_OPT_calculate_target_chunk(UPDATEELEMENTBLOCKGROUP *updateelementblockgroupptr,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,UPDATEELEMENT *updateelementptr);
//根据当前的数据进行计算
extern int UPDATE_OPT_calculate_target_chunk_RAID6(UPDATEELEMENTBLOCKGROUP *updateelementblockgroupptr,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,UPDATEELEMENT *updateelementptr);


//通用接口
extern int UPDATE_OPT_update_scheduling(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										STRIP *stripptr,CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix);
//RAID-6接口
extern int UPDATE_OPT_update_scheduling_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//
											STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,//
											CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix);