#include "maze.h"

Vec2 Maze::get_current_pos(size_t idx) { return current_pos_set[idx]; }

const Vec2 Maze::get_current_pos(size_t idx) const { return current_pos_set[idx]; }

void Maze::set_current_pos(const Vec2 &pos, size_t idx) { current_pos_set[idx] = pos; }

void Maze::copy_current_pos(size_t idx)
{
    current_pos_set.emplace_back(current_pos_set[idx]);
}

void Maze::remove_current_pos(size_t idx)
{
    // current_pos_set.erase(current_pos_set.begin() + idx);
}

size_t Maze::current_pos_size() { return current_pos_set.size(); }
const size_t Maze::current_pos_size() const { return current_pos_set.size(); }

std::vector<Vec2> Maze::clean_changed_pos_set()
{
    auto ret_set = changed_pos_set;
    changed_pos_set.clear();
    return ret_set;
}

BlockType Maze::look(const Movement &m, size_t idx) const
{
    Vec2 pos = get_current_pos(idx);
    switch (m)
    {
    case Movement::Up:
        pos += Vec2(-1, 0);
        break;
    case Movement::Down:
        pos += Vec2(1, 0);
        break;
    case Movement::Left:
        pos += Vec2(0, -1);
        break;
    case Movement::Right:
        pos += Vec2(0, 1);
        break;
    }
    return look_pos(pos);
}

BlockType Maze::stand(size_t idx) const { return look_pos(get_current_pos(idx)); }

bool Maze::move(const Movement &m, size_t idx)
{
    Vec2 pos = get_current_pos(idx);
    switch (m)
    {
    case Movement::Up:
        pos += Vec2(-2, 0);
        break;
    case Movement::Down:
        pos += Vec2(2, 0);
        break;
    case Movement::Left:
        pos += Vec2(0, -2);
        break;
    case Movement::Right:
        pos += Vec2(0, 2);
        break;
    }
    return move_pos(pos, idx);
}

void Maze::reset()
{
    block_map = origin;
    current_pos_set.clear();
    current_pos_set.emplace_back(start_pos());
}

std::vector<Block> Maze::block_data() { return block_map.block_data(); }
const std::vector<Block> Maze::block_data() const { return block_map.block_data(); }

size_t Maze::row_count() { return rows; }
const size_t Maze::row_count() const { return rows; }

size_t Maze::col_count() { return cols; }
const size_t Maze::col_count() const { return cols; }

Vec2 Maze::start_pos() { return block_map.get_start(); }
const Vec2 Maze::start_pos() const { return block_map.get_start(); }

Vec2 Maze::end_pos() { return block_map.get_end(); }
const Vec2 Maze::end_pos() const { return block_map.get_end(); }

BlockType Maze::look_pos(const Vec2 &p) const { return block_map.get_block(p).get_type(); }

bool Maze::move_pos(const Vec2 &p, size_t idx)
{
    int col = p.get_col(), row = p.get_row();

    // Even the boundary is also unacceptable!
    if (col <= 0 || col >= block_map.col_count() - 1 || row <= 0 || row >= block_map.row_count() - 1)
        return false;

    Vec2 edge_block_pos = (p + get_current_pos(idx)) / 2;
    BlockType edge_block_type = look_pos(edge_block_pos);
    switch (edge_block_type)
    {
    case BlockType::Air:
    case BlockType::Body:
        if (edge_block_type == BlockType::Air)
        {
            changed_pos_set.push_back(edge_block_pos);
            block_map.get_block(edge_block_pos).set_type(BlockType::Body);
        }

        if (block_map.get_block(p).get_type() == BlockType::Air)
        {
            changed_pos_set.push_back(p);
            block_map.get_block(p).set_type(BlockType::Body);
        }

        set_current_pos(p, idx);
        return true;
    default:
        return false;
    }
}
