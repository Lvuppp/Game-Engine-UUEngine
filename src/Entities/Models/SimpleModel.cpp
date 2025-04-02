#include "SimpleModel.h"

#include "Models/ModelParticle.h"

cSimpleModel::cSimpleModel()
    : cModel(ModelType::SimpleModel)
{
}

cSimpleModel::cSimpleModel(cModelParticle* modelParticle)
    : cModel(ModelType::SimpleModel)
    , m_modelParticle(modelParticle)
{
}

void cSimpleModel::drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, bool isUsingTexture, QOpenGLFunctions *functions)
{
    m_modelParticle->drawModelParticle(modelMatrix, shaderProgram, isUsingTexture, functions);
}

void cSimpleModel::setModel(cModelParticle * modelParticles)
{
    m_modelParticle.reset(modelParticles);
}

cModelParticle *cSimpleModel::modelParticle()
{
    return m_modelParticle.get();
}
