#include "ModelFolder.h"

void cModelFolder::append(const std::string &objectName, const std::string &modelName)
{
    m_modelsFolder.insert(std::make_pair<>(objectName, modelName));
}

void cModelFolder::remove(const std::string &objectName)
{
    m_modelsFolder.erase(objectName);
}

void cModelFolder::replace(const std::string &objectName, const std::string &modelName)
{
    m_modelsFolder[objectName] = modelName;
}

std::string cModelFolder::model(const std::string &name) const
{
    return m_modelsFolder.at(name);
}

void cModelFolder::clearFolder()
{
    m_modelsFolder.clear();
}
