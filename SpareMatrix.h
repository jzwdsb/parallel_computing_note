//
// Created by manout on 17-7-25.
//

#ifndef PARALLEL_COMPUTING_NOTE_SPAREMATRIX_H
#define PARALLEL_COMPUTING_NOTE_SPAREMATRIX_H

#include <vector>
#include <cstddef>
#include <cfloat>

#define NON_EXIST       DBL_MAX
// 基本矩阵类型
using simpleMatrix = std::vector<std::vector<double>>;

// 包含一行元素的列号和元素值的 pair
using rowElement = std::pair<std::vector<size_t>, std::vector<double>>;

// 稀疏矩阵接口
class SpareMatrix
{
public:

    virtual rowElement getRow(size_t r) = 0;
    virtual double getEle(size_t r, size_t c) = 0;
};

// 三元组存储法
class COO_SpareMatrix: public SpareMatrix
{
public:
    COO_SpareMatrix() = default;
    COO_SpareMatrix(const COO_SpareMatrix&) = default;
    COO_SpareMatrix(COO_SpareMatrix&&)noexcept = default;

    explicit COO_SpareMatrix(const simpleMatrix& mat);
    COO_SpareMatrix&operator=(const COO_SpareMatrix&) = default;
    COO_SpareMatrix&operator=(COO_SpareMatrix&&)noexcept = default;
    COO_SpareMatrix&operator=(const simpleMatrix& mat);
    ~COO_SpareMatrix() = default;
    rowElement getRow(size_t r) override;
    double getEle(size_t r, size_t c) override;
private:
    void helpInit(const simpleMatrix& mat);

    size_t  rows, cols;
    size_t  ele_count;
    size_t  max_ele_count;
    std::vector<size_t> row;
    std::vector<size_t> col;
    std::vector<double> values;
};

// 行偏移法
class CSR_SpareMatrix: public SpareMatrix
{
public:
    CSR_SpareMatrix() = default;
    CSR_SpareMatrix(const CSR_SpareMatrix&) = default;
    CSR_SpareMatrix(CSR_SpareMatrix&&)noexcept = default;

    explicit CSR_SpareMatrix(const simpleMatrix& mat);
    CSR_SpareMatrix&operator=(const CSR_SpareMatrix&) = default;
    CSR_SpareMatrix&operator=(CSR_SpareMatrix&&) = default;
    CSR_SpareMatrix&operator=(const simpleMatrix& mat);
    ~CSR_SpareMatrix() = default;
    rowElement getRow(size_t r) override;
    double getEle(size_t r, size_t c) override;
private:
    void helpInit(const simpleMatrix& mat);
    size_t rows, cols;
    size_t ele_count;
    size_t max_ele_count;
    std::vector<size_t> row_offset;
    std::vector<size_t> col;
    std::vector<double> values;
};

// ELL法
/*
 *      由于实现的原因这是个col_indices 和 values 是形状相同的锯齿型矩阵
 * 这倒也省去了某些行过长造成空间浪费的情况，或许不算ELL的标准实现
 */
class ELL_SpareMatrix: public SpareMatrix
{
public:

    ELL_SpareMatrix() = default;
    ELL_SpareMatrix(const ELL_SpareMatrix&) = default;
    ELL_SpareMatrix(ELL_SpareMatrix&&) = default;

    explicit ELL_SpareMatrix(const simpleMatrix& mat);
    ELL_SpareMatrix&operator=(const ELL_SpareMatrix&) = default;
    ELL_SpareMatrix&operator=(ELL_SpareMatrix&&) = default;
    ELL_SpareMatrix&operator=(const simpleMatrix& mat);
    ~ELL_SpareMatrix() = default;
    rowElement getRow(size_t r) override;
    double getEle(size_t r, size_t c) override;
private:
    void helpInit(const simpleMatrix& mat);
    size_t rows, cols;
    size_t ele_count;
    size_t max_ele_count;
    std::vector<std::vector<size_t>> col_indices;
    std::vector<std::vector<double>> values;
};

// 对角线存储法
class DLA_SpareMatrix: public SpareMatrix
{
public:
    DLA_SpareMatrix() = default;
    DLA_SpareMatrix(const DLA_SpareMatrix&) = default;
    DLA_SpareMatrix(DLA_SpareMatrix&&) = default;

    explicit DLA_SpareMatrix(const simpleMatrix& mat);
    DLA_SpareMatrix&operator=(const DLA_SpareMatrix&) = default;
    DLA_SpareMatrix&operator=(DLA_SpareMatrix&&) = default;
    DLA_SpareMatrix&operator=(const simpleMatrix& mat);
    ~DLA_SpareMatrix() = default;
    rowElement getRow(size_t r) override;
    double getEle(size_t r, size_t c) override;
private:
    void helpInit(const simpleMatrix& mat);
    size_t rows, cols;
    size_t ele_count;
    size_t max_ele_count;
    std::vector<double> values;
};

class HYB_Matrix: public SpareMatrix
{
public:
    HYB_Matrix() = default;
    HYB_Matrix(const HYB_Matrix&) = default;
    HYB_Matrix(HYB_Matrix&&) = default;

    explicit HYB_Matrix(const simpleMatrix& mat);
    HYB_Matrix&operator=(const HYB_Matrix&) = default;
    HYB_Matrix&operator=(HYB_Matrix&&) = default;
    HYB_Matrix&operator=(const simpleMatrix& mat);
    ~HYB_Matrix() = default;
    rowElement getRow(size_t r) override;
    double getEle(size_t r, size_t c) override;
private:
    size_t rows, cols;
    size_t ele_count;
    size_t max_ele_count;
    ELL_SpareMatrix ell;
    COO_SpareMatrix coo;
};



#endif //PARALLEL_COMPUTING_NOTE_SPAREMATRIX_H
