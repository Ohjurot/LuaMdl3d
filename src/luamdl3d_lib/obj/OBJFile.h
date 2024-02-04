#pragma once

#include <DirectXMath.h>
#include <luamdl3d_lib/obj/DirectXMath_Stream.h>

#include <list>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <ostream>
#include <sstream>

namespace luamdl3d
{
    using OBJVector2F = DirectX::XMFLOAT2;
    using OBJVector3F = DirectX::XMFLOAT3;
    using OBJVector4F = DirectX::XMFLOAT4;

    /*!
     * @brief single edge that bind coordinates to the normals and textures
    */
    struct OBJPoint
    {
        uint32_t VertexIndex, NormalIndex, TexCordIndex;
    };

    /*!
     * @brief Defines a triangle from points
    */
    struct OBJFace3
    {
        OBJPoint Points[3];
    };

    /*!
     * @brief One group within an object
    */
    struct OBJGroup
    {
        /*!
         * @brief Labels the group
        */
        std::string GroupName;

        /*!
         * @brief Name of the material for the group
        */
        std::string MaterialName;

        /*!
         * @brief Faces in a group
        */
        std::vector<OBJFace3> Faces;
    };

    /*!
     * @brief One object within the file
    */
    struct OBJObject
    {
        /*!
         * @brief Labels the object
        */
        std::string ObjectName;

        /*!
         * @brief Name of material for the object
        */
        std::string MaterialName;

        /*!
         * @brief Verticies of the object
        */
        std::vector<OBJVector3F> Verticies;

        /*!
         * @brief Normals of the object
        */
        std::vector<OBJVector3F> Normals;

        /*!
         * @brief Texture coordinates of the object
        */
        std::vector<OBJVector3F> TexCords;
        bool TexCords3D = false;

        /*!
         * @brief Groups of objects parts
        */
        std::list<OBJGroup> Groups;
    };

    /*!
     * @brief 
    */
    struct OBJFile
    {
        /*!
         * @brief Comment of the file
        */
        std::string Comment = 
            "LuaMdl3d OBJ-Modeler V1.0.0\n"
            "(c) Copyright 2024 Ludwig Fuechsl";

        /*!
         * @brief Reference to the MTL File
        */
        std::string MTLFileName;

        /*!
         * @brief Encapsulated objects
        */
        std::list<OBJObject> Objects;

    };
}

std::ostream& operator<<(std::ostream& out, const luamdl3d::OBJPoint& pt);
std::ostream& operator<<(std::ostream& out, const luamdl3d::OBJFace3& face3);
std::ostream& operator<<(std::ostream& out, const luamdl3d::OBJGroup& group);
std::ostream& operator<<(std::ostream& out, const luamdl3d::OBJObject& object);
std::ostream& operator<<(std::ostream& out, const luamdl3d::OBJFile& file);
