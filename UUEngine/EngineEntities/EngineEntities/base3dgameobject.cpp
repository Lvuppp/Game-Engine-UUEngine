#include "base3dgameobject.h"


Base3DGameObject::Base3DGameObject(Model *model) : BaseEngineObject()
{
    m_model = model;
    m_objectType = ObjectType::GameObject;

}

Base3DGameObject::~Base3DGameObject()
{
    if(m_model != nullptr)
        delete m_model;
}

Model *Base3DGameObject::model()
{
    return m_model;
}

void Base3DGameObject::setModel(Model * model)
{
    if(m_model != nullptr)
        delete m_model;

    m_model = model;
}

void Base3DGameObject::draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions,bool isUsingTexture)
{
    m_model->drawModel(this->modelMatrix(), shaderProgram, isUsingTexture,functions);
}
