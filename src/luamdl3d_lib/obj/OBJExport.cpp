#include "OBJExport.h"

void luamdl3d::OBJExport::AppendObject(OBJObject&& object)
{
    m_obj.Objects.push_back(std::move(object));
}

void luamdl3d::OBJExport::AppendMaterial(MTLMaterial&& material)
{
    m_mtl.Materials.push_back(std::move(material));
}

bool luamdl3d::OBJExport::Save(const std::filesystem::path& baseFilePath)
{
    auto objPath = baseFilePath;
    objPath.replace_extension(".obj");
    
    auto mtlPath = baseFilePath;
    mtlPath.replace_extension(".mtl");
    
    if (!m_mtl.Materials.empty())
    {
        m_obj.MTLFileName = mtlPath.filename().string();

        std::ofstream mtlFile(mtlPath, std::ios::out | std::ios::trunc);
        if (!mtlFile.is_open())
        {
            return false;
        }
        mtlFile << m_mtl;
    }

    std::ofstream objFile(objPath, std::ios::out | std::ios::trunc);
    if (!objFile.is_open())
    {
        return false;
    }
    objFile << m_obj;

    return true;
}

void luamdl3d::OBJExport::Clear()
{
    m_obj.MTLFileName = "";
    m_obj.Objects.clear();

    m_mtl.Materials.clear();
}
