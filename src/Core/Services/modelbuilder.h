#ifndef MODELBUILDER_H
#define MODELBUILDER_H

#include "Models/simplemodel.h"

enum class SimpleModelType{
    Cube,
    Pyramid,
    Sphere,
    Prism,
    Cone,
    Cylinder
};


class ModelBuilder
{
public:
    ModelBuilder();

    SimpleModel *createSkybox(const float &size, const QString &texture);

    SimpleModel *createCube(const float &width, const float &height, const float &depth);
    SimpleModel *createPyramide(const float &width, const float &height);
    SimpleModel *createSphere(const float & radius, const int & rings, const int & sectors);
    SimpleModel *createPrism(const float &width, const float &height, const float &depth, const float &angle);
    SimpleModel *createCone(const float & radius, const float & height, const int & sectors);
    SimpleModel *createCylinder(const float & radius, const float & height, const int & sectors);

};


#endif // MODELBUILDER_H
