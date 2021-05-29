clear all
close all
%% MFs
x=(0:0.1:10);
y1=trapmf(x,[0,0,2,5]);
y2=trimf(x,[0,5,10]);
y3=trapmf(x,[5,8,10,10]);
figure(1)
plot(x,y1); hold on
plot(x,y2); hold on
plot(x,y3); 
legend('Near,Low','Moderate','Far,High');
axis([0 10 0 1.5]);title ('Antecedents MFs');
 
z1=trapmf(x,[0,0,1,3]);
z2=trimf(x,[1,3,5]);
z3=trimf(x,[3,5,7]);
z4=trimf(x,[5,7,9]);
z5=trapmf(x,[7,9,10,10]);
 
figure(2)
plot(x,z1); hold on
plot(x,z2); hold on
plot(x,z3); hold on
plot(x,z4); hold on
plot(x,z5); 
legend('Very Weak','Weak','Medium','Strong','Very Strong');
axis([0 10 0 1.5]);title ('Consequent MFs');
%% singleton Fuzzy filter
%x1=(0:0.1:10);
x1=[4,8];
x2=(0:0.1:10);
x3=(0:0.1:10);
 
 
%% firing level for each rule(product implication and product t-norm)
N=length(x2);
%N=N*N;
R=zeros(N,N,27);
 
near(1)=trapmf(x1(1),[0,0,2,5]);
near(2)=trapmf(x1(2),[0,0,2,5]);
moderate1(1)=trimf(x1(1),[0,5,10]);
moderate1(2)=trimf(x2(1),[0,5,10]);
far(1)=trapmf(x1(1),[5,8,10,10]);
far(2)=trapmf(x1(2),[5,8,10,10]);
 
low2=trapmf(x2,[0,0,2,5]);
moderate2=trimf(x2,[0,5,10]);
high2=trapmf(x2,[5,8,10,10]);
 
