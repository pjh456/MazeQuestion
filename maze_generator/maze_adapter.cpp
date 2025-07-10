#ifndef INCLUDE_MAZE_ADAPTER_CPP
#define INCLUDE_MAZE_ADAPTER_CPP

#include "maze.h"

#include <string>
#include <napi.h>

class MazeAdapter : public Napi::ObjectWrap<MazeAdapter>
{
private:
    Maze maze;

public:
    static Napi::Object Init(Napi::Env, Napi::Object);
    MazeAdapter(const Napi::CallbackInfo &info)
        : Napi::ObjectWrap<MazeAdapter>(info),
          maze(parse_size(info, 0), parse_size(info, 1))
    {
        if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
        {
            Napi::TypeError::New(info.Env(), "Expected two numbers").ThrowAsJavaScriptException();
            return;
        }
    }

public:
    Napi::Value look_up(const Napi::CallbackInfo &);
    Napi::Value look_down(const Napi::CallbackInfo &);
    Napi::Value look_left(const Napi::CallbackInfo &);
    Napi::Value look_right(const Napi::CallbackInfo &);
    Napi::Value stand(const Napi::CallbackInfo &);

public:
    Napi::Value move_up(const Napi::CallbackInfo &);
    Napi::Value move_down(const Napi::CallbackInfo &);
    Napi::Value move_left(const Napi::CallbackInfo &);
    Napi::Value move_right(const Napi::CallbackInfo &);

public:
    Napi::Value get_start_pos(const Napi::CallbackInfo &);
    Napi::Value get_end_pos(const Napi::CallbackInfo &);
    Napi::Value get_current_pos(const Napi::CallbackInfo &);
    Napi::Value get_changed_pos(const Napi::CallbackInfo &);

public:
    Napi::Value copy_current_pos(const Napi::CallbackInfo &);
    Napi::Value remove_current_pos(const Napi::CallbackInfo &);

public:
    Napi::Value row_count(const Napi::CallbackInfo &);
    Napi::Value col_count(const Napi::CallbackInfo &);
    Napi::Value pos_size(const Napi::CallbackInfo &);

public:
    Napi::Value block_data(const Napi::CallbackInfo &);
    Napi::Value reset(const Napi::CallbackInfo &);

private:
    Napi::Value blocktype2str(const Napi::Env &, BlockType) const;
    static size_t parse_size(const Napi::CallbackInfo &, size_t);
};

Napi::Object MazeAdapter::Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = DefineClass(
        env,
        "MazeAdapter",
        {InstanceMethod("look_up", &MazeAdapter::look_up),
         InstanceMethod("look_down", &MazeAdapter::look_down),
         InstanceMethod("look_left", &MazeAdapter::look_left),
         InstanceMethod("look_right", &MazeAdapter::look_right),
         InstanceMethod("stand", &MazeAdapter::stand),

         InstanceMethod("move_up", &MazeAdapter::move_up),
         InstanceMethod("move_down", &MazeAdapter::move_down),
         InstanceMethod("move_left", &MazeAdapter::move_left),
         InstanceMethod("move_right", &MazeAdapter::move_right),

         InstanceMethod("start_pos", &MazeAdapter::get_start_pos),
         InstanceMethod("end_pos", &MazeAdapter::get_end_pos),
         InstanceMethod("current_pos", &MazeAdapter::get_current_pos),
         InstanceMethod("changed_pos", &MazeAdapter::get_changed_pos),

         InstanceMethod("copy_pos", &MazeAdapter::copy_current_pos),
         InstanceMethod("remove_pos", &MazeAdapter::remove_current_pos),

         InstanceMethod("row_count", &MazeAdapter::row_count),
         InstanceMethod("col_count", &MazeAdapter::col_count),
         InstanceMethod("pos_size", &MazeAdapter::pos_size),

         InstanceMethod("block_data", &MazeAdapter::block_data),
         InstanceMethod("reset", &MazeAdapter::reset)});
    exports.Set("MazeAdapter", func);
    return exports;
}

Napi::Value MazeAdapter::look_up(const Napi::CallbackInfo &info)
{
    if (info.Length() == 0)
    {
        return blocktype2str(info.Env(), maze.look(Movement::Up));
    }
    else
    {
        size_t idx = info[0].As<Napi::Number>().Uint32Value();
        return blocktype2str(info.Env(), maze.look(Movement::Up, idx));
    }
}

