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

const QVector<QString> ModelFolder::allModels()
{
    return m_modelsFolder.values();
}

QVector<QString> ModelFolder::models(const QString &name)
{
    QVector<QString> tmp;
    auto modelsIters =  m_modelsFolder.equal_range(name);

    for (auto it = modelsIters.first; it != modelsIters.second; ++it) {
        tmp.append(*it);
    }

    return tmp;
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
