#include "scriptengine.h"
#include "EngineEntities/base3dgameobject.h"
#include "Services/projectinfo.h"


ScriptEngine *ScriptEngine::m_instance = nullptr;

ScriptEngine::~ScriptEngine()
{

}

void ScriptEngine::startScene(Scene *scene)
{
    loadScripts(scene);
}

void ScriptEngine::stopScene()
{
    emit stopScripts();

    for (auto thread : m_threadPool) {
        thread->wait();
    }

    for (auto it = m_scripts.begin(); it != m_scripts.end(); ++it) {
        (*it)->unload();
        delete *it;
    }

    m_scripts.clear();
}

void ScriptEngine::loadScripts(Scene *scene)
{
    foreach(auto objectName, scene->gameObjectsHash().keys()){
        loadObjectScripts(objectName, scene->gameObjectsHash().value(objectName));
    }

    foreach (auto cameraName, scene->camerasHash().keys()) {
        loadObjectScripts(cameraName, scene->camerasHash().value(cameraName));
    }
}


void ScriptEngine::loadObjectScripts(const QString &objectName, BaseEngineObject *object)
{
    auto scripts = m_scriptsFolder->scripts(objectName);

    if(scripts.size() != 0 && scripts[0] != ""){
        for (int i = 0; i < scripts.size(); ++i) {
            QLibrary *lib = new QLibrary(ProjectInfo::projectFolder() + "/Scripts/" + scripts[i]);

            if(!lib->load()){
                throw std::runtime_error("BROKEN SCRIPT!");
            }

            Script *script = new Script(object, lib->resolve("update"));
            m_threadPool.append(script);
            connect(this, &ScriptEngine::stopScripts, script, &Script::requestInterruption);
            connect(script, &Script::updateScene, this, &ScriptEngine::updateScene);
            script->start();
            m_scripts.append(lib);
        }
    }
}


ScriptEngine *ScriptEngine::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new ScriptEngine();
    }

    return m_instance;
}

void ScriptEngine::updateScene()
{
    emit updateGraphics();
}

ScriptEngine::ScriptEngine() : m_gameStatus(false)
{
    m_scriptsFolder = ScriptFolder::getInstance();
    m_sceneFolder = SceneFolder::getInstance();
}

