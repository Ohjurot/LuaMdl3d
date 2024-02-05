#include "LuaDraw.h"

void luamdl3d::LDState::Bind(sol::state& luaState)
{
    BindGeneral(luaState);
    BindDemo(luaState);
    BindCursor(luaState);
}
