#ifndef SCENEFOLDER_H
#define SCENEFOLDER_H

#include "scene.h"

#include "Models/custommodel.h"

class SceneFolder
{
public:
    SceneFolder();
    ~SceneFolder();


    bool createScene(const QString &sceneName);
    Scene *setCurrentScene(const QString &sceneName);
    Scene *currentScene();

    QHash<QString, Scene *> scenes() const;

private:
    Scene *m_currentScene;
    QHash<QString, Scene *> m_scenes;
};

#endif // SCENEFOLDER_H
