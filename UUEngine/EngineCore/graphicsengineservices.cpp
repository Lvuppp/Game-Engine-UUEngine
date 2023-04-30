#include "graphicsengineservices.h"

GraphicsEngineServices::GraphicsEngineServices() : IGraphicsEngineServices()
{
}

GraphicsEngineServices::GraphicsEngineServices(QOpenGLFunctions *functions): IGraphicsEngineServices(functions)
{
}

GraphicsEngineServices::~GraphicsEngineServices()
{

}

void GraphicsEngineServices::processModel(Base3DGameObject *object, QOpenGLShaderProgram *shaderProgram)
{
//    auto texture = new QOpenGLTexture(object->texture()->mirrored());
//    auto vertexesBuffer = object->vertexesBuffer();
//    auto indexesBuffer = object->indexesBuffer();

//    texture->setMinificationFilter(QOpenGLTexture::Nearest);
//    texture->setMinificationFilter(QOpenGLTexture::Linear);
//    texture->setWrapMode(QOpenGLTexture::Repeat);


//    texture->bind(0);

//    shaderProgram->setUniformValue("u_texture", 0);
//    shaderProgram->setUniformValue("u_modelMatrix", object->modelMatrix());
//    shaderProgram->setUniformValue("u_specularFactor", object->specularFactor()); // блик от объекта
//    shaderProgram->setUniformValue("u_ambientFactor", object->ambiendFactor()); // свечение материала

//    vertexesBuffer->bind();
//    int offset = 0;
//    int vertLoc = shaderProgram->attributeLocation("a_position");

//    shaderProgram->enableAttributeArray(vertLoc);
//    shaderProgram->setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

//    offset += sizeof(QVector3D);
//    int textLoc = shaderProgram->attributeLocation("a_texcoord");

//    shaderProgram->enableAttributeArray(textLoc);
//    shaderProgram->setAttributeBuffer(textLoc, GL_FLOAT, offset, 2, sizeof(VertexData));

//    offset += sizeof(QVector2D);
//    int normLoc = shaderProgram->attributeLocation("a_normal");

//    shaderProgram->enableAttributeArray(normLoc);
//    shaderProgram->setAttributeBuffer(normLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

//    indexesBuffer->bind();

//    m_functions->glDrawElements(GL_TRIANGLES, indexesBuffer->size(), GL_UNSIGNED_INT, 0);

//    vertexesBuffer->release();
//    indexesBuffer->release();
//    texture->release();

}

void GraphicsEngineServices::processCamera(Camera * camera, QOpenGLShaderProgram *shaderProgram)
{
    shaderProgram->setUniformValue("u_viewMatrix", camera->modelMatrix());
}
