#include "baseengineobject.h"

BaseEngineObject::BaseEngineObject()
{
    m_coordinates = QVector3D(0.0f, 0.0f, 0.0f);
    m_rotate *= QQuaternion();
    m_scale = 1.0f;
    m_lock = false;


    m_modelMatrix.setToIdentity();

    m_modelMatrix.translate(m_coordinates);
    m_modelMatrix.rotate(m_rotate);
    m_modelMatrix.scale(m_scale);
}

BaseEngineObject::~BaseEngineObject()
{
}

bool BaseEngineObject::isLocked()
{
    return m_lock;
}

float BaseEngineObject::scale() const
{
    return m_scale;
}

QVector3D BaseEngineObject::coordinates() const
{
    return m_coordinates;
}

QQuaternion BaseEngineObject::rotation() const
{
    return m_rotate;
}

void BaseEngineObject::setScale(const float &scale)
{
    if(m_lock) return;
    m_scale = scale;
}

void BaseEngineObject::setRotation(const QQuaternion &rotation)
{
    if(m_lock) return;
    m_rotate = rotation;
}

void BaseEngineObject::setCoordinates(const QVector3D &coordinates)
{
    if(m_lock) return;
    m_coordinates = coordinates;
}

void BaseEngineObject::translate(const QVector3D &translation)
{
    if(m_lock) return;
    m_coordinates += translation;
}

void BaseEngineObject::rotate(const QQuaternion &rotation)
{
    if(m_lock) return;
    m_rotate = m_rotate * rotation;
}

void BaseEngineObject::scale(const float &scale)
{
    if(m_lock) return;
    m_scale += scale;
}

void BaseEngineObject::lock()
{
    m_lock = true;
}

void BaseEngineObject::unlock()
{
    m_lock = false;
}

QMatrix4x4 BaseEngineObject::modelMatrix()
{
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();

    modelMatrix.translate(m_coordinates);
    modelMatrix.rotate(m_rotate);
    modelMatrix.scale(m_scale);

    return modelMatrix;
}
