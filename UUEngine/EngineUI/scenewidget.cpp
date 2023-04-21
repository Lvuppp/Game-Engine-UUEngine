#include "scenewidget.h"

SceneWidget::SceneWidget(QWidget *parent)  : QOpenGLWidget(parent)
{
    //engine = new EngineCore();

}
void SceneWidget::initializeGL()
{
    glClearColor(1.0f,0.0f,0.0f,1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void SceneWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);

}

void SceneWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
