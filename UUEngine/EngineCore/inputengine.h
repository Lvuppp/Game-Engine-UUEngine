#ifndef INPUTENGINE_H
#define INPUTENGINE_H

#include<iostream>

#include <QWidget>
#include <QEvent>
#include <QObject>
#include <QMouseEvent>
#include <QQuaternion>

//применить паттерн стратегия
class InputEngine
{
public:
    ~InputEngine();

    void setMouseEvent(QEvent* event);

    QQuaternion getRotate();
    QVector3D getTranslate();
    static InputEngine *getInstance();

private:
    InputEngine();

    InputEngine(const InputEngine&) = delete;
    InputEngine& operator=(const InputEngine&) = delete;

    static InputEngine* _instance;

    QVector2D mouseCoordinates;

    QQuaternion rotate;
    QVector3D translate;

};

#endif // INPUTENGINE_H
