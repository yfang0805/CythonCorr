#include "stats.h"
#include <cmath>
#include <iostream>
#include <string.h>

std::vector<std::vector<double> > ALPHA::function2(const std::vector<std::vector<double>> & X)
{
    int row_size = X.size();
    int col_size = X[1].size();

    //计算平均值
    std::vector<double> list_mean;

    for(int i = 0; i < row_size; i++){
        double sum_x = 0;
        for(int j = 0; j < col_size; j++){
            sum_x += X[i][j];
        }
        list_mean.push_back(sum_x / col_size);
    }
    

    //计算相关性矩阵
    std::vector<std::vector<double> > corr_matrix;

    for(int j = 0; j < col_size; j++){
        std::vector<double> corr_list;
        double r;
        double sum_X = 0;
        double sum_Y = 0;
        double sum_X2 = 0;
        double sum_Y2 = 0;
        double sum_XY =0;

        for (int i = 0; i < row_size; i++){
            sum_X += X[i][j];
            sum_Y += list_mean[i];
            sum_X2 += X[i][j] * X[i][j];
            sum_Y2 += list_mean[i] * list_mean[i];
            sum_XY += X[i][j] * list_mean[i];
            r = ((i + 1) * sum_XY - sum_X * sum_Y)/ (sqrt((i + 1) * sum_X2 - sum_X * sum_X) * sqrt((i + 1) * sum_Y2 - sum_Y * sum_Y));
            corr_list.push_back(r);
           
        }
        
        corr_matrix.push_back(corr_list);
    }

    return corr_matrix;
}
