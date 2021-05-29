% 算法2理论吞吐量（未完成）
function [throughput] = A2TheoreticalThroughput (time, gamma)
Tr = mod(n + 1, 3) + 2 * n;
data_bits = 8472;

p_e = 0.5 * (1 - sqrt(gamma / (1 + gamma)));
theta = 1 - (1 - p_e).^data_bits; % p_e^i = p_e^i+1时
capital_theta = (1 - theta).^ (n + 1);
A = 1 + fix((time - n) / 3);
B = 1 + fix((time - Tr) / 3);

A_apostrophe = 0;
B_apostrophe = 0;

for k = 1 : A
    C_ak = factorial(A) / factorial(A - k) * factorial(k);
    P_ak = C_ak * capital_theta.^k * capital_theta.^(A - k);
    A_apostrophe = P_ak * k + A_apostrophe;
end

for k = 1 : B
    C_bk = factorial(B) / factorial(B - k) * factorial(k);
    P_bk = C_bk * capital_theta.^k * capital_theta.^(B - k);
    B_apostrophe = P_bk * k + B_apostrophe;
end
throughput =  (A_apostrophe +  B_apostrophe) / (time + 1);

end


