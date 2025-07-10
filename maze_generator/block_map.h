#ifndef INCLUDE_BLOCKMAP_H
#define INCLUDE_BLOCKMAP_H

#include "matrix2d.h"
#include "block.h"

class BlockMap
{
private:
    size_t rows, cols;
    Matrix2D<Block> blocks;
    Vec2 srt, fin;

public:
    BlockMap(size_t r, size_t c) : rows(r), cols(c), blocks(2 * r + 1, 2 * c + 1) {}
    BlockMap() : BlockMap(1, 1) {}
    BlockMap(const BlockMap &other) : rows(other.rows), cols(other.cols), blocks(other.blocks) {}
    ~BlockMap() = default;

public:
    void init_map();

    Block &get_block(const Vec2 &);
    const Block &get_block(const Vec2 &) const;

    void set(const Vec2 &, const Block &);

public:
    size_t row_count();
    const size_t row_count() const;

    size_t col_count();
    const size_t col_count() const;

public:
    Vec2 get_start();
    const Vec2 get_start() const;

    Vec2 get_end();
    const Vec2 get_end() const;

    std::vector<Block> &block_data();
    const std::vector<Block> &block_data() const;
};

#endif