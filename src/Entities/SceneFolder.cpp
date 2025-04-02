#include "SceneFolder.h"
cSceneFolder* cSceneFolder::m_instance = nullptr;

cSceneFolder::cSceneFolder(): m_currentScene(nullptr)
{
    m_scenes = QHash<QString, cScene*>();
}

cSceneFolder::~cSceneFolder()
{
    foreach (auto scene, m_scenes){
        delete scene;
    }
}

bool cSceneFolder::createScene(const QString &sceneName)
{
    if(m_scenes.contains(sceneName)) return false;

    m_scenes.insert(sceneName, new cScene());
    m_currentScene = m_scenes.value(sceneName);

    m_currentScene->addCamera("DefaultCamera");
    m_currentScene->addLighting("DefaultLight");

    m_currentScene->setCurrentCamera("DefaultCamera");

    return true;
}

cScene *cSceneFolder::setCurrentScene(const QString &sceneName)
{
    m_currentScene = m_scenes.value(sceneName);
    return m_currentScene;
}

cScene *cSceneFolder::currentScene()
{
    return m_currentScene;
}

void cSceneFolder::setScenes(QHash<QString, cScene *> scenes)
{
    clearFolder();
    m_scenes = scenes;

    if(!m_scenes.empty()){
        m_currentScene = m_scenes.begin().value();
    }
}

QHash<QString, cScene *> cSceneFolder::scenes() const
{
    return m_scenes;
}

void cSceneFolder::clearFolder()
{
    if(!m_scenes.empty()){
        foreach (auto scene, m_scenes){
            delete scene;
        }

        m_scenes.clear();
        m_currentScene = nullptr;
    }
}

cSceneFolder *cSceneFolder::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new cSceneFolder();
    }
    return m_instance;
}
