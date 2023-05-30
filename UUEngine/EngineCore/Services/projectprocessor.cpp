#include "projectprocessor.h"
#include "Folders/materiallib.h"
#include "Models/custommodel.h"
#include "Models/simplemodel.h"

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

void ProjectProcessor::createProject(const QString &path, const QString &name)
{

    QDir dir(path);
    m_projectInfo.m_projectPath = path;

    dir.mkdir(name);
    dir.cd(name);
    dir.mkdir("Models");
    dir.mkdir("Textures");
    dir.mkdir("Scripts");

    m_projectInfo.m_projectPath = path + '/' + name + "/" + name + ".uupj";
    m_projectInfo.m_projectName = name;
    m_projectInfo.m_projectFolder = path + '/' + name;

    QFile file(m_projectInfo.m_projectPath);
    file.open(QIODevice::WriteOnly);
    file.close();
}

void ProjectProcessor::closeProject(QHash<QString, Scene *> scenes)
{
    try {
        saveProject(scenes);

        m_projectInfo.m_projectName = "";
        m_projectInfo.m_projectPath = "";
        m_projectInfo.m_projectFolder = "";

    }
    catch (const std::exception& e) {
        qDebug() << "Close file error";
    }
}


//SAVE FILE

void ProjectProcessor::saveProject(QHash<QString, Scene *> scenes,const QString & path)
{
    try{

        if(path != ""){
            auto pathSplit = path.split('/');

            m_projectInfo.m_projectPath = path;
            m_projectInfo.m_projectFolder = pathSplit.mid(0, pathSplit.size() - 1).join('/');
            m_projectInfo.m_projectName = pathSplit[pathSplit.size() - 1].split('.')[0];
        }


        QFile file(m_projectInfo.m_projectPath);

        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream stream(&file);
            auto keys = scenes.keys();
            for (int i = 0; i < keys.size(); i++) {
                stream << saveScene (keys[i], scenes[keys[i]]);

                if(i != keys.size() - 1)
                    stream << '\n';
            }

            file.close();

        }
        else{
            qDebug() << "Can`t open project";
            return;

        }

    }
    catch(const std::exception& e){
        qDebug() << "Save project file error: " << e.what();
    }

}


QString ProjectProcessor::saveScene(const QString & sceneName, Scene *scene)
{

    QString savedObjects = "#" + sceneName;
    try {
        savedObjects += saveSkybox(scene->skybox());
        savedObjects += saveCameras(scene->camerasHash());
        savedObjects += saveLightins(scene->lighingsHash());
        savedObjects += saveGameObjects(scene->gameObjectsHash());
    } catch (const std::exception& e) {
        qDebug() << "Save scene " + sceneName + " error:" + e.what();
    }

    return savedObjects;
}

QString ProjectProcessor::saveSkybox(SkyBox *skybox)
{
    QString savedObject = " SKYBOX";

    if(skybox){
        auto objectModel = dynamic_cast<SimpleModel *>(skybox->model());
        savedObject += objectModel->modelParticle()->material()->diffuseMapPath();
        savedObject += saveScripts(m_scriptFolder->scripts("Skybox"));
    }
    else{
        savedObject += "null";
    }

    return savedObject;
}
/// КОГДА ПОМЕНЯЮ КАМЕРУ НАДО БУДЕТ И СОХРАНЕНИЕ ПОМЕНЯТЬ
QString ProjectProcessor::saveCameras(QHash<QString, Camera *> cameras)
{

    QString savedObjects = " CAMERAS";

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
    QString savedObjects = " LIGHTINGS";

    foreach (auto lightingName, lightings.keys()) {
        savedObjects += '+' + lightingName + '|';
        savedObjects += saveBaseParams(lightings[lightingName]);
        savedObjects += saveScripts(m_scriptFolder->scripts(lightingName));
    }
    return savedObjects;
}

