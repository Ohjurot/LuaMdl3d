#pragma once

#include <luamdl3d_lib/luadraw/LDState.h>

namespace luamdl3d::LDState
{
    /// === START ===

    using cursor_push_t = void(*)();
    void cursor_push();

    using cursor_pop_t = void(*)();
    void cursor_pop();

    using cursor_set_t = void(*)(float x, float y, float z);
    void cursor_set(float x, float y, float z);

    using cursor_mov_t = void(*)(float x, float y, float z);
    void cursor_mov(float x, float y, float z);

    /// === END ===

    void BindCursor(sol::state& luaState);
}
