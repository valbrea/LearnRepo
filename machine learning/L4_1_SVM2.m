%% SVM 支持向量机
 % 非线性分类，使用核函数
clear all; close all;
m = 5;
x = [1, 2, 4, 5, 6];
y = [1, 1, -1, -1, 1];
H = zeros(m);
for ii = 1 : m
    for jj = 1 : m
        xi = x(:, ii);
        xj = x(:, jj);
        yi = y(ii);
        yj = y(jj);
        H(ii,jj) = H(ii, jj) + yi * yj * (xi' * xj + 1)^2; % (xi' * xj + 1)^2是核函数
    end
end
f = -[1; 1; 1; 1; 1]; % 目标函数，“-”负号表示求最大
Aeq = [1, 1, -1, -1, 1];
beq = 0;
lb = zeros(m, 1);
xval = quadprog(H, f, [], [], Aeq, beq, lb, []) % A b没有，空着。
% quadprog()是二次规划函数，参看matlab帮助