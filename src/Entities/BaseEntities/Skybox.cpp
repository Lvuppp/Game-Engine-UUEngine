#include "Skybox.h"

#include "Entities/BaseEntities/BaseEngineObject.h"

cSkyBox::cSkyBox(uint32_t hash,cModel *model)
    : cBase3DGameObject(hash, model)
{
}

cBaseEngineObject::ObjectType cSkyBox::objectType() const
{
    return cBaseEngineObject::ObjectType::SkyBox;
}
