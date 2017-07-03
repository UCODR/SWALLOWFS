//将请求数据写入mysql数据库
#include "mysql.h"
#include "matrix.h"
#include "FILELAYER.h"
#include "file.h"

extern int checkpoint_record_recent_request(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr);//给出收到影响
extern int checkpoint_record_chunks(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,CHUNKBLOCKGROUP *parityblockgroupptr);//记录所有的块数据
//两个基本操作
extern int checkpoint_delete_request(int reqindex);//删除缓冲文件并且清空数据库
extern int checkpoint_delete_backup_data(CHECKPOINTGROUP *checkpointgrpptr);//删除给定请求的块

extern int checkpoint_record_one_chunk(CHUNK *chunkptr,UINT64 reqindex,int chunkindex);//需要将chunkindex记下

extern int checkpoint_recover_recent_request(int requestnum);//恢复最近的requestnum的请求回退
extern int checkpoint_recover_one_request(CHECKPOINTINF *checkpointinfptr);//恢复一个请求
extern int checkpoint_recover_one_chunk(CHECKPOINT *checkpointptr);//根据一条记录恢复一个块