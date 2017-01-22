#ifndef _PROFILE_H
#define _PROFILE_H
#include "file.h"
#include "FILELAYER.h"
#include "global_define.h"
#include "matrix.h"
//updateelemnent��chunkptr
extern int profile_updateelement_updatelist_countnum(int *updatelist,int updatenum);
extern CHUNK *profile_updateelement_chunk_ptr(UPDATEELEMENT *updateelementptr);
extern CHUNK *profile_updateelement_temp_chunk_ptr(UPDATEELEMENT *updateelementptr);
//�жϵ�ǰupdateelement����
extern int profile_updateelement_bitelement_equal(UPDATEELEMENT *updateelementptr,BITELEMENT *bitelementptr);
extern int profile_updateelement_updateelement_equal(UPDATEELEMENT *tarupdateelementptr,UPDATEELEMENT *souupdateelementptr);

extern UPDATEELEMENT *profile_updateelement_search_ptr(UPDATEELEMENTGROUP *updateelementgroupptr,int stripsectindex,int chunkindex);//�������ǰ��updateelement
extern int profile_updateelement_is_exist(UPDATEELEMENTGROUP *updateelementgroupptr,int stripsectindex,int chunkindex); //�ж�һ��Ԫ���ڲ���updateelement����

//bitelemet��updateelement֮��ľ���
extern int profile_matrix1_matrix2_update_distance(BITMATRIX *matrix1,BITMATRIX *matrix2,BITMATRIX *readmapmatrix);

extern int profile_updateelement_updatelement_updateI_distance(UPDATEELEMENT *tarupdateelement,UPDATEELEMENT *souupdateelement,BITMATRIX *readmapmatrix);
extern int profile_updateelement_updatelement_updateII_distance(UPDATEELEMENT *tarupdateelement,UPDATEELEMENT *souupdateelement,BITMATRIX *readmapmatrix);
extern int profile_updateelement_updatelement_distance(UPDATEELEMENT *tarupdateelement,UPDATEELEMENT *souupdateelement,BITMATRIX *readmapmatrix);//��������updateelement�ľ��룬����souupdateelementΪԴģʽ�������뵱ǰ�������

extern int profile_updateelememt_bitelement_updateI_distance(UPDATEELEMENT *tarupdateelement,BITELEMENT *soubitelement,BITMATRIX *readmapmatrix);//����updateelement�ľ���
extern int profile_updateelememt_bitelement_updateII_distance(UPDATEELEMENT *tarupdateelement,BITELEMENT *soubitelement,BITMATRIX *readmapmatrix);//����updateelement�ľ���
extern int profile_updateelememt_bitelement_distance(UPDATEELEMENT *tarupdateelement,BITELEMENT *soubitelement,BITMATRIX *readmapmatrix);//����updateelement�ľ���
//���㵱ǰ�ڴ��ͼ
extern int profile_memory_map_is_exist(BITMATRIX *readmapmatrixptr,int stripsectindex,int chunkindex);//�ж�һ��Ԫ���ڲ����ڴ��ͼ��
extern int profile_memory_map_add_element(BITMATRIX *readmapmatrixptr,int stripsectindex,int chunkindex);//���ڴ��ͼ�м���һ��Ԫ��

//����ʱ���϶
extern double profile_calculate_time_diff(long starttick,long endtick);//����sec����
//����ȫ��element,����rowsindex��colsindex��ָ��read map�е�λ��
extern int profile_bitelement_dataelement(int stripsectindex,int chunkindex,BITELEMENT *bitelementptr,BITMATRIX *matrix,REGION *regionptr);//������Ӧ�����ݿ�ģʽ
extern int profile_bitelement_codeelement(int stripsectindex,int chunkindex,BITELEMENT *bitelementptr,BITMATRIX *matrix,REGION *regionptr);//��������һ�н��п���

//����ȫ�ִ���ģʽ
extern int profile_create_global_errorpattern(ERRORPATTERN *errormatrix);
extern int profile_set_disk_available_state();
extern int profile_create_global_errorpattern_global_errorpattern(ERRORPATTERN *errormatrix);
//�����˹�����
extern int profile_set_global_disk_error(ERRORPATTERN *errormatrix);

//������Ӧ�ĵ�ͼ//����countnum����1,0������
extern int profile_create_memory_map(BITMATRIX *matrix,STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
									STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,int *countnum,REGION *regionptr);
