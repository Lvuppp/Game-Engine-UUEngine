#include "graphicsengine.h"
#include "vertexdata.h"

GraphicsEngine* GraphicsEngine::_instance = nullptr;

GraphicsEngine::GraphicsEngine()
{
    indexesBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
}

GraphicsEngine::~GraphicsEngine()
{

}

void GraphicsEngine::initGraphics()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
    initCube(0.5,1.5,0.5);
}

void GraphicsEngine::paintScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 viewMatrix;

    viewMatrix.setToIdentity();
    viewMatrix.translate(0.0f, 0.0f, -5.0f);
    viewMatrix.rotate(viewRotate);

    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();

    texture->bind(0);

    shaderProgram.bind();
    shaderProgram.setUniformValue("u_projectionMatrix", projectionMatrix);
    shaderProgram.setUniformValue("u_viewMatrix", viewMatrix);
    shaderProgram.setUniformValue("u_modelMatrix", modelMatrix);
    shaderProgram.setUniformValue("u_lightPosition", QVector4D(0.0,0.0, 0.0,1.0)); // позиция источника света
    shaderProgram.setUniformValue("u_eyePosition", QVector4D(0.0,0.0, 0.0,1.0)); // позиция наблюдателя
    shaderProgram.setUniformValue("u_specularFactor", 40.0f); // блик от объекта
    shaderProgram.setUniformValue("u_ambientFactor", 0.1f); // свечение материала
    shaderProgram.setUniformValue("u_lightPower", 5.0f); // сила свечения
    shaderProgram.setUniformValue("u_texture", 0);

    vertexesBuffer.bind();
    int offset = 0;
    int vertLoc = shaderProgram.attributeLocation("a_position");

    shaderProgram.enableAttributeArray(vertLoc);
    shaderProgram.setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);
    int textLoc = shaderProgram.attributeLocation("a_texcoord");

    shaderProgram.enableAttributeArray(textLoc);
    shaderProgram.setAttributeBuffer(textLoc, GL_FLOAT, offset, 2, sizeof(VertexData));

    offset += sizeof(QVector2D);
    int normLoc = shaderProgram.attributeLocation("a_normal");

    shaderProgram.enableAttributeArray(normLoc);
    shaderProgram.setAttributeBuffer(normLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    indexesBuffer.bind();

    QOpenGLFunctions::glDrawElements(GL_TRIANGLES, indexesBuffer.size(), GL_UNSIGNED_INT, 0);
}

void GraphicsEngine::resizeScene(int w,int h)
{
    float aspect = w / (float)h;

    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(45, aspect, 0.1f, 10.0f);

}

void GraphicsEngine::initShaders()
{
    qDebug() << "Start initialize shaders";

    if(!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                               "/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Shaders/vshader.vsh"))
    {
        qDebug() << "BROKEN SHADER!";
    }

    if(!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                               "/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Shaders/fshader.fsh")){
        qDebug() << "BROKEN SHADER!";
    }

    if(!shaderProgram.link()){
        qDebug() << "BROKEN LINKING!";
    }

    qDebug() << "End initialize shaders";
}

void GraphicsEngine::initCube(float width, float height, float depth){

    QVector<VertexData> vertexes;

    vertexes.append(VertexData(QVector3D(-width, height, depth), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-width, -height, depth), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width, height, depth), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width, -height, depth), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));

    vertexes.append(VertexData(QVector3D(width, height, depth), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width, -height, depth), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width, height, -depth), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width, -height, -depth), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width, height, depth), QVector2D(0.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width, height, -depth), QVector2D(0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width, height, depth), QVector2D(1.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width, height, -depth), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width, height, -depth), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(width, -height, -depth), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width, height, -depth), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width, -height, -depth), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));

    vertexes.append(VertexData(QVector3D(-width, height, depth), QVector2D(0.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width, height, -depth), QVector2D(0.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width, -height, depth), QVector2D(1.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width, -height, -depth), QVector2D(1.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(-width, -height, depth), QVector2D(0.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width, -height, -depth), QVector2D(0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width, -height, depth), QVector2D(1.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width, -height, -depth), QVector2D(1.0, 0.0), QVector3D(0.0, -1.0, 0.0)));

    QVector<GLuint> indexes;

    for(int i = 0; i < 24; i += 4) {
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);
        indexes.append(i + 2);
        indexes.append(i + 1);
        indexes.append(i + 3);
    }


    vertexesBuffer.create();
    vertexesBuffer.bind();
    vertexesBuffer.allocate(vertexes.constData(),vertexes.size() * sizeof(VertexData));
    vertexesBuffer.release();

    indexesBuffer.create();
    indexesBuffer.bind();
    indexesBuffer.allocate(indexes.constData(),indexes.size() * sizeof(GLuint));
    indexesBuffer.release();

    texture = new QOpenGLTexture(QImage("/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Textures/texture1.jpg").mirrored());

    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMinificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void GraphicsEngine::rotateModelViewMatrix(QQuaternion rotation)
{
    viewRotate *= rotation;
}

void GraphicsEngine::translateModelViewMatrix(QVector3D translation)
{
    viewTranslate += translation;
}

//Scene *GraphicsEngine::getCurrentScene() const
//{
//    return _currentScene;
//}


//void GraphicsEngine::loadScene(Scene *scene)
//{

//}

//void GraphicsEngine::loadScene(QVector<Scene *> scene)
//{

//}

GraphicsEngine *GraphicsEngine::getInstance()
{
    if(_instance == nullptr){
        _instance = new GraphicsEngine();
    }
    return _instance;
}
