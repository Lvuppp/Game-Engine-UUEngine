#include "ModelParticle.h"

#include "QOpenGLFunctions"
#include "QOpenGLTexture"
#include "QOpenGLShaderProgram"

cModelParticle::cModelParticle()
{
    m_indexes = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
}

cModelParticle::~cModelParticle()
{
    if (m_vertexes.isCreated())
    {
        m_vertexes.destroy();
    }

    if (m_indexes.isCreated())
    {
        m_indexes.destroy();
    }
}

cModelParticle::cModelParticle(Vertexes& vertexes, Indexes& indexes, cMaterial* material)
{
    m_indexes = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    initModelParticle(vertexes,indexes, material);
    setMaterial(material);
}

void cModelParticle::initModelParticle(Vertexes& vertexes, Indexes& indexes, cMaterial* material)
{
    if (vertexes.size() == 0)
    {
        return;
    }

    if (indexes.size() == 0)
    {
        return;
    }

    if (m_vertexes.isCreated())
    {
        m_vertexes.destroy();
    }

    if (m_indexes.isCreated())
    {
        m_indexes.destroy();
    }

    calculateTBN(vertexes);
    m_vertexesData = vertexes;

    m_vertexes.create();
    m_vertexes.bind();
    m_vertexes.allocate(vertexes.data(), vertexes.size() * sizeof(sVertexData));
    m_vertexes.release();

    m_indexes.create();
    m_indexes.bind();
    m_indexes.allocate(indexes.data(), indexes.size() * sizeof(GLuint));
    m_indexes.release();
}

void cModelParticle::drawModelParticle(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, bool isUsingTexture, QOpenGLFunctions *functions)
{
    const auto normalMap = m_material->getNormalMap();
    const auto diffuseMap = m_material->getDiffuseMap();

    const auto isNormalMapSet = normalMap != nullptr;
    const auto isDiffuseMapSet = diffuseMap != nullptr;

    if (isDiffuseMapSet)
    {
        diffuseMap->bind(0);
        shaderProgram->setUniformValue("u_model.diffuseMap", 0);
    }

    if (isNormalMapSet)
    {
        normalMap->bind(1);
        shaderProgram->setUniformValue("u_model.normalMap", 1);
    }

    shaderProgram->setUniformValue("u_modelMatrix", modelMatrix);
    shaderProgram->setUniformValue("u_model.isDiffuseMapUsing", isNormalMapSet);
    shaderProgram->setUniformValue("u_model.isNormalMapUsing", isNormalMapSet);
    shaderProgram->setUniformValue("u_model.diffuseColor", m_material->diffuseColor());
    shaderProgram->setUniformValue("u_model.specularColor", m_material->specularColor());
    shaderProgram->setUniformValue("u_model.ambienceColor", m_material->ambienceColor());
    shaderProgram->setUniformValue("u_model.shinnes", m_material->shinnes());

    m_vertexes.bind();
    size_t offset = 0u;
    size_t vertLoc = shaderProgram->attributeLocation("a_position");

    shaderProgram->enableAttributeArray(vertLoc);
    shaderProgram->setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(sVertexData));

    offset += sizeof(QVector3D);
    size_t textureCoordinations = shaderProgram->attributeLocation("a_texcoord");

    shaderProgram->enableAttributeArray(textureCoordinations);
    shaderProgram->setAttributeBuffer(textureCoordinations, GL_FLOAT, offset, 2, sizeof(sVertexData));

    offset += sizeof(QVector2D);
    size_t normLoc = shaderProgram->attributeLocation("a_normal");

    shaderProgram->enableAttributeArray(normLoc);
    shaderProgram->setAttributeBuffer(normLoc, GL_FLOAT, offset, 3, sizeof(sVertexData));

    offset += sizeof(QVector3D);
    size_t tanLoc = shaderProgram->attributeLocation("a_tangent");

    shaderProgram->enableAttributeArray(tanLoc);
    shaderProgram->setAttributeBuffer(tanLoc, GL_FLOAT, offset, 3, sizeof(sVertexData));

    offset += sizeof(QVector3D);
    size_t bitanLoc = shaderProgram->attributeLocation("a_bitangent");

    shaderProgram->enableAttributeArray(bitanLoc);
    shaderProgram->setAttributeBuffer(bitanLoc, GL_FLOAT, offset, 3, sizeof(sVertexData));

    m_indexes.bind();

    functions->glDrawElements(GL_TRIANGLES, m_indexes.size(), GL_UNSIGNED_INT, 0);

    m_vertexes.release();
    m_indexes.release();

    if (isDiffuseMapSet)
    {
        diffuseMap->release();
    }

    if (isNormalMapSet)
    {
        normalMap->release();
    }
}

const cModelParticle::Vertexes& cModelParticle::vertexesData() const
{
    return m_vertexesData;
}

void cModelParticle::calculateTBN(Vertexes& vertexes)
{
    for (auto i = 0u; i < vertexes.size(); i += 3u)
    {
        QVector3D &v1 = vertexes[i].position;
        QVector3D &v2 = vertexes[i + 1].position;
        QVector3D &v3 = vertexes[i + 2].position;

        QVector2D &uv1 = vertexes[i].texture;
        QVector2D &uv2 = vertexes[i + 1].texture;
        QVector2D &uv3 = vertexes[i + 2].texture;

        QVector3D deltaV1 = v2 - v1;
        QVector3D deltaV2 = v3 - v1;

        QVector2D deltaUV1 = uv2 - uv1;
        QVector2D deltaUV2 = uv3 - uv1;

        float r = 1.0f / (deltaV1.x() * deltaUV2.y() - deltaUV1.y() * deltaUV2.x());

        QVector3D tangent = (deltaV1 * deltaUV1.y() - deltaV2 * deltaUV1.y()) * r;
        QVector3D bitangent = (deltaV2 * deltaUV1.x() - deltaV1 * deltaUV2.x()) * r;

        vertexes[i].tangent = tangent;
        vertexes[i + 1].tangent = tangent;
        vertexes[i + 2].tangent = tangent;

        vertexes[i].bitangent = bitangent;
        vertexes[i + 1].bitangent = bitangent;
        vertexes[i + 2].bitangent = bitangent;
    }

}

void cModelParticle::setDiffuseMap(QOpenGLTexture* texture)
{
    m_material->setDiffuseMap(texture);
}

void cModelParticle::setNormalMap(QOpenGLTexture* texture)
{
    m_material->setNormalMap(texture);
}

cMaterial *cModelParticle::getMaterial() const
{
    return m_material.get();
}

void cModelParticle::setMaterial(cMaterial* material)
{
    m_material.reset(material);
}
