#include "EngineCore.h"

cEngineCore* cEngineCore::m_instance = nullptr;

cEngineCore::cEngineCore()
{
    m_modelFolder = cModelFolder::getInstance();
    m_scriptFolder = cScriptFolder::getInstance();
    m_textureFolder = cTextureFolder::getInstance();

    m_modelLoader.setFactory(new OBJModelFactory());
    m_sceneFolder = cSceneFolder::getInstance();

    m_projectProcessor = cProjectProcessor::getInstance();

    m_graphicsEngine = cGraphicsEngine::getInstance();
    m_inputEngine = cInputEngine::getInstance();
    m_scriptEngine = cScriptEngine::getInstance();

    connect(m_scriptEngine, &cScriptEngine::updateGraphics, this, &cEngineCore::updateGraphics);
}

cEngineCore *cEngineCore::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new cEngineCore();
    }
    return m_instance;
}

////////////////////////////////////////////////////Graphics Engine
void cEngineCore::resizeScene(int w, int h)
{
    m_graphicsEngine->resizeScene(w,h);
    m_inputEngine->setScreenCoords(w,h);
}

void cEngineCore::paintScene()
{
    //clock_t start = clock();

    if(getCurrentScene() == nullptr) return;

    m_graphicsEngine->paintScene();
    //clock_t end = clock();
    //qDebug() << (double)(end - start) / CLOCKS_PER_SEC;
}

void cEngineCore::initGraphicsEngine()
{
    m_graphicsEngine->initGraphics();
    //m_projectProcessor->saveProject("", m_sceneFolder->scenes(), "project");
    //m_projectProcessor->loadProject("project.uupj");
    //m_scriptEngine->loadScript(m_sceneFolder->object("Golem"));
}

//scene work

void cEngineCore::createScene(const QString &sceneName)
{
    m_sceneFolder->createScene(sceneName);
    m_graphicsEngine->setCurrentScene(getCurrentScene());
}

void cEngineCore::selectCurrentScene(const QString &sceneName)
{
    m_graphicsEngine->setCurrentScene(m_sceneFolder->setCurrentScene(sceneName));
    emit updateGraphics();
}

cScene *cEngineCore::getCurrentScene()
{
    return m_sceneFolder->currentScene();
}


void cEngineCore::translateObject(const QString &objectName, const QVector3D &translation)
{
    getCurrentScene()->gameObject(objectName)->
        translate(translation - QVector3D(getCurrentScene()->gameObject(objectName)->coordinates()));
}

void cEngineCore::rotateXObject(const QString &objectName, const QQuaternion &rotation)
{
    getCurrentScene()->gameObject(objectName)->
        rotateX(rotation - QQuaternion(getCurrentScene()->gameObject(objectName)->rotationX()));
}

void cEngineCore::rotateYObject(const QString &objectName, const QQuaternion &rotation)
{
    getCurrentScene()->gameObject(objectName)->
        rotateY(rotation - QQuaternion(getCurrentScene()->gameObject(objectName)->rotationY()));
}

void cEngineCore::scaleObject(const QString &objectName, const float &scale)
{
    getCurrentScene()->gameObject(objectName)->
        setScale(getCurrentScene()->gameObject(objectName)->scale() - scale);
}

void cEngineCore::deleteObject(const QString &objectName)
{
    getCurrentScene()->deleteGameObject(objectName);
    emit updateGraphics();
}

void cEngineCore::setNormalTexture(const QString &objectName, const QString &path)
{
    auto model = dynamic_cast<cSimpleModel *>(getCurrentScene()->gameObject(objectName)->model());

    if(model->modelType() == cModel::ModelType::CustomModel) return;

    model->modelParticle()->setNormalMap(path);
    loadTexture(objectName, path);
}

void cEngineCore::setDiffuseTexture(const QString &objectName, const QString &path)
{

    auto model = dynamic_cast<cSimpleModel *>(getCurrentScene()->gameObject(objectName)->model());

    if(model->modelType() == cModel::ModelType::CustomModel) return;

    model->modelParticle()->setDiffuseMap(path);
    loadTexture(objectName, path);
}


bool cEngineCore::createOBJModel(const QString &objectName, const QString &path)
{
    m_modelLoader.setFactory(new OBJModelFactory);
    if(!getCurrentScene()->addGameObject(objectName, m_modelLoader.createModel(path)))
        return false;

    m_modelFolder->append(objectName, path.split('/').constLast());
    placeObjectOnMousePosition(objectName);
    return true;
}

