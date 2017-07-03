//��ҪĿ��ʵ��galois����˷�����������������жϾ����Ƿ����
#ifndef _MATRIX_H
#define _MATRIX_H
#include <stdio.h>
#include "global_define.h"
#include "galois.h"
#include "profile.h"
//�����м�����һ������������˼��
//ͳ�Ƹ���
extern int matrix_count_number_one(BITMATRIX *matrix);//ͳ�Ƶ�ǰ������1�ĸ���
extern int matrix_count_number_zero(BITMATRIX *matrix);//ͳ�Ƶ�ǰ������0�ĸ���
//���󴴽�����
extern INTMATRIX matrix_create_w08(UINT32 *matrix,int rows,int cols);//������Ӧ8λ������mat��ֵ��ȥ,c�޷������ά��������ֻ��һά
extern INTMATRIX matrix_create_w16(UINT32 *matrix,int rows,int cols);//����16λ
extern INTMATRIX matrix_create_w32(UINT32 *matrix,int rows,int cols);//����32λ
extern INTMATRIX matrix_create_NULL();//����һ���յ�INTMATRIX
extern int matrix_set_data(INTMATRIX *matrix,UINT32 *mat,int rows,int cols,int w);//�趨����
extern INTMATRIX matrix_duplicate(INTMATRIX *matrix);//���ƾ���
extern int matrix_bitmatrix_data_copy(BITMATRIX *tarmatrix,BITMATRIX *soumatrix,int offset,int size);//�����ؾ����offset��nλ���п���
extern int matrix_destroy(INTMATRIX *matrix);//����һ������
//��ʾ����
void matrix_print_matrix_outcheck(INTMATRIX *matrix);//��ʾ10������Ӧ��������,����wΪ��Ӧ���ֳ�,���ǲ����wΪ8��������

extern void matrix_print_matrix(INTMATRIX *matrix);//��ʾ10������Ӧ��������,����wΪ��Ӧ���ֳ�
extern void matrix_print_16Xmatrix(INTMATRIX *matrix);//��ʾ16������Ӧ��������,����wΪ��Ӧ���ֳ�
extern void matrix_print_bitmatrix_oneline(BITMATRIX *matrix);//��ʾһ��������
extern void matrix_print_bitmatrix(INTMATRIX *matrix);//��ʾbit��

//�������㣨�������桢�˷���INTMATRIX->BITMATRIXת����
extern int matrix_invert(INTMATRIX *matrix,INTMATRIX *invmatrix);//ʵ�������
extern int matrix_invertable(INTMATRIX *matrix);//�жϾ����Ƿ����
//�����������������ƻ�ԭ�������Ҫ���ñ���
extern int matrix_matrix_multiply(INTMATRIX *mat1,INTMATRIX *mat2,INTMATRIX *res);//ʵ�������������
extern int matrix_matrix_to_bitmatrix(INTMATRIX *matrix,BITMATRIX *bitmatrix);//��INTMATRIX����һ��BITMATRIX
extern int matrix_invert_bitmatrix(BITMATRIX *matrix,BITMATRIX *invmatrix);//����bitmatrix�������
extern int matrix_invertable_bitmatrix(BITMATRIX *matrix);//bitmatrix�Ƿ����

//ʹ�þ����������
//����8/16/32
//CHUNK��С���붯̬����
//CHUNK��������
extern CHUNK matrix_CHUNK_create_NULL();//�������ݿ�
extern CHUNKGROUP matrix_CHUNKGROUP_create_NULL();//�����������

extern int matrix_CHUNK_print_data(CHUNK *ck,int cols);//���chunk������

