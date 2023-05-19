#ifndef MAINWINDOWVIEWMODEL_H
#define MAINWINDOWVIEWMODEL_H

#include "Cores/enginecore.h"

#include <QOpenGLWidget>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QWheelEvent>

class MainWindowViewModel : public QOpenGLWidget
{
    Q_OBJECT
public:
    MainWindowViewModel(QWidget *parent);

signals:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void createObjects();
    void setProjectLayout(QLayout *layout);

public slots:
    void updateGraphics();
    void loadProject();

private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    EngineCore* engine;
};

#endif // MAINWINDOWVIEWMODEL_H
