#ifndef SCENE_H
#define SCENE_H

#include "base3dgameobject.h"
#include "camera.h"
#include "lighting.h"
#include "skybox.h"

class Scene
{

public:
    Scene();
    ~Scene();

    void addGameObject(Base3DGameObject *object);
    void addLighting(Lighting *light);
    void addCamera(Camera *camera);
    //void addPhysicsObject();

// добавить добавление объектов камеры и света, а также добавить назначенеи текущей камеры.
public:
    QVector<Lighting *> lighings() const;
    QVector<Base3DGameObject *> gameObjects() const;
    Base3DGameObject *gameObjectById(int id) const;
    Camera *currentCamera() const;
    SkyBox *skybox() const;

    void setCurrentCamera(int id);

private:
    Camera *m_currentCamera;

    //QVector<Base3DPhysicsObject *> m_physicsObject;
    QVector<Base3DGameObject *> m_gameObjects;
    QVector<Camera *> m_cameras;
    QVector<Lighting *> m_lightings;

    SkyBox *m_skybox;
};

#endif // SCENE_H
