clear all; close all;
% BP algorithm
X = -1 : 0.05 : 1;

n = size(X, 1);
L = size(X, 2);
D = sin(X * 4) + cos(X * 5) + tanh (X * 3); % 非线性函数，经过映射变为线性关系
D = D/6 + 0.5; % 注意要归一化，f(z)的输出一定在[0, 1]之间，否则不会收敛
 % 看到竖轴范围是-3到3，所以除以6，是-0.5到0.5，+0.5是0到1
 
Num = 50000;
mu1 = 3; mu2 = 1; mu3 = 2; mu4 = 3;
m = 20;
W1 = randn(m, n); b1 = randn(m, 1);
W2 = randn(1, m); b2 = randn(1);

%% BP training
for kk = 1 : Num
    for ii = 1 : L
        x = X(:, ii);
        z2 = W1 * x + b1;
        a2 = 1 ./ (1 + exp(-z2)); % 激活函数y = 1 ./ (1 + exp(-z))
        z3 = W2 * a2 + b2;
        y(ii) = 1 ./ (1 + exp(-z3));
        d = D(ii);
        e = d - y(ii);    
        Jb1 = e * y(ii) * (1 - y(ii)); %激活函数的导数 y * (1 - y)
        b2 = b2 + mu4 * Jb1;
        W2 = W2 + mu3 * Jb1 * a2';
        Jb2 = W2' .* a2 .* (1 - a2);
        b1 = b1 + mu2 * Jb1 * Jb2;
        W1 = W1 + mu1 * Jb1 * Jb2 * x';
        
    end
    Err(kk) = norm(y - D);
end

figure, hold on;
plot(D,'r'), plot(y,'b');
legend('期望输出', '实际输出');
figure, plot(Err);