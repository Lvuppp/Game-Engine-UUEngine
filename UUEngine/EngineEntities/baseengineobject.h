#ifndef BASEENGINEOBJECT_H
#define BASEENGINEOBJECT_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>

class BaseEngineObject
{
public:
    BaseEngineObject(
        QVector3D coordinates= QVector3D(0.0f, 0.0f, 0.0f),
        QQuaternion rotation = QQuaternion(0.0f, 0.0f, 0.0f, 0.0f),
        float scale = 1.0f);

    ~BaseEngineObject();

    //получение текущих
    float getScale();
    QVector3D getCoordinates();
    void getRotation(QVector3D);
    QMatrix4x4 getProjectinMatrix();

    //задание текущих
    void setScale(float);
    void setRotation(QVector3D);
    void setCoordinates(QVector3D);

    //изменение относительно текущих
    void move(QVector3D);
    void rotate(QVector3D);
    void scale(float);
    void lock();
    void unlock();
    void update();


private:
    void changeProjectionMatrix();


private:
    QMatrix4x4 objectProjectionMatrix;
    QVector3D coordinatesParam;
    QQuaternion rotateParam;
    float scaleParam;
    bool isLock;

};

#endif // BASEENGINEOBJECT_H
