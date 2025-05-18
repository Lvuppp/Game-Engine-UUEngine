#include "ModelLoader.h"

#include "Core/Folders/ModelFolder.h"
#include "Entities/Models/ModelParticle.h"
#include "Entities/VertexData.h"

#include <QFile>
#include <QFileInfo>

#include <iostream>

OBJModelFactory::OBJModelFactory(cTextureManager* textureManager)
    : m_library(textureManager)
{

}

cModel* OBJModelFactory::createModel(std::string_view filePath)
{
    QFile objFile(filePath.data());
    QFileInfo fileInfo(filePath.data());

    std::vector<QVector3D> coordinates;
    std::vector<QVector2D> textureCoordinates;
    std::vector<QVector3D> normals;

    cModelParticle::Vertexes vertexes;
    cModelParticle::Indexes indexes;
    std::vector<std::shared_ptr<cModelParticle>> models;

    if (objFile.exists() == false)
    {
        std::cout << "Cant read file" << std::endl;
        return new cModel(models);
    }

    objFile.open(QIODevice::ReadOnly);
    QTextStream stream(&objFile);

    cMaterial* material = nullptr;
    //file_utils::copyFile();

    while (stream.atEnd() == false)
    {
        const auto line = stream.readLine();
        const auto splitedLine = line.split(' ');
        const auto prefix = splitedLine[0];

        if (prefix == "v")
        {
            const auto coords = QVector3D{ splitedLine[1].toFloat(),splitedLine[2].toFloat(),splitedLine[3].toFloat() };
            coordinates.emplace_back(coords);
        }
        else if (prefix == "vt")
        {
            const auto coords = QVector2D{ splitedLine[1].toFloat(),splitedLine[2].toFloat() };
            textureCoordinates.emplace_back(coords);
        }
        else if (prefix == "vn")
        {
            const auto normalsCoords = QVector3D{ splitedLine[1].toFloat(),splitedLine[2].toFloat(),splitedLine[3].toFloat() };
            normals.emplace_back(normalsCoords);
        }
        else if (prefix == "f")
        {
            for (auto i = 1u; i < splitedLine.size(); i++)
            {
                const auto vertexDataSplited = splitedLine[i].split("/");

                const auto vertexData = sVertexData{ coordinates[vertexDataSplited[0].toInt() - 1],
                                           textureCoordinates[vertexDataSplited[1].toInt() - 1],
                                           normals[vertexDataSplited[2].toInt() - 1] };

                vertexes.emplace_back(vertexData);
                indexes.emplace_back(static_cast<unsigned int>(indexes.size()));
            }
        }
        else if (prefix == "mtllib")
        {
            const auto mtlPath = (fileInfo.absolutePath() + "/" + splitedLine[1]).toStdString();
            m_library.loadMaterialsFromFile(mtlPath);
        }
        else if (prefix == "usemtl")
        {
            if (vertexes.empty() || indexes.empty())
            {
                material = m_library.getMaterial(splitedLine[1].toStdString());
                continue;
            }

            models.emplace_back(std::make_shared<cModelParticle>(vertexes, indexes, material));

            material = m_library.getMaterial(splitedLine[1].toStdString());
            vertexes.clear();
            indexes.clear();
        }
    }

    objFile.close();

    if (vertexes.empty() == false && indexes.empty() == false)
    {
        models.emplace_back(std::make_shared<cModelParticle>(vertexes, indexes, material));
    }

    return new cModel(models);
}

cModel* FBXModelFactory::createModel(std::string_view filePath)
{
    return new cModel();
}

void cModelLoader::setFactory(ModelAbstractFactory *strategy)
{
    if(m_factory != nullptr)
    {
        delete m_factory;
    }
    m_factory = strategy;
}

cModel* cModelLoader::createModel(std::string_view filePath)
{
    return m_factory->createModel(filePath);
}
