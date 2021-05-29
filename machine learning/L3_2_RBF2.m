clear all; close all;
X = -1 : 0.1 : 1; %已知X和D，求c、σ、w
% 如果效果不好可以考虑增加X点数，或者改变训练次数，调整隐层个数，步长等参数，总之RBF是万能函数逼近器
D = sin(X * 4) + cos(X * 5) + tanh(X * 3); % 目标函数
L = length(X); % 数据长度
m = 20; % 隐含层个数
c = rand(1,m) * 2 - 1; % 均值（中心矢量） 在 -1到 +1之间
a = ones(1,m) * 2; % σ取1或者2
w = randn(m + 1,1); % 权值，20层 + 偏置
h = zeros(m + 1,1); % 中间层初值

Num = 200; % 训练次数
mu1 = 0.1 ; mu2 = 0.5 ; mu3 = 0.1; % 步长 随意（要求三个值所以三个步长）
%% TRAINING 训练过程
for kk = 1 : Num % 训练200轮
    for ii = 1 : L % L个数据进行训练
        x = X(:, ii); % 已知输入X和期望的输出D
        d = D(ii);
        for jj = 1 : m % 已知h表达式 （高斯核函数）
            h(jj) = exp( - ( x - c(jj) )^2 * a(jj)^2);
        end
        h(m + 1) = 1; % h最后一个偏置
        y(ii) = w' * h;
        e = d - y(ii); % 误差项
        w = w + mu1 * e * h; % 对w进行更新
        for jj = 1 : m % 对每一个c和σ进行更新
            c(jj) = c(jj) + mu2 * e * w(jj) * h(jj) * ( x - c(jj) ); 
            a(jj) = a(jj) - mu3 * e * w(jj) * h(jj) * ( x - c(jj) )^2 * a(jj);
        end
    end
    Err(kk) = norm(D - y); % 每一轮训练的结果
end

%% TESTING 测试过程
for ii = 1 : L
    x = X(:, ii);
    for jj = 1 : m
        h(jj) = exp( - ( x - c(jj) )^2 * a(jj)^2);
    end
    h(m + 1) = 1; % 偏置为1
    y(ii) = w' * h;
end
    
figure, hold on;
plot(X, D);
plot(X, y,'r');
legend('REAL','TRAIN');
figure,plot(Err);