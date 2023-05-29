#ifndef BASE3DGAMEOBJECT_H
#define BASE3DGAMEOBJECT_H

#include "baseengineobject.h"
#include "Models/model.h"

#include <QImage>
#include <QVector3D>

// надо отвязать от этого модель и скрипты, сделать так чтобы модель была независима от объекта и скрипты.
// скрипты более менее понятно(сделать скрипт фолдер туда объекты к скриптам подвязывать, или хотябы название,
// по которым уже можно будет найти и скрипт и объект
class Base3DGameObject : public BaseEngineObject
{
public:
    Base3DGameObject(Model *model);

    ~Base3DGameObject();
    
    Model *model() ;
    void setModel(Model* model);

    void draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions, bool isUsingTexture = true) override;

private:
    Model *m_model;
};
#endif // BASE3DGAMEOBJECT_H
