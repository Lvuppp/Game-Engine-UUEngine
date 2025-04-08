#ifndef MODELPARTICLE_H
#define MODELPARTICLE_H

#include "Entities/Material.h"
#include "Entities/VertexData.h"
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

class QOpenGLFunctions;
class QOpenGLShaderProgram;

class cModelParticle
{
public:
    cModelParticle();

    using Vertexes = std::vector<sVertexData>;
    using Indexes = std::vector<GLuint>;
    cModelParticle(Vertexes& vertexes, Indexes& indexes, cMaterial* material);

    ~cModelParticle();

    void initModelParticle(Vertexes& vertexes, Indexes& indexes, cMaterial* material);
    void calculateTBN(Vertexes& vertexes);
    void drawModelParticle(const QMatrix4x4& modelMatrix, QOpenGLShaderProgram* shaderProgram, bool isUsingTexture, QOpenGLFunctions* functions);

    void setDiffuseMap(std::string_view texture);
    void setNormalMap(std::string_view texture);
    void setMaterial(cMaterial* material);

    const Vertexes& vertexesData() const;
    cMaterial* getMaterial() const;

private:
    Vertexes m_vertexesData;
    QOpenGLBuffer m_vertexes;
    QOpenGLBuffer m_indexes;

    std::unique_ptr<QOpenGLTexture> m_diffuseMap;
    std::unique_ptr<QOpenGLTexture> m_normalMap;
    std::unique_ptr<cMaterial> m_material;
};
#endif // MODELPARTICLE_H
