throughput1=zeros(1,31);
throughput11=zeros(1,31);
throughput2=zeros(1,31);
throughput22=zeros(1,11);
%for i=1:1:31
%    throughput11(i)=Noerror5(i);
%end
for j=0:40:400;
    throughput22(j/40+1)=amatlab(j);
end
x=0:40:400;
%plot(x,throughput1,'r*');
hold on;
%plot(x,throughput11,'r<');
hold on;
%plot(x,throughput2,'b^-');
hold on;
plot(x,throughput22,'b^--');
%hold on;
xlabel('Timeslots');
ylabel('Throughput(packets/timeslot])');
