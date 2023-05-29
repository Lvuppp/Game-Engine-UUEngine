#ifndef ENGINECORE_H
#define ENGINECORE_H

#include "graphicsengine.h"
#include "physicsengine.h"
#include "scriptengine.h"
#include "inputengine.h"
#include "Folders/scenefolder.h"
#include "Services/modelloader.h"
#include "Services/modelbuilder.h"
#include "Services/projectprocessor.h"

#include <QVBoxLayout>
//#include"camera.h"

class EngineCore : public QObject
{
    Q_OBJECT

public:
// intitializing of all engine parts
    void initGraphicsEngine();
    void initPhysicsEngine();
    void initScriptEngine();
    void initInputEngine(const int &width, const int &height);
    void initProjectProcessor(QVBoxLayout &layout);

    static EngineCore *getInstance();

//graphics engine part
public:
    void paintScene();
    void resizeScene(int w, int h);

public:
    void translateObject(const QString &objectName,const QVector3D &translation);
    void rotateObject(const QString &objectName,const QQuaternion &rotation);
    void scaleObject(const QString &objectName,const float &scale);

    void setNormalTexture(const QString &objectName, const QString &path);
    void setDiffuseTexture(const QString &objectName, const QString &path);

signals:
    void updateGraphics();

//input engine part;
public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    void translateObject(const QString &objectName);
//physics engine part
public:

//script engine part
public:

//scene project part
public:
    void setCurrentScene(const QString &sceneName);
    void createSimpleScene();

public:
    void createScene(const QString &sceneName);
    void createCameraInScene(const QString &cameraName);
    void createLightingInScene(const QString &lightingName);
    void setSkyBox(const float &size, const QString &path);

    void selectCurrentScene(const QString &sceneName);
    Scene *getCurrentScene();
//project processor part
signals:
    void projectLoaded();

public slots:
    void createProject(const QString &path, const QString &name);
    void loadProject(const QString & path);
    void saveProject(const QString &path = 0, const QString &projectName = 0);
    void closeProject();

//folders part
public:
    void loadModel(const QString &objectName, const QString &path);
    void loadTexture(const QString &objectName, const QString &path);
    void loadScript(const QString &objectName, const QString &path);

//model loader part
public:
    bool createOBJModel(const QString &objectName, const QString &modelPath);
    bool createFBXModel(const QString &objectName, const QString &modelPath);

//model builder
public:
    bool createCube(const QString &objectName, const float &width = 1.0f, const float &height = 1.0f, const float &depth = 1.0f);
    void createPyramide(const QString &objectName, const float &width = 1.0f, const float &height = 1.0f);
    bool createSphere(const QString &objectName, const float & radius = 1.0f, const int & rings = 20, const int & sectors = 20);
    void createPrism(const QString &objectName, const float &width = 1.0f, const float &height = 1.0f, const float &depth = 1.0f, const float &angle = 1.0f);
    void createCone(const QString &objectName, const float &width = 1.0f, const float &height = 1.0f, const int &sectors = 20);
    void createCylinder(const QString &objectName, const float &width = 1.0f, const float &height = 1.0f, const int &sectors = 20);

private:

    GraphicsEngine *m_graphicsEngine;
    PhysicsEngine *m_phyicsEngine;
    ScriptEngine *m_scriptEngine;
    InputEngine *m_inputEngine;

    ProjectProcessor *m_projectProcessor;
    ModelLoader m_modelLoader;
    ModelBuilder m_modelBuilder;

    SceneFolder *m_sceneFolder;
    ModelFolder *m_modelFolder;
    ScriptFolder *m_scriptFolder;
    TextureFolder *m_textureFolder;

private:
    EngineCore();

    EngineCore(const GraphicsEngine&) = delete;
    EngineCore& operator=(const GraphicsEngine&) = delete;

    static EngineCore* m_instance;

signals:
    void setDisableState(bool state);
    void emitObject(BaseEngineObject *object);
};

#endif // ENGINECORE_H
