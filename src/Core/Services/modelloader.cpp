#include "modelloader.h"

#include "Models/modelparticle.h"
#include "Models/custommodel.h"

ModelAbstractFactory::ModelAbstractFactory()
{

}

ModelAbstractFactory::~ModelAbstractFactory()
{

}

OBJModelFactory::OBJModelFactory() : ModelAbstractFactory()
{

}

OBJModelFactory::~OBJModelFactory()
{

}

CustomModel* OBJModelFactory::createModel(const QString &filePath)
{
    QFile objFile(filePath);

    QVector<QVector3D> coordinates;
    QVector<QVector2D> textureCoordinates;
    QVector<QVector3D> normals;

    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;
    QVector<ModelParticle *> models;

    if(!objFile.exists()){
        qDebug() << "cant read file";
        return new CustomModel(models);
    }

    objFile.open(QIODevice::ReadOnly);
    QTextStream stream(&objFile);

    Material *material = 0;
    ProjectInfo::copyToModels(filePath);

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
                vertexes.append(VertexData(coordinates[vertexData[0].toLong() - 1],
                                           textureCoordinates[vertexData[1].toLong() - 1],
                                           normals[vertexData[2].toLong() - 1]));
                indexes.append(indexes.size());
            }
        }
        else if(split[0] == "mtllib"){
            auto mtlPath = QFileInfo(filePath);
            ProjectInfo::copyToModels(QString("%1/%2").arg(mtlPath.absolutePath(), split[1]));
            library.loadMaterialsFromFile(QString("%1/%2").arg(mtlPath.absolutePath(), split[1]));
        }
        else if(split[0] == "usemtl"){
            if(vertexes.size() == 0 || indexes.size() == 0){
                material = library.material(split[1]);
                continue;
            }

            models.append(new ModelParticle(vertexes,indexes,material));

            material = library.material(split[1]);
            vertexes.clear();
            indexes.clear();
        }
    }

    objFile.close();

    models.append(new ModelParticle(vertexes,indexes,material));

    return new CustomModel(models);
}

FBXModelFactory::FBXModelFactory() : ModelAbstractFactory()
{

}

FBXModelFactory::~FBXModelFactory()
{

}

CustomModel* FBXModelFactory::createModel(const QString &filePath)
{
    return new CustomModel();
}

ModelLoader::ModelLoader(ModelAbstractFactory *strategy) : m_factory(strategy)
{
    m_modelFolder = ModelFolder::getInstance();
}

void ModelLoader::setFactory(ModelAbstractFactory *strategy)
{
    if(m_factory != nullptr){
        delete m_factory;
    }
    m_factory = strategy;
}

CustomModel* ModelLoader::createModel(const QString &filePath)
{
    return m_factory->createModel(filePath);
}



