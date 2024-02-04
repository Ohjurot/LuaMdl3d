#include <spdlog/spdlog.h>
#include <sol/sol.hpp>

#include <luamdl3d_lib/obj/OBJFile.h>

#include <string>
#include <fstream>

void log(const std::string& msg)
{
    spdlog::info("{}", msg);
}

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
        { "Front",  { makeFace(0, 1, 2, 0), makeFace(2, 3, 0, 0) } },
        { "Back",   { makeFace(5, 4, 7, 1), makeFace(7, 6, 5, 1) } },
        { "Left",   { makeFace(4, 0, 3, 2), makeFace(3, 7, 4, 2) } },
        { "Right",  { makeFace(1, 5, 6, 3), makeFace(6, 2, 1, 3) } },
        { "Bottom", { makeFace(4, 5, 1, 4), makeFace(1, 0, 4, 4) } },
        { "Top",    { makeFace(3, 2, 6, 5), makeFace(6, 7, 3, 5) } }
    };

    // Add groups to the cube object
    for (auto& side : sides) {
        cube.Groups.push_back(side);
    }

    // Add cube object to the OBJ file
    objFile.Objects.push_back(cube);
}

int main()
{
    luamdl3d::OBJFile objFile;
    CreateCube(objFile);

    std::ofstream fout("./cube.obj", std::ios::out);
    fout << objFile;

    sol::state lua;
    lua.open_libraries(sol::lib::string, sol::lib::math, sol::lib::table);

    lua["log"] = (void(*)(const std::string&))&log;
    lua.do_file("./script.lua");
}
