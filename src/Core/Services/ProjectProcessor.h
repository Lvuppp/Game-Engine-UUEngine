#ifndef PROJECTPROCESSOR_H
#define PROJECTPROCESSOR_H

#include "Entities/Scene.h"
#include "Core/Services/ModelLoader.h"
#include "Core/Services/ModelBuilder.h"
#include "Core/Services/ProjectInfo.h"
#include "Core/Folders/ScriptFolder.h"
#include "Core/Folders/ModelFolder.h"
#include "Core/Folders/TextureFolder.h"

#include <string>
#include <QFile>
#include <QTextStream>
#include <QHash>
#include <QVBoxLayout>

class cProjectProcessor
{
public:
    cProjectProcessor();
    ~cProjectProcessor();

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
    //cTextureFolder *m_textureFolder;
    cModelFolder *m_modelFolder;
    cScriptFolder *m_scriptFolder;
    cProjectInfo m_projectInfo;

    cModelBuilder m_modelBuilder;
    cModelLoader m_modelLoader;

    QBoxLayout *m_projectLayout;
};

#endif // PROJECTPROCESSOR_H
