#ifndef MODELPARTICLE_H
#define MODELPARTICLE_H

#include "material.h"
#include "vertexdata.h"

#include <QtOpenGL>

class ModelParticle
{
public:
    ModelParticle();
    ~ModelParticle();
    ModelParticle(QVector<VertexData> &vertexes, QVector<GLuint> &indexes,Material *material);

    void initModelParticle(QVector<VertexData> &vertexes,QVector<GLuint> &indexes,Material *material);
    void calculateTBN(QVector<VertexData> &vertexes);
    void drawModelParticle(const QMatrix4x4 &ModelParticleMatrix, QOpenGLShaderProgram *shaderProgram, bool isUsingTexture, QOpenGLFunctions *functions = 0);
    QVector<VertexData> vertexesData();

    void setDiffuseMap(QString texture);
    void setNormalMap(QString texture);
    Material *material() const;
    void setMaterial(Material *newMaterial);

private:
    QVector<VertexData> m_vertexesData;
    QOpenGLBuffer m_vertexes;
    QOpenGLBuffer m_indexes;
    QOpenGLTexture *m_diffuseMap;
    QOpenGLTexture *m_normalMap;
    Material *m_material;
};
#endif //MODELPARTICLE_H
