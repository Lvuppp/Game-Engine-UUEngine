#ifndef SCRIPTFOLDER_H
#define SCRIPTFOLDER_H

#include "EngineEntities/baseengineobject.h"

#include <QPair>
#include <QHash>
#include <QString>

class ScriptFolder
{
public:
    void addScript( const QString & objectName, const QString &scriptName);
    QVector<QString> scripts(const QString &name);
    void clearFolder();

    static ScriptFolder *getInstance();

private:
    QHash<QString,QString> m_scripts;

private:
    ScriptFolder();

    ScriptFolder(const ScriptFolder&) = delete;
    ScriptFolder& operator=(const ScriptFolder&) = delete;

    static ScriptFolder* m_instance;
};

#endif // SCRIPTFOLDER_H
