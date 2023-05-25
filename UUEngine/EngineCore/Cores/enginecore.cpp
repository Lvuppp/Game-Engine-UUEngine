#include "enginecore.h"

EngineCore* EngineCore::m_instance = nullptr;

EngineCore::EngineCore()
{
    m_modelLoader.setStrategy(new OBJModelLoadStraregy());
    m_sceneFolder = SceneFolder::getInstance();

    m_projectProcessor = ProjectProcessor::getInstance();
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


void EngineCore::paintScene()
{
    m_graphicsEngine->paintScene();
}

void EngineCore::initGraphicsEngine()
{
    m_graphicsEngine->initGraphics();
    createSimpleScene();
    //m_projectProcessor->saveProject("", m_sceneFolder->scenes(), "project");
    //m_projectProcessor->loadProject("project.uupj");
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

        m_graphicsEngine->rotateModelViewMatrix(m_inputEngine->getRotateX(), m_inputEngine->getRotateY());

        emit updateGraphics();
    }
    else if(event->type() == QEvent::Wheel){
        m_inputEngine->wheelEvent(event);

        m_graphicsEngine->translateModelViewMatrix(m_inputEngine->getTranslate());

        emit updateGraphics();
    }
}
////////////////////////////////////////////////////////////Project Processor

void EngineCore::initProjectProcessor(QVBoxLayout &layout)
{
    m_projectProcessor->setLayout(layout);
}

void EngineCore::createSimpleScene()
{
    m_sceneFolder->createScene("SimpleScene");

    m_sceneFolder->currentScene()->camera("DefaultCamera")->translate(QVector3D(0.0f, 1.0f, -5.0));

    m_sceneFolder->currentScene()->addGameObject("Giant", m_modelLoader.createModel(":/Models/TestModel/Stone.obj"));
    m_sceneFolder->currentScene()->addGameObject("Platform",ModelBuilder::createCube(20.0f, 1.0f, 20.0f));

    m_sceneFolder->currentScene()->setSkybox(ModelBuilder::createSkybox(100.0f, ":/Textures/skybox3.png"));
    m_graphicsEngine->setCurrentScene(m_sceneFolder->currentScene());

}

void EngineCore::createProject(const QString &path, const QString &name)
{
    m_projectProcessor->createProject(path, name);
}


void EngineCore::loadProject(const QString &path)
{
    m_projectProcessor->loadProject(path);
}

void EngineCore::saveProject(const QString &path, const QString &projectName)
{
    if(path == "" && ProjectInfo::projectPath() != "" && m_sceneFolder->scenes().size() > 0){
        m_projectProcessor->saveProject(m_sceneFolder->scenes());
    }
    else{
        m_projectProcessor->saveProject(m_sceneFolder->scenes(),path, projectName);
    }
}

void EngineCore::closeProject()
{
    m_sceneFolder->scenes().clear();
}

void EngineCore::loadModel(const QString &path)
{

}

void EngineCore::loadTexture(const QString &path)
{

}

void EngineCore::loadScript(const QString &path)
{

}

void EngineCore::createCustomObjectInScene()
{
    m_sceneFolder->currentScene()->addGameObject("Cube",ModelBuilder::createCube(2.0f, 2.0f, 2.0f));
    m_sceneFolder->currentScene()->gameObject("Cube")->translate(m_inputEngine->getTranslate());
}

void EngineCore::createSimpleObjectInScene()
{

}

void EngineCore::createCameraInScene()
{

}

void EngineCore::createLightingInScene()
{

}

