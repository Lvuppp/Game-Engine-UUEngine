#ifndef CAMERA_H
#define CAMERA_H

#include "baseengineobject.h"

class Camera : public BaseEngineObject
{
public:
    Camera();
    ~Camera();

    void draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions) override;

};

#endif // CAMERA_H
