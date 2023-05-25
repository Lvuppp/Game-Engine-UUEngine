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
    void initInputEngine();
    void initProjectProcessor(QVBoxLayout &layout);

    static EngineCore *getInstance();

//graphics engine part
public:

    void paintScene();
    void resizeScene(int w, int h);

signals:
    void updateGraphics();

//input engine part
public slots:
    void getEvent(QEvent* event);

//physics engine part
public:

//script engine part
public:

//scene project part
public:
    void setCurrentScene();
    void createSimpleScene();

public slots:
    void createCustomObjectInScene();
    void createSimpleObjectInScene();
    void createCameraInScene();
    void createLightingInScene();

//project processor part
signals:
    void projectLoaded();

public slots:
    void createProject(const QString &path, const QString &name);
    void loadProject(const QString & path);
    void saveProject(const QString &path = 0, const QString &projectName = 0);
    void closeProject();

//folders part
public slots:
    void loadModel(const QString & path);
    void loadTexture(const QString & path);
    void loadScript(const QString & path);


private:

    GraphicsEngine *m_graphicsEngine;
    PhysicsEngine *m_phyicsEngine;
    ScriptEngine *m_scriptEngine;
    InputEngine *m_inputEngine;

    ProjectProcessor *m_projectProcessor;
    ModelLoader m_modelLoader;
    ModelBuilder m_modelBuilder;

    SceneFolder *m_sceneFolder;

    EngineCore();

    EngineCore(const GraphicsEngine&) = delete;
    EngineCore& operator=(const GraphicsEngine&) = delete;


    static EngineCore* m_instance;
};

#endif // ENGINECORE_H
