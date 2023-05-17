#ifndef SCENEFOLDER_H
#define SCENEFOLDER_H

#include "scene.h"

#include <model.h>

class SceneFolder
{
public:
    SceneFolder();
    ~SceneFolder();


    bool createScene(const QString &sceneName);
    Scene *setCurrentScene(const QString &sceneName);
    Scene *currentScene();

public:
    void addObject(const QString &objectName, ModelType modelType, QVector<Model *> model , const QString &modelPath = "");
    void addObject(const QString &objectName, ModelType modelType, Model *model , const QString &modelPath = "");
    void addLight(const QString &lightName);
    void addCamera(const QString &cameraName);
    void setSkyBox(Model *model);
    void setCurrentCamera(const QString &cameraName);

public:
    Base3DGameObject *object(const QString &objectName);
    Camera *camera(const QString &objectName);
    Lighting *lighting(const QString &objectName);

    QHash<QString, Scene *> scenes() const;

private:
    Scene *m_currentScene;
    QHash<QString, Scene *> m_scenes;
};

#endif // SCENEFOLDER_H
