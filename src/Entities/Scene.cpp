#include "Scene.h"

#include "BaseEntities/Camera.h"
#include "Core/Cores/GraphicsEngine.h"
#include "Utils/Assert.h"

#include <iterator>

cScene::cScene()
{
    m_skybox = nullptr;
    m_currentCamera = nullptr;
}

cScene::cScene(std::unordered_map<uint32_t, cBase3DGameObject*>&& gameObjects, std::unordered_map<uint32_t, cLighting*>&& lighting,
             std::unordered_map<uint32_t, cCamera*>&& cameras, cSkyBox* skybox)
    : m_skybox(skybox)
    , m_cameras(std::move(cameras))
    , m_lightings(std::move(lighting))
    , m_gameObjects(std::move(gameObjects))
{

}

cScene::~cScene()
{
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
    {
        delete it->second;
    }

    for (auto it = m_cameras.begin(); it != m_cameras.end(); ++it)
    {
        delete it->second;
    }

    for (auto it = m_lightings.begin(); it != m_lightings.end(); ++it)
    {
        delete it->second;
    }
}

bool cScene::addGameObject(uint32_t name, cModel *model)
{
    auto it = std::find_if(m_gameObjects.cbegin(), m_gameObjects.cend(), [name](const auto& object) {
        return object.first == name;
    });

    if (it != m_gameObjects.cend())
    {
        return false;
    }

    m_gameObjects.insert(std::make_pair<>(name, new cBase3DGameObject(model)));
    return true;
}

bool cScene::addLighting(uint32_t name)
{
    auto it = std::find_if(m_lightings.cbegin(), m_lightings.cend(), [name](const auto& object) {
        return object.first == name;
    });

    if (it != m_lightings.cend())
    {
        return false;
    }

    m_lightings.insert(std::make_pair<>(name, new cLighting()));
    return true;
}

bool cScene::addCamera(uint32_t name)
{
    auto it = std::find_if(m_cameras.cbegin(), m_cameras.cend(), [name](const auto& object) {
        return object.first == name;
    });

    if (it != m_cameras.cend())
    {
        return false;
    }

    m_cameras.insert(std::make_pair<>(name, new cCamera()));
    return true;
}

bool cScene::deleteGameObject(uint32_t name)
{
    auto it = std::find_if(m_gameObjects.cbegin(), m_gameObjects.cend(), [name](const auto& object) {
        return object.first == name;
    });

    if (it != m_gameObjects.cend())
    {
        m_gameObjects.erase(m_gameObjects.cbegin(), it);
        return true;
    }

    return false;
}

bool cScene::deleteLighting(uint32_t name)
{
    auto it = std::find_if(m_lightings.cbegin(), m_lightings.cend(), [name](const auto& object) {
        return object.first == name;
    });

    if (it != m_lightings.cend())
    {
        m_lightings.erase(m_lightings.cbegin(), it);
        return true;
    }

    return false;
}

bool cScene::deleteCamera(uint32_t hash)
{
    auto it = std::find_if(m_cameras.cbegin(), m_cameras.cend(), [name](const auto& object) {
        return object.first == name;
    });

    ASSERT(it != m_cameras.cend(), "Camera doesn`t exist");
    if (it != m_cameras.cend())
    {
        m_cameras.erase(m_cameras.cbegin(), it);
        return true;
    }

    return false;
}

bool cScene::setSkybox(cModel *model)
{
    m_skybox = new cSkyBox(model);
    return true;
}

std::vector<cLighting*> cScene::lighings() const
{
    std::vector<cLighting*> lightings;
    lightings.reserve(m_lightings.size());

    for (auto [_, object] : m_lightings)
    {
        lightings.push_back(object);
    }

    return lightings;
}

std::vector<cBase3DGameObject*> cScene::gameObjects() const
{
    std::vector<cBase3DGameObject*> gameObjects;
    gameObjects.reserve(m_gameObjects.size());

    for (auto [_, object] : m_gameObjects)
    {
        gameObjects.push_back(object);
    }

    return gameObjects;
}

std::vector<cCamera *> cScene::cameras() const
{
    std::vector<cCamera*> cameras;
    cameras.reserve(m_cameras.size());

    for (auto [_, object] : m_cameras)
    {
        cameras.push_back(object);
    }

    return cameras;
}

const std::unordered_map<uint32_t, cLighting *>& cScene::lighingsHash() const
{
    return m_lightings;
}

const std::unordered_map<uint32_t, cBase3DGameObject *>& cScene::gameObjectsHash() const
{
    return m_gameObjects;
}

const std::unordered_map<uint32_t, cCamera *>& cScene::camerasHash() const
{
    return m_cameras;
}

cBase3DGameObject *cScene::gameObject(uint32_t hash) const
{
    return m_gameObjects.find(object)->second;
}

cCamera *cScene::camera(uint32_t hash) const
{
    return m_cameras.find(cameraName)->second;
}

cLighting *cScene::lighting(uint32_t hash) const
{
    return m_lightings.find(lightName)->second;
}

cCamera *cScene::currentCamera() const
{
    return m_currentCamera;
}

cSkyBox *cScene::skybox() const
{
    return m_skybox;
}

void cScene::setCurrentCamera(uint32_t name)
{
    m_currentCamera = m_cameras.find(name)->second;
}
