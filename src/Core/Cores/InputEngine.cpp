#include "InputEngine.h"

#include <QMatrix4x4>
#include <qevent.h>

#include <iostream>

bool cInputEngine::eventFilter(QObject* obj, QEvent* event)
{
    switch (event->type()) {
        case QEvent::KeyPress: {
            auto keyEvent = static_cast<QKeyEvent*>(event);
            return true;
        }

        case QEvent::KeyRelease: {
            auto keyEvent = static_cast<QKeyEvent*>(event);
            return true;
        }

        case QEvent::MouseButtonPress: {
            auto mouseEvent = static_cast<QMouseEvent*>(event);
            mousePressEvent(mouseEvent);
            return true;
        }

        case QEvent::MouseButtonRelease: {
            auto mouseEvent = static_cast<QMouseEvent*>(event);
            return true;
        }

        case QEvent::MouseMove: {
            auto mouseEvent = static_cast<QMouseEvent*>(event);
            mouseMoveEvent(mouseEvent);
            event->accept();
            return true;
        }

        case QEvent::Wheel: {
            auto wheelEvent = static_cast<QWheelEvent*>(event);
            wheelScrollEvent(wheelEvent);
            return true;
        }
        default:
            break;
    }

    return QObject::eventFilter(obj, event);
}

void cInputEngine::wheelScrollEvent(QWheelEvent* wheelEvent)
{
    if (wheelEvent->angleDelta().y() > 0)
    {
        m_translateDelta = QVector3D(0.0f, 0.0f, 0.2f);
    }
    else if (wheelEvent->angleDelta().y() < 0)
    {
        m_translateDelta = QVector3D(0.0f, 0.0f, -0.2f);
    }
}

QQuaternion cInputEngine::getRotateX()
{
    const auto delta = m_rotateXDelta;
    m_rotateXDelta = QQuaternion();
    return delta;
}

QQuaternion cInputEngine::getRotateY()
{
    const auto delta = m_rotateYDelta;
    m_rotateYDelta = QQuaternion();
    return delta;
}

QVector3D cInputEngine::getWorldCoordinates(QMatrix4x4 projectionMatrix, QMatrix4x4 viewMatrix, float objectY)
{
    QVector4D tmp(2.0f * m_mouseCoordinates.x() / m_screenWidth - 1.0f,
                  -2.0f * m_mouseCoordinates.y() / m_screenHeight + 1.0f, -1.0f, 1.0f);
    QVector4D iTmp((projectionMatrix.inverted() * tmp).toVector2D(), -1.0f, 0.0f);
    QVector3D direction((viewMatrix.inverted() * iTmp).toVector3D().normalized());
    QVector3D camPos(viewMatrix.inverted().map(QVector4D(0.0f, 0.0f, 0.0f, 1.0f).toVector3D()));

    QVector3D normal(0.0f, 1.0f, 0.0f);
    float t = -QVector3D::dotProduct(camPos, normal) / QVector3D::dotProduct(direction, normal);
    QVector3D result = camPos + direction * t;

    return result;
}

QVector3D cInputEngine::getTranslate()
{
    const auto delta = m_translateDelta;
    m_translateDelta = QVector3D();
    if (delta.x() != 0.0f || delta.y() != 0.0f || delta.z() != 0.0f)
    {
        std::cout << delta.x() << " " << delta.y() << " " << delta.z() << std::endl;
    }
    return delta;
}

void cInputEngine::setScreenCoords(const sVec2& size)
{
    m_screenWidth = size.x;
    m_screenHeight = size.y;
}

void cInputEngine::mousePressEvent(QMouseEvent *event)
{
    m_mouseCoordinates = QVector2D(event->position());
}

void cInputEngine::mouseMoveEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        return;
    }

    const auto pos = QVector2D(event->position());
    const auto diffpos = pos - m_mouseCoordinates;
    m_mouseCoordinates = pos;

    auto angleX = diffpos.y() / 2.0f;
    auto angleY = diffpos.x() / 2.0f;

    m_rotateXDelta = QQuaternion::fromAxisAndAngle(2.0f, 0.0f, 0.0f, angleX);
    m_rotateYDelta = QQuaternion::fromAxisAndAngle(0.0f, 2.0f, 0.0f, angleY);

    std::cout << m_rotateXDelta.x() << " " << m_rotateXDelta.y() << " " << m_rotateXDelta.z() << " " << m_rotateXDelta.scalar() << std::endl;
    std::cout << m_rotateYDelta.x() << " " << m_rotateYDelta.y() << " " << m_rotateYDelta.z() << " " << m_rotateYDelta.scalar() << std::endl;

    std::cout << std::endl;
}
