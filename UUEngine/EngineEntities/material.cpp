#include "material.h"


Material::Material() : isUsingDiffuseMap(false), isUsingNormalMap (false)
{

}

void Material::setName(const QString &&_mtlName)
{
    mtlName = _mtlName;
}

const QString &Material::MtlName() const
{
    return mtlName;
}

void Material::setDiffuseColor(const QVector3D &&_diffuseColor)
{
    diffuseColor = std::move(_diffuseColor);

    isUsingDiffuseMap = true;
}

const QVector3D &Material::getDiffuseColor() const
{
    return diffuseColor;
}

void Material::setAmbienceColor(const QVector3D &&_ambienceColor)
{
    ambienceColor = std::move(_ambienceColor);
}

const QVector3D &Material::AmbienceColor() const
{
    return ambienceColor;
}

void Material::setSpecularColor(const QVector3D &&_specularColor)
{
    specularColor = std::move(_specularColor);
}

const QVector3D &Material::SpecularColor() const
{
    return specularColor;
}

void Material::setShinnes(const qreal &&shinnes)
{
    this->shinnes = shinnes;
}

const float &Material::getShinnes() const
{
    return shinnes;
}

void Material::setDiffuseMap(const QString &&path)
{
    diffuseMap = QImage(std::move(path));
}

void Material::setDiffuseMap(const QImage &image)
{
    diffuseMap = image;
}

const QImage &Material::getDiffuseMap() const
{
    return diffuseMap;
}

bool Material::isDiffuseMapSet() const
{
    return isUsingDiffuseMap;
}

void Material::setNormalMap(const QString &&path)
{
    normalMap = QImage(std::move(path));

    isUsingNormalMap = true;
}

void Material::setNormalMap(const QImage &image)
{
    normalMap = image;

    isUsingNormalMap = true;
}

const QImage &Material::getNormalMap() const
{
    return normalMap;
}

bool Material::isNormalMapSet() const
{
    return isUsingNormalMap;
}
