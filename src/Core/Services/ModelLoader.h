#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "Core/Folders/MaterialLib.h"

class cModel;
class cModelFolder;

class ModelAbstractFactory
{
public:
    virtual ~ModelAbstractFactory() = default;

    virtual cModel* createModel(const std::string& filePath) = 0;

};

class OBJModelFactory : public ModelAbstractFactory
{
public:
    cModel* createModel(const std::string& filePath) override;

private:
    cMaterialLibrary library;
};

class FBXModelFactory : public ModelAbstractFactory
{
public:
    cModel* createModel(const std::string& filePath) override;

private:
    cMaterialLibrary library;
};

class cModelLoader{
public:
    void setFactory(ModelAbstractFactory *strategy);
    cModel* createModel(const std::string& filePath);

private:
    ModelAbstractFactory *m_factory = nullptr;
    cModelFolder *m_modelFolder = nullptr;
};
#endif // OBJECTABSTRACTFACTORY_H
