#ifndef BASEENGINEOBJECT_H
#define BASEENGINEOBJECT_H

#include <QtOpenGL>
#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>

class BaseEngineObject
{
public:
    BaseEngineObject(QVector3D coordinates, QQuaternion rotation, float scale, bool isObjectLocked);

    ~BaseEngineObject();

    bool isLocked();
    bool isModified();
    void lock();
    void unlock();

    //получение текущих
    float scale() const;
    QVector3D coordinates() const;
    QQuaternion rotation() const;
    QMatrix4x4 modelMatrix() const;

    //задание текущих
    void setScale(const float &scale);
    void setRotation(const QQuaternion &rotation);
    void setCoordinates(const QVector3D &coordinates);

    //изменение относительно текущих
    void translate(const QVector3D &coordinates);
    void rotate(const QQuaternion &rotatio);
    void scale(const float &scale);

private:
    QVector3D coordinatesParam;
    QQuaternion rotateParam;
    float scaleParam;
    bool lockStatment;
    bool modifiedStatement;

};

#endif // BASEENGINEOBJECT_H
