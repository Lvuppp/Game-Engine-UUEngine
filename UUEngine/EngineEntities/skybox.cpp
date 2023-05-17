#include "skybox.h"

SkyBox::SkyBox(Model *model) : m_model(model)
{
}

SkyBox::~SkyBox()
{
    delete m_model;
}

Model *SkyBox::model()
{
    return m_model;
}

void SkyBox::setDiffuseMap(QString texture)
{
    m_model->material()->setDiffuseMap(std::move(texture));
}


