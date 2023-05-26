#ifndef TEXTUREFOLDER_H
#define TEXTUREFOLDER_H

#include <QString>
#include <QHash>
#include <QPair>

class TextureFolder
{
public:
    void addTexture(const QString &objectName, const QString &textureName);
    QVector<QString> texture(const QString &objectName);
    void clearFolder();

public:
    static TextureFolder *getInstance();

private:
    QHash<QString,QString> m_textures;

private:
    TextureFolder();
    ~TextureFolder();


    TextureFolder(const TextureFolder&) = delete;
    TextureFolder& operator=(const TextureFolder&) = delete;

    static TextureFolder* m_instance;
};

#endif // TEXTUREFOLDER_H
