#ifndef TEXTUREFOLDER_H
#define TEXTUREFOLDER_H

#include <QString>
#include <QHash>
#include <QPair>

class cTextureFolder
{
public:
    void append(const QString &objectName, const QString &textureName);
    void remove(const QString &objectName);
    void replace(const QString &objectName, const QString &modelName);

    const QVector<QString> allModels();
    QVector<QString> texture(const QString &objectName);
    void clearFolder();

public:
    static cTextureFolder *getInstance();

private:
    QHash<QString,QString> m_textures;

private:
    cTextureFolder();
    ~cTextureFolder();

    cTextureFolder(const cTextureFolder&) = delete;
    cTextureFolder& operator=(const cTextureFolder&) = delete;

    static cTextureFolder* m_instance;
};

#endif // TEXTUREFOLDER_H
