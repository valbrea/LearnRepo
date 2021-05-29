clear all; close all;
%% d = w'* u + v  如果w不是实数，就要用hermit而不是转置
L = 2000;
p = 5;
wo = randn(p,1);
vv = randn(1,L) * 0.5;
% vv = rand(1,L);
% vv = vv - mean(vv);
% v1 = randn(1,L) * 0.1;
% v2 = randn(1,L);
% numa = randn(1,L);
% for ii = 1:L%弹噪声
%     if numa(ii) > 0.1
%         vv(ii) = v1(ii);
%     else
%         vv(ii) = v2(ii);
%     end
%     end
uu = randn(p,L);
dd = wo' * uu + vv; 
%% MSE mean squared error 最小均方差
mu = 0.01;
w_MSE = randn(p,1);
for ii = 1:L
    Err_MSE(ii) = norm(wo - w_MSE);
    en = dd(ii) - w_MSE'* uu(:,ii);
    w_MSE = w_MSE + mu * en * uu(:,ii);%为什么是uu(:,ii) 解释size(uu)代表5 * 2000 每次给一个5 * 1的数组，一共2000次。
end                                    %d = w'* u + v 每一次的u是一个5 * 1的数组。uu(:,1)就是第一次的数组

%% LMF least mean forth 最小四阶矩
mu = 0.01;
w_LMF = randn(p,1);
for ii = 1:L
    Err_LMF(ii) = norm(wo - w_LMF);
    en = dd(ii) - w_LMF'* uu(:,ii);
    w_LMF = w_LMF + mu * en^3 * uu(:,ii);
end
%对于幅度比较小的噪声效果比较好，例如
%vv = rand(1,L);
%vv = vv - mean(vv);
%kurtosis高斯=3（峭度）
%对于峭度>3的超高斯噪声，前两种方法不好用
%% MCC max correntropy criterion 最大相关熵
%因为目标函数是减函数，e越小，exp那一堆越大，所以是目标函数值最大化问题
mu = 0.05;
sigma = 2;
w_MCC = randn(p,1);
for ii = 1:L
    Err_MCC(ii) = norm(wo - w_MCC);
    en = dd(ii) - w_MCC'* uu(:,ii);
    w_MCC = w_MCC + mu * exp(-en^2/(2 * sigma^2)) * en * uu(:,ii);
end
%% RLS Recursive least square 递归最小二乘
P = eye(p);
lamda = 1;
w_RLS = zeros(p,1);
for ii = 1:L
    Err_RLS(ii) = norm(wo - w_RLS);
    en = dd(ii) - w_RLS'* uu(:,ii);
    kk = P * uu(:,ii)/(lamda + uu(:,ii)' * P * uu(:,ii));
    P = (1/lamda) * (P - kk * uu(:,ii)' * P);
    w_RLS = w_RLS + kk * en;
end
figure, hold on;
plot(Err_MSE, 'r');
% plot(Err_LMF, 'g');
% plot(Err_MCC, 'b');
plot(Err_RLS, 'k');
% legend('MSE','LMF','MCC','RLS');
legend('MSE','RLS');