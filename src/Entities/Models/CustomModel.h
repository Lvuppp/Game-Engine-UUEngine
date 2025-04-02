#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H

#include "ModelParticle.h"
#include "Model.h"

#include <QtOpenGL>


class cCustomModel : public cModel
{
public:
    cCustomModel();
    cCustomModel(QVector<cModelParticle *> modelParticles);
    ~cCustomModel();

    void drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, bool isUsingTexture, QOpenGLFunctions *functions) override;

    void setModel(QVector<cModelParticle *> modelParticles);
    cModelParticle *modelParticle(const int &index);
    QVector<cModelParticle *> allModelParticle();

private:
    QVector<cModelParticle *> m_modelParticles;
};

#endif // CUSTOMMODEL_H
