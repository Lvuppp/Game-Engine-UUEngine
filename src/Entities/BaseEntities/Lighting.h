#ifndef LIGHTING_H
#define LIGHTING_H

#include "BaseEngineObject.h"

class cLighting : public cBaseEngineObject
{
public:
    cLighting();
    ~cLighting();

    void draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions = 0,  bool isUsingTexture = true) override;

private:
    float m_lightPower;
    bool m_isLightingDynamic;

};

#endif // LIGHTING_H
