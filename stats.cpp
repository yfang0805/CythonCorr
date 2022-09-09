#include "stats.h"
#include <cmath>

double ALPHA::sum(const std::vector<double> & v)
{
    double r = 0;
    for (int i=0; i<v.size();++i){
        r += v[i];
    }
    return r;
}

double ALPHA::w_corr(const std::vector<double>&x, const std::vector<double>&y, double ls_ratio, double power)
{
    int x_size = x.size();
    std::vector<double> w(x_size,0);
    for (int i=0; i<x_size; i++){
        if (x[i]>0) w[i] = powf(x[i],power)*ls_ratio;
        else w[i] = powf(-x[i],power);
    }
    double w_sum = sum(w);
    for (int i=0; i<x_size; i++) w[i] = w[i]/w_sum;

    double w_sum_x = 0;
    double w_sum_x2 = 0;
    double w_sum_y = 0;
    double w_sum_y2 = 0;
    double w_sum_xy = 0;
    for (int i=0; i<x_size; i++){
        w_sum_x += w[i]*x[i];
        w_sum_x2 += w[i]*x[i]*x[i];
        w_sum_y += w[i]*y[i];
        w_sum_y2 += w[i]*y[i]*y[i];
        w_sum_xy += w[i]*y[i]*x[i];
    }
    double w_devX = fabs(x_size*w_sum_x2 - w_sum_x*w_sum_x);
    double w_devY = fabs(x_size*w_sum_y2 - w_sum_y*w_sum_y);

    double ret = (x_size*w_sum_xy - w_sum_x*w_sum_y)/ (sqrt(w_devX) * sqrt(w_devY));
    return ret;
}
