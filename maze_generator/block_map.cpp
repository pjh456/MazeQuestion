#include "block_map.h"

#include <random>
#include <functional>
#include <algorithm>
#include <ctime>

void BlockMap::init_map()
{
    // 1. Initialize variants and define functions.

    // 1.1 Define functions to transform Vec2 and index.
    auto pos2idx = [&](Vec2 pos)
    { return pos.get_row() * (this->cols) + pos.get_col(); };
    auto idx2pos = [&](int idx)
    { return Vec2(idx / (this->cols), idx % (this->cols)); };

    // 1.2 Initialize father_node array to build Union-Find method.
    std::vector<Vec2> father_node(cols * rows);
    for (size_t idx = 0; idx < father_node.size(); ++idx)
        father_node[idx] = idx2pos(idx);

    // 1.3 Define a function to easily get the father_node and compress the whole path.
    std::function<Vec2(Vec2)> get_father_node =
        [&](Vec2 pos) -> Vec2
    {
        Vec2 &father = father_node[pos2idx(pos)];
        if (father == pos)
            return pos;
        else
            return father = get_father_node(father);
    };

    // 1.4 Initialize the real wall map, size(2 * rows + 1, 2 * columns + 1)
    for (size_t r = 0; r < 2 * rows + 1; ++r)
    {
        for (size_t c = 0; c < 2 * cols + 1; ++c)
        {
            if (r == 0 || r == 2 * rows || c == 0 || c == 2 * cols) // Boundary
            {
                blocks(r, c) = Block(Vec2(r, c), BlockType::Wall);
            }
            else if ((r & 1) == 0 || (c & 1) == 0) // Edge, default to be unavailable.
            {
                blocks(r, c) = Block(Vec2(r, c), BlockType::Wall);
            }
            else // Node
            {
                blocks(r, c) = Block(Vec2(r, c), BlockType::Air);
            }
        }
    }

    // 1.5 Initialize all the available edge.
    std::vector<std::pair<Vec2, Vec2>> edges;
    for (size_t r = 0; r < rows; ++r)
    {
        for (size_t c = 0; c < cols; ++c)
        {
            Vec2 cur(r, c);
            if (r + 1 < rows)
                edges.emplace_back(cur, Vec2(r + 1, c)); // down side
            if (c + 1 < cols)
                edges.emplace_back(cur, Vec2(r, c + 1)); // right side
        }
    }
    // 2. Randomly generate the whole map.

    // 2.1 Disrupt the order of edges.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(edges.begin(), edges.end(), gen);

    // 2.2 Use Kruskal method to randomly connect positions.
    for (auto &edge : edges)
    {
        // 2.2.1 Get a edge to check if they are both in the same set.
        Vec2 x = edge.first, y = edge.second;
        Vec2 fax = get_father_node(x), fay = get_father_node(y);

        if (fax != fay)
        {
            // 2.2.2 Merge them if they are not in the same set.
            father_node[pos2idx(fax)] = fay;

            // 2.2.3 Make the edge availble in the map.
            Vec2 x_pos(2 * x.get_row() + 1, 2 * x.get_col() + 1);
            Vec2 y_pos(2 * y.get_row() + 1, 2 * y.get_col() + 1);
            Vec2 edge_pos = (x_pos + y_pos) / 2;
            blocks(edge_pos.get_row(), edge_pos.get_col()).set_type(BlockType::Air);
        }
    }
    // 3. Select start and end position.
    // Note: start from column 1, and end at column ${2 * cols - 1}
    srt = Vec2((gen() % rows) * 2 + 1, 1);
    fin = Vec2((gen() % rows) * 2 + 1, 2 * cols - 1);
    blocks(srt.get_row(), srt.get_col()).set_type(BlockType::Start);
    blocks(fin.get_row(), fin.get_col()).set_type(BlockType::End);
}

Block &BlockMap::get_block(const Vec2 &p)
{
    return blocks(p.get_row(), p.get_col());
}

const Block &BlockMap::get_block(const Vec2 &p) const
{
    return blocks(p.get_row(), p.get_col());
}

void BlockMap::set(const Vec2 &p, const Block &b)
{
    blocks(p.get_row(), p.get_col()) = b;
}

size_t BlockMap::row_count() { return blocks.row_count(); }
const size_t BlockMap::row_count() const { return blocks.row_count(); }

size_t BlockMap::col_count() { return blocks.col_count(); }
const size_t BlockMap::col_count() const { return blocks.col_count(); }

Vec2 BlockMap::get_start() { return srt; }
const Vec2 BlockMap::get_start() const { return srt; }

Vec2 BlockMap::get_end() { return fin; }
const Vec2 BlockMap::get_end() const { return fin; }

std::vector<Block> &BlockMap::block_data() { return blocks.vector_data(); }
const std::vector<Block> &BlockMap::block_data() const { return blocks.vector_data(); }