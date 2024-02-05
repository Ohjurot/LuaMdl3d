#include "LDDemo.h"

void luamdl3d::LDState::demo_cube(float size)
{
    // Cube definition
    luamdl3d::OBJObject cube;
    cube.ObjectName = GetData().CurrentObject;

    uint32_t vi = GetData().vi;
    uint32_t ni = GetData().ni;
    uint32_t ti = GetData().ti;

    // Define vertices of the cube
    auto& cur = GetData().Cursors.top();
    cube.Verticies = {
        { cur.PositionX - size, cur.PositionY - size, cur.PositionZ - size }, // 0
        { cur.PositionX + size, cur.PositionY - size, cur.PositionZ - size }, // 1
        { cur.PositionX + size, cur.PositionY + size, cur.PositionZ - size }, // 2
        { cur.PositionX - size, cur.PositionY + size, cur.PositionZ - size }, // 3
        { cur.PositionX - size, cur.PositionY - size, cur.PositionZ + size }, // 4
        { cur.PositionX + size, cur.PositionY - size, cur.PositionZ + size }, // 5
        { cur.PositionX + size, cur.PositionY + size, cur.PositionZ + size }, // 6
        { cur.PositionX - size, cur.PositionY + size, cur.PositionZ + size }  // 7
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

    GetData().vi += cube.Verticies.size();
    GetData().ni += cube.Normals.size();
    GetData().ti += cube.TexCords.size();

    // Helper lambda to create a face
    auto makeFace = [&](uint32_t v1, uint32_t v2, uint32_t v3, uint32_t n) -> luamdl3d::OBJFace3 {
        return { { {vi + v1, ni + n, ti + 0}, {vi + v2, ni + n, ti + 0}, {vi + v3, ni + n, ti + 0} } };
        };

    // Define faces (two triangles per side, 12 triangles total)
    // Assuming counter-clockwise winding
    std::vector<luamdl3d::OBJGroup> sides = {
        { "DEMO_Front",  LDDemoMaterialNames[0], { makeFace(0, 1, 2, 0), makeFace(2, 3, 0, 0) } },
        { "DEMO_Back",   LDDemoMaterialNames[1], { makeFace(5, 4, 7, 1), makeFace(7, 6, 5, 1) } },
        { "DEMO_Left",   LDDemoMaterialNames[2], { makeFace(4, 0, 3, 2), makeFace(3, 7, 4, 2) } },
        { "DEMO_Right",  LDDemoMaterialNames[3], { makeFace(1, 5, 6, 3), makeFace(6, 2, 1, 3) } },
        { "DEMO_Bottom", LDDemoMaterialNames[4], { makeFace(4, 5, 1, 4), makeFace(1, 0, 4, 4) } },
        { "DEMO_Top",    LDDemoMaterialNames[5], { makeFace(3, 2, 6, 5), makeFace(6, 7, 3, 5) } }
    };

    // Add groups to the cube objects
    for (auto& side : sides) {
        cube.Groups.push_back(side);
    }

    // Add cube object to the OBJ file
    GetData().Export.AppendObject(std::move(cube));
}

void luamdl3d::LDState::demo_materials()
{
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
        material.MaterialName = LDDemoMaterialNames[i];

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
        GetData().Export.AppendMaterial(std::move(material));
    }
}

void luamdl3d::LDState::BindDemo(sol::state& luaState)
{
    luaState.set_function("demo_cube", (demo_cube_t)&demo_cube);
    luaState.set_function("demo_materials", (demo_materials_t)&demo_materials);
}
