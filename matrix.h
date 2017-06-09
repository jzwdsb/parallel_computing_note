#ifndef MATRIX
#define MATRIX

class matrix
{
public:
    using size_t  = unsigned int;
    
    matrix():row(0), col(0), mat(nullptr){}
    matrix(size_t r, size_t c);
    matrix(matrix&& other);
    int* operator[](size_t);

private:
    size_t row, col;
    int* mat;
};
