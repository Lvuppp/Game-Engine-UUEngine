#include "scriptengine.h"
#include "EngineEntities/base3dgameobject.h"

ScriptEngine *ScriptEngine::m_instance = nullptr;

ScriptEngine::~ScriptEngine()
{

}

void ScriptEngine::loadScript(Base3DGameObject *object)
{
    QStringList filters;
    filters << "*.so"; // добавить фильтр для поиска только файлов с расширением .cpp
    currentDirectory.setNameFilters(filters);

    auto scriptsFiles = currentDirectory.entryInfoList(QDir::Files);
    if(scriptsFiles.empty()) return;

    QString dllCreatorCommand = "g++ ";
    QString dllParams = "-shared -fPIC -o scripts_library.so"; // параметры должны быть через пробел

    foreach (QFileInfo file, scriptsFiles) {
        dllCreatorCommand += "Scripts/" + file.fileName() + " ";
    }

    dllCreatorCommand += dllParams;

    int isDLLCreated = system(dllCreatorCommand.toStdString().c_str());
    if (isDLLCreated != 0)
    {
        qCritical() << "Error compiling library";
        return;
    }
    typedef void (*my_function_t)(Base3DGameObject *);

    void* my_library = dlopen("./libcube.so", RTLD_NOW | RTLD_GLOBAL);

    // Проверяем, успешно ли загрузилась библиотека
    if (my_library == NULL)
    {
        qCritical() << "Error loading library: " << dlerror() ;
        return;
    }

    // Получаем указатель на экспортируемую функцию
    my_function_t my_function = (my_function_t) dlsym(my_library, "update");

    // Проверяем, успешно ли получили указатель на функцию
    if (my_function == NULL)
    {
        qCritical() << "Error getting symbol: " << dlerror() ;
        dlclose(my_library);
        return;
    }

    // Вызываем экспортированную функцию
    my_function(object);

    qDebug() << "Coordinates changes: " << object->coordinates();

    // Выгружаем библиотеку
    dlclose(my_library);

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
    if(!currentDirectory.exists("Scripts"))
        currentDirectory.mkdir("Scripts");
    currentDirectory = currentDirectory.absolutePath() + "/Scripts";

}

