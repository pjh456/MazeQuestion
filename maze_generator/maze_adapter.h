// #ifndef INCLUDE_MAZE_ADAPTER
// #define INCLUDE_MAZE_ADAPTER

// #include "maze.h"

// #include <napi.h>

// class MazeAdapter : public Napi::ObjectWrap<MazeAdapter>
// {
// private:
//     Maze maze;

// public:
//     static Napi::Object Init(Napi::Env, Napi::Object);
//     MazeAdapter(const Napi::CallbackInfo &);

// public:
//     Napi::Value look_up(const Napi::CallbackInfo &);
//     Napi::Value look_down(const Napi::CallbackInfo &);
//     Napi::Value look_left(const Napi::CallbackInfo &);
//     Napi::Value look_right(const Napi::CallbackInfo &);

// public:
//     Napi::Value move_up(const Napi::CallbackInfo &);
//     Napi::Value move_down(const Napi::CallbackInfo &);
//     Napi::Value move_left(const Napi::CallbackInfo &);
//     Napi::Value move_right(const Napi::CallbackInfo &);

// private:
//     Napi::Value blocktype2str(const Napi::CallbackInfo &, BlockType) const;
// };

// #endif