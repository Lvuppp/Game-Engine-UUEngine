#ifndef SCENE_H
#define SCENE_H

#include "base3dgameobject.h"
#include "camera.h"
#include "lighting.h"

class Scene
{

public:
    Scene();
    ~Scene();

    void addGameObject(Base3DGameObject);
    void addPhysicsObject(Base3DGameObject);

    Camera camera() const;
    void setCamera(const Camera &newCamera);

    Lighting lighing() const;
    void setLighing(const Lighting &newLighing);

    QVector<Base3DGameObject *> gameObjects();

private:
    QVector<Base3DGameObject *> m_gameObjects;
    Camera m_camera;
    Lighting m_lighting;
};

#endif // SCENE_H
