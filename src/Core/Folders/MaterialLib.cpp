#include "MaterialLib.h"

#include "Services/Projectinfo.h"

cMaterialLibrary::cMaterialLibrary()
{

}

void cMaterialLibrary::addMaterial(cMaterial *material)
{
    if (!material)
        return;

    if (m_materials.contains(material))
        return;

    m_materials.append(material);
}

void cMaterialLibrary::loadMaterialsFromFile(const QString &path)
{
    QFile file(path);

    QTextStream inputStream(&file);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "\nmtl file";
        return;
    }

    QFileInfo fileInfo(std::move(path));

    for (int i = 0; i < m_materials.size(); ++i)
        delete m_materials[i];
    m_materials.clear();

    cMaterial *newMtl = 0;

    while (!inputStream.atEnd()) {

        QString str = inputStream.readLine();

        QStringList list = str.split(" ");

        if (list[0] == "newmtl") {

            addMaterial(newMtl);

            newMtl = new cMaterial;
            newMtl->setName(std::move(list[1]));
        }
        else if (list[0] == "Ns"){
            newMtl->setShinnes(list[1].toFloat());
        }
        else if (list[0] == "Ka"){
            newMtl->setAmbienceColor(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
        }
        else if (list[0] == "Kd"){
            newMtl->setDiffuseColor(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
        }
        else if (list[0] == "Ks"){
            newMtl->setSpecularColor(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
        }
        else if (list[0] == "map_Kd"){
            newMtl->setDiffuseMap(std::move(QString("%1/%2").arg(fileInfo.absolutePath()).arg(std::move(list[1]))));
            cProjectInfo::copyToModels(QString("%1/%2").arg(fileInfo.absolutePath()).arg(std::move(list[1])));
        }
        else if (list[0] == "map_Bump"){
            newMtl->setNormalMap(std::move(QString("%1/%2").arg(fileInfo.absolutePath()).arg(std::move(list[1]))));
            cProjectInfo::copyToModels(QString("%1/%2").arg(fileInfo.absolutePath()).arg(std::move(list[1])));
        }
    }

    addMaterial(newMtl);

    file.close();
}

cMaterial *cMaterialLibrary::material(quint32 index)
{
    if (index < m_materials.size())
        return m_materials[index];
    else
        return nullptr;
}

cMaterial *cMaterialLibrary::material(const QString &mtlName)
{
    for (int i = 0; i < m_materials.size(); ++i)
        if (m_materials[i]->mtlName() == mtlName)
            return m_materials[i];

    return nullptr;
}

quint32 cMaterialLibrary::countMaterials()
{
    return m_materials.size();
}
