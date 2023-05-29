#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "Folders/materiallib.h"
#include "Folders/modelfolder.h"
#include "Services/projectinfo.h"

class CustomModel;

class ModelLoadStrategy
{
public:
    ModelLoadStrategy();
    virtual ~ModelLoadStrategy();

    virtual CustomModel* createModel(const QString& filePath) = 0;

};

class OBJModelLoadStrategy : public ModelLoadStrategy
{
public:
    OBJModelLoadStrategy();
    ~OBJModelLoadStrategy();
    CustomModel*  createModel(const QString& filePath) override;

private:
    MaterialLibrary library;
};

class FBXModelLoadStrategy : public ModelLoadStrategy
{
public:
    FBXModelLoadStrategy();
    ~FBXModelLoadStrategy();
    CustomModel*  createModel(const QString& filePath) override;

private:
    MaterialLibrary library;
};

class ModelLoader{
public:
    explicit ModelLoader(ModelLoadStrategy* strategy = nullptr);

    void setStrategy(ModelLoadStrategy *strategy);
    CustomModel* createModel(const QString& filePath);

private:
    ModelLoadStrategy *m_strategy;
    ModelFolder *m_modelFolder;
};

#endif // OBJECTABSTRACTFACTORY_H
