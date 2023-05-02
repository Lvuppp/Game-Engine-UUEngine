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
    Model(const QVector<VertexData> &vertexes, const QVector<GLuint> &indexes,Material *material);

    void initModel(const QVector<VertexData> &vertexes, const QVector<GLuint> &indexes,Material *material);
    void drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions = 0);

    Material *material() const;
    void setMaterial(Material *newMaterial);

public:
    QOpenGLBuffer m_vertexes;
    QOpenGLBuffer m_indexes;
    QOpenGLTexture *m_diffuseMap;
    QOpenGLTexture *m_normalMap;
    Material *m_material;
};
#endif // MODEL_H
