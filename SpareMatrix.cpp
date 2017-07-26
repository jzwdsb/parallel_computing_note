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
            if (mat[r][c] not_eq 0)
            {
                this->col.push_back(c);
                this->values.push_back(mat[r][c]);
                ++rowOffset;
            }
        }
    }
}

rowElement CSR_SpareMatrix::getRow(size_t r)
{
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
    size_t row_length = this->row_offset[r + 1] - this->row_offset[r];
    size_t offset = this->row_offset[r];
    if(row_length == 0)
        return 0;
    while(offset < this->row_offset[r + 1] and this->col[offset++] not_eq c)  ;
    if (offset == this->row_offset[r + 1])
        return 0;
    return this->values[offset];:
}


ELL_SpareMatrix::ELL_SpareMatrix(const simpleMatrix &mat)
{
    size_t rows = mat.size();
    size_t cols = mat[0].size();
    for(size_t r = 0; r < rows; ++r)
    {
        for (size_t c = 0; c < cols; ++c)
        {
            if(mat[r][c] > 1e-6)
            {

            }
        }
    }
}



