#ifndef MATERIAL_H
#define MATERIAL_H

#include <QVector3D>
#include <QImage>
#include <qopengltexture.h>

class cMaterial
{
public:
    cMaterial() = default;

    void setName(std::string_view mtlName);
    std::string_view getName() const;

    void setDiffuseColor(const QVector3D& diffuseColor);
    const QVector3D& diffuseColor() const;

    void setAmbienceColor(const QVector3D& ambienceColor);
    const QVector3D& ambienceColor() const;

    void setSpecularColor(const QVector3D& specularColor);
    const QVector3D& specularColor() const;

    void setShinnes(float shinnes);
    float shinnes() const;

    void setDiffuseMap(QOpenGLTexture* texture);
    QOpenGLTexture* getDiffuseMap() const;

    void setNormalMap(QOpenGLTexture* texture);
    QOpenGLTexture* getNormalMap() const;

private:
    std::string m_mtlName;

    QVector3D m_diffuseColor = QVector3D(0.7f, 0.7f, 0.7f);
    QVector3D m_ambienceColor = QVector3D(1.0f, 1.0f, 1.0f);
    QVector3D m_specularColor = QVector3D(1.0f, 1.0f, 1.0f);

    float m_shinnes = 100.0f;

    QOpenGLTexture* m_diffuseMap = nullptr;
    QOpenGLTexture* m_normalMap = nullptr;
};

#endif // MATERIAL_H
