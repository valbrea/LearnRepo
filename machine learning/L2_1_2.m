clear all;
close all;
L = 1000;
p = 4;
V = randn(1,L) * (0.2)^0.5;
wo = randn(p,1);
uu = randn(p,L);
dd = wo'*uu + V;

A = uu';
b = dd';%²»ÓÃ¼õV, VÊÇÔëÉù

w = pinv(A) * b;

norm(w-wo);
%Î¬ÄÉÂË²¨