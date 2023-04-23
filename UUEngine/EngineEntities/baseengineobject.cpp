#include "baseengineobject.h"

BaseEngineObject::BaseEngineObject(QVector3D coordinates, QQuaternion rotation, float scale, bool isObjectLocked):
    coordinatesParam(coordinates), rotateParam(rotation), scaleParam(scale), lockStatment(isObjectLocked)
{

}

BaseEngineObject::~BaseEngineObject()
{

}


bool BaseEngineObject::isLocked()
{
    return lockStatment;
}

bool BaseEngineObject::isModified()
{
    return modifiedStatement;
}

float BaseEngineObject::getScale()
{
    return scaleParam;
}

QVector3D BaseEngineObject::getCoordinates()
{
    return coordinatesParam;
}

QQuaternion BaseEngineObject::getRotation()
{
    return rotateParam;
}

void BaseEngineObject::setScale(float scale)
{
    if(lockStatment) return;
    scaleParam = scale;
}

void BaseEngineObject::setRotation(QQuaternion rotation)
{
    if(lockStatment) return;
    rotateParam = rotation;
}

void BaseEngineObject::setCoordinates(QVector3D coordinates)
{
    if(lockStatment) return;
    coordinatesParam = coordinates;
}

void BaseEngineObject::translate(QVector3D translation)
{
    if(lockStatment) return;
    coordinatesParam += translation;
}

void BaseEngineObject::rotate(QQuaternion rotation)
{
    if(lockStatment) return;
    rotateParam += rotation;
}

void BaseEngineObject::scale(float scale)
{
    if(lockStatment) return;
    scaleParam += scale;
}

void BaseEngineObject::lock()
{
    lockStatment = true;
}

void BaseEngineObject::unlock()
{
    lockStatment = false;
}

void BaseEngineObject::changeProjectionMatrix()
{
    objectProjectionMatrix.setToIdentity();

    objectProjectionMatrix.translate(coordinatesParam);
    objectProjectionMatrix.rotate(rotateParam);
    objectProjectionMatrix.scale(scaleParam);
}
