#ifndef SCENE_H
#define SCENE_H

#include "baseengineobject.h"
#include "camera.h"

class Scene
{
public:
    Scene();

private:
    QVector<std::unique_ptr<BaseEngineObject>> gameObjects;
    std::unique_ptr<Camera>

};

#endif // SCENE_H
