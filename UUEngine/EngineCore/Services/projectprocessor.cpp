#include "projectprocessor.h"
#include "Folders/materiallib.h"

ProjectProcessor *ProjectProcessor::m_instance = nullptr;

ProjectProcessor::ProjectProcessor()
{
    m_scriptFolder = ScriptFolder::getInstance();
    m_textureFolder = TextureFolder::getInstance();
    m_modelFolder = ModelFolder::getInstance();
}

ProjectProcessor::~ProjectProcessor()
{
    delete m_projectLayout;
}


//
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

void ProjectProcessor::createProject(const QString &path, const QString &projectName)
{

    QDir dir(path);
    m_projectInfo.m_projectPath = path;

    dir.mkdir(projectName);
    dir.cd(projectName);
    dir.mkdir("Models");
    dir.mkdir("Textures");
    dir.mkdir("Scripts");

    m_projectInfo.m_projectName = projectName;
    m_projectInfo.m_projectPath = path + '/' + projectName;

    QFile file(m_projectInfo.m_projectPath + "/" + m_projectInfo.m_projectName + ".uupj");
    file.open(QIODevice::WriteOnly);
    file.close();
}


//SAVE FILE

void ProjectProcessor::saveProject( QHash<QString, Scene *> scenes,const QString & path,const QString &projectName)
{
    try{

        if(projectName != "" && path != ""){
            m_projectInfo.m_projectName = projectName;
            m_projectInfo.m_projectPath = path;
        }


        QFile file(m_projectInfo.m_projectPath + '/' + m_projectInfo.m_projectName + ".uupj");

        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream stream(&file);
            foreach (auto key, scenes.keys()) {
                stream << saveScene(key, scenes[key]);
            }

            file.close();

        }
        else{
            throw std::runtime_error("Save project file error");
        }
    }
    catch(...){
        throw std::runtime_error("Save project file error");
    }

}


QString ProjectProcessor::saveScene(const QString & sceneName, Scene *scene)
{

    QString savedObjects = "#" + sceneName;
    try {
        savedObjects += saveSkybox(scene->skybox());
        savedObjects += saveCameras(scene->camerasHash());
        savedObjects += saveLightins(scene->lighingsHash());
        savedObjects += saveGameObjects(scene->gameObjectsHash()) + '\n';
    } catch (...) {
        throw std::runtime_error(("Save scene " + sceneName + " error").toStdString());
    }

    return savedObjects;
}

QString ProjectProcessor::saveSkybox(SkyBox *skybox)
{
    QString savedObject = " SKYBOX ";

    auto objectModel = dynamic_cast<SimpleModel *>(skybox->model());
    savedObject += objectModel->modelParticle()->material()->diffuseMapPath();
    savedObject += saveScripts(m_scriptFolder->scripts("Skybox"));

    return savedObject;
}
/// КОГДА ПОМЕНЯЮ КАМЕРУ НАДО БУДЕТ И СОХРАНЕНИЕ ПОМЕНЯТЬ
QString ProjectProcessor::saveCameras(QHash<QString, Camera *> cameras)
{

    QString savedObjects = " CAMERAS ";

    foreach (auto cameraName, cameras.keys()) {

        savedObjects += '+' + cameraName + '|';
        savedObjects += saveBaseParams(cameras[cameraName]);
        savedObjects += saveScripts(m_scriptFolder->scripts(cameraName));
    }

    return savedObjects;
}

/// КОГДА ПОМЕНЯЮ СВЕТ НАДО БУДЕТ И СОХРАНЕНИЕ ПОМЕНЯТЬ
QString ProjectProcessor::saveLightins(QHash<QString, Lighting *> lightings)
{
    QString savedObjects = " LIGHTINGS ";

    foreach (auto lightingName, lightings.keys()) {
        savedObjects += '+' + lightingName + '|';
        savedObjects += saveBaseParams(lightings[lightingName]);
        savedObjects += saveScripts(m_scriptFolder->scripts(lightingName));
    }
    return savedObjects;
}

QString ProjectProcessor::saveGameObjects(QHash<QString, Base3DGameObject *> gameObjects)
{
    QString savedObjects =  " BASE3DGAMEOBJECT ";

    foreach (auto gameObjectName, gameObjects.keys()) {
        auto gameObject = gameObjects[gameObjectName];

        savedObjects += '+' + gameObjectName + '|';
        savedObjects += saveBaseParams(gameObject);
        savedObjects += saveModel(gameObjectName, gameObject);
        savedObjects += saveScripts(m_scriptFolder->scripts(gameObjectName));

    }

    return savedObjects;
}


