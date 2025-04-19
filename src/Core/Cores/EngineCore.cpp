#include "EngineCore.h"

#include "Core/Folders/ScriptFolder.h"

cEngineCore::cEngineCore()
{
    // TODO: make engine context
    m_modelFolder.reset(new cModelFolder());
    m_scriptFolder.reset(new cScriptFolder());
    m_textureFolder.reset(new cTextureFolder());

    m_modelLoader.setFactory(new OBJModelFactory());
    m_sceneFolder.reset(new cSceneFolder());

    m_projectProcessor.reset(new cProjectProcessor());

    m_scriptEngine.reset(new cScriptEngine());
}

void cEngineCore::initGraphicsEngine()
{
    m_graphicsEngine.reset(new cGraphicsEngine());
    m_graphicsEngine->initGraphics();
}

void cEngineCore::initInputEngine(sVec2 size)
{
    m_inputEngine.reset(new cInputEngine());
    m_inputEngine->setScreenCoords(size);
}

void cEngineCore::update(float dt)
{

}

void cEngineCore::render()
{
    m_graphicsEngine->render();
}

void cEngineCore::resizeScene(int w, int h)
{
    m_graphicsEngine->resizeScene(w, h);
    m_inputEngine->setScreenCoords(sVec2(w, h ));
}

void cEngineCore::createScene(const std::string &sceneName)
{
    m_sceneFolder->createScene(sceneName);
    m_graphicsEngine->setCurrentScene(getCurrentScene());
}

void cEngineCore::selectCurrentScene(const std::string &sceneName)
{
    m_graphicsEngine->setCurrentScene(m_sceneFolder->setCurrentScene(sceneName));

}

cScene *cEngineCore::getCurrentScene()
{
    return m_sceneFolder->currentScene();
}

void cEngineCore::translateObject(const std::string &objectName, const QVector3D &translation)
{
    getCurrentScene()->gameObject(objectName)->
        translate(translation - QVector3D(getCurrentScene()->gameObject(objectName)->coordinates()));
}

void cEngineCore::rotateXObject(const std::string &objectName, const QQuaternion &rotation)
{
    getCurrentScene()->gameObject(objectName)->
        rotateX(rotation - QQuaternion(getCurrentScene()->gameObject(objectName)->rotationX()));
}

void cEngineCore::rotateYObject(const std::string &objectName, const QQuaternion &rotation)
{
    getCurrentScene()->gameObject(objectName)->
        rotateY(rotation - QQuaternion(getCurrentScene()->gameObject(objectName)->rotationY()));
}

void cEngineCore::scaleObject(const std::string &objectName, const float &scale)
{
    getCurrentScene()->gameObject(objectName)->
        setScale(getCurrentScene()->gameObject(objectName)->scale() - scale);
}

void cEngineCore::deleteObject(const std::string &objectName)
{
    getCurrentScene()->deleteGameObject(objectName);
}

void cEngineCore::setNormalTexture(const std::string &objectName, const std::string &path)
{
    auto model = getCurrentScene()->gameObject(objectName)->model();

    model->setNormalMap(path);
    loadTexture(objectName, path);
}

void cEngineCore::setDiffuseTexture(const std::string &objectName, const std::string &path)
{
    auto model = getCurrentScene()->gameObject(objectName)->model();
    model->setDiffuseMap(path);
}


bool cEngineCore::createOBJModel(const std::string &objectName, const std::string &path)
{
    m_modelLoader.setFactory(new OBJModelFactory);
    if(!getCurrentScene()->addGameObject(objectName, m_modelLoader.createModel(path)))
        return false;

    m_modelFolder->append(objectName, path.substr(path.find_last_of('/') + 1));
    placeObjectOnMousePosition(objectName);
    return true;
}

bool cEngineCore::createFBXModel(const std::string &objectName, const std::string &path)
{
    m_modelLoader.setFactory(new FBXModelFactory);
    if(!getCurrentScene()->addGameObject(objectName, m_modelLoader.createModel(path)))
        return false;

    m_modelFolder->append(objectName, path.substr(path.find_last_of('/') + 1));
    placeObjectOnMousePosition(objectName);
    return true;
}

void cEngineCore::createCameraInScene(const std::string &objectName)
{
    getCurrentScene()->addCamera(objectName);
    getCurrentScene()->camera(objectName)->
        setCoordinates(m_inputEngine->getWorldCoordinates(m_graphicsEngine->projectionMatrix(),
                                                          m_graphicsEngine->cameraViewMatrix()));

}

void cEngineCore::createLightingInScene(const std::string &objectName)
{
    getCurrentScene()->addLighting(objectName);
    getCurrentScene()->lighting(objectName)->
        setCoordinates(m_inputEngine->getWorldCoordinates(m_graphicsEngine->projectionMatrix(),
                                                          m_graphicsEngine->cameraViewMatrix()));

}

void cEngineCore::setSkyBox(const float &size, const std::string &path)
{
    getCurrentScene()->setSkybox(m_modelBuilder.createSkybox(size, path));
    loadTexture("Skybox", path);
}

bool cEngineCore::createCube(const std::string &objectName, const float &width, const float &height, const float &depth)
{
    if(!getCurrentScene()->addGameObject(objectName, m_modelBuilder.createCube(width, height, depth)))
        return false;

    m_modelFolder->replace(objectName, "CUBE(" + std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(depth) + ")");
    placeObjectOnMousePosition(objectName);
    return true;
}

void cEngineCore::createPyramide(const std::string &objectName, const float &width, const float &height)
{
    getCurrentScene()->addGameObject(objectName, m_modelBuilder.createPyramide(width, height));
    m_modelFolder->replace(objectName, "PYRAMID(" + std::to_string(width) + " " + std::to_string(height) + ")");
    placeObjectOnMousePosition(objectName);
}

