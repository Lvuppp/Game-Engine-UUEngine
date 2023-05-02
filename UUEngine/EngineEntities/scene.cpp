#include "scene.h"

Scene::Scene()
{

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

Base3DGameObject *Scene::addGameObject(Base3DGameObject *object)
{
    m_gameObjects.append(object);
    return m_gameObjects.last();
}

Camera *Scene::addCamera(const QVector3D &coordinates, const QQuaternion &rotation,
                         const float &scale, const bool &isObjectLocked)
{
    m_cameras.append(new Camera(coordinates, rotation, scale, isObjectLocked));
    return m_cameras.last();
}


//void Scene::addPhysicsObject(Base3DGameObject)
//{

//}

Camera* Scene::camera() const
{
    return m_cameras.last();
}

//void Scene::setCamera(const Camera &newCamera)
//{
//    m_camera = newCamera;
//}

QVector<Lighting*> Scene::lighings() const
{
    return m_lightings;
}

//void Scene::setLighingы(const Lighting &newLighing)
//{
//    m_lightings = newLighing;
//}

QVector<Base3DGameObject *> Scene::gameObjects() const
{
    return m_gameObjects;
}

Camera *Scene::currentCamera() const
{
    return m_cameras.last();
}

void Scene::setCurrentCamera(Camera *newCurrentCamera)
{
    m_currentCamera = newCurrentCamera;
}
