#ifndef sceneManager_H
#define sceneManager_H

#include "Entities/Scene.h"

class cSceneManager
{
public:
    cSceneManager();
    ~cSceneManager();

    cSceneManager(const cSceneManager&) = delete;
    cSceneManager& operator=(const cSceneManager&) = delete;

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

#endif // sceneManager_H
