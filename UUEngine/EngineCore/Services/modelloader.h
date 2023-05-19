#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "base3dgameobject.h"
#include "Folders/materiallib.h"
#include "projectinfo.h"

class ModelLoadStraregy
{
public:
    ModelLoadStraregy();
    virtual ~ModelLoadStraregy();

    virtual QVector<Model *> createModel(const QString& filePath) = 0;

};

class OBJModelLoadStraregy : public ModelLoadStraregy
{
public:
    OBJModelLoadStraregy();
    ~OBJModelLoadStraregy();
    QVector<Model *> createModel(const QString& filePath) override;

private:
    MaterialLibrary library;
};

class FBXModelLoadStraregy : public ModelLoadStraregy
{
public:
    FBXModelLoadStraregy();
    ~FBXModelLoadStraregy();
    QVector<Model *> createModel(const QString& filePath) override;

private:
    MaterialLibrary library;
};

class ModelLoader{
public:
    explicit ModelLoader(ModelLoadStraregy* strategy = nullptr);

    void setStrategy(ModelLoadStraregy *strategy);
    QVector<Model *> createModel(const QString& filePath);

private:
    ModelLoadStraregy *m_strategy;
};

#endif // OBJECTABSTRACTFACTORY_H