extern int matrix_CHUNK_copy_meta(CHUNK *desck,CHUNK *souck);//��ԭ���ݽ��п���
extern int matrix_CHUNK_set_data(CHUNK *ck,BYTE* data,UINT64 regionid,int isparity,UINT64 stripid,int sizenum);//�������ݿ�����
extern int matrix_CHUNK_copy_data(CHUNK *desck,CHUNK *souck);//��chunk֮���໥����
extern int matrix_CHUNK_add_data(CHUNK *desck,CHUNK *souck);//ʵ������chunk���Ŀ�걣����desck��
//w=8,16,32
extern int matrix_CHUNK_w08_multiply(CHUNK *souck,UINT32 multby);//������08�����£�����chunk�뵥������˵Ľ����������������souck
extern int matrix_CHUNK_w16_multiply(CHUNK *souck,UINT32 multby);//������16�����£��˷�
extern int matrix_CHUNK_w32_multiply(CHUNK *souck,UINT32 multby);//������32�����£��˷�

extern int matrix_CHUNK_w08_multiply_add(CHUNK *desck,CHUNK *souck,UINT32 multby);//��souck�������˼ӵ�desck��
extern int matrix_CHUNK_w16_multiply_add(CHUNK *desck,CHUNK *souck,UINT32 multby);//��souck�������˼ӵ�desck��
extern int matrix_CHUNK_w32_multiply_add(CHUNK *desck,CHUNK *souck,UINT32 multby);//��souck�������˼ӵ�desck��

extern int matrix_CHUNK_w08_multiply_empty_add(CHUNK *desck,CHUNK *souck,UINT32 multby);//��desck�ƿգ�����souck��������ֵ��desck��
extern int matrix_CHUNK_w16_multiply_empty_add(CHUNK *desck,CHUNK *souck,UINT32 multby);//��desck�ƿգ�����souck��������ֵ��desck��
extern int matrix_CHUNK_w32_multiply_empty_add(CHUNK *desck,CHUNK *souck,UINT32 multby);//��desck�ƿգ�����souck��������ֵ��desck��

extern int matrix_CHUNKGROUP_set_data(CHUNKGROUP *ckgroup,CHUNK *chunklist,int size);//����chunk���б�
extern int matrix_CHUNKGROUP_add_CHUNK(CHUNKGROUP *ckgroup,CHUNK *CHUNK);//��CHUNKGROUP�м���CHUNK
extern int matrix_CHUNKGROUP_del_CHUNK(CHUNKGROUP *ckgroup,int index);//ɾ��index��

//��Ϣ����
//�����������
//colsnumΪϣ����˵������������Ϊgroupnum��src_id�б���group�ж�Ӧ��chunk��
extern DOTINF matrix_DOTINF_create_NULL();//����һ��dotinf
extern int matrix_DOTINF_set_data(DOTINF *dotin,int *src_ids,int linenum,int colsnum,int packetsize,int parityTF);//����dotinf����

extern ERASES matrix_ERASES_create_NULL();//����һ���յ�ERASES
extern int matrix_ERASES_set_data(ERASES *erarray,int *eras,int codenum,int datanum);///����ERASES����

extern ENDECODEPARA matrix_ENDECODEPARA_create_NULL();//����һ���յ�papra
extern int matrix_ENDECODEPARA_set_data(ENDECODEPARA *endecpara,int w,INTMATRIX *matrix);//����para����

extern SCHEDOP matrix_SCHUDOP_create_NULL();//����һ��SCHUDOP
extern int matrix_SCHUDOP_set_data(SCHEDOP *schedop,int op,int sd,int sb,int dd,int db,int istareget,CHUNK *tarchunkptr,UINT64 chunkid);//����SCHUDOP����

extern SCHEDULE matrix_SCHEDULE_create_NULL();//����һ��SCHUDOP
extern int matrix_SCHEDULE_set_data(SCHEDULE *sched,SCHEDOP *schudlist,int size,int w);//����SCHEDULE����

extern DM_IDS matrix_DM_IDS_create_NULL();
extern int matrix_DM_IDS_set_data(DM_IDS *dmids,int *dmarr,int size);

