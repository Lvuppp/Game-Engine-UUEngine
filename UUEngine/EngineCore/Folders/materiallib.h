#ifndef MATERIALLIB_H
#define MATERIALLIB_H

#include "material.h"
#include "Services/projectinfo.h"

#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

#include <QDebug>

class MaterialLibrary
{
public:

    MaterialLibrary();

    void addMaterial(Material* material);
    void loadMaterialsFromFile(const QString &path);

    Material* material(quint32 index);
    Material* material(const QString &mtlName);
    quint32 countMaterials();


private:
    QVector<Material *> m_materials;
};

#endif // MATERIALLIB_H
