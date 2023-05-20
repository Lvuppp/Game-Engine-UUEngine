#include "enginecore.h"

EngineCore* EngineCore::m_instance = nullptr;

EngineCore::EngineCore()
{
    m_modelLoader.setStrategy(new OBJModelLoadStraregy());
    m_sceneFolder = new SceneFolder();
    //m_projectProcessor = ProjectProcessor::getInstance();
    m_graphicsEngine = GraphicsEngine::getInstance();
    m_inputEngine = InputEngine::getInstance();
    m_scriptEngine = ScriptEngine::getInstance();
}

EngineCore *EngineCore::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new EngineCore();
    }
    return m_instance;
}

////////////////////////////////////////////////////Graphics Engine
void EngineCore::resizeScene(int w, int h)
{
    m_graphicsEngine->resizeScene(w,h);
}

void EngineCore::createSimpleScene()
{
    m_sceneFolder->createScene("SimpleScene");

    m_sceneFolder->currentScene()->addCamera("Camera");
    m_sceneFolder->currentScene()->camera("Camera")->translate(QVector3D(0.0f, 1.0f, -5.0));
    m_sceneFolder->currentScene()->setCurrentCamera("Camera");
    m_sceneFolder->currentScene()->addLighting("Light");

    m_sceneFolder->currentScene()->addGameObject("Giant", new CustomModel(m_modelLoader.createModel(":/Models/TestModel/Stone.obj")));
//    m_sceneFolder->currentScene()->addGameObject();
    m_sceneFolder->currentScene()->addGameObject("Platform",ModelBuilder::createCube(20.0f, 1.0f, 20.0f));
//    m_sceneFolder->currentScene()->addGameObject(new SimpleModel("Cube", m_modelBuilder.createCube(0.5f, 0.5f, 0.5f)));
//    m_sceneFolder->currentScene()->setSkybox(new SimpleModel(m_modelBuilder.createSkybox(100.0f, ":/Textures/skybox3.png")));

//    m_sceneFolder->currentScene()->gameObject("Cube")->translate(QVector3D(10.0f,1.5f,1.0f));

//    m_sceneFolder->currentScene()->gameObject("Platform")->model().last()->setDiffuseMap(":/Textures/texture1.jpg");
//    m_sceneFolder->currentScene()->gameObject("Platform")->model().last()->setNormalMap(":/Textures/normal2.jpg");
//    m_sceneFolder->currentScene()->gameObject("Cube")->model().last()->setDiffuseMap(":/Textures/rockTexture.jpeg");
//    m_sceneFolder->currentScene()->gameObject("Cube")->model().last()->setNormalMap(":/Textures/normal.jpeg");

    m_sceneFolder->currentScene()->setSkybox(ModelBuilder::createSkybox(100.0f, ":/Textures/skybox3.png"));
    m_graphicsEngine->setCurrentScene(m_sceneFolder->currentScene());

}

void EngineCore::loadProject(QString path)
{

}

void EngineCore::saveProject(QString path)
{

}

void EngineCore::paintScene()
{
    m_graphicsEngine->paintScene();
}

void EngineCore::initGraphicsEngine()
{
    m_graphicsEngine->initGraphics();
    createSimpleScene();
    //m_projectProcessor->saveProject("", m_sceneFolder->scenes(), "project");
    //m_scriptEngine->loadScript(m_sceneFolder->object("Golem"));
}

////////////////////////////////////////////////////Input Engine

void EngineCore::initInputEngine()
{

}

void EngineCore::getEvent(QEvent *event)
{
    if(event->type() == QEvent::MouseMove){
        m_inputEngine->mouseEvent(event);

        m_graphicsEngine->rotateModelViewMatrix(m_inputEngine->getRotate());

        emit updateGraphics();
    }
    else if(event->type() == QEvent::Wheel){
        m_inputEngine->wheelEvent(event);

        m_graphicsEngine->translateModelViewMatrix(m_inputEngine->getTranslate());

        emit updateGraphics();
    }
}
////////////////////////////////////////////////////////////Project Processor

//void EngineCore::initProjectProcessor(QVBoxLayout *layout)
//{

//}

