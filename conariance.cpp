//
// Created by manout on 17-6-17.
//

#include <omp.h>
#include <vector>
#include <sys/sysinfo.h>

float average(const std::vector<float>& data)
{
    double sum = 0.0;
    //获取当前系统可用的内核数量
    const int core_num = get_nprocs();
    const auto num_count = data.size();
    #pragma omp parallel for num_threads(num_count / core_num) reduction(+ : sum) schedule(static, 1)
    for(std::vector<float>::iterator num_it = data.begin(); num_it not_eq data.end(); ++num_it)
    {
        sum += num;
    }

    return sum / data.size();
}

float covariance(std::vector<float>& x, std::vector<float> y)
{
    aver_x =
}
