function [ output ] = COUNT1(data1,data2,databits)
A=length(data1)/databits;
output=0;
for i=1:A
    ndata1=data1(:,(100*(i-1)+1):100*i);
    ndata2=data2(:,(100*(i-1)+1):100*i);
    if biterr(ndata1,ndata2) == 0
        output=output+1;
    end        
end   
end