QString ProjectProcessor::saveGameObjects(QHash<QString, Base3DGameObject *> gameObjects)
{
    QString savedObjects =  " BASE3DGAMEOBJECT";

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
    auto vectorConverter = [](QVector3D vec) -> QString{
        return QString("%1 %2 %3 ").arg(vec.x()).arg(vec.y()).arg(vec.z());
    };

    float angleX, angleY;
    QVector3D vectorX, vectorY;
    object->rotationX().getAxisAndAngle(&vectorX ,&angleX);
    object->rotationY().getAxisAndAngle(&vectorY ,&angleY);

    return vectorConverter(object->coordinates()) + QString::number(angleX) + ' ' +vectorConverter(vectorX)
           + QString::number(angleY) + ' ' + vectorConverter(vectorY) + QString::number(object->scale()) + '|';

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
        material->diffuseMapPath()+ ' ' + material->normalMapPath() + ' ' + QString::number(material->shinnes());

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
        m_projectInfo.m_projectPath = path;

        auto pathSplit = path.split('/');
        m_projectInfo.m_projectName = pathSplit[pathSplit.size() - 1].split('.')[0];
        m_projectInfo.m_projectFolder = pathSplit.mid(0, pathSplit.size() - 1).join('/');

        QFile file(path);

        if(file.open(QIODevice::ReadOnly)){
            QTextStream stream(&file);
            try {
                QString fileInfo = stream.readAll();
                QVector<QString> sceneInfo = fileInfo.split('\n');

                QRegularExpression regex("#(.+) SKYBOX(.+) CAMERAS(.+) LIGHTINGS(.+) BASE3DGAMEOBJECT(.+)");

                foreach (auto scene, sceneInfo) {
                    QRegularExpressionMatchIterator matchIterator = regex.globalMatch(scene);

                    QRegularExpressionMatch matchObject = matchIterator.next();
                    qDebug() << matchObject.captured(0);
                    qDebug() << matchObject.captured(1);
                    qDebug() << matchObject.captured(2);
                    qDebug() << matchObject.captured(3);
                    qDebug() << matchObject.captured(4);
                    qDebug() << matchObject.captured(5);

                    scenes.insert(matchObject.captured(1), new Scene(loadGameObjects(matchObject.captured(5).split('+')),
                                                                        loadLightins(matchObject.captured(4).split('+')),
                                                                        loadCameras(matchObject.captured(3).split('+')),
                                                                     loadSkybox(matchObject.captured(2))));


                }

            } catch (const std::exception& e) {
                qDebug() << "Reading project file error" << e.what();
            }

            file.close();
        }
        else{
            qDebug() << "Open project file error";
        }
    } catch (const std::exception& e) {
        qDebug() << "Loading project file error" << e.what();
    }

    return scenes;
}


QHash<QString, Scene *> ProjectProcessor::loadScene(const QString sceneName, Scene *scene)
{

}


SkyBox *ProjectProcessor::loadSkybox(const QString &skybox)
{
    if(skybox == "null") return nullptr;
    return new SkyBox(m_modelBuilder.createSkybox(100.0f,skybox));
}


QHash<QString, Camera *> ProjectProcessor::loadCameras(const QVector<QString> &cameraObjects)
{
    QHash<QString, Camera *> cameras;

    for (int i = 1; i < cameraObjects.size(); ++i) {
        auto params = cameraObjects[i].split('|');
        auto camera = new Camera();

        loadBaseParams(params[1],camera);
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

        loadBaseParams(params[1],lighting);
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

        auto object = new Base3DGameObject(loadModel(params[0], params[2],params[3]));
        loadBaseParams(params[1], object);

        gameObjects.insert(params[0], object);
        m_scriptFolder->addScript(params[0], params[4]);
    }

    return gameObjects;
}


