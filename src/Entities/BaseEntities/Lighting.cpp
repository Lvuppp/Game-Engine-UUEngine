#include "Lighting.h"

#include "QOpenGLShaderProgram"

cLighting::cLighting()
    : cBaseEngineObject()
    , m_lightPower(5.0f)
    , m_isLightingDynamic(false)
{
}

cBaseEngineObject::ObjectType cLighting::objectType() const
{
    return cBaseEngineObject::ObjectType::Lighting;
}

void cLighting::draw(QOpenGLShaderProgram* shaderProgram, QOpenGLFunctions* /*functions*/, bool /*isUsingTexture*/)
{
    shaderProgram->setUniformValue("u_isDrawDynamic", m_isLightingDynamic);
    shaderProgram->setUniformValue("u_eyePosition", QVector4D(m_coordinates, 1.0f));
    shaderProgram->setUniformValue("u_lightPosition", QVector4D(0.0f,0.0f,0.0f,1.0f));
    shaderProgram->setUniformValue("u_lightPower", m_lightPower);
}
