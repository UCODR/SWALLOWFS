clear all

file32ptr=fopen('output32.txt','r');
file64ptr=fopen('output64.txt','r');
file128ptr=fopen('output128.txt','r');
file256ptr=fopen('output256.txt','r');
file512ptr=fopen('output512.txt','r');
str32=fscanf(file32ptr,'%s\n');
str64=fscanf(file64ptr,'%s\n');
str128=fscanf(file128ptr,'%s\n');
str256=fscanf(file256ptr,'%s\n');
str512=fscanf(file512ptr,'%s\n');
mivalue=100000;
maxvalue=0;
sumvalue=0;
%先统计每一个region的最大值最小值均

%重新读取

for i=1:5%5个组合起来
    for j=1:5
        for k=1:3%三种不同参数
            [number32str,remain32str]=strtok(str32,',');
            [number64str,remain64str]=strtok(str64,',');
            [number128str,remain128str]=strtok(str128,',');
            [number256str,remain256str]=strtok(str256,',');
            [number512str,remain512str]=strtok(str512,',');
            number(1)=str2num(number32str);
            number(2)=str2num(number64str);
            number(3)=str2num(number128str);
            number(4)=str2num(number256str);
            number(5)=str2num(number512str);
            if k==1
                 regionvalue(i,j,k,:)=number;
            end
            if k==2
                regionvalue(i,j,k,:)=number;
            end
            if k==3
                regionvalue(i,j,k,:)=number;
            end
            str32=remain32str(2:end);
            str64=remain64str(2:end);
            str128=remain128str(2:end);
            str256=remain256str(2:end);
            str512=remain512str(2:end);
        end
    end 
end
%开始找数据
for i=1:5
    for j=1:5
        minchunkvalue(i,j)=min(regionvalue(i,j,1,:));
        maxchunkvalue(i,j)=max(regionvalue(i,j,2,:));
        avgchunkvalue(i,j)=mean(regionvalue(i,j,3,:));
        minupdatevalue(i,j)=min(regionvalue(i,:,1,j));
        maxupdatevalue(i,j)=max(regionvalue(i,:,2,j));
        avgupdatevalue(i,j)=mean(regionvalue(i,:,3,j));
    end
end
dlmwrite('minchunkvalue.txt',minchunkvalue);
dlmwrite('maxchunkvalue.txt',maxchunkvalue);
dlmwrite('avgchunkvalue.txt',avgchunkvalue);
dlmwrite('minupdatevalue.txt',minupdatevalue);
dlmwrite('maxupdatevalue.txt',maxupdatevalue);
dlmwrite('avgupdatevalue.txt',avgupdatevalue);
    
