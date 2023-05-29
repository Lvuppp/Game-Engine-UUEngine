#include "scenefolder.h"
SceneFolder* SceneFolder::m_instance = nullptr;

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

    m_currentScene->setCurrentCamera("DefaultCamera");

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

void SceneFolder::setScenes(QHash<QString, Scene *> scenes)
{
    clearFolder();
    m_scenes = scenes;

    if(!m_scenes.empty()){
        m_currentScene = m_scenes.begin().value();
    }
}

QHash<QString, Scene *> SceneFolder::scenes() const
{
    return m_scenes;
}

void SceneFolder::clearFolder()
{
    if(!m_scenes.empty()){
        foreach (auto scene, m_scenes){
            delete scene;
        }

        m_scenes.clear();
        m_currentScene = nullptr;
    }
}

SceneFolder *SceneFolder::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new SceneFolder();
    }
    return m_instance;
}
