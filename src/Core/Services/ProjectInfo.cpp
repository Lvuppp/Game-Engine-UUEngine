#include "ProjectInfo.h"
#include "Utils/FileUtils.h"

#include <iostream>
#include <filesystem>

cProjectInfo::cProjectInfo()
{
    if (createSavesDirectory() == false)
    {
        std::cerr << "Failed to create saves directory at: " << m_projectPath << std::endl;
        return;
    }

    m_projectName = findNextAvailableSaveName();
    if (m_projectName.empty())
    {
        std::cerr << "Failed to find available save name" << std::endl;
        return;
    }

    if (createNewSaveDirectory(m_projectName) == false)
    {
        std::cerr << "Failed to create new save directory: " << m_projectName << std::endl;
        return;
    }

    m_scriptsDirectory = (std::filesystem::path(m_projectPath) / m_projectName / "scripts").string();
    m_texturesDirectory = (std::filesystem::path(m_projectPath) / m_projectName / "textures").string();
    m_modelsDirectory = (std::filesystem::path(m_projectPath)/ m_projectName / "models").string();
    m_soundsDirectory = (std::filesystem::path(m_projectPath) / m_projectName / "sounds").string();

    if (createProjectDirectories() == false)
    {
        std::cerr << "Failed to create project directories" << std::endl;
        return;
    }
}

void cProjectInfo::createNewProject(std::string_view path, std::string_view name)
{
    auto oldProjectPath = std::filesystem::path(m_projectPath) / m_projectName;
    m_projectName = name.data();
    m_projectPath = path.data();
    
    createNewSaveDirectory(m_projectName);
    copyProjectDirectories();

    if (m_isDefaultProject)
    {
        std::filesystem::remove_all(oldProjectPath);
        m_isDefaultProject = false;
    }
}

void cProjectInfo::openProject(std::string_view path)
{
    m_projectPath = std::filesystem::path(path).parent_path().string();
    m_projectName = std::filesystem::path(path).filename().string();

    m_scriptsDirectory = (std::filesystem::path(m_projectPath) / m_projectName / "scripts").string();
    m_texturesDirectory = (std::filesystem::path(m_projectPath) / m_projectName / "textures").string();
    m_modelsDirectory = (std::filesystem::path(m_projectPath)/ m_projectName / "models").string();
    m_soundsDirectory = (std::filesystem::path(m_projectPath) / m_projectName / "sounds").string();

    m_isDefaultProject = false;
}

void cProjectInfo::changeProjectName(std::string_view name)
{
    m_projectName = name.data();
    
    m_scriptsDirectory = (std::filesystem::path(m_projectPath) / m_projectName / "scripts").string();
    m_texturesDirectory = (std::filesystem::path(m_projectPath) / m_projectName / "textures").string();
    m_modelsDirectory = (std::filesystem::path(m_projectPath)/ m_projectName / "models").string();
    m_soundsDirectory = (std::filesystem::path(m_projectPath) / m_projectName / "sounds").string();
}

bool cProjectInfo::createSavesDirectory()
{
    m_projectPath = (std::filesystem::current_path() / "saves").string();
    if (std::filesystem::exists(m_projectPath))
    {
        return true;
    }

    std::error_code ec;
    std::filesystem::create_directory(m_projectPath, ec);

    if (ec)
    {
        std::cerr << "Error creating saves directory: " << ec.message() << std::endl;
        return false;
    }

    return true;
}

std::string cProjectInfo::findNextAvailableSaveName()
{
    int counter = 1;
    std::string baseName = "untitled";
    std::string saveName;

    while (true)
    {
        saveName = baseName + std::to_string(counter);
        std::filesystem::path savePath = std::filesystem::path(m_projectPath) / saveName;

        if (std::filesystem::exists(savePath) == false)
        {
            return saveName;
        }

        counter++;

        if (counter > 1000)
        {
            std::cerr << "Too many save directories, cannot create new one" << std::endl;
            return "";
        }
    }
}

bool cProjectInfo::createNewSaveDirectory(const std::string& saveName)
{
    std::filesystem::path savePath = std::filesystem::path(m_projectPath) / saveName;

    std::error_code ec;
    std::filesystem::create_directory(savePath, ec);

    if (ec)
    {
        std::cerr << "Error creating save directory " << saveName
                 << ": " << ec.message() << std::endl;
        return false;
    }

    return true;
}

bool cProjectInfo::createProjectDirectories()
{
    std::error_code ec;

    std::filesystem::create_directory(m_scriptsDirectory, ec);
    if (ec)
    {
        std::cerr << "Error creating scripts directory: " << ec.message() << std::endl;
        return false;
    }

    std::filesystem::create_directory(m_texturesDirectory, ec);
    if (ec)
    {
        std::cerr << "Error creating textures directory: " << ec.message() << std::endl;
        return false;
    }

    std::filesystem::create_directory(m_modelsDirectory, ec);
    if (ec)
    {
        std::cerr << "Error creating models directory: " << ec.message() << std::endl;
        return false;
    }

    std::filesystem::create_directory(m_soundsDirectory, ec);
    if (ec)
    {
        std::cerr << "Error creating sounds directory: " << ec.message() << std::endl;
        return false;
    }

    return true;
}

bool cProjectInfo::copyProjectDirectories()
{
    std::error_code ec;
    const auto newProjectPath = std::filesystem::path(m_projectPath) / m_projectName;

    const auto newScriptsPath = (newProjectPath / "scripts").string();
    std::filesystem::create_directory(newScriptsPath, ec);
    if (file_utils::copyDirectory(m_scriptsDirectory, newScriptsPath) == false)
    {
        std::cerr << "Error copying scripts directory" << std::endl;
        return false;
    }
    m_scriptsDirectory = newScriptsPath;

    const auto newTexturesPath = (newProjectPath / "textures").string();
    std::filesystem::create_directory(newTexturesPath, ec);
    if (file_utils::copyDirectory(m_texturesDirectory, newTexturesPath) == false)
    {
        std::cerr << "Error copying textures directory" << std::endl;
        return false;
    }
    m_texturesDirectory = newTexturesPath;

    const auto newModelsPath = (newProjectPath / "models").string();
    std::filesystem::create_directory(newModelsPath, ec);
    if (file_utils::copyDirectory(m_modelsDirectory, newModelsPath) == false)
    {
        std::cerr << "Error copying models directory" << std::endl;
        return false;
    }
    m_modelsDirectory = newModelsPath;

    const auto newSoundsPath = (newProjectPath / "sounds").string();
    if (file_utils::copyDirectory(m_soundsDirectory, newSoundsPath) == false)
    {
        std::cerr << "Error copying sounds directory" << std::endl;
        return false;
    }
    m_soundsDirectory = newSoundsPath;

    return true;
}
