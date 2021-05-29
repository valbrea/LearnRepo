clear all; close all;
%% 感知机分类
L = 200;
m = 2;
X = ones(m + 1, L);
D = ones(1, L);
for ii = 1 : L/2
    X(1 : 2, ii) = randn(m,1) + [4; 4]; % 中心点（4，4）
    D(ii) = 1;
end
for ii = 1 + L/2 : L
    X(1 : 2, ii) = randn(m,1) + [0; 0]; % 中心点（0，0）
    D(ii) = -1;
end

w = randn(m + 1, 1);
update = 0;
mu = 0.1;
Num = 200;
for kk = 1 : Num
    for ii = 1 : L/2
        x = X(:, ii);
        if w' * x < 0
            update = update - x;
        end
    end
    for ii = 1 - L/2 : L
        if w' * x > 0
            update = update + x;
        end
    end
    w = w + mu * update;
    Err(kk) = norm( D - sign(w' * X) );
end

% X'w = D'; Ax = b;
% D = w' * x;
%% wiener solution
w = inv(X * X') * X * D';

%% LMS solution
Num = 200;
w_LMS = randn(m + 1, 1);
mu = 0.001;

for kk = 1 : Num
    for ii = 1 : L
        d = D(ii);
        x = X(:, ii);
        e = d - w_LMS' * x;
        w_LMS = w_LMS + mu * e * x;
    end
%     Err(kk) = norm(w_LMS - w);
    Err(kk) = norm(D - sign(w_LMS' * X));
end


% w = [w1, w2, w3];
x1 = -4 : 0.1 : 12;
y1 = -w(3) / w(2) - w(1) * x1 / w(2); % 维纳滤波的解（最优解）
y2 = -w_LMS(3) / w_LMS(2) - w_LMS(1) * x1 / w_LMS(2); % 梯度下降的解（迭代解，逼近最优解）
norm(D - sign(w' * X)) % 应该等于0



figure, plot(Err);
figure, hold on;
plot(x1, y1, 'b');
plot(x1, y2, 'r');
plot(X(1, 1 : L/2), X(2, 1: L/2), 'b*');
plot(X(1, 1 + L/2 : L), X(2, 1 + L/2 : L), 'r.');
legend('维纳滤波的解（最优解）', '梯度下降的解（迭代解，逼近最优解）');
grid on;