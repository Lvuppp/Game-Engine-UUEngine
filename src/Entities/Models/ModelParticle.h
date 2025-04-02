#ifndef MODELPARTICLE_H
#define MODELPARTICLE_H

#include "Material.h"
#include "VertexData.h"

#include <QtOpenGL>

class cModelParticle
{
public:
    cModelParticle();
    ~cModelParticle();
    cModelParticle(QVector<sVertexData> &vertexes, QVector<GLuint> &indexes, cMaterial *material);

    void initModelParticle(QVector<sVertexData> &vertexes, QVector<GLuint> &indexes, cMaterial *material);
    void calculateTBN(QVector<sVertexData> &vertexes);
    void drawModelParticle(const QMatrix4x4 &modelParticleMatrix, QOpenGLShaderProgram *shaderProgram, bool isUsingTexture, QOpenGLFunctions *functions = nullptr);
    QVector<sVertexData> vertexesData() const;

    void setDiffuseMap(const QString &texture);
    void setNormalMap(const QString &texture);
    cMaterial *material() const;
    void setMaterial(cMaterial *newMaterial);

private:
    QVector<sVertexData> m_vertexesData;
    QOpenGLBuffer m_vertexes;
    QOpenGLBuffer m_indexes;
    QOpenGLTexture *m_diffuseMap;
    QOpenGLTexture *m_normalMap;
    cMaterial *m_material;
};

#endif // MODELPARTICLE_H
