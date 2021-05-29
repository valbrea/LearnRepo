%% svd_qr_nsfls_type1.m

%% Rule reduction of a non-singleton type-1 FLS when the antecedent 
%% membership functions are Gaussian, using some inputÐoutput 
%% training data. (Chapter 6, Section 6.6.4, of Uncertain Rule-Based 
%% Fuzzy Logic Systems: Introduction and New Directions, by 
%% Jerry M. Mendel, and published by Prentice-Hall, 2000).

%% M, sigma are mxn matrix denotes the mean and std of
%% antecedent Gaussian MFs (m rules, with n antecedent in each rule)
%% C is mx1 vector, which denotes the height of consequents
%% X is input matrix, Lxn matrix, each row is an input.
%% th is a threshold for choosing the principal component

function [M,sigma,C]=svd_qr_nsfls_type1(M,sigma,C,sigmax,X,th)

FBF=[];

[L,n]=size(X);
[m,n]=size(M);
rule=m;

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

fbf=U/sum(U);
FBF=[FBF,fbf'];
end
FBF=FBF';

[U,SS,V]=svd(FBF);

a=diag(SS);
for i=1:m
if a(i)>th
r=i;
end
end

A=[V(1:r,1:r)', V((r+1):rule,1:r)'];
[Q,R,E]=qr(A);
[e,I]=sort(E);
I=I(rule,1:r);


%%%%%%% Keep the most important parameters

M=M(I,:);
C=C(I);
sigma=sigma(I,:);


