#include "inputengine.h"

InputEngine* InputEngine::_instance = nullptr;


InputEngine::InputEngine()
{

}

InputEngine::~InputEngine()
{

}

void InputEngine::setMouseEvent(QEvent* event)
{
    auto mouseEvent = (QMouseEvent*)event;

    if(event->type() == QEvent::Type::MouseMove){
        QVector2D diff = QVector2D(mouseEvent->position()) - mouseCoordinates;
        mouseCoordinates = QVector2D(mouseEvent->position());

        float angle = diff.length() / 2.0f;

        QVector3D axis = QVector3D(diff.y(), diff.x(), 0.0f);

        rotate = QQuaternion::fromAxisAndAngle(axis,angle);
    }
    else if(event->type() == QEvent::Type::MouseButtonPress){
        mouseCoordinates = QVector2D(mouseEvent->position());
    }

    mouseEvent->accept();
}

QQuaternion InputEngine::getRotate()
{
    return rotate;
}

QVector3D InputEngine::getTranslate()
{
    return translate;
}

InputEngine *InputEngine::getInstance()
{
    if(_instance == nullptr){
        _instance = new InputEngine();
    }
    return _instance;
}
