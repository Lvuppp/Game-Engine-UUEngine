#ifndef MATERIALLIB_H
#define MATERIALLIB_H

#include "Entities/Material.h"

#include <vector>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

#include <QDebug>

class cMaterialLibrary
{
public:
    cMaterialLibrary();

    void addMaterial(cMaterial* material);
    void loadMaterialsFromFile(const std::string &path);

    cMaterial* material(quint32 index);
    cMaterial* material(const std::string &mtlName);
    quint32 countMaterials();

private:
    std::vector<cMaterial *> m_materials;
};

#endif // MATERIALLIB_H
