clear all;close all;
L=200;
m=2;
X=ones(m,L);
D= ones(1,L);
for ii = 1:L
    if ii>L/2
        X(1:2,ii)= randn(m,1) + [12;2];
        D(ii) = -1;
    else
        X(1:2,ii)= randn(m,1)+ [2;-6];
        D(ii) = 1;
    end
end

X1=X(1:2,1:L/2);
X2=X(1:2,1+L/2:end);
m1=mean(X1(1:2,:)')';
m2=mean(X2(1:2,:)')';
Sd = (m1-m2)*(m1-m2)';
Ss = 0;
for ii=1:L/2
    x1=X1(:,ii);
    x2=X2(:,ii);
    Ss = Ss +  (x1-m1)*(x1-m1)' + (x2-m2)*(x2-m2)';
end
%%Fisher
w = inv(Ss) * (m1-m2);
[U1, lamda] = eig(inv(Ss)*Sd);
w1 = U1(:,1);
w1(1)/w1(2)-w(1)/w(2)

x1 = -4:0.1:12;
y1 = w(2)/w(1)*x1;
A = [w(1); w(2)];

P1 = A*inv(A'*A)*A'*X1;
P2 = A*inv(A'*A)*A'*X2;
figure, hold on;
plot(x1,y1,'r')
plot(X1(1,:),X1(2,:),'.');
plot(P1(1,:),P1(2,:),'b*');
plot(X2(1,:),X2(2,:),'r.');
plot(P2(1,:),P2(2,:),'ro');
axis([-4 16 -12 8])
grid on;
%% PCA
[U2,lamda2,V2]=svd(X*X');
w2 = U2(:,1);
x1 = -4:0.1:12;
y1 = w2(2)/w2(1)*x1;
A = [w2(1); w2(2)];

P1 = A*inv(A'*A)*A'*X1;
P2 = A*inv(A'*A)*A'*X2;
figure, hold on;
plot(x1,y1,'r')
plot(X1(1,:),X1(2,:),'.');
plot(P1(1,:),P1(2,:),'b*');
plot(X2(1,:),X2(2,:),'r.');
plot(P2(1,:),P2(2,:),'ro');
axis([-4 16 -12 8])
grid on;


w3 = U2(:,2);
x1 = -4:0.1:12;
y1 = w3(2)/w3(1)*x1;
A = [w3(1); w3(2)];

P1 = A*inv(A'*A)*A'*X1;
P2 = A*inv(A'*A)*A'*X2;
figure, hold on;
plot(x1,y1,'r')
plot(X1(1,:),X1(2,:),'.');
plot(P1(1,:),P1(2,:),'b*');
plot(X2(1,:),X2(2,:),'r.');
plot(P2(1,:),P2(2,:),'ro');
axis([-4 16 -12 8])
grid on;