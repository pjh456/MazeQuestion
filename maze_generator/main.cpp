// #include "maze.h"
// #include <iostream>

// int main()
// {
//     int rows = 5, cols = 8;
//     Maze maze(rows, cols);
//     std::vector<Block> block_data = maze.block_data();
//     std::cout << block_data.size() << std::endl;
//     size_t idx = 0;
//     for (size_t r = 0; r < 2 * rows + 1; ++r)
//     {
//         for (size_t c = 0; c < 2 * cols + 1; ++c)
//         {
//             std::cout << static_cast<int>(block_data[r * (2 * cols + 1) + c].get_type()) << " ";
//         }
//         std::cout << std::endl;
//     }
// }