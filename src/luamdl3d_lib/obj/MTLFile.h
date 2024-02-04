#pragma once

#include <DirectXMath.h>
#include <luamdl3d_lib/obj/DirectXMath_Stream.h>

#include <list>
#include <string>
#include <iomanip>
#include <ostream>
#include <sstream>

namespace luamdl3d
{
    using MTLColor = DirectX::XMFLOAT3;

    /*!
     * @brief Type of property
    */
    enum class MTLPropertyType
    {
        Ka,
        Kd,
        Ks,
        Ns,
        Tr,
        Ni,
        illum,
        map_Kd,
        map_Ka,
        map_Ks,
        map_Ns,
        map_Bump,
        map_d,
        disp,
        refl,
    };

    /*!
     * @brief Material property
    */
    struct MTLProperty
    {
        /*!
         * @brief Type of the property
        */
        MTLPropertyType Type;

        union
        {
            MTLColor    ColorValue;
            float       FloatValue;
            int         IntValue;
        };

        std::string     MapPath;
    };

    /*!
     * @brief Defines a unique material
    */
    struct MTLMaterial
    {
        /*!
         * @brief Label of the material
        */
        std::string MaterialName;

        /*!
         * @brief Material properties
        */
        std::list<MTLProperty> Properties;
    };

    /*!
     * @brief Collection of materials
    */
    struct MTLFile
    {
        /*!
         * @brief Comment of the file
        */
        std::string Comment =
            "LuaMdl3d OBJ-Modeler V1.0.0\n"
            "(c) Copyright 2024 Ludwig Fuechsl";

        /*!
         * @brief List of materials defined by that file
        */
        std::list<MTLMaterial> Materials;
    };

    void OutputMTLProperty_Color(std::ostream& out, const MTLProperty& property);
    void OutputMTLProperty_Float(std::ostream& out, const MTLProperty& property);
    void OutputMTLProperty_Int(std::ostream& out, const MTLProperty& property);
    void OutputMTLProperty_Map(std::ostream& out, const MTLProperty& property);
}

std::ostream& operator<<(std::ostream& out, luamdl3d::MTLPropertyType type);
std::ostream& operator<<(std::ostream& out, const luamdl3d::MTLProperty& property);
std::ostream& operator<<(std::ostream& out, const luamdl3d::MTLMaterial& material);
std::ostream& operator<<(std::ostream& out, const luamdl3d::MTLFile& file);
