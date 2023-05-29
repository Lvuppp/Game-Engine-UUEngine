#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H

#include "modelparticle.h"
#include "model.h"

#include <QtOpenGL>



class CustomModel : public Model
{
public:
    CustomModel();
    CustomModel(QVector<ModelParticle *> modelParticles);
    ~CustomModel();

    void drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, bool isUsingTexture, QOpenGLFunctions *functions) override;

    void setModel(QVector<ModelParticle *> modelParticles);
    ModelParticle *modelParticle(const int &index);
    QVector<ModelParticle *> allModelParticle();

private:
    QVector<ModelParticle *> m_modelParticles;
};

#endif // CUSTOMMODEL_H
