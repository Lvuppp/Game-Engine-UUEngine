#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <QVector3D>
#include <vector>

struct sVertexData{
    sVertexData() = default;
    sVertexData(QVector3D position, QVector2D texture, QVector3D normal);

    QVector3D position = QVector3D{ 0.0f, 0.0f, 0.0f };
    QVector2D texture = QVector2D{ 0.0f, 0.0f };
    QVector3D normal = QVector3D{ 0.0f, 0.0f, 0.0f };
    QVector3D tangent = QVector3D{ 0.0f, 0.0f, 0.0f };
    QVector3D bitangent = QVector3D{ 0.0f, 0.0f, 0.0f };
};

#endif // VERTEXDATA_H
