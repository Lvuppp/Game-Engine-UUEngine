#include "ModelFolder.h"

cModelFolder *cModelFolder::m_instance = nullptr;

cModelFolder::cModelFolder()
{

}

void cModelFolder::append(const QString &objectName, const QString &modelName)
{
    m_modelsFolder.insert(objectName, modelName);
}

void cModelFolder::remove(const QString &objectName)
{
    m_modelsFolder.remove(objectName);
}

void cModelFolder::replace(const QString &objectName, const QString &modelName)
{
    m_modelsFolder[objectName] = modelName;
}

QString cModelFolder::model(const QString &name) const
{
    return m_modelsFolder[name];
}

void cModelFolder::clearFolder()
{
    m_modelsFolder.clear();
}

cModelFolder *cModelFolder::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new cModelFolder();
    }

    return m_instance;
}
