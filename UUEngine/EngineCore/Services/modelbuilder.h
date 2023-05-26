#ifndef MODELBUILDER_H
#define MODELBUILDER_H

#include "Models/simplemodel.h"

class ModelBuilder
{
public:
    ModelBuilder();

    static SimpleModel *createCube(const float &width, const float &height, const float &depth);
    static SimpleModel *createSkybox(const float &size, const QString &texture);
    static SimpleModel *createPyramide(const float &width, const float &height);

};

#endif // MODELBUILDER_H
