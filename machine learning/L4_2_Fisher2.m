clear all, close all;
%% Fisher 分类器 （距离最大）
% 生成两类数据
L = 200; 
m = 2;
X = rand(2, L) * 6;
X(1,:) = X(1,:) + 4;
X(2,:) = X(2,:) - 4;
for ii = 1 : L 
    if ii > L/2
        X(:,ii) = randn(m, 1) + [12; 2];
    else
        X(:,ii) = randn(m, 1) + [2; -6];
    end
end
X1 = X(:, 1 : L/2);
X2 = X(:, 1 + L/2 : end);

% step 1 计算类中心
m1 = mean(X1')';
m2 = mean(X2')';
% step 2 投影类中心距离矩阵
Sd = (m1 - m2) * (m1 - m2)';
% step 3 投影类内离散度矩阵
Ss = zeros(m);
for ii = 1 : L/2
    x1 = X1(:,ii);
    x2 = X2(:,ii);
    Ss = Ss + (x1 - m1) * (x1 - m1)' + (x2 - m2) * (x2 - m2)';
end
% step 4 特征值分解
[U1, lambda] = eig(inv(Ss) * Sd);
w1 = U1(:, 1); % 投影子空间A
A = w1;

% 投影直线
x1 = -6 : 0.1 : 16;
y1 = A(2)/A(1) * x1;

P1 = A * inv(A' * A) * A' * X1; % X1的投影
P2 = A * inv(A' * A) * A' * X2; % X2的投影

figure, hold on;
plot (x1, y1, 'k');
plot(X1(1,:), X1(2,:), 'r*');
plot(P1(1,:), P1(2,:), 'ro');
plot(X2(1,:), X2(2,:), 'b*');
plot(P2(1,:), P2(2,:), 'bo');
axis([-6, 16, -10, 12]);

%% PCA （能量最大）
R = X * X' / L;
[U2, lambda2, V2] = svd (R); % 奇异值分解
w2 = U2(:,1);
A = w2;

% 投影直线
x1 = -6 : 0.1 : 16;
y1 = A(2)/A(1) * x1;

P1 = A * inv(A' * A) * A' * X1; % X1的投影
P2 = A * inv(A' * A) * A' * X2; % X2的投影

figure, hold on;
plot (x1, y1, 'k');
plot(X1(1,:), X1(2,:), 'r*');
plot(P1(1,:), P1(2,:), 'ro');
plot(X2(1,:), X2(2,:), 'b*');
plot(P2(1,:), P2(2,:), 'bo');
axis([-6, 16, -10, 12]);