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
    void append(const QString &objectName, const QString &modelName);
    void remove(const QString &objectName);
    void replace(const QString &objectName, const QString &modelName);

    const QVector<QString> allModels();
    QVector<QString> models(const QString &name);
    void clearFolder();

public:
    static ModelFolder *getInstance();

private:
    QHash<QString, QString>  m_modelsFolder;

private:
    ModelFolder();
    ~ModelFolder();

    ModelFolder(const ModelFolder&) = delete;
    ModelFolder& operator=(const ModelFolder&) = delete;

    static ModelFolder *m_instance;

};

#endif // MODELFOLDER_H

