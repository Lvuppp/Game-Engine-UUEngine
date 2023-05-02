#ifndef OBJECTABSTRACTFACTORY_H
#define OBJECTABSTRACTFACTORY_H

#include "base3dgameobject.h"
#include "materiallib.h"

class ModelAbstractFactory
{
public:

};

class ObjectAbstractFactory
{
public:
    ObjectAbstractFactory();
    Base3DGameObject *createObject(const QString& filePath);
private:
    ModelAbstractFactory *m_factory;
    MaterialLibrary library;
};



#endif // OBJECTABSTRACTFACTORY_H
