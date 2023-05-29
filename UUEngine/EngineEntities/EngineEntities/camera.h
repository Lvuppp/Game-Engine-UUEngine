#ifndef CAMERA_H
#define CAMERA_H

#include "baseengineobject.h"

class Camera : public BaseEngineObject
{
public:
    Camera();
    ~Camera();

    void draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions = 0,  bool isUsingTexture = true) override;
};

#endif // CAMERA_H
