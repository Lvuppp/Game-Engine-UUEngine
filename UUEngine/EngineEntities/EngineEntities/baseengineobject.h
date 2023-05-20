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
    QQuaternion rotation() const;
    QMatrix4x4 modelMatrix();

    //задание текущих5
    void setModelMatrix(const QMatrix4x4 &modelMatrix);

    //изменение относительно текущих
    void translate(const QVector3D &coordinates);
    void rotate(const QQuaternion &rotation);
    void scale(const float &scale);

    virtual void draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions) = 0;

private:
    QMatrix4x4 m_modelMatrix;
    QVector3D m_coordinates;
    QQuaternion m_rotate;
    float m_scale;
    bool m_lock;
};

#endif // BASEENGINEOBJECT_H
