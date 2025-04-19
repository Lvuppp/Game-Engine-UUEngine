#ifndef MODELFOLDER_H
#define MODELFOLDER_H

#include "Entities/Models/Model.h"

#include <string>
#include <QHash>
#include <QPair>

class cModelFolder
{
public:
    cModelFolder() = default;
    ~cModelFolder() = default;

    cModelFolder(const cModelFolder&) = delete;
    cModelFolder& operator=(const cModelFolder&) = delete;

    void append(const std::string &objectName, const std::string &modelName);
    void remove(const std::string &objectName);
    void replace(const std::string &objectName, const std::string &modelName);

    std::string model(const std::string &name) const;

    void clearFolder();

private:
    std::unordered_map<std::string, std::string>  m_modelsFolder;
};

#endif // MODELFOLDER_H
