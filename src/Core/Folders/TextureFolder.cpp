#include "TextureFolder.h"

void cTextureFolder::append(uint32_t hash, const std::string &textureName)
{
    m_textures.insert(std::make_pair<>(hash, textureName));
}

void cTextureFolder::remove(uint32_t hash)
{
    m_textures.erase(hash);
}

void cTextureFolder::replace(uint32_t hash, const std::string &modelName)
{
    m_textures[hash] = modelName;
}

std::vector<std::string> cTextureFolder::texture(uint32_t hash)
{
    std::vector<std::string> tmp;
    auto texturesIters =  m_textures.equal_range(hash);

    for (auto it = texturesIters.first; it != texturesIters.second; ++it)
    {
        tmp.push_back(it->second);
    }

    return tmp;
}

void cTextureFolder::clearFolder()
{
    m_textures.clear();
}
