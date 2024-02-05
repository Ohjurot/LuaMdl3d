#pragma once

#include <luamdl3d_lib/luadraw/LDState.h>

namespace luamdl3d::LDState
{
    /*!
     * @brief Material names for the demo
    */
    inline constexpr const char* LDDemoMaterialNames[] = { 
        "DEMO_RedMetal", 
        "DEMO_GreenMetal", 
        "DEMO_BlueMetal", 
        "DEMO_YellowMetal", 
        "DEMO_CyanMetal", 
        "DEMO_MagentaMetal" 
    };

    // === BEGIN ===
    
    using demo_cube_t = void(*)(float);
    void demo_cube(float size);

    using demo_materials_t = void(*)();
    void demo_materials();

    // === END ===

    void BindDemo(sol::state& luaState);
}
