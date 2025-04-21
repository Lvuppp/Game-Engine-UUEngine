#include "ModelFolder.h"

void cModelFolder::append(uint32_t hash, const std::string &modelName)
{
    m_modelsFolder.insert(std::make_pair<>(hash, modelName));
}

void cModelFolder::remove(uint32_t hash)
{
    m_modelsFolder.erase(hash);
}

void cModelFolder::replace(uint32_t hash, const std::string &modelName)
{
    m_modelsFolder[hash] = modelName;
}

const std::string& cModelFolder::getModel(uint32_t hash)
{
    return m_modelsFolder[hash];
}

void cModelFolder::clearFolder()
{
    m_modelsFolder.clear();
}
