#ifndef INPUTENGINE_H
#define INPUTENGINE_H

#include<iostream>

#include <QWidget>
#include <QEvent>
#include <QObject>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QQuaternion>

//применить паттерн стратегия
class InputEngine
{
public:
    ~InputEngine();

    void mouseEvent(QEvent* event);
    void wheelEvent(QEvent* event);

    QQuaternion getRotate();
    QVector3D getTranslate();
    static InputEngine *getInstance();

private:
    InputEngine();

    InputEngine(const InputEngine&) = delete;
    InputEngine& operator=(const InputEngine&) = delete;

    static InputEngine* m_instance;

    QVector2D m_mouseCoordinates;

    QQuaternion m_rotateDelta;
    QVector3D m_translateDelta;

};

#endif // INPUTENGINE_H
