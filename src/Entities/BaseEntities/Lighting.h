#ifndef LIGHTING_H
#define LIGHTING_H

#include "Entities/BaseEntities/BaseEngineObject.h"

class cLighting : public cBaseEngineObject
{
public:
    cLighting() = default;
    cLighting(uint32_t id);
    ~cLighting() = default;

public:
    ObjectType objectType() const override;

    void draw(QOpenGLShaderProgram* shaderProgram, QOpenGLFunctions* functions, bool isUsingTexture) override;

private:
    float m_lightPower = 5.0f;
    bool m_isLightingDynamic = false;
};

#endif // LIGHTING_H