Napi::Value MazeAdapter::look_down(const Napi::CallbackInfo &info)
{
    if (info.Length() == 0)
    {
        return blocktype2str(info.Env(), maze.look(Movement::Down));
    }
    else
    {
        size_t idx = info[0].As<Napi::Number>().Uint32Value();
        return blocktype2str(info.Env(), maze.look(Movement::Down, idx));
    }
}

Napi::Value MazeAdapter::look_left(const Napi::CallbackInfo &info)
{
    if (info.Length() == 0)
    {
        return blocktype2str(info.Env(), maze.look(Movement::Left));
    }
    else
    {
        size_t idx = info[0].As<Napi::Number>().Uint32Value();
        return blocktype2str(info.Env(), maze.look(Movement::Left, idx));
    }
}

Napi::Value MazeAdapter::look_right(const Napi::CallbackInfo &info)
{
    if (info.Length() == 0)
    {
        return blocktype2str(info.Env(), maze.look(Movement::Right));
    }
    else
    {
        size_t idx = info[0].As<Napi::Number>().Uint32Value();
        return blocktype2str(info.Env(), maze.look(Movement::Right, idx));
    }
}

Napi::Value MazeAdapter::stand(const Napi::CallbackInfo &info)
{
    if (info.Length() == 0)
    {
        return blocktype2str(info.Env(), maze.stand());
    }
    else
    {
        size_t idx = info[0].As<Napi::Number>().Uint32Value();
        return blocktype2str(info.Env(), maze.stand(idx));
    }
}

Napi::Value MazeAdapter::move_up(const Napi::CallbackInfo &info)
{
    if (info.Length() == 0)
    {
        return Napi::Boolean::New(info.Env(), maze.move(Movement::Up));
    }
    else
    {
        size_t idx = info[0].As<Napi::Number>().Uint32Value();
        return Napi::Boolean::New(info.Env(), maze.move(Movement::Up, idx));
    }
}

Napi::Value MazeAdapter::move_down(const Napi::CallbackInfo &info)
{
    if (info.Length() == 0)
    {
        return Napi::Boolean::New(info.Env(), maze.move(Movement::Down));
    }
    else
    {
        size_t idx = info[0].As<Napi::Number>().Uint32Value();
        return Napi::Boolean::New(info.Env(), maze.move(Movement::Down, idx));
    }
}

Napi::Value MazeAdapter::move_left(const Napi::CallbackInfo &info)
{
    if (info.Length() == 0)
    {
        return Napi::Boolean::New(info.Env(), maze.move(Movement::Left));
    }
    else
    {
        size_t idx = info[0].As<Napi::Number>().Uint32Value();
        return Napi::Boolean::New(info.Env(), maze.move(Movement::Left, idx));
    }
}

Napi::Value MazeAdapter::move_right(const Napi::CallbackInfo &info)
{
    if (info.Length() == 0)
    {
        return Napi::Boolean::New(info.Env(), maze.move(Movement::Right));
    }
    else
    {
        size_t idx = info[0].As<Napi::Number>().Uint32Value();
        return Napi::Boolean::New(info.Env(), maze.move(Movement::Right, idx));
    }
}

Napi::Value MazeAdapter::get_start_pos(const Napi::CallbackInfo &info)
{
    Napi::Array arr = Napi::Array::New(info.Env(), 2);

    Vec2 start_pos = maze.start_pos();
    size_t row_idx = 0, col_idx = 1;

    arr.Set(row_idx, start_pos.get_row());
    arr.Set(col_idx, start_pos.get_col());

    return arr;
}

Napi::Value MazeAdapter::get_end_pos(const Napi::CallbackInfo &info)
{
    Napi::Array arr = Napi::Array::New(info.Env(), 2);

    Vec2 end_pos = maze.end_pos();
    size_t row_idx = 0, col_idx = 1;

    arr.Set(row_idx, end_pos.get_row());
    arr.Set(col_idx, end_pos.get_col());

    return arr;
}

