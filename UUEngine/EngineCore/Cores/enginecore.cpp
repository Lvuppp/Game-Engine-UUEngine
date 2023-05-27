#include "enginecore.h"

EngineCore* EngineCore::m_instance = nullptr;

EngineCore::EngineCore()
{
    m_modelFolder = ModelFolder::getInstance();
    m_scriptFolder = ScriptFolder::getInstance();
    m_textureFolder = TextureFolder::getInstance();

    m_modelLoader.setStrategy(new OBJModelLoadStrategy());
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
    m_inputEngine->setScreenCoords(w,h);
}

void EngineCore::createScene(const QString &sceneName)
{
    m_sceneFolder->createScene(sceneName);
    m_graphicsEngine->setCurrentScene(m_sceneFolder->currentScene());
}

void EngineCore::translateObject(const QString &objectName, const QVector3D &translation)
{
    m_sceneFolder->currentScene()->gameObject(objectName)->
        translate(QVector3D( m_sceneFolder->currentScene()->gameObject(objectName)->coordinates() - translation));
}

void EngineCore::rotateObject(const QString &objectName, const QQuaternion &rotation)
{
    m_sceneFolder->currentScene()->gameObject(objectName)->
        rotate(QQuaternion(m_sceneFolder->currentScene()->gameObject(objectName)->rotation() - rotation));
}

void EngineCore::scaleObject(const QString &objectName, const float &scale)
{
    m_sceneFolder->currentScene()->gameObject(objectName)->
        scale(m_sceneFolder->currentScene()->gameObject(objectName)->scale() - scale);
}

void EngineCore::setNormalTexture(const QString &objectName, const QString &path)
{
    auto model = dynamic_cast<SimpleModel *>(m_sceneFolder->currentScene()->gameObject(objectName)->model());
    model->modelParticle()->setNormalMap(path);
}

void EngineCore::setDiffuseTexture(const QString &objectName, const QString &path)
{
    auto model = dynamic_cast<SimpleModel *>(m_sceneFolder->currentScene()->gameObject(objectName)->model());
    model->modelParticle()->setDiffuseMap(path);
}

void EngineCore::createOBJModel(const QString &objectName, const QString &path)
{
    m_modelLoader.setStrategy(new OBJModelLoadStrategy);
    m_sceneFolder->currentScene()->addGameObject(objectName, m_modelLoader.createModel(path));
    m_modelFolder->append(objectName, path.split('/').constLast());
    emit updateGraphics();
}

void EngineCore::selectCurrentScene(const QString &sceneName)
{
    m_graphicsEngine->setCurrentScene(m_sceneFolder->setCurrentScene(sceneName));
    emit updateGraphics();
}

void EngineCore::createFBXModel(const QString &objectName, const QString &path)
{
    m_modelLoader.setStrategy(new FBXModelLoadStrategy);
    m_sceneFolder->currentScene()->addGameObject(objectName, m_modelLoader.createModel(path));
    m_modelFolder->append(objectName, path.split('/').constLast());
    emit updateGraphics();
}

void EngineCore::createCameraInScene(const QString &objectName)
{
    m_sceneFolder->currentScene()->addCamera(objectName);
    emit updateGraphics();
}

void EngineCore::createLightingInScene(const QString &objectName)
{
    m_sceneFolder->currentScene()->addLighting(objectName);
    emit updateGraphics();
}

void EngineCore::setSkyBox(const float &size, const QString &path)
{
    m_sceneFolder->currentScene()->setSkybox(m_modelBuilder.createSkybox(size, path));
    m_textureFolder->append("Skybox", path.split('/').constLast());
    emit updateGraphics();
}

void EngineCore::createCube(const QString &objectName, const float &width, const float &height, const float &depth)
{
    m_sceneFolder->currentScene()->addGameObject(objectName, m_modelBuilder.createCube(width, height, depth));
    m_modelFolder->replace(objectName, QString("CUBE(%1 %2 %3)").arg(width, height, depth));
    emit updateGraphics();
}

void EngineCore::createPyramide(const QString &objectName, const float &width, const float &height)
{
    m_sceneFolder->currentScene()->addGameObject(objectName, m_modelBuilder.createPyramide(width, height));
    m_modelFolder->replace(objectName, QString("PYRAMID(%1 %2)").arg(width, height));
    emit updateGraphics();
}

