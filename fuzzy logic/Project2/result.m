%% 结果和绘图
initial_values
final_values = [mean_SD, ybar_SD] % 最终centers & ybar表
final_sigmas = sigma_SD % 最终std表

figure, hold on;
plot(1 : 6, RMSE_OP * ones(1, 6));
plot(1 : 6, RMSE_SD);
legend('one pass', 'steepest descent');
title('RMSE');