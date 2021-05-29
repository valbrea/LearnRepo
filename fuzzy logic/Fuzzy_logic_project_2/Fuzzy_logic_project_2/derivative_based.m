%Apply back-propagation method to design a FLS
% Gaussian MFs, 4 antecedents,16 rules, height defuzzifier, product t-norms
% based on the Mackey-Glass chaotic time series in 1. with tao=40.
% Samples 1001-1504 are for training, and samples 1505-2000 are for testing.
% Provide initial values and final values for MF parameters, like Tables
% 4.7-4.9. Find RMSE for the tested data for 6 epochs.

% M, sigma are mxn matrix denotes the mean and std of
% antecedent Gaussian MFs (m rules, with n antecedent in each rule)
% c0 is mx1 vector, which denotes the height of consequents
% X is input matrix, Lxn matrix, each row is onw input.
% D is Lx1 vector which denotes the desired output

Mean_derivative = zeros(16,4); %M是均值，m条规则，n个antecedent，即16x4
sigma_derivative = zeros(16,4); %sigma是标准差std, the standard deviation
y_derivative = rand(16,1); %c0 is mx1 vector, which denotes the height of consequents，这里是[0,1]的随机数
y_output_derivative = zeros(496,1); %实际的输出值，也就是我们预测的输出值，和test_data-pair一样的维数
alpha = 0.2; %和书上相同β，不能用0.5，见page191

sigma_derivative(:,:) = 0.5240; %和书上相同，见page192
rule_no_derivative = 1;
mean_values = [0.3793 1.4272]; %和书上相同，见page191
for antecedent_1 = 1:2
    for antecedent_2 = 1:2
        for antecedent_3 = 1:2
            for antecedent_4 = 1:2
                Mean_derivative(rule_no_derivative,:) = [mean_values(antecedent_1) mean_values(antecedent_2) mean_values(antecedent_3) mean_values(antecedent_4)];
                rule_no_derivative = rule_no_derivative + 1;
            end
        end
    end
end

Table_47_initial_values = [Mean_derivative y_derivative];

RMSE_derivative = [];

for i = 1:6
    %X是输入数据，D是理想输出值
    %X是训练数据train_data_pair(:,1:p)，D是train_data_pair(:,p+1)
    [Mean_derivative,y_derivative,sigma_derivative] = train_sfls_type1(train_data_pairs(:,1:p),train_data_pairs(:,p+1),Mean_derivative,sigma_derivative,y_derivative,alpha);  
    y_output_derivative = sfls_type1(Mean_derivative,sigma_derivative,y_derivative,test_data_pairs(:,1:p));
    %这里的X是测试数据，与上面的X不同，C是训练数据的y值，对应于y_derivative，M对应于规则Mean_derivative
    
    Err_derivative = test_data_pairs(:,p+1) - y_output_derivative';
    Err_square_derivative = Err_derivative.* Err_derivative;
    RMSE_derivative(i) = sqrt(1/496 * sum(Err_square_derivative));
end
RMSE_derivative
Table_48_final_values = [Mean_derivative y_derivative];
Table_49_final_sigma = sigma_derivative;