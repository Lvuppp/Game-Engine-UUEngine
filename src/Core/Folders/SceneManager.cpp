#include "SceneManager.h"

#include "Utils/Hash.h"

cSceneManager::~cSceneManager()
{
    for (auto& [name, scene] : m_scenes)
    {
        delete scene;
    }
}

bool cSceneManager::createScene(uint32_t hash)
{
    if (m_scenes.find(hash) != m_scenes.end())
    {
        return false;
    }

    m_scenes.insert(std::make_pair(hash, new cScene()));
    m_currentScene = m_scenes[hash];

    m_currentScene->addCamera("DefaultCamera"_hash);
    m_currentScene->addLighting("DefaultLight"_hash);

    m_currentScene->setCurrentCamera("DefaultCamera"_hash);

    return true;
}

cScene *cSceneManager::setCurrentScene(uint32_t hash)
{
    if (m_scenes.find(hash) != m_scenes.end())
    {
        m_currentScene = m_scenes[hash];
    }
    return m_currentScene;
}

cScene *cSceneManager::currentScene()
{
    return m_currentScene;
}

void cSceneManager::setScenes(std::unordered_map<uint32_t, cScene *>&& scenes)
{
    clearFolder();
    m_scenes = std::move(scenes);

    if (!m_scenes.empty())
    {
        m_currentScene = m_scenes.begin()->second;
    }
}

std::unordered_map<uint32_t, cScene *> cSceneManager::scenes() const
{
    return m_scenes;
}

void cSceneManager::clearFolder()
{
    if (!m_scenes.empty())
    {
        for (auto& [name, scene] : m_scenes)
        {
            delete scene;
        }

        m_scenes.clear();
        m_currentScene = nullptr;
    }
}
