#ifndef sceneManager_H
#define sceneManager_H

#include "Entities/Scene.h"

#include <unordered_map>

class cSceneManager
{
public:
    cSceneManager() = default;
    ~cSceneManager();

    cSceneManager(const cSceneManager&) = delete;
    cSceneManager& operator=(const cSceneManager&) = delete;

    bool createScene(uint32_t hash);
    cScene *setCurrentScene(uint32_t hash);
    cScene *currentScene();

    void setScenes(std::unordered_map<uint32_t, cScene *>&& scenes);
    std::unordered_map<uint32_t, cScene *> scenes() const;
    void clearFolder();

private:
    cScene *m_currentScene = nullptr;
    std::unordered_map<uint32_t, cScene *> m_scenes;
};

#endif // sceneManager_H
