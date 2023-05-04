#ifndef SCENEFOLDER_H
#define SCENEFOLDER_H

#include "scene.h"

class SceneFolder
{
public:
    SceneFolder();

    Scene *createScene();
    Scene *setCurrentScene(int id);

public:
    void addObjectInCurrentScene(Base3DGameObject *object);
    void addLight(Lighting *lighting);
    void addCamera(Camera *camera);
    void setSkyBox(QImage skyBoxImage);

private:
    Scene *m_currentScene;
    QVector<Scene *> m_scenes;
};

#endif // SCENEFOLDER_H
