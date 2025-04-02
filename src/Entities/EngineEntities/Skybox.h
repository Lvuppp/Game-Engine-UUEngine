#ifndef SKYBOX_H
#define SKYBOX_H

#include "Models/SimpleModel.h"
#include "Base3DGameObject.h"
#include <QImage>

class cSkyBox : public cBase3DGameObject
{
public:
    cSkyBox(cSimpleModel *model);
    ~cSkyBox();

};

#endif // SKYBOX_H
