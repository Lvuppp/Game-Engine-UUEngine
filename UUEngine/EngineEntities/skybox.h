#ifndef SKYBOX_H
#define SKYBOX_H

#include "model.h"

#include <QImage>

class SkyBox
{
public:
    SkyBox(const float& size, QImage texture);
    ~SkyBox();

    Model *model();
    void setDiffuseMap(QImage texture);

private:
    Model *m_model;

};

#endif // SKYBOX_H
