#ifndef MODELPROCESSOR_H
#define MODELPROCESSOR_H

#include "base3dgameobject.h"

#include<QOpenGLShaderProgram>

class ModelProcessor
{
public:
    ModelProcessor(){};
    ModelProcessor(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *function);

    void processModel(Base3DGameObject *object);

private:
    QOpenGLShaderProgram *m_shaderProgram;
    QOpenGLFunctions *m_functions;
};

#endif // MODELPROCESSOR_H
