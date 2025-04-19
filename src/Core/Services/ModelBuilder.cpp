#include "ModelBuilder.h"

#include "Entities/Material.h"
#include "Entities/Models/Model.h"
#include "Entities/VertexData.h"
#include <memory>


cModel *cModelBuilder::createCube(const float &width, const float &height, const float &depth)
{
    std::vector<sVertexData> vertexes;
    std::vector<GLuint> indexes;

    vertexes.emplace_back(sVertexData(QVector3D(-width, height, depth), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-width, -height, depth), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.emplace_back(sVertexData(QVector3D(width, height, depth), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.emplace_back(sVertexData(QVector3D(width, -height, depth), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));

    vertexes.emplace_back(sVertexData(QVector3D(width, height, depth), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(width, -height, depth), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(width, height, -depth), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(width, -height, -depth), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    vertexes.emplace_back(sVertexData(QVector3D(width, height, depth), QVector2D(0.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(width, height, -depth), QVector2D(0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-width, height, depth), QVector2D(1.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-width, height, -depth), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));

    vertexes.emplace_back(sVertexData(QVector3D(width, height, -depth), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.emplace_back(sVertexData(QVector3D(width, -height, -depth), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-width, height, -depth), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-width, -height, -depth), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));

    vertexes.emplace_back(sVertexData(QVector3D(-width, height, depth), QVector2D(0.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-width, height, -depth), QVector2D(0.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-width, -height, depth), QVector2D(1.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-width, -height, -depth), QVector2D(1.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));

    vertexes.emplace_back(sVertexData(QVector3D(-width, -height, depth), QVector2D(0.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-width, -height, -depth), QVector2D(0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(width, -height, depth), QVector2D(1.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(width, -height, -depth), QVector2D(1.0, 0.0), QVector3D(0.0, -1.0, 0.0)));


    for(int i = 0; i < 24; i += 4) {
        indexes.emplace_back(i + 0);
        indexes.emplace_back(i + 1);
        indexes.emplace_back(i + 2);

        indexes.emplace_back(i + 2);
        indexes.emplace_back(i + 1);
        indexes.emplace_back(i + 3);
    }

    cMaterial *material = new cMaterial();
    material->setDiffuseColor(QVector3D(0.5, 0.5, 0.5));


    return new cModel(std::make_shared<cModelParticle>(vertexes, indexes, material));
}

cModel *cModelBuilder::createSkybox(const float &size, const std::string &texture)
{
    std::vector<sVertexData> vertexes;
    std::vector<GLuint> indexes;

    vertexes.emplace_back(sVertexData(QVector3D(-size, size, size), QVector2D(1.0f, 2.0f/3.0f), QVector3D(0.0, 0.0, -1.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-size, -size, size), QVector2D(1.0f, 1.0f/3.0f), QVector3D(0.0, 0.0, -1.0)));
    vertexes.emplace_back(sVertexData(QVector3D(size, size, size), QVector2D(3.0f/4.0f, 2.0f/3.0f), QVector3D(0.0, 0.0, -1.0)));
    vertexes.emplace_back(sVertexData(QVector3D(size, -size, size), QVector2D(3.0f/4.0f, 1.0f/3.0f), QVector3D(0.0, 0.0, -1.0)));

    vertexes.emplace_back(sVertexData(QVector3D(size, size, size), QVector2D(3.0f/4.0f, 2.0f/3.0f), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(size, -size, size), QVector2D(3.0f/4.0f, 1.0f/3.0f), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(size, size, -size), QVector2D(2.0f/4.0f, 2.0f/3.0f), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(size, -size, -size), QVector2D(2.0f/4.0f, 1.0f/3.0f), QVector3D(-1.0, 0.0, 0.0)));

    vertexes.emplace_back(sVertexData(QVector3D(size, size, size), QVector2D(2.0f/4.0f, 1.0f), QVector3D(0.0, -1.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(size, size, -size), QVector2D(2.0f/4.0f, 2.0f/3.0f), QVector3D(0.0, -1.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-size, size, size), QVector2D(1.0f/4.0f, 1.0f), QVector3D(0.0, -1.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-size, size, -size), QVector2D(1.0f/4.0f, 2.0f/3.0f), QVector3D(0.0, -1.0, 0.0)));

    vertexes.emplace_back(sVertexData(QVector3D(size, size, -size), QVector2D(2.0f/4.0f, 2.0f/3.0f), QVector3D(0.0, 0.0, 1.0)));
    vertexes.emplace_back(sVertexData(QVector3D(size, -size, -size), QVector2D(2.0f/4.0f, 1.0f/3.0f), QVector3D(0.0, 0.0, 1.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-size, size, -size), QVector2D(1.0f/4.0f, 2.0f/3.0f), QVector3D(0.0, 0.0, 1.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-size, -size, -size), QVector2D(1.0f/4.0f, 1.0f/3.0f), QVector3D(0.0, 0.0, 1.0)));

    vertexes.emplace_back(sVertexData(QVector3D(-size, size, size), QVector2D(0.0, 2.0f/3.0f), QVector3D(1.0, 0.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-size, size, -size), QVector2D(1.0f/4.0f, 2.0f/3.0f), QVector3D(1.0, 0.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-size, -size, size), QVector2D(0.0f, 1.0f/3.0f), QVector3D(1.0, 0.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-size, -size, -size), QVector2D(1.0f/4.0f, 1.0f/3.0f), QVector3D(1.0, 0.0, 0.0)));

    vertexes.emplace_back(sVertexData(QVector3D(-size, -size, size), QVector2D(1.0f/4.0f, 0.0f), QVector3D(0.0, 1.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-size, -size, -size), QVector2D(1.0f/4.0f, 1.0f/3.0f), QVector3D(0.0, 1.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(size, -size, size), QVector2D(2.0f/4.0f, 0.0f), QVector3D(0.0, 1.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(size, -size, -size), QVector2D(2.0f/4.0f, 1.0f/3.0f), QVector3D(0.0, 1.0, 0.0)));


    for (short i = 0; i < 24; i += 4) {

        indexes.emplace_back(i + 0);
        indexes.emplace_back(i + 2);
        indexes.emplace_back(i + 1);

        indexes.emplace_back(i + 2);
        indexes.emplace_back(i + 3);
        indexes.emplace_back(i + 1);
    }

    cMaterial *material = new cMaterial();
    material->setDiffuseMap(texture);
    return new cModel(std::make_shared<cModelParticle>(vertexes, indexes, material));
}

cModel *cModelBuilder::createPyramide(const float &width, const float &height)
{
    return nullptr;
}

cModel *cModelBuilder::createSphere(const float &radius, const int &stacks, const int &sectors)
{
    std::vector<sVertexData> vertexes;
    std::vector<GLuint> indexes;

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
    float s, t;
    float const PI = 3.1415926f;

    float sectorStep = 2 *  PI / sectors;
    float stackStep = PI / stacks;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stacks; ++i)
    {
        stackAngle =  PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for(int j = 0; j <= sectors; ++j)
        {
            sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);

            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;

            s = static_cast<float>(j) / sectors;
            t = static_cast<float>(i) / stacks;

            vertexes.emplace_back(QVector3D(x,y,z), QVector2D(s,t), QVector3D(nx,ny,nz));
        }
    }

    int k1, k2;
    for(int i = 0; i < stacks; ++i)
    {
        k1 = i * (sectors + 1);
        k2 = k1 + sectors + 1;      // beginning of next stack

        for(int j = 0; j < sectors; ++j, ++k1, ++k2)
        {
            if(i != 0)
            {
                indexes.emplace_back(k1);
                indexes.emplace_back(k2);
                indexes.emplace_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if(i != (stacks - 1))
            {
                indexes.emplace_back(k1 + 1);
                indexes.emplace_back(k2);
                indexes.emplace_back(k2 + 1);
            }
        }
    }


    cMaterial *material = new cMaterial();
    material->setDiffuseColor(QVector3D(0.5, 0.5, 0.5));


    return new cModel(std::make_shared<cModelParticle>(vertexes, indexes, material));
}

cModel* cModelBuilder::createPrism(const float &width, const float &height, const float &depth, const float &angle)
{
    return nullptr;
}

cModel* cModelBuilder::createCone(const float &radius, const float &height, const int &sectors)
{
    return nullptr;
}

cModel *cModelBuilder::createCylinder(const float &radius, const float &height, const int &sectors)
{
    return nullptr;
}
