function[output]=average(t)
%output1=zeros(1,20);
output1=0;
for i=1:1:1000
    output1=output1+DFNC3(t);
end
output=output1/1000;
    