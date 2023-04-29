#include "graphicsengine.h"
#include "vertexdata.h"

GraphicsEngine* GraphicsEngine::m_instance = nullptr;

GraphicsEngine::GraphicsEngine()
{
    //m_functions = new QOpenGLFunctions();
    m_currentScene = new Scene();
    m_modelProcessor = ModelProcessor(&m_shaderProgram, m_functions);
    viewTranslate = QVector3D(0.0f, 0.0f, -5.0f);
}

GraphicsEngine::~GraphicsEngine()
{
    m_shaderProgram.release();
}

void GraphicsEngine::initGraphics()
{
    m_functions->initializeOpenGLFunctions();
    m_functions->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    m_functions->glEnable(GL_DEPTH_TEST);
    m_functions->glEnable(GL_CULL_FACE);

    initShaders();
    initCube(0.5f,0.5f,0.5f);

    m_currentScene->addGameObject(vertexes,indexes,QImage("/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Textures/texture1.jpg"),
                                  0.1f, 40.0f, QVector3D(0.0f,0.0f,0.0f),QQuaternion(0, 0.0f, 0.0f, 0.0f), 1);
    m_currentScene->addGameObject(vertexes,indexes,QImage("/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Textures/texture1.jpg"),
                                  0.1f, 40.0f, QVector3D(0.0f,2.0f,0.0f),QQuaternion(0, 0.0f, 0.0f, 0.0f), 1.5);
    //third = new Base3DGameObject(vertexes,indexes,QImage(),QVector3D(0.0f,0.0f,0.0f),QQuaternion(30, 1.0f, 0.0f, 0.0f), 1);

}

void GraphicsEngine::paintScene()
{
    m_functions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 viewMatrix;

    viewMatrix.setToIdentity();
    viewMatrix.translate(viewTranslate);
    viewMatrix.rotate(viewRotate);

   m_shaderProgram.bind();
   m_shaderProgram.setUniformValue("u_projectionMatrix", projectionMatrix);
   m_shaderProgram.setUniformValue("u_isDrawDynamic", true);
   m_shaderProgram.setUniformValue("u_viewMatrix", viewMatrix);
   m_shaderProgram.setUniformValue("u_lightPosition", QVector4D(0.0,0.0, 0.0,1.0)); // позиция источника света
   m_shaderProgram.setUniformValue("u_eyePosition", QVector4D(0.0,0.0, 0.0,1.0)); // позиция наблюдателя
   m_shaderProgram.setUniformValue("u_lightPower", 10.0f); // сила свечения

    for (auto object : m_currentScene->gameObjects()) {
        m_modelProcessor.processModel(object);
    }

}

void GraphicsEngine::resizeScene(int w,int h)
{
    float aspect = w / (float)h;

    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(45, aspect, 0.001f, 1000.0f);

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
