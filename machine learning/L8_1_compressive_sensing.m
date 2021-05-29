clear all; close all;
%% 99 Nature 
% 把一个m * n的数据矩阵压缩为m * p + p * n的数据
m = 50; n = 20; p = 5;
V = rand(m, n); % 真实值
W = rand(m, p); % i*a的矩阵
H = rand(p, n); 
Num = 100;

for kk = 1: Num
    for a = 1 : p % W是P行 第一个公式 更新W的行
        V_tmp = W * H;
        tmp1 = V ./ V_tmp; % 标量
        for ii = 1 : m
            W(ii, a) = W(ii, a) * sum(tmp1(ii, :) .* H(a, :)); % V每行n个标量，H矩阵是每行n个数据，所以是点乘求和
        end
        
        W(:, a) = W(:, a) / sum(W(:, a)); % 第二个公式，更新W的列
        
        for mu = 1 : n 
            H(a, mu) = H(a, mu) * sum(W(:, a) .* tmp1(:, mu)); % 第三个公式，更新H
        end
    end
    Err(kk) = norm(V - W* H);
end

figure, plot(Err);
        