#ifndef ENGINECORE_H
#define ENGINECORE_H

#include "graphicsengine.h"
#include "physicsengine.h"
#include "scriptengine.h"
#include "inputengine.h"

//#include"camera.h"

class EngineCore : public QObject
{
    Q_OBJECT

public:
    EngineCore();

    void initGraphicsEngine();
    void initPhysicsEngine();
    void initScriptEngine();
    void initInputEngine();

    //graphics engine part
    void paintScene();
    void resizeScene(int w, int h);

    void loadScene();
    void setCurrentScene();

    //input engine part



    //physics engine part


    //script engine part
public slots:
    void getEvent(QEvent* event);

signals:
    void updateGraphics();

private:

    GraphicsEngine* graphicsEngine;
    PhysicsEngine* phyicsEngine;
    ScriptEngine* scriptEngine;
    InputEngine* inputEngine;

};

#endif // ENGINECORE_H
