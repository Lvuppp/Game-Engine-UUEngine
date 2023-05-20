#include "base3dgameobject.h"


Base3DGameObject::Base3DGameObject(Model *model) : BaseEngineObject()
{
    m_model = model;
}

Base3DGameObject::~Base3DGameObject()
{
    delete m_model;
}

Model *Base3DGameObject::model()
{
    return m_model;
}

void Base3DGameObject::setModel(Model * model)
{
    m_model = model;
}

void Base3DGameObject::draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions)
{
    m_model->drawModel(this->modelMatrix(), shaderProgram, functions);
}
