#ifndef SKYBOX_H
#define SKYBOX_H

#include "Entities/BaseEntities/Base3DGameObject.h"

class cSkyBox : public cBase3DGameObject
{
public:
    cSkyBox(uint32_t hash, cModel* model);

public:
    ObjectType objectType() const override;
};

#endif // SKYBOX_H
