#ifndef _ENCODER_H
#define _ENCODER_H
//文件进行编解码
//分块函数
//这里是veronica，因此仅仅使用encoder代表map，mate和encode三层编码
//veronica是简化版仅仅实验编码专用不支持目录结构
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
extern int encoder_METALAYER_matedata(BYTESTREAM *filecontent,char *filepath);//提取文件元数据和相应文件内容
extern int encoder_METALAYER_split(CHUNKBLOCKGROUP *ckbgroup,BYTESTREAM *filecontent);//将文件数据分解相应的块,其中chunksize必须已知计算groupsize大小

//encoder-layer
//调用编码函数
extern int encoder_ENCODERLAYER_encoder_data_ptr(STRIPBLOCKGROUP *stripblockgroupptr,REGION *regionptr);//使用选的region编码方式生成相应全体数据块生成数据校验
extern int encoder_ENCODERLAYER_encoder_data_id(STRIPBLOCKGROUP *stripblockgroupptr,UINT64 regionid);//通过regionid将数据块进行编码

//map-layer
//存储函数
//extern int encoder_MAPLAYER_map_data_ptr(CHUNKBLOCKGROUP *chunkblockgroupptr,STRIPBLOCKGROUP *stripblockgroupptr,REGION *regionptr);//将数据块放入指定位置
//下面两个函数是条带级的同步
extern int encoder_MAPLAYER_map_data_ptr(STRIPBLOCKGROUP *stripblockgroupptr,REGION *regionptr);//将数据块放入指定位置,以条带为单位
extern int encoder_MAPLAYER_map_data_and_file_ptr(STRIPBLOCKGROUP *stripblockgroupptr,FILEMETABLOCKGROUP *filemetablockgroupptr,REGION *regionptr);//将数据块放入指定位置+文件数据

extern int encoder_MAPLAYER_map_data_ptr_stripmeta(STRIPBLOCKGROUP *stripblockgroupptr,FILEMETABLOCKGROUP *filemetablockgroupptr,REGION *regionptr);//同步条带的元数据
extern int encoder_MAPLAYER_map_data_and_parity_ptr(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *datablockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,REGION *regionptr);//将校验块和数据块写入内存
extern int encoder_MAPLAYER_map_data_ptr_chunk(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *datablockgroupptr,REGION *regionptr);//同步条带元数据和数据块数据以及相应校验
extern int encoder_MAPLAYER_map_data_and_file_ptr_CHUNK(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *datablockgroupptr,FILEMETABLOCKGROUP *filemetablockgroupptr,REGION *regionptr);//同步条带元数据和数据块数据以及文件


//extern int encoder_MAPLAYER_map_data_id(CHUNKBLOCKGROUP *chunkblockgroupptr,STRIPBLOCKGROUP *stripblockgroupptr,UINT64 regionid);//通过id将数据放入指定位置
extern int encoder_MAPLAYER_map_data_id(STRIPBLOCKGROUP *stripblockgroupptr,UINT64 regionid);//通过id将数据放入指定位置



//总体调用函数
extern int encoder_filestore_API_path(char *tarpath,char *soupath);//其中soupath是本地文件路径，tarpath是文件系统路径
extern int encoder_filestore_API_CONTENT(char *tarpath,BYTESTREAM *filecontent);//其中BYTESTREAM filecontent代表文件内容，tarpath是文件系统路径


extern int encoder_METALAYER_update_map(CHUNKPOSITIONBLOCKGROUP *chunkposistionblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr,
										BYTESTREAM *updatestream,int offset,REGION *regionptr);//建立新的空间将数据分配到中间
extern int encoder_METALAYER_location_chunkposition_update_chunk(CHUNKPOSITIONBLOCK *chunkpositionblockptr);//更新chunk位置数据
extern int encoder_METALAYER_location_chunkposition_update(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr);//定位chunk在条带中的位置


extern int encoder_MATELAYER_update_data_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										CHUNK *chunkptr,int startoffset,int lastoffset,//数据块
										BYTESTREAM *bytecontentptr//内容的指针
										);
extern int encoder_METALAYER_update_data_split(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//当前已有chunk列表
												CHUNK *firstchunkptr,int startoffset,//第一个数据chunk以及离开头部的偏移量
												CHUNK *lastchunkptr,int lastoffset,//最后一个数据chunk以及数据chunk到底部的偏移量
												BYTESTREAM *bytecontentptr//内容的指针
												);

extern int encoder_ENCODERLAYER_update_encode_id(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,UINT64 regionid);//根据编码信息进行分析
extern int encoder_ENCODERLAYER_updata_encode_ptr(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr,REGION *regionptr);//根据编码信息进行分析

extern int encoder_MAPLAYER_update_map_data_and_pairty(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr);//将数据写入相应磁盘和内存位置

extern int encoder_filestore_API_update(char *tarpath,BYTESTREAM *updatestream,int offset);//根据update的偏移量
#endif