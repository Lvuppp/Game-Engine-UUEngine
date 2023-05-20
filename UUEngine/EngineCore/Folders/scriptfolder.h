#ifndef SCRIPTFOLDER_H
#define SCRIPTFOLDER_H

#include "EngineEntities/baseengineobject.h"

#include <QString>

class ScriptFolder
{
public:
    void addScript( const QString & objectName, const QString &scriptName, const QString & objectType);
    QHash<QString,QPair<QString,QString>> scripts();
    static ScriptFolder *getInstance();

private:
    ScriptFolder();

    ScriptFolder(const ScriptFolder&) = delete;
    ScriptFolder& operator=(const ScriptFolder&) = delete;

    QHash<QString,QPair<QString,QString>> m_scripts;
    static ScriptFolder* m_instance;
};

#endif // SCRIPTFOLDER_H
