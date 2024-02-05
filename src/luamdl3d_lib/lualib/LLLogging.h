#pragma once

#include <spdlog/spdlog.h>
#include <sol/sol.hpp>

namespace luamdl3d
{
    /*!
     * @brief Will bind the "info", "warn" and "error" logging functions
     * @param luaState State to register on
    */
    void LLBindLogging(sol::state& luaState);
}
