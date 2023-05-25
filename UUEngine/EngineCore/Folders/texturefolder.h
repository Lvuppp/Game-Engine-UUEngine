#ifndef TEXTUREFOLDER_H
#define TEXTUREFOLDER_H

#include <QString>
#include <QHash>
#include <QPair>

class TextureFolder
{
public:
    ~TextureFolder();

    void addTexture( const QString & objectName, const QString &textureName);
    QVector<QString> texture(const QString &objectName);
    void clearFolder();

    static TextureFolder *getInstance();

private:
    TextureFolder();

    TextureFolder(const TextureFolder&) = delete;
    TextureFolder& operator=(const TextureFolder&) = delete;

    QHash<QString,QString> m_textures;
    static TextureFolder* m_instance;
};

#endif // TEXTUREFOLDER_H
