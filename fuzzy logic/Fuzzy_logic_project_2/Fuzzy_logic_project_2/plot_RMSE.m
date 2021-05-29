figure,hold on;
plot(1:6,RMSE_derivative);
RMSE_OP=[RMSE RMSE RMSE RMSE RMSE RMSE];
plot(1:6,RMSE_OP);
legend("derivative","one-pass");

Table_47_initial_values;
Table_48_final_values;
Table_49_final_sigma;