#pragma once

#include <luamdl3d_lib/luadraw/LDState.h>

#include <sol/sol.hpp>

namespace luamdl3d::LDState
{
    /// === LDState START ===

    using object_t = void(*)(const std::string&);
    void object(const std::string& name);

    using group_t = void(*)(const std::string&);
    void group(const std::string& name);

    using save_t = void(*)(const std::string&);
    void save(const std::string& outputPath);

    /// === LDState END ===

    void BindGeneral(sol::state& luaState);
}
