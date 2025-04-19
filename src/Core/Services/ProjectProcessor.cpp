#include "ProjectProcessor.h"

#include "Core/Folders/MaterialLib.h"
#include "Utils/TextUtils.h"

#include <QDir>
#include <QRegularExpression>

cProjectProcessor::cProjectProcessor()
{
    // m_scriptFolder = cScriptFolder::getInstance();
    // m_textureFolder = cTextureFolder::getInstance();
    // m_modelFolder = cModelFolder::getInstance();
}

cProjectProcessor::~cProjectProcessor()
{
    delete m_projectLayout;
}

///////////// FILE FORMAT
// #SCENE_NAME|SCRIPT_PATH
// +SKYBOX
// OBJECT_NAME|DIFFUSE_MAP|SCRIPT_PATH ...
// +CAMERA
// OBJECT_NAME|MODEL_MATRIX|SCRIPT_PATH ...
// +LIGHTING
// OBJECT_NAME|MODEL_MATRIX|SCRIPT_PATH ...
// +BASE3DGAMEOBJECT
// OBJECT_NAME|MODEL_MATRIX|(CUSTOM_MODEL|MODEL_NAME)|(CUBE|PYRAMID|MATERIAL_PARAMS)|SCRIPT_PATH ...
// #SCENE_NAME ...



//CREATE PROJECT FOLDER

void cProjectProcessor::createProject(const std::string &path, const std::string &name)
{
    QDir dir(path.c_str());
    m_projectInfo.m_projectPath = path;

    dir.mkdir(name.c_str());
    dir.cd(name.c_str());
    dir.mkdir("Models");
    dir.mkdir("Textures");
    dir.mkdir("Scripts");

    m_projectInfo.m_projectPath = path + '/' + name + "/" + name + ".uupj";
    m_projectInfo.m_projectName = name;
    m_projectInfo.m_projectFolder = path + '/' + name;

    QFile file(m_projectInfo.m_projectPath.c_str());
    file.open(QIODevice::WriteOnly);
    file.close();
}

void cProjectProcessor::closeProject(std::unordered_map<std::string, cScene *> scenes)
{
    saveProject(scenes);

    m_projectInfo.m_projectName = "";
    m_projectInfo.m_projectPath = "";
    m_projectInfo.m_projectFolder = "";
}


//SAVE FILE

void cProjectProcessor::saveProject(const std::unordered_map<std::string, cScene *>& scenes, const std::string & path)
{
    if (path.empty())
    {
        auto pathSplit = text_utils::split(path, '/');
        const auto pathToProject = std::vector(pathSplit.cbegin(), pathSplit.cbegin() + pathSplit.size() - 2);

        m_projectInfo.m_projectPath = path;
        m_projectInfo.m_projectFolder = text_utils::join(pathToProject, '/');
        m_projectInfo.m_projectName = text_utils::split(pathSplit[pathSplit.size() - 1], '.')[0];
    }

    QFile file(m_projectInfo.m_projectPath.c_str());

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        for (auto [name, object] : scenes)
        {
            stream << saveScene(name, object).c_str();
        }

        stream << '\n';

        file.close();
    }
}


std::string cProjectProcessor::saveScene(const std::string & sceneName, cScene *scene)
{
    std::string savedObjects = "#" + sceneName;

    savedObjects += saveSkybox(scene->skybox());
    savedObjects += saveCameras(scene->camerasHash());
    savedObjects += saveLightings(scene->lighingsHash());
    savedObjects += saveGameObjects(scene->gameObjectsHash());

    return savedObjects;
}

std::string cProjectProcessor::saveSkybox(cSkyBox *skybox)
{
    std::string savedObject = " SKYBOX";

    if (skybox != nullptr)
    {
        auto objectModel = static_cast<cModel *>(skybox->model());
        savedObject += objectModel->getModelParticle(0)->getMaterial()->diffuseMapPath();
        savedObject += saveScripts(m_scriptFolder->scripts("Skybox"));
    }
    else{
        savedObject += "null";
    }

    return savedObject;
}
/// КОГДА ПОМЕНЯЮ КАМЕРУ НАДО БУДЕТ И СОХРАНЕНИЕ ПОМЕНЯТЬ
std::string cProjectProcessor::saveCameras(const std::unordered_map<std::string, cCamera *>& cameras)
{

    std::string savedObjects = " CAMERAS";

    for (const auto& [name, camera] : cameras) {

        savedObjects += '+' + name + '|';
        savedObjects += saveBaseParams(camera);
        savedObjects += saveScripts(m_scriptFolder->scripts(name));
    }

    return savedObjects;
}

