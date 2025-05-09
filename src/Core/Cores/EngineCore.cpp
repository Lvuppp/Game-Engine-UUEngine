#include "EngineCore.h"

#include "Core/Cores/EngineContext.h"
#include "Core/Cores/GraphicsEngine.h"
#include "Core/Cores/InputEngine.h"
#include "Core/Cores/PhysicsEngine.h"
#include "Core/Cores/ScriptEngine.h"

#include "Core/Services/ModelBuilder.h"
#include "Core/Services/ModelLoader.h"
#include "Core/Services/ProjectProcessor.h"
#include "Core/Services/ProjectInfo.h"
#include "Core/Folders/SceneManager.h"

#include "Utils/Hash.h"
#include <cmath>
#include <memory>

std::shared_ptr<cEngineCore> cEngineCore::m_instance = nullptr;

cEngineContext::~cEngineContext()
{
}

cEngineCore::cEngineCore()
{
    m_graphicsEngine = std::make_unique<cGraphicsEngine>();
    m_inputEngine = std::make_unique<cInputEngine>();
    m_scriptEngine = std::make_unique<cScriptEngine>();

    m_modelFolder = std::make_unique<cBaseFolder>();
    m_scriptFolder = std::make_unique<cBaseFolder>();
    m_textureFolder = std::make_unique<cBaseFolder>();

    m_modelLoader.setFactory(new OBJModelFactory());
    m_sceneManager = std::make_unique<cSceneManager>();

    m_projectProcessor = std::make_unique<cProjectProcessor>();
}

void cEngineCore::initGraphicsEngine()
{
    m_graphicsEngine->initGraphics();
}

std::shared_ptr<cEngineCore> cEngineCore::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = std::make_shared<cEngineCore>();
    }

    return m_instance;
}

void cEngineCore::update(float dt)
{
    //updateEngineCamera();
}

void cEngineCore::render()
{
    m_graphicsEngine->render();
}

void cEngineCore::updateEngineCamera()
{
    auto inputEngine = m_inputEngine.get();

    m_engineCamera->setCoordinates(inputEngine->getTranslate());
    m_engineCamera->setRotateX(inputEngine->getRotateX());
    m_engineCamera->setRotateY(inputEngine->getRotateY());
}

void cEngineCore::resizeScene(sVec2 size)
{
    m_graphicsEngine->resizeScene(size.x, size.y);
    m_inputEngine->setScreenCoords(size);
}

void cEngineCore::createScene(uint32_t hash)
{
    m_sceneManager->createScene(hash);
    m_graphicsEngine->setCurrentScene(getCurrentScene());
}

void cEngineCore::selectCurrentScene(const std::string &sceneName)
{
    auto currentScene = m_sceneManager->setCurrentScene(cHash::hash(sceneName));
    m_graphicsEngine->setCurrentScene(currentScene.get());
}

cScene *cEngineCore::getCurrentScene()
{
    return m_sceneManager->currentScene().get();
}

void cEngineCore::translateObject(uint32_t hash, const QVector3D &translation)
{
    getCurrentScene()->gameObject(hash)->
        translate(translation - QVector3D(getCurrentScene()->gameObject(hash)->coordinates()));
}

void cEngineCore::rotateXObject(uint32_t hash, const QQuaternion &rotation)
{
    getCurrentScene()->gameObject(hash)->
        rotateX(rotation - QQuaternion(getCurrentScene()->gameObject(hash)->rotationX()));
}

void cEngineCore::rotateYObject(uint32_t hash, const QQuaternion &rotation)
{
    getCurrentScene()->gameObject(hash)->
        rotateY(rotation - QQuaternion(getCurrentScene()->gameObject(hash)->rotationY()));
}

void cEngineCore::scaleObject(uint32_t hash, const float &scale)
{
    getCurrentScene()->gameObject(hash)->
        setScale(getCurrentScene()->gameObject(hash)->scale() - scale);
}

void cEngineCore::deleteObject(uint32_t hash)
{
    getCurrentScene()->deleteGameObject(hash);
}

