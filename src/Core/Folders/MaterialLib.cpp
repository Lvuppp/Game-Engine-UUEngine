#include "MaterialLib.h"

#include "Core/Services/ProjectInfo.h"

cMaterialLibrary::cMaterialLibrary()
{

}

void cMaterialLibrary::addMaterial(cMaterial *material)
{
    if (!material)
        return;

    if (std::find(m_materials.begin(), m_materials.end(), material) != m_materials.end())
        return;

    m_materials.push_back(material);
}

void cMaterialLibrary::loadMaterialsFromFile(const std::string &path)
{
    QFile file(QString::fromStdString(path));

    QTextStream inputStream(&file);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "\nmtl file";
        return;
    }

    QFileInfo fileInfo(QString::fromStdString(path));

    for (int i = 0; i < m_materials.size(); ++i)
        delete m_materials[i];
    m_materials.clear();

    cMaterial *newMtl = 0;

    while (!inputStream.atEnd()) {

        std::string str = inputStream.readLine().toStdString();

        QStringList list = QString::fromStdString(str).split(" ");

        if (list[0] == "newmtl") {

            addMaterial(newMtl);

            newMtl = new cMaterial;
            newMtl->setName(list[1].toStdString());
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
            //newMtl->setDiffuseMap(QString("%1/%2").arg(fileInfo.absolutePath(), list[1]).toStdString());
            //cProjectInfo::copyToModels(QString("%1/%2").arg(fileInfo.absolutePath(), list[1]).toStdString());
        }
        else if (list[0] == "map_Bump"){
            //newMtl->setNormalMap(QString("%1/%2").arg(fileInfo.absolutePath(), list[1]).toStdString());
            //cProjectInfo::copyToModels(QString("%1/%2").arg(fileInfo.absolutePath(), list[1]).toStdString());
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

cMaterial *cMaterialLibrary::material(const std::string &mtlName)
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
