#ifndef SCENE_H
#define SCENE_H

#include "EngineEntities/base3dgameobject.h"
#include "EngineEntities/camera.h"
#include "EngineEntities/lighting.h"
#include "EngineEntities/skybox.h"
#include "Models/simplemodel.h"

class Scene
{

public:
    Scene();
    Scene(QHash<QString, Base3DGameObject *> gameObjects, QHash<QString, Lighting *> lighting ,
          QHash<QString, Camera *> cameras, SkyBox *skybox);
    ~Scene();

    bool addGameObject(const QString &name, Model *model);
    bool addLighting(const QString &name);
    bool addCamera(const QString &name);

    bool deleteGameObject(const QString &name);
    bool deleteLighting(const QString &name);
    bool deleteCamera(const QString &name);

    bool setSkybox(SimpleModel *model);
    void setCurrentCamera(const QString &name);
    //void addPhysicsObject();

// добавить добавление объектов камеры и света, а также добавить назначенеи текущей камеры.
public:

    Base3DGameObject *gameObject(const QString &objectName) const;
    Camera *camera(const QString &cameraName) const;
    Lighting *lighting(const QString &lightName) const;

    QVector<Lighting *> lighings() const;
    QVector<Base3DGameObject *> gameObjects() const;
    QVector<Camera *> cameras() const;

    QHash<QString, Lighting *> lighingsHash() const;
    QHash<QString, Base3DGameObject *> gameObjectsHash() const;
    QHash<QString, Camera *> camerasHash() const;


    Camera *currentCamera() const;
    SkyBox *skybox() const;

private:
    QHash<QString, QString> m_objectsScriptsPath;

private:
    //QVector<Base3DPhysicsObject *> m_physicsObject;
    SkyBox *m_skybox;
    QHash<QString, Camera *> m_cameras;
    QHash<QString, Lighting *> m_lightings;
    QHash<QString, Base3DGameObject *> m_gameObjects;

    Camera *m_currentCamera;
};


#endif // SCENE_H
