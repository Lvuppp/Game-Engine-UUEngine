#include "GraphicsEngine.h"

#include "Utils/Assert.h"

#include <iostream>

#include <QOpenGLContext>
#include <QOpenGLFunctions>

cGraphicsEngine::cGraphicsEngine()
    : m_gameStatus(false)
{
    m_engineCamera = new cCamera();
    m_engineLighting = new cLighting();
}

cGraphicsEngine::~cGraphicsEngine()
{
    delete m_frameBuffer;
    delete m_engineCamera;
    delete m_engineLighting;
}

void cGraphicsEngine::initGraphics()
{
    auto context = QOpenGLContext::currentContext();
    ASSERT(context, "Context is null");

    m_glFunctions = context->functions();
    ASSERT(m_glFunctions, "Failed to get OpenGL functions");

    initShaders();

    m_frameBufferHeight = 1024;
    m_frameBufferWidth = 1024;

    m_frameBuffer = new QOpenGLFramebufferObject(m_frameBufferWidth, m_frameBufferHeight, QOpenGLFramebufferObject::Depth);

    m_projectionLightMatrix.setToIdentity();
    m_projectionLightMatrix.ortho(-40.0f, 40.0f, -40.0f, 40.0f, -40.0f, 40.0f);

    float m_LightRotateY = 50.0f;
    float m_LightRotateX = 40.0f;

    m_shadowLightMatrix.setToIdentity();
    m_shadowLightMatrix.rotate(m_LightRotateX, 1.0f, 0.0f, 0.0f);
    m_shadowLightMatrix.rotate(m_LightRotateY, 0.0f, 1.0f, 0.0f);

    m_lightMatrix.setToIdentity();
    m_lightMatrix.rotate(-m_LightRotateY, 0.0f, 1.0f, 0.0f);
    m_lightMatrix.rotate(-m_LightRotateX, 1.0f, 0.0f, 0.0f);
}

void cGraphicsEngine::render()
{
    m_glFunctions->glViewport(0, 0, m_frameBufferWidth, m_frameBufferWidth);
    m_glFunctions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_currentScene == nullptr)
    {
        return;
    }

    cCamera *currentCamera = m_engineCamera;

    if (m_gameStatus)
    {
        currentCamera = m_currentScene->currentCamera();
    }

    m_frameBuffer->bind();
    m_depthShaderProgram.bind();
    m_depthShaderProgram.setUniformValue("u_projectionLightMatrix", m_projectionLightMatrix);
    m_depthShaderProgram.setUniformValue("u_shadowLightMatrix", m_shadowLightMatrix);

    for (auto object : m_currentScene->gameObjects())
    {
        object->draw(&m_depthShaderProgram, m_glFunctions, false);
    }

    m_depthShaderProgram.release();
    m_frameBuffer->release();

    GLuint texture = m_frameBuffer->texture();

    m_glFunctions->glActiveTexture(GL_TEXTURE4);
    m_glFunctions->glBindTexture(GL_TEXTURE_2D, texture);

    m_glFunctions->glViewport(0, 0, m_windowWidth, m_windowHeight);
    m_glFunctions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_skyBoxShaderProgram.bind();

    m_skyBoxShaderProgram.setUniformValue("u_projectionMatrix", m_projectionMatrix);
    currentCamera->draw(&m_skyBoxShaderProgram, m_glFunctions, false);

    if (m_currentScene->skybox())
    {
        m_currentScene->skybox()->draw(&m_skyBoxShaderProgram, m_glFunctions, true);
    }

    m_skyBoxShaderProgram.release();

    m_sceneShaderProgram.bind();

    m_sceneShaderProgram.setUniformValue("u_shadowMap", GL_TEXTURE4 - GL_TEXTURE0);
    m_sceneShaderProgram.setUniformValue("u_ShadowPointCloudFilteringQuality", 1.5f);
    m_sceneShaderProgram.setUniformValue("u_shadowMapSize", 1024);
    m_sceneShaderProgram.setUniformValue("u_projectionMatrix", m_projectionMatrix);
    m_sceneShaderProgram.setUniformValue("u_projectionLightMatrix", m_projectionLightMatrix);
    m_sceneShaderProgram.setUniformValue("u_shadowLightMatrix", m_shadowLightMatrix);
    m_sceneShaderProgram.setUniformValue("u_lightMatrix", m_lightMatrix);
    m_sceneShaderProgram.setUniformValue("u_isDrawDynamic", false);
    m_sceneShaderProgram.setUniformValue("u_eyePosition", QVector4D(0.0f,0.0f,0.0f, 1.0f));
    m_sceneShaderProgram.setUniformValue("u_lightDirection", QVector4D(0.0f,0.0f,-1.0f, 0.0f)); // позиция света
    m_sceneShaderProgram.setUniformValue("u_lightPower", 1.0f); // сила свечения

    currentCamera->draw(&m_sceneShaderProgram, m_glFunctions, false);

    for (auto object : m_currentScene->gameObjects())
    {
        object->draw(&m_sceneShaderProgram, m_glFunctions, true);
    }

    m_sceneShaderProgram.release();
}

