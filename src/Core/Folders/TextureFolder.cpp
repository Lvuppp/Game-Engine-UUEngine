#include "TextureFolder.h"

#include "Utils/Hash.h"
#include "Utils/TextUtils.h"

#include <QImage>
#include <QOpenGLTexture>

#include <filesystem>

void cTextureManager::clean()
{
    for (auto [_, texture] : m_textures)
    {
        delete texture;
    }

    m_textures.clear();
}

QOpenGLTexture* cTextureManager::loadTexture(std::string_view objectPath)
{
    auto [fileName, _, file] = text_utils::getFullFileName(objectPath);
    const QImage image(objectPath.data());
    const auto texture = new QOpenGLTexture(image.mirrored());
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Nearest);
    texture->setWrapMode(QOpenGLTexture::Repeat);

    m_textures.insert(std::make_pair<>(cHash::hash(fileName), texture));

    return texture;
}

void cTextureManager::loadTextures(std::string_view objectPath)
{
    for (const auto& file : std::filesystem::directory_iterator(objectPath.data()))
    {
        loadTexture(file.path().string());
    }
}