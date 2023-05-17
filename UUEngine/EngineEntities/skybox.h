#ifndef SKYBOX_H
#define SKYBOX_H

#include "model.h"

#include <QImage>

class SkyBox
{
public:
    SkyBox(Model *model);
    ~SkyBox();

    Model *model();
    void setDiffuseMap(QString texturePath);

private:
    Model *m_model;

};

#endif // SKYBOX_H
