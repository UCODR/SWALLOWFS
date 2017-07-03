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
//元数据层
extern int decoder_METALAYER_storage(char *filepath,BYTESTREAM *filecontent);//将数据存储到相应的文件指针中
extern int decoder_METALAYER_merger(BYTESTREAM *filecontent,CHUNKBLOCKGROUP *chunkblockgroupptr);//将数据重新组织成为数据流

//encoderlayer

//recover下面四个函数用于recover
extern int decoder_DECODERLAYER_decoder_data_ptr(STRIPBLOCKGROUP *stripblockgrouppt,ERRORPATTERN *errormatrix,REGION *regionptr);//计算stripblock数据
extern int decoder_DECODERLAYER_decoder_data_ID(STRIPBLOCKGROUP *stripblockgrouppt,ERRORPATTERN *errormatrix,REGION *regionptr);//计算stripblock数据

//extern int decoder_DECODERLAYER_decoder_data_ptr_chunkblockstripptr(CHUNKBLOCKSTRIPGROUP *chunkblockstripptr,ERRORPATTERN *errormatrix,REGION *regionptr);//将校验数据和数据生成失效数据块中的原始数据块并且使用指针指向这些块
//extern int decoder_DECODERLAYER_decoder_data_ID_chunkblockstripptr(CHUNKBLOCKSTRIPGROUP *chunkblockstripptr,ERRORPATTERN *errormatrix,UINT64 regionid);//将校验数据和数据生成失效数据块的原始元数据块并且使用指针指向这些块
extern int decoder_DECODERLAYER_decoder_data_ptr_chunk(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//
extern int decoder_DECODERLAYER_decoder_data_ID_chunk(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,UINT64 regionid);

//degrader计算路径上的块
extern int decoder_DECODERLAYER_decoder_data_ID_chunk_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,UINT64 regionid);
extern int decoder_DECODERLAYER_decoder_data_ptr_chunk_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);

//maplayer
//像磁盘中写入数据
//chunk级同步
//extern int decoder_MAPLAYER_map_data_PTR_writer_chunk_chunkblockstrip(CHUNKBLOCKSTRIPGROUP *chunkblockstripgroupptr,REGION *regionptr);//主要调用decode内函数
//extern int decoder_MAPLAYER_map_data_ID_writer_chunk_chunkblockstrip(CHUNKBLOCKSTRIPGROUP *chunkblockstripgroupptr,UINT64 regionid);//主要调用decode计算

extern int decoder_MAPLAYER_map_data_PTR_writer_chunk(STRIPBLOCKGROUP *stripblockgroup,CHUNKBLOCKGROUP *chunkblockgroup,REGION *regionptr);//主要调用encode内函数
extern int decoder_MAPLAYER_map_data_ID_writer_chunk(STRIPBLOCKGROUP *stripblockgroup,CHUNKBLOCKGROUP *chunkblockgroup,UINT64 regionid);//主要调用encode计算

//strip级同步
extern int decoder_MAPLAYER_map_data_PTR_writer(STRIPBLOCKGROUP *stripblockgroupptr,REGION *regionptr);//将条带数据同步到
extern int decoder_MAPLAYER_map_data_ID_writer(STRIPBLOCKGROUP *stripblockgroupptr,UINT64 regionid);

//从磁盘中读取数据
extern int decoder_MAPLAYER_map_data_PTR(CHUNKBLOCKGROUP *chunkblockgroupptr,REGION *regionptr);//将生成数据根据策略读取数据//这里是pushtime来看策略
extern int decoder_MAPLAYER_map_data_ID(CHUNKBLOCKGROUP *chunkblockgroupptr,UINT64 regionid);//讲生成数据根据策略读取数据使用id查找群

//条带数据用于degrade download数据
extern int decoder_MAPLAYER_map_data_PTR_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//需要根据不同的算法选择相应的degrade的map读取
extern int decoder_MAPLAYER_map_data_ID_degrade(CHUNKBLOCKGROUP *chunkblockgroupptr,ERRORPATTERN *errormatrix,UINT64 regionid);//需要根据不同的算法选择相应的degrade的map读取

//用于recover数据map
extern int decoder_MAPLAYER_map_data_PTR_recover(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//需要根据不同的算法选择相应的recover的map读取
extern int decoder_MAPLAYER_map_data_ID_recover(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,UINT64 regionid);//当前需要的恢复的条带

//数据读完需要释放数据空间
extern int decoder_MAPLAYER_map_data_free_chunk(CHUNKBLOCKGROUP *chunkblockgroupptr);//释放chunk空间
extern int decoder_MAPLAYER_map_data_free_strip(STRIPBLOCKGROUP *stripblockgroupptr);//释放strip空间

//总体调用函数
extern int decoder_filestore_API_path(char *tarpath,char *soupath);//其中soupath是本地分布式文件路径，tarpath是计算文件系统路径
extern int decoder_filestore_API_CONTENT(BYTESTREAM *filecontent,char *soupath);//其中BYTESTREAM filecontent代表文件内容，tarpath是分布式文件系统路径
//degrade函数
extern int decoder_filestore_API_path_degrade(char *tarpath,char *soupath,ERRORPATTERN *errormatrix);//使用出错模式来进行degrade数据读取，其中soupath是本地分布式文件路径，tarpath是计算文件系统路径
extern int decoder_filestore_API_CONTENT_degrade(BYTESTREAM *filecontent,char *soupath,ERRORPATTERN *errormatrix);//使用出错模式来进行degrade数据读取，其中BYTESTREAM filecontent代表文件内容，tarpath是分布式文件系统路径

//recover函数
extern int decoder_filestore_API_recover_ID(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,UINT64 regionid);//使用出错模式来恢复数据,当stripblockgroup为空时,将region恢复全部数据
extern int decoder_filestore_API_recover_PTR(STRIPBLOCKGROUP *stripblockgroupptr,ERRORPATTERN *errormatrix,REGION *regionptr);//使用出错模式来恢复数据,当stripblockgroup为空时,将region恢复全部数据
#endif