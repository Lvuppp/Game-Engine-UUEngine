#include "graphicsengine.h"

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
    initCube(1.0f, 1.0f, 1.0f);
}

void GraphicsEngine::paintScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.setToIdentity();
    modelViewMatrix.translate(0.0f,0.0f,-5.0f);
    modelViewMatrix.rotate(30, 1.0f, 0.0f, 0.0f);
    modelViewMatrix.rotate(30, 0.0f, 1.0f, 0.0f);

    texture->bind(0);

    shaderProgram.bind();
    shaderProgram.setUniformValue("qt_ModelViewProjectionMatrix", projectionMatrix * modelViewMatrix);
    shaderProgram.setUniformValue("qt_TexCoord0", 0);

    vertexesBuffer.bind();

    int offset = 0;
    int vertLoc = shaderProgram.attributeLocation("qt_Vertex");

    shaderProgram.enableAttributeArray(vertLoc);
    shaderProgram.setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);
    int textLoc = shaderProgram.attributeLocation("qt_MultiTextCoord0");

    shaderProgram.enableAttributeArray(textLoc);
    shaderProgram.setAttributeBuffer(textLoc, GL_FLOAT, offset, 2, sizeof(VertexData));

    indexesBuffer.bind();

    glDrawElements(GL_TRIANGLES, indexesBuffer.size(), GL_UNSIGNED_INT, 0);
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

    texture = new QOpenGLTexture(QImage("/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Textures/test_block.png").mirrored());

    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMinificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);
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
