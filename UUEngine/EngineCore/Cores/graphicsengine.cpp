#include "graphicsengine.h"

#include <QOpenGLFunctions>

GraphicsEngine* GraphicsEngine::m_instance = nullptr;

GraphicsEngine::GraphicsEngine()
{
//    m_engineScene = new Scene;
//    m_engineScene->addCamera("EngineCamera");
//    m_engineScene->setCurrentCamera("EngineCamera");
//    m_engineScene->addLighting("EngineLighting");

}


GraphicsEngine::~GraphicsEngine()
{
    delete m_frameBuffer;
    delete this->currentContext()->functions();
}

void GraphicsEngine::initGraphics()
{
    this->currentContext()->functions()->initializeOpenGLFunctions();
    this->currentContext()->functions()->glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    this->currentContext()->functions()->glEnable(GL_DEPTH_TEST);
    this->currentContext()->functions()->glEnable(GL_CULL_FACE);

    initShaders();

    /// создания буффера для отображениыя тени
    m_frameBufferHeight = 1024;
    m_frameBufferWidth = 1024;

    m_frameBuffer = new QOpenGLFramebufferObject(m_frameBufferWidth, m_frameBufferHeight ,QOpenGLFramebufferObject::Depth);

    m_projectionLightMatrix.setToIdentity();
    m_projectionLightMatrix.ortho(-40.0f, 40.0f, -40.0f, 40.0f, -40.0f, 40.0f); // можно параметризировать

    float m_LightRotateY = 50;
    float m_LightRotateX = 40;

    m_shadowLightMatrix.setToIdentity();
    m_shadowLightMatrix.rotate(m_LightRotateX, 1.0f, 0.0f, 0.0f); // * Важен порядок
    m_shadowLightMatrix.rotate(m_LightRotateY, 0.0f, 1.0f, 0.0f); // *

    m_lightMatrix.setToIdentity();
    m_lightMatrix.rotate(-m_LightRotateY, 0.0f, 1.0f, 0.0f); // *
    m_lightMatrix.rotate(-m_LightRotateX, 1.0f, 0.0f, 0.0f); // *
}

void GraphicsEngine::paintScene()
{

    m_frameBuffer->bind();

    this->currentContext()->functions()->glViewport(0, 0, m_frameBufferWidth, m_frameBufferWidth);
    this->currentContext()->functions()->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_depthShaderProgram.bind();
    m_depthShaderProgram.setUniformValue("u_projectionLightMatrix", m_projectionLightMatrix);
    m_depthShaderProgram.setUniformValue("u_shadowLightMatrix", m_shadowLightMatrix);

    for (auto object : m_currentScene->gameObjects()) {
        object->draw(&m_depthShaderProgram,this->currentContext()->functions());
    }

    m_depthShaderProgram.release();
    m_frameBuffer->release();

    GLuint texture = m_frameBuffer->texture();

    this->currentContext()->functions()->glActiveTexture(GL_TEXTURE4);
    this->currentContext()->functions()->glBindTexture(GL_TEXTURE_2D, texture);

    this->currentContext()->functions()->glViewport(0, 0, m_windowWidth, m_windowHeight);
    this->currentContext()->functions()->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_skyBoxShaderProgram.bind();

    m_skyBoxShaderProgram.setUniformValue("u_projectionMatrix", m_projectionMatrix);
    m_currentScene->currentCamera()->draw(&m_skyBoxShaderProgram,this->currentContext()->functions());

    m_currentScene->skybox()->draw(&m_skyBoxShaderProgram,this->currentContext()->functions());

    m_skyBoxShaderProgram.release();

    m_sceneShaderProgram.bind();
    m_sceneShaderProgram.setUniformValue("u_shadowMap", GL_TEXTURE4 - GL_TEXTURE0);
    m_sceneShaderProgram.setUniformValue("u_ShadowPointCloudFilteringQuality", 1.5f);
    m_sceneShaderProgram.setUniformValue("u_shadowMapSize", 1024);
    m_sceneShaderProgram.setUniformValue("u_projectionMatrix", m_projectionMatrix);
    m_sceneShaderProgram.setUniformValue("u_projectionLightMatrix", m_projectionLightMatrix);
    m_sceneShaderProgram.setUniformValue("u_shadowLightMatrix", m_shadowLightMatrix);
    m_sceneShaderProgram.setUniformValue("u_lightMatrix", m_lightMatrix);
    m_sceneShaderProgram.setUniformValue("u_isDrawDynamic", false);// освещение динамическое или статическое
    m_sceneShaderProgram.setUniformValue("u_eyePosition", QVector4D(0.0f,0.0f,0.0f, 1.0f)); // позиция наблюдателя
    m_sceneShaderProgram.setUniformValue("u_lightDirection", QVector4D(0.0f,0.0f,-1.0f, 0.0f)); // позиция света
    m_sceneShaderProgram.setUniformValue("u_lightPower", 1.0f); // сила свечения


    m_currentScene->currentCamera()->draw(&m_skyBoxShaderProgram,this->currentContext()->functions());

    for (auto object : m_currentScene->gameObjects()) {
        object->draw(&m_sceneShaderProgram,this->currentContext()->functions());
    }

    m_sceneShaderProgram.release();
}

void GraphicsEngine::resizeScene(int w,int h)
{
    m_windowWidth = w;
    m_windowHeight = h;

    float aspect = w / (float)h;

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45, aspect, 0.01f, 1000.0f);

}


void GraphicsEngine::initShaders()
{
    qDebug() << "Start initialize shaders";

    try {
        m_sceneShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vshader.vsh");
        m_sceneShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fshader.fsh");
        m_sceneShaderProgram.link();

    } catch (...) {
        throw std::runtime_error("Broken main engine shaders!");
    }

    try {

        m_depthShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vdepth.vsh");
        m_depthShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fdepth.fsh");
        m_depthShaderProgram.link();

    } catch (...) {
        throw std::runtime_error("Broken depth shaders!");
    }

    try {
        m_skyBoxShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fskybox.fsh");
        m_skyBoxShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vskybox.vsh");
        m_skyBoxShaderProgram.link();
    } catch (...) {
        throw std::runtime_error("Broken skybox shaders!");
    }

    qDebug() << "End initialize shaders";
}

QMatrix4x4 GraphicsEngine::projectionMatrix() const
{
    return m_projectionMatrix;
}

void GraphicsEngine::rotateModelViewMatrix(const QQuaternion &rotationX,const QQuaternion &rotationY)
{
    if(m_currentScene == nullptr) return;
    m_currentScene->currentCamera()->rotateX(rotationX);
    m_currentScene->currentCamera()->rotateY(rotationY);
}

void GraphicsEngine::translateModelViewMatrix(QVector3D translation)
{
    if(m_currentScene == nullptr) return;
    m_currentScene->currentCamera()->translate(translation);
}

void GraphicsEngine::setCurrentScene(Scene *scene)
{
    m_currentScene = scene;
}

GraphicsEngine *GraphicsEngine::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new GraphicsEngine();
    }
    return m_instance;
}
