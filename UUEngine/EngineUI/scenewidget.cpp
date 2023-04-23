#include "scenewidget.h"

SceneWidget::SceneWidget(QWidget *parent)  : QOpenGLWidget(parent)
{
    engine = new EngineCore();

    connect(this, &SceneWidget::mousePressEvent, engine, &EngineCore::getEvent);
    connect(this, &SceneWidget::mouseMoveEvent, engine, &EngineCore::getEvent);
    connect(engine, &EngineCore::updateGraphics, this, &SceneWidget::updateGraphics);

}

void SceneWidget::updateGraphics()
{
    update();
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

