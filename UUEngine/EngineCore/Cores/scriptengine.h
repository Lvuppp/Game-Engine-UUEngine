#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include "scene.h"
#include "Folders/scriptfolder.h"
#include "Folders/scenefolder.h"
#include "script.h"

#include <QDir>
#include <dlfcn.h>

// В данный момент он довольно таки примитивный, но он старается :)

class ScriptEngine : public QThread
{
    Q_OBJECT
public:
    ~ScriptEngine();
    void startScene(Scene *scene);
    void stopScene();

public:
    void loadScripts(Scene *scene);
    void unloadScripts();

    void loadObjectScripts(const QString &objectName, BaseEngineObject *object);
    void changeGameStatus();

public:
    static ScriptEngine *getInstance();

signals:
    void updateScene();
signals:
    void stopScripts();

private:
    ScriptFolder *m_scriptsFolder;
    SceneFolder *m_sceneFolder;

    QVector<QLibrary *> m_scripts;
    QVector<QThread *> m_threadPool;

    bool m_gameStatus;
private:

    ScriptEngine();

    ScriptEngine(const ScriptEngine&) = delete;
    ScriptEngine& operator=(const ScriptEngine&) = delete;

    static ScriptEngine *m_instance;
};


#endif // SCRIPTENGINE_H
