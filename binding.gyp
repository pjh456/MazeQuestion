{
  "targets": [
    {
      "target_name": "maze",
      "sources": [
        "maze_generator/block.cpp",
        "maze_generator/block_map.cpp",
        "maze_generator/main.cpp",
        "maze_generator/matrix2d.cpp",
        "maze_generator/maze.cpp",
        "maze_generator/maze_adapter.cpp",
        "maze_generator/vec2.cpp"
      ],
      "include_dirs": [
        "<!(node -p \"require('node-addon-api').include\")",
        "<!(node -p \"require('node-addon-api').include_dir\")",
        "node_modules/node-addon-api"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "cflags_cc": [
        "-std=c++17"
      ],
      "defines": [
        "NAPI_CPP_EXCEPTIONS"
      ]
    }
  ]
}