#include <luamdl3d_lib/lualib/LLLogging.h>
#include <luamdl3d_lib/luadraw/LuaDraw.h>

#include <sol/sol.hpp>

int main()
{
    luamdl3d::LDState::Init();
    
    sol::state lua;
    lua.open_libraries(sol::lib::string, sol::lib::math, sol::lib::table);
    luamdl3d::LLBindLogging(lua);
    luamdl3d::LDState::Bind(lua);

    auto result = lua.do_file("./script.lua");
    if (result.status() != sol::call_status::ok)
    {
        spdlog::error("Failed to run lua file!");
    }
}
