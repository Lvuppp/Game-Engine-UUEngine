#ifndef SCRIPTFOLDER_H
#define SCRIPTFOLDER_H

#include <QPair>
#include <QHash>
#include <string>

class cScriptFolder
{
public:
    cScriptFolder() = default;
    ~cScriptFolder() = default;

    cScriptFolder(const cScriptFolder&) = delete;
    cScriptFolder& operator=(const cScriptFolder&) = delete;

    void addScript(uint32_t hash, const std::string& scriptName);
    std::vector<std::string> scripts(uint32_t hash) const;
    void clearFolder();

private:
    std::unordered_map<uint32_t, std::string> m_scriptsFolder;
};
#endif // SCRIPTFOLDER_H
