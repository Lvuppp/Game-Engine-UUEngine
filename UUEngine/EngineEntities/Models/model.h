#ifndef MODEL_H
#define MODEL_H

#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>


enum class ModelType{
    SimpleModel,
    CustomModel
};

class Model
{
public:
    Model();
    virtual ~Model();

    virtual void drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, bool isUsingTexture, QOpenGLFunctions *functions) = 0;

    ModelType modelType();

protected:
    ModelType p_modelType;

};

#endif // MODEL_H
