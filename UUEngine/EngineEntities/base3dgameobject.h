#ifndef BASE3DGAMEOBJECT_H
#define BASE3DGAMEOBJECT_H

#include "baseengineobject.h"
#include "model.h"

#include <QImage>
#include <QVector3D>

class Base3DGameObject : public BaseEngineObject
{
public:
    Base3DGameObject();
    Base3DGameObject(Model *model);
    Base3DGameObject(QVector<Model*> models);

    ~Base3DGameObject();

    QVector<Model *> model();
    void setModel(QVector<Model *> models);
    void setModel(Model *models);

    void draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions) override;

protected:
    QVector<Model *> m_modelParticulars;
};
#endif // BASE3DGAMEOBJECT_H
