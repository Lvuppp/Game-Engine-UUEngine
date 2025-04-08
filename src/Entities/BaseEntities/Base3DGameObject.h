#ifndef BASE3DGAMEOBJECT_H
#define BASE3DGAMEOBJECT_H

#include "Entities/BaseEntities/BaseEngineObject.h"
#include "Entities/Models/Model.h"

class QOpenGLShaderProgram;
class QOpenGLFunctions;

class cBase3DGameObject : public cBaseEngineObject
{
public:
    cBase3DGameObject(cModel* model);

    cModel* model();
    void setModel(cModel* model);

    virtual void draw(QOpenGLShaderProgram* shaderProgram, QOpenGLFunctions* functions, bool isUsingTexture) override;

private:
    std::unique_ptr<cModel> m_model;
};

#endif // BASE3DGAMEOBJECT_H
