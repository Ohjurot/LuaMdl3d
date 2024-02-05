#pragma once

#include <luamdl3d_lib/obj/OBJExport.h>

#include <sol/sol.hpp>
#include <spdlog/spdlog.h>

#include <stack>
#include <string>

namespace luamdl3d::LDState
{
    struct CursorData
    {
        float PositionX = .0f;
        float PositionY = .0f;
        float PositionZ = .0f;
    };

    struct Data
    {
        std::string CurrentObject;
        std::string CurrentGroup;

        std::stack<CursorData> Cursors;

        uint32_t vi = 0;
        uint32_t ni = 0;
        uint32_t ti = 0;

        OBJExport Export;
    };

    /*!
     * @brief Initializes the data
    */
    void Init();

    /*!
     * @brief Retrieve the instance of the state data
     * @return Static instance as ref
    */
    inline Data& GetData()
    {
        static Data data;
        return data;
    }
}