extern int profile_create_memory_map_RAID6(BITMATRIX *matrix,STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,
									STRIPSECT *pparity,STRIPSECT *qparity,int *countnum,REGION *regionptr);

//�ָ��
extern int profile_strip_into_stripsect_ptr(STRIPSECTBLOCKGROUP *datastrsetblockgroupptr,STRIPSECTBLOCKGROUP *codestrsetblockgroupptr,STRIP *stripptr);

//�ж�һ�����ǲ�������
extern int profile_is_prime(int w);//�жϵ�ǰ�������ǲ�������
extern int profile_next_prime(int datanum);//��ȡ֮����Ե�һ������
//�������ҳ���ǰchunk��λ��
extern int profile_chunk_to_chunkposition_ptr(CHUNKPOSITIONBLOCK *chunkpositionblockptr,CHUNK *chunkptr);//ͨ��ָ�����ж�λ��
//�鴦����
extern int profile_chunk_should_read(CHUNK *chunkptr);//�ж�һ��chunk���Ҫ��ȡ�ǲ�����Ҫ��Ӳ�̶�
extern int profile_chunk_create_empty_data(CHUNK *chunkptr);//����һ���տ�
extern int profile_chunk_data_read(CHUNK *chunkptr);//������ݲ����ڴ潫chunkdataͬ�����ݵ��ڴ棬���û��д����һ���տ�

//�ж�һ��chunk�Ƿ�ΪΪ��
extern int profile_chunk_data_haswrited(CHUNK *chunkptr);
extern int profile_chunk_data_isfree(CHUNK *chunkptr);
//����һ����REGION
extern int profile_region_setup_without_filemeta(REGION *regionptr,int codetype,CODEPARA *codepara,STRIPDES *strdes,UINT64 totalsize,
										UINT64 *glodeviceidlist,DEVICEBLOCK *glodeviceblockptr,int devicenum,
										UINT64 *glodiskidlist,DISKBLOCK *glodiskblockptr,int disknum);//����region���ҽ��и�ʽ��
extern int profile_region_setup_rootdictionary_filemeta(FILEMETA *rootdicptr,char *filename,USERPROFILE *userprofileptr,REGION *regionptr);//������Ӧ��rootdictionary
extern int profile_region_setup(REGION *regionptr,int codetype,CODEPARA *codepara,STRIPDES *strdes,UINT64 totalsize,
								UINT64 *glodeviceidlist,DEVICEBLOCK *glodeviceblockptr,int devicenum,
								UINT64 *glodiskidlist,DISKBLOCK *glodiskblockptr,int disknum,
								char *filename,USERPROFILE *userprofileptr);//���㵱ǰ������

//�������½�ƫ����
extern int profile_update_startoffset(int chunksize,int offset);//����firstoffset
extern int profile_update_lastoffset(int chunksize,int offset,int updatesize);//����lastoffset

//�ͷſռ�
extern int profile_free_chunk_data(CHUNK *chunkptr);
extern int profile_free_chunkgroup_data(CHUNKGROUP *chunkgroupptr);
extern int profile_free_chunkblockgroup_data(CHUNKBLOCKGROUP *chunkblockgroupptr);
extern int profile_free_chunkpositionblockgroup_data(CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgrouipptr);

extern int profile_tempfree_chunk_ptr(CHUNK *chunkptr);//�����ݿ��¼��tempreelist
extern int profile_tempfree_chunkblock_ptr(CHUNKBLOCKGROUP *chunkblockgroupptr);//�����ݿ����¼��tempfreelist
extern int profile_tempfree_free();//�ͷŵ�ǰ��free�б�

//���㺯��
extern int profile_mod_number(int m,int n);//������(������)��m mod n��

//��Ҫ��Ҫ��ʼ���Ĳ���,��ʾ��ͬ��Ϣ
extern int profile_chkpath_to_chunk_stripsectnum(CHUNKPATH *chkpathptr);//��ǰchunk����stripsec�е�λ��
extern int profile_chkpath_to_chunk_stripnum(CHUNKPATH *chkpathptr);//��ǰchunk����stripsec�е�λ��
extern int profile_chkpath_to_chunk_regionnum(CHUNKPATH *chkpathptr);//��ǰchunk����stripsec�е�λ��

extern int profile_chkpath_to_stripsect_stripnum(CHUNKPATH *chkpathptr);//��ǰchunk���ڵ�stripsect��strip�е�λ��
extern int profile_chkpath_to_stripsect_regionnum(CHUNKPATH *chkpathptr);//��ǰchunk���ڵ�stripsect��region�е�λ��

