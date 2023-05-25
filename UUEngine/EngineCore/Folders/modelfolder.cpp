#include "modelfolder.h"

ModelFolder *ModelFolder::m_instance = nullptr;

ModelFolder::ModelFolder() : m_models(QHash<QString,QString>())
{

}

QVector<QString> ModelFolder::models(const QString &name)
{
    QVector<QString> tmp;
    auto modelsIters =  m_models.equal_range(name);

    for (auto it = modelsIters.first; it != modelsIters.second; ++it) {
        tmp.append(*it);
    }

    return tmp;
}

void ModelFolder::clearFolder()
{
    m_models.clear();
}

ModelFolder *ModelFolder::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new ModelFolder();
    }

    return m_instance;
}
