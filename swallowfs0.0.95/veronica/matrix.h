//主要目的实现galois矩阵乘法，除法、逆运算和判断矩阵是否可逆
#ifndef _MATRIX_H
#define _MATRIX_H
#include <stdio.h>
#include "global_define.h"
#include "galois.h"
#include "profile.h"
//代码中加入了一定的面向对象的思想
//统计个数
extern int matrix_count_number_one(BITMATRIX *matrix);//统计当前矩阵中1的个数
extern int matrix_count_number_zero(BITMATRIX *matrix);//统计当前矩阵中0的个数
//矩阵创建函数
extern INTMATRIX matrix_create_w08(UINT32 *matrix,int rows,int cols);//生成相应8位，进行mat赋值上去,c无法处理二维函数传递只能一维
extern INTMATRIX matrix_create_w16(UINT32 *matrix,int rows,int cols);//生成16位
extern INTMATRIX matrix_create_w32(UINT32 *matrix,int rows,int cols);//生成32位
extern INTMATRIX matrix_create_NULL();//创建一个空的INTMATRIX
extern int matrix_set_data(INTMATRIX *matrix,UINT32 *mat,int rows,int cols,int w);//设定数据
extern INTMATRIX matrix_duplicate(INTMATRIX *matrix);//复制矩阵
extern int matrix_bitmatrix_data_copy(BITMATRIX *tarmatrix,BITMATRIX *soumatrix,int offset,int size);//将比特矩阵的offset的n位进行拷贝
extern int matrix_destroy(INTMATRIX *matrix);//销毁一个矩阵
//显示矩阵
void matrix_print_matrix_outcheck(INTMATRIX *matrix);//显示10进制相应矩阵内容,其中w为相应的字长,但是不检查w为8整数条件

extern void matrix_print_matrix(INTMATRIX *matrix);//显示10进制相应矩阵内容,其中w为相应的字长
extern void matrix_print_16Xmatrix(INTMATRIX *matrix);//显示16进制相应矩阵内容,其中w为相应的字长
extern void matrix_print_bitmatrix_oneline(BITMATRIX *matrix);//显示一个行向量
extern void matrix_print_bitmatrix(INTMATRIX *matrix);//显示bit阵

//矩阵运算（包括求逆、乘法和INTMATRIX->BITMATRIX转化）
extern int matrix_invert(INTMATRIX *matrix,INTMATRIX *invmatrix);//实现逆矩阵
extern int matrix_invertable(INTMATRIX *matrix);//判断矩阵是否可逆
//以上两个函数都会破坏原矩阵，因此要做好备份
extern int matrix_matrix_multiply(INTMATRIX *mat1,INTMATRIX *mat2,INTMATRIX *res);//实现两个矩阵相乘
extern int matrix_matrix_to_bitmatrix(INTMATRIX *matrix,BITMATRIX *bitmatrix);//从INTMATRIX生成一个BITMATRIX
extern int matrix_invert_bitmatrix(BITMATRIX *matrix,BITMATRIX *invmatrix);//生成bitmatrix的逆矩阵
extern int matrix_invertable_bitmatrix(BITMATRIX *matrix);//bitmatrix是否可逆

//使用矩阵计算编解码
//编码8/16/32
//CHUNK大小必须动态生成
//CHUNK创建函数
extern CHUNK matrix_CHUNK_create_NULL();//创建数据块
extern CHUNKGROUP matrix_CHUNKGROUP_create_NULL();//创建数据组块

extern int matrix_CHUNK_print_data(CHUNK *ck,int cols);//输出chunk的数据

