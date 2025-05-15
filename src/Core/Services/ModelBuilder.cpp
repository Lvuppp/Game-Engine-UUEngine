#include "ModelBuilder.h"

#include "Entities/Material.h"
#include "Entities/Models/Model.h"
#include "Entities/VertexData.h"

#include "Utils/Assert.h"

#include <memory>

cModel* cModelBuilder::createBaseFigure(Base3DFiguresType figureType)
{
    switch (figureType)
    {
        case Base3DFiguresType::Cube:
            return createCube(5.0f, 5.0f, 5.0f);

        case Base3DFiguresType::Sphere:
            return createSphere(1.0f, 20u, 20u);

        case Base3DFiguresType::Cone:
            return createCone(2.5f, 5.0f, 20u);

        case Base3DFiguresType::Cylinder:
            return createCylinder(2.5f, 5.0f, 20u);

        case Base3DFiguresType::Prism:
            return createPrism(5.0f, 5.0f, 5.0f, 45.0f);

        case Base3DFiguresType::Pyramid:
            return createPyramide(5.0f, 5.0f);

        default:
            return nullptr;
    }

    ASSERT(true, "Unknown figure");
    return nullptr;
}

cModel *cModelBuilder::createCube(float width, float height, float depth)
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

cModel *cModelBuilder::createSkybox(float size, QOpenGLTexture* texture)
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

