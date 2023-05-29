#include "baseengineobject.h"

BaseEngineObject::BaseEngineObject()
{
    m_coordinates = QVector3D(0.0f, 0.0f, 0.0f);
    m_rotate *= QQuaternion();
    m_scale = 1.0f;
    m_lock = false;
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

QQuaternion BaseEngineObject::rotationX() const
{
    return m_rotateY;
}

QQuaternion BaseEngineObject::rotationY() const
{
    return m_rotateY;
}

QQuaternion BaseEngineObject::rotation() const
{
    return m_rotate;
}

void BaseEngineObject::translate(const QVector3D &translation)
{
    m_coordinates += translation;
}

void BaseEngineObject::rotate(const QQuaternion &rotation)
{
    m_rotate *= rotation;
}

void BaseEngineObject::rotateX(const QQuaternion &rotation)
{
    m_rotateX = rotation * m_rotateX;
    m_rotate = m_rotateX * m_rotateY;
}

void BaseEngineObject::rotateY(const QQuaternion &rotation)
{
    m_rotateY = rotation * m_rotateY;
    m_rotate = m_rotateX * m_rotateY;
}

void BaseEngineObject::scale(const float &scale)
{
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

void BaseEngineObject::setCoordinates(const QVector3D &coordinates)
{
    m_coordinates = coordinates;
}

void BaseEngineObject::setScale(const float &scale)
{
    m_scale = scale;
}
