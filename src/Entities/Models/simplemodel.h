#ifndef SIMPLEMODEL_H
#define SIMPLEMODEL_H

class ModelParticle;

#include "model.h"

class SimpleModel : public Model
{
public:
    SimpleModel();
    SimpleModel(ModelParticle* modelParticle);

    void setModel(ModelParticle *modelParticle);
    ModelParticle* modelParticle();

public:
    void drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, bool isUsingTexture, QOpenGLFunctions *functions) override;

protected:
    std::unique_ptr<ModelParticle> m_modelParticle;
};


#endif // SIMPLEMODEL_H
