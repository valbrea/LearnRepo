%Similar to Fig 4, generate one decision example for clusterhead election.

nodes = rand(100,3)*10;
nodes_xy = rand(100,2)*100;
center = [50 50];
dist = [];
min_dist = sqrt(50*50*2);
%figure,hold on;
for i = 1:100
    dist(i) = sqrt((nodes_xy(i,1) - center(1))^2 + (nodes_xy(i,2) - center(2))^2);
    nodes(i,1) = dist(i) / min_dist * 10;
end

ex_y_cos = [];
ex_firing_levels = [];
ex_cos_rules = [];
for i = 1:100
    for j = 1:27
        current_x = nodes(i,:);
        tmp = 1;
        for k = 1:3
            if rules(j,k) == near || rules(j,k) == low
                tmp = tmp * trapmf(current_x(k),[0,0,2,5]);
            elseif rules(j,k) == moderate
                tmp = tmp * trimf(current_x(k),[0,5,10]);
            elseif rules(j,k) == far || rules(j,k) == high
                tmp = tmp * trapmf(current_x(k),[5,8,10,10]);
            end
        end
        ex_firing_levels(i,j) = tmp;
        if rules(j,4) == very_weak
            tmp = CG_Very_Weak;
        elseif rules(j,4) == weak
            tmp = CG_Weak;
        elseif rules(j,4) == medium
            tmp = CG_Medium;
        elseif rules(j,4) == strong
            tmp = CG_Strong;
        elseif rules(j,4) == very_strong
            tmp = CG_Very_Strong;
        end
        ex_cos_rules(i,j) = ex_firing_levels(i,j) * tmp;
    end
    denominator = sum(ex_firing_levels(i,:));  %·ÖÄ¸
    numerator = sum(ex_cos_rules(i,:));  %·Ö×Ó
    ex_y_cos(i) = numerator / denominator;
end
[max_y index_y] = max(ex_y_cos)
[max_battery index_b] = max(nodes(:,2))
[min_dist index_d] = min(nodes(:,1))
figure,hold on;
for i = 1:100
    if i == index_y
        plot(nodes_xy(index_y,1),nodes_xy(index_y,2),"sr",'MarkerSize',12);
    elseif i == index_b
        plot(nodes_xy(index_b,1),nodes_xy(index_b,2),"vr",'MarkerSize',12);
    elseif i == index_d
        plot(nodes_xy(index_d,1),nodes_xy(index_d,2),"pr",'MarkerSize',12);
    else
        plot(nodes_xy(i,1),nodes_xy(i,2),"ob");
    end
end

