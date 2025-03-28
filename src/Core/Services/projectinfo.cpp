#include "projectinfo.h"
#include "qdebug.h"

QString ProjectInfo::m_projectPath ="";
QString ProjectInfo::m_projectName ="";
QString ProjectInfo::m_projectFolder ="";


ProjectInfo::ProjectInfo()
{

}

QString ProjectInfo::projectName()
{
    return m_projectName;
}


QString ProjectInfo::projectPath()
{
    return m_projectPath;
}

QString ProjectInfo::projectFolder()
{
    return m_projectFolder;
}

void ProjectInfo::copyToModels(const QString &sourceFilePath)
{
    copyFile(sourceFilePath, m_projectFolder + "/Models/" + sourceFilePath.split('/').constLast());
}

void ProjectInfo::copyToTextures(const QString &sourceFilePath)
{
    copyFile(sourceFilePath, m_projectFolder + "/Textures/" +sourceFilePath.split('/').constLast());

}

void ProjectInfo::copyToScripts(const QString &sourceFilePath)
{
    copyFile(sourceFilePath, m_projectFolder + "/Scripts/" + sourceFilePath.split('/').constLast());
}

void ProjectInfo::copyFile(const QString& sourceFilePath, const QString &targetFilePath)
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
