#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "Folders/materiallib.h"
#include "Folders/modelfolder.h"
#include "Services/projectinfo.h"

class CustomModel;

class ModelAbstractFactory
{
public:
    ModelAbstractFactory();
    virtual ~ModelAbstractFactory();

    virtual CustomModel* createModel(const QString& filePath) = 0;

};

class OBJModelFactory : public ModelAbstractFactory
{
public:
    OBJModelFactory();
    ~OBJModelFactory();
    CustomModel*  createModel(const QString& filePath) override;

private:
    MaterialLibrary library;
};

class FBXModelFactory : public ModelAbstractFactory
{
public:
    FBXModelFactory();
    ~FBXModelFactory();
    CustomModel*  createModel(const QString& filePath) override;

private:
    MaterialLibrary library;
};

class ModelLoader{
public:
    explicit ModelLoader(ModelAbstractFactory* strategy = nullptr);

    void setFactory(ModelAbstractFactory *strategy);
    CustomModel* createModel(const QString& filePath);

private:
    ModelAbstractFactory *m_factory;
    ModelFolder *m_modelFolder;
};

#endif // OBJECTABSTRACTFACTORY_H
