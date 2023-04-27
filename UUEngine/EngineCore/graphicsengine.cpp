#include "graphicsengine.h"
#include "vertexdata.h"

GraphicsEngine* GraphicsEngine::m_instance = nullptr;

GraphicsEngine::GraphicsEngine()
{
    m_currentScene = new Scene();
}

GraphicsEngine::~GraphicsEngine()
{
    m_shaderProgram.release();
}

void GraphicsEngine::initGraphics()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
    initCube(0.5f,0.5f,0.5f);

    m_currentScene->addGameObject(Base3DGameObject(vertexes,indexes,QImage(),QVector3D(0.0f,0.0f,0.0f),QQuaternion(0, 0.0f, 0.0f, 0.0f), 1));
    m_currentScene->addGameObject(Base3DGameObject(vertexes,indexes,QImage(),QVector3D(1.0f,0.0f,0.0f),QQuaternion(30, 1.0f, 1.0f, 0.0f), 1));
    m_currentScene->addGameObject(Base3DGameObject(vertexes,indexes,QImage(),QVector3D(0.0f,2.0f,0.0f),QQuaternion(0, 0.0f, 0.0f, 0.0f), 1.5));


}

void GraphicsEngine::paintScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 viewMatrix;

    viewMatrix.setToIdentity();
    viewMatrix.translate(0.0f, 0.0f, -5.0f);
    viewMatrix.rotate(viewRotate);

    m_shaderProgram.bind();
    m_shaderProgram.setUniformValue("u_projectionMatrix", projectionMatrix);
    m_shaderProgram.setUniformValue("u_viewMatrix", viewMatrix);
    m_shaderProgram.setUniformValue("u_lightPosition", QVector4D(0.0,0.0, 0.0,1.0)); // позиция источника света
    m_shaderProgram.setUniformValue("u_eyePosition", QVector4D(0.0,0.0, 0.0,1.0)); // позиция наблюдателя
    m_shaderProgram.setUniformValue("u_specularFactor", 40.0f); // блик от объекта
    m_shaderProgram.setUniformValue("u_ambientFactor", 0.1f); // свечение материала
    m_shaderProgram.setUniformValue("u_lightPower", 5.0f); // сила свечения


    for (int i = 0; i < m_currentScene->gameObjects().size(); i++) {
        paintGameObjects(m_currentScene->gameObjects().at(i));
    }
}

void GraphicsEngine::resizeScene(int w,int h)
{
    float aspect = w / (float)h;

    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(45, aspect, 0.1f, 10.0f);

}

void GraphicsEngine::paintGameObjects(Base3DGameObject *object)
{

    auto texture = object->texture();
    auto vertexesBuffer = object->vertexesBuffer();
    auto indexesBuffer = object->indexesBuffer();

    //texture->bind(0);
    //m_shaderProgram.setUniformValue("u_texture", 0);
    m_shaderProgram.setUniformValue("u_modelMatrix", object->modelMatrix());

    vertexesBuffer->bind();
    int offset = 0;
    int vertLoc = m_shaderProgram.attributeLocation("a_position");

    m_shaderProgram.enableAttributeArray(vertLoc);
    m_shaderProgram.setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);
    int textLoc = m_shaderProgram.attributeLocation("a_texcoord");

    m_shaderProgram.enableAttributeArray(textLoc);
    m_shaderProgram.setAttributeBuffer(textLoc, GL_FLOAT, offset, 2, sizeof(VertexData));

    offset += sizeof(QVector2D);
    int normLoc = m_shaderProgram.attributeLocation("a_normal");

    m_shaderProgram.enableAttributeArray(normLoc);
    m_shaderProgram.setAttributeBuffer(normLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    indexesBuffer->bind();

    QOpenGLFunctions::glDrawElements(GL_TRIANGLES, indexesBuffer->size(), GL_UNSIGNED_INT, 0);

    vertexesBuffer->release();
    indexesBuffer->release();
}

void GraphicsEngine::initShaders()
{
    qDebug() << "Start initialize shaders";

    if(!m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                               "/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Shaders/vshader.vsh"))
    {
        qDebug() << "BROKEN SHADER!";
    }

    if(!m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                               "/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Shaders/fshader.fsh")){
        qDebug() << "BROKEN SHADER!";
    }

    if(!m_shaderProgram.link()){
        qDebug() << "BROKEN LINKING!";
    }

    qDebug() << "End initialize shaders";
}

void GraphicsEngine::initCube(float width, float height, float depth){

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



    for(int i = 0; i < 24; i += 4) {
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);
        indexes.append(i + 2);
        indexes.append(i + 1);
        indexes.append(i + 3);
    }

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
    if(m_instance == nullptr){
        m_instance = new GraphicsEngine();
    }
    return m_instance;
}
