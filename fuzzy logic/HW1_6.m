clear all; close all;

x = 0:0.1:10;
fa = exp(-1 / 2 .* (x - 3).^2 );
fb = exp(-1 / 2 .* (x - 4).^2 );

% figure; hold on;
% plot(x, fa);plot(x, fb);

%% 1
t_conorm1 = max(fa, fb);
t_conorm2 = fa + fb;
t_conorm2 ( t_conorm2 >= 1 ) = 1;

figure; hold on;
plot(x, t_conorm1);plot(x, t_conorm2);
title('t-conorms');
legend('maximum','algebraic sum');

%% 2 
t_norm1 = min( fa, fb);
t_norm2 =  fa .* fb;

figure; hold on;
plot(x, t_norm1);plot(x, t_norm2);
title('t-norms');
legend('minimum','algebraic product');