void cEngineCore::setNormalTexture(uint32_t hash, const std::string& path)
{
    auto model = getCurrentScene()->gameObject(hash)->model();

    model->setNormalMap(path);
    loadTexture(hash, path);
}

void cEngineCore::setDiffuseTexture(uint32_t hash, const std::string& path)
{
    auto model = getCurrentScene()->gameObject(hash)->model();
    model->setDiffuseMap(path);
}


bool cEngineCore::createOBJModel(uint32_t hash, const std::string& path)
{
    m_modelLoader.setFactory(new OBJModelFactory);
    if(!getCurrentScene()->addGameObject(hash, m_modelLoader.createModel(path)))
        return false;

    m_modelFolder->append(hash, path.substr(path.find_last_of('/') + 1));
    placeObjectOnMousePosition(hash);
    return true;
}

bool cEngineCore::createFBXModel(uint32_t hash, const std::string& path)
{
    m_modelLoader.setFactory(new FBXModelFactory);
    if(!getCurrentScene()->addGameObject(hash, m_modelLoader.createModel(path)))
        return false;

    m_modelFolder->append(hash, path.substr(path.find_last_of('/') + 1));
    placeObjectOnMousePosition(hash);
    return true;
}

void cEngineCore::createCameraInScene(uint32_t hash)
{
    getCurrentScene()->addCamera(hash);
    getCurrentScene()->camera(hash)->
        setCoordinates(m_inputEngine->getWorldCoordinates(m_graphicsEngine->projectionMatrix(),
                                                          m_graphicsEngine->cameraViewMatrix()));

}

void cEngineCore::createLightingInScene(uint32_t hash)
{
    getCurrentScene()->addLighting(hash);
    getCurrentScene()->lighting(hash)->
        setCoordinates(m_inputEngine->getWorldCoordinates(m_graphicsEngine->projectionMatrix(),
                                                          m_graphicsEngine->cameraViewMatrix()));

}

void cEngineCore::createSkyBox(const float &size, const std::string &path)
{
    getCurrentScene()->setSkybox(m_modelBuilder.createSkybox(size, path));
    loadTexture("Skybox"_hash, path);
}

bool cEngineCore::createCube(uint32_t hash, const float &width, const float &height, const float &depth)
{
    if(!getCurrentScene()->addGameObject(hash, m_modelBuilder.createCube(width, height, depth)))
        return false;

    m_modelFolder->replace(hash, "CUBE(" + std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(depth) + ")");
    placeObjectOnMousePosition(hash);
    return true;
}

void cEngineCore::createPyramide(uint32_t hash, const float &width, const float &height)
{
    getCurrentScene()->addGameObject(hash, m_modelBuilder.createPyramide(width, height));
    m_modelFolder->replace(hash, "PYRAMID(" + std::to_string(width) + " " + std::to_string(height) + ")");
    placeObjectOnMousePosition(hash);
}

bool cEngineCore::createSphere(uint32_t hash, const float &radius, const int &stacks, const int &sectors)
{
    if(!getCurrentScene()->addGameObject(hash, m_modelBuilder.createSphere(radius,stacks, sectors)))
        return false;

    m_modelFolder->replace(hash, "SPHERE(" + std::to_string(radius) + " " + std::to_string(stacks) + " " + std::to_string(sectors) + ")");
    placeObjectOnMousePosition(hash);
    return true;
}

void cEngineCore::createPrism(uint32_t hash, const float &width, const float &height, const float &depth, const float &angle)
{
    getCurrentScene()->addGameObject(hash, m_modelBuilder.createPrism(width,height, depth, angle));
    m_modelFolder->replace(hash, "PRISM(" + std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(depth) + " " + std::to_string(angle) + ")");
    placeObjectOnMousePosition(hash);
}

void cEngineCore::createCone(uint32_t hash, const float &width, const float &height, const int &sectors)
{
    getCurrentScene()->addGameObject(hash, m_modelBuilder.createCone(width, height, sectors));
    m_modelFolder->replace(hash, "CONE(" + std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(sectors) + ")");
    placeObjectOnMousePosition(hash);
}

