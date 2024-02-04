#include "MTLFile.h"

void luamdl3d::OutputMTLProperty_Color(std::ostream& out, const MTLProperty& property)
{
    out << property.Type << " " << property.ColorValue << std::endl;
}

void luamdl3d::OutputMTLProperty_Float(std::ostream& out, const MTLProperty& property)
{
    out << property.Type << " " << property.FloatValue << std::endl;
}

void luamdl3d::OutputMTLProperty_Int(std::ostream& out, const MTLProperty& property)
{
    out << property.Type << " " << property.IntValue << std::endl;
}

void luamdl3d::OutputMTLProperty_Map(std::ostream& out, const MTLProperty& property)
{
    out << property.Type << " " << property.MapPath << std::endl;
}

std::ostream& operator<<(std::ostream& out, luamdl3d::MTLPropertyType type)
{
    switch (type)
    {
        case luamdl3d::MTLPropertyType::Ka:
            out << "Ka";
            break;
        case luamdl3d::MTLPropertyType::Kd:
            out << "Kd";
            break;
        case luamdl3d::MTLPropertyType::Ks:
            out << "Ks";
            break;
        case luamdl3d::MTLPropertyType::Ns:
            out << "Ns";
            break;
        case luamdl3d::MTLPropertyType::Tr:
            out << "Tr";
            break;
        case luamdl3d::MTLPropertyType::Ni:
            out << "Ni";
            break;
        case luamdl3d::MTLPropertyType::illum:
            out << "illum";
            break;
        case luamdl3d::MTLPropertyType::map_Kd:
            out << "map_Kd";
            break;
        case luamdl3d::MTLPropertyType::map_Ka:
            out << "map_Ka";
            break;
        case luamdl3d::MTLPropertyType::map_Ks:
            out << "map_Ks";
            break;
        case luamdl3d::MTLPropertyType::map_Ns:
            out << "map_Ns";
            break;
        case luamdl3d::MTLPropertyType::map_Bump:
            out << "map_Bump";
            break;
        case luamdl3d::MTLPropertyType::map_d:
            out << "map_d";
            break;
        case luamdl3d::MTLPropertyType::disp:
            out << "disp";
            break;
        case luamdl3d::MTLPropertyType::refl:
            out << "refl";
            break;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const luamdl3d::MTLProperty& property)
{
    switch (property.Type)
    {
        case luamdl3d::MTLPropertyType::Ka:
        case luamdl3d::MTLPropertyType::Kd:
        case luamdl3d::MTLPropertyType::Ks:
            luamdl3d::OutputMTLProperty_Color(out, property);
            break;
        case luamdl3d::MTLPropertyType::Ns:
        case luamdl3d::MTLPropertyType::Tr:
        case luamdl3d::MTLPropertyType::Ni:
            luamdl3d::OutputMTLProperty_Float(out, property);
            break;
        case luamdl3d::MTLPropertyType::illum:
            luamdl3d::OutputMTLProperty_Int(out, property);
            break;
        case luamdl3d::MTLPropertyType::map_Kd:
        case luamdl3d::MTLPropertyType::map_Ka:
        case luamdl3d::MTLPropertyType::map_Ks:
        case luamdl3d::MTLPropertyType::map_Ns:
        case luamdl3d::MTLPropertyType::map_Bump:
        case luamdl3d::MTLPropertyType::map_d:
        case luamdl3d::MTLPropertyType::disp:
        case luamdl3d::MTLPropertyType::refl:
            luamdl3d::OutputMTLProperty_Map(out, property);
            break;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const luamdl3d::MTLMaterial& material)
{
    out << "newmtl " << material.MaterialName << std::endl;
    for (const auto& propertie : material.Properties)
    {
        out << propertie;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const luamdl3d::MTLFile& file)
{
    std::stringstream ss;
    ss << file.Comment;
    std::string line;
    while (std::getline(ss, line))
    {
        out << "# " << line << std::endl;
    }

    for (const auto& material : file.Materials)
    {
        out << material;
    }

    return out;
}