/// КОГДА ПОМЕНЯЮ СВЕТ НАДО БУДЕТ И СОХРАНЕНИЕ ПОМЕНЯТЬ
std::string cProjectProcessor::saveLightings(const std::unordered_map<std::string, cLighting *>& lightings)
{
    std::string savedObjects = " LIGHTINGS";

    for (const auto& [name, object] : lightings)
    {
        savedObjects += '+' + name + '|';
        savedObjects += saveBaseParams(object);
        savedObjects += saveScripts(m_scriptFolder->scripts(name));
    }
    return savedObjects;
}

std::string cProjectProcessor::saveGameObjects(const std::unordered_map<std::string, cBase3DGameObject *>& gameObjects)
{
    std::string savedObjects =  " BASE3DGAMEOBJECT";

    for (const auto& [name, object] : gameObjects)
    {
        savedObjects += '+' + name + '|';
        savedObjects += saveBaseParams(object);
        savedObjects += saveModel(name, object);
        savedObjects += saveScripts(m_scriptFolder->scripts(name));

    }

    return savedObjects;
}


std::string cProjectProcessor::saveBaseParams(cBaseEngineObject *object)
{
    // auto vectorConverter = [](QVector3D vec) -> std::string{
    //     return std::string("%1 %2 %3 ").arg(vec.x()).arg(vec.y()).arg(vec.z());
    // };

    // float angleX, angleY;
    // QVector3D vectorX, vectorY;
    // object->rotationX().getAxisAndAngle(&vectorX ,&angleX);
    // object->rotationY().getAxisAndAngle(&vectorY ,&angleY);

    // return vectorConverter(object->coordinates()) + std::string::number(angleX) + ' ' +vectorConverter(vectorX)
    //        + std::string::number(angleY) + ' ' + vectorConverter(vectorY) + std::string::number(object->scale()) + '|';

}

std::string cProjectProcessor::saveModel(const std::string &objectName, cBase3DGameObject *gameObject)
{
    std::string savedObject;

    // if(gameObject->model()->modelType() == cModel::ModelType::CustomModel){
    //     return "CUSTOM_MODEL|" + m_modelFolder->model(objectName) + "|";
    // }
    // else{
    //     auto simpleModel = dynamic_cast<cSimpleModel *>(gameObject->model());
    //     return "SIMPLE_MODEL|" + m_modelFolder->model(objectName) + ",MATERIAL(" +
    //            saveMaterial(simpleModel->modelParticle()->material()) + ")|";
    // }
    return savedObject;
}

std::string cProjectProcessor::saveMaterial(cMaterial *material)
{
    // auto vectorConverter = [](QVector3D vec) -> std::string{
    //     return std::string("%1$%2$%3$").arg(vec.x()).arg(vec.y()).arg(vec.z());
    // };

    // return vectorConverter(material->ambienceColor())+
    //     vectorConverter(material->diffuseColor()) + vectorConverter(material->specularColor()) + material->diffuseMapPath().data() + '$' + material->normalMapPath().data() + '$' + std::string::number(material->shinnes());

}

std::string cProjectProcessor::saveScripts(std::vector<std::string> scripts)
{
//    return scripts.join(' ');
}

/////////////////////////////////LOAD FILE