//chunkgroup����������chunk��codechunk
//����
//RAID-5����һ�α���
extern int matrix_do_parity(CHUNKGROUP* ckgroup,CHUNK* parity);//����У����ʱУ���ǰ��Ϊ1
//ʹ�þ�����б���
//�����ֱ�����������ж�ȡ�����ʹ������Ҫ����ǰ����GROUP��Ϣ���и�ֵ
extern int matrix_matrix_encode(CHUNKGROUP *pargroup,CHUNKGROUP *ckgroup,INTMATRIX *matrix);//����INT�������//�����ֱ�����������ж�ȡ
extern int matrix_matrix_encode_BLOCK(CHUNKBLOCKGROUP *pargroup,CHUNKBLOCKGROUP *ckgroup,INTMATRIX *matrix);//chunkblock���б���
//ʹ��bit����б���
extern int matrix_bitmatrix_encode(CHUNKGROUP *pargroup,CHUNKGROUP *ckgroup,BITMATRIX *matrix,int packetsize);//����bitmatrix���б���
extern int matrix_bitmatrix_encode_BLOCK(CHUNKBLOCKGROUP *pargroup,CHUNKBLOCKGROUP *ckgroup,BITMATRIX *matrix,int packetsize);//BLOCK����У��
//ʹ��schedule���б���
extern int matrix_schedule_encode(CHUNKGROUP *pargroup,CHUNKGROUP *ckgroup,SCHEDULE *sched,int packetsize);
extern int matrix_schedule_encode_BLOCK(CHUNKBLOCKGROUP *pargroup,CHUNKBLOCKGROUP *ckgroup,SCHEDULE *sched,int packetsize);


//����RAID-6 stripsect����
extern int matrix_matrix_firstchunk_handle(CHUNK *parityptr,CHUNK *chunkptr,int curvalue,int w);
extern int matrix_matrix_notfirstchunk_handle(CHUNK *parityptr,CHUNK *chunkptr,int curvalue,int w);

extern int matrix_bitmatrix_encode_stripsect_RAID6(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr,BITMATRIX *matrix);//����cuachy RS��RDP��XOR��
extern int matrix_matrix_encode_stripsect_RAID6(STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparityptr,STRIPSECT *qparityptr,INTMATRIX *matrix);

extern int matrix_bitmatrix_encode_strip(STRIP *stripptr,BITMATRIX *matrix);
extern int matrix_matrix_encode_strip(STRIP *stripptr,INTMATRIX *matrix);

//IΪ���¼��㣬IIΪ����У������

extern int matrix_update_bitmatrix_pqparity_chunklist_create(int *pupdatelist,int *qupdatelist,
															CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,BITMATRIX *matrix);//�ҳ���ǰ��Ҫ���и��µ��б�
extern int matrix_update_bitmatrix_pqupdatenum_chunklist_create(int *pupdatelist1,int *pupdatelist2,
															int *qupdatelist1,int *qupdatelist2,
															CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
															STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,
															BITMATRIX *matrix);//�ҳ���ǰ��Ҫ���и��µ��б�
extern int matrix_bitmatrix_updateI_chunk_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition������Ҫ���µ�У����б�
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//��ǰ����������
											CHUNK *tarchunkptr,BITMATRIX *matrix,int chkindex);//Ŀ��У��飬����Ŀ�������				
extern int matrix_bitmatrix_updateII_chunk_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition������Ҫ���µ�У����б�
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//��ǰ����������
											CHUNK *tarchunkptr,BITMATRIX *matrix,int chkindex);//Ŀ��У��飬����Ŀ�������
extern int matrix_bitmatrix_updateI_stripsect_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,
											CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix);//RCWRAID6
extern int matrix_bitmatrix_updateII_stripsect_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,
											CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix);
extern int matrix_bitmatrix_update_stripsect_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,//
											CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix);//��ǰchunkblockgroup�е�������Ҫ��һ��strip��

extern int matrix_matrix_updateII_chunk_calcaulate(CHUNK *tarchunkptr,CHUNK *souchunkptr,int curvalue,int w);
//extern int matrix_update_matrix_pqparity_chunklist_create();//��RAID-6classic RS����������鶼Ҫ����
extern int matrix_update_matrix_pqupdatenum_chunklist_create(int *pupdatelist,int *qupdatelist,//updatelist��һ��Ϊ��һ���������ڶ���Ϊ�ڶ�����
															CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
															STRIPSECTBLOCKGROUP *strsetblockgroupptr,BITMATRIX *matrix);
