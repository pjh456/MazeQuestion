#ifndef INCLUDE_MATRIX2D_H
#define INCLUDE_MATRIX2D_H

#include <vector>

template <typename T>
class Matrix2D
{
private:
    size_t rows, cols;
    std::vector<T> data;

public:
    Matrix2D(size_t r, size_t c, const T &default_data = T())
        : rows(r), cols(c), data(r * c, default_data) {}
    Matrix2D(const Matrix2D<T> &other) : rows(other.rows), cols(other.cols), data(other.data) {}
    ~Matrix2D() = default;

public:
    T &operator()(size_t r, size_t c) { return data[r * cols + c]; }

    const T &operator()(size_t r, size_t c) const { return data[r * cols + c]; }

public:
    size_t row_count() { return rows; }
    const size_t row_count() const { return rows; }

    size_t col_count() { return cols; }
    const size_t col_count() const { return cols; }

public:
    void fill(const T &val) { std::fill(data.begin(), data.end(), val); }

public:
    T *raw_data() { return data.data(); }
    const T *raw_data() const { return data.data(); }

    std::vector<T> &vector_data() { return data; }
    const std::vector<T> &vector_data() const { return data; }
};

#endif