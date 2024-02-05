#include "LLLogging.h"

void luamdl3d::LLBindLogging(sol::state& luaState)
{
    luaState.set_function("info",
        [](const std::string& msg)
        {
            spdlog::info("{}", msg);
        }
    );
    luaState.set_function("warn",
        [](const std::string& msg)
        {
            spdlog::warn("{}", msg);
        }
    );
    luaState.set_function("error",
        [](const std::string& msg)
        {
            spdlog::error("{}", msg);
        }
    );
}
