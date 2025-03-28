#include "custommodel.h"

CustomModel::CustomModel() :Model(ModelType::CustomModel)
{

}

CustomModel::CustomModel(QVector<ModelParticle *> modelParticles) : Model(ModelType::CustomModel)
{
    m_modelParticles.append(modelParticles);
    p_modelType = ModelType::CustomModel;
}

CustomModel::~CustomModel()
{
//    for(auto it = m_modelParticles.begin(), end = m_modelParticles.end(); it != end; it++ ){
//        delete it;
//    }

    m_modelParticles.clear();

}


void CustomModel::drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, bool isUsingTexture, QOpenGLFunctions *functions)
{
    foreach(auto model, m_modelParticles){
        model->drawModelParticle(modelMatrix, shaderProgram, isUsingTexture, functions);
    }
}

void CustomModel::setModel(QVector<ModelParticle *> modelParticles)
{
    for(auto it = m_modelParticles.begin(), end = m_modelParticles.end(); it != end; it++ ){
        delete *it;
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
