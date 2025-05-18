#include "FileUtils.h"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace file_utils
{
    bool createFile(const std::string& filePath)
    {
        std::ofstream file(filePath);
        if (file.is_open() == false)
        {
            std::cerr << "Error creating file: " << filePath << std::endl;
            return false;
        }
        file.close();
        return true;
    }

    bool copyFile(const std::string& sourcePath, const std::string& destinationPath)
    {
        if (!std::filesystem::is_regular_file(sourcePath)) {
            std::cerr << "Source path is not a file: " << sourcePath << std::endl;
            return false;
        }

        try {
            std::filesystem::copy_file(sourcePath, destinationPath,
                                     std::filesystem::copy_options::overwrite_existing);
            return true;
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error copying file from " << sourcePath
                     << " to " << destinationPath << ": " << e.what() << std::endl;
            return false;
        }
    }

    bool copyDirectory(const std::string& sourcePath, const std::string& destinationPath)
    {
        if (!std::filesystem::is_directory(sourcePath)) {
            std::cerr << "Source path is not a directory: " << sourcePath << std::endl;
            return false;
        }

        try {
            std::filesystem::copy(sourcePath, destinationPath,
                                std::filesystem::copy_options::recursive | 
                                std::filesystem::copy_options::overwrite_existing);
            return true;
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error copying directory from " << sourcePath
                     << " to " << destinationPath << ": " << e.what() << std::endl;
            return false;
        }
    }

    bool deleteFile(const std::string& filePath)
    {
        try {
            return std::filesystem::remove(filePath);
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error deleting file " << filePath
                     << ": " << e.what() << std::endl;
            return false;
        }
    }

    bool writeToFile(const std::string& filePath, const std::string& content)
    {
        std::ofstream file(filePath, std::ios::out | std::ios::trunc);
        if (file.is_open() == false)
        {
            std::cerr << "Error opening file for writing: " << filePath << std::endl;
            return false;
        }

        file << content;
        if (file.fail())
        {
            std::cerr << "Error writing to file: " << filePath << std::endl;
            file.close();
            return false;
        }

        file.close();
        return true;
    }

    bool readFromFile(const std::string& filePath, std::string& content)
    {
        std::ifstream file(filePath, std::ios::in);
        if (file.is_open() == false)
        {
            std::cerr << "Error opening file for reading: " << filePath << std::endl;
            return false;
        }

        content = std::string((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());

        if (file.fail() && file.eof() == false)
        {
            std::cerr << "Error reading file: " << filePath << std::endl;
            file.close();
            return false;
        }

        file.close();
        return true;
    }

    bool fileExists(const std::string& filePath)
    {
        return std::filesystem::exists(filePath);
    }

    size_t getFileSize(const std::string& filePath)
    {
        try {
            return std::filesystem::file_size(filePath);
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error getting file size for " << filePath
                     << ": " << e.what() << std::endl;
            return 0;
        }
    }
}
