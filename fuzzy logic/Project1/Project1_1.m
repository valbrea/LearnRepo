x1 = 4;
% x1 = 8;
X2 = 0 : 0.1 : 10; 
X3 = 0 : 0.1 : 10; 

L = 27;
C = [4, 3, 2.5, 6, 5.5, 5, 10, 9, 7, 3.5, 2.5, 2, 4.5, 3.5, 2, 7, 6, 5, 1.5, 1, 0.5, 4, 3, 2, 5.5, 4.5, 3];

% a1 = trapmf(x, [0, 0, 2, 5]);
% a2 = trimf(x, [0, 5, 10]);
% a3 = trapmf(x, [5, 8, 10, 10]);
for j = 1 : length(X2)
    for k = 1 : length(X3)
    u = 0;
    d = 0; 
        for i = 1 : L
        x2 = X2(:, j);
        x3 = X3(:, k);
        cl = C(:, i);
        if i <= 9  % A1 MF
            u1 = trapmf(x1, [0, 0, 2, 5]);
        else
            if i <= 18
                u1 = trimf(x1, [0, 5, 10]);
            else 
                u1 = trapmf(x1, [5, 8, 10, 10]);
            end
        end
 

        switch mod(i, 9) % A2 MF
        case {1, 2, 3}
            u2 = trapmf(x2, [0, 0, 2, 5]);
        case {4, 5, 6}
            u2 = trimf(x2, [0, 5, 10]);
        case {7, 8, 0}
            u2 = trapmf(x2, [5, 8, 10, 10]);
        end

        switch mod(i, 3) % A3 MF
        case 1
            u3 = trapmf(x3, [0, 0, 2, 5]);
        case 2
            u3 = trimf(x3, [0, 5, 10]);
        case 0
            u3 = trapmf(x3, [5, 8, 10, 10]);
        end
  % L´ÎÇóºÍ
        d = u1 * u2 * u3 + d;
        u = u1 * u2 * u3 * cl + u;  
        end

    YY(j,k) = u / d;
    end
end
figure;
mesh(X2, X3, YY);
