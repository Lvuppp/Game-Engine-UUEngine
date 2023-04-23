#include "enginecore.h"

EngineCore::EngineCore()
{
    graphicsEngine = GraphicsEngine::getInstance();
    inputEngine = InputEngine::getInstance();

}
////////////////////////////////////////////////////Graphics Engine
void EngineCore::resizeScene(int w, int h)
{
    graphicsEngine->resizeScene(w,h);
}
void EngineCore::paintScene()
{
    graphicsEngine->paintScene();
}

void EngineCore::initGraphicsEngine()
{
    graphicsEngine->initGraphics();
}

////////////////////////////////////////////////////Input Engine

void EngineCore::initInputEngine()
{

}

void EngineCore::getEvent(QEvent *event)
{
    if(event->type() == QEvent::MouseMove){
        inputEngine->setMouseEvent(event);

        graphicsEngine->rotateModelViewMatrix(inputEngine->getRotate());
        graphicsEngine->translateModelViewMatrix(inputEngine->getTranslate());

        emit updateGraphics();
    }
}

