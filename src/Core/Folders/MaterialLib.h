#ifndef MATERIALLIB_H
#define MATERIALLIB_H

#include "Material.h"

#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

#include <QDebug>

class cMaterialLibrary
{
public:

    cMaterialLibrary();

    void addMaterial(cMaterial* material);
    void loadMaterialsFromFile(const QString &path);

    cMaterial* material(quint32 index);
    cMaterial* material(const QString &mtlName);
    quint32 countMaterials();


private:
    QVector<cMaterial *> m_materials;
};

#endif // MATERIALLIB_H
