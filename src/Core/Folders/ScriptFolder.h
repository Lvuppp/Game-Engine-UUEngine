#ifndef SCRIPTFOLDER_H
#define SCRIPTFOLDER_H

#include "EngineEntities/BaseEngineObject.h"

#include <QPair>
#include <QHash>
#include <QString>

class cScriptFolder
{
public:
    void addScript(const QString &objectName, const QString &scriptName);
    QVector<QString> scripts(const QString &name) const;
    void clearFolder();

    static cScriptFolder *getInstance();

private:
    QHash<QString, QString> m_scriptsFolder;

    cScriptFolder();
    ~cScriptFolder();

    cScriptFolder(const cScriptFolder&) = delete;
    cScriptFolder& operator=(const cScriptFolder&) = delete;

    static cScriptFolder *m_instance;
};

#endif // SCRIPTFOLDER_H
