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

bool Scene::addGameObject(const QString &name)
{
    if(m_gameObjects.contains(name)) return false;

    m_gameObjects.insert(name, new Base3DGameObject());
    return true;
}

bool Scene::addLighting(const QString &name)
{
    if(m_lightings.contains(name)) return false;

    m_lightings.insert(name, new Lighting());
    return true;
}

bool Scene::addCamera(const QString &name)
{
    if(m_cameras.contains(name)) return false;

    m_cameras.insert(name, new Camera());
    return true;
}
QVector<Lighting*> Scene::lighings() const
{
    return m_lightings.values();
}

QVector<Base3DGameObject *> Scene::gameObjects() const
{
    return m_gameObjects.values();
}

Base3DGameObject *Scene::gameObject(const QString &objectName) const
{
    return m_gameObjects.value(objectName);
}

Camera *Scene::camera(const QString &cameraName) const
{
    return m_cameras.value(cameraName);
}

Lighting *Scene::lighting(const QString &lightName) const
{
    return m_lightings.value(lightName);
}

Camera *Scene::currentCamera() const
{
    return m_currentCamera;
}

SkyBox *Scene::skybox() const
{
    return m_skybox;
}

void Scene::setCurrentCamera(const QString &name)
{
    m_currentCamera = m_cameras.value(name);
}

