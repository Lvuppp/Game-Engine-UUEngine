#ifndef ENGINECORE_H
#define ENGINECORE_H

#include "Core/Cores/GraphicsEngine.h"
#include "Core/Cores/PhysicsEngine.h"
#include "Core/Cores/ScriptEngine.h"
#include "Core/Cores/InputEngine.h"
#include "Core/Services/ModelLoader.h"
#include "Core/Services/ModelBuilder.h"
#include "Core/Services/ProjectProcessor.h"
#include "Utils/Vectors.h"

#include <QVBoxLayout>

class cGraphicsEngine;
class cInputEngine;
class cPhysicsEngine;
class cProjectProcessor;
class cScriptEngine;

class cEngineCore : public QObject
{
    Q_OBJECT

public:
    cEngineCore();
    ~cEngineCore() = default;

    cEngineCore(const cEngineCore& core) = delete;
    cEngineCore& operator=(const cEngineCore& core) = delete;

public:
    void initInputEngine(sVec2 size);
    void initProjectProcessor(QVBoxLayout &layout);
    void initGraphicsEngine();

    void update(float dt);
    void render();
    void resizeScene(int w, int h);

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
    void setSkyBox(const float &size, const std::string& path);

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

    const std::string& getModel(uint32_t hash);
    std::vector<std::string> getScripts(uint32_t hash);

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
    std::unique_ptr<cGraphicsEngine> m_graphicsEngine = nullptr;
    std::unique_ptr<cPhysicsEngine> m_phyicsEngine = nullptr;
    std::unique_ptr<cScriptEngine> m_scriptEngine = nullptr;
    std::unique_ptr<cInputEngine> m_inputEngine = nullptr;

    std::unique_ptr<cProjectProcessor> m_projectProcessor = nullptr;

    std::unique_ptr<cSceneManager> m_sceneManager = nullptr;
    std::unique_ptr<cModelFolder> m_modelFolder = nullptr;
    std::unique_ptr<cScriptFolder> m_scriptFolder = nullptr;
    std::unique_ptr<cTextureFolder> m_textureFolder = nullptr;

    cModelLoader m_modelLoader;
    cModelBuilder m_modelBuilder;
};

#endif // ENGINECORE_H
