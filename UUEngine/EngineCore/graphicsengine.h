#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

//#include "scene.h"

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

    //Scene *getCurrentScene() const;

//    void loadScene(Scene* scene);
//    void loadScene(QVector<Scene*> scene);

    static GraphicsEngine *getInstance();

private:
    GraphicsEngine();

    GraphicsEngine(const GraphicsEngine&) = delete;
    GraphicsEngine& operator=(const GraphicsEngine&) = delete;

 //   Scene* _currentScene;
 //   QVector<Scene*> _sceneVector;
    QMatrix4x4 projectionMatrix;

    static GraphicsEngine* _instance;
};

#endif // GRAPHICSENGINE_H
