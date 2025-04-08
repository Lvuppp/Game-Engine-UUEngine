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

void cModel::setNormalMap(std::string_view path)
{
    for (const auto& model : m_modelParticles)
    {
        model->setNormalMap(path);
    }
}

void cModel::setDiffuseMap(std::string_view path)
{
    for (const auto& model : m_modelParticles)
    {
        model->setDiffuseMap(path);
    }
}

void cModel::setNormalMap(std::string_view path, size_t index)
{
    ASSERT(index < m_modelParticles.size(), "Index out of range");
    m_modelParticles[index]->setNormalMap(path);
}

void cModel::setDiffuseMap(std::string_view path, size_t index)
{
    ASSERT(index < m_modelParticles.size(), "Index out of range");
    m_modelParticles[index]->setDiffuseMap(path);
}
