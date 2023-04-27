#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include "scene.h"
#include "base3dgameobject.h"

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
    void paintGameObjects(Base3DGameObject *object);

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
    QOpenGLShaderProgram m_shaderProgram;
//    QOpenGLBuffer vertexesBuffer;
//    QOpenGLBuffer indexesBuffer;
//    QOpenGLTexture* texture;
    QVector<GLuint> indexes;
    QVector<VertexData> vertexes;
    QQuaternion viewRotate;
    QVector3D viewTranslate;

    Scene* m_currentScene;
    QVector<Base3DGameObject *> gameObjects;

    static GraphicsEngine* m_instance;
};

#endif // GRAPHICSENGINE_H
