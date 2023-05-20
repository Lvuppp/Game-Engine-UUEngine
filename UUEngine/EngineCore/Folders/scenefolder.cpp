#include "scenefolder.h"

SceneFolder::SceneFolder(): m_currentScene(nullptr)
{
    m_scenes = QHash<QString, Scene*>();
}

SceneFolder::~SceneFolder()
{
    foreach (auto scene, m_scenes){
        delete scene;
    }
}

bool SceneFolder::createScene(const QString &sceneName)
{
    if(m_scenes.contains(sceneName)) return false;

    m_scenes.insert(sceneName, new Scene());
    m_currentScene = m_scenes.value(sceneName);

    m_currentScene->addCamera("DefaultCamera");
    m_currentScene->addLighting("DefaultLight");

    return true;
}

Scene *SceneFolder::setCurrentScene(const QString &sceneName)
{
    m_currentScene = m_scenes.value(sceneName);
    return m_currentScene;
}

Scene *SceneFolder::currentScene()
{
    return m_currentScene;
}

QHash<QString, Scene *> SceneFolder::scenes() const
{
    return m_scenes;
}
