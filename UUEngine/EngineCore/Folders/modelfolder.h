#ifndef MODELFOLDER_H
#define MODELFOLDER_H

#include <QString>
#include <QHash>

class ModelFolder
{
public:
    QHash<QString, QString> models() const;

private:
    QHash<QString, QString> m_models;

public:
    static ModelFolder *getInstance();
protected:
    friend class ModelLoader;

    void addModel(QPair<QString,QString>);
private:

    ModelFolder();

    ModelFolder(const ModelFolder&) = delete;
    ModelFolder& operator=(const ModelFolder&) = delete;

    static ModelFolder *m_instance;

};

#endif // MODELFOLDER_H
