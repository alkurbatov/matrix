#pragma once

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "Errors.h"

// NB (alkurbatov): A proxy class which only purpose is to provide additional operator[].
// Shouldn't be used as a standalone entity.
template <typename T>
struct Row
{
    Row() = delete;

    Row(unsigned row_num_, unsigned cols_, std::vector<T>& data_):
        m_row_num(row_num_), m_cols(cols_), m_data(data_)
    {}

    T& operator[](unsigned col_)
    {
        return m_data[(m_row_num * m_cols) + col_];
    }

    const T& operator[](unsigned col_) const
    {
        return operator[](col_);
    }

private:
    unsigned m_row_num;
    unsigned m_cols;

    std::vector<T>& m_data;
};

template <typename T>
struct Matrix
{
    Matrix() = delete;

    Matrix(unsigned rows_, unsigned cols_):
        m_rows(rows_), m_cols(cols_), m_data(rows_ * cols_, 0)
    {}

    Matrix(const Matrix<T>& src_): m_rows(src_.m_rows), m_cols(src_.m_cols), m_data(src_.m_data)
    {}

    Matrix(Matrix<T>&& src_):
        m_rows(std::exchange(src_.m_rows, 0)), m_cols(std::exchange(src_.m_cols, 0)),
        m_data(std::move(src_.m_data))
    {}

    unsigned rows() const
    {
        return m_rows;
    }

    unsigned cols() const
    {
        return m_cols;
    }

    std::string to_string() const
    {
        std::string rv;

        if (m_data.empty())
            return rv;

        for (unsigned i = 0; i < m_rows; ++i)
        {
            rv += "|";

            for (unsigned j = 0; j < m_cols; ++j)
            {
                rv += std::to_string(m_data[(i * m_cols) + j]);

                if (j != m_cols - 1)
                    rv += " ";
            }

            rv += "|\n";
        }

        return rv;
    }

    Row<T> operator[](unsigned row_)
    {
        return Row<T>(row_, m_cols, m_data);
    }

    Row<T> operator[](unsigned row_) const
    {
        return operator[](row_);
    }

    auto begin() const
    {
        return m_data.begin();
    }

    auto end() const
    {
        return m_data.end();
    }

    Matrix<T> operator+(const Matrix<T>& src_) const
    {
        if (m_cols != src_.m_cols || m_rows != src_.m_rows)
            throw DimensionsDontMatch();

        Matrix<T> rv(*this);

        std::transform(rv.m_data.begin(), rv.m_data.end(), src_.m_data.begin(),
                       rv.m_data.begin(), std::plus<T>());

        return rv;
    }

    // NB (alkurbatov): Provides vertical concatenation.
    Matrix<T> operator|(const Matrix<T>& src_) const
    {
        if (m_cols != src_.m_cols)
            throw DimensionsDontMatch();

        Matrix<T> rv(*this);

        rv.m_rows += src_.m_rows;
        std::copy(src_.m_data.begin(), src_.m_data.end(), std::back_inserter(rv.m_data));

        return rv;
    }

private:
    unsigned m_rows;
    unsigned m_cols;

    std::vector<T> m_data;
};
