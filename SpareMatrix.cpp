//
// Created by manout on 17-7-25.
//

#include <cassert>
#include <algorithm>
#include "SpareMatrix.h"

using std::vector;


COO_SpareMatrix::COO_SpareMatrix(const simpleMatrix & mat)
{
    helpInit(mat);
}

COO_SpareMatrix &COO_SpareMatrix::operator=(const simpleMatrix &mat)
{
    this->row.clear();
    this->col.clear();
    this->values.clear();
    helpInit(mat);
    return *this;
}

void COO_SpareMatrix::helpInit(const simpleMatrix &mat)
{
    this->rows = mat.size();
    this->cols = mat[0].size();
    for(size_t r = 0; r < rows; ++r)
    {
        for (size_t c = 0; c < cols; ++c)
        {
            if(mat[r][c] > 1e-6)
            {
                this->row.push_back(r);
                this->col.push_back(c);
                this->values.push_back( mat[r][c]);
            }
        }
    }
    this->ele_count = this->values.size();
    this->max_ele_count = this->rows * this->cols;
    assert(row.size() == col.size());
}

rowElement COO_SpareMatrix::getRow(size_t r)
{
    assert(r < this->rows);
    vector<size_t> col_indices;
    vector<double> values;

    size_t index;
    index = static_cast<size_t>(std::find(this->row.begin(), this->row.end(), r) - this->row.begin());
    while(r == this->row[index])
    {
        col_indices.push_back(this->col[index]);
        values.push_back(this->values[index]);
        ++index;
    }

    return std::make_pair(col_indices, values);
}

double COO_SpareMatrix::getEle(size_t r, size_t c)
{
    assert(r < this->rows and c < this->cols);
    size_t index;
    index = static_cast<size_t>(std::find(this->row.begin(), this->row.end(), r) - this->row.begin());
    while(r == this->row[index] and c not_eq this->col[index])
        ++index;
    if(r not_eq this->row[index])
        return 0;
    return this->values[index];
}



CSR_SpareMatrix::CSR_SpareMatrix(const simpleMatrix &mat)
{
   helpInit(mat);
}

CSR_SpareMatrix &CSR_SpareMatrix::operator=(const simpleMatrix &mat)
{
    this->col.clear();
    this->row_offset.clear();
    this->values.clear();
    helpInit(mat);
    return *this;
}

void CSR_SpareMatrix::helpInit(const simpleMatrix &mat)
{
    this->rows = mat.size();
    this->cols = mat[0].size();
    size_t rowOffset = 0;
    for (size_t r = 0; r < this->rows; ++r)
    {
        this->row_offset.push_back(rowOffset);
        for (size_t c = 0; c < this->cols; ++c)
        {
            if (mat[r][c] > 1e-6)
            {
                this->col.push_back(c);
                this->values.push_back(mat[r][c]);
                ++rowOffset;
            }
        }
    }
    this->ele_count = this->values.size();
    this->max_ele_count = this->rows * this->cols ;
}

rowElement CSR_SpareMatrix::getRow(size_t r)
{
    assert(r < this->rows);
    vector<size_t> colIndices;
    vector<double> vals;

    size_t offset = this->row_offset[r];
    size_t eleCount  = this->row_offset[r + 1] - this->row_offset[r];

    while(eleCount not_eq 0)
    {
        colIndices.push_back(this->col[offset]);
        vals.push_back(this->values[offset]);
        ++offset;
        --eleCount;
    }
    return std::make_pair(colIndices, vals);
}

double CSR_SpareMatrix::getEle(size_t r, size_t c)
{
    assert(r < this->rows and c < this->cols);
    size_t row_length = this->row_offset[r + 1] - this->row_offset[r];
    size_t offset = this->row_offset[r];
    if(row_length == 0)
        return 0;
    while(offset < this->row_offset[r + 1] and this->col[offset++] not_eq c)  ;
    if (offset == this->row_offset[r + 1])
        return 0;
    return this->values[offset];
}


ELL_SpareMatrix::ELL_SpareMatrix(const simpleMatrix &mat)
{
    helpInit(mat);
}


ELL_SpareMatrix &ELL_SpareMatrix::operator=(const simpleMatrix &mat)
{
    this->col_indices.clear();
    this->values.clear();
    helpInit(mat);
    return *this;

}


void ELL_SpareMatrix::helpInit(const simpleMatrix &mat)
{
    this->rows = mat.size();
    this->cols = mat[0].size();
    size_t eleNum = 0;
    for (size_t r = 0; r < this->rows; ++r)
    {
        for (size_t c = 0; c < this->cols; ++c)
        {
            this->col_indices.emplace_back();
            this->values.emplace_back();
            if(mat[r][c] > 1e-6)
            {
                this->col_indices[r].push_back(c);
                this->values[r].push_back(mat[r][c]);
                ++eleNum;
            }
        }
    }
    this->ele_count = eleNum;
    this->max_ele_count = this->rows * this->cols;
}

rowElement ELL_SpareMatrix::getRow(size_t r)
{
    assert(r < this->rows);
    return std::make_pair(this->col_indices[r], this->values[r]);
}

double ELL_SpareMatrix::getEle(size_t r, size_t c)
{
    assert(r < this->rows and c < this->cols);
    size_t i = 0;
    while(i < this->col_indices[r].size() and i not_eq this->col_indices[r][i])
        ++i;
    if (i == this->col_indices[r].size())
        return 0;
    return this->values[r][i];
}


DLA_SpareMatrix::DLA_SpareMatrix(const simpleMatrix &mat)
{
    helpInit(mat);
}

DLA_SpareMatrix &DLA_SpareMatrix::operator=(const simpleMatrix &mat)
{
    this->values.clear();
    helpInit(mat);
}

void DLA_SpareMatrix::helpInit(const simpleMatrix &mat)
{
    this->rows = mat.size();
    this->cols = mat[0].size();
    size_t dia_num = this->rows >= this->cols ?
                            this->rows * 2 - 1 : this->cols * 2 - 1;
    size_t c_ = 0;
    vector<vector<double>> diagonal;


    for (size_t i = 0; i < dia_num; ++i)
    {
        size_t r, r_ = i < this->rows ? this->rows - i -1 : 0;
        size_t c, c__ = i < this->rows ? 0 : c_++;
        size_t no_zero_count = 0;
        r = r_;
        c = c__;
        diagonal.emplace_back();
        while(r < this->rows and c < this->cols)
        {
            if (mat[r][c] > 1e-6)
            {
                ++no_zero_count;
            }
            ++r, ++c;
        }
        if(no_zero_count not_eq 0)
        {
            //TODO here implement the DIA
        }
    }

}


rowElement DLA_SpareMatrix::getRow(size_t r)
{
}

double DLA_SpareMatrix::getEle(size_t r, size_t c)
{


}
