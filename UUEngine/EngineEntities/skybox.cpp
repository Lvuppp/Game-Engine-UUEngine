#include "skybox.h"
#include "vertexdata.h"

SkyBox::SkyBox(const float& size, const QImage& texture)
{
    QVector<VertexData> vertexes;

    vertexes.append(VertexData(QVector3D(-size, size, size), QVector2D(1.0f, 2.0f/3.0f), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-size, -size, size), QVector2D(1.0f, 1.0f/3.0f), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(size, size, size), QVector2D(3.0f/4.0f, 2.0f/3.0f), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(size, -size, size), QVector2D(3.0f/4.0f, 1.0f/3.0f), QVector3D(0.0, 0.0, -1.0)));

    vertexes.append(VertexData(QVector3D(size, size, size), QVector2D(3.0f/4.0f, 2.0f/3.0f), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(size, -size, size), QVector2D(3.0f/4.0f, 1.0f/3.0f), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(size, size, -size), QVector2D(2.0f/4.0f, 2.0f/3.0f), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(size, -size, -size), QVector2D(2.0f/4.0f, 1.0f/3.0f), QVector3D(-1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(size, size, size), QVector2D(2.0f/4.0f, 1.0f), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(size, size, -size), QVector2D(2.0f/4.0f, 2.0f/3.0f), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-size, size, size), QVector2D(1.0f/4.0f, 1.0f), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-size, size, -size), QVector2D(1.0f/4.0f, 2.0f/3.0f), QVector3D(0.0, -1.0, 0.0)));

    vertexes.append(VertexData(QVector3D(size, size, -size), QVector2D(2.0f/4.0f, 2.0f/3.0f), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(size, -size, -size), QVector2D(2.0f/4.0f, 1.0f/3.0f), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-size, size, -size), QVector2D(1.0f/4.0f, 2.0f/3.0f), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-size, -size, -size), QVector2D(1.0f/4.0f, 1.0f/3.0f), QVector3D(0.0, 0.0, 1.0)));

    vertexes.append(VertexData(QVector3D(-size, size, size), QVector2D(0.0, 2.0f/3.0f), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-size, size, -size), QVector2D(1.0f/4.0f, 2.0f/3.0f), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-size, -size, size), QVector2D(0.0f, 1.0f/3.0f), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-size, -size, -size), QVector2D(1.0f/4.0f, 1.0f/3.0f), QVector3D(1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(-size, -size, size), QVector2D(1.0f/4.0f, 0.0f), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-size, -size, -size), QVector2D(1.0f/4.0f, 1.0f/3.0f), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(size, -size, size), QVector2D(2.0f/4.0f, 0.0f), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(size, -size, -size), QVector2D(2.0f/4.0f, 1.0f/3.0f), QVector3D(0.0, 1.0, 0.0)));

    QVector<GLuint> indexes;

    for (short i = 0; i < 24; i += 4) {

        indexes.append(i + 0);
        indexes.append(i + 2);
        indexes.append(i + 1);

        indexes.append(i + 2);
        indexes.append(i + 3);
        indexes.append(i + 1);
    }

    //Model *

    //m_model = new Base3DGameObject();
}

SkyBox::~SkyBox()
{
    delete m_model;
}

Base3DGameObject *SkyBox::model()
{
    return m_model;
}


