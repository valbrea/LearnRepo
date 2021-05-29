clear all; close all;
L = 2000;
p = 5;
wo = randn(p,1);
vv = randn(1,L) * 0.5;
uu = randn(p,L);
dd = wo' * uu + vv; 
%% LMS 1 最速下降法
w_lms = zeros(p,1);
mu_lms = 0.02;

for ii = 1:L
    Err_LMS(ii) = norm(w_lms - wo);
    en = dd(ii) - w_lms' * uu(:,ii);
    w_lms = w_lms + mu_lms * en * uu(:,ii);
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
plot(Err_LMS);
plot(Err_RLS,'r');
legend('LMS','RLS');