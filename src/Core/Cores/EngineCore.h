#ifndef ENGINECORE_H
#define ENGINECORE_H

#include "Core/Cores/GraphicsEngine.h"
#include "Core/Cores/PhysicsEngine.h"
#include "Core/Cores/ScriptEngine.h"
#include "Core/Cores/InputEngine.h"
#include "Core/Services/ModelLoader.h"
#include "Core/Services/ModelBuilder.h"
#include "Core/Services/ProjectProcessor.h"
#include "Entities/SceneFolder.h"
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
    void translateObject(const std::string &objectName, const QVector3D &translation);
    void rotateXObject(const std::string &objectName, const QQuaternion &rotation);
    void rotateYObject(const std::string &objectName, const QQuaternion &rotation);
    void scaleObject(const std::string &objectName, const float &scale);
    void deleteObject(const std::string& objectName);

    void setNormalTexture(const std::string &objectName, const std::string &path);
    void setDiffuseTexture(const std::string &objectName, const std::string &path);

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    void placeObjectOnMousePosition(const std::string &objectName);

public:
    void changeGameStatus();

public:
    void setCurrentScene(const std::string &sceneName);
    void createSimpleScene();

public:
    void createScene(const std::string &sceneName);
    void createCameraInScene(const std::string &cameraName);
    void createLightingInScene(const std::string &lightingName);
    void setSkyBox(const float &size, const std::string &path);

    void selectCurrentScene(const std::string &sceneName);
    cScene *getCurrentScene();

public slots:
    void createProject(const std::string &path, const std::string &name);
    void loadProject(const std::string & path);
    void saveProject(const std::string &path = 0, const std::string &projectName = 0);
    void closeProject();

public:
    void loadModel(const std::string &objectName, const std::string &path);
    void loadTexture(const std::string &objectName, const std::string &path);
    void loadScript(const std::string &objectName, const std::string &path);

    std::string getModel(const std::string &objectName);
    std::vector<std::string> getScripts(const std::string &objectName);

public:
    bool createOBJModel(const std::string &objectName, const std::string &modelPath);
    bool createFBXModel(const std::string &objectName, const std::string &modelPath);

public:
    bool createCube(const std::string &objectName, const float &width = 1.0f, const float &height = 1.0f, const float &depth = 1.0f);
    void createPyramide(const std::string &objectName, const float &width = 1.0f, const float &height = 1.0f);
    bool createSphere(const std::string &objectName, const float & radius = 1.0f, const int & rings = 20, const int & sectors = 20);
    void createPrism(const std::string &objectName, const float &width = 1.0f, const float &height = 1.0f, const float &depth = 1.0f, const float &angle = 1.0f);
    void createCone(const std::string &objectName, const float &width = 1.0f, const float &height = 1.0f, const int &sectors = 20);
    void createCylinder(const std::string &objectName, const float &width = 1.0f, const float &height = 1.0f, const int &sectors = 20);

    void changeCube(const std::string &objectName, const float &width, const float &height, const float &depth);
    void changeSphere(const std::string &objectName, const float & radius = 1.0f, const int & rings = 20, const int & sectors = 20);

private:
    bool m_gameStatus = false;

signals:
    void setDisableState(bool state);
    void emitObject(const std::string &objectName, cBase3DGameObject **object);

private:
    std::unique_ptr<cGraphicsEngine> m_graphicsEngine = nullptr;
    std::unique_ptr<cPhysicsEngine> m_phyicsEngine = nullptr;
    std::unique_ptr<cScriptEngine> m_scriptEngine = nullptr;
    std::unique_ptr<cInputEngine> m_inputEngine = nullptr;

    std::unique_ptr<cProjectProcessor> m_projectProcessor = nullptr;

    std::unique_ptr<cSceneFolder> m_sceneFolder = nullptr;
    std::unique_ptr<cModelFolder> m_modelFolder = nullptr;
    std::unique_ptr<cScriptFolder> m_scriptFolder = nullptr;
    std::unique_ptr<cTextureFolder> m_textureFolder = nullptr;

    cModelLoader m_modelLoader;
    cModelBuilder m_modelBuilder;
};

#endif // ENGINECORE_H
