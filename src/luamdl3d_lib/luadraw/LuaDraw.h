#pragma once

#include <sol/sol.hpp>

#include <luamdl3d_lib/luadraw/LDState.h>

#include <luamdl3d_lib/luadraw/ld/LDDemo.h>
#include <luamdl3d_lib/luadraw/ld/LDCursor.h>
#include <luamdl3d_lib/luadraw/ld/LDGeneral.h>

namespace luamdl3d::LDState
{
    /*!
     * @brief Bind all implementations
     * @param luaState Lua state to bind on
    */
    void Bind(sol::state& luaState);
}
