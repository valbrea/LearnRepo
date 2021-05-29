data_bits=8472;
count = 0;
for i = 1 : 1000
    input = randi([0,1], 1, data_bits);
    output = BPSK(40, input);
    if isequal(input, output)
        count = count + 1;
    end 
end
ans = count / 1000
