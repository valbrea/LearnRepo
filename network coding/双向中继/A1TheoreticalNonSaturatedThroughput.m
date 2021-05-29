% 算法1理论不饱和吞吐量
function [throughput] = A1TheoreticalNonSaturatedThroughput (time)

    alpha = 0.9;
    beta = 0.8;

    N = 4; % 中继节点个数
    Tr = mod(N + 1, 3) + 2 * N;

    if 0 <= time && time < N
        throughput = 0;
    elseif N <= time && time < Tr
        throughput = alpha * (1 + fix((time - N) / 3)) / (time + 1);
    elseif time >= Tr
        throughput = (alpha * fix((time - N) / 3) + beta * fix((time - Tr) / 3) + alpha + beta)/ (time + 1);
    end

end