extern int profile_chkpath_to_strip_regionnum(CHUNKPATH *chkpathptr);//��ǰchunk���ڵ�strip��region�е�λ��

//ת������
extern int profile_stripblock_to_datachunkblock(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr);//����ǰ�������е�data chunk������ȡ
extern int profile_stripblock_to_paritychunkblock(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr);//����ǰ�������е�parity datachunk������ȡ
extern int profile_chunkblock_to_stripblock(STRIPBLOCKGROUP *stripblockgroupptr,CHUNKBLOCKGROUP *chunkblockgroupptr);//�ҳ�chunkblock��Ӧ��stripblock

//����ָ��
extern int profile_chunkblockpositiongroup_from_chunkblockpositiongroup_search_ptr(CHUNKPOSITIONBLOCKGROUP *tarchunkblockpositiongroupptr,
																		CHUNKPOSITIONBLOCKGROUP *souchunkpositionblockgroupptr,
																		STRIP *stripptr);//��chunkpositionblockgroup�ҵ���Ӧstrip��chunk���ҽ�����д������TRUE��FALSE

extern int profile_chunkblockstripgroup_search_ptr(CHUNKBLOCKSTRIPGROUP *chunkblockstripgroupptr,STRIP *stripptr);//�ҵ���Ӧ��strip������
extern int profile_stripblockgroup_search_ptr(STRIPBLOCKGROUP *stripblockgroupptr,STRIP *stripptr);//��stripptr��ָ������λ�ã�û�ҵ�����-1
extern int profile_stripsectblockgroup_search_ptr(STRIPSECTBLOCKGROUP *stripsetblockgroupptr,STRIPSECT *stripsectptr);//��stripptr��ָ������λ�ã�û�ҵ�����-1
extern int profile_chunkblockgroup_search_ptr(CHUNKBLOCKGROUP *chunkblockgroupptr,CHUNK *chunkptr);//��chunkptr��ָ������λ�ã�û�ҵ�����-1

extern int profile_region_filemeta_add(REGION *regionptr,FILEMETA *filemetaptr);
//������������ʹ��ǰ��ҪԤ�ȷ���ռ�
extern int profile_stripblockstripgroup_chunk_add(CHUNKBLOCKSTRIPGROUP *chunkblockstripgroupptr,CHUNK *chunkptr,STRIP *stripptr);//���㵱ǰ
extern int profile_stripblockgroup_strip_add(STRIPBLOCKGROUP *stripblockgroupptr,STRIP *stripptr);//��stripblockgroupptr�м���һ��strip
extern int profile_stripsetblockgroup_stripsect_add(STRIPSECTBLOCKGROUP *stripsectblockgrouptr,STRIPSECT *stripsectptr); //��stripsectblockgroupptr�м���һ��stripsect
extern int profile_chunkblockgroup_chunk_add(CHUNKBLOCKGROUP *chunkblockgroupptr,CHUNK *chunkptr);//��chunkblockgroupptr�м���һ��chunk

//���洢��Ϣ��������
extern int profile_set_file_storage_information(FILEINF *fileinfptr,
												CHUNKBLOCKGROUP *chunkblockgroupptr,STRIPSECTBLOCKGROUP *stripsectblockgroupptr,
												STRIPBLOCKGROUP *stripblockgroupptr,REGION *regionptr,
												CHUNKPATH *chunkpathlist,FILEMETA *filemetaptr
												);
//�����ļ�����һ��ָ��
extern int profile_set_parent_filemeta_ptr(FILEMETA *filemetaptr);

//��������,�����ݴ�ȫ���б����ҳ�ָ��

extern int profile_filemeta_filemetablock_search(FILEMETABLOCK *filemetablockptr,UINT64 *fileidlist,int filenum,FILEMETABLOCKGROUP *filemetablockgroupptr);

extern int profile_chunk_chunkpath_search(CHUNKBLOCK *chunkblockptr,UINT64 *chunkidlist,CHUNKPATH *chkpathptr,int chunknum);
extern int profile_stripsect_chunkpath_search(STRIPSECTBLOCK *stripsectblockptr,UINT64 *stripsectidlist,int stripsectnum,CHUNKPATH *chkpathptr,int chunknum);
extern int profile_strip_chunkpath_search(STRIPBLOCK *stripblockptr,UINT64 *stripidlist,int stripnum,CHUNKPATH *chkpathptr,int chunknum);