extern int matrix_matrix_updateI_chunk_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition������Ҫ���µ�У����б�
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//��ǰ����������
											CHUNK *tarchunkptr,INTMATRIX *matrix,int chkindex);//Ŀ��У��飬����Ŀ�������
extern int matrix_matrix_updateII_chunk_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition������Ҫ���µ�У����б�
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//��ǰ����������
											CHUNK *tarchunkptr,INTMATRIX *matrix,int chkindex);//Ŀ��У��飬����Ŀ�������
extern int matrix_matrix_update_stripsect_RAID6(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,STRIPSECT *pparity,STRIPSECT *qparity,
											CHUNKBLOCKGROUP *parityblockgroupptr,INTMATRIX *matrix);//��ǰchunkblockgroup�е�������Ҫ��һ��strip��


extern int matrix_update_bitmatrix_parity_chunklist(int *updatelist,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
													BITMATRIX *matrix,int updatenum);//�ҳ���ǰ��Ҫ���и��µ��б�
extern int matrix_update_bitmatrix_updatenum_chunklist_create(int *updatelist1,int *updatelist2,
																CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
																STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
																BITMATRIX *matrix,int updatenum);//�������ַ�����updatelist
extern int matrix_bitmatrix_updateI_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition������Ҫ���µ�У����б�
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//��ǰ����������
											CHUNK *tarchunkptr,BITMATRIX *matrix,int chkindex);//Ŀ��У��飬����Ŀ�������
extern int matrix_bitmatrix_updateII_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition������Ҫ���µ�У����б�
											STRIPSECTBLOCKGROUP *strsetblockgroupptr,//��ǰ����������
											CHUNK *tarchunkptr,BITMATRIX *matrix,int chkindex);//Ŀ��У��飬����Ŀ�������
extern int matrix_bitmatrix_update_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										STRIP *stripptr,CHUNKBLOCKGROUP *parityblockgroupptr,BITMATRIX *matrix);


extern int matrix_update_matrix_parity_chunklist(int *updatelist,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,BITMATRIX *matrix,int updatenum);//�ҳ���ǰ��Ҫ���и��µ��б�,MSR��MBR������0
extern int matrix_update_matrix_updatenum_chunklist_create(int *updatelist1,int *updatelist2,
															CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
															STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
															BITMATRIX *matrix,int updatenum);//�������ַ�����updatelist
extern int matrix_matrix_updateI_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition������Ҫ���µ�У����б�
										STRIPSECTBLOCKGROUP *strsetblockgroupptr,//��ǰ����������
										CHUNK *tarchunkptr,INTMATRIX *matrix,int chkindex);//Ŀ��У��飬����Ŀ�������
extern int matrix_matrix_updateII_chunk(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,//chunkposition������Ҫ���µ�У����б�
										STRIPSECTBLOCKGROUP *strsetblockgroupptr,//��ǰ����������
										CHUNK *tarchunkptr,INTMATRIX *matrix,int chkindex);//Ŀ��У��飬����Ŀ�������
extern int matrix_matrix_update_strip(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr,
										STRIP *stripptr,CHUNKBLOCKGROUP *parityblockgroupptr,INTMATRIX *matrix);

