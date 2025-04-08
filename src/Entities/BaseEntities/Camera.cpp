#include "Camera.h"

#include "QOpenGLShaderProgram"

cBaseEngineObject::ObjectType cCamera::objectType() const
{
    return cBaseEngineObject::ObjectType::Camera;
}

void cCamera::draw(QOpenGLShaderProgram* shaderProgram, QOpenGLFunctions* /*functions*/, bool /*isUsingTexture*/)
{
    shaderProgram->setUniformValue("u_viewMatrix", m_modelMatrix);
}
