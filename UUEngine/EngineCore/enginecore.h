#ifndef ENGINECORE_H
#define ENGINECORE_H

#include "graphicsengine.h"
#include "physicsengine.h"
#include "scriptengine.h"
#include "inputengine.h"
#include "scenefolder.h"
#include "modelloader.h"
#include "objectbuilder.h"
#include "base3dgameobject.h"
#include "projectprocessor.h"
//#include"camera.h"

class EngineCore : public QObject
{
    Q_OBJECT

public:
    EngineCore();
// иницализация всех частей движка
    void initGraphicsEngine();
    void initPhysicsEngine();
    void initScriptEngine();
    void initInputEngine();

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

//scene folder part
public:
    void setCurrentScene();
    void createSimpleScene();


private:

    GraphicsEngine *m_graphicsEngine;
    PhysicsEngine *m_phyicsEngine;
    ScriptEngine *m_scriptEngine;
    InputEngine *m_inputEngine;

    SceneFolder *m_sceneFolder;
    ModelLoader *m_modelLoader;
    ObjectBuilder *m_objectBuilder;

};

#endif // ENGINECORE_H
