#ifndef OBJECTBUILDER_H
#define OBJECTBUILDER_H

#include "base3dgameobject.h"

class ObjectBuilder
{
public:
    ObjectBuilder();

    Model *createCube(const float &width, const float &height, const float &depth);
    Model *createSkybox(const float &size, const QString &texture);
};

#endif // OBJECTBUILDER_H
