#ifndef TEXTUREFOLDER_H
#define TEXTUREFOLDER_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

class cTextureFolder
{
public:
    cTextureFolder() = default;
    ~cTextureFolder() = default;

    cTextureFolder(const cTextureFolder&) = delete;
    cTextureFolder& operator=(const cTextureFolder&) = delete;

    void append(uint32_t hash, const std::string &textureName);
    void remove(uint32_t hash);
    void replace(uint32_t hash, const std::string &modelName);

    const std::vector<std::string> allModels();
    std::vector<std::string> texture(uint32_t hash);
    void clearFolder();

private:
    std::unordered_map<uint32_t,std::string> m_textures;
};

#endif // TEXTUREFOLDER_H
