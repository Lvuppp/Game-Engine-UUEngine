#include "enginecore.h"

EngineCore::EngineCore()
{
    m_modelLoader = new ModelLoader(new OBJModelLoadStraregy());
    m_objectBuilder = new ObjectBuilder();
    m_sceneFolder = new SceneFolder();
    m_graphicsEngine = GraphicsEngine::getInstance();
    m_inputEngine = InputEngine::getInstance();
    m_scriptEngine = ScriptEngine::getInstance();


}
////////////////////////////////////////////////////Graphics Engine
void EngineCore::resizeScene(int w, int h)
{
    m_graphicsEngine->resizeScene(w,h);
}

void EngineCore::createSimpleScene()
{
    m_sceneFolder->createScene("SimpleScene");

    m_sceneFolder->addCamera("Camera");
    m_sceneFolder->camera("Camera")->translate(QVector3D(0.0f, 1.0f, -5.0));
    m_sceneFolder->setCurrentCamera("Camera");
    m_sceneFolder->addLight("Light");
    m_sceneFolder->addObject("Golem", ModelType::CustomeModel, m_modelLoader->createModel(":/Models/TestModel/Stone.obj"), ":/Models/TestModel/Stone.obj");
    m_sceneFolder->addObject("Platform", ModelType::Cube, m_objectBuilder->createCube(20.0f, 1.0f, 20.0f));
    m_sceneFolder->addObject("Cube", ModelType::Cube, m_objectBuilder->createCube(0.5f, 0.5f, 0.5f));
    m_sceneFolder->setSkyBox(m_objectBuilder->createSkybox(100.0f, ":/Textures/skybox3.png"));

    m_sceneFolder->object("Cube")->translate(QVector3D(10.0f,1.5f,1.0f));

    m_sceneFolder->object("Platform")->model().last()->setDiffuseMap(":/Textures/texture1.jpg");
    m_sceneFolder->object("Platform")->model().last()->setNormalMap(":/Textures/normal2.jpg");
    m_sceneFolder->object("Cube")->model().last()->setDiffuseMap(":/Textures/rockTexture.jpeg");
    m_sceneFolder->object("Cube")->model().last()->setNormalMap(":/Textures/normal.jpeg");


    m_graphicsEngine->setCurrentScene(m_sceneFolder->currentScene());

}
void EngineCore::paintScene()
{
    m_graphicsEngine->paintScene();
}

void EngineCore::initGraphicsEngine()
{
    m_graphicsEngine->initGraphics();
    createSimpleScene();
    ProjectProcessor::saveProject("", m_sceneFolder->scenes(), "project");
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

