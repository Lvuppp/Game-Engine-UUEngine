#include "modelprocessor.h"


ModelProcessor::ModelProcessor(QOpenGLShaderProgram *shaderProgram, QOpenGLFunctions *functions)
{
    m_shaderProgram = shaderProgram;
    m_functions = functions;
}

void ModelProcessor::processModel(Base3DGameObject *object)
{
    auto texture = object->texture();
    auto vertexesBuffer = object->vertexesBuffer();
    auto indexesBuffer = object->indexesBuffer();

    texture->bind(0);
    m_shaderProgram->setUniformValue("u_texture", 0);
    m_shaderProgram->setUniformValue("u_modelMatrix", object->modelMatrix());
    m_shaderProgram->setUniformValue("u_specularFactor", object->specularFactor()); // блик от объекта
    m_shaderProgram->setUniformValue("u_ambientFactor", object->ambiendFactor()); // свечение материала

    vertexesBuffer->bind();
    int offset = 0;
    int vertLoc = m_shaderProgram->attributeLocation("a_position");

    m_shaderProgram->enableAttributeArray(vertLoc);
    m_shaderProgram->setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);
    int textLoc = m_shaderProgram->attributeLocation("a_texcoord");

    m_shaderProgram->enableAttributeArray(textLoc);
    m_shaderProgram->setAttributeBuffer(textLoc, GL_FLOAT, offset, 2, sizeof(VertexData));

    offset += sizeof(QVector2D);
    int normLoc = m_shaderProgram->attributeLocation("a_normal");

    m_shaderProgram->enableAttributeArray(normLoc);
    m_shaderProgram->setAttributeBuffer(normLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    indexesBuffer->bind();

    m_functions->glDrawElements(GL_TRIANGLES, indexesBuffer->size(), GL_UNSIGNED_INT, 0);

    vertexesBuffer->release();
    indexesBuffer->release();
    texture->release();

}
