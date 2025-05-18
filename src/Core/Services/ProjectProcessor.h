#ifndef PROJECTPROCESSOR_H
#define PROJECTPROCESSOR_H

#include "Core/Services/ProjectInfo.h"

#include "BaseEngineObject_generated.h"
#include "Scene_generated.h"

#include "flatbuffers/flatbuffers.h"

#include <vector>

class cProjectInfo;
class cSceneManager;
class cTextureManager;
class cScene;
class cCamera;
class cLighting;
class cBase3DGameObject;
class cSkyBox;
class cMaterial;
class cBaseEngineObject;

class cProjectProcessor
{
public:
    cProjectProcessor(cSceneManager *sceneManager, cTextureManager *textureManager);
    ~cProjectProcessor() = default;

    void loadProject(std::string_view path);
    void saveProject(std::string_view path);
    void createProject(std::string_view path, std::string_view name);
    void closeProject(std::unordered_map<std::string, cScene*>& scenes);

private:
    void saveScene(std::string_view path, cScene* scene);
    void saveCameras(flatbuffers::FlatBufferBuilder& builder, std::vector<cCamera*>& cameras);
    void saveLightings(flatbuffers::FlatBufferBuilder& builder, std::vector<cLighting*>& lightings);
    void saveGameObjects(flatbuffers::FlatBufferBuilder& builder, std::vector<cBase3DGameObject*>& gameObjects);
    void saveSkybox(flatbuffers::FlatBufferBuilder& builder, cSkyBox* skybox);

    flatbuffers::Offset<UUEngine::BaseEngineObject> saveBaseParams(flatbuffers::FlatBufferBuilder& builder, cBaseEngineObject* object);
    flatbuffers::Offset<UUEngine::Model> saveModel(flatbuffers::FlatBufferBuilder& builder, const std::string& objectName, cBase3DGameObject* gameObject);
    flatbuffers::Offset<UUEngine::Material> saveMaterial(flatbuffers::FlatBufferBuilder& builder, cMaterial* material);
    //flatbuffers::Offset<UUEngine::BaseEngineObject> saveScripts(flatbuffers::FlatBufferBuilder& builder, std::vector<std::string>& scripts);

    void loadBaseParams(const std::string& objectMatrix, cBaseEngineObject* object);

//     void saveProject(const std::unordered_map<std::string, cScene *>& scenes, const std::string &path = "");
//     std::unordered_map<std::string, cScene*> loadProject(std::string path);
//     void createProject(const std::string &path, const std::string &name);
//     void closeProject(std::unordered_map<std::string, cScene *> scenes);

//     void setLayout(QBoxLayout &layout);
// private:
//     std::string saveScene(const std::string &sceneName, cScene *scene);
//     std::string saveCameras(const std::unordered_map<std::string, cCamera *>& cameras);
//     std::string saveLightings(const std::unordered_map<std::string, cLighting *>& lightings);
//     std::string saveGameObjects(const std::unordered_map<std::string, cBase3DGameObject *>& gameObjects);
//     std::string saveSkybox(cSkyBox *skybox);

//     std::string saveBaseParams(cBaseEngineObject *object);
//     std::string saveModel(const std::string &objectName, cBase3DGameObject *gameObject);
//     std::string saveMaterial(cMaterial *material);
//     std::string saveScripts(std::vector<std::string> scripts);

//     std::unordered_map<std::string, cScene *> loadScene(const std::string sceneName, cScene *scene);
//     std::unordered_map<std::string, cCamera *> loadCameras(const std::vector<std::string> &cameras);
//     std::unordered_map<std::string, cLighting *> loadLightins(const std::vector<std::string> &lights);
//     std::unordered_map<std::string, cBase3DGameObject *> loadGameObjects(const std::vector<std::string> &gameObjects);
//     cSkyBox *loadSkybox(const std::string &skybox);

//     void loadBaseParams(const std::string &objectMatrix, cBaseEngineObject *object);
//     cModel *loadModel(const std::string &objectName, const std::string &objectType, const std::string &gameObject);
//     cMaterial* loadMaterial(const std::string &objectName,const std::string &material);
//     void loadScripts(const std::string &objectName,const std::string &scripts);

private:
    cProjectInfo m_projectInfo;
    cSceneManager* m_sceneManager = nullptr;
    cTextureManager* m_textureManager = nullptr;

    //QBoxLayout *m_projectLayout;
};

#endif // PROJECTPROCESSOR_H
