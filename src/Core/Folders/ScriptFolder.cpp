#include "ScriptFolder.h"

cScriptFolder* cScriptFolder::m_instance = nullptr;

cScriptFolder::cScriptFolder() : m_scriptsFolder(QHash<QString,QString>())
{

}

void cScriptFolder::addScript( const QString & objectName, const QString &scriptName)
{
    m_scriptsFolder.insert(objectName, scriptName);
}

QVector<QString> cScriptFolder::scripts(const QString &name) const
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

void cScriptFolder::clearFolder()
{
    m_scriptsFolder.clear();
}

cScriptFolder *cScriptFolder::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new cScriptFolder();
    }
    return m_instance;
}
