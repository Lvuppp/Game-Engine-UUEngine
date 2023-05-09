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

    bool addGameObject(const QString &name);
    bool addLighting(const QString &name);
    bool addCamera(const QString &name);
    //void addPhysicsObject();

// добавить добавление объектов камеры и света, а также добавить назначенеи текущей камеры.
public:
    QVector<Lighting *> lighings() const;
    QVector<Base3DGameObject *> gameObjects() const;
    Base3DGameObject *gameObject(const QString &objectName) const;
    Camera *camera(const QString &cameraName) const;
    Lighting *lighting(const QString &lightName) const;
    Camera *currentCamera() const;
    SkyBox *skybox() const;

    void setCurrentCamera(const QString &name);

private:
    Camera *m_currentCamera;

    //QVector<Base3DPhysicsObject *> m_physicsObject;
    QHash<QString, Base3DGameObject *> m_gameObjects;
    QHash<QString, Camera *> m_cameras;
    QHash<QString, Lighting *> m_lightings;

    SkyBox *m_skybox;
};

#endif // SCENE_H
