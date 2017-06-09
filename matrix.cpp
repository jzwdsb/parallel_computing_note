#include <matrix.h>
#include <string.h>
#include <memory.h>
matrix::matrix():row(0),col(0), mat(nullptr){}

matrix::matrix(size_t r, size_t c):row(r), col(c)
{
    this->mat = new int [r * c];
    memset(mat, 0, sizeof(int)* r * c);
}


int* matrix::operator [](size_t r)
{
    return this->mat + r * this->col;
}