#include "EngineCore.h"

#include "Core/Cores/GraphicsEngine.h"
#include "Core/Cores/InputEngine.h"
#include "Core/Cores/PhysicsEngine.h"
#include "Core/Cores/ScriptEngine.h"

#include "Core/Folders/TextureFolder.h"
#include "Core/Services/ModelBuilder.h"
#include "Core/Services/ModelLoader.h"
#include "Core/Services/ProjectProcessor.h"
#include "Core/Services/ProjectInfo.h"
#include "Core/Folders/SceneManager.h"

#include "Utils/Hash.h"

#include <cmath>
#include <memory>

#include <QOpenGLWidget>

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
    m_textureManager = std::make_unique<cTextureManager>();

    m_modelLoader.setFactory(new OBJModelFactory(m_textureManager.get()));
    m_sceneManager = std::make_unique<cSceneManager>();

    m_projectProcessor = std::make_unique<cProjectProcessor>(m_sceneManager.get(), m_textureManager.get());

    createScene("DefaultScene");
    auto currentScene = getCurrentScene();
}

void cEngineCore::initGraphicsEngine(QOpenGLWidget *openGLWidget)
{
    m_graphicsEngine->initGraphics();
    m_openGLWidget = openGLWidget;
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
    updateEngineCamera();
}

void cEngineCore::render()
{
    m_graphicsEngine->render();
    //m_graphicsEngine->testShaders();
}

void cEngineCore::updateEngineCamera()
{
    auto currentScene = getCurrentScene();
    auto engineCamera = currentScene->getCurrentCamera();

    engineCamera->translate(m_inputEngine->getTranslate());
    engineCamera->rotateX(m_inputEngine->getRotateX());
    engineCamera->rotateY(m_inputEngine->getRotateY());
}

void cEngineCore::resizeScene(sVec2 size)
{
    m_graphicsEngine->resizeScene(size.x, size.y);
    m_inputEngine->setScreenCoords(size);
}

void cEngineCore::createScene(const std::string& name)
{
    m_sceneManager->createScene(name);
    m_graphicsEngine->setCurrentScene(getCurrentScene());
}

void cEngineCore::selectCurrentScene(const std::string &sceneName)
{
    auto currentScene = m_sceneManager->setCurrentScene(sceneName);
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

    auto texture = m_textureManager->loadTexture(path);
    model->setNormalMap(texture);
}

void cEngineCore::setDiffuseTexture(uint32_t hash, const std::string& path)
{
    auto model = getCurrentScene()->gameObject(hash)->model();
    auto texture = m_textureManager->loadTexture(path);
    model->setDiffuseMap(texture);
}

