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
enum class InputMode{
    CameraMove,
    Move,
    Rotate,
    Create,
    Edit
};

class cInputEngine
{
public:
    ~cInputEngine();

    QQuaternion getRotateX();
    QQuaternion getRotateY();

    QVector3D getWorldCoordinates(QMatrix4x4 projectionMatrix, QMatrix4x4 viewMatrix, const float &objectY = 0);

    QVector3D getTranslate();
public:
    void setScreenCoords(const int &width, const int &height);

public:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

public:
    static cInputEngine *getInstance();

private:

    QVector2D m_mouseCoordinates;

    QQuaternion m_rotateXDelta;
    QQuaternion m_rotateYDelta;
    QQuaternion m_rotateDelta;
    QVector3D m_translateDelta;

    int m_screenWidth;
    int m_screenHeight;

private:
    cInputEngine();

    cInputEngine(const cInputEngine&) = delete;
    cInputEngine& operator=(const cInputEngine&) = delete;

    static cInputEngine* m_instance;

};

#endif // INPUTENGINE_H
