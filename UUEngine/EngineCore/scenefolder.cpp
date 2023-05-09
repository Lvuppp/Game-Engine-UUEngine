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
    m_currentScene = m_scenes.take(sceneName);

    m_currentScene->addCamera("Camera");
    m_currentScene->addLighting("Light");

    return true;
}

Scene *SceneFolder::setCurrentScene(const QString &sceneName)
{
    m_currentScene = m_scenes.take(sceneName);
    return m_currentScene;
}

Scene *SceneFolder::currentScene()
{
    return m_currentScene;
}

void SceneFolder::addObject(const QString &objectName)
{
    m_currentScene->addGameObject(objectName);
}

void SceneFolder::addLight(const QString &lightName)
{
    m_currentScene->addLighting(lightName);
}

void SceneFolder::addCamera(const QString &cameraName)
{
    m_currentScene->addCamera(cameraName);
}

void SceneFolder::setSkyBox(QImage skyBoxImage)
{
    m_currentScene->skybox()->setDiffuseMap(skyBoxImage);
}

void SceneFolder::setCurrentCamera(const QString &cameraName)
{
    m_currentScene->setCurrentCamera(cameraName);
}

Base3DGameObject *SceneFolder::object(const QString &objectName)
{
    return m_currentScene->gameObject(objectName);
}

Camera *SceneFolder::camera(const QString &objectName)
{
    return m_currentScene->camera(objectName);
}

Lighting *SceneFolder::lighting(const QString &objectName)
{
   return m_currentScene->lighting(objectName);
}
