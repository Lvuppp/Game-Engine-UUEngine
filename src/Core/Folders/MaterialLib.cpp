#include "MaterialLib.h"

#include "Core/Folders/TextureFolder.h"
#include "Utils/Assert.h"

#include <QFile>
#include <QTextStream>
#include <QFileInfo>

cMaterialLibrary::cMaterialLibrary(cTextureManager* textureManager)
    : m_textureManager(textureManager)
{
}

void cMaterialLibrary::addMaterial(cMaterial* material)
{
    if (material == nullptr)
    {
        ASSERT(false, "Material is nullptr");
        return;
    }

    auto it = std::find_if(m_materials.begin(), m_materials.end(), [currentMaterial = material](const auto& material) {
        return material->getName() == currentMaterial->getName();
    });

    if (it != m_materials.end())
    {
        return;
    }

    m_materials.push_back(material);
}

void cMaterialLibrary::loadMaterialsFromFile(std::string_view filePath)
{
    QFile file(filePath.data());
    QTextStream inputStream(&file);
    QFileInfo fileInfo(filePath.data());
    const auto absoluteFilePath = fileInfo.absolutePath();

    if (file.open(QIODevice::ReadOnly) == false)
    {
        ASSERT(false, "Can`t open mtl file");
        return;
    }

    for (auto i = 0u; i < m_materials.size(); ++i)
    {
        delete m_materials[i];
    }
    m_materials.clear();

    cMaterial* newMtl = nullptr;

    while (inputStream.atEnd() == false)
    {
        const auto line = inputStream.readLine();
        const auto splitedLine = line.split(' ');
        const auto prefix = splitedLine[0];

        if (prefix == "newmtl")
        {
            if (newMtl != nullptr)
            {
                addMaterial(newMtl);
            }

            newMtl = new cMaterial();
            newMtl->setName(splitedLine[1].toStdString());
        }
        else if (prefix == "Ns")
        {
            newMtl->setShinnes(splitedLine[1].toFloat());
        }
        else if (prefix == "Ka")
        {
            const auto color = QVector3D(splitedLine[1].toFloat(), splitedLine[2].toFloat(), splitedLine[3].toFloat());
            newMtl->setAmbienceColor(color);
        }
        else if (prefix == "Kd")
        {
            const auto color = QVector3D(splitedLine[1].toFloat(), splitedLine[2].toFloat(), splitedLine[3].toFloat());
            newMtl->setDiffuseColor(color);
        }
        else if (prefix == "Ks")
        {
            const auto color = QVector3D(splitedLine[1].toFloat(), splitedLine[2].toFloat(), splitedLine[3].toFloat());
            newMtl->setSpecularColor(color);
        }
        else if (prefix == "map_Kd")
        {
            const auto filePath = absoluteFilePath + '/' + splitedLine[1];
            auto texture = m_textureManager->loadTexture(filePath.toStdString());
            newMtl->setDiffuseMap(texture);
        }
        else if (prefix == "map_Bump") 
        {
            const auto filePath = absoluteFilePath + '/' + splitedLine[1];
            auto texture = m_textureManager->loadTexture(filePath.toStdString());
            newMtl->setNormalMap(texture);
        }
    }
    file.close();

    addMaterial(newMtl);
}

cMaterial *cMaterialLibrary::material(quint32 index)
{
    if (index < m_materials.size())
    {
        return m_materials[index];
    }

    ASSERT(false, "Unknown Material!");
    return nullptr;
}

cMaterial* cMaterialLibrary::getMaterial(std::string_view mtlName)
{
    for (int i = 0; i < m_materials.size(); ++i)
    {
        if (m_materials[i]->getName() == mtlName)
        {
            return m_materials[i];
        }
    }

    return nullptr;
}

uint32_t cMaterialLibrary::countMaterials()
{
    return static_cast<uint32_t>(m_materials.size());
}
