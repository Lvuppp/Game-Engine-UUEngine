#ifndef MODELBUILDER_H
#define MODELBUILDER_H

#include <cstdint>

class cModel;
class QOpenGLTexture;

class cModelBuilder
{
public:
    enum class Base3DFiguresType
    {
        Cube,
        Pyramid,
        Sphere,
        Prism,
        Cone,
        Cylinder
    };
    cModel* createBaseFigure(Base3DFiguresType figureType);
    cModel* createSkybox(float size, QOpenGLTexture* texture);

private:
    cModel* createCube(float width, float height, float depth);
    cModel* createPyramide(float width, float height);
    cModel* createSphere(float  radius, uint32_t rings, uint32_t sectors);
    cModel* createPrism(float width, float height, float depth, float angle);
    cModel* createCone(float  radius, float  height, uint32_t sectors);
    cModel* createCylinder(float  radius, float  height, uint32_t sectors);
};

#endif // MODELBUILDER_H
