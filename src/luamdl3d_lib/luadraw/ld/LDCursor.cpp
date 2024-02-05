#include "LDCursor.h"

void luamdl3d::LDState::cursor_push()
{
    GetData().Cursors.push(GetData().Cursors.top());
}

void luamdl3d::LDState::cursor_pop()
{
    if (GetData().Cursors.size() == 1)
    {
        spdlog::warn("Can't \"cursor_pop\" which would pop the only left over cursor");
    }
    else
    {
        GetData().Cursors.pop();
    }
}

void luamdl3d::LDState::cursor_set(float x, float y, float z)
{
    auto& cursor = GetData().Cursors.top();
    cursor.PositionX = x;
    cursor.PositionY = y;
    cursor.PositionZ = z;
}

void luamdl3d::LDState::cursor_mov(float x, float y, float z)
{
    auto& cursor = GetData().Cursors.top();
    cursor.PositionX += x;
    cursor.PositionY += y;
    cursor.PositionZ += z;
}

void luamdl3d::LDState::BindCursor(sol::state& luaState)
{
    luaState.set_function("cursor_push", (cursor_push_t)&cursor_push);
    luaState.set_function("cursor_pop", (cursor_pop_t)&cursor_pop);
    luaState.set_function("cursor_set", (cursor_set_t)&cursor_set);
    luaState.set_function("cursor_mov", (cursor_mov_t)&cursor_mov);
}
