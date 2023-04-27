#ifndef MODELPROCESSOR_H
#define MODELPROCESSOR_H

#include<QOpenGLShaderProgram>

class ModelProcessor
{
public:
    ModelProcessor(QOpenGLShaderProgram *shaderProgram);

    void processModel();

private:
    QOpenGLShaderProgram *m_shaderProgram;
};

#endif // MODELPROCESSOR_H
