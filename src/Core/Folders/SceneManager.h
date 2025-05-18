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

    bool createScene(const std::string& name);
    std::shared_ptr<cScene> setCurrentScene(const std::string& name);
    std::shared_ptr<cScene> currentScene();

    void loadScenes(std::vector<std::shared_ptr<cScene>>&& scenes);
    const std::vector<std::shared_ptr<cScene>>& getScenes() const;
    void clearFolder();

private:
    std::shared_ptr<cScene> m_currentScene = nullptr;
    std::vector<std::shared_ptr<cScene>> m_scenes;
};

#endif // sceneManager_H
