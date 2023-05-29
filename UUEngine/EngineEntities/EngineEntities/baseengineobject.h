#ifndef BASEENGINEOBJECT_H
#define BASEENGINEOBJECT_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QtOpenGL>

class BaseEngineObject
{
public:
    BaseEngineObject();
    virtual ~BaseEngineObject();

    bool isLocked();
    void lock();
    void unlock();

    //получение текущих
    float scale() const;
    QVector3D coordinates() const;
    QQuaternion rotationX() const;
    QQuaternion rotationY() const;
    QQuaternion rotation() const;
    QMatrix4x4 modelMatrix();

    void setCoordinates(const QVector3D &coordinates);
    void setRotateX(const QQuaternion &rotation);
    void setRotateY(const QQuaternion &rotation);
    void setScale(const float &scale);

    //изменение относительно текущих
    void translate(const QVector3D &coordinates);
    void rotate(const QQuaternion &rotation);
    void rotateX(const QQuaternion &rotation);
    void rotateY(const QQuaternion &rotation);
    void scale(const float &scale);

    virtual void draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions, bool isUsingTexture = true) = 0;

private:
    QMatrix4x4 m_modelMatrix;
    QVector3D m_coordinates;
    QQuaternion m_rotate;
    QQuaternion m_rotateX;
    QQuaternion m_rotateY;
    float m_scale;
    bool m_lock;
};

#endif // BASEENGINEOBJECT_H
