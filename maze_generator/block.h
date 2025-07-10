#ifndef INCLUDE_BLOCK_H
#define INCLUDE_BLOCK_H

#include "vec2.h"

enum class BlockType
{
    Wall,
    Air,
    Start,
    End,
    Body
};

class Block
{
private:
    Vec2 pos;
    BlockType type;

public:
    Block() : pos(0, 0), type(BlockType::Air) {}
    Block(const Vec2 &p, const BlockType &t) : pos(p), type(t) {}
    Block(const Block &other) : pos(other.pos), type(other.type) {}
    Block(Block &&other) noexcept : pos(other.pos), type(other.type) {}
    ~Block() = default;

public:
    Block &operator=(const Block &) = default;

public:
    Vec2 get_pos();
    const Vec2 get_pos() const;

    void set_pos(const Vec2 &);

    BlockType get_type();
    const BlockType get_type() const;

    void set_type(const BlockType &);
};

#endif