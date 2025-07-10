#ifndef INCLUDE_MAZE_H
#define INCLUDE_MAZE_H

#include "block_map.h"
#include <vector>

enum class Movement
{
    Up,
    Down,
    Left,
    Right
};

class Maze
{
private:
    size_t rows, cols;
    BlockMap block_map, origin;
    std::vector<Vec2> current_pos_set;
    std::vector<Vec2> changed_pos_set;

public:
    Maze(size_t r, size_t c) : rows(r), cols(c), block_map(r, c), current_pos_set(), changed_pos_set()
    {
        block_map.init_map();
        origin = block_map;
        current_pos_set.emplace_back(block_map.get_start());
    }
    ~Maze() = default;

public:
    Vec2 get_current_pos(size_t = 0);
    const Vec2 get_current_pos(size_t = 0) const;
    void set_current_pos(const Vec2 &, size_t = 0);

    size_t current_pos_size();
    const size_t current_pos_size() const;

    std::vector<Vec2> clean_changed_pos_set();

public:
    void copy_current_pos(size_t);
    void remove_current_pos(size_t);

    BlockType look(const Movement &, size_t = 0) const;
    BlockType stand(size_t = 0) const;
    bool move(const Movement &, size_t = 0);
    void reset();

public:
    std::vector<Block> block_data();
    const std::vector<Block> block_data() const;

    size_t row_count();
    const size_t row_count() const;

    size_t col_count();
    const size_t col_count() const;

    Vec2 start_pos();
    const Vec2 start_pos() const;

    Vec2 end_pos();
    const Vec2 end_pos() const;

public:
    BlockType look_pos(const Vec2 &) const;
    bool move_pos(const Vec2 &, size_t = 0);
};

#endif