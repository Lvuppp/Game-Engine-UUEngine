#ifndef SKYBOX_H
#define SKYBOX_H

#include "Models/simplemodel.h"
#include "base3dgameobject.h"
#include <QImage>

class SkyBox : public Base3DGameObject
{
public:
    SkyBox(SimpleModel *model);
    ~SkyBox();

};

#endif // SKYBOX_H
