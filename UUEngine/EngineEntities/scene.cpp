#include "scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{
    for(auto object : m_gameObjects)
        delete object;
}

void Scene::addGameObject(Base3DGameObject object)
{
    m_gameObjects.append(new Base3DGameObject(object));
}

void Scene::addPhysicsObject(Base3DGameObject)
{

}

Camera Scene::camera() const
{
    return m_camera;
}

void Scene::setCamera(const Camera &newCamera)
{
    m_camera = newCamera;
}

Lighting Scene::lighing() const
{
    return m_lighting;
}

void Scene::setLighing(const Lighting &newLighing)
{
    m_lighting = newLighing;
}

QVector<Base3DGameObject *> Scene::gameObjects()
{
    return m_gameObjects;
}
