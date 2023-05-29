#include "scriptengine.h"
#include "EngineEntities/base3dgameobject.h"

ScriptEngine *ScriptEngine::m_instance = nullptr;

ScriptEngine::~ScriptEngine()
{

}

void ScriptEngine::startCameraScript(QHash<QString, Camera *> camera)
{

}

void ScriptEngine::startLightingScript(QHash<QString, Lighting *> camera)
{

}

void ScriptEngine::startGameObjectScript(QHash<QString, Base3DGameObject *> object)
{
//    typedef void (*my_function_t)(Base3DGameObject *);

//    void* my_library = dlopen("./" + , RTLD_NOW | RTLD_GLOBAL);

//    if (my_library == NULL)
//    {
//        qCritical() << "Error loading library: " << dlerror() ;
//        return;
//    }

//    my_function_t my_function = (my_function_t) dlsym(my_library, "update");

//    // Проверяем, успешно ли получили указатель на функцию
//    if (my_function == NULL)
//    {
//        qCritical() << "Error getting symbol: " << dlerror() ;
//        dlclose(my_library);
//        return;
//    }


//    // Вызываем экспортированную функцию
//    my_function(object);

//    qDebug() << "Coordinates changes: " << object->coordinates();

//    // Выгружаем библиотеку
//    dlclose(my_library);
}

void ScriptEngine::startSkyBox(SkyBox *skybox)
{

}



ScriptEngine *ScriptEngine::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new ScriptEngine();
    }

    return m_instance;
}

ScriptEngine::ScriptEngine()
{
    m_scriptsFolder = ScriptFolder::getInstance();
}

