#ifndef MODELBUILDER_H
#define MODELBUILDER_H

#include <string>

enum class SimpleModelType{
    Cube,
    Pyramid,
    Sphere,
    Prism,
    Cone,
    Cylinder
};

class cModel;

class cModelBuilder
{
public:
    cModel *createSkybox(const float &size, const std::string &texture);

    cModel *createCube(const float &width, const float &height, const float &depth);
    cModel *createPyramide(const float &width, const float &height);
    cModel *createSphere(const float & radius, const int & rings, const int & sectors);
    cModel *createPrism(const float &width, const float &height, const float &depth, const float &angle);
    cModel *createCone(const float & radius, const float & height, const int & sectors);
    cModel *createCylinder(const float & radius, const float & height, const int & sectors);

};


#endif // MODELBUILDER_H
