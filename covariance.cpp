//
// Created by manout on 17-6-17.
//

#include <omp.h>
#include <vector>
#include <cstddef>
#include <opencv>

double average(const std::vector<float>& data)
{
    double sum = 0.0;

    for(int i = 0; i < data.size(); ++i)
    {
        sum += data[i];
    }

    return sum / data.size();
}

double average_p(const std::vector<float>& data)
{
    double sum = 0.0;

#pragma omp parallel for  reduction(+ : sum)
    for(int i = 0; i < data.size(); ++i)
    {
        sum += data[i];
    }

    return sum / data.size();
}

//假设向量x与向量y的维数是相等的，并没有检查
// 协方差计算公式 E[(X - E[X])(Y - E[Y]]
double covariance(std::vector<float>& x, std::vector<float>& y)
{
    double aver_x = average(x);
    double aver_y = average(y);
    float mid = 0;

    for (int i = 0; i < x.size(); ++i)
    {
        mid += (x[i]- aver_x) * (y[i] - aver_y);
    }

    return mid / x.size();
}

double covariance_p(std::vector<float>& x, std::vector<float>& y)
{
    double aver_x = average_p(x);
    double aver_y = average_p(y);
    float mid = 0;

#pragma omp parallel for  reduction(+ : mid)
    for (int i = 0; i < x.size(); ++i)
    {
        mid += (x[i]- aver_x) * (y[i] - aver_y);
    }

    return mid / x.size();
}
