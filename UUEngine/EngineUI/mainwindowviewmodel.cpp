#include "mainwindowviewmodel.h"

MainWindowViewModel::MainWindowViewModel(QWidget *parent)  : QOpenGLWidget(parent)
{
    engine = new EngineCore();

    connect(this, &MainWindowViewModel::mousePressEvent, engine, &EngineCore::getEvent);
    connect(this, &MainWindowViewModel::mouseMoveEvent, engine, &EngineCore::getEvent);
    connect(this, &MainWindowViewModel::wheelEvent, engine, &EngineCore::getEvent);
    connect(engine, &EngineCore::updateGraphics, this, &MainWindowViewModel::updateGraphics);

    QVBoxLayout *layout = new QVBoxLayout();

    emit setProjectLayout(nullptr);

}

void MainWindowViewModel::updateGraphics()
{
    update();
}

void MainWindowViewModel::loadProject()
{

}


void MainWindowViewModel::initializeGL()
{
    engine->initGraphicsEngine();
}

void MainWindowViewModel::resizeGL(int w, int h)
{
    engine->resizeScene(w, h);
}

void MainWindowViewModel::paintGL()
{
    engine->paintScene();
}

