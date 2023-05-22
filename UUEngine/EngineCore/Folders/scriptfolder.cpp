#include "scriptfolder.h"

ScriptFolder* ScriptFolder::m_instance = nullptr;

ScriptFolder::ScriptFolder() : m_scripts(QHash<QString,QString>())
{

}

void ScriptFolder::addScript( const QString & objectName, const QString &scriptName)
{
    m_scripts.insert(objectName, scriptName);
}

QVector<QString> ScriptFolder::scripts(const QString &name)
{
    QVector<QString> tmp;
    auto scriptsIters =  m_scripts.equal_range(name);

    for (auto it = scriptsIters.first; it != scriptsIters.second; ++it) {
        tmp.append(*it);
    }

    return tmp;
}

ScriptFolder *ScriptFolder::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new ScriptFolder();
    }
    return m_instance;
}
