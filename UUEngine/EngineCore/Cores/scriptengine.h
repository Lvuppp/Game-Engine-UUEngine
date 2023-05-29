#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include "EngineEntities/base3dgameobject.h"
#include "EngineEntities/camera.h"
#include "EngineEntities/lighting.h"
#include "EngineEntities/skybox.h"
#include "Folders/scriptfolder.h"

#include <QDir>
#include <dlfcn.h>

// В данный момент он довольно таки примитивный, но он старается :)

class ScriptEngine : public QThread
{
public:
    ~ScriptEngine();

    void startCameraScript(QHash<QString, Camera*> camera);
    void startLightingScript(QHash<QString, Lighting*> lighting);
    void startGameObjectScript(QHash<QString, Base3DGameObject*> gameObject);
    void startSkyBox(SkyBox *skybox);

public:
    static ScriptEngine *getInstance();

signals:
    void updateScene();

private:
    QDir currentDirectory;
    ScriptFolder *m_scriptsFolder;

private:
    ScriptEngine();

    ScriptEngine(const ScriptEngine&) = delete;
    ScriptEngine& operator=(const ScriptEngine&) = delete;

    static ScriptEngine *m_instance;
};

#endif // SCRIPTENGINE_H
