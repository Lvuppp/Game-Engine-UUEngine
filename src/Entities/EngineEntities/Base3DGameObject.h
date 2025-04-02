#ifndef BASE3DGAMEOBJECT_H
#define BASE3DGAMEOBJECT_H

#include "BaseEngineObject.h"

// Forward declaration
class cModel;
class QOpenGLShaderProgram;
class QOpenGLFunctions;

class cBase3DGameObject : public cBaseEngineObject
{
public:
    cBase3DGameObject(cModel *model);
    virtual ~cBase3DGameObject();
    
    cModel *model();
    void setModel(cModel *model);
    
    virtual void draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions, bool isUsingTexture = true) override;
    
private:
    cModel *m_model;
};

#endif // BASE3DGAMEOBJECT_H