Model *ProjectProcessor::loadModel(const QString &objectName, const QString &objectType, const QString &modelParams)
{
    if(objectType == "CUSTOM_MODEL"){
        m_modelLoader.setFactory(new OBJModelFactory());
        m_modelFolder->append(objectName, modelParams);

        return m_modelLoader.createModel(m_projectInfo.projectFolder() + "/Models/" + modelParams);
    }

    SimpleModel *model;

    QRegularExpression paramsRegex("(\\w*)\\((.*?)\\)");
    QRegularExpressionMatchIterator matchIterator = paramsRegex.globalMatch(modelParams);
    QRegularExpressionMatch matchObject = matchIterator.next();

    m_modelFolder->append(objectName, matchObject.captured(0));

    if(matchObject.captured(1) == "CUBE") {
        QVector<QString> modelParams = matchObject.captured(2).split(' ');
        model = m_modelBuilder.createCube(modelParams[0].toFloat(),modelParams[1].toFloat(),modelParams[2].toFloat());
    }
    else if(matchObject.captured(1) == "PYRAMID"){
        QVector<QString> modelParams = matchObject.captured(2).split(' ');
        model = m_modelBuilder.createPyramide(modelParams[0].toFloat(),modelParams[1].toFloat());
    }
    else if(matchObject.captured(1) == "SPHERE"){
        QVector<QString> modelParams = matchObject.captured(2).split(' ');
        model = m_modelBuilder.createSphere(modelParams[0].toFloat(),modelParams[1].toInt(),modelParams[2].toInt());
    }
    else if(matchObject.captured(1) == "PRISM"){
        QVector<QString> modelParams = matchObject.captured(2).split(' ');
        model = m_modelBuilder.createPrism(modelParams[0].toFloat(),modelParams[1].toFloat(),modelParams[2].toFloat(),modelParams[3].toFloat());
    }
    else if(matchObject.captured(1) == "CONE"){
        QVector<QString> modelParams = matchObject.captured(2).split(' ');
        model = m_modelBuilder.createCone(modelParams[0].toFloat(),modelParams[1].toFloat(), modelParams[2].toInt());
    }
    else if(matchObject.captured(1) == "CYLINDER"){
        QVector<QString> modelParams = matchObject.captured(2).split(' ');
        model = m_modelBuilder.createCylinder(modelParams[0].toFloat(),modelParams[1].toFloat(), modelParams[2].toInt());
    }
    else{
       model = new SimpleModel();
    }

    matchObject = matchIterator.next();
    model->modelParticle()->setMaterial(loadMaterial(objectName, matchObject.captured(2)));

    return model;
}

Material *ProjectProcessor::loadMaterial(const QString &objectName, const QString &material)
{
    auto params = material.split(' ');

    Material *mat = new Material();

    mat->setAmbienceColor(QVector3D(params[0].toFloat(),params[1].toFloat(),params[2].toFloat()));
    mat->setDiffuseColor(QVector3D(params[3].toFloat(),params[4].toFloat(),params[5].toFloat()));
    mat->setSpecularColor(QVector3D(params[6].toFloat(),params[7].toFloat(),params[8].toFloat()));

    if(params[9] != "null"){
       m_textureFolder->append(objectName, params[9]);
       mat->setDiffuseMap(m_projectInfo.projectPath() + "/Textures/" + params[9]);
    }

    if(params[10] != "null"){
       m_textureFolder->append(objectName, params[10]);
       mat->setNormalMap(m_projectInfo.projectPath() + "/Textures/" +params[10]);
    }

    mat->setShinnes(params[11].toFloat());

    return mat;
}


void ProjectProcessor::loadBaseParams(const QString &matrixParams, BaseEngineObject *object)
{
    auto params = matrixParams.split(' ');
    object->setCoordinates(QVector3D(params[0].toFloat(),params[1].toFloat(),params[2].toFloat()));
    object->rotateX(QQuaternion::fromAxisAndAngle(QVector3D(params[3].toFloat(),params[4].toFloat(),params[5].toFloat()), params[6].toFloat()));
    object->rotateY(QQuaternion::fromAxisAndAngle(QVector3D(params[7].toFloat(),params[8].toFloat(),params[9].toFloat()), params[10].toFloat()));
    object->setScale(params[11].toFloat());
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
