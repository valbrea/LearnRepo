% clear all, close all;
% %% 输入数据
% sn = MG(40, 2000); % MG序列
% p = 4;
% train = zeros(500, 5);
% train_num = 1;
% % 训练数据
% for ii = 1001 : 1500
%     train(train_num, :) = sn(ii : ii + p);
%     train_num = train_num + 1;
% end
% 
% % 测试数据
% test = zeros(496, 5);
% test_num = 1;
% for ii = 1505 : 1996
%     test(test_num, :) = sn(ii : ii + p);
%     test_num = test_num + 1;
% end
%% 初始化
m_s = mean(sn(1001 : 1504));
sigma_s = std(sn(1001 : 1504));
% centers of anticident MFs的初始值全排列
m_value = [m_s - 2 * sigma_s, m_s + 2 * sigma_s];
a1 = m_value;
a2 = m_value;
a3 = m_value;
a4 = m_value;
[A4, A3, A2, A1] = ndgrid(a4, a3, a2, a1);

mean_SD = [A1(:), A2(:), A3(:), A4(:)]; 
sigma_SD = 2 * sigma_s * ones(16, 4); % 初始值为2σs
ybar_SD = rand(16, 1);
CC = train(:, p + 1);
XX = train(:, 1 : p);
DD = test(:, 1 : p);
alpha = 0.2;
initial_values = [mean_SD, ybar_SD]; % 初始centers & ybar表
%% 训练
for ii = 1 : 6 % 6 epochs
    [mean_SD, ybar_SD, sigma_SD] = train_sfls_type1(XX, CC, mean_SD, sigma_SD, ybar_SD, alpha);
    Y = sfls_type1(mean_SD, sigma_SD, ybar_SD, DD);
    RMSE_SD(ii) = sqrt(sum((test(:, p + 1) - Y').^ 2) / 496);
end
%%
% M, sigma are mxn matrix denotes the mean and std of
% antecedent Gaussian MFs (m rules, with n antecedent in each rule)
% c0 is mx1 vector, which denotes the height of consequents
% X is input matrix, Lxn matrix, each row is onw input.
% D is Lx1 vector which denotes the desired output

% function [M,c0,sigma]=train_sfls_1(X,D,M,sigma,c0,alpha);


% M, sigma are mxn matrix denotes the mean and std of
% antecedent Gaussian MFs (m rules, with n antecedent in each rule)
% C is mx1 vector, which denotes the height of consequents
% X is input matrix, Lxn matrix, each row is an input.

% function [OUT]=sfls_1(M,sigma,C,X)
