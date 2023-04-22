#include "scenewidget.h"

SceneWidget::SceneWidget(QWidget *parent)  : QOpenGLWidget(parent)
{
    engine = new EngineCore();

}
void SceneWidget::initializeGL()
{
    engine->initGraphicsEngine();
}

void SceneWidget::resizeGL(int w, int h)
{
    engine->resizeScene(w, h);
}

void SceneWidget::paintGL()
{
    engine->paintScene();
}
