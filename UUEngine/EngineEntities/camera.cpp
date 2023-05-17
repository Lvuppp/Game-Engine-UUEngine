#include "camera.h"

Camera::Camera() :
    BaseEngineObject()
{

}

Camera::~Camera()
{


}

void Camera::addScript(QString script)
{
    m_scriptsNames.append(script);
}

QVector<QString> Camera::scripts()
{
    return m_scriptsNames;
}


void Camera::draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions)
{
    shaderProgram->setUniformValue("u_viewMatrix", this->modelMatrix());
}
