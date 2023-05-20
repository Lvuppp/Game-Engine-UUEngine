#include "custommodel.h"

CustomModel::CustomModel() :Model()
{

}

CustomModel::CustomModel(QVector<ModelParticle *> modelParticles) : Model()
{
    m_modelParticles.append(modelParticles);
    p_modelType = ModelType::CustomModel;
}

CustomModel::~CustomModel()
{
    for(auto it = m_modelParticles.begin(), end = m_modelParticles.end(); it != end; it++ ){
        delete it;
    }

    m_modelParticles.clear();

}


void CustomModel::drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions)
{
    foreach(auto model, m_modelParticles){
        model->drawModelParticle(modelMatrix, shaderProgram, functions);
    }
}

void CustomModel::setModel(QVector<ModelParticle *> modelParticles)
{
    for(auto it = m_modelParticles.begin(), end = m_modelParticles.end(); it != end; it++ ){
        delete it;
    }

    m_modelParticles.clear();
    m_modelParticles.append(modelParticles);
}

ModelParticle *CustomModel::modelParticle(const int &index)
{
    return m_modelParticles.at(index);
}

QVector<ModelParticle *> CustomModel::allModelParticle()
{
    return m_modelParticles;
}
