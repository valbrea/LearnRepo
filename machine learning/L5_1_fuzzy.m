clear all
close all
clc
% 模糊聚类方法 
N = 300;
%% 产生样本
K = 1.5;
for iii = 1 : N
    if iii < 101
        data(:, iii) = K * randn(2, 1) + [3; 4];
    elseif (iii > 200)
        data(:, iii) = K * randn(2, 1) + [-3; 4];
    else
        data(:, iii) = K * randn(2, 1) + [-3; -4];
    end
end
 
figure; plot(data(1, :), data(2, :), 'ro')
 
%% 
Nc = 3; 
Ni = 30;
P = randperm(N);
c1 = data(:, P(1));
c2 = data(:, P(2));
c3 = data(:, P(3));
epss = 0.00001;
q = 2; % q只能=2
figure;
for kkk = 1 : Ni
    
    %% 更新隶属度
    for iii = 1 : N
        dr1 = norm(data(:, iii) - c1);
        dr2 = norm(data(:, iii) - c2);
        dr3 = norm(data(:, iii) - c3);
        if dr1 == 0
            dr1 = epss;
        end
        if dr2 == 0
            dr2 = epss;
        end
        if dr3 == 0
            dr3 = epss;
        end
        U(1, iii) = 1 / ((dr1 / dr1)^(1 / (q - 1)) + (dr1 / dr2)^(1 / (q - 1)) + (dr1 / dr3)^(1 / (q - 1)));
        U(2, iii) = 1 / ((dr2 / dr1)^(1 / (q - 1)) + (dr2 / dr2)^(1 / (q - 1)) + (dr2 / dr3)^(1 / (q - 1)));
        U(3, iii) = 1 / ((dr3 / dr1)^(1 / (q - 1)) + (dr3 / dr2)^(1 / (q - 1)) + (dr3 / dr3)^(1 / (q - 1)));
    end
    
    %% 更新类中心
    c11 = zeros(2, 1);
    c22 = zeros(2, 1);
    c33 = zeros(2, 1);
    for iii = 1 : N
        c11 = c11 + U(1, iii) .^2 * data(:, iii);
        c22 = c22 + U(2, iii) .^2 * data(:, iii);
        c33 = c33 + U(3, iii) .^2 * data(:, iii);
    end
    c11 = c11 / sum(U(1, :).^2);
    c22 = c22 / sum(U(2, :).^2);
    c33 = c33 / sum(U(3, :).^2);
%     figure; plot(U.')
    if ((norm(c11 - c1) < epss) && (norm(c22 - c2) < epss) && (norm(c33 - c3) < epss))
        break;
    end
    
    c1 = c11;
    c2 = c22;
    c3 = c33;
    
    %% 显示
    cnt1 = 1;
    cnt2 = 1;
    cnt3 = 1;
    clear Class1 Class2 Class3
    for iii = 1 : N
        tmp = U(:, iii);
        [a, b] = max(tmp);
 
        switch b
            case 1
                Class1(cnt1) = iii;    
                cnt1 = cnt1 + 1;
            case 2
                Class2(cnt2) = iii;    
                cnt2 = cnt2 + 1;
            case 3
                Class3(cnt3) = iii;    
                cnt3 = cnt3 + 1;
        end
    end
    
    hold off;
    plot(c1(1), c1(2), 'r+', 'markersize', 10, 'linewidth', 2)
    hold on;
    plot(c2(1), c2(2), 'b+', 'markersize', 10, 'linewidth', 2)
    plot(c3(1), c3(2), 'k+', 'markersize', 10, 'linewidth', 2)
    plot(data(1, Class1), data(2, Class1), 'ro')
    plot(data(1, Class2), data(2, Class2), 'bo')
    plot(data(1, Class3), data(2, Class3), 'ko')
    pause(0.5);
end
 
cnt1 = 1;
cnt2 = 1;
cnt3 = 1;
for iii = 1 : N
    tmp = U(:, iii);
    [a, b] = max(tmp);
    
    switch b
        case 1
            Class1(cnt1) = iii;    
            cnt1 = cnt1 + 1;
        case 2
            Class2(cnt2) = iii;    
            cnt2 = cnt2 + 1;
        case 3
            Class3(cnt3) = iii;    
            cnt3 = cnt3 + 1;
    end
end
 
figure; hold on;
plot(c1(1), c1(2), 'r+', 'markersize', 10, 'linewidth', 2)
plot(c2(1), c2(2), 'b+', 'markersize', 10, 'linewidth', 2)
plot(c3(1), c3(2), 'k+', 'markersize', 10, 'linewidth', 2)
plot(data(1, Class1), data(2, Class1), 'ro')
plot(data(1, Class2), data(2, Class2), 'bo')
plot(data(1, Class3), data(2, Class3), 'ko')
 
 

