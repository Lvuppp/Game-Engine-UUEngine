#include "ScriptFolder.h"

cScriptFolder::cScriptFolder()
    : m_scriptsFolder(std::unordered_map<std::string,std::string>())
{

}

void cScriptFolder::addScript( const std::string & objectName, const std::string &scriptName)
{
    m_scriptsFolder.insert(std::make_pair<>(objectName, scriptName));
}

std::vector<std::string> cScriptFolder::scripts(const std::string &name) const
{
    std::vector<std::string> tmp;

    if(m_scriptsFolder.find(name) != m_scriptsFolder.cend())
    {
        return tmp;
    }

    auto scriptsIters =  m_scriptsFolder.equal_range(name);

    for (auto it = scriptsIters.first; it != scriptsIters.second; it++)
    {
        tmp.push_back(it->first);
    }

    return tmp;
}

void cScriptFolder::clearFolder()
{
    m_scriptsFolder.clear();
}
