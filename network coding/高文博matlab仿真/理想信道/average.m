function[output]=average(t)
%output1=zeros(1,20);
output1=0;
for i=1:1:500
    output1=output1+asymmetry6(t);
end
output=output1/500;