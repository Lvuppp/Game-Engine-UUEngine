#include "TextureFolder.h"

cTextureFolder::cTextureFolder()
    : m_textures(std::unordered_map<std::string,std::string>())
{

}

void cTextureFolder::append(const std::string &objectName, const std::string &textureName)
{
    m_textures.insert(std::make_pair<>(objectName, textureName));
}

void cTextureFolder::remove(const std::string &objectName)
{
    m_textures.erase(objectName);
}

void cTextureFolder::replace(const std::string &objectName, const std::string &modelName)
{
    m_textures[objectName] = modelName;
}

std::vector<std::string> cTextureFolder::texture(const std::string &objectName)
{
    std::vector<std::string> tmp;
    auto texturesIters =  m_textures.equal_range(objectName);

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
