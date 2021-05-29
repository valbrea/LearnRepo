%% train_nsfls_type1.m

%% Tune the parameters of a non-singleton type-1 FLS when the antecedent 
%% membership functions are Gaussian, using some inputÐoutput training 
%% data (Chapter 6, Section 6.6.3, of Uncertain Rule-Based Fuzzy Logic 
%% Systems: Introduction and New Directions, by Jerry M. Mendel,
%% and published by Prentice-Hall, 2000).

%% M, sigma are mxn matrix denotes the mean and std of
%% antecedent Gaussian MFs (m rules, with n antecedent in each rule)
%% c0 is mx1 vector, which denotes the height of consequents
%% sigmax is 1xn vector which is the std of input.
%% X is input matrix, Lxn matrix, each row is onw input.
%% D is Lx1 vector denotes the desired output

function [M,c0,sigma,sigmax]=train_sfls_1(X,D,M,sigma,c0,alpha);

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
f=fa*c0; 
fa=fa';
e=D(i)-f;

sigma0=sigma;
M0=M;


for l=1:m
for k=1:n
M(l,k)=M(l,k)+alpha*e*((X(i,k)-M(l,k))/(sigma(l,k)^2+sigmax0(k)^2))...
*(c0(l)-f)*U(l)/sum(U);

sigma(l,k)=sigma(l,k)+alpha*e*((sigma(l,k)*(X(i,k)-M0(l,k))^2)/...
(sigma(l,k)^2+sigmax0(k)^2)^2)*(c0(l)-f)*U(l)/sum(U);

sigmax(k)=sigmax(k)+alpha4*e*((sigmax0(k)*(X(i,k)-M0(l,k))^2)/...
(sigma(l,k)^2+sigmax0(k)^2)^2)*(c0(l)-f)*U(l)/sum(U);

if sigmax(k)>sigma(l,k)
sigmax(k)=sigma(l,k);
end

end
end

c0=c0+alpha*e*fa;
end