low3=trapmf(x3,[0,0,2,5]);
moderate3=trimf(x3,[0,5,10]);
high3=trapmf(x3,[5,8,10,10]);
% R(1,:,:)=trapmf(x1(1),[0,0,2,5])*(trapmf(x2,[0,0,2,5]).')*trapmf(x3,[0,0,2,5]);
% R(2,:,:)=trapmf(x1(1),[0,0,2,5])*(trapmf(x2,[0,0,2,5]).')*trimf(x3,[0,5,10]);
% R(3,:,:)=trapmf(x1(1),[0,0,2,5])*(trapmf(x2,[0,0,2,5]).')*trapmf(x3,[5,8,10,10]);
% R(4,:,:)=trapmf(x1(1),[0,0,2,5])*(trimf(x2,[0,5,10]).')*trapmf(x3,[0,0,2,5]);
% R(5,:,:)=trapmf(x1(1),[0,0,2,5])*(trimf(x2,[0,5,10]).')*trimf(x3,[0,5,10]);
R(:,:,1)=near(1)*(low2.')*low3;
R(:,:,2)=near(1)*(low2.')*moderate3;
R(:,:,3)=near(1)*(low2.')*high3;
R(:,:,4)=near(1)*(moderate2.')*low3;
R(:,:,5)=near(1)*(moderate2.')*moderate3;
R(:,:,6)=near(1)*(moderate2.')*high3;
R(:,:,7)=near(1)*(high2.')*low3;
R(:,:,8)=near(1)*(high2.')*moderate3;
R(:,:,9)=near(1)*(high2.')*high3;
R(:,:,10)=moderate1(1)*(low2.')*low3;
R(:,:,11)=moderate1(1)*(low2.')*moderate3;
R(:,:,12)=moderate1(1)*(low2.')*high3;
R(:,:,13)=moderate1(1)*(moderate2.')*low3;
R(:,:,14)=moderate1(1)*(moderate2.')*moderate3;
R(:,:,15)=moderate1(1)*(moderate2.')*high3;
R(:,:,16)=moderate1(1)*(high2.')*low3;
R(:,:,17)=moderate1(1)*(high2.')*moderate3;
R(:,:,18)=moderate1(1)*(high2.')*high3;
R(:,:,19)=far(1)*(low2.')*low3;
R(:,:,20)=far(1)*(low2.')*moderate3;
R(:,:,21)=far(1)*(low2.')*high3;
R(:,:,22)=far(1)*(moderate2.')*low3;
R(:,:,23)=far(1)*(moderate2.')*moderate3;
R(:,:,24)=far(1)*(moderate2.')*high3;
R(:,:,25)=far(1)*(high2.')*low3;
R(:,:,26)=far(1)*(high2.')*moderate3;
R(:,:,27)=far(1)*(high2.')*high3;
%% Defuzzification
VW=defuzz(x,z1,'centroid');
W=defuzz(x,z2,'centroid');
M=defuzz(x,z3,'centroid');
S=defuzz(x,z4,'centroid');
VS=defuzz(x,z5,'centroid');
 
%y=zeros(N,N);
sum_0=zeros(N,N);
for ii=1:27
    sum_0=sum_0+R(:,:,ii);
end
R(:,:,1)=R(:,:,1)*M;
R(:,:,2)=R(:,:,2)*W;
R(:,:,3)=R(:,:,3)*W;
R(:,:,4)=R(:,:,4)*S;
R(:,:,5)=R(:,:,5)*S;
R(:,:,6)=R(:,:,6)*M;
R(:,:,7)=R(:,:,7)*VS;
R(:,:,8)=R(:,:,8)*S;
R(:,:,9)=R(:,:,9)*M;
R(:,:,10)=R(:,:,10)*W;
R(:,:,11)=R(:,:,11)*VW;
R(:,:,12)=R(:,:,12)*VW;
R(:,:,13)=R(:,:,13)*M;
R(:,:,14)=R(:,:,14)*M;
R(:,:,15)=R(:,:,15)*W;
R(:,:,16)=R(:,:,16)*S;
R(:,:,17)=R(:,:,17)*S;
R(:,:,18)=R(:,:,18)*M;
R(:,:,19)=R(:,:,19)*W;
R(:,:,20)=R(:,:,20)*VW;
R(:,:,21)=R(:,:,21)*VW;
R(:,:,22)=R(:,:,22)*W;
R(:,:,23)=R(:,:,23)*W;
R(:,:,24)=R(:,:,24)*VW;
R(:,:,25)=R(:,:,25)*M;
R(:,:,26)=R(:,:,26)*S;
R(:,:,27)=R(:,:,27)*M;
 
sum_1=zeros(N,N);
for ii=1:27
    sum_1=sum_1+R(:,:,ii);
end
y=sum_1./sum_0;
 
figure(3)
mesh(x2,x3,y.'),xlabel('x2'),ylabel('x3'),zlabel('y');
 
%% random
x0=rand(1,100)*100;
y0=rand(1,100)*100;
 
x_0=sum(x0)/100;
y_0=sum(y0)/100;
%plot(x_0,y_0,'r.')
range=((y0-y_0).^2+(x0-x_0).^2).^(1/2);
range=range/max(range)*10;
x1=range;
x2=rand(1,100)*10;
x3=rand(1,100)*10;
 
N=length(x2);
%N=N*N;
R=zeros(27,N);
 
for jj=1:N % don't needed if use .*
near(jj)=trapmf(x1(jj),[0,0,2,5]);
moderate1(jj)=trimf(x1(jj),[0,5,10]);
far(jj)=trapmf(x1(jj),[5,8,10,10]);
 
low2(jj)=trapmf(x2(jj),[0,0,2,5]);
moderate2(jj)=trimf(x2(jj),[0,5,10]);
high2(jj)=trapmf(x2(jj),[5,8,10,10]);
 
low3(jj)=trapmf(x3(jj),[0,0,2,5]);
moderate3(jj)=trimf(x3(jj),[0,5,10]);
high3(jj)=trapmf(x3(jj),[5,8,10,10]);
 
R(1,jj)=near(jj)*(low2(jj))*low3(jj);
R(2,jj)=near(jj)*(low2(jj))*moderate3(jj);
R(3,jj)=near(jj)*(low2(jj))*high3(jj);
R(4,jj)=near(jj)*(moderate2(jj))*low3(jj);
R(5,jj)=near(jj)*(moderate2(jj))*moderate3(jj);
R(6,jj)=near(jj)*(moderate2(jj))*high3(jj);
R(7,jj)=near(jj)*(high2(jj))*low3(jj);
R(8,jj)=near(jj)*(high2(jj))*moderate3(jj);
R(9,jj)=near(jj)*(high2(jj))*high3(jj);
R(10,jj)=moderate1(jj)*(low2(jj))*low3(jj);
R(11,jj)=moderate1(jj)*(low2(jj))*moderate3(jj);
R(12,jj)=moderate1(jj)*(low2(jj))*high3(jj);
R(13,jj)=moderate1(jj)*(moderate2(jj))*low3(jj);
R(14,jj)=moderate1(jj)*(moderate2(jj))*moderate3(jj);
R(15,jj)=moderate1(jj)*(moderate2(jj))*high3(jj);
R(16,jj)=moderate1(jj)*(high2(jj))*low3(jj);
R(17,jj)=moderate1(jj)*(high2(jj))*moderate3(jj);
R(18,jj)=moderate1(jj)*(high2(jj))*high3(jj);
R(19,jj)=far(jj)*(low2(jj))*low3(jj);
R(20,jj)=far(jj)*(low2(jj))*moderate3(jj);
R(21,jj)=far(jj)*(low2(jj))*high3(jj);
R(22,jj)=far(jj)*(moderate2(jj))*low3(jj);
R(23,jj)=far(jj)*(moderate2(jj))*moderate3(jj);
R(24,jj)=far(jj)*(moderate2(jj))*high3(jj);
R(25,jj)=far(jj)*(high2(jj))*low3(jj);
R(26,jj)=far(jj)*(high2(jj))*moderate3(jj);
R(27,jj)=far(jj)*(high2(jj))*high3(jj);
 
end
 
VW=defuzz(x,z1,'centroid');
W=defuzz(x,z2,'centroid');
M=defuzz(x,z3,'centroid');
S=defuzz(x,z4,'centroid');
VS=defuzz(x,z5,'centroid');
 
 
sum_0=zeros(1,N);
for ii=1:27
    sum_0=sum_0+R(ii,:);
end
 
for jj=1:N  % don't needed 
R(1,jj)=R(1,jj)*M;
R(2,jj)=R(2,jj)*W;
R(3,jj)=R(3,jj)*W;
R(4,jj)=R(4,jj)*S;
R(5,jj)=R(5,jj)*S;
R(6,jj)=R(6,jj)*M;
R(7,jj)=R(7,jj)*VS;
R(8,jj)=R(8,jj)*S;
R(9,jj)=R(9,jj)*M;
R(10,jj)=R(10,jj)*W;
R(11,jj)=R(11,jj)*VW;
R(12,jj)=R(12,jj)*VW;
R(13,jj)=R(13,jj)*M;
R(14,jj)=R(14,jj)*M;
R(15,jj)=R(15,jj)*W;
R(16,jj)=R(16,jj)*S;
R(17,jj)=R(17,jj)*S;
R(18,jj)=R(18,jj)*M;
R(19,jj)=R(19,jj)*W;
R(20,jj)=R(20,jj)*VW;
R(21,jj)=R(21,jj)*VW;
R(22,jj)=R(22,jj)*W;
R(23,jj)=R(23,jj)*W;
R(24,jj)=R(24,jj)*VW;
R(25,jj)=R(25,jj)*M;
R(26,jj)=R(26,jj)*S;
R(27,jj)=R(27,jj)*M;
end
 
sum_1=zeros(1,N);
for ii=1:27
    sum_1=sum_1+R(ii,:);
end
 
y=sum_1./sum_0;
[m,p]=max(y);
 
figure (4)
plot(x0,y0,'.');hold on
plot(x0(p),y0(p),'r.')
x1(p)
x2(p)
x3(p)