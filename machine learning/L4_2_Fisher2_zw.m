%Fisher分类器
clear all;
close all;
%有200个点
L=200;
m=2;
%测试数据
X=rand(2,L)*6;%范围0到6
%X分成两类数据
for ii=1:L
    if ii > L/2
        X(:,ii)=randn(m,1)+[12;2];%选12 2是中心
    else
        X(:,ii)=randn(m,1)+[2;-6];%选2 -6为中心
    end
end
X1=X(:,1:L/2);
X2=X(:,1+L/2:end);

%找直线让其投影最大
%1.计算类中心
m1=mean(X1')';
m2=mean(X2')';
%2.计算Sd
Sd=(m1-m2)*(m1-m2)';
%3.计算Ss
Ss=zeros(m);
for ii= 1:L/2
    x1=X1(:,ii);
    x2=X2(:,ii);
    Ss=Ss+(x1-m1)*(x1-m1)'+(x2-m2)*(x2-m2)';
end
%4.特征值分解
[U1,lamda]=eig(inv(Ss)*Sd);
%最大特征值和其特征向量
w1=U1(:,1);%最大特征向量
%曲线x轴是-2到16，算投影子空间A，w1作为投影子空间
A=w1;
%X1在子空间上面的投影P1
P1=A*inv(A'*A)*A'*X1;
P2=A*inv(A'*A)*A'*X2;
%5.做投影的直线
x=-6:0.1:16;
y=A(2)/A(1)*x;

figure
hold on
plot(X1(1,:),X1(2,:),'r*')
plot(P1(1,:),P1(2,:),'ro')
plot(x,y,'b')
plot(X2(1,:),X2(2,:),'k*')
plot(P2(1,:),P2(2,:),'ko')
axis([-6 16 -10 12])