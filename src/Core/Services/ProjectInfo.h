#ifndef PROJECTINFO_H
#define PROJECTINFO_H

#include <string>
#include <QFile>
#include <QSaveFile>

class cProjectProcessor;

class cProjectInfo
{
public:
    cProjectInfo() = default;

    static std::string projectName();
    static std::string projectPath();
    static std::string projectFolder();

    static void copyToModels(const std::string& sourceFilePath);
    static void copyToTextures(const std::string& sourceFilePath);
    static void copyToScripts(const std::string& sourceFilePath);

    friend class cProjectProcessor;
private:

    static void copyFile(const std::string& sourceFilePath, const std::string &targetFilePath);

    static std::string m_projectName;
    static std::string m_projectPath;
    static std::string m_projectFolder;

private:
};

#endif // PROJECTINFO_H
