#include "graphicsengine.h"

GraphicsEngine* GraphicsEngine::_instance = nullptr;

GraphicsEngine::GraphicsEngine()
{

}

GraphicsEngine::~GraphicsEngine()
{

}

void GraphicsEngine::initGraphics()
{
    glClearColor(0,0,0,1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void GraphicsEngine::paintScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsEngine::resizeScene(int w,int h)
{
    float aspect = w / (float)h;

    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(45,aspect, 0.1f, 10.0f);

}

//Scene *GraphicsEngine::getCurrentScene() const
//{
//    return _currentScene;
//}


//void GraphicsEngine::loadScene(Scene *scene)
//{

//}

//void GraphicsEngine::loadScene(QVector<Scene *> scene)
//{

//}

GraphicsEngine *GraphicsEngine::getInstance()
{
    if(_instance == nullptr){
        _instance = new GraphicsEngine();
    }
    return _instance;
}
