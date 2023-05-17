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

    bool addGameObject(const QString &name, ModelType modelType, QVector<Model *> model, const QString &modelPath = "");
    bool addGameObject(const QString &name,  ModelType modelType, Model *model, const QString &modelPath = "");
    bool addLighting(const QString &name);
    bool addCamera(const QString &name);

    bool setSkybox(Model *model);
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
    QHash<QString, Base3DGameObject *> m_gameObjects;
    QHash<QString, Camera *> m_cameras;
    QHash<QString, Lighting *> m_lightings;

    Camera *m_currentCamera;
    SkyBox *m_skybox;
};

#endif // SCENE_H
