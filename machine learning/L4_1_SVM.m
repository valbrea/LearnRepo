%% SVM 支持向量机
 % 在支持向量机中，距离超平面最近的且满足一定条件的几个训练样本点被称为支持向量。
clear all; close all;
m = 4;
x = [0, 1, 2, 0; 0, 0, 0, 2];
y = [1, 1, -1, -1];
H = zeros(m);
for ii = 1 : m
    for jj = 1 : m
        xi = x(:, ii);
        xj = x(:, jj);
        yi = y(ii);
        yj = y(jj);
        H(ii,jj) = H(ii, jj) + yi * yj * xi' * xj; % Hesse矩阵
    end
end
f = -[1; 1; 1; 1]; % 目标函数，“-”负号表示求最大
Aeq = [1, 1, -1, -1];
beq = 0;
lb = zeros(m, 1);
xval = quadprog(H, f, [], [], Aeq, beq, lb, []) % A b没有，空着。
% quadprog()是二次规划函数，参看matlab帮助

% figure, hold on;
% plot(x(1, 1 : 2), x(2, 1:2), 'ro');
% plot(x(1, 3 : 4), x(2, 3:4), 'b');



