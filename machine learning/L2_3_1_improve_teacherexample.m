clear all; close all;
%% d = w' * u + v
L = 2000;
p = 5;
wo = randn(p,1);
vv = randn(1,L) * 0.5;
% vv = rand(1,L);
% vv = vv - mean(vv);
% v1 = randn(1,L) * 0.1; v2 = randn(1,L);
% numa = rand(1,L);
% for ii = 1 : L
%     if numa(ii) > 0.1
%         vv(ii) = v1(ii);
%     else
%         vv(ii) = v2(ii);
%     end
% end
uu = randn(p,L);
dd = wo' * uu + vv;
%% MSE mean squared error
mu = 0.01;
w_MSE = randn(p,1);
for ii = 1:L
    Err_MSE(ii) = norm(wo-w_MSE);
    en = dd(ii) - w_MSE' * uu(:,ii);
    w_MSE = w_MSE + mu * en * uu(:,ii);
end

%% LMF least mean forth
mu = 0.01;
w_LMF = randn(p,1);
for ii = 1:L
    Err_LMF(ii) = norm(wo-w_LMF);
    en = dd(ii) - w_LMF' * uu(:,ii);
    w_LMF = w_LMF + mu * en^3 * uu(:,ii);
end

%% MCC max correntropy criterion
mu3 = 0.05;
w_MCC = randn(p,1);
sigma = 0.8;
for ii = 1:L
    Err_MCC(ii) = norm(wo-w_MCC);
    en = dd(ii) - w_MCC' * uu(:,ii);
    w_MCC = w_MCC + mu3 * exp(-en^2/2/sigma^2) * en * uu(:,ii);
end

%% RLS Recursive lease square
P = eye(p); lamta = 1;
w_RLS = zeros(p,1);
for ii = 1:L
    Err_RLS(ii) = norm(wo-w_RLS);
    u1 = uu(:,ii);
    en = dd(ii) - w_RLS' * u1;
    kn = P * u1 / (lamta + u1' * P * u1) ;
    P = 1/lamta * (P - kn * u1' * P);
    w_RLS = w_RLS + kn * en;
end


figure, hold on;
plot(Err_MSE,'r');
% plot(Err_LMF, 'k');
% plot(Err_MCC, 'g');legend('MSE','LMF','MCC','RLS');

plot(Err_RLS,'b');legend('MSE','RLS');

% figure, plot(vv);