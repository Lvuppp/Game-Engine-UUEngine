#ifndef CAMERA_H
#define CAMERA_H

#include "BaseEngineObject.h"

class cCamera : public cBaseEngineObject
{
public:
    cCamera();
    ~cCamera();

    void draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions = 0,  bool isUsingTexture = true) override;
};

#endif // CAMERA_H
