#include "ProjectInfo.h"

#include "Utils/TextUtils.h"

#include "qdebug.h"

std::string cProjectInfo::m_projectPath ="";
std::string cProjectInfo::m_projectName ="";
std::string cProjectInfo::m_projectFolder ="";

std::string cProjectInfo::projectName()
{
    return m_projectName;
}


std::string cProjectInfo::projectPath()
{
    return m_projectPath;
}

std::string cProjectInfo::projectFolder()
{
    return m_projectFolder;
}

void cProjectInfo::copyToModels(const std::string &sourceFilePath)
{
    const auto path = text_utils::split(sourceFilePath, '/');
    copyFile(sourceFilePath, m_projectFolder + "/Models/" + path.back());
}

void cProjectInfo::copyToTextures(const std::string &sourceFilePath)
{
    const auto path = text_utils::split(sourceFilePath, '/');
    copyFile(sourceFilePath, m_projectFolder + "/Textures/" + path.back());

}

void cProjectInfo::copyToScripts(const std::string &sourceFilePath)
{
    const auto path = text_utils::split(sourceFilePath, '/');
    copyFile(sourceFilePath, m_projectFolder + "/Scripts/" + path.back());
}

void cProjectInfo::copyFile(const std::string& sourceFilePath, const std::string &targetFilePath)
{
    QFile sourceFile(sourceFilePath.c_str());
    if (sourceFile.open(QIODevice::ReadOnly) == false)
    {
        qDebug() << "Can`t open file";
        return;
    }

    QSaveFile targetFile(targetFilePath.c_str());
    if (targetFile.open(QIODevice::WriteOnly) == false)
    {
        qDebug() << "Can`t open copy file";
        return;
    }

    targetFile.write(sourceFile.readAll());

    if (targetFile.error() != QSaveFile::NoError)
    {
        qDebug() << "Error writing in copy file";
        return ;
    }

    if (targetFile.commit() == false)
    {
        qDebug() << "Error save in copy file";
        return ;
    }

}