extern USERPROFILE *profile_get_usergroup_ptr(UINT64 userid,USERGROUP *usergroupptr);

extern FILEMETA *profile_get_filemetablock_ptr(UINT64 fileid,FILEMETABLOCKGROUP *filemetablockgroupptr);//�ҵ���Ӧ��filemeta



extern CHUNK *profile_get_chunkblock_ptr(UINT64 chunkid,CHUNKBLOCKGROUP *chunkblockgroupptr);//�ҵ���Ӧchunk
extern CHUNK *profile_get_chunkposition_ptr(int stripsectindex,int chunkindex,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr);//�ҳ���ǰstripsectnum��chunknum��ָ��
extern int profile_search_chunkposition_id(int stripsectindex,int chunkindex,CHUNKPOSITIONBLOCKGROUP *chunkpositionblockgroupptr);//�ҳ���ǰstripsectnum��chunknum�ı��
extern UINT64 profile_get_region_id(char *filepath);//����id��
extern REGION *profile_region_search_ptr(UINT64 regionid);//���ҵ�ǰregionid��REGIONָ��

extern int profile_device_search(DEVICEBLOCK *deviceblockptr,UINT64 *deviceidlist,int devicenum);//�ҵ���ǰid�б���deviceָ��
extern int profile_disk_search(DISKBLOCK *diskblockptr,UINT64 *diskidlsit,int disknum);//�ҵ���ǰid�б��е�diskָ��
extern int profile_region_search(REGION *regionptr);//����region��
extern DEVICE *profile_device_ptr_search(UINT64 deviceid,DEVICEBLOCK *deviceblockptr,int devicenum);//�ҵ���ǰ�б���deviceid
extern DISK *profile_disk_ptr_search(UINT64 diskid,DISKBLOCK *diskblockptr,int disknum);//�ҵ���ǰ�б���deviceid


//��ʾʵ������
extern int profile_region_info_ID(UINT64 regionid);//����regionid��ʾ����
extern int profile_region_info(REGION *regionptr);//����regionָ����ʾ����
extern int profile_strip_info(STRIP *stripptr);//����stripָ����ʾ����
extern int profile_stripsect_info(STRIPSECT *stripsectptr);//����stripsectָ����ʾ����
extern int profile_chunk_info(CHUNK *chunkptr);//����chunkָ����ʾ����
extern int profile_disk_info(DISK *diskptr);//����diskָ����ʾ����
extern int profile_device_info(DEVICE *deviceptr);//����deviceָ����ʾ����
extern int profile_filemeta_info(FILEMETA *filemetaptr);//����filemetaָ����ʾ����
extern int profile_userprofile_info(USERPROFILE *useprofileptr);//����useprofileָ����ʾ����

extern int profile_global_define_reader();//��ȫ�ֶ������ݶ���

extern int profile_region_reader();//��ȡȫ������Ԫ����
extern int profile_userprofile_reader();//��ȡȫ���û���Ϣ
extern int profile_device_reader();//��ȡ�豸Ԫ����
extern int profile_disk_reader();//��ȡ�洢��Ԫ����
extern int profile_dirtydata_intial();//��ʼ��dirtydata������
//���������Ϊ����
extern int profile_map_define_intial(REGION *regionptr);//����region�е�raid�����������޸���Ӧ��У����Ϣ


extern int profile_device_disk_setup(DEVICE *deviceptr,DISK *diskptr,int index);//����device�Լ�diskָ���ϵ

extern int profile_region_format_PTR(REGION *regionptr);//��ʽ��regionָ������
extern int profile_region_reader_PTR(REGION *regionptr);//��ȡ��ǰregion����


extern int profile_chunk_fileinf(CHUNKBLOCK *chunkblockptr,FILEMETA *filemetaptr,int chunknum);

extern int profile_setup_file_fullchkpath(CHUNKPATH *chkpathptr,REGION *regionptr);

