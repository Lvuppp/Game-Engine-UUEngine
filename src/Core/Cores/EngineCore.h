#ifndef ENGINECORE_H
#define ENGINECORE_H


#include "Core/Folders/BaseFolder.h"
#include "Core/Services/ModelBuilder.h"
#include "Core/Services/ModelLoader.h"
#include "Entities/BaseEntities/Base3DGameObject.h"
#include "Entities/BaseEntities/Camera.h"
#include "Entities/BaseEntities/Lighting.h"
#include "Utils/Vectors.h"

#include <memory>

#include <QVBoxLayout>

class cCamera;
class cGraphicsEngine;
class cInputEngine;
class cLighting;
class cPhysicsEngine;
class cProjectProcessor;
class cSceneManager;
class cModelFolder;
class cScene;
class cScriptEngine;
class cScriptFolder;
class cTextureFolder;

class QMouseEvent;
class QWheelEvent;

class cEngineContext
{
public:
    ~cEngineContext();

    std::unique_ptr<cGraphicsEngine> m_graphicsEngine;
    std::unique_ptr<cPhysicsEngine> m_phyicsEngine;
    std::unique_ptr<cScriptEngine> m_scriptEngine;
    std::unique_ptr<cInputEngine> m_inputEngine;
    std::unique_ptr<cProjectProcessor> m_projectProcessor;
    std::unique_ptr<cSceneManager> m_sceneManager;
    std::unique_ptr<cBaseFolder> m_modelFolder;
    std::unique_ptr<cBaseFolder> m_scriptFolder;
    std::unique_ptr<cBaseFolder> m_textureFolder;

    cModelLoader m_modelLoader;
    cModelBuilder m_modelBuilder;
};

class cEngineCore final : public QObject, public cEngineContext
{
    Q_OBJECT

public:
    cEngineCore();

    cEngineCore(const cEngineCore& core) = delete;
    cEngineCore& operator=(const cEngineCore& core) = delete;

    static std::shared_ptr<cEngineCore> getInstance();

public:
    void initInputEngine(sVec2 size);
    void initProjectProcessor(QVBoxLayout &layout);
    void initGraphicsEngine();

    void update(float dt);
    void render();
    void resizeScene(sVec2 size);

    void updateEngineCamera();
    void updateEngineLightning();

public:
    void translateObject(uint32_t hash, const QVector3D &translation);
    void rotateXObject(uint32_t hash, const QQuaternion &rotation);
    void rotateYObject(uint32_t hash, const QQuaternion &rotation);
    void scaleObject(uint32_t hash, const float &scale);
    void deleteObject(uint32_t hash);

    void setNormalTexture(uint32_t hash, const std::string& path);
    void setDiffuseTexture(uint32_t hash, const std::string& path);

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    void placeObjectOnMousePosition(uint32_t hash);

public:
    void changeGameStatus();

public:
    void setCurrentScene(const std::string& sceneName);
    void createSimpleScene();

public:
    void createScene(uint32_t hash);
    void createCameraInScene(uint32_t hash);
    void createLightingInScene(uint32_t hash);
    void createSkyBox(const float &size, const std::string& path);

    void selectCurrentScene(const std::string& sceneName);
    cScene *getCurrentScene();

public slots:
    void createProject(const std::string& path, const std::string &name);
    void loadProject(const std::string& path);
    void saveProject(const std::string& path = 0, const std::string& projectName = 0);
    void closeProject();

public:
    void loadModel(uint32_t hash, const std::string& path);
    void loadTexture(uint32_t hash, const std::string& path);
    void loadScript(uint32_t hash, const std::string& path);

    std::string_view getModel(uint32_t hash);
    std::vector<std::string_view> getScripts(uint32_t hash);

public:
    bool createOBJModel(uint32_t hash, const std::string& modelPath);
    bool createFBXModel(uint32_t hash, const std::string& modelPath);

public:
    bool createCube(uint32_t hash, const float &width = 1.0f, const float &height = 1.0f, const float &depth = 1.0f);
    void createPyramide(uint32_t hash, const float &width = 1.0f, const float &height = 1.0f);
    bool createSphere(uint32_t hash, const float & radius = 1.0f, const int & rings = 20, const int & sectors = 20);
    void createPrism(uint32_t hash, const float &width = 1.0f, const float &height = 1.0f, const float &depth = 1.0f, const float &angle = 1.0f);
    void createCone(uint32_t hash, const float &width = 1.0f, const float &height = 1.0f, const int &sectors = 20);
    void createCylinder(uint32_t hash, const float &width = 1.0f, const float &height = 1.0f, const int &sectors = 20);

    void changeCube(uint32_t hash, const float &width, const float &height, const float &depth);
    void changeSphere(uint32_t hash, const float & radius = 1.0f, const int & rings = 20, const int & sectors = 20);

private:
    bool m_gameStatus = false;

signals:
    void setDisableState(bool state);
    void emitObject(uint32_t hash, cBase3DGameObject **object);

private:
    std::unique_ptr<cCamera> m_engineCamera = nullptr;
    std::unique_ptr<cLighting> m_engineLighting = nullptr;

private:
    static std::shared_ptr<cEngineCore> m_instance;
};

#endif // ENGINECORE_H
