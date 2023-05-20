#ifndef SIMPLEMODEL_H
#define SIMPLEMODEL_H

#include "model.h"
#include "modelparticle.h"

class SimpleModel : public Model
{
public:
    SimpleModel();
    SimpleModel(ModelParticle *modelParticle);
    ~SimpleModel();

    void drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions) override;
    void setModel(ModelParticle *modelParticle);
    ModelParticle *modelParticle();

private:
    ModelParticle *m_modelParticle;

};


#endif // SIMPLEMODEL_H
