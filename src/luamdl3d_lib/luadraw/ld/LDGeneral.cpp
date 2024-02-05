#include "LDGeneral.h"

void luamdl3d::LDState::object(const std::string& name)
{
    GetData().CurrentObject = name;
}

void luamdl3d::LDState::group(const std::string& name)
{
    GetData().CurrentGroup = name;
}

void luamdl3d::LDState::save(const std::string& outputPath)
{
    GetData().Export.Save(outputPath);
}

void luamdl3d::LDState::BindGeneral(sol::state& luaState)
{
    luaState.set_function("object", (object_t)&object);
    luaState.set_function("group", (group_t)&group);
    luaState.set_function("save", (save_t)&save);
}
