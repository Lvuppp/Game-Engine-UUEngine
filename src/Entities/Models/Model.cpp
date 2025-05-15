#include "Model.h"
#include "Utils/Assert.h"

cModel::cModel(ModelParticle modelParticles)
{
    m_modelParticles.push_back(modelParticles);
}

cModel::cModel(ModelParticles modelParticles)
    : m_modelParticles(modelParticles)
{
}

cModel::ModelParticle cModel::getModelParticle(size_t index) const
{
    ASSERT(index < m_modelParticles.size(), "Index out of range");
    return m_modelParticles[index];
}

cModel::ModelParticles cModel::getModelParticles() const
{
    return m_modelParticles;
}

void cModel::drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, bool isUsingTexture, QOpenGLFunctions *functions)
{
    for (const auto& model : m_modelParticles)
    {
        model->drawModelParticle(modelMatrix, shaderProgram, isUsingTexture, functions);
    }
}

void cModel::setNormalMap(QOpenGLTexture* texture)
{
    for (const auto& model : m_modelParticles)
    {
        model->setNormalMap(texture);
    }
}

void cModel::setDiffuseMap(QOpenGLTexture* texture)
{
    for (const auto& model : m_modelParticles)
    {
        model->setDiffuseMap(texture);
    }
}

void cModel::setNormalMap(QOpenGLTexture* texture, size_t index)
{
    ASSERT(index < m_modelParticles.size(), "Index out of range");
    m_modelParticles[index]->setNormalMap(texture);
}

void cModel::setDiffuseMap(QOpenGLTexture* texture, size_t index)
{
    ASSERT(index < m_modelParticles.size(), "Index out of range");
    m_modelParticles[index]->setDiffuseMap(texture);
}
