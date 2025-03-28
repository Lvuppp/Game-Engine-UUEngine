#include "modelfolder.h"

ModelFolder *ModelFolder::m_instance = nullptr;

ModelFolder::ModelFolder()
{

}

void ModelFolder::append(const QString &objectName, const QString &modelName)
{
    m_modelsFolder.insert(objectName, modelName);
}

void ModelFolder::remove(const QString &objectName)
{
    m_modelsFolder.remove(objectName);
}

void ModelFolder::replace(const QString &objectName, const QString &modelName)
{
    m_modelsFolder[objectName] = modelName;
}

QString ModelFolder::model(const QString &name)
{
    return m_modelsFolder[name];
}

void ModelFolder::clearFolder()
{
    m_modelsFolder.clear();
}

ModelFolder *ModelFolder::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new ModelFolder();
    }

    return m_instance;
}
