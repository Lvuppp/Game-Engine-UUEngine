#include "scene.h"

Scene::Scene()
{
    m_skybox = new SkyBox(100.0f,QImage("/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Textures/skybox3.png"));
}

Scene::~Scene()
{
    for(auto object : m_gameObjects)
        delete object;

    for(auto camera : m_cameras)
        delete camera;

    for(auto lighting : m_lightings)
        delete lighting;
}

void Scene::addGameObject(Base3DGameObject *object)
{
    m_gameObjects.append(object);
}

void Scene::addLighting(Lighting *light)
{
    m_lightings.append(light);
}

void Scene::addCamera(Camera *camera)
{
    m_cameras.append(camera);

    if(m_cameras.size() == 0) m_currentCamera = m_cameras.last();
}
QVector<Lighting*> Scene::lighings() const
{
    return m_lightings;
}

QVector<Base3DGameObject *> Scene::gameObjects() const
{
    return m_gameObjects;
}

Base3DGameObject *Scene::gameObjectById(int id) const
{
    return m_gameObjects.at(id);
}

Camera *Scene::currentCamera() const
{
    return m_cameras.last();
}

SkyBox *Scene::skybox() const
{
    return m_skybox;
}

void Scene::setCurrentCamera(int id)
{
    m_currentCamera = m_cameras.at(id);
}