bool cEngineCore::createFBXModel(const QString &objectName, const QString &path)
{
    m_modelLoader.setFactory(new FBXModelFactory);
    if(!getCurrentScene()->addGameObject(objectName, m_modelLoader.createModel(path)))
        return false;

    m_modelFolder->append(objectName, path.split('/').constLast());
    placeObjectOnMousePosition(objectName);
    return true;
}

void cEngineCore::createCameraInScene(const QString &objectName)
{
    getCurrentScene()->addCamera(objectName);
    getCurrentScene()->camera(objectName)->
        setCoordinates(m_inputEngine->getWorldCoordinates(m_graphicsEngine->projectionMatrix(),
                                                          m_graphicsEngine->cameraViewMatrix()));
    emit updateGraphics();
}

void cEngineCore::createLightingInScene(const QString &objectName)
{
    getCurrentScene()->addLighting(objectName);
    getCurrentScene()->lighting(objectName)->
        setCoordinates(m_inputEngine->getWorldCoordinates(m_graphicsEngine->projectionMatrix(),
                                                          m_graphicsEngine->cameraViewMatrix()));
    emit updateGraphics();
}

void cEngineCore::setSkyBox(const float &size, const QString &path)
{
    getCurrentScene()->setSkybox(m_modelBuilder.createSkybox(size, path));
    loadTexture("Skybox", path);

    emit updateGraphics();
}

bool cEngineCore::createCube(const QString &objectName, const float &width, const float &height, const float &depth)
{
    if(!getCurrentScene()->addGameObject(objectName, m_modelBuilder.createCube(width, height, depth)))
        return false;

    m_modelFolder->replace(objectName, QString("CUBE(%1 %2 %3)").arg(width).arg(height).arg(depth));
    placeObjectOnMousePosition(objectName);
    return true;
}

void cEngineCore::createPyramide(const QString &objectName, const float &width, const float &height)
{
    getCurrentScene()->addGameObject(objectName, m_modelBuilder.createPyramide(width, height));
    m_modelFolder->replace(objectName, QString("PYRAMID(%1 %2)").arg(width).arg(height));
    placeObjectOnMousePosition(objectName);
}

bool cEngineCore::createSphere(const QString &objectName, const float &radius, const int &stacks, const int &sectors)
{
    if(!getCurrentScene()->addGameObject(objectName, m_modelBuilder.createSphere(radius,stacks, sectors)))
        return false;

    m_modelFolder->replace(objectName, QString("SPHERE(%1 %2 %3)").arg(radius).arg(stacks).arg(sectors));
    placeObjectOnMousePosition(objectName);
    return true;
}

void cEngineCore::createPrism(const QString &objectName, const float &width, const float &height, const float &depth, const float &angle)
{
    getCurrentScene()->addGameObject(objectName, m_modelBuilder.createPrism(width,height, depth, angle));
    m_modelFolder->replace(objectName, QString("PRISM(%1 %2 %3 %4)").arg(width).arg(height).arg(depth).arg(angle));
    placeObjectOnMousePosition(objectName);
}

void cEngineCore::createCone(const QString &objectName, const float &width, const float &height, const int &sectors)
{
    getCurrentScene()->addGameObject(objectName, m_modelBuilder.createCone(width, height, sectors));
    m_modelFolder->replace(objectName, QString("CONE(%1 %2 %3)").arg(width).arg(height).arg(sectors));
    placeObjectOnMousePosition(objectName);
}

void cEngineCore::createCylinder(const QString &objectName, const float &width, const float &height, const int &sectors)
{
    getCurrentScene()->addGameObject(objectName, m_modelBuilder.createCylinder(width, height, sectors));
    m_modelFolder->replace(objectName, QString("CYLINDER(%1 %2 %3)").arg(width).arg(height).arg(sectors));
    placeObjectOnMousePosition(objectName);
}

void cEngineCore::changeCube(const QString &objectName, const float &width, const float &height, const float &depth)
{
    getCurrentScene()->gameObject(objectName)->setModel(m_modelBuilder.createCube(width, height, depth));
    m_modelFolder->replace(objectName, QString("CUBE(%1 %2 %3)").arg(width).arg(height).arg(depth));
    emit updateGraphics();
}

void cEngineCore::changeSphere(const QString &objectName, const float &radius, const int &rings, const int &sectors)
{
    getCurrentScene()->gameObject(objectName)->setModel(m_modelBuilder.createSphere(radius, rings, sectors));
    m_modelFolder->replace(objectName, QString("SPHERE(%1 %2 %3)").arg(radius).arg(rings).arg(sectors));
    emit updateGraphics();
}


