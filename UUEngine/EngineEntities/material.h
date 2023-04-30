#ifndef MATERIAL_H
#define MATERIAL_H

#include <QString>
#include <QVector3D>
#include <QImage>

class Material
{
public:
    Material();

    void setName(const QString &&mtlName);
    const QString &mtlName() const;

    void setDiffuseColor(const QVector3D &&diffuseColor);
    const QVector3D &diffuseColor() const;

    void setAmbienceColor(const QVector3D &&ambienceColor);
    const QVector3D &ambienceColor() const;

    void setSpecularColor(const QVector3D &&specularColor);
    const QVector3D &specularColor() const;

    void setShinnes(const qreal &&shinnes);
    const float &shinnes() const;

    void setDiffuseMap(const QString &&path);
    void setDiffuseMap(const QImage &image);
    const QImage &diffuseMap() const;

    bool isDiffuseMapSet() const;

    void setNormalMap(const QString &&path);
    void setNormalMap(const QImage &image);
    const QImage &normalMap() const;

    bool isNormalMapSet() const;

private:
    QString m_mtlName;

    QVector3D m_diffuseColor;
    QVector3D m_ambienceColor;
    QVector3D m_specularColor;

    float m_shinnes;

    QImage m_diffuseMap;
    QImage m_normalMap;

    bool m_isUsingDiffuseMap;
    bool m_isUsingNormalMap;
};

#endif // MATERIAL_H
