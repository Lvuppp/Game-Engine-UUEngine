#include "SceneFolder.h"

cSceneFolder::cSceneFolder()
    : m_currentScene(nullptr)
{
    m_scenes = std::unordered_map<std::string, cScene*>();
}

cSceneFolder::~cSceneFolder()
{
    for (auto& [name, scene] : m_scenes)
    {
        delete scene;
    }
}

bool cSceneFolder::createScene(const std::string &sceneName)
{
    if (m_scenes.find(sceneName) != m_scenes.end()) 
    {
        return false;
    }
    
    m_scenes.insert(std::make_pair(sceneName, new cScene()));
    m_currentScene = m_scenes[sceneName];

    m_currentScene->addCamera("DefaultCamera");
    m_currentScene->addLighting("DefaultLight");

    m_currentScene->setCurrentCamera("DefaultCamera");

    return true;
}

cScene *cSceneFolder::setCurrentScene(const std::string &sceneName)
{
    if (m_scenes.find(sceneName) != m_scenes.end())
    {
        m_currentScene = m_scenes[sceneName];
    }
    return m_currentScene;
}

cScene *cSceneFolder::currentScene()
{
    return m_currentScene;
}

void cSceneFolder::setScenes(std::unordered_map<std::string, cScene *> scenes)
{
    clearFolder();
    m_scenes = std::move(scenes);

    if (!m_scenes.empty())
    {
        m_currentScene = m_scenes.begin()->second;
    }
}

std::unordered_map<std::string, cScene *> cSceneFolder::scenes() const
{
    return m_scenes;
}

void cSceneFolder::clearFolder()
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
