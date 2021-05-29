throughput1=zeros(1,101);
for i=1:1:101
    throughput1(i)=asymmetry6(i);
end
x=0:1:100;
plot(x,throughput1,'r*');
hold on;