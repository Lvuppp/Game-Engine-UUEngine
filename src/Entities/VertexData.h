#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <QVector3D>

struct sVertexData{
    sVertexData();
    sVertexData(QVector3D position, QVector2D texture, QVector3D normal);

    QVector3D position;
    QVector2D texture;
    QVector3D normal;
    QVector3D tangent;
    QVector3D bitangent;
};


#endif // VERTEXDATA_H
