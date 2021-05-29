% clear all, close all;
% sn = MG(40, 2000); % MG序列

p = 4;
train = zeros(500, 5);
train_num = 1;
% 训练数据
for ii = 1001 : 1500
    train(train_num, :) = sn(ii : ii + p);
    train_num = train_num + 1;
end

% 测试数据
test = zeros(496, 5);
test_num = 1;
for ii = 1505 : 1996
    test(test_num, :) = sn(ii : ii + p);
    test_num = test_num + 1;
end

X = train(:, 1 : p);
sigma = 0.1 * ones(500, p); % std = 0.1
C = train(:, p + 1);
D = test(:, 1 : p);

Y = sfls_type1(X, sigma, C, D);
RMSE_OP = sqrt(sum((test(:, p + 1) - Y').^ 2) / 496);

% M, sigma are mxn matrix denotes the mean and std of
% antecedent Gaussian MFs (m rules, with n antecedent in each rule)
% C is mx1 vector, which denotes the height of consequents
% X is input matrix, Lxn matrix, each row is an input.

% function [OUT]=sfls_1(M,sigma,C,X)

