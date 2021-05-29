%% train_tsk_type1.m

%% Tune the parameters of a type-1 TSK FLS (type-1 antecedents 
%% and type-0 consequent) when the antecedent membership functions 
%% are Gaussian, using some input–output training data. (Chapter 13, 
%% Section 13.2.4 of Uncertain Rule-Based Fuzzy Logic Systems: 
%% Introduction and New Directions, by Jerry M. Mendel, and published 
%% by Prentice-Hall, 2000).

%% M, sigma are mxn matrix denotes the mean and std of
%% antecedent Gaussian MFs (m rules, with n antecedent in each rule)
%% C is mx(n+1) matrix, which denotes the height of consequents
%% X is input matrix, Lxn matrix, each row is onw input.
%% D is Lx1 vector which denotes the desired output

function [M,c0,sigma]=train_tsk_type1(X,D,M,sigma,C,alpha);

[L,n]=size(X);
[m,n]=size(M);


for i=1:L
U=[];
for j=1:m
u=1;
for t=1:n
u=u*(gaussmf(X(i,t),[sigma(j,1),M(j,1)]);
end
U=[U,u];
end

c0=C(:,1);
for t=1:n
c0=c0+C(:,t)*X(i,t);
end

fa=U/sum(U);
f=fa*c0; 
fa=fa';
e=D(i)-f;

sigma0=sigma;
M0=M;

for l=1:m
for k=1:n
M(l,k)=M(l,k)+alpha*e*((X(i+k-1)-M(l,k))/(sigma(l,k)^2))...
*(c0(l)-f)*U(l)/sum(U);
sigma(l,k)=sigma(l,k)+alpha*e*(((X(i+k-1)-M0(l,k))^2)/(sigma(l,k)^3))...
*(c0(l)-f)*U(l)/sum(U);
end
end
C(:,1)=C(:,1)+alpha*e*fa;

for j=2:(ant+1)
C(:,j)=C(:,j)+alpha*e*fa*X(i,j-1);
end

end

