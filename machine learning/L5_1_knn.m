clear all; close all;
% k均值聚类方法
N = 300;
K = 2;
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
Ni = 10;
Dist_all=zeros(Ni,1);
 
c1 = data(:, round((N-1)*rand)+1);
c2 = data(:, round((N-1)*rand)+1);
c3 = data(:, round((N-1)*rand)+1);
c1 = randn(2,1);c2 = randn(2,1);c3 = randn(2,1);
figure;
for kk = 1 : Ni
    cnt1 = 0;
    cnt2 = 0;
    cnt3 = 0;
    clear Class1 Class2 Class3
    for ii = 1 : N
        dist(1) = norm(data(:, ii) - c1, 2);
        dist(2) = norm(data(:, ii) - c2, 2);
        dist(3) = norm(data(:, ii) - c3, 2);
        [a, b] = min(dist);
 
        switch b
            case 1
                cnt1 = cnt1 + 1;   
                Class1(cnt1) = ii; 
            case 2
                cnt2 = cnt2 + 1;   
                Class2(cnt2) = ii; 
            case 3
                cnt3 = cnt3 + 1;   
                Class3(cnt3) = ii; 
        end
    end
    c11 = sum(data(:, Class1).').' / cnt1;
    c22 = sum(data(:, Class2).').' / cnt2;
    c33 = sum(data(:, Class3).').' / cnt3;
    
    
    c1 = c11;
    c2 = c22;
    c3 = c33;
    
    for ii = 1 : cnt1
        Dist_all(kk) = Dist_all(kk) + norm(c1 - data(:,Class1(ii)));
    end
    for ii = 1 : cnt2
        Dist_all(kk) = Dist_all(kk) + norm(c2 - data(:,Class2(ii)));
    end
    for ii = 1 : cnt3
        Dist_all(kk) = Dist_all(kk) + norm(c3 - data(:,Class3(ii)));
    end
        
    
    hold off;
    plot(c1(1), c1(2), 'r+')
    hold on;  
    plot(c2(1), c2(2), 'b+')
    plot(c3(1), c3(2), 'k+')
  
    plot(data(1, Class1), data(2, Class1), 'ro')
    plot(data(1, Class2), data(2, Class2), 'bo')
    plot(data(1, Class3), data(2, Class3), 'ko')
    pause(0.5);
end
 

figure,plot(Dist_all)
[cnt1, cnt2, cnt3]
 
