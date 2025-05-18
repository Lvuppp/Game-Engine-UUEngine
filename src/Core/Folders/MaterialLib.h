#ifndef MATERIALLIB_H
#define MATERIALLIB_H

#include "Entities/Material.h"

#include <vector>

class cTextureManager;

class cMaterialLibrary
{
public:
    cMaterialLibrary(cTextureManager* textureManager);

    void addMaterial(cMaterial* material);
    void loadMaterialsFromFile(std::string_view path);

    cMaterial* material(uint32_t index);
    cMaterial* getMaterial(std::string_view mtlName);
    uint32_t countMaterials();

private:
    cTextureManager* m_textureManager = nullptr;

    std::vector<cMaterial *> m_materials;
};

#endif // MATERIALLIB_H
