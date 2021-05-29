clear all, close all;
a = [1, 1, -1, 1, -1, -1];
b = [1, 1, 1, 1, 1, 1];
ma = mean(a);
mb = mean(b);
p1 = 0;
p2 = 0;
p3 = 0;
for i = 1 : 6
    p1 = (a(:, i) - ma) * (b(:, i) - mb) + p1;
    p2 = (a(:, i) - ma) ^ 2 + p2;
    p3 = (b(:, i) - mb) ^ 2 + p3;
end
p = p1 / (sqrt(p2) * sqrt(p3)) 