extern int matrix_matrix_calculate_share(BITMATRIX *matrixptr,CODEPARA *codeptr,AONTSHAREGROUP *sharegroupptr,int sharesize);//����bit�����share
//����
//����raid-5
extern int matrix_do_deparity(CHUNKGROUP *ckgroup,CHUNK *lost,int TFparity);//������Ӧ�Ķ�ʧ�飬TFparity��ָ���ɿ��ǲ���У���
//matrix����
extern int matrix_matrix_decode(CHUNKGROUP *lostgroup,CHUNKGROUP *ckgroup,INTMATRIX *matrix,ERASES *erarray);//ʹ�þ�����н���
extern int matrix_matrix_decode_BLOCK(CHUNKBLOCKGROUP *laostgroup,CHUNKBLOCKGROUP *ckgroup,INTMATRIX *matrix,ERASES *erarry);// ����������
//bitmatrix����
extern int matrix_bitmatrix_decode(CHUNKGROUP *lostgroup,CHUNKGROUP *ckgroup,BITMATRIX *matrix,ERASES *erarray);//����bit��ǰ��ʧ�����ݿ�
extern int matrix_bitmatrix_decode_BLOCK(CHUNKBLOCKGROUP *lostgroup,CHUNKBLOCKGROUP *ckgroup,BITMATRIX *matrix,ERASES *errarry);//ʹ��bit����
//scheudle���뷽��
extern int matrix_schedule_decode_lazy();//��Plank����ӿں���
extern int matrix_schedule_decode_cache();

//������Ӧ�������
extern int matrix_make_decoding_matrix_only(INTMATRIX *decoding_matrix,INTMATRIX *matrix,ERASES *erarray);//������Ҫ����matrix�������
extern int matrix_make_decoding_matrix(INTMATRIX *decoding_matrix,INTMATRIX *matrix,ERASES *erarray,DM_IDS *dmids);//����matrix�����������������ID��

extern int matrix_make_decoding_bitmatrix_only(INTMATRIX *decoding_matrix,INTMATRIX *matrix,ERASES *erarray);//������Ҫ����bitmatrix�������
extern int matrix_make_decoding_bitmatrix(BITMATRIX *decoding_matrix,BITMATRIX *matrix,ERASES *erarray,DM_IDS *dmids);//����bitmatrix�����������������ID��

//����erases����
extern int matrix_make_decoding_chunkblockgroup(CHUNKBLOCKGROUP *tarchunkptr,CHUNKBLOCKGROUP *souchunpptr,ERASES *erarry);//������Ӧ��ɾchunkblockgroup

//��˴�ȫ
//desid������������,���һ��
extern int matrix_matrix_dotprod_BLOCK(INTMATRIX *matrix,CHUNKBLOCKGROUP *ckgroup,CHUNK *parchunk,DOTINF *dotin);
extern int matrix_matrix_dotprod(INTMATRIX *matrix,CHUNKGROUP *chkgroup,CHUNK *parchunk,DOTINF *dotin);//�����

extern int matrix_bitmatrix_dotprod_BLOCK(BITMATRIX *matrix,CHUNKBLOCKGROUP *ckgroup,CHUNK *parchunk,DOTINF *dotin);
extern int matrix_bitmatrix_dotprod(BITMATRIX *matrix,CHUNKGROUP *chkgroup,CHUNK *parchunk,DOTINF *dotin);

extern int matrix_do_scheduled_operations_BLOCK(SCHEDULE *sch,CHUNKBLOCKGROUP *ckgrpup,CHUNK *parchunk,DOTINF *dotin);
extern int matrix_do_scheduled_operations(SCHEDULE *sch,CHUNKGROUP *chkgroup,CHUNK *parchunk,DOTINF *dotin);

//BITMATRIXת������
extern int matrix_matrix_to_bitmatrix(INTMATRIX *matrix,BITMATRIX *bitmatrix);//��INTMATRIX����һ��BITMATRIX
extern int matrix_dumb_bitmatrix_to_schedule(BITMATRIX *matrix,SCHEDULE *sch);//����ת������
extern int matrix_smart_bitmatrix_to_schedule(BITMATRIX *matrix,SCHEDULE *sch); 
extern int matrix_generate_schedule_cache(BITMATRIX *matrix,int smart);

extern int matrix_free_schedule(SCHEDULE *sch);
extern int matrix_free_cache(CACHE *cah);

//����ͳ��
extern int matrix_get_stats(STATSITEM *fill_in);//��ȡϵͳͳ������
#endif
