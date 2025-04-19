#include "ModelLoader.h"

#include "Core/Folders/ModelFolder.h"
#include "Entities/Models/ModelParticle.h"
#include "Entities/VertexData.h"
#include "Core/Services/ProjectInfo.h"

cModel* OBJModelFactory::createModel(const std::string &filePath)
{
    QFile objFile(filePath.c_str());

    std::vector<QVector3D> coordinates;
    std::vector<QVector2D> textureCoordinates;
    std::vector<QVector3D> normals;

    cModelParticle::Vertexes vertexes;
    cModelParticle::Indexes indexes;
    std::vector<std::shared_ptr<cModelParticle>> models;

    if(!objFile.exists()){
        qDebug() << "cant read file";
        return new cModel(models);
    }

    objFile.open(QIODevice::ReadOnly);
    QTextStream stream(&objFile);

    cMaterial *material = nullptr; // Fixed initialization to nullptr
    cProjectInfo::copyToModels(filePath);

    while(!stream.atEnd()){

        auto split = stream.readLine().split(" ");

        if(split[0] == "v"){
            coordinates.emplace_back(QVector3D(split[1].toFloat(),split[2].toFloat(),split[3].toFloat()));
        }
        else if(split[0] == "vt"){
            textureCoordinates.emplace_back(QVector2D(split[1].toFloat(),split[2].toFloat()));
        }
        else if(split[0] == "vn"){
            normals.emplace_back(QVector3D(split[1].toFloat(),split[2].toFloat(),split[3].toFloat()));
        }
        else if(split[0] == "f"){
            for (int i = 1; i < split.size(); i++) {
                auto vertexData = split[i].split("/");
                vertexes.emplace_back(sVertexData(coordinates[vertexData[0].toInt() - 1], // Fixed toInt instead of toLong
                                           textureCoordinates[vertexData[1].toInt() - 1],
                                           normals[vertexData[2].toInt() - 1]));
                indexes.emplace_back(static_cast<unsigned int>(indexes.size())); // Explicit cast to unsigned int
            }
        }
        else if(split[0] == "mtllib"){
            auto mtlPath = QFileInfo(filePath.c_str());
            cProjectInfo::copyToModels((mtlPath.absolutePath() + "/" + split[1]).toStdString()); // Fixed string concatenation
            library.loadMaterialsFromFile((mtlPath.absolutePath() + "/" + split[1]).toStdString());
        }
        else if(split[0] == "usemtl"){
            if(vertexes.empty() || indexes.empty()){
                //material = library.material(split[1]);
                continue;
            }

            models.emplace_back(std::make_shared<cModelParticle>(vertexes, indexes, material));

            //material = library.material(split[1]);
            vertexes.clear();
            indexes.clear();
        }
    }

    objFile.close();

    if (!vertexes.empty() && !indexes.empty()) { // Ensure no empty data is added
        models.emplace_back(std::make_shared<cModelParticle>(vertexes, indexes, material));
    }

    return new cModel(models);
}

cModel* FBXModelFactory::createModel(const std::string &filePath)
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

cModel* cModelLoader::createModel(const std::string &filePath)
{
    return m_factory->createModel(filePath);
}
