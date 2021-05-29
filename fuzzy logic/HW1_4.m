clear all; close all;

T = true;
F = false;

p = [T T T T F F F F]';
q = [T T F F T T F F]';
r = [T F T F T F T F]';
%% 1
a = p & (q | r);
b = (p & q) | (p & r);
%% 2
c = p | (q & r);
d = (p | q) & (p | r);
%% 3
e = p & (q & r);
f = (p & q) & r;
%% 4
g = p | (q | r);
h = (p | q) | r;

A = [p q r]
A1 = [p q r a b]
A2 = [p q r c d]
A3 = [p q r e f]
A4 = [p q r g h]