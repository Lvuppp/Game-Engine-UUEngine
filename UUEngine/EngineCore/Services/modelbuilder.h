#ifndef MODELBUILDER_H
#define MODELBUILDER_H

#include "base3dgameobject.h"

class ModelBuilder
{
public:
    ModelBuilder();

    static Model *createCube(const float &width, const float &height, const float &depth);
    static Model *createSkybox(const float &size, const QString &texture);
    static Model *createPyramide(const float &width, const float &height);
};

#endif // MODELBUILDER_H
