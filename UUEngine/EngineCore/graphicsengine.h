#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

//#include "scene.h"

#include <QtOpenGL>
#include <GL/gl.h>
#include <QMatrix4x4>
#include <QVector>


//сделать классы поддвижков singltone
class GraphicsEngine : public QOpenGLFunctions
{
public:
    ~GraphicsEngine();

    void initGraphics();
    void paintScene();
    void resizeScene(int w, int h);

    void initShaders();
    void initCube(float width, float height, float depth);

    void rotateModelViewMatrix(QQuaternion rotation);
    void translateModelViewMatrix(QVector3D translation);

    //Scene *getCurrentScene() const;

//    void loadScene(Scene* scene);
//    void loadScene(QVector<Scene*> scene);

    static GraphicsEngine *getInstance();

private:
    GraphicsEngine();

    GraphicsEngine(const GraphicsEngine&) = delete;
    GraphicsEngine& operator=(const GraphicsEngine&) = delete;

    QMatrix4x4 projectionMatrix;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vertexesBuffer;
    QOpenGLBuffer indexesBuffer;
    QOpenGLTexture* texture;

    QQuaternion modelViewRotate;
    QVector3D modelViewTranslate;

    //   Scene* _currentScene;
    //   QVector<Scene*> _sceneVector;

    static GraphicsEngine* _instance;
};

#endif // GRAPHICSENGINE_H
