#ifndef LIGHTING_H
#define LIGHTING_H

#include "baseengineobject.h"

class Lighting : public BaseEngineObject
{
public:
    Lighting();
    ~Lighting();

    void draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions) override;

private:
    float m_lightPower;
    bool m_isLightingDynamic;

};

#endif // LIGHTING_H
