#include "Scene.h"

cScene::cScene()
{
    m_gameObjects = QHash<QString, cBase3DGameObject *>();
    m_cameras = QHash<QString, cCamera*>();
    m_lightings = QHash<QString, cLighting*>();
    m_skybox = nullptr;
    m_currentCamera = nullptr;

}

cScene::cScene(QHash<QString, cBase3DGameObject *> gameObjects, QHash<QString, cLighting *> lighting,
             QHash<QString, cCamera *> cameras, cSkyBox *skybox) : m_skybox(skybox), m_cameras(cameras),
            m_lightings(lighting), m_gameObjects(gameObjects)
{

}

cScene::~cScene()
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

bool cScene::addGameObject(const QString &name, cModel *model)
{
    if(m_gameObjects.contains(name)) return false;

    m_gameObjects.insert(name, new cBase3DGameObject(model));
    return true;
}

bool cScene::addLighting(const QString &name)
{
    if(m_lightings.contains(name)) return false;

    m_lightings.insert(name, new cLighting());
    return true;
}

bool cScene::addCamera(const QString &name)
{
    if(m_cameras.contains(name)) return false;

    m_cameras.insert(name, new cCamera());
    return true;
}

bool cScene::deleteGameObject(const QString &name)
{
    return m_gameObjects.remove(name);
}

bool cScene::deleteLighting(const QString &name)
{
    return m_cameras.remove(name);
}

bool cScene::deleteCamera(const QString &name)
{
    return m_lightings.remove(name);
}

bool cScene::setSkybox(cSimpleModel *model)
{
    m_skybox = new cSkyBox(model);
    return true;
}


QVector<cLighting*> cScene::lighings() const
{
    return m_lightings.values();
}

QVector<cBase3DGameObject *> cScene::gameObjects() const
{
    return m_gameObjects.values();
}

QVector<cCamera *> cScene::cameras() const
{
    return m_cameras.values();
}

QHash<QString, cLighting *> cScene::lighingsHash() const
{
    return m_lightings;
}

QHash<QString, cBase3DGameObject *> cScene::gameObjectsHash() const
{
    return m_gameObjects;
}

QHash<QString, cCamera *> cScene::camerasHash() const
{
    return m_cameras;
}

cBase3DGameObject *cScene::gameObject(const QString &objectName) const
{
    return m_gameObjects.value(objectName);
}

cCamera *cScene::camera(const QString &cameraName) const
{
    return m_cameras.value(cameraName);
}

cLighting *cScene::lighting(const QString &lightName) const
{
    return m_lightings.value(lightName);
}

cCamera *cScene::currentCamera() const
{
    return m_currentCamera;
}

cSkyBox *cScene::skybox() const
{
    return m_skybox;
}

void cScene::setCurrentCamera(const QString &name)
{
    m_currentCamera = m_cameras.value(name);
}

