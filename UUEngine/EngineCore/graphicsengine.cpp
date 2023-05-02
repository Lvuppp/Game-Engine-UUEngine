#include "graphicsengine.h"
#include "vertexdata.h"

GraphicsEngine* GraphicsEngine::m_instance = nullptr;

GraphicsEngine::GraphicsEngine()
{
    m_currentScene = new Scene();

}

GraphicsEngine::~GraphicsEngine()
{
}

void GraphicsEngine::initGraphics()
{
    m_functions->initializeOpenGLFunctions();
    m_functions->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    m_functions->glEnable(GL_DEPTH_TEST);
    m_functions->glEnable(GL_CULL_FACE);

    initShaders();
    initCube(0.5f,0.5f,0.5f);

    testObject2 = factory.createObject("/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Models/TestModel/Stone.obj");

//    m_currentScene->addGameObject(new Base3DGameObject(vertexes,indexes,QImage("/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Textures/texture1.jpg"),
//                                                       0.1f, 40.0f, QVector3D(0.0f,-2.0f,0.0f),QQuaternion(0, 0.0f, 0.0f, 0.0f), 1));
//    m_currentScene->addGameObject(new Base3DGameObject(vertexes,indexes,QImage("/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Textures/texture1.jpg"),
//                                                       0.1f, 40.0f, QVector3D(0.0f,2.0f,0.0f),QQuaternion(0, 0.0f, 0.0f, 0.0f), 1.5));
    Material *material = new Material();
    material->setAmbienceColor(QVector3D(0.0f,0.0f,0.0f));
    material->setDiffuseColor(QVector3D(0.1f,0.0f,0.0f));
    material->setSpecularColor(QVector3D(0.1f,0.1f,0.1f));
    material->setShinnes(60.0f);

    material->setDiffuseMap("/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Textures/texture1.jpg");

    model.append(new Model(vertexes,indexes,material));

    testObject = new Base3DGameObject();
    testObject->setModel(model);
    testObject->setScale(0.5f);
    testObject2->setScale(0.1f);
    m_engineCamera = new Camera(QVector3D(0.0f, 0.0f, -5.0f));
    m_skyBox = new SkyBox(50.0f, QImage("/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Textures/skybox4.png"));

}

void GraphicsEngine::paintScene()
{
    m_functions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_skyBoxShaderProgram.bind();
    m_skyBoxShaderProgram.setUniformValue("u_projectionMatrix", m_projectionMatrix);

    //m_graphicsServies->processCamera(m_engineCamera, &m_sceneShaderProgram);

    //m_engineCamera->draw(&m_sceneShaderProgram,m_functions);
    //m_skyBox->model()->draw(&m_skyBoxShaderProgram,m_functions);

    m_skyBoxShaderProgram.release();

    m_sceneShaderProgram.bind();

    m_sceneShaderProgram.setUniformValue("u_projectionMatrix", m_projectionMatrix);
    m_sceneShaderProgram.setUniformValue("u_isDrawDynamic", true);// освещение динамическое или статическое
    m_sceneShaderProgram.setUniformValue("u_lightPosition", QVector4D(0.0,0.0,0.0,1.0)); // позиция источника света
    m_sceneShaderProgram.setUniformValue("u_eyePosition", QVector4D(0.0,0.0, 0.0,1.0)); // позиция наблюдателя
    m_sceneShaderProgram.setUniformValue("u_lightPower", 5.0f); // сила свечения


    for (auto object : m_currentScene->gameObjects()) {
        //object->draw(&m_sceneShaderProgram,m_functions);
    }
    m_engineCamera->draw(&m_sceneShaderProgram,m_functions);
    testObject->draw(&m_sceneShaderProgram,m_functions);
    testObject2->draw(&m_sceneShaderProgram,m_functions);

    m_sceneShaderProgram.release();
}

void GraphicsEngine::resizeScene(int w,int h)
{
    float aspect = w / (float)h;

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45, aspect, 0.01f, 1000.0f);

}


void GraphicsEngine::initShaders()
{
    qDebug() << "Start initialize shaders";
    
    if(!m_sceneShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                               "/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Shaders/vshader.vsh")){
        qDebug() << "BROKEN SHADER!";
    }
    
    if(!m_sceneShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                               "/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Shaders/fshader.fsh")){
        qDebug() << "BROKEN SHADER!";
    }

    if(!m_sceneShaderProgram.link()){
        qDebug() << "BROKEN LINKING!";
    }

    if(!m_skyBoxShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                                "/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Shaders/fskybox.fsh")){
        qDebug() << "BROKEN SHADER!";
    }

    if(!m_skyBoxShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                                "/home/egorbagrovets/OOP_Coursework/UUEngine/EngineCore/Shaders/vskybox.vsh")){
        qDebug() << "BROKEN SHADER!";
    }

    if(!m_skyBoxShaderProgram.link()){
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
    m_engineCamera->rotate(rotation);
}

void GraphicsEngine::translateModelViewMatrix(QVector3D translation)
{
    m_engineCamera->translate(translation);
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
