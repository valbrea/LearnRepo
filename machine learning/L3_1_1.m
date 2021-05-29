%% S形函数 模拟真实神经网络中的生物脉冲，超过一定幅度最大刺激也就是1，主要靠频率而不是强度来区分
% x = -10:0.1:10;
% fx = 1 ./ (1 + exp (-x));
%% 识别香蕉和苹果（例1）-单层感知机
clear all; close all;
L = 1000;
% N = 2;%2种可能
N = 4;%改成分4类 3个项最多分成8类，所以最多可以分8类
m = 4;%维数=4 3项+1个偏置
% X = [[-1 1 -1 1]',[1 1 -1 1]'];%输入
X = [-1 1 1 -1%输入
    1 1 1 -1
    -1 -1 1 -1
    1 1 1 1];
D = [1 0 0.5 0.2];


% D = [1 0];%期望（真实值）
w = randn(m,1);%初始权值（随机）
mu = 5;%步长 本例适合大步长，因为不会发散

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


