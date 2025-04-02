#include "Material.h"

cMaterial::cMaterial() : m_isUsingDiffuseMap(false), m_isUsingNormalMap(false)
{
}

void cMaterial::setName(const QString &mtlName)
{
    m_mtlName = mtlName;
}

const QString &cMaterial::mtlName() const
{
    return m_mtlName;
}

void cMaterial::setDiffuseColor(const QVector3D &_diffuseColor)
{
    m_diffuseColor = _diffuseColor;
}

const QVector3D &cMaterial::diffuseColor() const
{
    return m_diffuseColor;
}

void cMaterial::setAmbienceColor(const QVector3D &_ambienceColor)
{
    m_ambienceColor = _ambienceColor;
}

const QVector3D &cMaterial::ambienceColor() const
{
    return m_ambienceColor;
}

void cMaterial::setSpecularColor(const QVector3D &_specularColor)
{
    m_specularColor = _specularColor;
}

const QVector3D &cMaterial::specularColor() const
{
    return m_specularColor;
}

void cMaterial::setShinnes(qreal shinnes)
{
    this->m_shinnes = shinnes;
}

float cMaterial::shinnes() const
{
    return m_shinnes;
}

void cMaterial::setDiffuseMap(const QString &path)
{
    m_diffuseMapPath = path;
    m_diffuseMap = QImage(path);
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

void cMaterial::setNormalMap(const QString &path)
{
    m_normalMap = QImage(path);
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

QString cMaterial::diffuseMapPath() const
{
    return m_diffuseMapPath;
}

QString cMaterial::normalMapPath() const
{
    return m_normalMapPath;
}
