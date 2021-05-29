%% sfls_type1.m

%% Compute the output(s) of a singleton type-1 FLS, when the antecedent 
%% membership functions are Gaussian (Chapter 5 of Uncertain Rule-Based 
%% Fuzzy Logic Systems: Introduction and New Directions, by Jerry M. Mendel, 
%% and published by Prentice-Hall, 2000).

%% M, sigma ，these two symbols are mxn（维度） matrix denotes the mean（均值） and std（方差） of
%% antecedent Gaussian MFs (m rules, with n antecedent in each rule)
%% C is mx1（维度） vector, which denotes the height of consequents
%% X is input matrix, Lxn（维度） matrix, each row is an input.


function [OUT]=sfls_1(M,sigma,C,X)

OUT=[];
[L,n]=size(X);  %表示共有L条rule，n个
[m,n]=size(M);  %表示共有m条rule，n个

%c为y值

for i=1:L   %针对每个input
    U=[];
    for j=1:m  %m rules
        u=1;
        for t=1:n  % n antecedent
            u=u*gaussmf(X(i,t),[sigma(j,t),M(j,t)]);  %X(i,t)表示是这个第i行第t列，sigma为sigma的方差，M为第j行第t列
        end
        U=[U,u];  %这个应该是拼接吧，将每一次的数据按新的一列记录下来
    end
    
    fa=U/sum(U);  %
    f=fa*C;  %
    OUT=[OUT,f];   %表示每个input的输出
end
