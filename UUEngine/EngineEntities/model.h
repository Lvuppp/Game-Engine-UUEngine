#ifndef MODEL_H
#define MODEL_H


#include "material.h"
#include "vertexdata.h"

#include <QtOpenGL>

class Model
{
public:
    Model();
    ~Model();
    Model(QVector<VertexData> &vertexes, QVector<GLuint> &indexes,Material *material);

    void initModel(QVector<VertexData> &vertexes,QVector<GLuint> &indexes,Material *material);
    void calculateTBN(QVector<VertexData> &vertexes);
    void drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions = 0);

    void setDiffuseMap(QString texture);
    void setNormalMap(QString texture);
    Material *material() const;
    void setMaterial(Material *newMaterial);

private:
    QOpenGLBuffer m_vertexes;
    QOpenGLBuffer m_indexes;
    QOpenGLTexture *m_diffuseMap;
    QOpenGLTexture *m_normalMap;
    Material *m_material;
};
#endif // MODEL_H
