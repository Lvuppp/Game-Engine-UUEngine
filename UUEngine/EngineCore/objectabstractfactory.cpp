#include "objectabstractfactory.h"

ObjectAbstractFactory::ObjectAbstractFactory()
{

}

Base3DGameObject *ObjectAbstractFactory::createObject(const QString &filePath)
{
    QFile objFile(filePath);

    if(!objFile.exists()){
        qDebug() << "cant read file";
        return 0;
    }

    objFile.open(QIODevice::ReadOnly);
    QTextStream stream(&objFile);

    QVector<QVector3D> coordinates;
    QVector<QVector2D> textureCoordinates;
    QVector<QVector3D> normals;

    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

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
        //материал
        }
    }

    objFile.close();

    auto obj = new Base3DGameObject(vertexes,indexes,QImage("/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Textures/texture1.jpg"),
                                    0.1f, 40.0f, QVector3D(0.0f,2.0f,0.0f),QQuaternion(0, 0.0f, 0.0f, 0.0f), 1.5);
    obj->setTexture(QImage("/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Textures/texture1.jpg"));
    return obj;
}
