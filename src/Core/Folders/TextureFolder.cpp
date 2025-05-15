#include "TextureFolder.h"

#include "Utils/Hash.h"
#include "Utils/TextUtils.h"

#include <QImage>
#include <QOpenGLTexture>

constexpr const char* cBaseFolder::FolderPath = "Texture";

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
    copyFileToProject();
    const QImage image(objectPath.data());
    const auto texture = new QOpenGLTexture(image.mirrored());

    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMinificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);

    m_textures.insert(std::make_pair<>(cHash::hash(fileName), texture));

    return texture;
}
