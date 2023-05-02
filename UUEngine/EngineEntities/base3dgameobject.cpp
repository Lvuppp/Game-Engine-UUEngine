#include "base3dgameobject.h"

Base3DGameObject::Base3DGameObject(const QVector3D &coordinates, const QQuaternion &rotation,
                                   const float &scale, const bool &isObjectLocked):
    BaseEngineObject(coordinates, rotation, scale, isObjectLocked)
{
}

Base3DGameObject::Base3DGameObject(QVector<Model *> models, const QVector3D &coordinates,
                                   const QQuaternion &rotation, const float &scale, const bool &isObjectLocked):
    BaseEngineObject(coordinates, rotation, scale, isObjectLocked)
{
    m_modelParticulars.append(models);
}

Base3DGameObject::~Base3DGameObject()
{
    for(auto model : m_modelParticulars){
        delete model;
    }
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
