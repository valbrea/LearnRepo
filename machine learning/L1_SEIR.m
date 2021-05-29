clear all;
close all;
alpha=0.008;
gamma=0.01;
I=10;
S=1000;
N=1000;%开始数量
R0=4;
beida=R0/N*gamma;
I(1)=10;
E(1)=0;
R(1)=0;
S(1)=N-I(1);
T=1200;%5天
t=(0:T)/24;
for ii=1:T
    S(ii+1)=S(ii)-beida*I(ii)*S(ii);
    E(ii+1)=E(ii)+beida*I(ii)*S(ii)-alpha*E(ii);
    I(ii+1)=I(ii)+alpha*E(ii)-gamma*I(ii);
    R(ii+1)=R(ii)+gamma*I(ii);
end
figure,hold on;
plot(t,S,'b');plot(t,E,'k');plot(t,I,'r');plot(t,R,'g');
legend('Susceptible','Exposed','Infectors','Removed');