extern int matrix_CHUNK_copy_meta(CHUNK *desck,CHUNK *souck);//将原数据进行拷贝
extern int matrix_CHUNK_set_data(CHUNK *ck,BYTE* data,UINT64 regionid,int isparity,UINT64 stripid,int sizenum);//设置数据块内容
extern int matrix_CHUNK_copy_data(CHUNK *desck,CHUNK *souck);//将chunk之间相互拷贝
extern int matrix_CHUNK_add_data(CHUNK *desck,CHUNK *souck);//实现两个chunk异或，目标保存在desck中
//w=8,16,32
extern int matrix_CHUNK_w08_multiply(CHUNK *souck,UINT32 multby);//计算在08环境下，计算chunk与单个数相乘的结果，计算结果保存在souck
extern int matrix_CHUNK_w16_multiply(CHUNK *souck,UINT32 multby);//计算在16环境下，乘法
extern int matrix_CHUNK_w32_multiply(CHUNK *souck,UINT32 multby);//计算在32环境下，乘法

extern int matrix_CHUNK_w08_multiply_add(CHUNK *desck,CHUNK *souck,UINT32 multby);//将souck运算结果乘加到desck上
extern int matrix_CHUNK_w16_multiply_add(CHUNK *desck,CHUNK *souck,UINT32 multby);//将souck运算结果乘加到desck上
extern int matrix_CHUNK_w32_multiply_add(CHUNK *desck,CHUNK *souck,UINT32 multby);//将souck运算结果乘加到desck上

extern int matrix_CHUNK_w08_multiply_empty_add(CHUNK *desck,CHUNK *souck,UINT32 multby);//将desck制空，并将souck运算结果赋值到desck上
extern int matrix_CHUNK_w16_multiply_empty_add(CHUNK *desck,CHUNK *souck,UINT32 multby);//将desck制空，并将souck运算结果赋值到desck上
extern int matrix_CHUNK_w32_multiply_empty_add(CHUNK *desck,CHUNK *souck,UINT32 multby);//将desck制空，并将souck运算结果赋值到desck上

extern int matrix_CHUNKGROUP_set_data(CHUNKGROUP *ckgroup,CHUNK *chunklist,int size);//设置chunk组列表
extern int matrix_CHUNKGROUP_add_CHUNK(CHUNKGROUP *ckgroup,CHUNK *CHUNK);//向CHUNKGROUP中加入CHUNK
extern int matrix_CHUNKGROUP_del_CHUNK(CHUNKGROUP *ckgroup,int index);//删除index块

//信息函数
//如果计算所有
//colsnum为希望点乘的数量，如果不为groupnum在src_id中表明group中对应的chunk号
extern DOTINF matrix_DOTINF_create_NULL();//创建一个dotinf
extern int matrix_DOTINF_set_data(DOTINF *dotin,int *src_ids,int linenum,int colsnum,int packetsize,int parityTF);//设置dotinf数据

extern ERASES matrix_ERASES_create_NULL();//生成一个空的ERASES
extern int matrix_ERASES_set_data(ERASES *erarray,int *eras,int codenum,int datanum);///设置ERASES数据

extern ENDECODEPARA matrix_ENDECODEPARA_create_NULL();//生成一个空的papra
extern int matrix_ENDECODEPARA_set_data(ENDECODEPARA *endecpara,int w,INTMATRIX *matrix);//设置para数据

extern SCHEDOP matrix_SCHUDOP_create_NULL();//创建一个SCHUDOP
extern int matrix_SCHUDOP_set_data(SCHEDOP *schedop,int op,int sd,int sb,int dd,int db,int istareget,CHUNK *tarchunkptr,UINT64 chunkid);//设置SCHUDOP数据

extern SCHEDULE matrix_SCHEDULE_create_NULL();//创建一个SCHUDOP
extern int matrix_SCHEDULE_set_data(SCHEDULE *sched,SCHEDOP *schudlist,int size,int w);//设置SCHEDULE数据

extern DM_IDS matrix_DM_IDS_create_NULL();
extern int matrix_DM_IDS_set_data(DM_IDS *dmids,int *dmarr,int size);

