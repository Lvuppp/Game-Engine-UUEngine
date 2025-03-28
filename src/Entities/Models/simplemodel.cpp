#include "simplemodel.h"

#include "Models/modelparticle.h"

SimpleModel::SimpleModel()
    : Model(ModelType::SimpleModel)
{
}

SimpleModel::SimpleModel(ModelParticle* modelParticle)
    : Model(ModelType::SimpleModel)
    , m_modelParticle(modelParticle)
{
}

void SimpleModel::drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, bool isUsingTexture, QOpenGLFunctions *functions)
{
    m_modelParticle->drawModelParticle(modelMatrix, shaderProgram, isUsingTexture, functions);
}

void SimpleModel::setModel(ModelParticle * modelParticles)
{
    m_modelParticle.reset(modelParticles);
}

ModelParticle *SimpleModel::modelParticle()
{
    return m_modelParticle.get();
}
