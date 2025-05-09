#ifndef INPUTENGINE_H
#define INPUTENGINE_H

#include "Utils/Vectors.h"

#include <QWidget>
#include <QEvent>
#include <QObject>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QQuaternion>

class cInputEngine : public QObject
{
    Q_OBJECT

public:
    cInputEngine();
    ~cInputEngine() = default;

    void setScreenCoords(const sVec2& size);

    QQuaternion getRotateX();
    QQuaternion getRotateY();
    QVector3D getTranslate();

    QVector3D getWorldCoordinates(QMatrix4x4 projectionMatrix, 
        QMatrix4x4 viewMatrix, const float &objectY = 0);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelScrollEvent(QWheelEvent* event);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QVector2D m_mouseCoordinates;

    QQuaternion m_rotateXDelta;
    QQuaternion m_rotateYDelta;
    QQuaternion m_rotateDelta;
    QVector3D m_translateDelta;

    int m_screenWidth;
    int m_screenHeight;
};

#endif // INPUTENGINE_H
