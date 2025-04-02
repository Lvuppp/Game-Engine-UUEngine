#include "BaseEngineObject.h"

cBaseEngineObject::cBaseEngineObject()
{
    m_coordinates = QVector3D(0.0f, 0.0f, 0.0f);
    m_rotate *= QQuaternion();
    m_scale = 1.0f;
    m_lock = false;
}

cBaseEngineObject::~cBaseEngineObject()
{
}

bool cBaseEngineObject::isLocked() const
{
    return m_lock;
}

float cBaseEngineObject::scale() const
{
    return m_scale;
}

QVector3D cBaseEngineObject::coordinates() const
{
    return m_coordinates;
}

QQuaternion cBaseEngineObject::rotationX() const
{
    return m_rotateY;
}

QQuaternion cBaseEngineObject::rotationY() const
{
    return m_rotateY;
}

QQuaternion cBaseEngineObject::rotation() const
{
    return m_rotate;
}

void cBaseEngineObject::translate(const QVector3D &translation)
{
    m_coordinates += translation;
}

void cBaseEngineObject::rotate(const QQuaternion &rotation)
{
    m_rotate *= rotation;
}

void cBaseEngineObject::rotateX(const QQuaternion &rotation)
{
    m_rotateX = rotation * m_rotateX;
    m_rotate = m_rotateX * m_rotateY;
}

void cBaseEngineObject::rotateY(const QQuaternion &rotation)
{
    m_rotateY = rotation * m_rotateY;
    m_rotate = m_rotateX * m_rotateY;
}

void cBaseEngineObject::scale(float scale)
{
    m_scale += scale;
}

void cBaseEngineObject::lock()
{
    m_lock = true;
}

void cBaseEngineObject::unlock()
{
    m_lock = false;
}

QMatrix4x4 cBaseEngineObject::modelMatrix() const
{
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();

    modelMatrix.translate(m_coordinates);
    modelMatrix.rotate(m_rotate);
    modelMatrix.scale(m_scale);

    return modelMatrix;
}

ObjectType cBaseEngineObject::objectType() const
{
    return m_objectType;
}

void cBaseEngineObject::setCoordinates(const QVector3D &coordinates)
{
    m_coordinates = coordinates;
}

void cBaseEngineObject::setScale(float scale)
{
    m_scale = scale;
}