bool cEngineCore::createSphere(const std::string &objectName, const float &radius, const int &stacks, const int &sectors)
{
    if(!getCurrentScene()->addGameObject(objectName, m_modelBuilder.createSphere(radius,stacks, sectors)))
        return false;

    m_modelFolder->replace(objectName, "SPHERE(" + std::to_string(radius) + " " + std::to_string(stacks) + " " + std::to_string(sectors) + ")");
    placeObjectOnMousePosition(objectName);
    return true;
}

void cEngineCore::createPrism(const std::string &objectName, const float &width, const float &height, const float &depth, const float &angle)
{
    getCurrentScene()->addGameObject(objectName, m_modelBuilder.createPrism(width,height, depth, angle));
    m_modelFolder->replace(objectName, "PRISM(" + std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(depth) + " " + std::to_string(angle) + ")");
    placeObjectOnMousePosition(objectName);
}

void cEngineCore::createCone(const std::string &objectName, const float &width, const float &height, const int &sectors)
{
    getCurrentScene()->addGameObject(objectName, m_modelBuilder.createCone(width, height, sectors));
    m_modelFolder->replace(objectName, "CONE(" + std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(sectors) + ")");
    placeObjectOnMousePosition(objectName);
}

void cEngineCore::createCylinder(const std::string &objectName, const float &width, const float &height, const int &sectors)
{
    getCurrentScene()->addGameObject(objectName, m_modelBuilder.createCylinder(width, height, sectors));
    m_modelFolder->replace(objectName, "CYLINDER(" + std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(sectors) + ")");
    placeObjectOnMousePosition(objectName);
}

void cEngineCore::changeCube(const std::string &objectName, const float &width, const float &height, const float &depth)
{
    getCurrentScene()->gameObject(objectName)->setModel(m_modelBuilder.createCube(width, height, depth));
    m_modelFolder->replace(objectName, "CUBE(" + std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(depth) + ")");

}

void cEngineCore::changeSphere(const std::string &objectName, const float &radius, const int &rings, const int &sectors)
{
    getCurrentScene()->gameObject(objectName)->setModel(m_modelBuilder.createSphere(radius, rings, sectors));
    m_modelFolder->replace(objectName, "SPHERE(" + std::to_string(radius) + " " + std::to_string(rings) + " " + std::to_string(sectors) + ")");
}

void cEngineCore::mousePressEvent(QMouseEvent *event)
{
    m_inputEngine->mousePressEvent(event);
}

void cEngineCore::mouseMoveEvent(QMouseEvent *event)
{
    m_inputEngine->mouseMoveEvent(event);
    m_graphicsEngine->rotateModelViewMatrix(m_inputEngine->getRotateX(), m_inputEngine->getRotateY());
}

void cEngineCore::wheelEvent(QWheelEvent *event)
{
    m_inputEngine->wheelScrollEvent(event);
    m_graphicsEngine->translateModelViewMatrix(m_inputEngine->getTranslate());
}

void cEngineCore::mouseDoubleClickEvent(QMouseEvent *event)
{
    auto tmpObject = m_graphicsEngine->selectObject(event->pos());
    if(tmpObject == nullptr) return;


    auto tmp = dynamic_cast<cBase3DGameObject*>(tmpObject);
    auto objectName = getCurrentScene()->gameObjectsHash()[tmpObject.name];
    auto object = dynamic_cast<cBase3DGameObject*>(m_graphicsEngine->selectObject(event->pos()));
    emit emitObject(objectName, &object);
}

void cEngineCore::placeObjectOnMousePosition(const std::string &objectName)
{
    getCurrentScene()->gameObject(objectName)->
        setCoordinates(m_inputEngine->getWorldCoordinates(m_graphicsEngine->projectionMatrix(),
                                                          m_graphicsEngine->cameraViewMatrix()));
}

void cEngineCore::changeGameStatus()tmpObject
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

////////////////////////////////////////////////////////////Project Processor

void cEngineCore::initProjectProcessor(QVBoxLayout &layout)
{
    m_projectProcessor->setLayout(layout);
}


void cEngineCore::createProject(const std::string &path, const std::string &name)
{
    m_projectProcessor->createProject(path, name);
    m_sceneFolder->createScene(name);
    m_graphicsEngine->setCurrentScene(getCurrentScene());
    emit setDisableState(false);
}


void cEngineCore::loadProject(const std::string &path)
{
    m_sceneFolder->setScenes(m_projectProcessor->loadProject(path));
    m_graphicsEngine->setCurrentScene(getCurrentScene());
    emit setDisableState(false);

}

void cEngineCore::saveProject(const std::string &path, const std::string &projectName)
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

    emit setDisableState(true);
}

void cEngineCore::loadModel(const std::string &objectName, const std::string &path)
{
    m_modelFolder->replace(objectName, path);
}

void cEngineCore::loadTexture(const std::string &objectName, const std::string &path)
{
    m_textureFolder->replace(objectName, cProjectInfo::projectFolder() + "/Textures/" + path.substr(path.find_last_of('/') + 1));
    cProjectInfo::copyToTextures(path);
}

void cEngineCore::loadScript(const std::string &objectName, const std::string &path)
{
    m_scriptFolder->addScript(objectName, path.substr(path.find_last_of('/') + 1));
    cProjectInfo::copyToScripts(path);
}

std::string cEngineCore::getModel(const std::string &objectName)
{
    return m_modelFolder->model(objectName);
}

std::vector<std::string> cEngineCore::getScripts(const std::string &objectName)
{
    return m_scriptFolder->scripts(objectName);
}