cModel *cModelBuilder::createPyramide(float width, float height)
{
    std::vector<sVertexData> vertexes;
    std::vector<GLuint> indexes;

    vertexes.emplace_back(sVertexData(QVector3D(-width/2, -height/2, -width/2), QVector2D(0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(width/2, -height/2, -width/2), QVector2D(1.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(width/2, -height/2, width/2), QVector2D(1.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.emplace_back(sVertexData(QVector3D(-width/2, -height/2, width/2), QVector2D(0.0, 1.0), QVector3D(0.0, -1.0, 0.0)));

    vertexes.emplace_back(sVertexData(QVector3D(0.0, height/2, 0.0), QVector2D(0.5, 0.5), QVector3D(0.0, 1.0, 0.0)));

    indexes.emplace_back(0);
    indexes.emplace_back(1);
    indexes.emplace_back(2);

    indexes.emplace_back(0);
    indexes.emplace_back(2);
    indexes.emplace_back(3);

    indexes.emplace_back(0);
    indexes.emplace_back(4);
    indexes.emplace_back(1);

    indexes.emplace_back(1);
    indexes.emplace_back(4);
    indexes.emplace_back(2);

    indexes.emplace_back(2);
    indexes.emplace_back(4);
    indexes.emplace_back(3);

    indexes.emplace_back(3);
    indexes.emplace_back(4);
    indexes.emplace_back(0);

    cMaterial *material = new cMaterial();
    material->setDiffuseColor(QVector3D(0.5, 0.5, 0.5));

    return new cModel(std::make_shared<cModelParticle>(vertexes, indexes, material));
}

cModel *cModelBuilder::createSphere(float radius, uint32_t stacks, uint32_t sectors)
{
    std::vector<sVertexData> vertexes;
    std::vector<GLuint> indexes;

    float x, y, z, xy;                              
    float nx, ny, nz, lengthInv = 1.0f / radius;    
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
        k2 = k1 + sectors + 1;

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

cModel* cModelBuilder::createPrism(float width, float height, float depth, float angle)
{
    std::vector<sVertexData> vertexes;
    std::vector<GLuint> indexes;

    float angleRad = angle * M_PI / 180.0f;
    float cosAngle = cosf(angleRad);
    float sinAngle = sinf(angleRad);

    vertexes.emplace_back(sVertexData(QVector3D(-width/2, -height/2, -depth/2), QVector2D(0.0f, 0.0f), QVector3D(0.0f, -1.0f, 0.0f)));
    vertexes.emplace_back(sVertexData(QVector3D(width/2, -height/2, -depth/2), QVector2D(1.0f, 0.0f), QVector3D(0.0f, -1.0f, 0.0f)));
    vertexes.emplace_back(sVertexData(QVector3D(width/2 * cosAngle - depth/2 * sinAngle, -height/2, width/2 * sinAngle + depth/2 * cosAngle), 
                                    QVector2D(1.0f, 1.0f), QVector3D(0.0f, -1.0f, 0.0f)));
    vertexes.emplace_back(sVertexData(QVector3D(-width/2 * cosAngle - depth/2 * sinAngle, -height/2, -width/2 * sinAngle + depth/2 * cosAngle), 
                                    QVector2D(0.0f, 1.0f), QVector3D(0.0f, -1.0f, 0.0f)));

    vertexes.emplace_back(sVertexData(QVector3D(-width/2, height/2, -depth/2), QVector2D(0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f)));
    vertexes.emplace_back(sVertexData(QVector3D(width/2, height/2, -depth/2), QVector2D(1.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f)));
    vertexes.emplace_back(sVertexData(QVector3D(width/2 * cosAngle - depth/2 * sinAngle, height/2, width/2 * sinAngle + depth/2 * cosAngle), 
                                    QVector2D(1.0f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f)));
    vertexes.emplace_back(sVertexData(QVector3D(-width/2 * cosAngle - depth/2 * sinAngle, height/2, -width/2 * sinAngle + depth/2 * cosAngle), 
                                    QVector2D(0.0f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f)));

    indexes.emplace_back(0);
    indexes.emplace_back(1);
    indexes.emplace_back(2);
    indexes.emplace_back(0);
    indexes.emplace_back(2);
    indexes.emplace_back(3);

    // Верхнее основание
    indexes.emplace_back(4);
    indexes.emplace_back(6);
    indexes.emplace_back(5);
    indexes.emplace_back(4);
    indexes.emplace_back(7);
    indexes.emplace_back(6);

    indexes.emplace_back(0);
    indexes.emplace_back(4);
    indexes.emplace_back(1);
    indexes.emplace_back(1);
    indexes.emplace_back(4);
    indexes.emplace_back(5);

    indexes.emplace_back(1);
    indexes.emplace_back(5);
    indexes.emplace_back(2);
    indexes.emplace_back(2);
    indexes.emplace_back(5);
    indexes.emplace_back(6);

    indexes.emplace_back(2);
    indexes.emplace_back(6);
    indexes.emplace_back(3);
    indexes.emplace_back(3);
    indexes.emplace_back(6);
    indexes.emplace_back(7);

    indexes.emplace_back(3);
    indexes.emplace_back(7);
    indexes.emplace_back(0);
    indexes.emplace_back(0);
    indexes.emplace_back(7);
    indexes.emplace_back(4);

    cMaterial *material = new cMaterial();
    material->setDiffuseColor(QVector3D(0.5, 0.5, 0.5));

    return new cModel(std::make_shared<cModelParticle>(vertexes, indexes, material));
}

cModel* cModelBuilder::createCone(float radius, float height, uint32_t sectors)
{
    std::vector<sVertexData> vertexes;
    std::vector<GLuint> indexes;

    float sectorStep = 2.0f * M_PI / sectors;
    float const PI = 3.1415926f;

    vertexes.emplace_back(sVertexData(QVector3D(0.0f, -height/2, 0.0f), QVector2D(0.5f, 0.5f), QVector3D(0.0f, -1.0f, 0.0f)));

    for(uint32_t i = 0; i <= sectors; ++i)
    {
        float sectorAngle = i * sectorStep;
        float x = radius * cosf(sectorAngle);
        float z = radius * sinf(sectorAngle);
        
        vertexes.emplace_back(sVertexData(
            QVector3D(x, -height / 2, z),
            QVector2D(0.5f + 0.5f * cosf(sectorAngle), 0.5f + 0.5f * sinf(sectorAngle)),
            QVector3D(0.0f, -1.0f, 0.0f)
        ));

        QVector3D normal = QVector3D(x, height/2, z).normalized();
        vertexes.emplace_back(sVertexData(
            QVector3D(x, -height/2, z),
            QVector2D(static_cast<float>(i) / sectors, 0.0f),
            normal
        ));
    }

    vertexes.emplace_back(sVertexData(
        QVector3D(0.0f, height/2, 0.0f),
        QVector2D(0.5f, 1.0f),
        QVector3D(0.0f, 1.0f, 0.0f)
    ));

    for(uint32_t i = 0; i < sectors; ++i)
    {
        indexes.emplace_back(0);
        indexes.emplace_back(1 + i * 2);
        indexes.emplace_back(1 + (i + 1) * 2);
    }

    for(uint32_t i = 0; i < sectors; ++i)
    {
        indexes.emplace_back(1 + i * 2 + 1);
        indexes.emplace_back(vertexes.size() - 1);
        indexes.emplace_back(1 + ((i + 1) % sectors) * 2 + 1);
    }

    cMaterial *material = new cMaterial();
    material->setDiffuseColor(QVector3D(0.5, 0.5, 0.5));

    return new cModel(std::make_shared<cModelParticle>(vertexes, indexes, material));
}

cModel *cModelBuilder::createCylinder(float radius, float height, uint32_t sectors)
{
    std::vector<sVertexData> vertexes;
    std::vector<GLuint> indexes;

    float sectorStep = 2.0f * M_PI / sectors;
    float const PI = 3.1415926f;

    vertexes.emplace_back(sVertexData(QVector3D(0.0f, -height/2, 0.0f), QVector2D(0.5f, 0.5f), QVector3D(0.0f, -1.0f, 0.0f)));
    vertexes.emplace_back(sVertexData(QVector3D(0.0f, height/2, 0.0f), QVector2D(0.5f, 0.5f), QVector3D(0.0f, 1.0f, 0.0f)));

    for(uint32_t i = 0; i <= sectors; ++i)
    {
        float sectorAngle = i * sectorStep;
        float x = radius * cosf(sectorAngle);
        float z = radius * sinf(sectorAngle);
        
        vertexes.emplace_back(sVertexData(
            QVector3D(x, -height / 2, z),
            QVector2D(0.5f + 0.5f * cosf(sectorAngle), 0.5f + 0.5f * sinf(sectorAngle)),
            QVector3D(0.0f, -1.0f, 0.0f)
        ));

        vertexes.emplace_back(sVertexData(
            QVector3D(x, height / 2, z),
            QVector2D(0.5f + 0.5f * cosf(sectorAngle), 0.5f + 0.5f * sinf(sectorAngle)),
            QVector3D(0.0f, 1.0f, 0.0f)
        ));

        QVector3D normal = QVector3D(cosf(sectorAngle), 0.0f, sinf(sectorAngle));
        vertexes.emplace_back(sVertexData(
            QVector3D(x, -height / 2, z),
            QVector2D(static_cast<float>(i) / sectors, 0.0f),
            normal
        ));
        vertexes.emplace_back(sVertexData(
            QVector3D(x, height / 2, z),
            QVector2D(static_cast<float>(i) / sectors, 1.0f),
            normal
        ));
    }

    for(uint32_t i = 0; i < sectors; ++i)
    {
        indexes.emplace_back(0);
        indexes.emplace_back(2 + i * 4);
        indexes.emplace_back(2 + ((i + 1) % sectors) * 4);

        indexes.emplace_back(1);
        indexes.emplace_back(3 + i * 4);
        indexes.emplace_back(3 + ((i + 1) % sectors) * 4);
    }

    for(uint32_t i = 0; i < sectors; ++i)
    {
        uint32_t baseIndex = 4 + i * 4;
        indexes.emplace_back(baseIndex);
        indexes.emplace_back(baseIndex + 1);
        indexes.emplace_back(baseIndex + 4);
        indexes.emplace_back(baseIndex + 1);
        indexes.emplace_back(baseIndex + 5);
        indexes.emplace_back(baseIndex + 4);
    }

    cMaterial *material = new cMaterial();
    material->setDiffuseColor(QVector3D(0.5, 0.5, 0.5));

    return new cModel(std::make_shared<cModelParticle>(vertexes, indexes, material));
}
