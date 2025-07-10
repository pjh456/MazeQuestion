#include "vec2.h"

#include <cmath>

Vec2 Vec2::operator+(const Vec2 &other) const
{
    return Vec2(row + other.row, col + other.col);
}

Vec2 Vec2::operator-(const Vec2 &other) const
{
    return Vec2(row - other.row, col - other.col);
}

Vec2 Vec2::operator/(const int &val) const
{
    return Vec2(row / val, col / val);
}

void Vec2::operator+=(const Vec2 &other)
{
    row += other.row;
    col += other.col;
}

void Vec2::operator-=(const Vec2 &other)
{
    row -= other.row;
    col -= other.col;
}

bool Vec2::operator==(const Vec2 &other) const
{
    return (row == other.row) && (col == other.col);
}

bool Vec2::operator!=(const Vec2 &other) const
{
    return (row != other.row) || (col != other.col);
}

int Vec2::get_row() { return row; }
const int Vec2::get_row() const { return row; }

int Vec2::get_col() { return col; }
const int Vec2::get_col() const { return col; }

Vec2 Vec2::normalize() const noexcept
{
    int length = std::sqrt((row * row) + (col * col));
    return Vec2(row / length, col / length);
}

float Vec2::distance(const Vec2 &other) const noexcept
{
    int delta_row = row - other.row;
    int delta_col = col - other.col;
    float dis = std::sqrt(delta_row * delta_row + delta_col * delta_col);
    return dis;
}

int Vec2::manhaton_distance(const Vec2 &other) const noexcept
{
    int delta_row = row - other.row;
    int delta_col = col - other.col;
    return std::abs(delta_row) + std::abs(delta_col);
}

void Vec2::clear() noexcept { row = col = 0; }
