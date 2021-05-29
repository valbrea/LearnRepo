clear all, close all;
%% 求数据在某条直线上的投影
L = 200; % 生成随机分布的一团数据
X = rand(2, L) * 6;
X(1,:) = X(1,:) + 4;
X(2,:) = X(2,:) - 4;

x = -5 : 0.5 : 5; % 任意找一条直线
y = 2 * x; 
A = [1; 2]; 

p = A * inv(A' * A) * A' * X; % 数据在直线上的投影
% A = A / norm(A);
%除以范数后A' * A=1，则p=A * A' * X, A * A'是个算子


figure, hold on;
plot(x, y, 'r');
plot(X(1,:), X(2,:), '*');
plot(p(1,:), p(2,:), 'o');
axis([-10, 10, -10, 10]);