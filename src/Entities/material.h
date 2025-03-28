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
    const QImage &diffuseMap() const;
    QString diffuseMapPath() const;

    bool isDiffuseMapSet() const;

    void setNormalMap(const QString &&path);
    const QImage &normalMap() const;
    QString normalMapPath() const;

    bool isNormalMapSet() const;


private:
    QString m_mtlName;
    QString m_diffuseMapPath = "null";
    QString m_normalMapPath = "null";

    QVector3D m_diffuseColor = QVector3D(0.7f,0.7f,0.7f);
    QVector3D m_ambienceColor = QVector3D(1.0f,1.0f,1.0f);
    QVector3D m_specularColor = QVector3D(1.0f,1.0f,1.0f);

    float m_shinnes = 100.0f;

    QImage m_diffuseMap;
    QImage m_normalMap;

    bool m_isUsingDiffuseMap;
    bool m_isUsingNormalMap;
};

#endif // MATERIAL_H
