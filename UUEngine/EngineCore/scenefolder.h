#ifndef SCENEFOLDER_H
#define SCENEFOLDER_H

#include "scene.h"

class SceneFolder
{
public:
    SceneFolder();
    ~SceneFolder();


    bool createScene(const QString &sceneName);
    Scene *setCurrentScene(const QString &sceneName);
    Scene *currentScene();

public:
    void addObject(const QString &objectName);
    void addLight(const QString &lightName);
    void addCamera(const QString &cameraName);
    void setSkyBox(QImage skyBoxImage);
    void setCurrentCamera(const QString &cameraName);

public:
    Base3DGameObject *object(const QString &objectName);
    Camera *camera(const QString &objectName);
    Lighting *lighting(const QString &objectName);

private:
    Scene *m_currentScene;
    QHash<QString, Scene *> m_scenes;
};

#endif // SCENEFOLDER_H