bool cEngineCore::createOBJModel(uint32_t hash, const std::string& path)
{
    m_modelLoader.setFactory(new OBJModelFactory(m_textureManager.get()));
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

void cEngineCore::createCameraInScene(const std::string& name)
{
    /* getCurrentScene()->addCamera(hash);
    getCurrentScene()->camera(hash)->
        setCoordinates(m_inputEngine->getWorldCoordinates(m_graphicsEngine->projectionMatrix(),
                                                          m_graphicsEngine->cameraViewMatrix()));
 */
}

void cEngineCore::createLightingInScene(const std::string& name)
{
    /* getCurrentScene()->addLighting(hash);
    getCurrentScene()->lighting(hash)->
        setCoordinates(m_inputEngine->getWorldCoordinates(m_graphicsEngine->projectionMatrix(),
                                                          m_graphicsEngine->cameraViewMatrix()));
 */
}

    void cEngineCore::createSkyBox(const std::string& name, const std::string &path, float size)
{
    auto currentScene = m_sceneManager->currentScene();
    auto texture = m_textureManager->loadTexture(path);
    cModelBuilder modelBuilder;
    currentScene->addSkyBox(cHash::hash(name), modelBuilder.createSkybox(size, texture));
}

bool cEngineCore::createCustomModelObject(uint32_t hash, std::string_view path)
{
    auto currentScene = getCurrentScene();
    auto model = m_modelLoader.createModel(path.data());

    auto createdObject = currentScene->addGameObject(hash, model);

    if (createdObject == nullptr)
    {
        return false;
    }

    const auto& projectionMatrix = m_graphicsEngine->getProjectionMatrix();
    const auto& viewMatrix = currentScene->getCurrentCamera()->modelMatrix();
    const auto coords = m_inputEngine->getWorldCoordinates(projectionMatrix, viewMatrix, 0.0f);
    createdObject->setCoordinates(coords);

    return true;
}

bool cEngineCore::createBaseFigureObject(uint32_t hash, cModelBuilder::Base3DFiguresType figureType)
{
    auto currentScene = getCurrentScene();
    if (currentScene == nullptr)
    {
        return false;
    }

    cModelBuilder modelBuilder;
    const auto model = modelBuilder.createBaseFigure(figureType);
    const auto texture = m_textureManager->loadTexture("/home/egor/photo.jpg");

    model->setDiffuseMap(texture);
    auto createdObject = currentScene->addGameObject(hash, model);

    if (createdObject == nullptr)
    {
        return false;
    }

    const auto& projectionMatrix = m_graphicsEngine->getProjectionMatrix();
    const auto& viewMatrix = currentScene->getCurrentCamera()->modelMatrix();
    const auto coords = m_inputEngine->getWorldCoordinates(projectionMatrix, viewMatrix, 0.0f);
    createdObject->setCoordinates(coords);

    return true;
}

void cEngineCore::mousePressEvent(QMouseEvent *event)
{
    m_inputEngine->mousePressEvent(event);
}

void cEngineCore::mouseMoveEvent(QMouseEvent *event)
{
    auto currentScene = getCurrentScene();
    auto engineCamera = currentScene->getCurrentCamera();

    engineCamera->rotateX(m_inputEngine->getRotateX());
    engineCamera->rotateY(m_inputEngine->getRotateY());
}

void cEngineCore::wheelEvent(QWheelEvent *event)
{
    auto currentScene = getCurrentScene();
    auto engineCamera = currentScene->getCurrentCamera();

    engineCamera->translate(m_inputEngine->getTranslate());
}

void cEngineCore::mouseDoubleClickEvent(QMouseEvent *event)
{
    auto currentScene = getCurrentScene();
    auto engineCamera = currentScene->getCurrentCamera();

    engineCamera->translate(m_inputEngine->getTranslate());
    engineCamera->rotateX(m_inputEngine->getRotateX());
    engineCamera->rotateY(m_inputEngine->getRotateY());
}

void cEngineCore::placeObjectOnMousePosition(uint32_t hash)
{
    /* getCurrentScene()->gameObject(hash)->
        setCoordinates(m_inputEngine->getWorldCoordinates(m_graphicsEngine->projectionMatrix(),
                                                          m_graphicsEngine->cameraViewMatrix()));
 */}

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

void cEngineCore::initProjectProcessor(QVBoxLayout& layout)
{
    //m_projectProcessor->setLayout(layout);
}

void cEngineCore::createProject(const std::string& path, const std::string& name)
{
    m_projectProcessor->createProject(path, name);
}

void cEngineCore::loadProject(const std::string &path)
{
    //m_sceneManager->setScenes(m_projectProcessor->loadProject(path));
    m_graphicsEngine->setCurrentScene(getCurrentScene());
    emit setDisableState(false);

}

void cEngineCore::saveProject(const std::string &path, const std::string &projectName)
{
    // if (path.empty())
    // {
    //     m_projectProcessor->saveProject(m_sceneManager->scenes());
    // }
    // else
    // {
    //     m_projectProcessor->saveProject(m_sceneManager->scenes(), path);
    // }
}

void cEngineCore::closeProject()
{
    //m_projectProcessor->closeProject(m_sceneManager->scenes());
    m_sceneManager->clearFolder();
}

void cEngineCore::loadModel(uint32_t hash, const std::string &path)
{
    m_modelFolder->replace(hash, path);
}

void cEngineCore::loadTexture(uint32_t hash, const std::string &path)
{
    //m_textureManager->replace(hash, cProjectInfo::projectFolder() + "/Textures/" + path.substr(path.find_last_of('/') + 1));
}

void cEngineCore::loadScript(uint32_t hash, const std::string &path)
{
    m_scriptFolder->append(hash, path.substr(path.find_last_of('/') + 1));
}

std::string_view cEngineCore::getModel(uint32_t hash)
{
    return m_modelFolder->getFile(hash);
}

std::vector<std::string_view> cEngineCore::getScripts(uint32_t hash)
{
    return m_scriptFolder->getFiles();
}