std::unordered_map<std::string, cScene *>  cProjectProcessor::loadProject(std::string path)
{
    // std::unordered_map<std::string, cScene *> scenes;

    // try {
    //     m_projectInfo.m_projectPath = path;

    //     auto pathSplit = path.split('/');
    //     m_projectInfo.m_projectName = pathSplit[pathSplit.size() - 1].split('.')[0];
    //     m_projectInfo.m_projectFolder = pathSplit.mid(0, pathSplit.size() - 1).join('/');

    //     QFile file(path);

    //     if(file.open(QIODevice::ReadOnly)){
    //         QTextStream stream(&file);
    //         try {
    //             std::string fileInfo = stream.readAll();
    //             std::vector<std::string> sceneInfo = fileInfo.split('\n');

    //             QRegularExpression regex("#(.+) SKYBOX(.+) CAMERAS(.+) LIGHTINGS(.+) BASE3DGAMEOBJECT(.+)");

    //             foreach (auto scene, sceneInfo) {
    //                 if(scene == "")
    //                     return scenes;

    //                 QRegularExpressionMatchIterator matchIterator = regex.globalMatch(scene);

    //                 QRegularExpressionMatch matchObject = matchIterator.next();

    //                 scenes.insert(matchObject.captured(1), new cScene(loadGameObjects(matchObject.captured(5).split('+')),
    //                                                                     loadLightins(matchObject.captured(4).split('+')),
    //                                                                     loadCameras(matchObject.captured(3).split('+')),
    //                                                                  loadSkybox(matchObject.captured(2))));


    //             }

    //         } catch (const std::exception& e) {
    //             qDebug() << "Reading project file error" << e.what();
    //         }

    //         file.close();
    //     }
    //     else{
    //         qDebug() << "Open project file error";
    //     }
    // } catch (const std::exception& e) {
    //     qDebug() << "Loading project file error" << e.what();
    // }

    // return scenes;
}


std::unordered_map<std::string, cScene *> cProjectProcessor::loadScene(const std::string sceneName, cScene *scene)
{
    return std::unordered_map<std::string, cScene*>();
}


cSkyBox *cProjectProcessor::loadSkybox(const std::string &skybox)
{
    if(skybox == "null") return nullptr;
    return new cSkyBox(m_modelBuilder.createSkybox(100.0f, skybox));
}


std::unordered_map<std::string, cCamera *> cProjectProcessor::loadCameras(const std::vector<std::string> &cameraObjects)
{
//     std::unordered_map<std::string, cCamera *> cameras;

//     for (int i = 1; i < cameraObjects.size(); ++i) {
//         auto params = cameraObjects[i].split('|');
//         auto camera = new cCamera();

//         loadBaseParams(params[1],camera);
//         cameras.insert(params[0], camera);

//         loadScripts(params[0],params[2]);
//     }

//     return cameras;
 }

std::unordered_map<std::string, cLighting *> cProjectProcessor::loadLightins(const std::vector<std::string> &lightingObjects)
{
    // std::unordered_map<std::string, cLighting *> lightings;

    // for (int i = 1; i < lightingObjects.size(); ++i) {

    //     auto params = lightingObjects[i].split('|');
    //     auto lighting = new cLighting();

    //     loadBaseParams(params[1],lighting);
    //     lightings.insert(params[0], lighting);

    //     loadScripts(params[0],params[2]);
    // }

    // return lightings;
}

std::unordered_map<std::string, cBase3DGameObject *> cProjectProcessor::loadGameObjects(const std::vector<std::string> &gameObjectParams)
{
    // std::unordered_map<std::string, cBase3DGameObject *> gameObjects;

    // for (int i = 1; i < gameObjectParams.size(); ++i) {

    //     auto params = gameObjectParams[i].split('|');

    //     auto object = new cBase3DGameObject(loadModel(params[0], params[2],params[3]));
    //     loadBaseParams(params[1], object);

    //     gameObjects.insert(params[0], object);
    //     m_scriptFolder->addScript(params[0], params[4]);
    // }

    // return gameObjects;
}


