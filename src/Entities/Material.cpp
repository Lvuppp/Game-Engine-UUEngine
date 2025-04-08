#include "Material.h"

cMaterial::cMaterial() : m_isUsingDiffuseMap(false), m_isUsingNormalMap(false)
{
}

void cMaterial::setName(std::string_view mtlName)
{
    m_mtlName = mtlName;
}

std::string_view cMaterial::mtlName() const
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

void cMaterial::setDiffuseMap(std::string_view path)
{
    m_diffuseMapPath = path;
    m_diffuseMap = QImage(path.data());
    m_isUsingDiffuseMap = true;
}

const QImage &cMaterial::diffuseMap() const
{
    return m_diffuseMap;
}

bool cMaterial::isDiffuseMapSet() const
{
    return m_isUsingDiffuseMap;
}

void cMaterial::setNormalMap(std::string_view path)
{
    m_normalMap = QImage(path.data());
    m_normalMapPath = path;
    m_isUsingNormalMap = true;
}

const QImage &cMaterial::normalMap() const
{
    return m_normalMap;
}

bool cMaterial::isNormalMapSet() const
{
    return m_isUsingNormalMap;
}

std::string_view cMaterial::diffuseMapPath() const
{
    return m_diffuseMapPath;
}

std::string_view cMaterial::normalMapPath() const
{
    return m_normalMapPath;
}
