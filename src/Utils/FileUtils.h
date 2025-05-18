#pragma once

#include <string>
#include <filesystem>
#include <fstream>

namespace file_utils
{
    bool createFile(const std::string& filePath);
    
    bool copyFile(const std::string& sourcePath, const std::string& destinationPath);
    
    bool copyDirectory(const std::string& sourcePath, const std::string& destinationPath);
    
    bool deleteFile(const std::string& filePath);
    
    bool writeToFile(const std::string& filePath, const std::string& content);

    bool readFromFile(const std::string& filePath, std::string& content);
    
    bool fileExists(const std::string& filePath);
    
    std::uintmax_t getFileSize(const std::string& filePath);
}
