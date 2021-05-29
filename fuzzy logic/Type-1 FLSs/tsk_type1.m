tsk_type1.m

%% Compute the output(s) of a type-1 TSK FLS (type-1 antecedents 
%% and type-0 consequent) when the antecedent membership functions 
%% are Gaussian (Chapter 13, Section 13.2 of Uncertain Rule-Based 
%% Fuzzy Logic Systems: Introduction and New Directions, by 
%% Jerry M. Mendel, and published by Prentice-Hall, 2000).

%% M, sigma are mxn matrix denotes the mean and std of
%% antecedent Gaussian MFs (m rules, with n antecedent in each rule)
%% C is mx(n+1) matrix, which denotes the coefficients of consequents
%% X is input matrix, Lxn matrix, each row is onw input.


function [OUT]=tsk_type1(M,sigma,C,X)

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

%% compute the consequent

c0=C(:,1)
for t=1:n
c0=c0+C(:,t)*X(i,t);
end


fa=U/sum(U);
f=fa*C;
OUT=[OUT,f]; 
end
