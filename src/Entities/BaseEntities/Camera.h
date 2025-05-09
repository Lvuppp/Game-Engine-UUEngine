#ifndef CAMERA_H
#define CAMERA_H

#include "Entities/BaseEntities/BaseEngineObject.h"

class cCamera : public cBaseEngineObject
{
public:
    cCamera() = default;
    ~cCamera() = default; 
    
    ObjectType objectType() const override;
    void draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions,  bool isUsingTexture) override;
};

#endif // CAMERA_H
