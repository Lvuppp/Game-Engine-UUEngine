#include "Base3DGameObject.h"
#include "Entities/Models/Model.h"

cBase3DGameObject::cBase3DGameObject(cModel* model)
    : cBaseEngineObject()
    , m_model(model)
{
}

cModel* cBase3DGameObject::model()
{
    return m_model.get();
}

void cBase3DGameObject::setModel(cModel* model)
{
    m_model.reset(model);
}

void cBase3DGameObject::draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions, bool isUsingTexture)
{
    m_model->drawModel(this->modelMatrix(), shaderProgram, isUsingTexture, functions);
}