cModel *cProjectProcessor::loadModel(const std::string &objectName, const std::string &objectType, const std::string &modelParams)
{
    // if(objectType == "CUSTOM_MODEL"){
    //     m_modelLoader.setFactory(new OBJModelFactory());
    //     m_modelFolder->append(objectName, modelParams);

    //     return m_modelLoader.createModel(m_projectInfo.projectFolder() + "/Models/" + modelParams);
    // }

    // cModel *model;

    // QRegularExpression paramsRegex("(\\w*)\\((.*?)\\)");
    // QRegularExpressionMatchIterator matchIterator = paramsRegex.globalMatch(modelParams);
    // QRegularExpressionMatch matchObject = matchIterator.next();

    // m_modelFolder->append(objectName, matchObject.captured(0));

    // if(matchObject.captured(1) == "CUBE") {
    //     std::vector<std::string> modelParams = matchObject.captured(2).split(' ');
    //     model = m_modelBuilder.createCube(modelParams[0].toFloat(),modelParams[1].toFloat(),modelParams[2].toFloat());
    // }
    // else if(matchObject.captured(1) == "PYRAMID"){
    //     std::vector<std::string> modelParams = matchObject.captured(2).split(' ');
    //     model = m_modelBuilder.createPyramide(modelParams[0].toFloat(),modelParams[1].toFloat());
    // }
    // else if(matchObject.captured(1) == "SPHERE"){
    //     std::vector<std::string> modelParams = matchObject.captured(2).split(' ');
    //     model = m_modelBuilder.createSphere(modelParams[0].toFloat(),modelParams[1].toInt(),modelParams[2].toInt());
    // }
    // else if(matchObject.captured(1) == "PRISM"){
    //     std::vector<std::string> modelParams = matchObject.captured(2).split(' ');
    //     model = m_modelBuilder.createPrism(modelParams[0].toFloat(),modelParams[1].toFloat(),modelParams[2].toFloat(),modelParams[3].toFloat());
    // }
    // else if(matchObject.captured(1) == "CONE"){
    //     std::vector<std::string> modelParams = matchObject.captured(2).split(' ');
    //     model = m_modelBuilder.createCone(modelParams[0].toFloat(),modelParams[1].toFloat(), modelParams[2].toInt());
    // }
    // else if(matchObject.captured(1) == "CYLINDER"){
    //     std::vector<std::string> modelParams = matchObject.captured(2).split(' ');
    //     model = m_modelBuilder.createCylinder(modelParams[0].toFloat(),modelParams[1].toFloat(), modelParams[2].toInt());
    // }
    // else{
    //    model = new cModel();
    // }

    // matchObject = matchIterator.next();
    // model->getModelParticle(0)->setMaterial(loadMaterial(objectName, matchObject.captured(2)));

    // return model;
}

cMaterial *cProjectProcessor::loadMaterial(const std::string &objectName, const std::string &material)
{
    // auto params = material.split('$');

    // cMaterial *mat = new cMaterial();

    // mat->setAmbienceColor(QVector3D(params[0].toFloat(),params[1].toFloat(),params[2].toFloat()));
    // mat->setDiffuseColor(QVector3D(params[3].toFloat(),params[4].toFloat(),params[5].toFloat()));
    // mat->setSpecularColor(QVector3D(params[6].toFloat(),params[7].toFloat(),params[8].toFloat()));

    // if(params[9] != "null"){
    //    m_textureFolder->append(objectName, params[9]);
    //    mat->setDiffuseMap(params[9].toStdString());
    // }

    // if(params[10] != "null"){
    //    m_textureFolder->append(objectName, params[10]);
    //    mat->setNormalMap(params[10].toStdString());
    // }

    // mat->setShinnes(params[11].toFloat());

    // return mat;
}


void cProjectProcessor::loadBaseParams(const std::string &matrixParams, cBaseEngineObject *object)
{
    // auto params = matrixParams.split(' ');
    // object->setCoordinates(QVector3D(params[0].toFloat(),params[1].toFloat(),params[2].toFloat()));
    // object->rotateX(QQuaternion::fromAxisAndAngle(QVector3D(params[3].toFloat(),params[4].toFloat(),params[5].toFloat()), params[6].toFloat()));
    // object->rotateY(QQuaternion::fromAxisAndAngle(QVector3D(params[7].toFloat(),params[8].toFloat(),params[9].toFloat()), params[10].toFloat()));
    // object->setScale(params[11].toFloat());
}

void cProjectProcessor::loadScripts(const std::string &objectName, const std::string &scripts)
{
    // foreach (auto script, scripts.split(' ')) {
    //    m_scriptFolder->addScript(objectName, script);
    // }
}


void cProjectProcessor::setLayout(QBoxLayout &layout)
{
    m_projectLayout = &layout;
}
