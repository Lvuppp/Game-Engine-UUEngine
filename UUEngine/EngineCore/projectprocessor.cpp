#include "projectprocessor.h"

QString ProjectProcessor::m_currentProjectName = "";
QString ProjectProcessor::m_currentProjectPath = "";


ProjectProcessor::ProjectProcessor()
{

}


//
// FILE FORMAT
// #SCENE_NAME
// -CAMERA
// OBJECT_NAME$COORDS$ROTATATION$SCALE$SCRIPT_PATH ...
// -CAMERA
// LIGHTING$COORDS$ROTATATION$SCALE$SCRIPT_PATH ...
// -BASE3DGAMEOBJECT
// OBJECT_NAME$COORDS$ROTATATION$SCALE$(CUSTOM_MODEL$MODEL_PATH)|(CUBE|PYRAMID$DIFFUSE_MAP$NORMAL_MAP$)$SCRIPT_PATH ...
// #SCENE_NAME ...


void ProjectProcessor::saveProject(QString path, QHash<QString, Scene *> scenes, QString projectName)
{
    if(projectName != ""){
        m_currentProjectName = projectName;
    }

    QFile file(path + m_currentProjectName + ".uupj");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream *stream = new QTextStream(&file);
        QTextStream s(&file);
        foreach (auto key, scenes.keys()) {
            *stream << "#" << key;
            saveScene(key, scenes[key], stream);
        }

        delete stream;
        file.close();

    }
    else{
        throw std::runtime_error("Project file error");
    }

}

void ProjectProcessor::loadProject(QString path)
{

}

void ProjectProcessor::saveScene(QString sceneName, Scene *scene, QTextStream *stream)
{
    try {
        saveCameras(scene->camerasHash(), stream);
        saveLightins(scene->lighingsHash(), stream);
        saveGameObjects(scene->gameObjectsHash(), stream);

    } catch (...) {
        throw std::runtime_error(("Save scene " + sceneName + " error").toStdString());
    }

}

/// КОГДА ПОМЕНЯЮ КАМЕРУ НАДО БУДЕТ И СОХРАНЕНИЕ ПОМЕНЯТЬ
void ProjectProcessor::saveCameras(QHash<QString, Camera *> cameras, QTextStream *stream)
{

    *stream << "-CAMERAS";

    foreach (auto cameraName, cameras.keys()) {
        saveBaseParams(cameras[cameraName], stream);
        saveScripts(cameras[cameraName]->scripts(), stream);
    }
}

/// КОГДА ПОМЕНЯЮ СВЕТ НАДО БУДЕТ И СОХРАНЕНИЕ ПОМЕНЯТЬ
void ProjectProcessor::saveLightins(QHash<QString, Lighting *> lightings, QTextStream *stream)
{
    *stream << "-LIGHTINGS";

    foreach (auto lightingName, lightings.keys()) {

        saveBaseParams(lightings[lightingName], stream);
        saveScripts(lightings[lightingName]->scripts(), stream);
    }
}

void ProjectProcessor::saveGameObjects(QHash<QString, Base3DGameObject *> gameObjects, QTextStream *stream)
{
    *stream << "-BASE3DGAMEOBJECT";

    foreach (auto gameObjectName, gameObjects.keys()) {
        auto gameObject = gameObjects[gameObjectName];
        saveBaseParams(gameObject, stream);

        if(gameObject->modelType() == ModelType::CustomeModel){
            *stream << "-CUSTOM_MODEL";
            *stream << gameObject->modelPath();
        }
        else{

            if(gameObject->modelType() == ModelType::Cube){
                *stream << "-CUBE";
            }
            else if(gameObject->modelType() == ModelType::Pyramide){
                *stream << "-PYRAMID";
            }

            Material *material = gameObject->model().constLast()->material();

            if(material->mtlName() != ""){
                *stream << material->mtlName();
            }
            else{
                auto vectorConverter = [](QVector3D vec) -> QString{
                    return QString("%1 %2 %3").arg(vec.x()).arg(vec.y()).arg(vec.z());
                };

                *stream << "-NOMTL";
                *stream << vectorConverter(material->ambienceColor());
                *stream << vectorConverter(material->diffuseColor());
                *stream << vectorConverter(material->specularColor());
                *stream << material->diffuseMapPath();
                *stream << material->normalMapPath();
                *stream << material->shinnes();
            }

            saveScripts(gameObject->scripts(), stream);
        }
    }
}

void ProjectProcessor::saveBaseParams(BaseEngineObject *object, QTextStream *stream)
{
    *stream << QString("%1 %2 %3 %4$").arg(object->modelMatrix().row(0)[0]).arg(object->modelMatrix().row(1)[0]).arg(object->modelMatrix().row(1)[0]).arg(object->modelMatrix().row(1)[0]) <<
        QString("%1 %2 %3 %4").arg(object->modelMatrix().row(1)[0]).arg(object->modelMatrix().row(1)[0]).arg(object->modelMatrix().row(1)[0]).arg(object->modelMatrix().row(1)[0])<<
        QString("%1 %2 %3 %4").arg(object->modelMatrix().row(2)[0]).arg(object->modelMatrix().row(1)[0]).arg(object->modelMatrix().row(1)[0]).arg(object->modelMatrix().row(1)[0]) <<
        QString("%1 %2 %3 %4").arg(object->modelMatrix().row(3)[0]).arg(object->modelMatrix().row(1)[0]).arg(object->modelMatrix().row(1)[0]).arg(object->modelMatrix().row(1)[0]);
    //я не знаю как это сделать красиво и эффективно:(
}

void ProjectProcessor::saveScripts(QVector<QString> scripts, QTextStream *stream)
{
    for(auto it = scripts.begin(); it < scripts.end() - 1; it++){
        *stream << *it << " ";
    }

    *stream << *scripts.end() << '\n';

}