//chunkgroup建议先数据chunk后codechunk
//编码
//RAID-5进行一次编码
extern int matrix_do_parity(CHUNKGROUP* ckgroup,CHUNK* parity);//计算校验块此时校验块前置为1
//使用矩阵进行编码
//参数分别从三个数据中读取，因此使用者需要在事前对于GROUP信息进行赋值
extern int matrix_matrix_encode(CHUNKGROUP *pargroup,CHUNKGROUP *ckgroup,INTMATRIX *matrix);//进行INT矩阵编码//参数分别从三个数据中读取
extern int matrix_matrix_encode_BLOCK(CHUNKBLOCKGROUP *pargroup,CHUNKBLOCKGROUP *ckgroup,INTMATRIX *matrix);//chunkblock进行编码
//使用bit阵进行编码
extern int matrix_bitmatrix_encode(CHUNKGROUP *pargroup,CHUNKGROUP *ckgroup,BITMATRIX *matrix,int packetsize);//计算bitmatrix进行编码
extern int matrix_bitmatrix_encode_BLOCK(CHUNKBLOCKGROUP *pargroup,CHUNKBLOCKGROUP *ckgroup,BITMATRIX *matrix,int packetsize);//BLOCK计算校验
//使用schedule进行编码
extern int matrix_schedule_encode(CHUNKGROUP *pargroup,CHUNKGROUP *ckgroup,SCHEDULE *sched,int packetsize);
extern int matrix_schedule_encode_BLOCK(CHUNKBLOCKGROUP *pargroup,CHUNKBLOCKGROUP *ckgroup,SCHEDULE *sched,int packetsize);


//计算RAID-6 stripsect数据
extern int matrix_matrix_firstchunk_handle(CHUNK *parityptr,CHUNK *chunkptr,int curvalue,int w);
extern int matrix_matrix_notfirstchunk_handle(CHUNK *parityptr,CHUNK *chunkptr,int curvalue,int w);

extern int matrix_bitmatrix_encode_stripsect_RAID6(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr,BITMATRIX *matrix);//用于cuachy RS，RDP等XOR码
extern int matrix_matrix_encode_stripsect_RAID6(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr,INTMATRIX *matrix);

extern int matrix_bitmatrix_encode_strip(STRIP *stripptr,BITMATRIX *matrix);
extern int matrix_matrix_encode_strip(STRIP *stripptr,INTMATRIX *matrix);

//I为重新计算，II为利用校验块计算

extern int matrix_update_bitmatrix_pqparity_chunklist_create(int *pupdatelist,int *qupdatelist,
															CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,BITMATRIX *matrix);//找出当前需要进行更新的列表
extern int matrix_update_bitmatrix_pqupdatenum_chunklist_create(int *pupdatelist1,int *pupdatelist2,
															int *qupdatelist1,int *qupdatelist2,
															CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
															STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,
															BITMATRIX *matrix);//找出当前需要进行更新的列表
extern int matrix_bitmatrix_updateI_chunk_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition代表需要更新的校验块列表
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//当前的数据条带
											CHUNK *tarchunkptr,BITMATRIX *matrix,int chkindex);//目标校验块，矩阵，目标块索引				
extern int matrix_bitmatrix_updateII_chunk_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition代表需要更新的校验块列表
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//当前的数据条带
											CHUNK *tarchunkptr,BITMATRIX *matrix,int chkindex);//目标校验块，矩阵，目标块索引
extern int matrix_bitmatrix_updateI_stripsect_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,
											CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix);//RCWRAID6
extern int matrix_bitmatrix_updateII_stripsect_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,
											CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix);
extern int matrix_bitmatrix_update_stripsect_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,//
											CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix);//当前chunkblockgroup中的数据需要在一个strip中

