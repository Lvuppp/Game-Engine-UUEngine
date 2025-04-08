#ifndef MODEL_H
#define MODEL_H

class QOpenGLFunctions;
class QOpenGLShaderProgram;

#include "ModelParticle.h"

#include <QMatrix4x4>

class cModel
{
public:
    cModel() = default;
    virtual ~cModel() = default;

    using ModelParticle = std::shared_ptr<cModelParticle>;
    using ModelParticles = std::vector<ModelParticle>;
    cModel(ModelParticle modelParticles);
    cModel(ModelParticles modelParticles);

    void setModel(ModelParticles& modelParticles);

    ModelParticle getModelParticle(size_t index) const;
    ModelParticles getModelParticles() const;

    void setNormalMap(std::string_view path);
    void setDiffuseMap(std::string_view path);

    inline void setNormalMap(std::string_view path, size_t index);
    inline void setDiffuseMap(std::string_view path, size_t index);

public:
    virtual void drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram* shaderProgram, bool isUsingTexture, QOpenGLFunctions* functions);

private:
    ModelParticles m_modelParticles;
};

#endif // MODEL_H
