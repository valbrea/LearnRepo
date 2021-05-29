%%nsfls_type1.m

%% Compute the output(s) of a non-singleton type-1 FLS when the antecedent 
%% membership functions are Gaussian and the input sets are Gaussian. 
%% (Chapter 6 of Uncertain Rule-Based Fuzzy Logic Systems: Introduction 
%% and New Directions, by Jerry M. Mendel, and published by Prentice-Hall, 2000).

%% M, sigma are mxn matrix denotes the mean and std of
%% antecedent Gaussian MFs (m rules, with n antecedent in each rule)
%% C is mx1 vector, which denotes the height of consequents
%% sigmax is 1xn vector which is the std of input
%% X is input matrix, Lxn matrix, each row is an input.

function [OUT]=nsfls_type1(M,sigma,C,sigmax,X)

OUT=[];
[L,n]=size(X);
[m,n]=size(M);

for i=1:L
U=[];
for j=1:m
u=1;
for t=1:n
x=((sigmax(t)^2)*M(j,t)+(sigma(j,t)^2)*X(i,t))/(sigmax(t)^2+sigma(j,t)^2);
u1=gaussmf(x,[sigma(j,t),M(j,t)])*gaussmf(x,[sigmax(t),X(i,t)]);
u=u*u1;
end
U=[U,u];
end

fa=U/sum(U);
f=fa*C;
OUT=[OUT,f]; 
end
