#include "Scene.h"

#include "BaseEntities/Base3DGameObject.h"
#include "BaseEntities/Camera.h"
#include "BaseEntities/Lighting.h"
#include "BaseEntities/Skybox.h"

#include "Utils/Assert.h"
#include "Utils/Hash.h"

cScene::cScene(const std::string& name)
    : m_id(cHash::hash(name))
    , m_name(name)
{
    m_currentCamera = new cCamera("DefaultCamera"_hash);
    m_currentLighting = new cLighting("DefaultLight"_hash);

    m_cameras.emplace_back(m_currentCamera);
    m_lightings.emplace_back(m_currentLighting);
}

cScene::cScene(const std::string& name, std::vector<cBase3DGameObject*>&& gameObjects, std::vector<cLighting*>&& lighting,
             std::vector<cCamera*>&& cameras, std::vector<cSkyBox*>&& skyBoxes)
    : m_id(cHash::hash(name))
    , m_name(name)
    , m_skyBoxes(std::move(skyBoxes))
    , m_cameras(std::move(cameras))
    , m_lightings(std::move(lighting))
    , m_gameObjects(std::move(gameObjects))
{

}

cScene::~cScene()
{
    for (auto& object : m_gameObjects)
    {
        delete object;
    }

    for (auto& object : m_cameras)
    {
        delete object;
    }

    for (auto& object : m_lightings)
    {
        delete object;
    }

    for (auto& object : m_skyBoxes)
    {
        delete object;
    }
}

uint32_t cScene::getId() const
{
    return m_id;
}

std::string_view cScene::getName() const
{
    return m_name;
}

cBase3DGameObject* cScene::addGameObject(uint32_t name, cModel *model)
{
    auto it = std::find_if(m_gameObjects.cbegin(), m_gameObjects.cend(), [name](const auto& object) {
        return object->getId() == name;
    });

    if (it != m_gameObjects.cend())
    {
        return nullptr;
    }

    m_gameObjects.emplace_back(new cBase3DGameObject(name, model));
    return m_gameObjects.back();
}

bool cScene::addLighting(uint32_t name)
{
    auto it = std::find_if(m_lightings.cbegin(), m_lightings.cend(), [name](const auto& object) {
        return object->getId() == name;
    });

    if (it != m_lightings.cend())
    {
        return false;
    }

    m_lightings.emplace_back(new cLighting());
    return true;
}

bool cScene::addCamera(uint32_t name)
{
    auto it = std::find_if(m_cameras.cbegin(), m_cameras.cend(), [name](const auto& object) {
        return object->getId() == name;
    });

    if (it != m_cameras.cend())
    {
        return false;
    }

    m_cameras.emplace_back(new cCamera());
    return true;
}

bool cScene::deleteGameObject(uint32_t name)
{
    auto it = std::find_if(m_gameObjects.cbegin(), m_gameObjects.cend(), [name](const auto& object) {
        return object->getId() == name;
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
        return object->getId() == name;
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
    auto it = std::find_if(m_cameras.cbegin(), m_cameras.cend(), [hash](const auto& object) {
        return object->getId() == hash;
    });

    ASSERT(it != m_cameras.cend(), "Camera doesn`t exist");
    if (it != m_cameras.cend())
    {
        m_cameras.erase(m_cameras.cbegin(), it);
        return true;
    }

    return false;
}

bool cScene::addSkyBox(uint32_t hash, cModel *model)
{
    auto it = std::find_if(m_skyBoxes.cbegin(), m_skyBoxes.cend(), [hash](const auto& object) {
        return object->getId() == hash;
    });

    if (it != m_skyBoxes.cend())
    {
        return false;
    }

    auto skyBox = new cSkyBox(hash, model);
    m_skyBoxes.emplace_back(skyBox);
    m_currentSkyBox = skyBox;
    
    return true;
}

const std::vector<cLighting*>& cScene::lighings() const
{
    return m_lightings;
}

const std::vector<cBase3DGameObject*>& cScene::gameObjects() const
{
    return m_gameObjects;
}

const std::vector<cCamera *>& cScene::cameras() const
{
    return m_cameras;
}

cBase3DGameObject *cScene::gameObject(uint32_t hash) const
{
    auto it = std::find_if(m_gameObjects.cbegin(), m_gameObjects.cend(), [hash](const auto& object) {
        return object->getId() == hash;
    });

    if (it != m_gameObjects.cend())
    {
        return *it;
    }

    return m_gameObjects[0];
}

cCamera *cScene::camera(uint32_t hash) const
{
    auto it = std::find_if(m_cameras.cbegin(), m_cameras.cend(), [hash](const auto& object) {
        return object->getId() == hash;
    });

    if (it != m_cameras.cend())
    {
        return *it;
    }

    return m_cameras[0];
}

cLighting *cScene::lighting(uint32_t hash) const
{
    auto it = std::find_if(m_lightings.cbegin(), m_lightings.cend(), [hash](const auto& object) {
        return object->getId() == hash;
    });

    if (it != m_lightings.cend())
    {
        return *it;
    }

    return m_lightings[0];
}

void cScene::setCurrentCamera(uint32_t hash)
{
    auto it = std::find_if(m_cameras.cbegin(), m_cameras.cend(), [hash](const auto& object) {
        return object->getId() == hash;
    });

    if (it != m_cameras.cend())
    {
        m_currentCamera = *it;
    }
}

cCamera* cScene::getCurrentCamera() const
{
    return m_currentCamera;
}

void cScene::setCurrentSkyBox(uint32_t hash)
{
    auto it = std::find_if(m_skyBoxes.cbegin(), m_skyBoxes.cend(), [hash](const auto& object) {
        return object->getId() == hash;
    });

    if (it != m_skyBoxes.cend())
    {
        m_currentSkyBox = *it;
    }
}

cSkyBox* cScene::getCurrentSkyBox() const
{
    return m_currentSkyBox;
}
