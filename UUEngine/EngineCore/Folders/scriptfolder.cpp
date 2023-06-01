#include "scriptfolder.h"

ScriptFolder* ScriptFolder::m_instance = nullptr;

ScriptFolder::ScriptFolder() : m_scriptsFolder(QHash<QString,QString>())
{

}

void ScriptFolder::addScript( const QString & objectName, const QString &scriptName)
{
    m_scriptsFolder.insert(objectName, scriptName);
}

QVector<QString> ScriptFolder::scripts(const QString &name)
{
    QVector<QString> tmp(0);

    if(!m_scriptsFolder.contains(name)){
        return tmp;
    }

    auto scriptsIters =  m_scriptsFolder.equal_range(name);


    for (auto it = scriptsIters.first; it != scriptsIters.second; ++it) {
        tmp.append(*it);
    }

    return tmp;
}

void ScriptFolder::clearFolder()
{
    m_scriptsFolder.clear();
}

ScriptFolder *ScriptFolder::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new ScriptFolder();
    }
    return m_instance;
}
