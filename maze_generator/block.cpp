#include "block.h"

Vec2 Block::get_pos() { return pos; }

const Vec2 Block::get_pos() const { return pos; }

void Block::set_pos(const Vec2 &p) { pos = p; }

BlockType Block::get_type() { return type; }

const BlockType Block::get_type() const { return type; }

void Block::set_type(const BlockType &t) { type = t; }