#include "Camera.h"

cCamera::cCamera() :
    cBaseEngineObject()
{
    m_objectType = ObjectType::Camera;
}

cCamera::~cCamera()
{


}
void cCamera::draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions, bool isUsingTexture)
{
    shaderProgram->setUniformValue("u_viewMatrix", this->modelMatrix());
}
