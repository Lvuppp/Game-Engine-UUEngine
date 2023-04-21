#ifndef BASEENGINEOBJECT_H
#define BASEENGINEOBJECT_H

#include<QVector3D>

class BaseEngineObject
{
public:
    BaseEngineObject();
    virtual ~BaseEngineObject() = 0;

    virtual void move(QVector3D) = 0;
    virtual void rotate(QVector3D) = 0;
    virtual void scale(int) = 0;
    virtual void setRotation(QVector3D) = 0;
    virtual void setCoordinates(QVector3D) = 0;
    virtual double getScale() = 0;
    virtual QVector3D getCoordinates() = 0;
    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual void update() = 0;

protected:
    QVector3D coordinatesParam;
    double scaleParam;
    bool isLock;
};

#endif // BASEENGINEOBJECT_H
