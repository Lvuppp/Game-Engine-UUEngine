#include "ScriptFolder.h"

void cScriptFolder::addScript(uint32_t hash, const std::string &scriptName)
{
    m_scriptsFolder.insert(std::make_pair<>(hash, scriptName));
}

std::vector<std::string> cScriptFolder::scripts(uint32_t hash) const
{
    std::vector<std::string> tmp;

    if(m_scriptsFolder.find(hash) != m_scriptsFolder.cend())
    {
        return tmp;
    }

    auto scriptsIters =  m_scriptsFolder.equal_range(hash);

    for (auto it = scriptsIters.first; it != scriptsIters.second; it++)
    {
        tmp.push_back(it->second);
    }

    return tmp;
}

void cScriptFolder::clearFolder()
{
    m_scriptsFolder.clear();
}
