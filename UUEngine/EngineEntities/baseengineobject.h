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
    virtual void update();

    //получение текущих
    float getScale();
    QVector3D getCoordinates();
    QQuaternion getRotation();
    QMatrix4x4 getProjectinMatrix();

    //задание текущих
    void setScale(float scale);
    void setRotation(QQuaternion rotation);
    void setCoordinates(QVector3D coordinates);

    //изменение относительно текущих
    void translate(QVector3D translation);
    void rotate(QQuaternion rotation);
    void scale(float scale);

private:
    void changeProjectionMatrix();

private:
    QMatrix4x4 objectProjectionMatrix;
    QVector3D coordinatesParam;
    QQuaternion rotateParam;
    float scaleParam;
    bool lockStatment;
    bool modifiedStatement;

};

#endif // BASEENGINEOBJECT_H
