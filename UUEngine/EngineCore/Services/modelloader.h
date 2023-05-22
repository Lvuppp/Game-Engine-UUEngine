#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "Folders/materiallib.h"

#include "projectinfo.h"
class CustomModel;


class ModelLoadStraregy
{
public:
    ModelLoadStraregy();
    virtual ~ModelLoadStraregy();

    virtual CustomModel* createModel(const QString& filePath) = 0;

};

class OBJModelLoadStraregy : public ModelLoadStraregy
{
public:
    OBJModelLoadStraregy();
    ~OBJModelLoadStraregy();
    CustomModel*  createModel(const QString& filePath) override;

private:
    MaterialLibrary library;
};

class FBXModelLoadStraregy : public ModelLoadStraregy
{
public:
    FBXModelLoadStraregy();
    ~FBXModelLoadStraregy();
    CustomModel*  createModel(const QString& filePath) override;

private:
    MaterialLibrary library;
};

class ModelLoader{
public:
    explicit ModelLoader(ModelLoadStraregy* strategy = nullptr);

    void setStrategy(ModelLoadStraregy *strategy);
    CustomModel* createModel(const QString& filePath);

private:
    ModelLoadStraregy *m_strategy;
};

#endif // OBJECTABSTRACTFACTORY_H
