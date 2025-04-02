#include "CustomModel.h"

cCustomModel::cCustomModel() : cModel(ModelType::CustomModel)
{

}

cCustomModel::cCustomModel(QVector<cModelParticle *> modelParticles) : cModel(ModelType::CustomModel)
{
    m_modelParticles.append(modelParticles);
    p_modelType = ModelType::CustomModel;
}

cCustomModel::~cCustomModel()
{
//    for(auto it = m_modelParticles.begin(), end = m_modelParticles.end(); it != end; it++ ){
//        delete it;
//    }

    m_modelParticles.clear();

}


void cCustomModel::drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, bool isUsingTexture, QOpenGLFunctions *functions)
{
    foreach(auto model, m_modelParticles){
        model->drawModelParticle(modelMatrix, shaderProgram, isUsingTexture, functions);
    }
}

void cCustomModel::setModel(QVector<cModelParticle *> modelParticles)
{
    for(auto it = m_modelParticles.begin(), end = m_modelParticles.end(); it != end; it++ ){
        delete *it;
    }

    m_modelParticles.clear();
    m_modelParticles.append(modelParticles);
}

cModelParticle *cCustomModel::modelParticle(const int &index)
{   
    return m_modelParticles.at(index);
}

QVector<cModelParticle *> cCustomModel::allModelParticle()
{
    return m_modelParticles;
}
