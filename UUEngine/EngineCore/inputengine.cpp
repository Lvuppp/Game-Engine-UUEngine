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

    if(event->type() == QEvent::Type::MouseMove){
        QVector2D diffpos = QVector2D(mouseEvent->localPos()) - m_mouseCoordinates;
        m_mouseCoordinates = QVector2D(mouseEvent->localPos());

        float angle = diffpos.length() / 2.0f;
        QVector3D axis = QVector3D(diffpos.y(), diffpos.x(), 0.0f);

        m_rotateDelta = QQuaternion::fromAxisAndAngle(axis,angle);
    }
    else if(event->type() == QEvent::Type::MouseButtonPress){
        m_mouseCoordinates = QVector2D(mouseEvent->localPos());
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

QQuaternion InputEngine::getRotate()
{
    return m_rotateDelta;
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
