#include "modelbuilder.h"

ModelBuilder::ModelBuilder()
{
}

SimpleModel *ModelBuilder::createCube(const float &width, const float &height, const float &depth)
{
    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    vertexes.append(VertexData(QVector3D(-width, height, depth), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-width, -height, depth), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width, height, depth), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width, -height, depth), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));

    vertexes.append(VertexData(QVector3D(width, height, depth), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width, -height, depth), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width, height, -depth), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width, -height, -depth), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width, height, depth), QVector2D(0.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width, height, -depth), QVector2D(0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width, height, depth), QVector2D(1.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width, height, -depth), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width, height, -depth), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(width, -height, -depth), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width, height, -depth), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width, -height, -depth), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));

    vertexes.append(VertexData(QVector3D(-width, height, depth), QVector2D(0.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width, height, -depth), QVector2D(0.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width, -height, depth), QVector2D(1.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width, -height, -depth), QVector2D(1.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(-width, -height, depth), QVector2D(0.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width, -height, -depth), QVector2D(0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width, -height, depth), QVector2D(1.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width, -height, -depth), QVector2D(1.0, 0.0), QVector3D(0.0, -1.0, 0.0)));



    for(int i = 0; i < 24; i += 4) {
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);

        indexes.append(i + 2);
        indexes.append(i + 1);
        indexes.append(i + 3);
    }

    Material *material = new Material();
    material->setDiffuseColor(QVector3D(0.5, 0.5, 0.5));


    return new SimpleModel(new ModelParticle(vertexes,indexes, material));
}

SimpleModel *ModelBuilder::createSkybox(const float &size, const QString &texture)
{
    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

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


    for (short i = 0; i < 24; i += 4) {

        indexes.append(i + 0);
        indexes.append(i + 2);
        indexes.append(i + 1);

        indexes.append(i + 2);
        indexes.append(i + 3);
        indexes.append(i + 1);
    }

    Material *material = new Material();
    material->setDiffuseMap(std::move(texture));
    return new SimpleModel(new ModelParticle(vertexes,indexes, material));
}

SimpleModel *ModelBuilder::createPyramide(const float &width, const float &height)
{
    return nullptr;
}

SimpleModel *ModelBuilder::createSphere(const float &radius, const int &rings, const int &sectors)
{
    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    float const PI = 3.1415926f;
    float const PI_2 = PI * 2.0f;

    float const R = 1.0f / (float)(rings - 1);
    float const S = 1.0f / (float)(sectors - 1);

    for (int r = 0; r < rings; ++r) {
        for (int s = 0; s < sectors; ++s) {
            float const y = sin(-PI_2 + PI * r * R);
            float const x = cos(PI_2 * s * S) * sin(PI * r * R);
            float const z = sin(PI_2 * s * S) * sin(PI * r * R);

            QVector3D position(x * radius, y * radius, z * radius);
            QVector2D texture(s * S, r * R);
            QVector3D normal(x, y, z);

            vertexes.emplace_back(position, texture, normal);
        }
    }


    for (int r = 0; r < rings - 1; ++r) {
        for (int s = 0; s < sectors - 1; ++s) {
            int currentRow = r * sectors;
            int nextRow = (r + 1) * sectors;

            indexes.append(currentRow + s);
            indexes.append(nextRow + s);
            indexes.append(nextRow + s + 1);

            indexes.append(currentRow + s);
            indexes.append(nextRow + s + 1);
            indexes.append(currentRow + s + 1);
        }
    }


    Material *material = new Material();
    material->setDiffuseColor(QVector3D(0.5, 0.5, 0.5));


    return new SimpleModel(new ModelParticle(vertexes,indexes, material));
}

SimpleModel *ModelBuilder::createPrism(const float &width, const float &height, const float &depth, const float &angle)
{

}

SimpleModel *ModelBuilder::createCone(const float &radius, const float &height, const int &sectors)
{

}

SimpleModel *ModelBuilder::createCylinder(const float &radius, const float &height, const int &sectors)
{

}
