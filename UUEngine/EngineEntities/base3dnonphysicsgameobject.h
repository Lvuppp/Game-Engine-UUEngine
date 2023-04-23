#ifndef BASE3DNONPHYSICSGAMEOBJECT_H
#define BASE3DNONPHYSICSGAMEOBJECT_H

#include "baseengineobject.h"
#include "vertexdata.h"

#include <QImage>

class Base3DNonPhysicsGameObject : public BaseEngineObject
{
public:
    Base3DNonPhysicsGameObject(
        QVector3D coordinates= QVector3D(0.0f, 0.0f, 0.0f),
        QQuaternion rotation = QQuaternion(0.0f, 0.0f, 0.0f, 0.0f),
        float scale = 1.0f,
        bool isObjectLocked = false);

    void update() override;

protected:
    QImage texture;
    QVector<VertexData> vertexes;
};

#endif // BASE3DNONPHYSICSGAMEOBJECT_H
