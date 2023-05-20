#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "Models/modelparticle.h"
#include "Folders/materiallib.h"

#include "projectinfo.h"
class CustomModel;


class ModelLoadStraregy
{
public:
    ModelLoadStraregy();
    virtual ~ModelLoadStraregy();

    virtual QVector<ModelParticle *> createModel(const QString& filePath) = 0;

};

class OBJModelLoadStraregy : public ModelLoadStraregy
{
public:
    OBJModelLoadStraregy();
    ~OBJModelLoadStraregy();
    QVector<ModelParticle *> createModel(const QString& filePath) override;

private:
    MaterialLibrary library;
};

class FBXModelLoadStraregy : public ModelLoadStraregy
{
public:
    FBXModelLoadStraregy();
    ~FBXModelLoadStraregy();
    QVector<ModelParticle *> createModel(const QString& filePath) override;

private:
    MaterialLibrary library;
};

class ModelLoader{
public:
    explicit ModelLoader(ModelLoadStraregy* strategy = nullptr);

    void setStrategy(ModelLoadStraregy *strategy);
    QVector<ModelParticle *>createModel(const QString& filePath);

private:
    ModelLoadStraregy *m_strategy;
};

#endif // OBJECTABSTRACTFACTORY_H