QString ProjectProcessor::saveBaseParams(BaseEngineObject *object)
{
        return QString("%1 %2 %3 %4 ").arg(object->modelMatrix().row(0)[0]).arg(object->modelMatrix().row(0)[1]).arg(object->modelMatrix().row(0)[2]).arg(object->modelMatrix().row(0)[3]) +
               QString("%1 %2 %3 %4 ").arg(object->modelMatrix().row(1)[0]).arg(object->modelMatrix().row(1)[1]).arg(object->modelMatrix().row(1)[2]).arg(object->modelMatrix().row(1)[3]) +
            QString("%1 %2 %3 %4 ").arg(object->modelMatrix().row(2)[0]).arg(object->modelMatrix().row(2)[1]).arg(object->modelMatrix().row(2)[2]).arg(object->modelMatrix().row(2)[3]) +
            QString("%1 %2 %3 %4|").arg(object->modelMatrix().row(3)[0]).arg(object->modelMatrix().row(3)[1]).arg(object->modelMatrix().row(3)[2]).arg(object->modelMatrix().row(3)[3]);
    //я не знаю как это сделать красиво и эффективно:(
    //(просто выгрузка модельной матрицы)
}

QString ProjectProcessor::saveModel(const QString &objectName, Base3DGameObject *gameObject)
{
    QString savedObject;

    if(gameObject->model()->modelType() == ModelType::CustomModel){
        return "CUSTOM_MODEL|" + m_modelFolder->models(objectName).join(' ') + "|";
    }
    else{
        auto simpleModel = dynamic_cast<SimpleModel *>(gameObject->model());
        return "SIMPLE_MODEL|" + m_modelFolder->models(objectName).join(' ') + ",MATERIAL(" +
               saveMaterial(simpleModel->modelParticle()->material()) + ")|";
    }
    return savedObject;
}

QString ProjectProcessor::saveMaterial(Material *material)
{
    auto vectorConverter = [](QVector3D vec) -> QString{
        return QString("%1 %2 %3 ").arg(vec.x()).arg(vec.y()).arg(vec.z());
    };

    return vectorConverter(material->ambienceColor())+
        vectorConverter(material->diffuseColor()) + vectorConverter(material->specularColor()) +
        material->diffuseMapPath()+ ' ' + material->normalMapPath() + ' ' + QString::number(material->shinnes()) + '|';

}

QString ProjectProcessor::saveScripts(QVector<QString> scripts)
{
    return scripts.join(' ');
}

/////////////////////////////////LOAD FILE


QHash<QString, Scene *>  ProjectProcessor::loadProject(const QString & path)
{
    QHash<QString, Scene *> scenes;

    try {
        QFile file(path);
        auto pathList = path.split('/');
        m_projectInfo.m_projectPath = path;
        m_projectInfo.m_projectName = pathList[pathList.size() - 1];

        if(file.open(QIODevice::ReadOnly)){
            QTextStream stream(&file);
            try {
                QString fileInfo = stream.readAll();
                QVector<QString> sceneInfo = fileInfo.split('\n');

                QRegularExpression regex("#(.*) SKYBOX(.+) CAMERAS(.+) LIGHTINGS (.+) BASE3DGAMEOBJECT(.+)");

                foreach (auto scene, sceneInfo) {
                    QRegularExpressionMatchIterator matchIterator = regex.globalMatch(scene);

                    QRegularExpressionMatch matchObject = matchIterator.next();
                    scenes.insert(matchObject.captured(0), new Scene(loadGameObjects(matchObject.captured(5).split('+')),
                                                                        loadLightins(matchObject.captured(4).split('+')),
                                                                        loadCameras(matchObject.captured(3).split('+')),
                                                                     loadSkybox(matchObject.captured(2))));


                }

            } catch (...) {
                throw std::runtime_error("Reading project file error");
            }

            file.close();
        }
        else{
            throw std::runtime_error("Open project file error");
        }
    } catch (...) {
        throw std::runtime_error("Loading project file error");
    }

    return scenes;
}


SkyBox *ProjectProcessor::loadSkybox(const QString &skybox)
{
    return new SkyBox(m_modelBuilder.createSkybox(100.0f,skybox));
}


