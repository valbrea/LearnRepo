%% 例2 任意两类
clear all; close all;
L = 1000;
N = 2;%2种可能
m = 6;%维数m变成6
X = [[-1 1 -1 1]',[1 1 -1 1]'];
X = [rand -rand,%randn也一样，randn不用正负号
    -rand rand,
    rand -rand,
    -rand rand,
    rand -rand,
    1 1];%输入
D = [1 0];%期望（真实值）
w = randn(m,1);%初始权值（随机）
mu = 10;%改变步长 本例适合大步长，因为不会发散

for kk = 1:L%训练
    for ii = 1:N
        x = X(:,ii);
        z = w' * x;
        fz = 1 /(1 + exp(-z));
        d = D(ii);
        e = d - fz;
        w = w + mu * e * fz * (1 - fz) * x;
    end
    Err(kk) = norm(e);
end
    
    
for ii = 1:N %未进行训练
    x = X(:,ii);
    z = w' * x;
    fz(ii) = 1 /(1 + exp(-z));
end

figure,plot(Err);
figure, hold on;
plot(D,'ro');plot(fz,'g*');
legend('REAL','TRAIN');

