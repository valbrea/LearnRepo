clear all; close all;
% BP algorithm
X=-1:0.05:1;
% X = -2: 0.1:2;
X = [ 1 0 0 1; 1 0 1 0];
D = [ 0 0 1 1]
X=[0.5152	0.8173	1.0000 ;     0.8173	1.0000	0.7308;     1.0000	0.7308	0.1390;
     0.7308	0.1390	0.1087;     0.1390	0.1087	0.3520;     0.1087	0.3520	0.0000;]';

D=[0.7308 0.1390 0.1087 0.3520 0.0000 0.3761];

n = size(X,1);
L = size(X,2);
% D=[-0.9602,-0.5770,-0.0729,0.3771,0.6405,0.66,0.4609,0.1366,-0.2013 -0.4344,-0.5,-0.393,-0.1647,0.0988,0.3072,0.396,0.3449,0.1816,-0.0312,-0.2183,-0.3201];
% D=sin(X*5+randn(1,L)*0.0)+1;
% D= sin(X* 4) + cos(X*5) + tanh (X*3);
% % D = sin(4*X) + cos(5*X+rand(1,L)*0.0) + tanh(6 *X);D = D/6 +0.5;
% D = D/6 + 0.5; %% [0 1]

Num = 20000;
mu1 = 0.5; mu2 = 0.5; mu3 = 2; mu4 = 3;
m = 20;
W1 = randn(m, n); b1 = randn(m, 1);
W2 = randn(1, m); b2 = randn(1);

%%BP training
for kk = 1 : Num
    for ii = 1 : L
        x = X(:, ii);
        z2 = W1 * x + b1;
        a2 = 1 ./ (1+exp(-z2));
        z3 = W2 * a2 + b2;
        y(ii) = 1 ./ (1+exp(-z3));
        d = D(ii);
        e = d - y(ii);
        Jb1 = e * y(ii) * (1-y(ii));
        b2 = b2 + mu4 * Jb1;
        W2 = W2 + mu3 * Jb1 * a2';
        Jb2 = W2' .* a2 .* (1 - a2);
        b1 = b1 + mu2 * Jb1 * Jb2 ;
        W1 = W1 + mu1 * Jb1 * Jb2 * x';              
    end
    Err(kk) = norm(y-D);
end
        
        
figure, plot(Err);
figure, hold on;
plot(D,'ro'), plot(y,'b*');