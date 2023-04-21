#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLFunctions>

class GraphicsEngine : protected QOpenGLFunctions
{
public:
    ~GraphicsEngine();

    void initGraphics(){

    };
    void paintScene(){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
;
    void resizeScene(int w, int h){

    };

    //Scene *getCurrentScene() const;

//    void loadScene(Scene* scene);
//    void loadScene(QVector<Scene*> scene);

//    static GraphicsEngine *getInstance();

private:
    GraphicsEngine();

    GraphicsEngine(const GraphicsEngine&) = delete;
    GraphicsEngine& operator=(const GraphicsEngine&) = delete;

 //   Scene* _currentScene;
 //   QVector<Scene*> _sceneVector;


};

//Scene *GraphicsEngine::getCurrentScene() const
//{
//    return _currentScene;
//}


//void GraphicsEngine::loadScene(Scene *scene)
//{

//}

//void GraphicsEngine::loadScene(QVector<Scene *> scene)
//{

//}


class SceneWidget : public QOpenGLWidget
{

    Q_OBJECT
public:
    SceneWidget(QWidget *parent);
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    QMatrix4x4 projectionMatrix;
};

#endif // SCENEWIDGET_H
