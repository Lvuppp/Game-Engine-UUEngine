#ifndef TEXTUREFOLDER_H
#define TEXTUREFOLDER_H

#include <string>
#include <unordered_map>
#include <vector>

class cTextureFolder
{
public:
    cTextureFolder();
    ~cTextureFolder() = default;

    cTextureFolder(const cTextureFolder&) = delete;
    cTextureFolder& operator=(const cTextureFolder&) = delete;

    void append(const std::string &objectName, const std::string &textureName);
    void remove(const std::string &objectName);
    void replace(const std::string &objectName, const std::string &modelName);

    const std::vector<std::string> allModels();
    std::vector<std::string> texture(const std::string &objectName);
    void clearFolder();

private:
    std::unordered_map<std::string,std::string> m_textures;
};

#endif // TEXTUREFOLDER_H
