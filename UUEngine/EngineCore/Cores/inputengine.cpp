#include "inputengine.h"

InputEngine* InputEngine::m_instance = nullptr;


InputEngine::InputEngine()
{

}

InputEngine::~InputEngine()
{

}

void InputEngine::mouseEvent(QEvent* event)
{
    auto mouseEvent = (QMouseEvent*)event;

    if(mouseEvent->type() == QMouseEvent::MouseMove){
        QVector2D diffpos = QVector2D(mouseEvent->position()) - m_mouseCoordinates;
        m_mouseCoordinates = QVector2D(mouseEvent->position());

        float angleX = diffpos.y() / 2.0f;
        float angleY = diffpos.x() / 2.0f;

        m_rotateXDelta = QQuaternion::fromAxisAndAngle(1.0f ,0.0f ,0.0f, angleX);
        m_rotateYDelta = QQuaternion::fromAxisAndAngle(0.0f ,1.0f ,0.0f, angleY);

    }
    else if(mouseEvent->type() == QMouseEvent::MouseButtonPress){
        m_mouseCoordinates = QVector2D(mouseEvent->position());
    }
    mouseEvent->accept();
}

void InputEngine::wheelEvent(QEvent *event)
{
    auto wheelEvent = (QWheelEvent*)event;

    if (wheelEvent->angleDelta().y() > 0)
        m_translateDelta = QVector3D(0.0f, 0.0f, 0.2f);

    else if (wheelEvent->angleDelta().y() < 0)
        m_translateDelta = QVector3D(0.0f, 0.0f, -0.2f);

    wheelEvent->accept();
}

QQuaternion InputEngine::getRotateX()
{
    return m_rotateXDelta;
}

QQuaternion InputEngine::getRotateY()
{
    return m_rotateYDelta;
}

QVector3D InputEngine::getWorldCoordinates()
{
//    QVector4D tmp(m_mouseCoordinates.x() / width());
}

QVector3D InputEngine::getTranslate()
{
    return m_translateDelta;
}

InputEngine *InputEngine::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new InputEngine();
    }
    return m_instance;
}
