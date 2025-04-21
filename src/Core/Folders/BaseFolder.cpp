#include "BaseFolder.h"

void cBaseFolder::append(uint32_t hash, const std::string &fileName)
{
    m_fileFolder.insert(std::make_pair<>(hash, fileName));
}

void cBaseFolder::remove(uint32_t hash)
{
    m_fileFolder.erase(hash);
}

void cBaseFolder::replace(uint32_t hash, const std::string &fileName)
{
    m_fileFolder[hash] = fileName;
}
