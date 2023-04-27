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

float BaseEngineObject::scale() const
{
    return scaleParam;
}

QVector3D BaseEngineObject::coordinates() const
{
    return coordinatesParam;
}

QQuaternion BaseEngineObject::rotation() const
{
    return rotateParam;
}

void BaseEngineObject::setScale(const float &scale)
{
    if(lockStatment) return;
    scaleParam = scale;
}

void BaseEngineObject::setRotation(const QQuaternion &rotation)
{
    if(lockStatment) return;
    rotateParam = rotation;
}

void BaseEngineObject::setCoordinates(const QVector3D &coordinates)
{
    if(lockStatment) return;
    coordinatesParam = coordinates;
}

void BaseEngineObject::translate(const QVector3D &translation)
{
    if(lockStatment) return;
    coordinatesParam += translation;
}

void BaseEngineObject::rotate(const QQuaternion &rotation)
{
    if(lockStatment) return;
    rotateParam += rotation;
}

void BaseEngineObject::scale(const float &scale)
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

QMatrix4x4 BaseEngineObject::modelMatrix() const
{
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();

    modelMatrix.translate(coordinatesParam);
    modelMatrix.rotate(rotateParam);
    modelMatrix.scale(scaleParam);

    return modelMatrix;
}
