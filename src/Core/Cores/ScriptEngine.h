#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include "Entities/Scene.h"
#include "Core/Folders/ScriptFolder.h"
#include "Entities/SceneFolder.h"
#include "Entities/Script.h"
#include <QLibrary>

#include <QDir>
#include <QThread>

// В данный момент он довольно таки примитивный, но он старается :)

class cScriptEngine : public QThread
{
    Q_OBJECT
public:
    cScriptEngine();
    ~cScriptEngine() = default;

    cScriptEngine(const cScriptEngine&) = delete;
    cScriptEngine& operator=(const cScriptEngine&) = delete;

    void startScene(cScene *scene);
    void stopScene();

public:
    void loadScripts(cScene *scene);
    void unloadScripts();

    void loadObjectScripts(const std::string &objectName, cBaseEngineObject *object);

signals:
    void stopScripts();

private:
    cScriptFolder *m_scriptsFolder;
    cSceneFolder *m_sceneFolder;

    std::vector<QLibrary *> m_scripts;
    std::vector<QThread *> m_threadPool;

    cScene *m_currentSceneCopy;
    std::unordered_map<std::string, cScene *> m_scenesCopy;

    bool m_gameStatus;
};


#endif // SCRIPTENGINE_H
