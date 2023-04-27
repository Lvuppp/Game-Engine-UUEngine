#ifndef CAMERA_H
#define CAMERA_H

#include "baseengineobject.h"

class Camera : public BaseEngineObject
{
public:
    Camera(
        const QVector3D &coordinates = QVector3D(0.0f, 0.0f, 0.0f),
        const QQuaternion &rotation = QQuaternion(0.0f, 0.0f, 0.0f, 0.0f),
        const float &scale = 1.0f,
        const bool &isObjectLocked = false);
    ~Camera();

};

#endif // CAMERA_H
