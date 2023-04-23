#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

//#include "scene.h"

#include <QtOpenGL>
#include <GL/gl.h>

#include <QMatrix4x4>
#include <QVector>

struct VertexData{
    VertexData(){

    }
    VertexData(QVector3D position, QVector2D texture, QVector3D normal):
        position(position), normal(normal), texture(texture){};

    QVector3D position;
    QVector3D normal;
    QVector2D texture;

};

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

    //   Scene* _currentScene;
    //   QVector<Scene*> _sceneVector;

    static GraphicsEngine* _instance;
};

#endif // GRAPHICSENGINE_H
