#include "Material.h"

void cMaterial::setName(std::string_view mtlName)
{
    m_mtlName = mtlName;
}

std::string_view cMaterial::getName() const
{
    return m_mtlName;
}

void cMaterial::setDiffuseColor(const QVector3D& diffuseColor)
{
    m_diffuseColor = diffuseColor;
}

const QVector3D &cMaterial::diffuseColor() const
{
    return m_diffuseColor;
}

void cMaterial::setAmbienceColor(const QVector3D& ambienceColor)
{
    m_ambienceColor = ambienceColor;
}

const QVector3D &cMaterial::ambienceColor() const
{
    return m_ambienceColor;
}

void cMaterial::setSpecularColor(const QVector3D &specularColor)
{
    m_specularColor = specularColor;
}

const QVector3D &cMaterial::specularColor() const
{
    return m_specularColor;
}

void cMaterial::setShinnes(float shinnes)
{
    m_shinnes = shinnes;
}

float cMaterial::shinnes() const
{
    return m_shinnes;
}

void cMaterial::setDiffuseMap(QOpenGLTexture* texture)
{
    m_diffuseMap = texture;
}

QOpenGLTexture* cMaterial::getDiffuseMap() const
{
    return m_diffuseMap;
}

void cMaterial::setNormalMap(QOpenGLTexture* texture)
{
    m_normalMap = texture;
}

QOpenGLTexture* cMaterial::getNormalMap() const
{
    return m_normalMap;
}
