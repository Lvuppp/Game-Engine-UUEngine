#include "sceneprocessor.h"
SceneProcessor* SceneProcessor::m_instance = nullptr;

Scene *SceneProcessor::setCurrentScene(const QString &sceneName)
{
    if(m_scenes.contains(sceneName)){
        m_currentScene = m_scenes.value(sceneName);
    }

    return m_currentScene;
}

Scene *SceneProcessor::currentScene()
{
    return m_currentScene;
}

SceneProcessor *SceneProcessor::getInstance(QHash<QString, Scene *> &scenes)
{
    if(!m_instance){
        m_instance = new SceneProcessor(scenes);
    }
}

SceneProcessor::SceneProcessor(QHash<QString, Scene *> &scenes)
{
    m_scenes = scenes;
}
