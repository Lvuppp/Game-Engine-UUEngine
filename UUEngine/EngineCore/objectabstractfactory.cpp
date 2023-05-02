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
    QVector<Model *> models;
    Material *material = 0;

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
            library.loadMaterialsFromFile(QString("%1/%2").arg(mtlPath.absolutePath()).arg(split[1]));
        }
        else if(split[0] == "usemtl"){
            if(vertexes.size() == 0 || indexes.size() == 0){
                material = library.material(split[1]);
                continue;
            }

            models.append(new Model(vertexes,indexes,material));

            material = library.material(split[1]);
            vertexes.clear();
            indexes.clear();
        }
    }

    objFile.close();

    models.append(new Model(vertexes,indexes,material));
    auto object = new Base3DGameObject(models);

    return object;
}
