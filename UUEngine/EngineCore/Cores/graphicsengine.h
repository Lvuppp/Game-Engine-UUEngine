#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include "scene.h"

#include <QtOpenGL>
#include <GL/gl.h>
#include <QMatrix4x4>
#include <QOpenGLFramebufferObject>
#include <QVector>


//сделать классы поддвижков singltone
class GraphicsEngine : QOpenGLContext
{
public:
    ~GraphicsEngine();

    void initGraphics();
    void initShaders();
    void paintScene();
    void resizeScene(int w, int h);

    BaseEngineObject *selectObject(const QPoint &mouseCoordinates);

    void rotateModelViewMatrix(const QQuaternion &rotationX,const QQuaternion &rotationY);
    void translateModelViewMatrix(QVector3D translation);

    void setCurrentScene(Scene* scene);

    QMatrix4x4 projectionMatrix() const;
    QMatrix4x4 cameraViewMatrix() const;

public:
    static GraphicsEngine *getInstance();

private:
    GraphicsEngine();

    GraphicsEngine(const GraphicsEngine&) = delete;
    GraphicsEngine& operator=(const GraphicsEngine&) = delete;

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
    Scene *m_currentScene;
    //камера и освещениме движка
    Camera *m_engineCamera;
    Lighting *m_engineLighting;

    int m_windowWidth;
    int m_windowHeight;

    bool m_isSceneStart = false;
    static GraphicsEngine* m_instance;
};

#endif // GRAPHICSENGINE_H
