#include "scriptengine.h"

ScriptEngine *ScriptEngine::m_instance = nullptr;

ScriptEngine::~ScriptEngine()
{

}

void ScriptEngine::loadScript()
{
    QStringList filters;
    filters << "*.cpp"; // добавить фильтр для поиска только файлов с расширением .cpp
    currentDirectory.setNameFilters(filters);

    auto scriptsFiles = currentDirectory.entryInfoList(QDir::Files);
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
    typedef int (*my_function_t)(int, int);

    void* my_library = dlopen("./scripts_library.so", RTLD_LAZY);

    // Проверяем, успешно ли загрузилась библиотека
    if (my_library == NULL)
    {
        qCritical() << "Error loading library: " << dlerror() ;
        return;
    }

    // Получаем указатель на экспортируемую функцию
    my_function_t my_function = (my_function_t) dlsym(my_library, "my_function");

    // Проверяем, успешно ли получили указатель на функцию
    if (my_function == NULL)
    {
        qCritical() << "Error getting symbol: " << dlerror() ;
        dlclose(my_library);
        return;
    }

    // Вызываем экспортированную функцию
    int result = my_function(1, 2);

    // Выводим результат
    qDebug() << "Result: " << result ;

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

   loadScript();
}

