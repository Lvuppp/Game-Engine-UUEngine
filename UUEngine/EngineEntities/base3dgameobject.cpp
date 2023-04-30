#include "base3dgameobject.h"

Base3DGameObject::Base3DGameObject(const QVector3D &coordinates, const QQuaternion &rotation,
                                   const float &scale, const bool &isObjectLocked):
    BaseEngineObject(coordinates, rotation, scale, isObjectLocked)
{
    s_indexes = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
}

Base3DGameObject::Base3DGameObject(const QVector<VertexData> &vertexes, const QVector<GLuint> &indexes,
                                   const QImage &texture,const float &ambiendFactor,const float &specularFactor, const QVector3D &coordinates,
                                   const QQuaternion &rotation, const float &scale, const bool &isObjectLocked):
    BaseEngineObject(coordinates, rotation, scale, isObjectLocked), s_specularFactor(specularFactor), s_ambiendFactor(ambiendFactor)
{
    s_indexes = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

    if(!texture.isNull())
        setTexture(texture);

    if(!vertexes.isEmpty())
        setVertexesBuffer(vertexes);

    if(!indexes.isEmpty())
        setIndexesBuffer(indexes);
}

Base3DGameObject::~Base3DGameObject()
{
    if(s_vertexes.isCreated())
        s_vertexes.destroy();

    if(s_indexes.isCreated())
        s_indexes.destroy();

    if(s_texture != 0){
        if(s_texture->isCreated()){
            delete s_texture;
        }
    }
}

void Base3DGameObject::setTexture(const QImage &newTexture)
{
    s_texture = new QOpenGLTexture(newTexture.mirrored());

    s_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    s_texture->setMinificationFilter(QOpenGLTexture::Linear);
    s_texture->setWrapMode(QOpenGLTexture::Repeat);
}

void Base3DGameObject::setVertexesBuffer(const QVector<VertexData> &newVertexes)
{
    if(newVertexes.size() == 0)
        return;

    if(s_vertexes.isCreated())
        s_vertexes.destroy();

    s_vertexes.create();
    s_vertexes.bind();
    s_vertexes.allocate(newVertexes.constData(), newVertexes.size() * sizeof(VertexData));
    s_vertexes.release();
}

void Base3DGameObject::setIndexesBuffer(const QVector<GLuint> &newIndexes)
{
    if(newIndexes.size() == 0)
        return;

    if(s_indexes.isCreated())
        s_indexes.destroy();

    s_indexes.create();
    s_indexes.bind();
    s_indexes.allocate(newIndexes.constData(), newIndexes.size() * sizeof(VertexData));
    s_indexes.release();
}

float Base3DGameObject::specularFactor() const
{
    return s_specularFactor;
}

void Base3DGameObject::setSpecularFactor(float newSpecularFactor)
{
    s_specularFactor = newSpecularFactor;
}

float Base3DGameObject::ambiendFactor() const
{
    return s_ambiendFactor;
}

void Base3DGameObject::setAmbiendFactor(float newAmbientFactor)
{
    s_ambiendFactor = newAmbientFactor;
}

void Base3DGameObject::draw(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions)
{
    s_texture->bind(0);

    shaderProgram->setUniformValue("u_texture", 0);
    shaderProgram->setUniformValue("u_modelMatrix", modelMatrix());
    shaderProgram->setUniformValue("u_specularFactor", specularFactor()); // блик от объекта
    shaderProgram->setUniformValue("u_ambientFactor", ambiendFactor()); // свечение материала

    s_vertexes.bind();
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

    s_indexes.bind();

    functions->glDrawElements(GL_POLYGON, s_indexes.size(), GL_UNSIGNED_INT, 0);

    s_vertexes.release();
    s_indexes.release();
    s_texture->release();
}
