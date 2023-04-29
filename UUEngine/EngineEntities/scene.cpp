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

Base3DGameObject *Scene::addGameObject(const QVector<VertexData> &vertexes, const QVector<GLuint> &indexes,
                          const QImage &texture, const float &ambiendFactor, const float &specularFactor,
                          const QVector3D &coordinates, const QQuaternion &rotation,
                          const float &scale, const bool &isObjectLocked)
{
    m_gameObjects.append(new Base3DGameObject(vertexes, indexes, texture, ambiendFactor, specularFactor, coordinates, rotation, scale, isObjectLocked));
    return m_gameObjects.last();
}

Camera *Scene::addCamera(const QVector3D &coordinates, const QQuaternion &rotation,
                         const float &scale, const bool &isObjectLocked)
{
    m_cameras.append(new Camera(coordinates, rotation, scale, isObjectLocked));
}


//void Scene::addPhysicsObject(Base3DGameObject)
//{

//}

Camera *Scene::camera()
{
    return m_camera;
}

//void Scene::setCamera(const Camera &newCamera)
//{
//    m_camera = newCamera;
//}

QVector<Lighting*> Scene::lighings()
{
    return m_lightings;
}

//void Scene::setLighingы(const Lighting &newLighing)
//{
//    m_lightings = newLighing;
//}

QVector<Base3DGameObject *> Scene::gameObjects()
{
    return m_gameObjects;
}