void cEngineCore::createCylinder(uint32_t hash, const float &width, const float &height, const int &sectors)
{
    getCurrentScene()->addGameObject(hash, m_modelBuilder.createCylinder(width, height, sectors));
    m_modelFolder->replace(hash, "CYLINDER(" + std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(sectors) + ")");
    placeObjectOnMousePosition(hash);
}

void cEngineCore::changeCube(uint32_t hash, const float &width, const float &height, const float &depth)
{
    getCurrentScene()->gameObject(hash)->setModel(m_modelBuilder.createCube(width, height, depth));
    m_modelFolder->replace(hash, "CUBE(" + std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(depth) + ")");

}

void cEngineCore::changeSphere(uint32_t hash, const float &radius, const int &rings, const int &sectors)
{
    getCurrentScene()->gameObject(hash)->setModel(m_modelBuilder.createSphere(radius, rings, sectors));
    m_modelFolder->replace(hash, "SPHERE(" + std::to_string(radius) + " " + std::to_string(rings) + " " + std::to_string(sectors) + ")");
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
    // auto object = dynamic_cast<cBase3DGameObject*>(m_graphicsEngine->selectObject(event->pos()));
    // emit emitObject(object->hash, &object);
}

void cEngineCore::placeObjectOnMousePosition(uint32_t hash)
{
    getCurrentScene()->gameObject(hash)->
        setCoordinates(m_inputEngine->getWorldCoordinates(m_graphicsEngine->projectionMatrix(),
                                                          m_graphicsEngine->cameraViewMatrix()));
}

void cEngineCore::changeGameStatus()
{
    m_gameStatus = !m_gameStatus;

    if (m_gameStatus)
    {
        //m_projectProcessor->saveProject(m_sceneManager->scenes());
        m_scriptEngine->startScene(m_sceneManager->currentScene().get());
    }
    else
    {
        m_scriptEngine->stopScene();
        //m_sceneManager->setScenes(m_projectProcessor->loadProject(cProjectInfo::projectPath()));
        m_graphicsEngine->setCurrentScene(getCurrentScene());
    }
}

////////////////////////////////////////////////////////////Project Processor

void cEngineCore::initProjectProcessor(QVBoxLayout &layout)
{
    //m_projectProcessor->setLayout(layout);
}


void cEngineCore::createProject(const std::string &path, const std::string &name)
{
    //m_projectProcessor->createProject(path, name);
    m_sceneManager->createScene(cHash::hash(name));
    m_graphicsEngine->setCurrentScene(getCurrentScene());
    emit setDisableState(false);
}


void cEngineCore::loadProject(const std::string &path)
{
    //m_sceneManager->setScenes(m_projectProcessor->loadProject(path));
    m_graphicsEngine->setCurrentScene(getCurrentScene());
    emit setDisableState(false);

}

void cEngineCore::saveProject(const std::string &path, const std::string &projectName)
{
    // if(path == "" && cProjectInfo::projectPath() != "" && m_sceneManager->scenes().size() > 0){
    //     m_projectProcessor->saveProject(m_sceneManager->scenes());
    // }
    // else{
    //     m_projectProcessor->saveProject(m_sceneManager->scenes(),path);
    // }
}

void cEngineCore::closeProject()
{
    //m_projectProcessor->closeProject(m_sceneManager->scenes());
    m_sceneManager->clearFolder();

    emit setDisableState(true);
}

void cEngineCore::loadModel(uint32_t hash, const std::string &path)
{
    m_modelFolder->replace(hash, path);
}

void cEngineCore::loadTexture(uint32_t hash, const std::string &path)
{
    m_textureFolder->replace(hash, cProjectInfo::projectFolder() + "/Textures/" + path.substr(path.find_last_of('/') + 1));
    cProjectInfo::copyToTextures(path);
}

void cEngineCore::loadScript(uint32_t hash, const std::string &path)
{
    m_scriptFolder->append(hash, path.substr(path.find_last_of('/') + 1));
    cProjectInfo::copyToScripts(path);
}

std::string_view cEngineCore::getModel(uint32_t hash)
{
    return m_modelFolder->getFile(hash);
}

std::vector<std::string_view> cEngineCore::getScripts(uint32_t hash)
{
    return m_scriptFolder->getFiles();
}
