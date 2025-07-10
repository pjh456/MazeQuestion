#ifndef INCLUDE_VEC2_H
#define INCLUDE_VEC2_H

class Vec2
{
private:
    int row;
    int col;

public:
    Vec2() : col(0), row(0) {}
    Vec2(int r, int c) : row(r), col(c) {}
    Vec2(const Vec2 &other) : row(other.row), col(other.col) {}
    Vec2(Vec2 &&other) noexcept : row(other.row), col(other.col) { other.row = other.col = 0; }
    ~Vec2() = default;

public:
    Vec2 operator+(const Vec2 &) const;
    Vec2 operator-(const Vec2 &) const;
    Vec2 operator/(const int &) const;
    Vec2 &operator=(const Vec2 &) = default;

public:
    void operator+=(const Vec2 &);
    void operator-=(const Vec2 &);
    bool operator==(const Vec2 &) const;
    bool operator!=(const Vec2 &) const;

public:
    int get_row();
    const int get_row() const;

    int get_col();
    const int get_col() const;

public:
    Vec2 normalize() const noexcept;
    float distance(const Vec2 &) const noexcept;
    int manhaton_distance(const Vec2 &) const noexcept;
    void clear() noexcept;
};

#endif