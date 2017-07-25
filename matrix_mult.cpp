#include <iostream>
const int n = 100;

int main()
{
    int mat_A [n][n];
    int mat_B [n][n];
    int mult_ret[n][n];

    for(int i = 0; i < n ; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            mult_ret[i][j] = 0;
            for(int k = 0; k < n; ++k)
            {
                mult_ret[i][j] += mat_A[j][k] * mat_B[k][j];
            }
        }
    }

    for(int i = 0 ;i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            //一个使用局部性原理优化矩阵相乘的方法
            //之前的算法直接根据公式进行计算，现在的算法消除了步长为n的一次访问
            //而是将内存的访问转化为步长为1

            //先缓存当前mat_A的元素值，是为了避免步长过大
            int r = mat_A[j][i];
            for(int k = 0; k < n; ++j)
            {
                //根据公式，mult_ret[j][k] += r * mat_B[i][k]
                //mult_ret[j]行元素的第一个和数是r与mat_B的[i]的行相乘的积
                //mult_ret[i][j]的每个元素计算完成是当mat_A,mat_B全部访问完后才会完成
                mult_ret[j][k] += r * mat_B[i][k];
            }
        }
    }

}
