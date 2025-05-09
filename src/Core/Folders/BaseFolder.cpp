#include "BaseFolder.h"
#include <algorithm>

void cBaseFolder::append(uint32_t hash, const std::string &fileName)
{
    m_files.insert(std::make_pair<>(hash, fileName));
}

void cBaseFolder::remove(uint32_t hash)
{
    m_files.erase(hash);
}

void cBaseFolder::replace(uint32_t hash, const std::string &fileName)
{
    m_files[hash] = fileName;
}

std::string_view cBaseFolder::getFile(uint32_t hash)
{
    return m_files[hash].data();
}

std::vector<std::string_view> cBaseFolder::getFiles() const
{
    std::vector<std::string_view> files;
    for (const auto file : m_files)
    {
        files.push_back(file.second.data());
    }
    return files;
}
