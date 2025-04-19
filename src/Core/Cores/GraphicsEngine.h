#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include "Entities/Scene.h"

#include <QtOpenGL>
#include <GL/gl.h>
#include <QMatrix4x4>
#include <QOpenGLFramebufferObject>
#include <vector>

//сделать классы поддвижков singltone
class cGraphicsEngine
{
public:
    cGraphicsEngine();
    ~cGraphicsEngine();

    cGraphicsEngine(const cGraphicsEngine&) = delete;
    cGraphicsEngine& operator=(const cGraphicsEngine&) = delete;

    void initGraphics();
    void initShaders();
    void render();
    void resizeScene(int w, int h);

    cBaseEngineObject *selectObject(const QPoint &mouseCoordinates);

    void rotateModelViewMatrix(const QQuaternion &rotationX,const QQuaternion &rotationY);
    void translateModelViewMatrix(QVector3D translation);

    void setCurrentScene(cScene* scene);

    QMatrix4x4 projectionMatrix() const;
    QMatrix4x4 cameraViewMatrix() const;

    void changeGameStatus();

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

    bool m_gameStatus;
};
#endif // GRAPHICSENGINE_H