void cGraphicsEngine::resizeScene(int w,int h)
{
    m_windowWidth = w;
    m_windowHeight = h;

    float aspect = w / static_cast<float>(h);

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45, aspect, 0.01f, 1000.0f);

}

cBaseEngineObject *cGraphicsEngine::selectObject(const QPoint &mouseCoordinates)
{
    if(m_gameStatus)
    {
        return nullptr;
    }

    m_glFunctions->glViewport(0, 0, m_windowWidth, m_windowHeight);
    m_glFunctions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_glFunctions->glEnable(GL_DEPTH_TEST); //для корректной работы оси z: дальние объекты не должны перекрывать ближние

    m_selectShaderProgram.bind();
    m_selectShaderProgram.setUniformValue("u_projectionMatrix", m_projectionMatrix);;
    m_engineCamera->draw(&m_selectShaderProgram, nullptr, false);

    for (qsizetype i = 0; i < m_currentScene->gameObjects().size(); ++i) {

        m_selectShaderProgram.setUniformValue("u_code", float(i + 1)); //i + 1 чтоб не совпадал с цветом фона (чёрный)
        m_currentScene->gameObjects().at(i)->draw(&m_selectShaderProgram, m_glFunctions, false);
    }

    m_selectShaderProgram.release();

    GLint viewport[4]; //x, y, w, h
    m_glFunctions->glGetIntegerv(GL_VIEWPORT, viewport);

    unsigned char res[4]; //4 компоненты RGBA, каждый по байту, [0-255], поэтому такой тип данных

    //1, 1 - ширина и высота пикселя который нужно считать под указателем мыши
    m_glFunctions->glReadPixels(mouseCoordinates.x(), viewport[3] - mouseCoordinates.y(), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);

    m_glFunctions->glDisable(GL_DEPTH_TEST);

    if(res[0] - 1 == -1) return nullptr;
    return m_currentScene->gameObjects()[res[0] - 1]; //красная компонента
}


void cGraphicsEngine::initShaders()
{
    std::cout << "Start initialize shaders" << std::endl;

    if (m_sceneShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vshader.vsh") == false)
    {
        std::cout << "Failed to load vertex shader: " + m_sceneShaderProgram.log().toStdString() << std::endl;
    }

    if (m_sceneShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fshader.fsh") == false)
    {
        std::cout << "Failed to load fragment shader: " + m_sceneShaderProgram.log().toStdString() << std::endl;
    }

    if (m_sceneShaderProgram.link() == false)
    {
        std::cout << "Failed to link shader program: " + m_sceneShaderProgram.log().toStdString() << std::endl;
    }

    if (m_depthShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vdepth.vsh") == false)
    {
        std::cout << "Failed to load depth vertex shader: " + m_depthShaderProgram.log().toStdString() << std::endl;
    }

    if (m_depthShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fdepth.fsh") == false)
    {
        std::cout << "Failed to load depth fragment shader: " + m_depthShaderProgram.log().toStdString() << std::endl;
    }

    if (m_depthShaderProgram.link() == false)
    {
        std::cout << "Failed to link depth shader program: " + m_depthShaderProgram.log().toStdString() << std::endl;
    }

    if (m_skyBoxShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fskybox.fsh") == false)
    {
        std::cout << "Failed to load skybox fragment shader: " + m_skyBoxShaderProgram.log().toStdString() << std::endl;
    }

    if (m_skyBoxShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vskybox.vsh") == false)
    {
        std::cout << "Failed to load skybox vertex shader: " + m_skyBoxShaderProgram.log().toStdString() << std::endl;
    }

    if (m_skyBoxShaderProgram.link() == false)
    {
        std::cout << "Failed to link skybox shader program: " + m_skyBoxShaderProgram.log().toStdString() << std::endl;
    }


    if (m_selectShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fselectshader.fsh") == false)
    {
        std::cout << "Failed to load select fragment shader: " + m_selectShaderProgram.log().toStdString() << std::endl;
    }

    if (m_selectShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vselectshader.vsh") == false)
    {
        std::cout << "Failed to load select vertex shader: " + m_selectShaderProgram.log().toStdString() << std::endl;
    }

    if (m_selectShaderProgram.link() == false)
    {
        std::cout << "Failed to link select shader program: " + m_selectShaderProgram.log().toStdString() << std::endl;
    }

    std::cout << "End initialize shaders" << std::endl;
}

QMatrix4x4 cGraphicsEngine::projectionMatrix() const
{
    return m_projectionMatrix;
}

QMatrix4x4 cGraphicsEngine::cameraViewMatrix() const
{
    return m_engineCamera->modelMatrix();
}

void cGraphicsEngine::changeGameStatus()
{
    m_gameStatus = !m_gameStatus;
}

void cGraphicsEngine::rotateModelViewMatrix(const QQuaternion &rotationX,const QQuaternion &rotationY)
{
    m_engineCamera->rotateX(rotationX);
    m_engineCamera->rotateY(rotationY);
}

void cGraphicsEngine::translateModelViewMatrix(QVector3D translation)
{
    m_engineCamera->translate(translation);
}

void cGraphicsEngine::setCurrentScene(cScene *scene)
{
    m_currentScene = scene;
}
