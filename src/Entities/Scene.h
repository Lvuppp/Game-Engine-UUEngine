#ifndef SCENE_H
#define SCENE_H

#include "EngineEntities/Base3DGameObject.h"
#include "EngineEntities/Camera.h"
#include "EngineEntities/Lighting.h"
#include "EngineEntities/Skybox.h"
#include "Models/SimpleModel.h"

class cScene
{

public:
    cScene();
    cScene(QHash<QString, cBase3DGameObject *> gameObjects, QHash<QString, cLighting *> lighting ,
          QHash<QString, cCamera *> cameras, cSkyBox *skybox);
    ~cScene();

    bool addGameObject(const QString &name, cModel *model);
    bool addLighting(const QString &name);
    bool addCamera(const QString &name);

    bool deleteGameObject(const QString &name);
    bool deleteLighting(const QString &name);
    bool deleteCamera(const QString &name);

    bool setSkybox(cSimpleModel *model);
    void setCurrentCamera(const QString &name);
    //void addPhysicsObject();

// добавить добавление объектов камеры и света, а также добавить назначенеи текущей камеры.
public:

    cBase3DGameObject *gameObject(const QString &objectName) const;
    cCamera *camera(const QString &cameraName) const;
    cLighting *lighting(const QString &lightName) const;

    QVector<cLighting*> lighings() const;
    QVector<cBase3DGameObject*> gameObjects() const;
    QVector<cCamera*> cameras() const;

    QHash<QString, cLighting *> lighingsHash() const;
    QHash<QString, cBase3DGameObject *> gameObjectsHash() const;
    QHash<QString, cCamera *> camerasHash() const;


    cCamera *currentCamera() const;
    cSkyBox *skybox() const;

private:
    //QVector<Base3DPhysicsObject *> m_physicsObject;
    cSkyBox *m_skybox;
    QHash<QString, cCamera *> m_cameras;
    QHash<QString, cLighting *> m_lightings;
    QHash<QString, cBase3DGameObject *> m_gameObjects;

    cCamera *m_currentCamera;
};


#endif // SCENE_H
