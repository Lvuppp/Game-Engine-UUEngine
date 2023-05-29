#include "simplemodel.h"

SimpleModel::SimpleModel() : Model()
{

}

SimpleModel::SimpleModel(ModelParticle *modelParticle) : Model(), m_modelParticle(modelParticle)
{
    p_modelType = ModelType::SimpleModel;
}

SimpleModel::~SimpleModel()
{
    delete m_modelParticle;
}

void SimpleModel::drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, bool isUsingTexture, QOpenGLFunctions *functions)
{
    m_modelParticle->drawModelParticle(modelMatrix, shaderProgram, isUsingTexture, functions);
}

void SimpleModel::setModel(ModelParticle * modelParticles)
{
    delete m_modelParticle;
    m_modelParticle = modelParticles;
}

ModelParticle *SimpleModel::modelParticle()
{
    return m_modelParticle;
}
