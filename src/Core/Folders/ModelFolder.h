#ifndef MODELFOLDER_H
#define MODELFOLDER_H

#include "Models/Model.h"

#include <QString>
#include <QHash>
#include <QPair>


// Хранит в себе либо параметры модели, либо название самой модели в папке проекта Models
// по факту этот класс используется только для работы конекретно с проектом и его структурой
class cModelFolder
{
public:
    void append(const QString &objectName, const QString &modelName);
    void remove(const QString &objectName);
    void replace(const QString &objectName, const QString &modelName);

    QString model(const QString &name) const;
    void clearFolder();

public:
    static cModelFolder *getInstance();

private:
    QHash<QString, QString>  m_modelsFolder;

private:
    cModelFolder();
    ~cModelFolder();

    cModelFolder(const cModelFolder&) = delete;
    cModelFolder& operator=(const cModelFolder&) = delete;

    static cModelFolder *m_instance;

};

#endif // MODELFOLDER_H

