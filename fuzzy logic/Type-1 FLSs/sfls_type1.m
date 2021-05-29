%% sfls_type1.m

%% Compute the output(s) of a singleton type-1 FLS, when the antecedent 
%% membership functions are Gaussian (Chapter 5 of Uncertain Rule-Based 
%% Fuzzy Logic Systems: Introduction and New Directions, by Jerry M. Mendel, 
%% and published by Prentice-Hall, 2000).

%% M, sigma are mxn matrix denotes the mean and std of
%% antecedent Gaussian MFs (m rules, with n antecedent in each rule)
%% C is mx1 vector, which denotes the height of consequents
%% X is input matrix, Lxn matrix, each row is an input.


function [OUT]=sfls_1(M,sigma,C,X)

OUT=[];
[L,n]=size(X);
[m,n]=size(M);

for i=1:L
U=[];
for j=1:m
u=1;
for t=1:n
u=u*gaussmf(X(i,t),[sigma(j,t),M(j,t)]);
end
U=[U,u];
end

fa=U/sum(U);
f=fa*C;
OUT=[OUT,f]; 
end
