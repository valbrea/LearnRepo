clear all; close all;
T = true;
F = false;

p = [T T F F]';
q = [T F T F]';

pp = [T T T T F F F F]';
qq = [T T F F T T F F]';
rr = [T F T F T F T F]';
%% 1
a = p & q;
b = p | q;
c = ~a | b;

%% 2
x = ~(pp & qq) | rr;
y = (~pp | rr) | (~qq | rr);
z = (x == y)

A1 = [p q a b c]
A2 = [pp qq rr x y z]

