#include "VertexData.h"

sVertexData::sVertexData()
{

}

sVertexData::sVertexData(QVector3D position, QVector2D texture, QVector3D normal):
    position(position), texture(texture), normal(normal)
{

}
