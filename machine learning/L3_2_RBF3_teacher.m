clear all ; close all;
X = -1 : 0.1 : 1;
D= sin(X* 10) + cos(X*5 + randn*10 ) + tanh (X*3 + randn*6);
D= sin(X* 4) + cos(X*5  ) + tanh (X*3 );

% X = [ 1 0 0 1; 1 0 1 0];
% D = [ 0 0 1 1];
L = length(D);
n = size(X,1);
m = 30;
w = randn(m+1 ,1);
c = rand(n,m) * 2 - 1;
a = rand(1,m) * 2;
h = zeros(m+1, 1);
Num = 100;
mu1 = 0.3; mu2 = 0.1; mu3 = 0.1;
%% TRAINING
for kk = 1 : Num
    
    for ii = 1 : L
        x = X(:, ii);
        d = D(ii);
        for jj = 1 : m
            h(jj) = exp( - ( x - c(:, jj) )' *( x - c(:, jj) ) * a(jj)^2 );
        end
        h(m+1) = 0;
        y(ii) = w' * h;
        e = d - y(ii);
        w = w + mu1 * e * h;
        for jj = 1 : m
            %           c(jj) = c(jj) + mu2 * e * w(jj) * h(jj) * ( x-c(jj)) * a(jj)^2;
            c(:,jj) = c(:,jj) + mu2 * e * w(jj) * h(jj) * ( x-c(:,jj));
 %            a(jj) = a(jj) - mu3 * e * w(jj) * h(jj) * ( x-c(jj))^2 * a(jj);
            a(jj) = a(jj) - mu3 * e * w(jj) * h(jj) * ( x-c(:, jj))' * ( x-c(:, jj)) *1;
        end
    end
    Err(kk) = norm(D-y);
end


for ii = 1 : L
    x = X(:, ii);
    for jj = 1 : m
        h(jj) = exp( - ( x - c(:,jj) )' * ( x - c(:,jj) ) * a(jj)^2 );
    end
    h(m+1) = 0;
    y(ii) = w' * h;
end

figure, hold on;
plot(X, D,'o'); plot(X, y,'r*');
legend('REAL','TRAIN');
figure,plot(Err)