extern int profile_setup_parent_subfile_relation(FILEMETA *parentptr,FILEMETABLOCK *subfileblockptr,int subfilenum);
extern int profile_setup_file_dictionaryinformation(FILEMETA *filemetaptr,FILEMETABLOCKGROUP *filemetablockgroupptr);
extern int profile_setup_file_chunkinformation(FILEMETA *filemetaptr);
extern int profile_setup_file_diskinformation(FILEMETA *filemetaptr);
extern int profile_setup_file_deviceinformation(FILEMETA *filemetaptr);
extern int profile_setup_file_userinformation(FILEMETA *filemetaptr);
extern int profile_setup_file_storeinformation(FILEMETA *filemetaptr);//����ǰ��
extern int profile_region_read_filemeta(REGION *regionptr);//����Ԫ�����ļ������ļ���Ϣ���ã��ļ�ϵͳ�߼��ṹ
//��Ҫ�ֳ���������1.�趨ȫ��Ԫ����·��2.����ȫ���ļ��ṹ3.����ȫ�ֵĿ�ṹ
//��ʼ��regionϵͳ����
extern int profile_global_system_intial_basic();//��ʼ����������
extern int profile_global_region_intial(REGION *regionptr);//ͨ��regionptr�����ݳ�ʼ��
extern int profile_global_region_intial_without_datafile(REGION *regionptr);//ͨ��regionptr�����ݳ�ʼ��
extern int profile_global_system_intial();//��ʼ��ȫ�ֽӿ�
extern int profile_global_system_intial_without_datafile();//��ʼ��ȫ�ֽӿ�

extern int profile_set_global_metapath(char *filename);//�ӵ�ǰĿ¼���ļ�����Ԫ�����ļ���λ��


extern int profile_globaldefine_sync();//gloabl-defineͬ��
extern int profile_region_sync(REGION *regionptr);//region�ṹԪ����ͬ�������� 
extern int profile_filemeta_sync(REGION *regionptr);//���ļ�Ԫ����ͬ��
extern int profile_device_disk_sync();//��device��diskԪ����ͬ��������
extern int profile_userprofile_sync();//�û���Ϣͬ����
extern int profile_GLOBAL_chunk_data_sync();//����Ԫ�����ļ��е�chunk������

extern int profile_metadata_sync();//Ԫ����ͬ��

//�����������б�
extern int profile_dirtydata_set_data(CHUNKBLOCK *chunkblockptr,int chunknum,//chunk����
										STRIPSECTBLOCK *stripsectblockptr,int stripsectnum,//stripsect����
										STRIPBLOCK *stripblockptr,int stripnum,//strip����
										REGIONBLOCK *regionblockptr,int regionnum,//region����
										FILEMETABLOCK *filemetablockptr,int filemtetanum,//file����
										DEVICEBLOCK *deviceblockptr,int devicenum,//device����
										DISKBLOCK *diskblockptr,int disknum,//disk����
										USERBLOCK *userblockptr,int usernum//user����
										);//�趨ȫ��������

//8��������ͬ������
extern int profile_dirtydata_region_sync();//region������ͬ��
extern int profile_dirtydata_strip_sync();//strip������ͬ��
extern int profile_dirtydata_stripsect_sync();//stripsect������ͬ��
extern int profile_dirtydata_chunk_sync();//chunk������ͬ��
extern int profile_dirtydata_device_sync();//device������ͬ��
extern int profile_dirtydata_disk_sync();//disk������ͬ��
extern int profile_dirtydata_userprofile_sync();//userprofile������ͬ��
extern int profile_dirtydata_filemeta_sync();//filemeta������ͬ��

extern int profile_dirtydata_sync();//����������ͬ��


extern int profile_update_allocate_chunkstate(CHUNKPATH *chkpath);//�������chunkstate
extern int profile_update_free_chunkstate(CHUNKPATH *chkpath);//�ͷŸ���chunkstate

extern CHUNKPATH *profile_allocate_chunk_data(REGION *regionptr);//������㷨,������Ӧ�Ŀ�·��
extern int profile_free_chunk_ptr(CHUNKPATH *chkpath);//�ͷ�һ����

extern int profile_setup_file_ptr(FILEMETA *perantptr,FILEMETA *curfileptr);//������Ӧ�ĵ�ָ��
extern int profile_add_file_to_region(FILEMETA *perantptr,FILEMETA *curfileptr,REGION *regiomptr);//��һ��ԭʼregion��û�е��ļ�����region�У����ҽ�����Ӧ��perant��ָ��
extern int profile_add_file_chunkblock_to_region(FILEMETA *perantptr,FILEMETA *curfileptr,CHUNKBLOCKGROUP *chunkblockgroupptr,REGION *regionptr);//��һ��ԭʼregion��û�е��ļ�����region�У����ҽ�����Ӧ��perant��ָ�룬������chunkblockgroup֮��Ĺ�ϵ
#endif