extern int matrix_matrix_updateII_chunk_calcaulate(CHUNK *tarchunkptr,CHUNK *souchunkptr,int curvalue,int w);
//extern int matrix_update_matrix_pqparity_chunklist_create();//在RAID-6classic RS情况下两个块都要更新
extern int matrix_update_matrix_pqupdatenum_chunklist_create(int *pupdatelist,int *qupdatelist,//updatelist第一行为第一个方案，第二行为第二方案
															CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
															STRIPSECTBLOCKGROUP *strsetblockgroupptr,BITMATRIX *matrix);
extern int matrix_matrix_updateI_chunk_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition代表需要更新的校验块列表
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//当前的数据条带
											CHUNK *tarchunkptr,INTMATRIX *matrix,int chkindex);//目标校验块，矩阵，目标块索引
extern int matrix_matrix_updateII_chunk_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition代表需要更新的校验块列表
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//当前的数据条带
											CHUNK *tarchunkptr,INTMATRIX *matrix,int chkindex);//目标校验块，矩阵，目标块索引
extern int matrix_matrix_update_stripsect_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,
											CHUNKBLOCKGROUP *parityblockgroupptr,INTMATRIX *matrix);//当前chunkblockgroup中的数据需要在一个strip中


extern int matrix_update_bitmatrix_parity_chunklist(int *updatelist,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
													BITMATRIX *matrix,int updatenum);//找出当前需要进行更新的列表
extern int matrix_update_bitmatrix_updatenum_chunklist_create(int *updatelist1,int *updatelist2,
																CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
																STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
																BITMATRIX *matrix,int updatenum);//计算两种方案的updatelist
extern int matrix_bitmatrix_updateI_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition代表需要更新的校验块列表
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//当前的数据条带
											CHUNK *tarchunkptr,BITMATRIX *matrix,int chkindex);//目标校验块，矩阵，目标块索引
extern int matrix_bitmatrix_updateII_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition代表需要更新的校验块列表
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//当前的数据条带
											CHUNK *tarchunkptr,BITMATRIX *matrix,int chkindex);//目标校验块，矩阵，目标块索引
extern int matrix_bitmatrix_update_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										STRIP *stripptr,CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix);


extern int matrix_update_matrix_parity_chunklist(int *updatelist,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,BITMATRIX *matrix,int updatenum);//找出当前需要进行更新的列表,MSR和MBR可能有0
extern int matrix_update_matrix_updatenum_chunklist_create(int *updatelist1,int *updatelist2,
															CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
															STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
															BITMATRIX *matrix,int updatenum);//计算两种方案的updatelist
extern int matrix_matrix_updateI_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition代表需要更新的校验块列表
										STRIPSECTBLOCKGROUP *strsetblockgroupptr,//当前的数据条带
										CHUNK *tarchunkptr,INTMATRIX *matrix,int chkindex);//目标校验块，矩阵，目标块索引
extern int matrix_matrix_updateII_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition代表需要更新的校验块列表
										STRIPSECTBLOCKGROUP *strsetblockgroupptr,//当前的数据条带
										CHUNK *tarchunkptr,INTMATRIX *matrix,int chkindex);//目标校验块，矩阵，目标块索引
extern int matrix_matrix_update_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										STRIP *stripptr,CHUNKBLOCKGROUP *parityblockgroupptr,INTMATRIX *matrix);

