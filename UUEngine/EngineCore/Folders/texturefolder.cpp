#include "texturefolder.h"

TextureFolder *TextureFolder::m_instance = nullptr;

TextureFolder::~TextureFolder()
{

}

void TextureFolder::append(const QString &objectName, const QString &textureName)
{
    m_textures.insert(objectName, textureName);
}

void TextureFolder::remove(const QString &objectName)
{
    m_textures.remove(objectName);
}

void TextureFolder::replace(const QString &objectName, const QString &modelName)
{
    m_textures[objectName] = modelName;
}

QVector<QString> TextureFolder::texture(const QString &objectName)
{
    QVector<QString> tmp;
    auto texturesIters =  m_textures.equal_range(objectName);

    for (auto it = texturesIters.first; it != texturesIters.second; ++it) {
        tmp.append(*it);
    }

    return tmp;
}

void TextureFolder::clearFolder()
{
    m_textures.clear();
}

TextureFolder *TextureFolder::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new TextureFolder();
    }

    return m_instance;
}

TextureFolder::TextureFolder() : m_textures(QHash<QString,QString>())
{

}
