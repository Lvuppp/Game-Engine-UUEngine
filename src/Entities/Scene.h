#ifndef SCENE_H
#define SCENE_H

#include <cstdint>
#include <vector>

class cBase3DGameObject;
class cCamera;
class cModel;
class cLighting;
class cSkyBox;

class cScene
{
public:
    cScene();
    cScene(std::vector<cBase3DGameObject*>&& gameObjects, std::vector<cLighting*>&& lighting,
          std::vector<cCamera*>&& cameras, std::vector<cSkyBox*>&& skyBox);
    ~cScene();

    bool addGameObject(uint32_t name, cModel *model);
    bool addLighting(uint32_t name);
    bool addCamera(uint32_t name);

    bool deleteGameObject(uint32_t name);
    bool deleteLighting(uint32_t name);
    bool deleteCamera(uint32_t name);

    bool setSkybox(cModel *model);
    void setCurrentCamera(uint32_t name);

public:
    cBase3DGameObject *gameObject(uint32_t objectName) const;
    cCamera *camera(uint32_t cameraName) const;
    cLighting *lighting(uint32_t lightName) const;

    const std::vector<cLighting*>& lighings() const;
    const std::vector<cBase3DGameObject*>& gameObjects() const;
    const std::vector<cCamera*>& cameras() const;

    cCamera *currentCamera() const;
    cSkyBox *skybox() const;

private:
    cCamera* m_currentCamera = nullptr;
    cLighting* m_currentLighting = nullptr;
    cSkyBox* m_skyBox = nullptr;

    std::vector<cSkyBox*> m_skyBoxes;
    std::vector<cCamera*> m_cameras;
    std::vector<cLighting*> m_lightings;
    std::vector<cBase3DGameObject*> m_gameObjects;
    //std::vector<Base3DPhysicsObject *> m_physicsObject;
};


#endif // SCENE_H