extern int matrix_matrix_calculate_share(BITMATRIX *matrixptr,CODEPARA *codeptr,AONTSHAREGROUP *sharegroupptr,int sharesize);//根据bit阵计算share
//解码
//解码raid-5
extern int matrix_do_deparity(CHUNKGROUP *ckgroup,CHUNK *lost,int TFparity);//生成相应的丢失块，TFparity是指生成块是不是校验块
//matrix解码
extern int matrix_matrix_decode(CHUNKGROUP *lostgroup,CHUNKGROUP *ckgroup,INTMATRIX *matrix,ERASES *erarray);//使用矩阵进行解码
extern int matrix_matrix_decode_BLOCK(CHUNKBLOCKGROUP *laostgroup,CHUNKBLOCKGROUP *ckgroup,INTMATRIX *matrix,ERASES *erarry);// 计算矩阵解码
//bitmatrix解码
extern int matrix_bitmatrix_decode(CHUNKGROUP *lostgroup,CHUNKGROUP *ckgroup,BITMATRIX *matrix,ERASES *erarray);//计算bit阵当前丢失的数据块
extern int matrix_bitmatrix_decode_BLOCK(CHUNKBLOCKGROUP *lostgroup,CHUNKBLOCKGROUP *ckgroup,BITMATRIX *matrix,ERASES *errarry);//使用bit矩阵
//scheudle解码方案
extern int matrix_schedule_decode_lazy();//仿Plank对外接口函数
extern int matrix_schedule_decode_cache();

//生成相应解码矩阵
extern int matrix_make_decoding_matrix_only(INTMATRIX *decoding_matrix,INTMATRIX *matrix,ERASES *erarray);//仅仅需要计算matrix解码矩阵
extern int matrix_make_decoding_matrix(INTMATRIX *decoding_matrix,INTMATRIX *matrix,ERASES *erarray,DM_IDS *dmids);//计算matrix解码矩阵并且生成数据ID号

extern int matrix_make_decoding_bitmatrix_only(INTMATRIX *decoding_matrix,INTMATRIX *matrix,ERASES *erarray);//仅仅需要计算bitmatrix解码矩阵
extern int matrix_make_decoding_bitmatrix(BITMATRIX *decoding_matrix,BITMATRIX *matrix,ERASES *erarray,DM_IDS *dmids);//计算bitmatrix解码矩阵并且生成数据ID号

//生成erases数据
extern int matrix_make_decoding_chunkblockgroup(CHUNKBLOCKGROUP *tarchunkptr,CHUNKBLOCKGROUP *souchunpptr,ERASES *erarry);//生成相应纠删chunkblockgroup

//点乘大全
//desid以明码盘数量,点乘一行
extern int matrix_matrix_dotprod_BLOCK(INTMATRIX *matrix,CHUNKBLOCKGROUP *ckgroup,CHUNK *parchunk,DOTINF *dotin);
extern int matrix_matrix_dotprod(INTMATRIX *matrix,CHUNKGROUP *chkgroup,CHUNK *parchunk,DOTINF *dotin);//三点乘

extern int matrix_bitmatrix_dotprod_BLOCK(BITMATRIX *matrix,CHUNKBLOCKGROUP *ckgroup,CHUNK *parchunk,DOTINF *dotin);
extern int matrix_bitmatrix_dotprod(BITMATRIX *matrix,CHUNKGROUP *chkgroup,CHUNK *parchunk,DOTINF *dotin);

extern int matrix_do_scheduled_operations_BLOCK(SCHEDULE *sch,CHUNKBLOCKGROUP *ckgrpup,CHUNK *parchunk,DOTINF *dotin);
extern int matrix_do_scheduled_operations(SCHEDULE *sch,CHUNKGROUP *chkgroup,CHUNK *parchunk,DOTINF *dotin);

//BITMATRIX转化函数
extern int matrix_matrix_to_bitmatrix(INTMATRIX *matrix,BITMATRIX *bitmatrix);//从INTMATRIX生成一个BITMATRIX
extern int matrix_dumb_bitmatrix_to_schedule(BITMATRIX *matrix,SCHEDULE *sch);//两种转化方法
extern int matrix_smart_bitmatrix_to_schedule(BITMATRIX *matrix,SCHEDULE *sch); 
extern int matrix_generate_schedule_cache(BITMATRIX *matrix,int smart);

extern int matrix_free_schedule(SCHEDULE *sch);
extern int matrix_free_cache(CACHE *cah);

//性能统计
extern int matrix_get_stats(STATSITEM *fill_in);//读取系统统计数据
#endif
