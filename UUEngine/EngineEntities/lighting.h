#ifndef LIGHTING_H
#define LIGHTING_H

#include "baseengineobject.h"

class Lighting : public BaseEngineObject
{
public:
    Lighting(
        const QVector3D &coordinates = QVector3D(0.0f, 0.0f, 0.0f),
        const QQuaternion &rotation = QQuaternion(0.0f, 0.0f, 0.0f, 0.0f),
        const float &scale = 1.0f,
        const bool &isObjectLocked = false);

private:

};

#endif // LIGHTING_H
