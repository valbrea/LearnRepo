%% train_sfls_type1.m

%% Tune the parameters of a singleton type-1 FLS when the antecedent 
%% membership functions are Gaussian, using some input衞utput training 
%% data (Chapter 5, Section 5.9.3, of Uncertain Rule-Based Fuzzy Logic 
%% Systems: Introduction and New Directions, by Jerry M. Mendel,
%% and published by Prentice-Hall, 2000).

%% M, sigma are mxn matrix denotes the mean and std of
%% antecedent Gaussian MFs (m rules, with n antecedent in each rule)
%% c0 is mx1 vector, which denotes the height of consequents
%% X is input matrix, Lxn matrix, each row is onw input.
%% D is Lx1 vector which denotes the desired output

function [M,c0,sigma]=train_sfls_1(X,D,M,sigma,c0,alpha);

[L,n]=size(X);
[m,n]=size(M);

for i=1:L
U=[];
for j=1:m
u=1;
for t=1:n
% u=u*(gaussmf(X(i,t),[sigma(j,1),M(j,1)]); 多打了个括号
  u=u*gaussmf(X(i,t),[sigma(j,t),M(j,t)]);
end
U=[U,u];
end

fa=U/sum(U);
f=fa*c0; 
fa=fa';
e=D(i)-f;

sigma0=sigma;
M0=M;

for l=1:m
for k=1:n
M(l,k)=M(l,k)+alpha*e*((X(i,k)-M(l,k))/(sigma(l,k)^2))...
*(c0(l)-f)*U(l)/sum(U);
sigma(l,k)=sigma(l,k)+alpha*e*(((X(i,k)-M0(l,k))^2)/(sigma(l,k)^3))...
*(c0(l)-f)*U(l)/sum(U);
end
end
c0=c0+alpha*e*fa;
end

