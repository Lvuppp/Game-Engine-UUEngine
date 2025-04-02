#ifndef MODELBUILDER_H
#define MODELBUILDER_H

#include "Models/SimpleModel.h"

enum class SimpleModelType{
    Cube,
    Pyramid,
    Sphere,
    Prism,
    Cone,
    Cylinder
};


class cModelBuilder
{
public:
    cModelBuilder();

    cSimpleModel *createSkybox(const float &size, const QString &texture);

    cSimpleModel *createCube(const float &width, const float &height, const float &depth);
    cSimpleModel *createPyramide(const float &width, const float &height);
    cSimpleModel *createSphere(const float & radius, const int & rings, const int & sectors);
    cSimpleModel *createPrism(const float &width, const float &height, const float &depth, const float &angle);
    cSimpleModel *createCone(const float & radius, const float & height, const int & sectors);
    cSimpleModel *createCylinder(const float & radius, const float & height, const int & sectors);

};


#endif // MODELBUILDER_H
