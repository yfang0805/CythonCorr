#include "stats.h"
#include <cmath>
#include <iostream>
#include <string.h>

std::vector<double> ALPHA::function1(const std::vector<double> & X, const std::vector<double> & Y)
{
    int X_size = X.size();
    double sum_X = 0;
    double sum_Y = 0;
    double sum_X2 = 0;
    double sum_Y2 = 0;
    double sum_XY =0;
    double r;

    std::vector<double> corr_list;
    for (int i = 0; i < X_size; i++){
        sum_X += X[i];
        sum_Y += Y[i];
        sum_X2 += X[i] * X[i];
        sum_Y2 += Y[i] * Y[i];
        sum_XY += X[i] * Y[i];
        r = ((i + 1) * sum_XY - sum_X * sum_Y)/ (sqrt((i + 1) * sum_X2 - sum_X * sum_X) * sqrt((i + 1) * sum_Y2 - sum_Y * sum_Y));
        corr_list.push_back(r);
    }
    
    return corr_list;
}

std::vector<std::vector<double> > ALPHA::function1plus(const std::vector<std::vector<double>> & X, const std::vector<double> &y)
{
    // X是pd.DataFrame转换成的numpy二维数组，y为一列数据，function1plus计算X的每一列与y计算返回的expanding相关性列，并拼接成一张pd.DataFrame
    int row_size = X.size();
    int col_size = X[1].size();

    std::vector<std::vector<double> > corr_table;
    for (int j=0; j < col_size; j++){
        std::vector<double> X_list;
        for (int i=0; i < row_size; i++){
            X_list.push_back(X[i][j]);
        }   
        std::vector<double> corr_list;
        corr_list = function1(X_list, y);
        corr_table.push_back(corr_list);
    }
    return corr_table;
}
