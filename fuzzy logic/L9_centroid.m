clear all; close all;
%% How to find centroid
x = [0 : 0.1 : 10];
y = trapmf(x, [2, 5, 8, 8]);
z = defuzz(x, y, 'centroid');
