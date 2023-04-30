#ifndef OBJECTABSTRACTFACTORY_H
#define OBJECTABSTRACTFACTORY_H

#include "base3dgameobject.h"


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
};



#endif // OBJECTABSTRACTFACTORY_H
