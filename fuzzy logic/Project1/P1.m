clear all; close all;
x = 0:0.1:10;
%% Antecedent MFs
a1 = trapmf(x, [0, 0, 2, 5]);
a2 = trimf(x, [0, 5, 10]);
a3 = trapmf(x, [5, 8, 10, 10]);

figure;
hold on;
plot(x,a1);
plot(x,a2);
plot(x,a3);
axis([0, 10, 0, 1.5]);
legend('near, low' ,'moderate', 'far, high');
title('Antecedent MFs');

%% Consequent MFs
y1 = trapmf(x, [0, 0, 1, 3]);
y2 = trimf(x, [1, 3, 5]);
y3 = trimf(x, [3, 5, 7]);
y4 = trimf(x, [5, 7, 9]);
y5 = trapmf(x,[7, 9, 10, 10]);

figure;
hold on;
plot(x,y1);
plot(x,y2);
plot(x,y3);
plot(x,y4);
plot(x,y5);
axis([0, 10, 0, 1.5]);
legend('very weak' ,'weak', 'medium', 'strong', 'very strong');
title('Consequent MFs');