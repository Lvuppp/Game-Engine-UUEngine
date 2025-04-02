#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include "Scene.h"

#include <QtOpenGL>
#include <GL/gl.h>
#include <QMatrix4x4>
#include <QOpenGLFramebufferObject>
#include <QVector>


//сделать классы поддвижков singltone
class cGraphicsEngine : QOpenGLContext
{
public:
    ~cGraphicsEngine();

    void initGraphics();
    void initShaders();
    void paintScene();
    void resizeScene(int w, int h);

    cBaseEngineObject *selectObject(const QPoint &mouseCoordinates);

    void rotateModelViewMatrix(const QQuaternion &rotationX,const QQuaternion &rotationY);
    void translateModelViewMatrix(QVector3D translation);

    void setCurrentScene(cScene* scene);

    QMatrix4x4 projectionMatrix() const;
    QMatrix4x4 cameraViewMatrix() const;

    void changeGameStatus();

public:
    static cGraphicsEngine *getInstance();

private:
    cGraphicsEngine();

    cGraphicsEngine(const cGraphicsEngine&) = delete;
    cGraphicsEngine& operator=(const cGraphicsEngine&) = delete;

    //openGL поля
    QOpenGLShaderProgram m_sceneShaderProgram;
    QOpenGLShaderProgram m_skyBoxShaderProgram;
    QOpenGLShaderProgram m_depthShaderProgram;
    QOpenGLShaderProgram m_selectShaderProgram;

    QMatrix4x4 m_projectionMatrix;
    //поля тени
    QOpenGLFramebufferObject *m_frameBuffer;
    int m_frameBufferHeight;
    int m_frameBufferWidth;
    QMatrix4x4 m_projectionLightMatrix;
    QMatrix4x4 m_lightMatrix;
    QMatrix4x4 m_shadowLightMatrix;

    //поле сцены
    cScene *m_currentScene;
    //камера и освещениме движка
    cCamera *m_engineCamera;
    cLighting *m_engineLighting;

    int m_windowWidth;
    int m_windowHeight;

    bool m_gameStatus;
    static cGraphicsEngine* m_instance;
};

#endif // GRAPHICSENGINE_H
