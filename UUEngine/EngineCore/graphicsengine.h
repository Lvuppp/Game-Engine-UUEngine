#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include "scene.h"
#include "base3dgameobject.h"
#include "skybox.h"
#include "objectabstractfactory.h"
#include "objectbuilder.h"

#include <QtOpenGL>
#include <GL/gl.h>
#include <QMatrix4x4>
#include <QOpenGLFramebufferObject>
#include <QVector>


//сделать классы поддвижков singltone
class GraphicsEngine
{
public:
    ~GraphicsEngine();

    void initGraphics();
    void initShaders();
    void paintScene();
    void resizeScene(int w, int h);

    void initCube(float width, float height, float depth);

    void rotateModelViewMatrix(QQuaternion rotation);
    void translateModelViewMatrix(QVector3D translation);

    void loadScene(Scene* scene);

    static GraphicsEngine *getInstance();

private:
    GraphicsEngine();

    GraphicsEngine(const GraphicsEngine&) = delete;
    GraphicsEngine& operator=(const GraphicsEngine&) = delete;

    //openGL функции
    QOpenGLFunctions *m_functions;
    QOpenGLShaderProgram m_sceneShaderProgram;
    QOpenGLShaderProgram m_skyBoxShaderProgram;
    QOpenGLShaderProgram m_depthShaderProgram;

    QMatrix4x4 m_projectionMatrix;
    ObjectAbstractFactory factory;
    ObjectBuilder builder;
    ////
    QOpenGLFramebufferObject *m_frameBuffer;
    int m_frameBufferHeight;
    int m_frameBufferWidth;
    QMatrix4x4 m_projectionLightMatrix;
    QMatrix4x4 m_lightMatrix;
    QMatrix4x4 m_shadowLightMatrix;
    ////
    Scene* m_currentScene;

    // камера и освещение во время создания сцены
    Camera *m_engineCamera;
    Lighting *m_engineLighting;
    Base3DGameObject *testObject;

    int m_windowWidth;
    int m_windowHeight;

    bool sceneStart;
    static GraphicsEngine* m_instance;
};

#endif // GRAPHICSENGINE_H
