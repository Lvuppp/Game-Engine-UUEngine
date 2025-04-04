#ifndef ENGINECORE_H
#define ENGINECORE_H

#include "GraphicsEngine.h"
#include "PhysicsEngine.h"
#include "ScriptEngine.h"
#include "InputEngine.h"
#include "SceneFolder.h"
#include "Services/ModelLoader.h"
#include "Services/ModelBuilder.h"
#include "Services/ProjectProcessor.h"

#include <QVBoxLayout>
//#include"camera.h"

class cEngineCore : public QObject
{
    Q_OBJECT

public:
// intitializing of all engine parts
    void initGraphicsEngine();
    void initPhysicsEngine();
    void initScriptEngine();
    void initInputEngine(const int &width, const int &height);
    void initProjectProcessor(QVBoxLayout &layout);

    static cEngineCore *getInstance();

//graphics engine part
public:
    void paintScene();
    void resizeScene(int w, int h);

public:
    void translateObject(const QString &objectName,const QVector3D &translation);
    void rotateXObject(const QString &objectName,const QQuaternion &rotation);
    void rotateYObject(const QString &objectName,const QQuaternion &rotation);
    void scaleObject(const QString &objectName,const float &scale);
    void deleteObject(const QString& objectName);

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

    void placeObjectOnMousePosition(const QString &objectName);
//physics engine part
public:

//script engine part
public:
    void changeGameStatus();

public slots:
    void updateScene();

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
    cScene *getCurrentScene();

//project processor part
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

    QString getModel(const QString &objectName);
    QVector<QString> getScripts(const QString &objectName);

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

    void changeCube(const QString &objectName, const float &width, const float &height, const float &depth);
    void changeSphere(const QString &objectName, const float & radius = 1.0f, const int & rings = 20, const int & sectors = 20);
private:

    cGraphicsEngine *m_graphicsEngine;
    cPhysicsEngine *m_phyicsEngine;
    cScriptEngine *m_scriptEngine;
    cInputEngine *m_inputEngine;

    cProjectProcessor *m_projectProcessor;
    cModelLoader m_modelLoader;
    cModelBuilder m_modelBuilder;

    cSceneFolder *m_sceneFolder;
    cModelFolder *m_modelFolder;
    cScriptFolder *m_scriptFolder;
    cTextureFolder *m_textureFolder;

private:
    cEngineCore();

    cEngineCore(const cGraphicsEngine&) = delete;
    cEngineCore& operator=(const cGraphicsEngine&) = delete;

    static cEngineCore* m_instance;

    bool m_gameStatus = false;

signals:
    void setDisableState(bool state);
    void emitObject(const QString &objectName, cBase3DGameObject **object);
};


#endif // ENGINECORE_H
