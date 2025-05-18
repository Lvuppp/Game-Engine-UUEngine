#ifndef PROJECTINFO_H
#define PROJECTINFO_H

#include <string>

class cProjectInfo
{
public:
    cProjectInfo();
    ~cProjectInfo() = default;

    void createNewProject(std::string_view path, std::string_view name);
    void openProject(std::string_view path);
    void changeProjectName(std::string_view name);
    
    std::string_view getProjectName() const
    {
        return m_projectName;
    }

    std::string_view getProjectPath() const
    {
        return m_projectPath;
    }

    std::string_view getScriptsDirectory() const
    {
        return m_scriptsDirectory;
    }

    std::string_view getTexturesDirectory() const
    {
        return m_texturesDirectory;
    }

    std::string_view getModelsDirectory() const
    {
        return m_modelsDirectory;
    }

    std::string_view getSoundsDirectory() const
    {
        return m_soundsDirectory;
    }

private:
    std::string m_projectName = "";
    std::string m_projectPath = "";
    std::string m_scriptsDirectory = "";
    std::string m_texturesDirectory = "";
    std::string m_modelsDirectory = "";
    std::string m_soundsDirectory = "";

    bool m_isDefaultProject = true;

    bool createSavesDirectory();
    std::string findNextAvailableSaveName();
    bool createNewSaveDirectory(const std::string& saveName);
    bool createProjectDirectories();
    bool copyProjectDirectories();
};

#endif // PROJECTINFO_H
