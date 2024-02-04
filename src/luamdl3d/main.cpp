#include <spdlog/spdlog.h>
#include <sol/sol.hpp>

#include <luamdl3d_lib/obj/OBJFile.h>
#include <luamdl3d_lib/obj/MTLFile.h>

#include <string>
#include <fstream>

const char* G_materialNames[] = { "RedMetal", "GreenMetal", "BlueMetal", "YellowMetal", "CyanMetal", "MagentaMetal" };

void lua_info(const std::string& msg) { spdlog::info("{}", msg); }
void lua_warn(const std::string& msg) { spdlog::warn("{}", msg); }
void lua_error(const std::string& msg) { spdlog::error("{}", msg); }

void CreateCube(luamdl3d::OBJFile& objFile) {
    // Cube definition
    luamdl3d::OBJObject cube;
    cube.ObjectName = "Cube";

    // Define vertices of the cube
    cube.Verticies = {
        { -0.5f, -0.5f, -0.5f }, // 0
        { 0.5f, -0.5f, -0.5f },  // 1
        { 0.5f, 0.5f, -0.5f },   // 2
        { -0.5f, 0.5f, -0.5f },  // 3
        { -0.5f, -0.5f, 0.5f },  // 4
        { 0.5f, -0.5f, 0.5f },   // 5
        { 0.5f, 0.5f, 0.5f },    // 6
        { -0.5f, 0.5f, 0.5f }    // 7
    };

    // Define normals pointing outwards from each face
    cube.Normals = {
        { 0.0f, 0.0f, -1.0f }, // Front
        { 0.0f, 0.0f, 1.0f },  // Back
        { -1.0f, 0.0f, 0.0f }, // Left
        { 1.0f, 0.0f, 0.0f },  // Right
        { 0.0f, -1.0f, 0.0f }, // Bottom
        { 0.0f, 1.0f, 0.0f }   // Top
    };

    // Optionally, define texture coordinates for each vertex (dummy values used here)
    cube.TexCords = {
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f }
    };

    // Helper lambda to create a face
    auto makeFace = [](uint32_t v1, uint32_t v2, uint32_t v3, uint32_t n) -> luamdl3d::OBJFace3 {
        return { { {v1, n, 0}, {v2, n, 0}, {v3, n, 0} } };
        };

    // Define faces (two triangles per side, 12 triangles total)
    // Assuming counter-clockwise winding
    std::vector<luamdl3d::OBJGroup> sides = {
        { "Front",  G_materialNames[0], { makeFace(0, 1, 2, 0), makeFace(2, 3, 0, 0) } },
        { "Back",   G_materialNames[1], { makeFace(5, 4, 7, 1), makeFace(7, 6, 5, 1) } },
        { "Left",   G_materialNames[2], { makeFace(4, 0, 3, 2), makeFace(3, 7, 4, 2) } },
        { "Right",  G_materialNames[3], { makeFace(1, 5, 6, 3), makeFace(6, 2, 1, 3) } },
        { "Bottom", G_materialNames[4], { makeFace(4, 5, 1, 4), makeFace(1, 0, 4, 4) } },
        { "Top",    G_materialNames[5], { makeFace(3, 2, 6, 5), makeFace(6, 7, 3, 5) } }
    };

    // Add groups to the cube objects
    for (auto& side : sides) {
        cube.Groups.push_back(side);
    }

    // Add cube object to the OBJ file
    objFile.Objects.push_back(cube);
}

void CreateMetallicMaterials(luamdl3d::MTLFile& mtlFile) {
    // Define six colors for the metallic materials
    luamdl3d::MTLColor colors[] = {
        {1.0f, 0.0f, 0.0f}, // Red
        {0.0f, 1.0f, 0.0f}, // Green
        {0.0f, 0.0f, 1.0f}, // Blue
        {1.0f, 1.0f, 0.0f}, // Yellow
        {0.0f, 1.0f, 1.0f}, // Cyan
        {1.0f, 0.0f, 1.0f}  // Magenta
    };

    for (int i = 0; i < 6; ++i) {
        luamdl3d::MTLMaterial material;
        material.MaterialName = G_materialNames[i];

        // Diffuse Color (Kd)
        luamdl3d::MTLProperty kd;
        kd.Type = luamdl3d::MTLPropertyType::Kd;
        kd.ColorValue = colors[i];
        material.Properties.push_back(kd);

        // Specular Color (Ks) - assuming a generic metallic specular color
        luamdl3d::MTLProperty ks;
        ks.Type = luamdl3d::MTLPropertyType::Ks;
        ks.ColorValue = { 0.5f, 0.5f, 0.5f };
        material.Properties.push_back(ks);

        // Specular Exponent (Ns) - giving a sharp specular highlight
        luamdl3d::MTLProperty ns;
        ns.Type = luamdl3d::MTLPropertyType::Ns;
        ns.FloatValue = 25.0f; // A common value for metals, adjust as needed
        material.Properties.push_back(ns);

        // Add the material to the file
        mtlFile.Materials.push_back(material);
    }
}

int main()
{
    luamdl3d::OBJFile objFile;
    luamdl3d::MTLFile mtlFile;

    CreateCube(objFile);
    CreateMetallicMaterials(mtlFile);
    
    objFile.MTLFileName = "cube.mtl";
    std::ofstream foutObj("./cube.obj", std::ios::out);
    foutObj << objFile;
    std::ofstream foutMtl("./cube.mtl", std::ios::out);
    foutMtl << mtlFile;

    sol::state lua;
    lua.open_libraries(sol::lib::string, sol::lib::math, sol::lib::table);

    lua["info"] = (void(*)(const std::string&))&lua_info;
    lua["warn"] = (void(*)(const std::string&))&lua_warn;
    lua["error"] = (void(*)(const std::string&))&lua_error;

    lua.do_file("./script.lua");
}
