#include "InputEngine.h"

#include <QMatrix4x4>

cInputEngine* cInputEngine::m_instance = nullptr;


cInputEngine::cInputEngine()
{

}

cInputEngine::~cInputEngine()
{

}



void cInputEngine::wheelEvent(QWheelEvent *event)
{
    auto wheelEvent = (QWheelEvent*)event;

    if (wheelEvent->angleDelta().y() > 0)
        m_translateDelta = QVector3D(0.0f, 0.0f, 0.2f);

    else if (wheelEvent->angleDelta().y() < 0)
        m_translateDelta = QVector3D(0.0f, 0.0f, -0.2f);

}

QQuaternion cInputEngine::getRotateX()
{
    return m_rotateXDelta;
}

QQuaternion cInputEngine::getRotateY()
{
    return m_rotateYDelta;
}

QVector3D cInputEngine::getWorldCoordinates(QMatrix4x4 projectionMatrix, QMatrix4x4 viewMatrix, const float &objectY)
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
    return m_translateDelta;
}

void cInputEngine::setScreenCoords(const int &width, const int &height)
{
    m_screenWidth = width;
    m_screenHeight = height;
}

void cInputEngine::mousePressEvent(QMouseEvent *event)
{
    m_mouseCoordinates = QVector2D(event->position());
}

void cInputEngine::mouseMoveEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton) return;

    QVector2D diffpos = QVector2D(event->position()) - m_mouseCoordinates;
    m_mouseCoordinates = QVector2D(event->position());

    float angleX = diffpos.y() / 2.0f;
    float angleY = diffpos.x() / 2.0f;

    m_rotateXDelta = QQuaternion::fromAxisAndAngle(1.0f ,0.0f ,0.0f, angleX);
    m_rotateYDelta = QQuaternion::fromAxisAndAngle(0.0f ,1.0f ,0.0f, angleY);

}

cInputEngine *cInputEngine::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new cInputEngine();
    }
    return m_instance;
}
