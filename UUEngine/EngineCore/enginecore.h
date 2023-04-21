#ifndef ENGINECORE_H
#define ENGINECORE_H

#include "graphicsengine.h"
#include "physicsengine.h"
#include "scriptengine.h"

//#include"camera.h"

class EngineCore
{
public:
    EngineCore();

    void initGraphicsEngine();
    void initPhysicsEngine();
    void initScriptEngine();
    //graphics engine part
    void paintScene();
    void resizeScene(int w, int h);

    void loadScene();
    void setCurrentScene();

    //physics engine part


    //script engine part


private:

    GraphicsEngine* graphicsEngine;
    PhysicsEngine* phyicsEngine;
    ScriptEngine* scriptEngine;

};

#endif // ENGINECORE_H
