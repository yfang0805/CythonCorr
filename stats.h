#ifndef STATS_H_
#define STATS_H_
#include <vector>

namespace ALPHA
{
    std::vector<double> function1(const std::vector<double> & X, const std::vector<double> & Y);
    std::vector<std::vector<double> > function1plus(const std::vector<std::vector<double>> & X, const std::vector<double> &y);
    std::vector<std::vector<double> > function2(const std::vector<std::vector<double>> & X);
    double sum(const std::vector<double> &v);
    double w_corr(const std::vector<double>&x, const std::vector<double>&y, double ls_ratio, double power);
}

#endif
