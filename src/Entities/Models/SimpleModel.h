#ifndef SIMPLEMODEL_H
#define SIMPLEMODEL_H

class cModelParticle;

#include "Model.h"

class cSimpleModel : public cModel
{
public:
    cSimpleModel();
    cSimpleModel(cModelParticle* modelParticle);

    void setModel(cModelParticle *modelParticle);
    cModelParticle* modelParticle();

public:
    void drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, bool isUsingTexture, QOpenGLFunctions *functions) override;

protected:
    std::unique_ptr<cModelParticle> m_modelParticle;
};


#endif // SIMPLEMODEL_H
