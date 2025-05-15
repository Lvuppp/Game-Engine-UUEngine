#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include "Core/Services/ModelBuilder.h"
#include "Entities/BaseEntities/Base3DGameObject.h"
#include "Entities/Scene.h"

#include <QtOpenGL>
#include <GL/gl.h>
#include <QMatrix4x4>
#include <QOpenGLFramebufferObject>

class cBaseEngineObject;

class cGraphicsEngine
{
public:
    cGraphicsEngine() = default;
    ~cGraphicsEngine();

    cGraphicsEngine(const cGraphicsEngine&) = delete;
    cGraphicsEngine& operator=(const cGraphicsEngine&) = delete;

    void initGraphics();
    void initShaders();
    void render();
    void resizeScene(int w, int h);

    cBaseEngineObject *selectObject(const QPoint &mouseCoordinates);
    void setCurrentScene(cScene* scene);

    const QMatrix4x4& getProjectionMatrix() const;

    void changeGameStatus();

    void testShaders();

private:
    QOpenGLFunctions* m_glFunctions = nullptr;
    QOpenGLFramebufferObject *m_frameBuffer = nullptr;

    QOpenGLShaderProgram m_sceneShaderProgram;
    QOpenGLShaderProgram m_skyBoxShaderProgram;
    QOpenGLShaderProgram m_depthShaderProgram;
    QOpenGLShaderProgram m_selectShaderProgram;

    QMatrix4x4 m_projectionMatrix;
    int m_frameBufferHeight;
    int m_frameBufferWidth;

    QMatrix4x4 m_projectionLightMatrix;
    QMatrix4x4 m_lightMatrix;
    QMatrix4x4 m_shadowLightMatrix;

    cScene* m_currentScene = nullptr;
    cCamera* m_engineCamera = nullptr;
    cLighting* m_engineLighting = nullptr;

    int m_windowWidth;
    int m_windowHeight;

    bool m_gameStatus = false;

    void testSceneShader();
    void testSkyboxShader();
    void testDepthShader();
    void testSelectShader();

    void renderTestCube(QOpenGLShaderProgram* shader);

    std::unique_ptr<cBase3DGameObject> m_testCube;
    cModelBuilder m_modelBuilder;
};
#endif // GRAPHICSENGINE_H
