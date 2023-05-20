#include "scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
        delete it.value();
    }
    m_gameObjects.clear();

    // Удаление камер
    for (auto it = m_cameras.begin(); it != m_cameras.end(); ++it) {
        delete *it;
    }
    m_cameras.clear();

    // Удаление освещения
    for (auto it = m_lightings.begin(); it != m_lightings.end(); ++it) {
        delete *it;
    }
    m_lightings.clear();
}

bool Scene::addGameObject(const QString &name, Model *model)
{
    if(m_gameObjects.contains(name)) return false;

    m_gameObjects.insert(name, new Base3DGameObject(model));
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

bool Scene::setSkybox(SimpleModel *model)
{
    m_skybox = new SkyBox(model);
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

QVector<Camera *> Scene::cameras() const
{
    return m_cameras.values();
}

QHash<QString, Lighting *> Scene::lighingsHash() const
{
    return m_lightings;
}

QHash<QString, Base3DGameObject *> Scene::gameObjectsHash() const
{
    return m_gameObjects;
}

QHash<QString, Camera *> Scene::camerasHash() const
{
    return m_cameras;
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

