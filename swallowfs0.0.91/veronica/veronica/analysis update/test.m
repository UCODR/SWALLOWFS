clear all
dataregionvalue=open('dataregionvalue.mat');
dataregionvalue=dataregionvalue.regionvalue;
schregionvalue=open('schregionvalue.mat');
schregionvalue=schregionvalue.regionvalue;

for i=1:5
    datachunkvalue(i)=mean(mean(dataregionvalue(:,i,3,:)));
    schchunkvalue(i)=mean(mean(schregionvalue(:,i,3,:)));
    
    dataupdatevalue(i)=mean(mean(dataregionvalue(:,:,3,i)));
    schupdatevalue(i)=mean(mean(schregionvalue(:,:,3,i)));
    
    datacodetype(i)=mean(mean(dataregionvalue(i,:,3,:)));
    schcodetype(i)=mean(mean(schregionvalue(i,:,3,:)));
end
x=[1:5]

plot(x,datachunkvalue,'r--o',x,schchunkvalue,'b--x','markersize',10);
xlabel('块大小');
ylabel('更新时间');
legend('数据块更新','调度更新');
figure

plot(x,dataupdatevalue,'r--o',x,schupdatevalue,'b--x','markersize',10);
xlabel('更新大小');
ylabel('更新时间');
legend('数据块更新','调度更新');
figure

plot(x,datacodetype,'r--o',x,schcodetype,'b--x','markersize',10);
xlabel('编码类型');
ylabel('更新时间');
legend('数据块更新','调度更新');