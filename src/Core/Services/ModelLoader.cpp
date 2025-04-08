#include "ModelLoader.h"

#include "Core/Folders/ModelFolder.h"
#include "Entities/Models/ModelParticle.h"
#include "Entities/VertexData.h"
#include "Core/Services/Projectinfo.h"


cModel* OBJModelFactory::createModel(const QString &filePath)
{
    QFile objFile(filePath);

    QVector<QVector3D> coordinates;
    QVector<QVector2D> textureCoordinates;
    QVector<QVector3D> normals;

    cModelParticle::Vertexes vertexes;
    cModelParticle::Indexes indexes;
    std::vector<std::shared_ptr<cModelParticle>> models;

    if(!objFile.exists()){
        qDebug() << "cant read file";
        return new cModel(models);
    }

    objFile.open(QIODevice::ReadOnly);
    QTextStream stream(&objFile);

    cMaterial *material = 0;
    cProjectInfo::copyToModels(filePath);

    while(!stream.atEnd()){

        auto split = stream.readLine().split(" ");

        if(split[0] == "v"){
            coordinates.append(QVector3D(split[1].toFloat(),split[2].toFloat(),split[3].toFloat()));
        }
        else if(split[0] == "vt"){
            textureCoordinates.append(QVector2D(split[1].toFloat(),split[2].toFloat()));
        }
        else if(split[0] == "vn"){
            normals.append(QVector3D(split[1].toFloat(),split[2].toFloat(),split[3].toFloat()));
        }
        else if(split[0] == "f"){
            for (int i = 1; i < split.size(); i++) {
                auto vertexData = split[i].split("/");
                vertexes.emplace_back(sVertexData(coordinates[vertexData[0].toLong() - 1],
                                           textureCoordinates[vertexData[1].toLong() - 1],
                                           normals[vertexData[2].toLong() - 1]));
                indexes.emplace_back(indexes.size());
            }
        }
        else if(split[0] == "mtllib"){
            auto mtlPath = QFileInfo(filePath);
            cProjectInfo::copyToModels(QString("%1/%2").arg(mtlPath.absolutePath(), split[1]));
            library.loadMaterialsFromFile(QString("%1/%2").arg(mtlPath.absolutePath(), split[1]));
        }
        else if(split[0] == "usemtl"){
            if(vertexes.size() == 0 || indexes.size() == 0){
                material = library.material(split[1]);
                continue;
            }

            models.emplace_back(std::make_shared<cModelParticle>(vertexes, indexes, material));

            material = library.material(split[1]);
            vertexes.clear();
            indexes.clear();
        }
    }

    objFile.close();

    models.emplace_back(std::make_shared<cModelParticle>(vertexes, indexes, material));

    return new cModel(models);
}

cModel* FBXModelFactory::createModel(const QString &filePath)
{
    return new cModel();
}

cModelLoader::cModelLoader(ModelAbstractFactory *strategy) : m_factory(strategy)
{
    m_modelFolder = cModelFolder::getInstance();
}

void cModelLoader::setFactory(ModelAbstractFactory *strategy)
{
    if(m_factory != nullptr){
        delete m_factory;
    }
    m_factory = strategy;
}

cModel* cModelLoader::createModel(const QString &filePath)
{
    return m_factory->createModel(filePath);
}
