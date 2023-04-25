#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <QVector3D>

struct VertexData{
    VertexData();
    VertexData(QVector3D position, QVector2D texture, QVector3D normal);

    QVector3D position;
    QVector2D texture;
    QVector3D normal;

};


#endif // VERTEXDATA_H
