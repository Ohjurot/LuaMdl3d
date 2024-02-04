#include "OBJFile.h"

std::ostream& operator<<(std::ostream& out, const luamdl3d::OBJPoint& pt)
{
    out << (pt.VertexIndex + 1) << "/" << (pt.TexCordIndex + 1)  << "/" << (pt.NormalIndex + 1);
    return out;
}

std::ostream& operator<<(std::ostream& out, const luamdl3d::OBJFace3& face3)
{
    out << "f " << face3.Points[0] << " " << face3.Points[1] << " " << face3.Points[2];
    return out;
}

std::ostream& operator<<(std::ostream& out, const luamdl3d::OBJGroup& group)
{
    if (!group.GroupName.empty())
    {
        out << "g " << group.GroupName << std::endl;
    }

    if (!group.MaterialName.empty())
    {
        out << "usemtl " << group.MaterialName << std::endl;
    }

    for (const auto& face : group.Faces)
    {
        out << face << std::endl;
    }

    return out;
}

std::ostream& operator<<(std::ostream& out, const luamdl3d::OBJObject& object)
{
    if (!object.ObjectName.empty())
    {
        out << "o " << object.ObjectName << std::endl;
    }

    if (!object.MaterialName.empty())
    {
        out << "usemtl " << object.MaterialName << std::endl;
    }

    for (const auto& vertex : object.Verticies)
    {
        out << "v " << vertex << std::endl;
    }
    for (const auto& texCord : object.TexCords)
    {
        if (object.TexCords3D)
        {
            out << "vt " << texCord << std::endl;
        }
        else
        {
            luamdl3d::OBJVector2F v2f(texCord.x, texCord.y);
            out << "vt " << v2f << std::endl;
        }
    }
    for (const auto& normal : object.Normals)
    {
        out << "vn " << normal << std::endl;
    }

    for (const auto& group : object.Groups)
    {
        out << group;
    }

    return out;
}

std::ostream& operator<<(std::ostream& out, const luamdl3d::OBJFile& file)
{
    std::stringstream ss;
    ss << file.Comment;
    std::string line;
    while (std::getline(ss, line))
    {
        out << "# " << line << std::endl;
    }

    if (!file.MTLFileName.empty())
    {
        out << "mtllib " << file.MTLFileName << std::endl;
    }

    for (const auto& object : file.Objects)
    {
        out << object;
    }

    return out;
}
