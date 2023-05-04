#include "base3dgameobject.h"

Base3DGameObject::Base3DGameObject():
    BaseEngineObject()
{
}

Base3DGameObject::Base3DGameObject(Model *model)
{
    setModel(model);
}

Base3DGameObject::Base3DGameObject(QVector<Model *> models):
    BaseEngineObject()
{
    setModel(models);
}

Base3DGameObject::~Base3DGameObject()
{
    for(auto model : m_modelParticulars){
        delete model;
    }
}

QVector<Model *> Base3DGameObject::model()
{
    return m_modelParticulars;
}

void Base3DGameObject::setModel(QVector<Model *>models)
{
    m_modelParticulars.append(models);
}

void Base3DGameObject::setModel(Model *models)
{
    m_modelParticulars.append(models);
}

void Base3DGameObject::draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions)
{
    QMatrix4x4 modelMatrix = this->modelMatrix();

    for(auto particulars : m_modelParticulars){
        particulars->drawModel(modelMatrix, shaderProgram, functions);
    }

}
