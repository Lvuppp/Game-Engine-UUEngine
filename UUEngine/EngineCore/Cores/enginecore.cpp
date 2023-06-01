#include "enginecore.h"

EngineCore* EngineCore::m_instance = nullptr;

EngineCore::EngineCore()
{
    m_modelFolder = ModelFolder::getInstance();
    m_scriptFolder = ScriptFolder::getInstance();
    m_textureFolder = TextureFolder::getInstance();

    m_modelLoader.setFactory(new OBJModelFactory());
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

void EngineCore::paintScene()
{
    //clock_t start = clock();

    if(getCurrentScene() == nullptr) return;

    m_graphicsEngine->paintScene();
    //clock_t end = clock();
    //qDebug() << (double)(end - start) / CLOCKS_PER_SEC;
}

void EngineCore::initGraphicsEngine()
{
    m_graphicsEngine->initGraphics();
    //m_projectProcessor->saveProject("", m_sceneFolder->scenes(), "project");
    //m_projectProcessor->loadProject("project.uupj");
    //m_scriptEngine->loadScript(m_sceneFolder->object("Golem"));
}

//scene work

void EngineCore::createScene(const QString &sceneName)
{
    m_sceneFolder->createScene(sceneName);
    m_graphicsEngine->setCurrentScene(getCurrentScene());
}

void EngineCore::selectCurrentScene(const QString &sceneName)
{
    m_graphicsEngine->setCurrentScene(m_sceneFolder->setCurrentScene(sceneName));
    emit updateGraphics();
}

Scene *EngineCore::getCurrentScene()
{
    return m_sceneFolder->currentScene();
}


void EngineCore::translateObject(const QString &objectName, const QVector3D &translation)
{
    getCurrentScene()->gameObject(objectName)->
        translate(translation - QVector3D(getCurrentScene()->gameObject(objectName)->coordinates()));
}

void EngineCore::rotateXObject(const QString &objectName, const QQuaternion &rotation)
{
    getCurrentScene()->gameObject(objectName)->
        rotateX(rotation - QQuaternion(getCurrentScene()->gameObject(objectName)->rotationX()));
}

void EngineCore::rotateYObject(const QString &objectName, const QQuaternion &rotation)
{
    getCurrentScene()->gameObject(objectName)->
        rotateY(rotation - QQuaternion(getCurrentScene()->gameObject(objectName)->rotationY()));
}

void EngineCore::scaleObject(const QString &objectName, const float &scale)
{
    getCurrentScene()->gameObject(objectName)->
        scale(getCurrentScene()->gameObject(objectName)->scale() - scale);
}

void EngineCore::setNormalTexture(const QString &objectName, const QString &path)
{
    auto model = dynamic_cast<SimpleModel *>(getCurrentScene()->gameObject(objectName)->model());
    model->modelParticle()->setNormalMap(path);
}

void EngineCore::setDiffuseTexture(const QString &objectName, const QString &path)
{
    auto model = dynamic_cast<SimpleModel *>(getCurrentScene()->gameObject(objectName)->model());
    model->modelParticle()->setDiffuseMap(path);
    loadTexture(objectName, path);
}


bool EngineCore::createOBJModel(const QString &objectName, const QString &path)
{
    m_modelLoader.setFactory(new OBJModelFactory);
    if(!getCurrentScene()->addGameObject(objectName, m_modelLoader.createModel(path)))
        return false;

    m_modelFolder->append(objectName, path.split('/').constLast());
    placeObjectOnMousePosition(objectName);
    return true;
}

bool EngineCore::createFBXModel(const QString &objectName, const QString &path)
{
    m_modelLoader.setFactory(new FBXModelFactory);
    if(!getCurrentScene()->addGameObject(objectName, m_modelLoader.createModel(path)))
        return false;

    m_modelFolder->append(objectName, path.split('/').constLast());
    placeObjectOnMousePosition(objectName);
    return true;
}

void EngineCore::createCameraInScene(const QString &objectName)
{
    getCurrentScene()->addCamera(objectName);
    getCurrentScene()->camera(objectName)->
        setCoordinates(m_inputEngine->getWorldCoordinates(m_graphicsEngine->projectionMatrix(),
                                                          m_graphicsEngine->cameraViewMatrix()));
    emit updateGraphics();
}

void EngineCore::createLightingInScene(const QString &objectName)
{
    getCurrentScene()->addLighting(objectName);
    getCurrentScene()->lighting(objectName)->
        setCoordinates(m_inputEngine->getWorldCoordinates(m_graphicsEngine->projectionMatrix(),
                                                          m_graphicsEngine->cameraViewMatrix()));
    emit updateGraphics();
}

void EngineCore::setSkyBox(const float &size, const QString &path)
{
    getCurrentScene()->setSkybox(m_modelBuilder.createSkybox(size, path));
    m_textureFolder->append("Skybox", path.split('/').constLast());
    emit updateGraphics();
}

bool EngineCore::createCube(const QString &objectName, const float &width, const float &height, const float &depth)
{
    if(!getCurrentScene()->addGameObject(objectName, m_modelBuilder.createCube(width, height, depth)))
        return false;

    m_modelFolder->replace(objectName, QString("CUBE(%1 %2 %3)").arg(width).arg(height).arg(depth));
    placeObjectOnMousePosition(objectName);
    return true;
}

void EngineCore::createPyramide(const QString &objectName, const float &width, const float &height)
{
    getCurrentScene()->addGameObject(objectName, m_modelBuilder.createPyramide(width, height));
    m_modelFolder->replace(objectName, QString("PYRAMID(%1 %2)").arg(width).arg(height));
    placeObjectOnMousePosition(objectName);
}

bool EngineCore::createSphere(const QString &objectName, const float &radius, const int &stacks, const int &sectors)
{
    if(!getCurrentScene()->addGameObject(objectName, m_modelBuilder.createSphere(radius,stacks, sectors)))
        return false;

    m_modelFolder->replace(objectName, QString("SPHERE(%1 %2 %3)").arg(radius).arg(stacks).arg(sectors));
    placeObjectOnMousePosition(objectName);
    return true;
}

void EngineCore::createPrism(const QString &objectName, const float &width, const float &height, const float &depth, const float &angle)
{
    getCurrentScene()->addGameObject(objectName, m_modelBuilder.createPrism(width,height, depth, angle));
    m_modelFolder->replace(objectName, QString("PRISM(%1 %2 %3 %4)").arg(width).arg(height).arg(depth).arg(angle));
    placeObjectOnMousePosition(objectName);
}

void EngineCore::createCone(const QString &objectName, const float &width, const float &height, const int &sectors)
{
    getCurrentScene()->addGameObject(objectName, m_modelBuilder.createCone(width, height, sectors));
    m_modelFolder->replace(objectName, QString("CONE(%1 %2 %3)").arg(width).arg(height).arg(sectors));
    placeObjectOnMousePosition(objectName);
}

void EngineCore::createCylinder(const QString &objectName, const float &width, const float &height, const int &sectors)
{
    getCurrentScene()->addGameObject(objectName, m_modelBuilder.createCylinder(width, height, sectors));
    m_modelFolder->replace(objectName, QString("CYLINDER(%1 %2 %3)").arg(width).arg(height).arg(sectors));
    placeObjectOnMousePosition(objectName);
}

void EngineCore::changeCube(const QString &objectName, const float &width, const float &height, const float &depth)
{
    getCurrentScene()->gameObject(objectName)->setModel(m_modelBuilder.createCube(width, height, depth));
    m_modelFolder->replace(objectName, QString("CUBE(%1 %2 %3)").arg(width).arg(height).arg(depth));
    emit updateGraphics();
}

void EngineCore::changeSphere(const QString &objectName, const float &radius, const int &rings, const int &sectors)
{
    getCurrentScene()->gameObject(objectName)->setModel(m_modelBuilder.createSphere(radius, rings, sectors));
    m_modelFolder->replace(objectName, QString("SPHERE(%1 %2 %3)").arg(radius).arg(rings).arg(sectors));
    emit updateGraphics();
}


////////////////////////////////////////////////////Input Engine

void EngineCore::initInputEngine(const int &width, const int &height)
{
    m_inputEngine->setScreenCoords(width, height);
}


void EngineCore::mousePressEvent(QMouseEvent *event)
{
    m_inputEngine->mousePressEvent(event);
    emit updateGraphics();
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

void EngineCore::mouseDoubleClickEvent(QMouseEvent *event)
{
    auto objectName = getCurrentScene()->gameObjectsHash().key(dynamic_cast<Base3DGameObject*>(m_graphicsEngine->selectObject(event->pos())));
    auto object = dynamic_cast<Base3DGameObject*>(m_graphicsEngine->selectObject(event->pos()));
    emit emitObject(objectName, &object);
    emit updateGraphics();
}

void EngineCore::placeObjectOnMousePosition(const QString &objectName)
{
    getCurrentScene()->gameObject(objectName)->
        setCoordinates(m_inputEngine->getWorldCoordinates(m_graphicsEngine->projectionMatrix(),
                                                          m_graphicsEngine->cameraViewMatrix()));
}

void EngineCore::changeGameStatus()
{
    m_scriptEngine->changeGameStatus();
}


////////////////////////////////////////////////////////////Project Processor

void EngineCore::initProjectProcessor(QVBoxLayout &layout)
{
    m_projectProcessor->setLayout(layout);
}


void EngineCore::createProject(const QString &path, const QString &name)
{
    m_projectProcessor->createProject(path, name);
    m_sceneFolder->createScene(name);
    m_graphicsEngine->setCurrentScene(getCurrentScene());
    emit setDisableState(false);
}


void EngineCore::loadProject(const QString &path)
{
    m_sceneFolder->setScenes(m_projectProcessor->loadProject(path));
    m_graphicsEngine->setCurrentScene(getCurrentScene());
    emit setDisableState(false);

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
    emit setDisableState(true);
}

void EngineCore::loadModel(const QString &objectName, const QString &path)
{
    m_modelFolder->append(objectName, path);
}

void EngineCore::loadTexture(const QString &objectName, const QString &path)
{
    m_textureFolder->append(objectName, path.split('/').constLast());
    ProjectInfo::copyToTextures(path);
}

void EngineCore::loadScript(const QString &objectName, const QString &path)
{
    m_scriptFolder->addScript(objectName, path.split('/').constLast());
    ProjectInfo::copyToScripts(path);
}

QString EngineCore::getModel(const QString &objectName)
{
    return m_modelFolder->model(objectName);
}

QVector<QString> EngineCore::getScripts(const QString &objectName)
{
    return m_scriptFolder->scripts(objectName);
}
