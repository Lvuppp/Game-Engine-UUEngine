#include "Base3DGameObject.h"
#include "Models/Model.h"

cBase3DGameObject::cBase3DGameObject(cModel *model) : cBaseEngineObject()
{
    m_model = model;
    m_objectType = ObjectType::GameObject;

}

cBase3DGameObject::~cBase3DGameObject()
{
    if(m_model != nullptr)
        delete m_model;
}

cModel *cBase3DGameObject::model()
{
    return m_model;
}

void cBase3DGameObject::setModel(cModel *model)
{
    if(m_model != nullptr)
        delete m_model;

    m_model = model;
}

void cBase3DGameObject::draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions, bool isUsingTexture)
{
    m_model->drawModel(this->modelMatrix(), shaderProgram, isUsingTexture, functions);
}
