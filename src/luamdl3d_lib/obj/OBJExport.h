#pragma once

#include <luamdl3d_lib/obj/OBJFile.h>
#include <luamdl3d_lib/obj/MTLFile.h>

#include <fstream>
#include <filesystem>

namespace luamdl3d
{
    class OBJExport
    {
        public:
            /*!
             * @brief Appends an object to the export
             * @param object Object to be appended to the output
            */
            void AppendObject(OBJObject&& object);

            /*!
             * @brief Appends a material to the output
             * @param material Material
            */
            void AppendMaterial(MTLMaterial&& material);

            /*!
             * @brief Writes the OBJ and MTL file to disk
             * @param baseFilePath Filepath to file without .obj or .mtl extension
             * @return True on success
            */
            bool Save(const std::filesystem::path& baseFilePath);

            /*!
             * @brief Clears all data from the export
            */
            void Clear();

        private:
            OBJFile m_obj;
            MTLFile m_mtl;
    };
}
