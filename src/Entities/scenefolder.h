#ifndef SCENEFOLDER_H
#define SCENEFOLDER_H

#include "scene.h"

#include "Models/custommodel.h"

class SceneFolder
{
public:

    bool createScene(const QString &sceneName);
    Scene *setCurrentScene(const QString &sceneName);
    Scene *currentScene();

    void setScenes(QHash<QString, Scene *> scenes);
    QHash<QString, Scene *> scenes() const;
    void clearFolder();

public:
    static SceneFolder *getInstance();

private:
    Scene *m_currentScene;
    QHash<QString, Scene *> m_scenes;

private:
    SceneFolder();
    ~SceneFolder();

    SceneFolder(const SceneFolder&) = delete;
    SceneFolder& operator=(const SceneFolder&) = delete;

    static SceneFolder* m_instance;
};

#endif // SCENEFOLDER_H
