#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

class cBaseFolder
{
public:
    cBaseFolder() = default;

    cBaseFolder(const cBaseFolder&) = delete;
    cBaseFolder& operator=(const cBaseFolder&) = delete;

    void append(uint32_t hash, const std::string &fileName);
    void remove(uint32_t hash);
    void replace(uint32_t hash, const std::string &fileName);
    std::string_view getFile(uint32_t hash);
    std::vector<std::string_view> getFiles() const;

protected:
    std::unordered_map<uint32_t, std::string>  m_files;
};
