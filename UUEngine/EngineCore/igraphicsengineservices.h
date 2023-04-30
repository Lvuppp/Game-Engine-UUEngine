#ifndef IGRAPHICSENGINESERVICES_H
#define IGRAPHICSENGINESERVICES_H

#include "base3dgameobject.h"
#include "camera.h"

class IGraphicsEngineServices
{
public:
    IGraphicsEngineServices();
    IGraphicsEngineServices(QOpenGLFunctions *functions);
    virtual ~IGraphicsEngineServices(){};

    virtual void processModel(Base3DGameObject *, QOpenGLShaderProgram *) = 0;
    virtual void processCamera(Camera *, QOpenGLShaderProgram *shaderProgram) = 0;
protected:
    QOpenGLFunctions *m_functions;
};

#endif // IGRAPHICSENGINESERVICES_H
