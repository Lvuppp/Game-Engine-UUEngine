#include "SceneManager.h"

#include "Utils/Hash.h"

#include <algorithm>

bool cSceneManager::createScene(const std::string& name)
{
    const auto it = std::find_if(m_scenes.cbegin(), m_scenes.cend(), [hash = cHash::hash(name)](const auto& scene) {
        return scene->getId() == hash;
    });

    if (it != m_scenes.end())
    {
        return false;
    }

    auto scene = std::make_shared<cScene>(name);
    m_scenes.push_back(scene);
    m_currentScene = scene;

    return true;
}

std::shared_ptr<cScene> cSceneManager::setCurrentScene(const std::string& name)
{
    const auto it = std::find_if(m_scenes.cbegin(), m_scenes.cend(), [hash = cHash::hash(name)](const auto& scene) {
        return scene->getId() == hash;
    });

    if (it != m_scenes.end())
    {
        m_currentScene = *it;
    }
    return m_currentScene;
}

std::shared_ptr<cScene> cSceneManager::currentScene()
{
    return m_currentScene;
}

void cSceneManager::loadScenes(std::vector<std::shared_ptr<cScene>>&& scenes)
{
    clearFolder();
    m_scenes = std::move(scenes); // TODO: check if it's correct

    if (m_scenes.empty() == false)
    {
        m_currentScene = m_scenes.front();
    }
}

const std::vector<std::shared_ptr<cScene>>& cSceneManager::getScenes() const
{
    return m_scenes;
}

void cSceneManager::clearFolder()
{
    if (m_scenes.empty() == false)
    {
        m_scenes.clear();
        m_currentScene = nullptr;
    }
}
