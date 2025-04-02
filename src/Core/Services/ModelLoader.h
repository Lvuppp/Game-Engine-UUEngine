#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "Folders/MaterialLib.h"
#include "Folders/ModelFolder.h"
#include "Services/Projectinfo.h"

class cCustomModel;

class ModelAbstractFactory
{
public:
    ModelAbstractFactory();
    virtual ~ModelAbstractFactory();

    virtual cCustomModel* createModel(const QString& filePath) = 0;

};

class OBJModelFactory : public ModelAbstractFactory
{
public:
    OBJModelFactory();
    ~OBJModelFactory();
    cCustomModel*  createModel(const QString& filePath) override;

private:
    cMaterialLibrary library;
};

class FBXModelFactory : public ModelAbstractFactory
{
public:
    FBXModelFactory();
    ~FBXModelFactory();
    cCustomModel*  createModel(const QString& filePath) override;

private:
    cMaterialLibrary library;
};

class cModelLoader{
public:
    explicit cModelLoader(ModelAbstractFactory* strategy = nullptr);

    void setFactory(ModelAbstractFactory *strategy);
    cCustomModel* createModel(const QString& filePath);

private:
    ModelAbstractFactory *m_factory;
    cModelFolder *m_modelFolder;
};

#endif // OBJECTABSTRACTFACTORY_H
