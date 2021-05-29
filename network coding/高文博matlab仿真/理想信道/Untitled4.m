throughput1=zeros(1,10);
for i=0:1:10
    throughput1(i+1)=amatlab(i*10);
    throughput11(i+1)=amatlab1(i*10);
    throughput111(i+1)=amatlab2(i*10);
end
throughput2=[0,0.2693 , 0.3515, 0.3872, 0.4235,  0.4343, 0.4423, 0.4472, 0.459, 0.464,0.466];
throughput22=[0 ,0.2816, 0.3816, 0.4145, 0.4482, 0.4687, 0.4724, 0.4796, 0.4913,0.4925, 0.4922];
throughput222=[0 ,0.2952,  0.4112 , 0.4390, 0.4763, 0.5019, 0.5033,  0.5104, 0.5266,0.5233, 0.5241];
x=0:10:100;
plot(x,throughput1,'r*');
hold on;
plot(x,throughput11,'b*');
hold on;
plot(x,throughput111,'k*');
hold on;
plot(x,throughput2,'r<-');
hold on;
plot(x,throughput22,'b<-');
hold on;
plot(x,throughput222,'k<-');
hold on;