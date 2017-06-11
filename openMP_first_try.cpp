#include <iostream>
#include <stdio.h>
#include <omp.h>


int main(int argc, char *argv[])
{
    double factor = 1.0;
    double sum = 0.0;
    double pi_approx ;
    #pragma omp parallel for num_threads(1000)\
     reduction(+: sum)  private(factor)
    for(int i = 0; i < 10000; ++i)
    {
        //缺省情况下任何在循环前面声明的变量在线程间都是共享的(除了循环变量）
        //所以对factor的访问是有冲突的，可以将其设置为线程的私有变量
        factor = (i % 2) ? -1 : 1;
        sum += factor/(2 * i + 1);
    }
    pi_approx = 4 * sum;
    printf("%f\n", pi_approx);
    return 0;
}
