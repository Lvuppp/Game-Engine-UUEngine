#ifndef PROJECTPROCESSOR_H
#define PROJECTPROCESSOR_H

#include "scene.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QHash>

class ProjectProcessor
{
public:
    ProjectProcessor();

    static void saveProject(QString path, QHash<QString, Scene *> scenes, QString projectName="");
    static void loadProject(QString path);

private:
    static void saveScene(QString sceneName, Scene *scene, QTextStream *stream);
    static void saveCameras(QHash<QString, Camera *> cameras, QTextStream *stream);
    static void saveLightins(QHash<QString, Lighting *> lightings, QTextStream *stream);
    static void saveGameObjects(QHash<QString, Base3DGameObject *> gameObjects, QTextStream *stream);

    static void loadScene(QString sceneName, Scene *scene, QTextStream *stream);

    static void saveBaseParams(BaseEngineObject *object, QTextStream *stream);
    static void saveScripts(QVector<QString> scripts, QTextStream *stream);

private:

    static QString m_currentProjectName;
    static QString m_currentProjectPath;

};


#endif // PROJECTPROCESSOR_H
