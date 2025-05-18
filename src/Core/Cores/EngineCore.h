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
class cTextureManager;

class QOpenGLWidget;
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
    std::unique_ptr<cTextureManager> m_textureManager;

    cModelLoader m_modelLoader;
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
    void initGraphicsEngine(QOpenGLWidget* widget);

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
    void createScene(const std::string& name);
    void createCameraInScene(const std::string& name);
    void createLightingInScene(const std::string& name);
    void createSkyBox(const std::string& name, const std::string &path, float size = 100.0f);

    void selectCurrentScene(const std::string& sceneName);
    inline cScene *getCurrentScene();

public:
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
    bool createCustomModelObject(uint32_t hash, std::string_view path);
    bool createBaseFigureObject(uint32_t hash, cModelBuilder::Base3DFiguresType figureType);

private:
    bool m_gameStatus = false;

signals:
    void setDisableState(bool state);
    void emitObject(uint32_t hash, cBase3DGameObject **object);

private:
    QOpenGLWidget* m_openGLWidget;

private:
    static std::shared_ptr<cEngineCore> m_instance;
};

#endif // ENGINECORE_H
