#include "scriptfolder.h"

ScriptFolder* ScriptFolder::m_instance = nullptr;

ScriptFolder::ScriptFolder()
{

}

void ScriptFolder::addScript( const QString & objectName, const QString &scriptName, const QString & objectType)
{
    m_scripts.insert(objectName, QPair<QString,QString>(scriptName,objectType));
}

QHash<QString, QPair<QString, QString> > ScriptFolder::scripts()
{
    return m_scripts;
}

ScriptFolder *ScriptFolder::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new ScriptFolder();
    }
    return m_instance;
}