Napi::Value MazeAdapter::get_current_pos(const Napi::CallbackInfo &info)
{
    Napi::Array arr = Napi::Array::New(info.Env(), 2);

    size_t pos_idx = 0;
    if (info.Length() != 0 && info[0].IsNumber())
        pos_idx = info[0].As<Napi::Number>().Uint32Value();

    Vec2 current_pos = maze.get_current_pos(pos_idx);
    size_t row_idx = 0, col_idx = 1;

    arr.Set(row_idx, current_pos.get_row());
    arr.Set(col_idx, current_pos.get_col());

    return arr;
}

Napi::Value MazeAdapter::get_changed_pos(const Napi::CallbackInfo &info)
{
    std::vector<Vec2> changed_pos = maze.clean_changed_pos_set();
    Napi::Array arr = Napi::Array::New(info.Env(), changed_pos.size());

    for (size_t idx = 0; idx < changed_pos.size(); ++idx)
    {
        Napi::Array vec2_arr = Napi::Array::New(info.Env(), 3);
        size_t row_idx = 0, col_idx = 1, type_idx = 2;

        vec2_arr.Set(row_idx, changed_pos[idx].get_row());
        vec2_arr.Set(col_idx, changed_pos[idx].get_col());
        vec2_arr.Set(type_idx, blocktype2str(info.Env(), maze.look_pos(changed_pos[idx])));
        arr.Set(idx, vec2_arr);
    }

    return arr;
}

Napi::Value MazeAdapter::copy_current_pos(const Napi::CallbackInfo &info)
{
    size_t pos_idx = 0;
    if (info.Length() != 0 && info[0].IsNumber())
        pos_idx = info[0].As<Napi::Number>().Uint32Value();

    if (pos_idx >= maze.current_pos_size())
        return Napi::Boolean::New(info.Env(), false);
    else
        return maze.copy_current_pos(pos_idx), Napi::Boolean::New(info.Env(), true);
}

Napi::Value MazeAdapter::remove_current_pos(const Napi::CallbackInfo &info)
{
    size_t pos_idx = 0;
    if (info.Length() != 0 && info[0].IsNumber())
        pos_idx = info[0].As<Napi::Number>().Uint32Value();

    if (pos_idx >= maze.current_pos_size())
        return Napi::Boolean::New(info.Env(), false);
    else
        return maze.remove_current_pos(pos_idx), Napi::Boolean::New(info.Env(), true);
}

Napi::Value MazeAdapter::row_count(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), maze.row_count());
}

Napi::Value MazeAdapter::col_count(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), maze.col_count());
}

Napi::Value MazeAdapter::pos_size(const Napi::CallbackInfo &info)
{
    return Napi::Number::New(info.Env(), maze.current_pos_size());
}

Napi::Value MazeAdapter::block_data(const Napi::CallbackInfo &info)
{
    std::vector<Block> raw_data = maze.block_data();
    size_t map_cols = 2 * maze.col_count() + 1;
    size_t map_rows = 2 * maze.row_count() + 1;
    auto env = info.Env();

    Napi::Array outer = Napi::Array::New(env, map_rows);
    for (size_t r = 0; r < map_rows; ++r)
    {
        Napi::Array inner = Napi::Array::New(env, map_cols);
        for (size_t c = 0; c < map_cols; ++c)
        {
            size_t index = r * map_cols + c;
            inner.Set(c, blocktype2str(env, raw_data[index].get_type()));
        }
        outer.Set(r, inner);
    }

    return outer;
}

Napi::Value MazeAdapter::reset(const Napi::CallbackInfo &info)
{
    maze.reset();
    return info.Env().Null();
}

Napi::Value MazeAdapter::blocktype2str(const Napi::Env &env, BlockType t) const
{
    std::string str;
    switch (t)
    {
    case BlockType::Air:
        str = "air";
        break;
    case BlockType::Body:
        str = "body";
        break;
    case BlockType::Start:
        str = "start";
        break;
    case BlockType::End:
        str = "end";
        break;
    case BlockType::Wall:
        str = "wall";
        break;
    }
    return Napi::String::New(env, str);
}

size_t MazeAdapter::parse_size(const Napi::CallbackInfo &info, size_t idx)
{
    return info[idx].As<Napi::Number>().Uint32Value();
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
    return MazeAdapter::Init(env, exports);
}

NODE_API_MODULE(maze, InitAll);

#endif