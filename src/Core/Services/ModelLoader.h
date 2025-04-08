#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "Core/Folders/MaterialLib.h"

class cModel;
class cModelFolder;

class ModelAbstractFactory
{
public:
    virtual ~ModelAbstractFactory() = default;

    virtual cModel* createModel(const QString& filePath) = 0;

};

class OBJModelFactory : public ModelAbstractFactory
{
public:
    cModel* createModel(const QString& filePath) override;

private:
    cMaterialLibrary library;
};

class FBXModelFactory : public ModelAbstractFactory
{
public:
    cModel* createModel(const QString& filePath) override;

private:
    cMaterialLibrary library;
};

class cModelLoader{
public:
    explicit cModelLoader(ModelAbstractFactory* strategy = nullptr);

    void setFactory(ModelAbstractFactory *strategy);
    cModel* createModel(const QString& filePath);

private:
    ModelAbstractFactory *m_factory;
    cModelFolder *m_modelFolder;
};
#endif // OBJECTABSTRACTFACTORY_H
