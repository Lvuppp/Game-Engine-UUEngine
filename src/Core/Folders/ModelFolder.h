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

    void append(uint32_t hash, const std::string &modelName);
    void remove(uint32_t hash);
    void replace(uint32_t hash, const std::string &modelName);

    const std::string& getModel(uint32_t hash);

    void clearFolder();

private:
    std::unordered_map<uint32_t, std::string>  m_modelsFolder;
};

#endif // MODELFOLDER_H
