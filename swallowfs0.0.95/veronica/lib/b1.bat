@echo ��ʼע��
copy pthreadvc2.dll %windir%\system32\
regsvr32 %windir%\system32\pthreadvc2.dll /s
@echo pthreadvc2.dllע��ɹ�
@pause