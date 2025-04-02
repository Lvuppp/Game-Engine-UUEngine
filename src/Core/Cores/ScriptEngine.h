#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include "Scene.h"
#include "Folders/ScriptFolder.h"
#include "SceneFolder.h"
#include "Script.h"

#include <QDir>
//#include <dlfcn.h>

// В данный момент он довольно таки примитивный, но он старается :)

class cScriptEngine : public QThread
{
    Q_OBJECT
public:
    ~cScriptEngine();
    void startScene(cScene *scene);
    void stopScene();

public:
    void loadScripts(cScene *scene);
    void unloadScripts();

    void loadObjectScripts(const QString &objectName, cBaseEngineObject *object);

public:
    static cScriptEngine *getInstance();

public slots:
    void updateScene();

signals:
    void updateGraphics();
    void stopScripts();

private:
    cScriptFolder *m_scriptsFolder;
    cSceneFolder *m_sceneFolder;

    QVector<QLibrary *> m_scripts;
    QVector<QThread *> m_threadPool;

    cScene *m_currentSceneCopy;
    QHash<QString, cScene *> m_scenesCopy;

    bool m_gameStatus;
private:

    cScriptEngine();

    cScriptEngine(const cScriptEngine&) = delete;
    cScriptEngine& operator=(const cScriptEngine&) = delete;

    static cScriptEngine *m_instance;
};


#endif // SCRIPTENGINE_H
