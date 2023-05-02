#include "model.h"
Model::Model(): m_diffuseMap(0),m_normalMap(0)
{
    m_indexes = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
}

Model::~Model()
{
    if(m_vertexes.isCreated())
        m_vertexes.destroy();

    if(m_indexes.isCreated())
        m_indexes.destroy();

    if(m_diffuseMap != 0)
        if(m_diffuseMap->isCreated())
            delete m_diffuseMap;

    if(m_normalMap != 0)
        if(m_normalMap->isCreated())
            delete m_normalMap;

}

Model::Model(const QVector<VertexData> &vertexes, const QVector<GLuint> &indexes, Material *material)
{
    m_indexes = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    initModel(vertexes,indexes, material);
}

void Model::initModel(const QVector<VertexData> &vertexes, const QVector<GLuint> &indexes, Material *material)
{
    if(vertexes.size() == 0){
        return;
    }

    if(indexes.size() == 0){
        return;
    }

    if(m_vertexes.isCreated()){
        m_vertexes.destroy();
    }

    if(m_indexes.isCreated()){
        m_indexes.destroy();
    }

    //    if(m_texture != 0){
    //        if(m_texture->isCreated()){
    //            delete m_texture;
    //        }
    //    }

    m_vertexes.create();
    m_vertexes.bind();
    m_vertexes.allocate(vertexes.constData(), vertexes.size() * sizeof(VertexData));
    m_vertexes.release();

    m_indexes.create();
    m_indexes.bind();
    m_indexes.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
    m_indexes.release();

    m_material = material;

    if(m_material->isDiffuseMapSet()){
        m_diffuseMap = new QOpenGLTexture(m_material->diffuseMap().mirrored());

        m_diffuseMap->setMinificationFilter(QOpenGLTexture::Nearest);
        m_diffuseMap->setMinificationFilter(QOpenGLTexture::Linear);
        m_diffuseMap->setWrapMode(QOpenGLTexture::Repeat);
    }

    if(m_material->isNormalMapSet()){
        m_normalMap = new QOpenGLTexture(m_material->normalMap().mirrored());

        m_normalMap->setMinificationFilter(QOpenGLTexture::Nearest);
        m_normalMap->setMinificationFilter(QOpenGLTexture::Linear);
        m_normalMap->setWrapMode(QOpenGLTexture::Repeat);
    }
}

void Model::drawModel(const QMatrix4x4 &modelMatrix, QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions)
{
    if(m_material->isDiffuseMapSet()){
        m_diffuseMap->bind(0);
        shaderProgram->setUniformValue("u_model.diffuseMap", 0);
    }

    if(m_material->isNormalMapSet()){
        m_normalMap->bind(1);
        shaderProgram->setUniformValue("u_model.normalMap", 1);
    }

    shaderProgram->setUniformValue("u_modelMatrix", modelMatrix);
    shaderProgram->setUniformValue("u_model.u_isDiffuseMapUsing", m_material->isDiffuseMapSet());
    shaderProgram->setUniformValue("u_model.u_isNormalMapUsing", m_material->isNormalMapSet());
    shaderProgram->setUniformValue("u_model.diffuseColor", m_material->diffuseColor());
    shaderProgram->setUniformValue("u_model.specularColor", m_material->specularColor());
    shaderProgram->setUniformValue("u_model.ambienceColor", m_material->ambienceColor());
    shaderProgram->setUniformValue("u_model.shinnes", m_material->shinnes());

    m_vertexes.bind();
    int offset = 0;
    int vertLoc = shaderProgram->attributeLocation("a_position");

    shaderProgram->enableAttributeArray(vertLoc);
    shaderProgram->setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);
    int textLoc = shaderProgram->attributeLocation("a_texcoord");

    shaderProgram->enableAttributeArray(textLoc);
    shaderProgram->setAttributeBuffer(textLoc, GL_FLOAT, offset, 2, sizeof(VertexData));

    offset += sizeof(QVector2D);
    int normLoc = shaderProgram->attributeLocation("a_normal");

    shaderProgram->enableAttributeArray(normLoc);
    shaderProgram->setAttributeBuffer(normLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    m_indexes.bind();

    functions->glDrawElements(GL_TRIANGLES, m_indexes.size(), GL_UNSIGNED_INT, 0);

    m_vertexes.release();
    m_indexes.release();

    if(m_material->isDiffuseMapSet()) m_diffuseMap->release();
    if(m_material->isNormalMapSet()) m_normalMap->release();
}

Material *Model::material() const
{
    return m_material;
}

void Model::setMaterial(Material *newMaterial)
{
    m_material = newMaterial;
}
