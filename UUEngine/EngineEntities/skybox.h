#ifndef SKYBOX_H
#define SKYBOX_H

#include "base3dgameobject.h"

#include <QImage>

class SkyBox
{
public:
    SkyBox(const float& size, const QImage& texture);
    ~SkyBox();

    Base3DGameObject *model();

private:
    Base3DGameObject *m_model;

};

#endif // SKYBOX_H
