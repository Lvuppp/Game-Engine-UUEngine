#include "base3dnonphysicsgameobject.h"


Base3DNonPhysicsGameObject::Base3DNonPhysicsGameObject(QVector3D coordinates, QQuaternion rotation, float scale, bool isObjectLocked) :
    BaseEngineObject(coordinates, rotation, scale, isObjectLocked)
{

}

void Base3DNonPhysicsGameObject::update()
{

}
