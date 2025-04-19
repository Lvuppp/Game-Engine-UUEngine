#ifndef SCENEFOLDER_H
#define SCENEFOLDER_H

#include "Scene.h"

class cSceneFolder
{
public:
    cSceneFolder();
    ~cSceneFolder();

    cSceneFolder(const cSceneFolder&) = delete;
    cSceneFolder& operator=(const cSceneFolder&) = delete;

    bool createScene(const std::string &sceneName);
    cScene *setCurrentScene(const std::string &sceneName);
    cScene *currentScene();

    void setScenes(std::unordered_map<std::string, cScene *> scenes);
    std::unordered_map<std::string, cScene *> scenes() const;
    void clearFolder();

private:
    cScene *m_currentScene;
    std::unordered_map<std::string, cScene *> m_scenes;
};

#endif // SCENEFOLDER_H
