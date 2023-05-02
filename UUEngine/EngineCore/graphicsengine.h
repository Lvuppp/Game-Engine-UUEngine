#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include "scene.h"
#include "base3dgameobject.h"
#include "skybox.h"
#include "objectabstractfactory.h"

#include <QtOpenGL>
#include <GL/gl.h>
#include <QMatrix4x4>
#include <QVector>


//сделать классы поддвижков singltone
class GraphicsEngine
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

    // сделать перенос объекто текущей сцены в определённые processor-ы
    //Scene *getCurrentScene() const;

//    void loadScene(Scene* scene);
//    void loadScene(QVector<Scene*> scene);

    static GraphicsEngine *getInstance();

private:
    GraphicsEngine();

    GraphicsEngine(const GraphicsEngine&) = delete;
    GraphicsEngine& operator=(const GraphicsEngine&) = delete;

    //openGL функции
    QOpenGLFunctions *m_functions;
    QOpenGLShaderProgram m_sceneShaderProgram;
    QOpenGLShaderProgram m_skyBoxShaderProgram;

    QMatrix4x4 m_projectionMatrix;
    QVector<Model *>model;
    ObjectAbstractFactory factory;

    QVector<GLuint> indexes;
    QVector<VertexData> vertexes;
    Base3DGameObject *testObject;
    Base3DGameObject *testObject2;


    Scene* m_currentScene;

    // камера и освещение во время создания сцены
    Camera *m_engineCamera;
    Lighting *m_engineLighting;
    SkyBox *m_skyBox;

    bool sceneStart;
    static GraphicsEngine* m_instance;
};

#endif // GRAPHICSENGINE_H
