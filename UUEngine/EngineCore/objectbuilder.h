#ifndef OBJECTBUILDER_H
#define OBJECTBUILDER_H

#include "base3dgameobject.h"

class ObjectBuilder
{
public:
    ObjectBuilder();

    Model *createCube(const float &width, const float &height, const float &depth);
};

#endif // OBJECTBUILDER_H
