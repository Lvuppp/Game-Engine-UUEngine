#ifndef GRAPHICSENGINESERVICES_H
#define GRAPHICSENGINESERVICES_H

#include "igraphicsengineservices.h"


class GraphicsEngineServices : public IGraphicsEngineServices
{
public:
    GraphicsEngineServices();
    GraphicsEngineServices(QOpenGLFunctions *functions);

    ~GraphicsEngineServices();

    void processModel(Base3DGameObject *object, QOpenGLShaderProgram *shaderProgram) override;
    void processCamera(Camera *camera, QOpenGLShaderProgram *shaderProgram) override;

};

#endif // GRAPHICSENGINESERVICES_H
