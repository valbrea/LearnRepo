%% 输入 tau = τ， N为序列长度 输出Mackey Glass序列
function[sn] = MG(tau, N)  % tau = 11 and tau = 40 
sn = [];
fsn = [];
sn(1 : tau + 1) = rand(1, tau + 1); % 初始化前tau个样本

for ii = tau + 1 : N % ii - tau所以从tau + 1开始
    fsn(ii) = 0.2 * sn(ii - tau) / (1 + sn(ii - tau) ^ 10) - 0.1 * sn(ii);
    sn(ii + 1) = sn(ii) + fsn(ii);
end

% 输出1000：1500样本
figure;
plot(1000 : 1500, sn(1000 : 1500));
xlabel('t'), ylabel('s(n)');
title(['Mackey-Glass Series when τ = ', num2str(tau)]);

% 相图
figure;
plot(sn(1000 : 1500), sn(1000 - tau : 1500 - tau));
xlabel('s(n)'), ylabel('s(n - τ)');
title(['Phase diagram when τ = ', num2str(tau)]);
end