void EngineCore::createSphere(const QString &objectName, const float &radius, const int &rings, const int &sectors)
{
    m_sceneFolder->currentScene()->addGameObject(objectName, m_modelBuilder.createSphere(radius,rings, sectors));
    m_modelFolder->replace(objectName, QString("SPHERE(%1 %2 %3)").arg(radius).arg(rings, sectors));
    emit updateGraphics();
}

void EngineCore::createPrism(const QString &objectName, const float &width, const float &height, const float &depth, const float &angle)
{
    m_sceneFolder->currentScene()->addGameObject(objectName, m_modelBuilder.createPrism(width,height, depth, angle));
    m_modelFolder->replace(objectName, QString("PRISM(%1 %2 %3 %4)").arg(width,height, depth, angle));
    emit updateGraphics();
}

void EngineCore::createCone(const QString &objectName, const float &width, const float &height, const int &sectors)
{
    m_sceneFolder->currentScene()->addGameObject(objectName, m_modelBuilder.createCone(width, height, sectors));
    m_modelFolder->replace(objectName, QString("CONE(%1 %2 %3)").arg(width, height).arg(sectors));
    emit updateGraphics();
}

void EngineCore::createCylinder(const QString &objectName, const float &width, const float &height, const int &sectors)
{
    m_sceneFolder->currentScene()->addGameObject(objectName, m_modelBuilder.createCylinder(width, height, sectors));
    m_modelFolder->replace(objectName, QString("CYLINDER(%1 %2 %3)").arg(width, height).arg(sectors));
    emit updateGraphics();
}

void EngineCore::paintScene()
{
    //clock_t start = clock();

    if(m_sceneFolder->currentScene() == nullptr) return;

    m_graphicsEngine->paintScene();
    //clock_t end = clock();
    //qDebug() << (double)(end - start) / CLOCKS_PER_SEC;
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

void EngineCore::initInputEngine(const int &width, const int &height)
{
    m_inputEngine->setScreenCoords(width, height);
}


void EngineCore::mousePressEvent(QMouseEvent *event)
{
    m_inputEngine->mousePressEvent(event);
}

void EngineCore::mouseMoveEvent(QMouseEvent *event)
{
    m_inputEngine->mouseMoveEvent(event);
    m_graphicsEngine->rotateModelViewMatrix(m_inputEngine->getRotateX(), m_inputEngine->getRotateY());
    emit updateGraphics();
}

void EngineCore::wheelEvent(QWheelEvent *event)
{
    m_inputEngine->wheelEvent(event);
    m_graphicsEngine->translateModelViewMatrix(m_inputEngine->getTranslate());
    emit updateGraphics();
}

////////////////////////////////////////////////////////////Project Processor

void EngineCore::initProjectProcessor(QVBoxLayout &layout)
{
    m_projectProcessor->setLayout(layout);
}

void EngineCore::createSimpleScene()
{
    createScene("SimpleScene");
    createOBJModel("Giant", ":/Models/TestModel/Stone.obj");
    createCube("Platform", 20.0f, 1.0f, 20.0f);
    createCube("Cube", 2.0f, 1.0f, 2.0f);
    translateObject("Cube", QVector3D(5.0f,0.0f,0.0f));
    translateObject("Platform",QVector3D(0.0f,2.0f,0.0f));
}


void EngineCore::createProject(const QString &path, const QString &name)
{
    m_projectProcessor->createProject(path, name);
    m_sceneFolder->createScene(name);
    m_graphicsEngine->setCurrentScene(m_sceneFolder->currentScene());
    emit updateGraphics();
}


void EngineCore::loadProject(const QString &path)
{
    //m_projectProcessor->loadProject(path);
    createSimpleScene();
    emit updateGraphics();
}

void EngineCore::saveProject(const QString &path, const QString &projectName)
{
    if(path == "" && ProjectInfo::projectPath() != "" && m_sceneFolder->scenes().size() > 0){
        m_projectProcessor->saveProject(m_sceneFolder->scenes());
    }
    else{
        m_projectProcessor->saveProject(m_sceneFolder->scenes(),path);
    }
}

void EngineCore::closeProject()
{
    m_projectProcessor->closeProject(m_sceneFolder->scenes());
    m_sceneFolder->clearFolder();
    emit updateGraphics();
}

void EngineCore::loadModel(const QString &objectName, const QString &path)
{
    m_modelFolder->append(objectName, path);
}

void EngineCore::loadTexture(const QString &objectName, const QString &path)
{
    m_textureFolder->append(objectName, path);
}

void EngineCore::loadScript(const QString &objectName, const QString &path)
{
    m_scriptFolder->addScript(objectName, path);
}
