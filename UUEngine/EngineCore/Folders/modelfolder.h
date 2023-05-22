#ifndef MODELFOLDER_H
#define MODELFOLDER_H

#include "Models/model.h"

#include <QString>
#include <QHash>
#include <QPair>


// Хранит в себе либо параметры модели, либо название самой модели в папке проекта Models
// по факту этот класс используется только для работы конекретно с проектом и его структурой
class ModelFolder
{
public:

    void addModel( const QString & objectName, const QString &modelsName);
    QVector<QString> models(const QString &name);

    static ModelFolder *getInstance();

private:
    QHash<QString, QString>  m_models;

private:

    ModelFolder();

    ModelFolder(const ModelFolder&) = delete;
    ModelFolder& operator=(const ModelFolder&) = delete;

    static ModelFolder *m_instance;

};

#endif // MODELFOLDER_H

