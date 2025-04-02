#include "Projectinfo.h"
#include "qdebug.h"

QString cProjectInfo::m_projectPath ="";
QString cProjectInfo::m_projectName ="";
QString cProjectInfo::m_projectFolder ="";


cProjectInfo::cProjectInfo()
{

}

QString cProjectInfo::projectName()
{
    return m_projectName;
}


QString cProjectInfo::projectPath()
{
    return m_projectPath;
}

QString cProjectInfo::projectFolder()
{
    return m_projectFolder;
}

void cProjectInfo::copyToModels(const QString &sourceFilePath)
{
    copyFile(sourceFilePath, m_projectFolder + "/Models/" + sourceFilePath.split('/').constLast());
}

void cProjectInfo::copyToTextures(const QString &sourceFilePath)
{
    copyFile(sourceFilePath, m_projectFolder + "/Textures/" +sourceFilePath.split('/').constLast());

}

void cProjectInfo::copyToScripts(const QString &sourceFilePath)
{
    copyFile(sourceFilePath, m_projectFolder + "/Scripts/" + sourceFilePath.split('/').constLast());
}

void cProjectInfo::copyFile(const QString& sourceFilePath, const QString &targetFilePath)
{
    QFile sourceFile(sourceFilePath);
    if (!sourceFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Can`t open file";
        return;
    }

    QSaveFile targetFile(targetFilePath);
    if (!targetFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Can`t open copy file";
        return;
    }

    targetFile.write(sourceFile.readAll());

    if (targetFile.error() != QSaveFile::NoError) {
        qDebug() << "Error writing in copy file";
        return ;
    }

    if (!targetFile.commit()) {
        qDebug() << "Error save in copy file";
        return ;
    }

}
