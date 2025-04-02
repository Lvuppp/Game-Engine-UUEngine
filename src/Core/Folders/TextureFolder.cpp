#include "TextureFolder.h"

cTextureFolder *cTextureFolder::m_instance = nullptr;

cTextureFolder::~cTextureFolder()
{

}

void cTextureFolder::append(const QString &objectName, const QString &textureName)
{
    m_textures.insert(objectName, textureName);
}

void cTextureFolder::remove(const QString &objectName)
{
    m_textures.remove(objectName);
}

void cTextureFolder::replace(const QString &objectName, const QString &modelName)
{
    m_textures[objectName] = modelName;
}

QVector<QString> cTextureFolder::texture(const QString &objectName)
{
    QVector<QString> tmp;
    auto texturesIters =  m_textures.equal_range(objectName);

    for (auto it = texturesIters.first; it != texturesIters.second; ++it) {
        tmp.append(*it);
    }

    return tmp;
}

void cTextureFolder::clearFolder()
{
    m_textures.clear();
}

cTextureFolder *cTextureFolder::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new cTextureFolder();
    }

    return m_instance;
}

cTextureFolder::cTextureFolder() : m_textures(QHash<QString,QString>())
{

}
