#include "vertexdata.h"

VertexData::VertexData()
{

}

VertexData::VertexData(QVector3D position, QVector2D texture, QVector3D normal):
    position(position), texture(texture), normal(normal)
{

}