QHash<QString, Camera *> ProjectProcessor::loadCameras(const QVector<QString> &cameraObjects)
{
    QHash<QString, Camera *> cameras;

    for (int i = 1; i < cameraObjects.size(); ++i) {
        auto params = cameraObjects[i].split('|');
        auto camera = new Camera();

        camera->setModelMatrix(loadBaseParams(params[1]));
        cameras.insert(params[0], camera);

        loadScripts(params[0],params[2]);
    }

    return cameras;
}

QHash<QString, Lighting *> ProjectProcessor::loadLightins(const QVector<QString> &lightingObjects)
{
    QHash<QString, Lighting *> lightings;

    for (int i = 1; i < lightingObjects.size(); ++i) {

        auto params = lightingObjects[i].split('|');
        auto lighting = new Lighting();

        lighting->setModelMatrix(loadBaseParams(params[1]));
        lightings.insert(params[0], lighting);

        loadScripts(params[0],params[2]);
    }

    return lightings;
}

QHash<QString, Base3DGameObject *> ProjectProcessor::loadGameObjects(const QVector<QString> &gameObjectParams)
{
    QHash<QString, Base3DGameObject *> gameObjects;

    for (int i = 1; i < gameObjectParams.size(); ++i) {

        auto params = gameObjectParams[i].split('|');

        auto object = new Base3DGameObject(loadModel(params[2],params[3]));
        object->setModelMatrix(loadBaseParams(params[1]));

        gameObjects.insert(params[0], object);
        m_scriptFolder->addScript(params[0], params[4]);
    }

    return gameObjects;
}


Model *ProjectProcessor::loadModel(const QString &objectType, const QString &modelParams)
{
    if(objectType == "CUSTOM_MODEL"){
        m_modelLoader.setStrategy(new OBJModelLoadStraregy());
        return m_modelLoader.createModel(modelParams);

    }

    SimpleModel *model;

    QRegularExpression paramsRegex("(\\w*)\\((.*?)\\)");
    QRegularExpressionMatchIterator matchIterator = paramsRegex.globalMatch(modelParams);
    QRegularExpressionMatch matchObject = matchIterator.next();

    if(matchObject.captured(0) == "CUBE") {
        QVector<QString> modelParams = matchObject.captured(1).split(' ');
        model = m_modelBuilder.createCube(modelParams[0].toFloat(),modelParams[1].toFloat(),modelParams[2].toFloat());
    }
    else if(matchObject.captured(0) == "PYRAMID"){
        QVector<QString> modelParams = matchObject.captured(1).split(' ');
        model = m_modelBuilder.createPyramide(modelParams[0].toFloat(),modelParams[1].toFloat());
    }
    else{
       model = new SimpleModel();
    }

    matchObject = matchIterator.next();
    model->modelParticle()->setMaterial(loadMaterial(matchObject.captured(1)));

    return model;
}

Material *ProjectProcessor::loadMaterial(const QString &material)
{
    auto params = material.split(' ');

    Material *mat = new Material();

    mat->setAmbienceColor(QVector3D(params[0].toFloat(),params[1].toFloat(),params[2].toFloat()));
    mat->setDiffuseColor(QVector3D(params[3].toFloat(),params[4].toFloat(),params[5].toFloat()));
    mat->setSpecularColor(QVector3D(params[6].toFloat(),params[7].toFloat(),params[8].toFloat()));
    mat->setDiffuseMap(std::move(params[9]));
    mat->setNormalMap(std::move(params[10]));
    mat->setShinnes(params[11].toFloat());

    return mat;
}


QMatrix4x4 ProjectProcessor::loadBaseParams(const QString &matrixParams)
{
    auto params = matrixParams.split(' ');

    QMatrix4x4 mat;
    mat.setRow(0, QVector4D(params[0].toFloat(),params[1].toFloat(),params[2].toFloat(),params[3].toFloat()));
    mat.setRow(1, QVector4D(params[4].toFloat(),params[5].toFloat(),params[6].toFloat(),params[7].toFloat()));
    mat.setRow(2, QVector4D(params[8].toFloat(),params[9].toFloat(),params[10].toFloat(),params[11].toFloat()));
    mat.setRow(3, QVector4D(params[12].toFloat(),params[13].toFloat(),params[14].toFloat(),params[15].toFloat()));

    return mat;
}

void ProjectProcessor::loadScripts(const QString &objectName, const QString &scripts)
{
    foreach (auto script, scripts.split(' ')) {
       m_scriptFolder->addScript(objectName, script);
    }
}


void ProjectProcessor::setLayout(QBoxLayout &layout)
{
    m_projectLayout = &layout;
}

ProjectProcessor *ProjectProcessor::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new ProjectProcessor();
    }
    return m_instance;
}
