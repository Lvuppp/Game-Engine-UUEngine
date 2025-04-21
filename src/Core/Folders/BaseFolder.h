#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>


class cBaseFolder
{
public:
    void append(uint32_t hash, const std::string &fileName);
    void remove(uint32_t hash);
    void replace(uint32_t hash, const std::string &fileName);

protected:
    std::unordered_map<uint32_t, std::string>  m_fileFolder;
};
