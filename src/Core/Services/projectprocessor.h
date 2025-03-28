#ifndef PROJECTPROCESSOR_H
#define PROJECTPROCESSOR_H

#include "scene.h"
#include "modelloader.h"
#include "modelbuilder.h"
#include "projectinfo.h"
#include "Folders/scriptfolder.h"
#include "Folders/modelfolder.h"
#include "Folders/texturefolder.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QHash>
#include <QVBoxLayout>

class ProjectProcessor
{
public:
    ~ProjectProcessor();

    void saveProject(QHash<QString, Scene *> scenes, const QString &path = "");
    QHash<QString, Scene*> loadProject(const QString & path);
    void createProject(const QString &path, const QString &name);
    void closeProject(QHash<QString, Scene *> scenes);

    void setLayout(QBoxLayout &layout);
    static ProjectProcessor *getInstance();
private:
    QString saveScene(const QString &sceneName, Scene *scene);
    QString saveCameras(QHash<QString, Camera *> cameras);
    QString saveLightins(QHash<QString, Lighting *> lightings);
    QString saveGameObjects(QHash<QString, Base3DGameObject *> gameObjects);
    QString saveSkybox(SkyBox *skybox);

    QString saveBaseParams(BaseEngineObject *object);
    QString saveModel(const QString &objectName, Base3DGameObject *gameObject);
    QString saveMaterial(Material *material);
    QString saveScripts(QVector<QString> scripts);

    QHash<QString, Scene *> loadScene(const QString sceneName, Scene *scene);
    QHash<QString, Camera *> loadCameras(const QVector<QString> &cameras);
    QHash<QString, Lighting *> loadLightins(const QVector<QString> &lights);
    QHash<QString, Base3DGameObject *> loadGameObjects(const QVector<QString> &gameObjects);
    SkyBox *loadSkybox(const QString &skybox);

    void loadBaseParams(const QString &objectMatrix, BaseEngineObject *object);
    Model *loadModel(const QString &objectName, const QString &objectType, const QString &gameObject);
    Material* loadMaterial(const QString &objectName,const QString &material);
    void loadScripts(const QString &objectName,const QString &scripts);

private:
    TextureFolder *m_textureFolder;
    ModelFolder *m_modelFolder;
    ScriptFolder *m_scriptFolder;
    ProjectInfo m_projectInfo;

    ModelBuilder m_modelBuilder;
    ModelLoader m_modelLoader;

    QBoxLayout *m_projectLayout;

private:

    ProjectProcessor();
    ProjectProcessor(const ProjectProcessor&) = delete;
    ProjectProcessor& operator=(const ProjectProcessor&) = delete;


    static ProjectProcessor *m_instance;

};


#endif // PROJECTPROCESSOR_H
