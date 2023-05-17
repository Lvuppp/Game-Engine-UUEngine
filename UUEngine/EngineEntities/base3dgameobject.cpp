#include "base3dgameobject.h"

Base3DGameObject::Base3DGameObject():
    BaseEngineObject()
{
}

Base3DGameObject::Base3DGameObject(ModelType modelType, QVector<Model *>models, QString modelPath):
    BaseEngineObject()
{
    setModel(modelType, models, modelPath);
}

Base3DGameObject::Base3DGameObject(ModelType modelType, Model *models, QString modelPath):
    BaseEngineObject()
{
    setModel(modelType, models, modelPath);
}
Base3DGameObject::~Base3DGameObject()
{
    for(auto model : m_modelParticulars){
        delete model;
    }
}

void Base3DGameObject::addScript(QString script)
{
    m_scriptsName.append(script);
}

QVector<QString> Base3DGameObject::scripts()
{
    return m_scriptsName;
}

QVector<Model *> Base3DGameObject::model()
{
    return m_modelParticulars;
}

QString Base3DGameObject::modelPath()
{
    return m_modelPath;
}

ModelType Base3DGameObject::modelType()
{
    return m_modelType;
}

void Base3DGameObject::setModel(ModelType modelType, QVector<Model *>models, QString modelPath)
{
    m_modelParticulars.append(models);
    m_modelPath = modelPath;
    m_modelType = modelType;
}

void Base3DGameObject::setModel(ModelType modelType, Model *models, QString modelPath)
{
    m_modelParticulars.append(models);
    m_modelPath = modelPath;
    m_modelType = modelType;
}

void Base3DGameObject::draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions)
{
    QMatrix4x4 modelMatrix = this->modelMatrix();

    for(auto particulars : m_modelParticulars){
        particulars->drawModel(modelMatrix, shaderProgram, functions);
    }

}
