#include "scenefolder.h"

SceneFolder::SceneFolder(): m_currentScene(nullptr)
{
}

Scene *SceneFolder::createScene()
{
    m_scenes.append(new Scene());
    m_currentScene = m_scenes.last();

    m_currentScene->addCamera(new Camera());
    m_currentScene->addLighting(new Lighting());

    return m_currentScene;
}

Scene *SceneFolder::setCurrentScene(int id)
{
    m_currentScene = m_scenes.at(id);
    return m_currentScene;
}

void SceneFolder::addObjectInCurrentScene(Base3DGameObject *object)
{
    m_currentScene->addGameObject(object);
}

void SceneFolder::addLight(Lighting *lighting)
{
    m_currentScene->addLighting(lighting);
}

void SceneFolder::addCamera(Camera *camera)
{
    m_currentScene->addCamera(camera);
}

void SceneFolder::setSkyBox(QImage skyBoxImage)
{
    m_currentScene->skybox()->model()->material()->setDiffuseMap(skyBoxImage);
}
