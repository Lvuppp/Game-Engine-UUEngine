#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include "enginecore.h"

#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>

class SceneWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    SceneWidget(QWidget *parent);

signals:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void createObjects();

public slots:
    void updateGraphics();

public:
    void testLoadFromUI();

private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    EngineCore* engine;
};

#endif // SCENEWIDGET_H
