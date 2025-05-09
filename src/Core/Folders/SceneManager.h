#ifndef sceneManager_H
#define sceneManager_H

#include "Entities/Scene.h"

#include <memory>
#include <unordered_map>

class cCamera;
class cLigthing;

class cSceneManager
{
public:
    cSceneManager() = default;

    cSceneManager(const cSceneManager&) = delete;
    cSceneManager& operator=(const cSceneManager&) = delete;

    bool createScene(uint32_t hash);
    std::shared_ptr<cScene> setCurrentScene(uint32_t hash);
    std::shared_ptr<cScene> currentScene();

    void setScenes(std::unordered_map<uint32_t, std::shared_ptr<cScene>>&& scenes);
    std::unordered_map<uint32_t, std::shared_ptr<cScene>> scenes() const;
    void clearFolder();

private:
    std::shared_ptr<cScene> m_currentScene = nullptr;
    std::unordered_map<uint32_t, std::shared_ptr<cScene>> m_scenes;
};

#endif // sceneManager_H
