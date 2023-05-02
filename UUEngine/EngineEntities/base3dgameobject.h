#ifndef BASE3DGAMEOBJECT_H
#define BASE3DGAMEOBJECT_H

#include "baseengineobject.h"
#include "model.h"

#include <QImage>

class Base3DGameObject : public BaseEngineObject
{
public:
    Base3DGameObject(
        const QVector3D &coordinates = QVector3D(0.0f, 0.0f, 0.0f),
        const QQuaternion &rotation = QQuaternion(),
        const float &scale = 1.0f,
        const bool &isObjectLocked = false);

    Base3DGameObject(
        QVector<Model*> models,
        const QVector3D &coordinates = QVector3D(0.0f, 0.0f, 0.0f),
        const QQuaternion &rotation = QQuaternion(),
        const float &scale = 1.0f,
        const bool &isObjectLocked = false);

    ~Base3DGameObject();

    void setModel(QVector<Model *>models) override;
    void setModel(Model *models) override;
    void draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions) override;

protected:
    QVector<Model *> m_modelParticulars;

};
#endif // BASE3DGAMEOBJECT_H
