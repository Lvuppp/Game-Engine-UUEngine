#include "camera.h"

Camera::Camera() :
    BaseEngineObject()
{
    m_objectType = ObjectType::Camera;
}

Camera::~Camera()
{


}
void Camera::draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions, bool isUsingTexture)
{
    shaderProgram->setUniformValue("u_viewMatrix", this->modelMatrix());
}
