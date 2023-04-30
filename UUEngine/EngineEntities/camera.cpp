#include "camera.h"

Camera::Camera(const QVector3D &coordinates, const QQuaternion &rotation, const float &scale, const bool &isObjectLocked) :
    BaseEngineObject(coordinates,rotation,scale,isObjectLocked)
{

}

Camera::~Camera()
{

}

void Camera::draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions)
{
    shaderProgram->setUniformValue("u_viewMatrix", this->modelMatrix());
}
