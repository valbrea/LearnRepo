clear all; close all;
x1=[0 1]; 
x2=[0 1]; 
x3=[0 1];
x4=[0 1];
[X4,X3,X2,X1] = ndgrid(x4,x3,x2,x1);
combinatorics=[X1(:) X2(:) X3(:) X4(:)]; %所有排列组合情况
