//
// Created by manout on 17-7-14.
//

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <mpi/mpi.h>
#include <functional>
#include <cmath>

#define MAX_STRING  100

double Trap(std::function<double(double)>, double, double, int, double);
double fun(double);
int main(int argc, char * argv[])
{
    int my_rank, comm_sz, n = 1024, local_n;
    double a = 0.0, b = 4.0, h, local_a, local_b;
    double local_int, total_int;
    MPI_Init(nullptr, nullptr);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    h = (b - a) / n;
    local_n = n / comm_sz;
    local_a = a + my_rank * local_n * h;
    local_b = local_a + local_n * h;
    local_int = Trap(fun, local_a, local_b, local_n, h);
    /*if(my_rank not_eq 0)
    {
        MPI_Send(&local_int, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        total_int = local_int;
        for (int i = 1; i < comm_sz; ++i)
        {
            MPI_Recv(&local_int, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_int += local_int;
        }
    }
*/
    //mpi　的集合通信函数，归约函数，将所有进程的 local_int 累加到 0 号进程的total_int 上
    MPI_Reduce(&local_int, &total_int, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(my_rank == 0)
    {
        printf("%f", total_int);
    }
    MPI_Finalize();
    return 0;
}

//　先试试简单函数
double fun(double x)
{
    return x;
}

double Trap(std::function<double(double)> f, double left_endpt, double right_endpt, int trap_count, double base_len)
{
    double estimate, x;
    // 梯形积分法
    estimate = (f(left_endpt) + f(right_endpt)) / 2.0;
    for (int i = 0; i < trap_count - 1; ++i)
    {
        x = left_endpt + i * base_len;
        estimate += f(x);
    }

    return estimate * base_len;
}