#ifndef MODEL_H
#define MODEL_H

class QOpenGLFunctions;
class QOpenGLShaderProgram;

#include <QMatrix4x4>

class cModel
{
public:
    enum class ModelType
    {
        SimpleModel,
        CustomModel,

        Unknown
    };

    cModel(ModelType type);

    ModelType modelType();

public:
    virtual ~cModel() = default;
    virtual void drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram* shaderProgram, bool isUsingTexture, QOpenGLFunctions* functions) = 0;

protected:
    ModelType p_modelType = ModelType::Unknown;
};

#endif // MODEL_H
