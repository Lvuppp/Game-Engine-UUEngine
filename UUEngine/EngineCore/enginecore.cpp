#include "enginecore.h"

EngineCore::EngineCore()
{
    graphicsEngine = GraphicsEngine::getInstance();
}

void EngineCore::resizeScene(int w, int h)
{
    graphicsEngine->resizeScene(w,h);
}

void EngineCore::initGraphicsEngine()
{
    graphicsEngine->initGraphics();
}

void EngineCore::paintScene()
{
    graphicsEngine->paintScene();
}
