//#ifndef PROJECTPROCESSOR_H
//#define PROJECTPROCESSOR_H

//#include "scene.h"
//#include "modelloader.h"
//#include "modelbuilder.h"
//#include "projectinfo.h"

//#include <QString>
//#include <QFile>
//#include <QTextStream>
//#include <QHash>
//#include <QVBoxLayout>

//class ProjectProcessor
//{
//public:
//    ~ProjectProcessor();

//    void saveProject(const QString &path, QHash<QString, Scene *> scenes, const QString &projectName="");
//    QHash<QString, Scene *> loadProject(const QString & path);

//    static ProjectProcessor *getInstance();
//private:
//    QString saveScene(const QString &sceneName, Scene *scene);
//    QString saveCameras(QHash<QString, Camera *> cameras);
//    QString saveLightins(QHash<QString, Lighting *> lightings);
//    QString saveGameObjects(QHash<QString, Base3DGameObject *> gameObjects);
//    QString saveSkybox(SkyBox *skybox);

//    QString saveBaseParams(BaseEngineObject *object);
//    QString saveModel(Base3DGameObject *gameObject);
//    QString saveMaterial(Material *material);
//    QString saveScripts(QVector<QString> scripts);


//    QHash<QString, Scene *> loadScene(const QString sceneName, Scene *scene);
//    QHash<QString, Camera *> loadCameras(const QVector<QString> &cameras);
//    QHash<QString, Lighting *> loadLightins(const QVector<QString> &lights);
//    QHash<QString, Base3DGameObject *> loadGameObjects(const QVector<QString> &gameObjects);
//    SkyBox *loadSkybox(const QString &skybox);

//    Base3DGameObject* saveModel(QVector<QString> gameObject);
//    Material* saveMaterial(QVector<QString> material);
//    QMatrix4x4 loadBaseParams(const QString &objectMatrix);
//    QVector<QString> loadScripts(const QString &scripts);

//private:

//    ProjectProcessor();
//    ProjectProcessor(const ProjectProcessor&) = delete;
//    ProjectProcessor& operator=(const ProjectProcessor&) = delete;


//    static ProjectProcessor *m_instance;

//    ProjectInfo m_projectInfo;
//    ModelBuilder m_modelBuilder;
//    ModelLoader m_modelLoader;
//    QBoxLayout *m_projectLayout;
//};


//#endif // PROJECTPROCESSOR_H
