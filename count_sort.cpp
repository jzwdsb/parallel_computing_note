#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <vector>

void count_sort(std::vector<int> &a)
{
    int count;
    unsigned  long len;
    len = a.size();
    std::vector<int> buffer(len);
    #pragma omp parallel for num_threads(100) private (count)
    for (int i = 0; i < len; ++i)
    {
        count = 0;
        for (int j = 0; j < len; ++j)
        {
            if(a[j] < a[i])
                ++count;
            else if(a[j] == a[i] and j < i)
                ++count;
        }
        buffer[count] = a[i];
    }
    a = buffer;
}

int main(int argc, char *argv[])
{
    std::vector<int> a;
    clock_t start_time, end_time;

    srand(unsigned(time(0)));
    for (int i = 0; i < 10000; ++i)
    {
        a.push_back(random());
    }
    for (auto & num : a)
    {
        printf("%d\t", num);
    }
    printf("\n");
    start_time = clock();
    count_sort(a);
    for(auto & num : a)
    {
        printf("%d\t", num);
    }
    end_time = clock();

    printf("\n%ld\n", (end_time - start_time) / 1000);

}
