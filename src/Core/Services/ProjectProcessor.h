#ifndef PROJECTPROCESSOR_H
#define PROJECTPROCESSOR_H

#include "Scene.h"
#include "ModelLoader.h"
#include "ModelBuilder.h"
#include "Projectinfo.h"
#include "Folders/ScriptFolder.h"
#include "Folders/ModelFolder.h"
#include "Folders/TextureFolder.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QHash>
#include <QVBoxLayout>

class cProjectProcessor
{
public:
    ~cProjectProcessor();

    void saveProject(QHash<QString, cScene *> scenes, const QString &path = "");
    QHash<QString, cScene*> loadProject(const QString & path);
    void createProject(const QString &path, const QString &name);
    void closeProject(QHash<QString, cScene *> scenes);

    void setLayout(QBoxLayout &layout);
    static cProjectProcessor *getInstance();
private:
    QString saveScene(const QString &sceneName, cScene *scene);
    QString saveCameras(QHash<QString, cCamera *> cameras);
    QString saveLightins(QHash<QString, cLighting *> lightings);
    QString saveGameObjects(QHash<QString, cBase3DGameObject *> gameObjects);
    QString saveSkybox(cSkyBox *skybox);

    QString saveBaseParams(cBaseEngineObject *object);
    QString saveModel(const QString &objectName, cBase3DGameObject *gameObject);
    QString saveMaterial(cMaterial *material);
    QString saveScripts(QVector<QString> scripts);

    QHash<QString, cScene *> loadScene(const QString sceneName, cScene *scene);
    QHash<QString, cCamera *> loadCameras(const QVector<QString> &cameras);
    QHash<QString, cLighting *> loadLightins(const QVector<QString> &lights);
    QHash<QString, cBase3DGameObject *> loadGameObjects(const QVector<QString> &gameObjects);
    cSkyBox *loadSkybox(const QString &skybox);

    void loadBaseParams(const QString &objectMatrix, cBaseEngineObject *object);
    cModel *loadModel(const QString &objectName, const QString &objectType, const QString &gameObject);
    cMaterial* loadMaterial(const QString &objectName,const QString &material);
    void loadScripts(const QString &objectName,const QString &scripts);

private:
    cTextureFolder *m_textureFolder;
    cModelFolder *m_modelFolder;
    cScriptFolder *m_scriptFolder;
    cProjectInfo m_projectInfo;

    cModelBuilder m_modelBuilder;
    cModelLoader m_modelLoader;

    QBoxLayout *m_projectLayout;

private:

    cProjectProcessor();
    cProjectProcessor(const cProjectProcessor&) = delete;
    cProjectProcessor& operator=(const cProjectProcessor&) = delete;


    static cProjectProcessor *m_instance;

};


#endif // PROJECTPROCESSOR_H
