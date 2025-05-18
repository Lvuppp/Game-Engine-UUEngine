#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "Core/Folders/MaterialLib.h"

class cModel;
class cModelFolder;

class ModelAbstractFactory
{
public:
    virtual ~ModelAbstractFactory() = default;

    virtual cModel* createModel(std::string_view filePath) = 0;

};

class OBJModelFactory : public ModelAbstractFactory
{
public:
    OBJModelFactory(cTextureManager* textureManager);
    cModel* createModel(std::string_view filePath) override;

private:
    cMaterialLibrary m_library;
};

class FBXModelFactory : public ModelAbstractFactory
{
public:
    cModel* createModel(std::string_view filePath) override;

private:
    //cMaterialLibrary library;
};

class cModelLoader{
public:
    void setFactory(ModelAbstractFactory *strategy);
    cModel* createModel(std::string_view filePath);

private:
    ModelAbstractFactory* m_factory = nullptr;
    cModelFolder* m_modelFolder = nullptr;
};
#endif // OBJECTABSTRACTFACTORY_H
