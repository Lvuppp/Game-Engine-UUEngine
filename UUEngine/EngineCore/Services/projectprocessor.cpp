#include "projectprocessor.h"
#include "Folders/materiallib.h"

ProjectProcessor *ProjectProcessor::m_instance = nullptr;

ProjectProcessor::ProjectProcessor()
{

}

ProjectProcessor::~ProjectProcessor()
{
    delete m_projectLayout;
}


//
///////////// FILE FORMAT
// #SCENE_NAME$SCRIPT_PATH
// +CAMERA
// OBJECT_NAME$MODEL_MATRIX$SCRIPT_PATH ...
// +LIGHTING
// OBJECT_NAME$MODEL_MATRIX$SCRIPT_PATH ...
// +BASE3DGAMEOBJECT
// OBJECT_NAME$MODEL_MATRIX$(CUSTOM_MODEL$MODEL_NAME)|(CUBE|PYRAMID$MATERIAL_PARAMS)$SCRIPT_PATH ...
// #SCENE_NAME ...


//////////////////////////////////SAVE FILE

void ProjectProcessor::saveProject(const QString & path, QHash<QString, Scene *> scenes, const QString &projectName)
{
    try{

        if(projectName != ""){
            m_projectInfo.m_projectName = projectName;
        }

        QDir dir(path);

        dir.mkdir(projectName);
        dir.cd(m_projectInfo.m_projectName);
        dir.mkdir("Models");
        dir.mkdir("Textures");
        dir.mkdir("Scripts");

        QFile file(dir.absolutePath() + "/" + m_projectInfo.m_projectName + ".uupj");

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

    QString savedObjects = "#" + sceneName + '\n';
    try {
        savedObjects += saveSkybox(scene->skybox());
        savedObjects += saveCameras(scene->camerasHash());
        savedObjects += saveLightins(scene->lighingsHash());
        savedObjects += saveGameObjects(scene->gameObjectsHash());


    } catch (...) {
        throw std::runtime_error(("Save scene " + sceneName + " error").toStdString());
    }

    return savedObjects;
}

QString ProjectProcessor::saveSkybox(SkyBox *skybox)
{
    QString savedObject = "+SKYBOX\n";
    savedObject += QString::number(skybox->model()->vertexesData().constFirst().position.x()) + skybox->model()->material()->diffuseMapPath() + '\n';
    return savedObject;
}
/// КОГДА ПОМЕНЯЮ КАМЕРУ НАДО БУДЕТ И СОХРАНЕНИЕ ПОМЕНЯТЬ
QString ProjectProcessor::saveCameras(QHash<QString, Camera *> cameras)
{

    QString savedObjects = "+CAMERAS\n";

    foreach (auto cameraName, cameras.keys()) {
        savedObjects += cameraName + '$';
        savedObjects += saveBaseParams(cameras[cameraName]);
        savedObjects += saveScripts(cameras[cameraName]->scripts());
    }
    return savedObjects;
}

/// КОГДА ПОМЕНЯЮ СВЕТ НАДО БУДЕТ И СОХРАНЕНИЕ ПОМЕНЯТЬ
QString ProjectProcessor::saveLightins(QHash<QString, Lighting *> lightings)
{
    QString savedObjects = "+LIGHTINGS\n";

    foreach (auto lightingName, lightings.keys()) {
        savedObjects += lightingName + '$';
        savedObjects += saveBaseParams(lightings[lightingName]);
        savedObjects += saveScripts(lightings[lightingName]->scripts());
    }
    return savedObjects;
}

QString ProjectProcessor::saveGameObjects(QHash<QString, Base3DGameObject *> gameObjects)
{
    QString savedObjects =  "+BASE3DGAMEOBJECT\n";

    foreach (auto gameObjectName, gameObjects.keys()) {
        auto gameObject = gameObjects[gameObjectName];

        savedObjects += gameObjectName + '$';
        savedObjects += saveBaseParams(gameObject);
        savedObjects += saveModel(gameObject);
        savedObjects += saveScripts(gameObject->scripts());

    }

    return savedObjects;
}


QString ProjectProcessor::saveBaseParams(BaseEngineObject *object)
{
    return QString("%1 %2 %3 %4 ").arg(object->modelMatrix().row(0)[0]).arg(object->modelMatrix().row(0)[1]).arg(object->modelMatrix().row(0)[2]).arg(object->modelMatrix().row(0)[3]) +
           QString("%1 %2 %3 %4 ").arg(object->modelMatrix().row(1)[0]).arg(object->modelMatrix().row(1)[1]).arg(object->modelMatrix().row(1)[2]).arg(object->modelMatrix().row(1)[3]) +
        QString("%1 %2 %3 %4 ").arg(object->modelMatrix().row(2)[0]).arg(object->modelMatrix().row(2)[1]).arg(object->modelMatrix().row(2)[2]).arg(object->modelMatrix().row(2)[3]) +
        QString("%1 %2 %3 %4$").arg(object->modelMatrix().row(3)[0]).arg(object->modelMatrix().row(3)[1]).arg(object->modelMatrix().row(3)[2]).arg(object->modelMatrix().row(3)[3]);
    //я не знаю как это сделать красиво и эффективно:(
    //(просто выгрузка модельной матрицы)
}

QString ProjectProcessor::saveModel(Base3DGameObject *gameObject)
{
    QString savedObject;

    if(gameObject->modelType() == ModelType::CustomeModel){
        return "CUSTOM_MODEL " + gameObject->modelPath() + '$';
    }
    else{
        if(gameObject->modelType() == ModelType::Cube){
            savedObject += "CUBE " + QString::number(gameObject->model().constLast()->vertexesData().constFirst().position.x())+
                           QString::number(gameObject->model().constLast()->vertexesData().constFirst().position.y())+
                           QString::number(gameObject->model().constLast()->vertexesData().constFirst().position.z());
        }
        else if(gameObject->modelType() == ModelType::Pyramide){
            savedObject += "PYRAMID " + QString::number(gameObject->model().constLast()->vertexesData().constFirst().position.x())+
                           QString::number(gameObject->model().constLast()->vertexesData().constFirst().position.y());
        }

        savedObject += saveMaterial(gameObject->model().constLast()->material());

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
        material->diffuseMapPath()+ ' ' + material->normalMapPath() + ' ' + QString::number(material->shinnes()) + '$';

}

QString ProjectProcessor::saveScripts(QVector<QString> scripts)
{
    return scripts.join(' ') + '\n';
}

/////////////////////////////////LOAD FILE


QHash<QString, Scene *>  ProjectProcessor::loadProject(const QString & path)
{
    QHash<QString, Scene *> scenes;

    try {
        QFile file(path);

        if(file.open(QIODevice::ReadOnly)){
            QTextStream stream(&file);
            try {
                QString str = stream.readLine();
                QString sceneName = str.split('#')[1];

                scenes.insert(sceneName, new Scene());


            } catch (...) {
                throw std::runtime_error("Open project file error");
            }

            file.close();
        }
        else{
            throw std::runtime_error("Open project file error");
        }
    } catch (...) {
        throw std::runtime_error("Project file error");
    }

    return scenes;
}



QHash<QString, Base3DGameObject *> ProjectProcessor::loadGameObjects(const QVector<QString> &gameObjectParams)
{
    QHash<QString, Base3DGameObject *> gameObjects;

    foreach (auto objectParams, gameObjectParams) {
        auto params = objectParams.split('$');

        ModelType modelType;
        QVector<Model *> models;
        auto modelParams = params[2].split(' ');

        if(modelParams[0] == "CUSTOM_MODEL"){
            modelType = ModelType::CustomeModel;

            m_modelLoader.setStrategy(new OBJModelLoadStraregy());
            models.append(m_modelLoader.createModel(modelParams[1]));
        }
        else{

            if(modelParams[0] == "CUBE"){
                modelType = ModelType::Cube;
                m_modelBuilder.createCube(modelParams[1].toFloat(), modelParams[2].toFloat(), modelParams[3].toFloat());
            }
            else if(modelParams[0] == "PYRAMID"){
                modelType = ModelType::Pyramide;
                m_modelBuilder.createPyramide(modelParams[1].toFloat(), modelParams[2].toFloat());
            }

            //object->setModel();
        }

        auto object = new Base3DGameObject(modelType, modelParam, );
        object->setModelMatrix(loadBaseParams(params[1]));


        gameObjects.insert(objectParams[0], object);

    }
}

QHash<QString, Camera *> ProjectProcessor::loadCameras(const QVector<QString> &cameras)
{

}

QHash<QString, Lighting *> ProjectProcessor::loadLightins(const QVector<QString> &lights)
{

}


QMatrix4x4 ProjectProcessor::loadBaseParams(const QString &matrixParams)
{
    auto params = matrixParams.split(' ');

    QMatrix4x4 mat;
    mat.setRow(0, QVector4D(params[0].toFloat(),params[1].toFloat(),params[2].toFloat(),params[3].toFloat()));
    mat.setRow(1, QVector4D(params[4].toFloat(),params[5].toFloat(),params[6].toFloat(),params[7].toFloat()));
    mat.setRow(2, QVector4D(params[8].toFloat(),params[9].toFloat(),params[10].toFloat(),params[11].toFloat()));
    mat.setRow(3, QVector4D(params[12].toFloat(),params[13].toFloat(),params[14].toFloat(),params[15].toFloat()));
}

QVector<QString> ProjectProcessor::loadScripts(const QString &scripts)
{
    return scripts.split(' ');
}

ProjectProcessor *ProjectProcessor::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new ProjectProcessor();
    }
    return m_instance;
}
