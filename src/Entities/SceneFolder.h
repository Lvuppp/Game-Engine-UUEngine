#ifndef SCENEFOLDER_H
#define SCENEFOLDER_H

#include "Scene.h"

#include "Models/CustomModel.h"

class cSceneFolder
{
public:

    bool createScene(const QString &sceneName);
    cScene *setCurrentScene(const QString &sceneName);
    cScene *currentScene();

    void setScenes(QHash<QString, cScene *> scenes);
    QHash<QString, cScene *> scenes() const;
    void clearFolder();

public:
    static cSceneFolder *getInstance();

private:
    cScene *m_currentScene;
    QHash<QString, cScene *> m_scenes;

private:
    cSceneFolder();
    ~cSceneFolder();

    cSceneFolder(const cSceneFolder&) = delete;
    cSceneFolder& operator=(const cSceneFolder&) = delete;

    static cSceneFolder* m_instance;
};

#endif // SCENEFOLDER_H
