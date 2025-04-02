#ifndef PROJECTINFO_H
#define PROJECTINFO_H

#include <QString>
#include <QFile>
#include <QSaveFile>

class cProjectProcessor;

class cProjectInfo
{
public:
    cProjectInfo();

    static QString projectName();
    static QString projectPath();
    static QString projectFolder();

    static void copyToModels(const QString& sourceFilePath);
    static void copyToTextures(const QString& sourceFilePath);
    static void copyToScripts(const QString& sourceFilePath);

    friend class cProjectProcessor;
private:

    static void copyFile(const QString& sourceFilePath, const QString &targetFilePath);

    static QString m_projectName;
    static QString m_projectPath;
    static QString m_projectFolder;

private:
};

#endif // PROJECTINFO_H
