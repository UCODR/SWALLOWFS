@echo 开始注册
copy pthreadvc2.dll %windir%\system32\
regsvr32 %windir%\system32\pthreadvc2.dll /s
@echo pthreadvc2.dll注册成功
@pause