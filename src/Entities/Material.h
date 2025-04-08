#ifndef MATERIAL_H
#define MATERIAL_H

#include <QVector3D>
#include <QImage>

class cMaterial
{
public:
    cMaterial();

    void setName(std::string_view mtlName);
    std::string_view mtlName() const;

    void setDiffuseColor(const QVector3D& diffuseColor);
    const QVector3D& diffuseColor() const;

    void setAmbienceColor(const QVector3D& ambienceColor);
    const QVector3D& ambienceColor() const;

    void setSpecularColor(const QVector3D& specularColor);
    const QVector3D& specularColor() const;

    void setShinnes(float shinnes);
    float shinnes() const;

    void setDiffuseMap(std::string_view path);
    const QImage &diffuseMap() const;
    std::string_view diffuseMapPath() const;
    bool isDiffuseMapSet() const;

    void setNormalMap(std::string_view path);
    const QImage &normalMap() const;
    std::string_view normalMapPath() const;
    bool isNormalMapSet() const;

private:
    std::string_view m_mtlName;
    std::string_view m_diffuseMapPath = "null";
    std::string_view m_normalMapPath = "null";

    QVector3D m_diffuseColor = QVector3D(0.7f, 0.7f, 0.7f);
    QVector3D m_ambienceColor = QVector3D(1.0f, 1.0f, 1.0f);
    QVector3D m_specularColor = QVector3D(1.0f, 1.0f, 1.0f);

    float m_shinnes = 100.0f;

    QImage m_diffuseMap;
    QImage m_normalMap;

    bool m_isUsingDiffuseMap = false;
    bool m_isUsingNormalMap = false;
};

#endif // MATERIAL_H
