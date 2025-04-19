#ifndef SCRIPTFOLDER_H
#define SCRIPTFOLDER_H

#include "Entities/BaseEntities/BaseEngineObject.h"

#include <QPair>
#include <QHash>
#include <string>

class cScriptFolder
{
public:
    cScriptFolder();
    ~cScriptFolder() = default;

    cScriptFolder(const cScriptFolder&) = delete;
    cScriptFolder& operator=(const cScriptFolder&) = delete;

    void addScript(const std::string &objectName, const std::string &scriptName);
    std::vector<std::string> scripts(const std::string &name) const;
    void clearFolder();

private:
    std::unordered_map<std::string, std::string> m_scriptsFolder;
};
#endif // SCRIPTFOLDER_H
