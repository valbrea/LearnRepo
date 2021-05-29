clear all; close all;
% known a and c, solution w using LS
X=-1:0.02:1;
% X = -2: 0.1:2;
L=length(X);
% D=[-0.9602,-0.5770,-0.0729,0.3771,0.6405,0.66,0.4609,0.1366,-0.2013 -0.4344,-0.5,-0.393,-0.1647,0.0988,0.3072,0.396,0.3449,0.1816,-0.0312,-0.2183,-0.3201];
% D=sin(X*5+randn(1,L)*0.0)+1;
D= sin(X* 8) + cos(X*5) + tanh (X*3);
% D = sin(4*X) + cos(5*X+rand(1,L)*0.0) + tanh(6 *X);D = D/6 +0.5;
m=20;
D = D';
c=rand(1,m)*2-1;
% c=randn(1,m);

Num =200;
a =rand(1,m)*2;
a =ones(1,m)*2;
w = randn(m,1); b=0;
z = zeros(m,1);
y = zeros(L,1);
mu = 0.15; mu2=0.5; mu3=0.1;
for kk =1: Num
    for ii=1:L
        x = X(:,ii);       
        d = D(ii);        
        for jj=1:m
            z(jj) = exp(-(x-c(jj))^2 * a(jj)^2); 
        end
        y(ii) = w' * z + b;
        e = d - y(ii);
        w = w + mu * e * z;
%         b = b + mu * e ;
        for jj=1:m
%             z(jj) = exp(-(x-c(jj))^2 * a(jj));
            c(jj) = c(jj) + mu2 * e *w(jj) * z(jj) * (x-c(jj));
            a(jj) =a(jj) - mu3 * e* w(jj) * z(jj) * (x-c(jj))^2 *a(jj);
        end
         
    end
    Err(kk) = norm(D-y);
end


%% H * w = D; i.e. Ax = b;
 %已知σ和c，相当于直接求LMS


for ii=1:L
    x = X(:,ii);
    for jj=1:m
        H(ii, jj) = exp(-(x-c(jj))^2 * a(jj)^2);
    end

end
w_LS = pinv(H) * D;
y_LS = H * w_LS;

norm(D-y)
norm(D - y_LS)
figure, plot(Err);
figure, hold on;
plot(X,D,'r'); plot(X, y, 'b');plot(X, y_LS, 'k');

legend('Original','RBF','LS')
[ norm(D - y), norm(D - y_LS) ]
