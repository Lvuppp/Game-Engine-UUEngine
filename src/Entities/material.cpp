#include "material.h"


Material::Material() : m_isUsingDiffuseMap(false), m_isUsingNormalMap(false)
{
}

void Material::setName(const QString &&mtlName)
{
    m_mtlName = mtlName;
}

const QString &Material::mtlName() const
{
    return m_mtlName;
}

void Material::setDiffuseColor(const QVector3D &&_diffuseColor)
{
    m_diffuseColor = std::move(_diffuseColor);
}

const QVector3D &Material::diffuseColor() const
{
    return m_diffuseColor;
}

void Material::setAmbienceColor(const QVector3D &&_ambienceColor)
{
    m_ambienceColor = std::move(_ambienceColor);
}

const QVector3D &Material::ambienceColor() const
{
    return m_ambienceColor;
}

void Material::setSpecularColor(const QVector3D &&_specularColor)
{
    m_specularColor = std::move(_specularColor);
}

const QVector3D &Material::specularColor() const
{
    return m_specularColor;
}

void Material::setShinnes(const qreal &&shinnes)
{
    this->m_shinnes = shinnes;
}

const float &Material::shinnes() const
{
    return m_shinnes;
}

void Material::setDiffuseMap(const QString &&path)
{
    m_diffuseMapPath = std::move(path);
    m_diffuseMap = QImage(std::move(path));
    m_isUsingDiffuseMap = true;
}

const QImage &Material::diffuseMap() const
{
    return m_diffuseMap;
}

bool Material::isDiffuseMapSet() const
{
    return m_isUsingDiffuseMap;
}

void Material::setNormalMap(const QString &&path)
{
    m_normalMap = QImage(std::move(path));
    m_normalMapPath = std::move(path);
    m_isUsingNormalMap = true;
}

const QImage &Material::normalMap() const
{
    return m_normalMap;
}

bool Material::isNormalMapSet() const
{

    return m_isUsingNormalMap;
}

QString Material::diffuseMapPath() const
{
    return m_diffuseMapPath;
}

QString Material::normalMapPath() const
{
    return m_normalMapPath;
}
