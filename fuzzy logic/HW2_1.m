clear all, close all;

%% Antecedent Membership Functions
x = 0:0.1:10; % X1: Near, Far; X2: Low, High
A1 = sigmf(x,[1, 5]); % Far & High
A2 = sigmf(x,[-1, 5]); % Near & Low
figure, hold on;
plot (x, A1), plot (x, A2);
legend('Far, High', 'Near, Low');
xlabel('x');


%% Consequent Membership Functions
y = 0:0.1:1;
C1 = trapmf(y, [0, 0, 0.2, 0.5]); % Low
C2 = trimf(y, [0, 0.5, 1]); % Moderate
C3 = trapmf(y, [0.5, 0.8, 1, 1]); % High
figure, hold on;
plot (y, C1), plot (y, C2), plot (y, C3);
legend('Low', 'Moderate', 'High');
xlabel('y');
z1 = defuzz(y, C1, 'centroid');
z2 = defuzz(y, C2, 'centroid');
z3 = defuzz(y, C3, 'centroid');