////////////////////////////////////////////////////Input Engine

void cEngineCore::initInputEngine(const int &width, const int &height)
{
    m_inputEngine->setScreenCoords(width, height);
}


void cEngineCore::mousePressEvent(QMouseEvent *event)
{
    m_inputEngine->mousePressEvent(event);
    emit updateGraphics();
}

void cEngineCore::mouseMoveEvent(QMouseEvent *event)
{
    m_inputEngine->mouseMoveEvent(event);
    m_graphicsEngine->rotateModelViewMatrix(m_inputEngine->getRotateX(), m_inputEngine->getRotateY());
    emit updateGraphics();
}

void cEngineCore::wheelEvent(QWheelEvent *event)
{
    m_inputEngine->wheelEvent(event);
    m_graphicsEngine->translateModelViewMatrix(m_inputEngine->getTranslate());
    emit updateGraphics();
}

void cEngineCore::mouseDoubleClickEvent(QMouseEvent *event)
{
    auto tmpObject = m_graphicsEngine->selectObject(event->pos());
    if(tmpObject == nullptr) return;

    auto objectName = getCurrentScene()->gameObjectsHash().key(dynamic_cast<cBase3DGameObject*>(tmpObject));
    auto object = dynamic_cast<cBase3DGameObject*>(m_graphicsEngine->selectObject(event->pos()));
    emit emitObject(objectName, &object);
    emit updateGraphics();
}

void cEngineCore::placeObjectOnMousePosition(const QString &objectName)
{
    getCurrentScene()->gameObject(objectName)->
        setCoordinates(m_inputEngine->getWorldCoordinates(m_graphicsEngine->projectionMatrix(),
                                                          m_graphicsEngine->cameraViewMatrix()));
}

void cEngineCore::changeGameStatus()
{
    m_gameStatus = !m_gameStatus;

    if(m_gameStatus){
        m_projectProcessor->saveProject(m_sceneFolder->scenes());
        m_scriptEngine->startScene(m_sceneFolder->currentScene());
    }
    else{
        m_scriptEngine->stopScene();
        m_sceneFolder->setScenes(m_projectProcessor->loadProject(cProjectInfo::projectPath()));
        m_graphicsEngine->setCurrentScene(getCurrentScene());
    }
}

void cEngineCore::updateScene()
{
    emit updateGraphics();
}


////////////////////////////////////////////////////////////Project Processor

void cEngineCore::initProjectProcessor(QVBoxLayout &layout)
{
    m_projectProcessor->setLayout(layout);
}


void cEngineCore::createProject(const QString &path, const QString &name)
{
    m_projectProcessor->createProject(path, name);
    m_sceneFolder->createScene(name);
    m_graphicsEngine->setCurrentScene(getCurrentScene());
    emit setDisableState(false);
}


void cEngineCore::loadProject(const QString &path)
{
    m_sceneFolder->setScenes(m_projectProcessor->loadProject(path));
    m_graphicsEngine->setCurrentScene(getCurrentScene());
    emit setDisableState(false);

}

void cEngineCore::saveProject(const QString &path, const QString &projectName)
{
    if(path == "" && cProjectInfo::projectPath() != "" && m_sceneFolder->scenes().size() > 0){
        m_projectProcessor->saveProject(m_sceneFolder->scenes());
    }
    else{
        m_projectProcessor->saveProject(m_sceneFolder->scenes(),path);
    }
}

void cEngineCore::closeProject()
{
    m_projectProcessor->closeProject(m_sceneFolder->scenes());
    m_sceneFolder->clearFolder();
    emit updateGraphics();
    emit setDisableState(true);
}

void cEngineCore::loadModel(const QString &objectName, const QString &path)
{
    m_modelFolder->replace(objectName, path);
}

void cEngineCore::loadTexture(const QString &objectName, const QString &path)
{
    m_textureFolder->replace(objectName, cProjectInfo::projectFolder() + "/Textures/" + path.split('/').constLast());
    cProjectInfo::copyToTextures(path);
}

void cEngineCore::loadScript(const QString &objectName, const QString &path)
{
    m_scriptFolder->addScript(objectName, path.split('/').constLast());
    cProjectInfo::copyToScripts(path);
}

QString cEngineCore::getModel(const QString &objectName)
{
    return m_modelFolder->model(objectName);
}

QVector<QString> cEngineCore::getScripts(const QString &objectName)
{
    return m_scriptFolder->scripts(objectName);
}
