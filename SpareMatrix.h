//
// Created by manout on 17-7-25.
//

#ifndef PARALLEL_COMPUTING_NOTE_SPAREMATRIX_H
#define PARALLEL_COMPUTING_NOTE_SPAREMATRIX_H

#include <vector>
#include <cstddef>

class SpareMatrix
{
    virtual std::vector<double>& operator[](size_t ) = 0;
};

// 三元组存储法
class COO_SpareMatrix: public SpareMatrix
{
private:
    std::vector<size_t> row;
    std::vector<size_t> col;
    std::vector<double> values;
};

// 行偏移法
class CSR_SpareMatrix: public SpareMatrix
{
private:
    std::vector<size_t> row_offset;
    std::vector<size_t> rol;
    std::vector<double> values;
};

// ELL法
class ELL_SpareMatrix: public SpareMatrix
{
private:
    std::vector<std::vector<size_t>> col_indices;
    std::vector<std::vector<double>> values;
};

// 对角线存储法
class DLA_SpareMatrix: public SpareMatrix
{
private:
    std::vector<double> values;
};

class HYB_Matrix: public SpareMatrix
{
private:
    ELL_SpareMatrix ell;
    COO_SpareMatrix coo;
};



#endif //PARALLEL_COMPUTING_NOTE_SPAREMATRIX_H
