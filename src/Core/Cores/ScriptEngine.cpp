#include "ScriptEngine.h"

#include "Core/Services/ProjectInfo.h"

#include <QLibrary>

void cScriptEngine::startScene(cScene *scene)
{
    loadScripts(scene);
}

void cScriptEngine::stopScene()
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

void cScriptEngine::loadScripts(cScene *scene)
{
    // for(auto [objectName, scene] :  scene->gameObjectsHash()){
    //     loadObjectScripts(objectName, scene->gameObjectsHash().value(objectName));
    // }

    // foreach (auto cameraName, scene->camerasHash().keys()) {
    //     loadObjectScripts(cameraName, scene->camerasHash().value(cameraName));
    // }
}


void cScriptEngine::loadObjectScripts(const std::string &objectName, cBaseEngineObject *object)
{
    // auto scripts = m_scriptsFolder->scripts(objectName);

    // if(scripts.size() != 0 && scripts[0] != ""){
    //     for (int i = 0; i < scripts.size(); ++i) {
    //         QLibrary *lib = new QLibrary(cProjectInfo::projectFolder() + "/Scripts/" + std::string::fromStdString(scripts[i]));

    //         if(!lib->load()){
    //             throw std::runtime_error("BROKEN SCRIPT!");
    //         }

    //         cScript *script = new cScript(object, lib->resolve("update"));
    //         m_threadPool.append(script);
    //         connect(this, &cScriptEngine::stopScripts, script, &cScript::requestInterruption);
    //         //connect(script, &cScript::updateScene, this, &cScriptEngine::updateScene);
    //         script->start();
    //         m_scripts.append(lib);
    //     }
    // }
}

cScriptEngine::cScriptEngine()
    : m_gameStatus(false)
{
}
