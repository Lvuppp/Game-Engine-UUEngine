#include "camera.h"

Camera::Camera() :
    BaseEngineObject()
{

}

Camera::~Camera()
{


}
void Camera::draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions, bool isUsingTexture)
{
    shaderProgram->setUniformValue("u_viewMatrix", this->modelMatrix());
}